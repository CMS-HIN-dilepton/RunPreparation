
#include"../OniaIO/OniaIO.h"
#include"../Utils/Utils.h"
#include"TrigEff.h"
#include"Helpers.h"

#include<iostream>
#include<unordered_map>

#include"TFile.h"
#include"TEfficiency.h"

using std::cout;
using std::cerr;
using HltIndex=std::unordered_map<Long64_t,HltobjEntry>;

void Process(Input* input, Output* output);
HltIndex generateIndexer(Input* input);

Output allocateOutput();

void TrigEff(const char* oniaFilename, const char* triggerFilename, const char* triggerName, const char* outputFilename)
{
    //open and create required files
    TFile* oniaFile = OpenFile(oniaFilename);
    if (oniaFile==nullptr) {std::cout<<"No Onia Tree"<<std::endl; return;}
    
    TFile* triggerFile = OpenFile(triggerFilename);
    if (triggerFile==nullptr) {std::cout<<"No Trigger file"<<std::endl; return;}

    std::string outFilename=outputFilename;

    TFile* outputFile = CreateFile(outFilename+"/output.root");

    //init inputs
    Input input;

    //check if is L1 using the trigger name
    input.isL1=std::string(triggerName).find("HLT_HIL1")!= std::string::npos;
    input.isDBmu=std::string(triggerName).find("Double")!= std::string::npos;
    if (input.isL1) std::cout <<"L1 trigger detected\n";
    if (input.isDBmu) std::cout <<"Double muon trigger detected\n";

    input.oniaTree =OpenTree(oniaFile,oniaTreeName);
    input.hltanalysisTree=OpenTree(triggerFile,hltanalysisTreeName);

    std::string triggerPath=std::string(hltobjDirectoryName)+triggerName;
    input.hltobjectTree=OpenTree(triggerFile,triggerPath.data());

    if ((input.oniaTree!=nullptr) && (input.hltanalysisTree!=nullptr) && (input.hltobjectTree!=nullptr))
    {
        //init outputs
        Output output=allocateOutput();

        Process(&input,&output);

        output.pass->Write();
        output.total->Write();

        cout << "Success.\n";
    }

    delete oniaFile;
    delete triggerFile;
    delete outputFile;
}

HltIndex generateIndexer(Input* input)
{
    HltIndex indexer;
    Reader<HltobjInput> hltObj(input->hltobjectTree);
    Reader<HltanalysisInput> hltAn(input->hltanalysisTree);

    Long64_t entryNum= input->hltanalysisTree->GetEntries();

    indexer.reserve(entryNum);

    std::cout << "indexing events..\n";
    long long repeatedEvents=0;

    for(Long64_t entry=0;entry < entryNum;entry++)
    {
        const HltanalysisInput* analysisInput = hltAn.readEntry(entry);
        const HltobjInput* hltobjInput = hltObj.readEntry(entry);

        auto item= indexer.emplace(analysisInput->event,HltobjEntry());
        
        if(!item.second)
        {
            repeatedEvents++;
        }

        HltobjEntry* hltentry= &(item.first->second);
        hltentry->eta=*(hltobjInput->eta);
        hltentry->mass=*(hltobjInput->mass);
        hltentry->phi=*(hltobjInput->phi);
        hltentry->pt=*(hltobjInput->pt);
    }

    std::cout << "Indexing finished, index generated :" << entryNum-repeatedEvents << "\n";
    std::cout << "repeated events: " << repeatedEvents << "\n"; 
    return indexer;

}

void Process(Input* input, Output* output)
{
    Reader<OniaInput> onia(input->oniaTree);

    const HltIndex indexer= generateIndexer(input);

    Writer<OniaOutput> total(output->total);
    Writer<OniaOutput> pass(output->pass);
    
    Long64_t oniaEntryNum= input->oniaTree->GetEntries();
    Long64_t entryStep= oniaEntryNum/50;

    for(Long64_t entry=0;entry< oniaEntryNum;entry++)
    {
        if ((entry % entryStep)==0)
        {
            cout << "processing entries : " << round((100.0f*entry)/oniaEntryNum)
                 << "% " << entry << " / " << oniaEntryNum << '\n';
        }
            
        const OniaInput* oniaInput = onia.readEntry(entry);
        int object_size ;
	object_size = input->isDBmu ?  oniaInput->reco_QQ_size : oniaInput->reco_mu_size;
        const auto hltobjFound= indexer.find(oniaInput->event);
        if (hltobjFound== indexer.end()) continue;
	for(int iMu=0;iMu< object_size;iMu++)
        {
//	    cout << "running candidate " << iMu << " in entry " << entry << '\n';
            const TLorentzVector* mu,* simu_pl,* simu_mi;
//	cout << "debug HLT if not DBMU" << std::endl;
	    if(!(input->isDBmu))
	    {
            mu= input->isL1 ? 
                    (TLorentzVector*) oniaInput->reco_mu_L1_mom4->At(iMu) 
                :   (TLorentzVector*) oniaInput->reco_mu_mom4->At(iMu);
	    }

//	cout << "debug HLT if DBMU" << std::endl;
	    if(input->isDBmu)
	    {
            mu  =    (TLorentzVector*) oniaInput->reco_QQ_mom4->At(iMu);
            simu_pl= input->isL1 ? 
                    (TLorentzVector*) oniaInput->reco_mu_L1_mom4->At(oniaInput->reco_QQ_mupl_idx[iMu]) 
                :   (TLorentzVector*) oniaInput->reco_mu_mom4->At(oniaInput->reco_QQ_mupl_idx[iMu]);
            simu_mi= input->isL1 ? 
                    (TLorentzVector*) oniaInput->reco_mu_L1_mom4->At(oniaInput->reco_QQ_mumi_idx[iMu]) 
                :   (TLorentzVector*) oniaInput->reco_mu_mom4->At(oniaInput->reco_QQ_mumi_idx[iMu]);
	    }

            
//	cout << "debug HLT fetch variables" << std::endl;
            const float pt= mu->Pt();
            const float y= mu->Rapidity();
            const float eta= mu->Eta();
            const int cent= oniaInput->centrality;
	//   const auto res = indexer.find(oniaInput->event)->second;
	 //   cout << pt << res.pt.at(iMu) <<std::endl;

//	cout << "debug HLT selection" << std::endl;
            if (pt>100.0f) continue;
	    //if (abs(y)>2.4 || abs(y) <1.6) continue; 	
	    if(!(input->isDBmu))
	    {
                if (!isInAcceptance(pt,abs(eta))) continue;
            
                if (!isPassQualityCuts(oniaInput,iMu)) continue;
	    }
	    if(input->isDBmu)
	    {
                if (!(isInAcceptance((const float) simu_pl->Pt(),abs( (const float) simu_pl->Eta())) && isInAcceptance((const float) simu_mi->Pt(),abs( (const float) simu_mi->Eta())))) continue;
            
                if (!(isPassQualityCuts(oniaInput,oniaInput->reco_QQ_mumi_idx[iMu]) && isPassQualityCuts(oniaInput,oniaInput->reco_QQ_mupl_idx[iMu]))) continue;
	    }

//	cout << "debug HLT output stream" << std::endl;
            //Passed acceptance and quality cuts
            total.output.pt=pt;
            total.output.y=y;
            total.output.cent = cent;
            total.output.m= mu->M();
            total.output.eta=eta;
	    if(input->isDBmu){	
	    total.output.pt_pl = simu_pl -> Pt();
	    total.output.pt_mi = simu_mi -> Pt();
	    total.output.eta_pl = simu_pl -> Eta();
	    total.output.eta_mi = simu_mi -> Eta();
	    }
            total.writeEntry();
//	cout << "debug HLT find index" << std::endl;
            //read hltobj, if not found, continue
 
	    if(!(input->isDBmu))
	    {
                if (isMatched(mu,&(hltobjFound->second)))
                {
                    pass.output= total.output;
                    pass.writeEntry();
                }
	    }
	    if(input->isDBmu)
	    {
                if (isMatched(simu_mi,&(hltobjFound->second)) && isMatched(simu_pl,&(hltobjFound->second)) )
                {
                    pass.output= total.output;
                    pass.writeEntry();
                }
	    }
        }
    }

    cout << "finished processing "<< oniaEntryNum << " entries\n";
}

Output allocateOutput()
{
    Output out;

    out.pass = new TTree("pass","passing muons");
    out.total = new TTree("total","total muons");

    return out;
}

#if !defined(__CLING__)

int main(int argc, char **argv)
{
    if (argc==5)
        TrigEff(argv[1],argv[2],argv[3],argv[4]);
    else
        cerr << "Wrong number of parameters:\nUsage:\nOnia Filename , Trigger Filename, Trigger Name, OutputFilename\n";
    return 0;
}

#endif
