
#include"Utils.h"

#include<iostream>

#include"TCanvas.h"
#include"THStack.h"
#include"TMultiGraph.h"
#include"TGraphAsymmErrors.h"

TFile* OpenFile(const std::string& filename)
{
    std::cout << "opening root file: " << filename << '\n';
    TFile* file = TFile::Open(filename.data(), "READ");
    //input file is found? is output filename valid?
    if (file==nullptr) 
        std::cout << std::string("file ") + filename +" cannot be read\n";
    return file;
}

TFile* CreateFile(const std::string& filename)
{
    std::cout << "creating root file: " << filename << '\n';
    TFile* file = TFile::Open(filename.data(), "CREATE");
    //input file is found? is output filename valid?
    if (file==nullptr) 
        std::cout << std::string("file ") + filename +" cannot be created\n";
    return file;
}

TTree* OpenTree(TFile* file ,const std::string& treeName)
{
    std::cout << "reading tree '" << treeName << "' from file '" << file->GetName() << "'\n";
    TTree* tree =nullptr;
    file->GetObject(treeName.data(),tree);
    if (tree==nullptr)
    {
        std::cerr << "Tree '" << treeName << "' does not exist.\n";
    }
    return tree;
}

TH1* OpenTH1(TFile* file ,const std::string& histName)
{
    std::cout << "reading histogram '" << histName << "' from file '" << file->GetName() << "'\n";
    TH1* hist =nullptr;
    file->GetObject(histName.data(),hist);
    if (hist==nullptr)
    {
        std::cerr << "TH1 '" << histName << "' does not exist.\n";
    }
    return hist;
}

TEfficiency* OpenTEff(TFile* file ,const std::string& histName)
{
    std::cout << "reading efficiency histogram '" << histName << "' from file '" << file->GetName() << "'\n";
    TEfficiency* hist =nullptr;
    file->GetObject(histName.data(),hist);
    if (hist==nullptr)
    {
        std::cerr << "TEfficiency '" << histName << "' does not exist.\n";
    }
    return hist;
}

void writeToCanvas(TH1* hist,const std::string& xname,const std::string& yname, const std::string& outname, bool yLog)
{
    const std::string canvasName=std::string(hist->GetName())+" plot";
    const std::string outputFilename=outname+"_"+hist->GetName()+".pdf";
    TCanvas canvas(canvasName.data(),canvasName.data(),canvasWidth,canvasHeight);
    canvas.cd();
    TPad pad("pad","fit", padSizes[0], padSizes[1], padSizes[2], padSizes[3]);
    pad.Draw();
    pad.cd();
    if (yLog) pad.SetLogy();
    hist->GetYaxis()->SetTitle(yname.data());
    hist->GetXaxis()->SetTitle(xname.data());
    hist->Draw("COLZ");
    canvas.SaveAs(outputFilename.data());
}

void writeToCanvas(TEfficiency* hist,const std::string& xname,const std::string& yname, const std::string& outname)
{
    const std::string canvasName=std::string(hist->GetName())+" plot";
    const std::string outputFilename=outname+"_"+hist->GetName()+".pdf";
    TCanvas canvas(canvasName.data(),canvasName.data(),canvasWidth,canvasHeight);
    canvas.cd();
    TPad pad("pad","fit", padSizes[0], padSizes[1], padSizes[2], padSizes[3]);
    pad.Draw();
    pad.cd();
    std::string title= std::string(hist->GetName())+';'+xname+';'+yname;
    hist->SetTitle(title.data());
    hist->Draw();
    canvas.SaveAs(outputFilename.data());
}

void writeToCanvas2D(TEfficiency* hist,const std::string& xname,const std::string& yname, const std::string& outname)
{
    const std::string canvasName=std::string(hist->GetName())+" plot";
    const std::string outputFilename=outname+"_"+hist->GetName()+".pdf";
    TCanvas canvas(canvasName.data(),canvasName.data(),canvasWidth,canvasHeight);
    canvas.cd();
    TPad pad("pad","fit", padSizes[0], padSizes[1], padSizes[2], padSizes[3]);
    pad.Draw();
    pad.cd();
    std::string title= std::string(hist->GetName())+';'+xname+';'+yname;
    hist->SetTitle(title.data());
    hist->Draw("COLZ");
    canvas.SaveAs(outputFilename.data());
}

void writeToCanvas(std::vector<TH1*>& hists,const std::string& title,const std::string& xname,const std::string& yname, const std::string& outname, bool yLog)
{
    TCanvas canvas((title+"_plot").data(),"",canvasWidth,canvasHeight);
    canvas.cd();

    TPad pad("pad","fit", padSizes[0], padSizes[1], padSizes[2], padSizes[3]);
    pad.Draw();
    pad.cd();
    if (yLog) pad.SetLogy();
    THStack stack((title+"_stack").data(),(title+" plot").data());
    for(auto hist : hists)
    {
        stack.Add(hist);
    }
    stack.Draw("nostack");
    stack.GetYaxis()->SetTitle(yname.data());
    stack.GetXaxis()->SetTitle(xname.data());
    pad.BuildLegend(0.7,0.8,1.0,1.0);
    canvas.SaveAs(outname.data());
}

void writeToCanvas(std::vector<TEfficiency*>& hists,const std::string& title,const std::string& xname,const std::string& yname, const std::string& outname)
{
    TCanvas canvas((title+"_plot").data(),"",canvasWidth,canvasHeight);
    canvas.cd();

    TPad pad("pad","fit", padSizes[0], padSizes[1], padSizes[2], padSizes[3]);
    pad.Draw();
    pad.cd();

    TMultiGraph* mg= new TMultiGraph(title.data(),title.data());

    int i=1;
    for(auto hist : hists)
    {
        hist->SetLineColor(i);
        mg->Add(hist->CreateGraph());
        i++;
    }
    mg->Draw("AP");

    pad.BuildLegend(0.7,0.8,1.0,1.0);
    canvas.SaveAs(outname.data());
}

TH1* createTH1(const std::string& name,const std::string& title, const std::vector<double>& bins)
{
    TH1D* result=new TH1D(name.data(),title.data(),bins.size()-1,bins.data());
    result->SetStats(false);
    result->Sumw2();
    return result;
}

TH2* createTH2(const std::string& name,const std::string& title, const std::vector<double>& xbins, const std::vector<double>& ybins)
{
    TH2* result =new TH2D(name.data(),title.data(),xbins.size()-1,xbins.data(),ybins.size()-1,ybins.data());
    result->SetStats(false);
    result->Sumw2();
    return result;
}