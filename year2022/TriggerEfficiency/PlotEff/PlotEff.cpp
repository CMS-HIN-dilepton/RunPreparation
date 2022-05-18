
#include"TEfficiency.h"

#include"PlotEff.h"
#include"MultiPlotEff.h"
#include"../OniaIO/OniaIO.h"
#include"../Utils/Utils.h"

#include<iostream>

void produceOutput(HistPair out, const std::string& outputpath);
void produceOutput(Hist2Pair out, const std::string& outputpath);
void readTotals(TFile* inputFile, Output* out, bool isup);
void readPass(TFile* inputFile, Output* output,bool isup);
Output allocateOutput(bool highPt);

bool Isfoward(bool isfwd, float pt, float absrap){
	if(isfwd){
		if(absrap<2.4 && absrap>1.6) return pt>3;
		else return false;
	}

	else{
		if(absrap <1.6) return pt>6.5;
		else return false;
	}
}



void PlotEff(const char* inputfilename, const char* outputFilename, const char* ptRange, const char* type)
{
	std::string outFilename=outputFilename;
	bool isup = std::string(type).find("Up")!=std::string::npos;
	TFile* inputFile= OpenFile(inputfilename);
	if (inputFile==nullptr) return;

	TFile* outputFile= CreateFile(outFilename+"/hist.root");
	std::cout<<isup<<std::endl;
	bool isHighPt=std::string(ptRange)!="lowpt";
	if (isHighPt)
		std::cout << "in high pt range.\n";
	else
		std::cout << "in low pt range.\n";

	Output output=allocateOutput(isHighPt);

	readTotals(inputFile,&output,isup);
	readPass(inputFile,&output,isup);

	produceOutput(output.y,outFilename);
	produceOutput(output.pt,outFilename);
	produceOutput(output.cent,outFilename);
	produceOutput(output.pt_fwd,outFilename);
	produceOutput(output.pt_mid,outFilename);
	produceOutput(output.pt_y,outFilename);

	delete inputFile;
	delete outputFile;
}

void readTotals(TFile* inputFile, Output* output,bool isup)
{
	TTree* oniaTreeTotal= OpenTree(inputFile,"total");
	Reader<OniaOutput> onia(oniaTreeTotal);

	Long64_t entries= oniaTreeTotal->GetEntries();
	if(!(isup)){
		for(Long64_t i=0;i<entries;i++)
		{
			auto input= onia.readEntry(i);
			if(fabs(input->y)<2.4 && (input->pt)>6.5)  output->pt.den->Fill(input->pt);
			output->cent.den->Fill(input->cent);
			if(input->pt>6.5) output->y.den->Fill(input->y);
			output->pt_y.den->Fill(input->y,input->pt);
			if (Isfoward(1,input->pt,fabs(input->y))) output->pt_fwd.den->Fill(input->pt);
			if(Isfoward(0,input->pt,fabs(input->y))) output->pt_mid.den->Fill(input->pt);
		}
	}	
	else{  
		for(Long64_t i=0;i<entries;i++)
		{
			auto input= onia.readEntry(i);
			if(fabs(input->y)<2.4 && (input->pt)>0)  output->pt.den->Fill(input->pt);
			output->cent.den->Fill(input->cent);
			if(input->pt>0) output->y.den->Fill(input->y);
			output->pt_y.den->Fill(input->y,input->pt);
		}	
	}
}

void readPass(TFile* inputFile, Output* output, bool isup)
{
	TTree* oniaTreePass= OpenTree(inputFile,"pass");
	Reader<OniaOutput> onia(oniaTreePass);

	Long64_t entries= oniaTreePass->GetEntries();
	if(!(isup)){
		for(Long64_t i=0;i<entries;i++)
		{
			auto input= onia.readEntry(i);
			if(fabs(input->y)<2.4 && (input->pt)>6.5){ output->pt.num->Fill(input->pt);}
			//std::cout<<input->pt<<std::endl;}
			output->cent.num->Fill(input->cent);
			if(input->pt>6.5) output->y.num->Fill(input->y);
			output->pt_y.num->Fill(input->y,input->pt);
			if (Isfoward(1,input->pt,fabs(input->y))) output->pt_fwd.num->Fill(input->pt);
			if(Isfoward(0,input->pt,fabs(input->y)))output->pt_mid.num->Fill(input->pt);
		}
		}
	else{  
		for(Long64_t i=0;i<entries;i++)
		{
			auto input= onia.readEntry(i);
			if(fabs(input->y)<2.4 && (input->pt)>0)  output->pt.num->Fill(input->pt);
			output->cent.num->Fill(input->cent);
			if(input->pt>0) output->y.num->Fill(input->y);
			output->pt_y.num->Fill(input->y,input->pt);
		}	
	}
}



	Output allocateOutput(bool highPt)
	{
		Output out;
		const std::vector<double>& ptBins= (highPt ? ptBinsHigh : ptBinsLow);

		out.pt.den= createTH1("den_pt", "denominator vs pt", ptBins);
		out.pt.num= createTH1("num_pt", "numerator vs pt",ptBins);
		out.pt.xlabel=histPtLabel;

		out.y.den = createTH1("den_y", "denominator vs y",yBins);
		out.y.num = createTH1("num_y", "numerator vs y",yBins);
		out.y.xlabel=histYLabel;

		out.cent.num= createTH1("num_cent","denominator vs centrality",centBins);
		out.cent.den= createTH1("den_cent","numerator vs centrality",centBins);
		out.cent.xlabel=histCentLabel;

		out.pt_fwd.den= createTH1("den_pt_fwd", "forward : denominator vs pt", ptBins);
		out.pt_fwd.num= createTH1("num_pt_fwd", "forward : numerator vs pt",ptBins);
		out.pt_fwd.xlabel=histPtLabel;

		out.pt_mid.den= createTH1("den_pt_mid", "mid barrel: denominator vs pt", ptBins);
		out.pt_mid.num= createTH1("num_pt_mid", "mid barrel: numerator vs pt",ptBins);
		out.pt_mid.xlabel=histPtLabel;

		out.pt_y.den =createTH2("den_pt_y", "denominator vs pt,y",yBins,ptBins);
		out.pt_y.num=createTH2("num_pt_y","numerator vs pt,y",yBins,ptBins);
		out.pt_y.xlabel=histYLabel;
		out.pt_y.ylabel=histPtLabel;

		return out;
	}

	void produceOutput(HistPair out, const std::string& outputpath)
	{
		TEfficiency eff(*out.num,*out.den);
		const std::string eff_name="eff_"+std::string(out.num->GetName()).substr(4);
		eff.SetName(eff_name.data());

		const std::string outputfilename=outputpath+"/output";
		const char* ylabel= "";

		writeToCanvas(out.num,out.xlabel,ylabel,outputfilename);
		writeToCanvas(out.den,out.xlabel,ylabel,outputfilename);
		writeToCanvas(&eff,out.xlabel,"Efficiency",outputfilename);

		out.num->Write();
		out.den->Write();
		eff.Write();
	}

	void produceOutput(Hist2Pair out, const std::string& outputpath)
	{
		TEfficiency eff(*out.num,*out.den);
		const std::string eff_name="eff_"+std::string(out.num->GetName()).substr(4);
		eff.SetName(eff_name.data());

		const std::string outputfilename=outputpath+"/output";

		const char* ylabel= out.ylabel ;

		writeToCanvas(out.num,out.xlabel,ylabel,outputfilename);
		writeToCanvas(out.den,out.xlabel,ylabel,outputfilename);
		writeToCanvas2D(&eff,out.xlabel,out.ylabel,outputfilename);

		out.num->Write();
		out.den->Write();
		eff.Write();
	}

#if !defined(__CLING__)

	int main(int argc, char **argv)
	{
		std::string flags= argv[1];

		if (flags=="-multi")
		{
			const char* inputs[64];
			const int numOfTriggers=argc-4;
			for(int i=0;i< numOfTriggers;i++) 
				inputs[i]=argv[i+3];

			if (numOfTriggers>1)
				MultiPlotEff(argv[2],inputs,argv[argc-1],numOfTriggers);
			else
				std::cerr << "Wrong number of parameters:\nUsage:\nmainpath trigger0 trigger1...  output\n";
		}
		else
		{
			if (argc==5)
				PlotEff(argv[1],argv[2],argv[3],argv[4]);
			else
				std::cerr << "Wrong number of parameters:\nUsage:\ninput , output, {lowpt,highpt}\n";
		}

		return 0;
	}

#endif
