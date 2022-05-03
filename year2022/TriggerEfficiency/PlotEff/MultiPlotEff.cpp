
#include"../Utils/Utils.h"

#include"PlotEff.h"

#include<vector>

std::vector<TEfficiency*> outputPlots(std::vector<TFile*>& triggerFiles, const char** triggernames, int inputSize, const std::string& name);

void MultiPlotEff(const char* mainpath, const char** triggernames, const char* outputFilename, int inputSize)
{
    std::string outFilename=outputFilename;

    std::vector<TFile*> triggerFiles(inputSize);

    for(int i=0;i<inputSize;i++)
    {
        std::string filename=std::string(mainpath)+'/'+triggernames[i]+"/hist.root";
        triggerFiles[i]=OpenFile(filename);
        if (triggerFiles[i]==nullptr) return;
    }

    auto pt_hists=outputPlots(triggerFiles,triggernames,inputSize,"eff_pt");
    writeToCanvas(pt_hists,"Efficiency vs pt",histPtLabel,"Efficiency",outFilename+"_pt.pdf");

    auto pt_fwd_hists=outputPlots(triggerFiles,triggernames,inputSize,"eff_pt_fwd");
    writeToCanvas(pt_fwd_hists,"Efficiency vs pt : forward region",histPtLabel,"Efficiency",outFilename+"_pt_fwd.pdf");

    auto pt_mid_hists=outputPlots(triggerFiles,triggernames,inputSize,"eff_pt_mid");
    writeToCanvas(pt_mid_hists,"Efficiency vs pt : mid region",histPtLabel,"Efficiency",outFilename+"_pt_mid.pdf");

    auto y_hists=outputPlots(triggerFiles,triggernames,inputSize,"eff_y");
    writeToCanvas(y_hists,"Efficiency vs y",histYLabel,"Efficiency",outFilename+"_y.pdf");

    auto cent_hists=outputPlots(triggerFiles,triggernames,inputSize,"eff_cent");
    writeToCanvas(cent_hists,"Efficiency vs centrality",histYLabel,"Efficiency",outFilename+"_cent.pdf");

}

std::vector<TEfficiency*> outputPlots(std::vector<TFile*>& triggerFiles, const char** triggernames, int inputSize, const std::string& name)
{
    std::vector<TEfficiency*> hists(inputSize);

    for(int i=0;i<inputSize;i++)
    {
        hists[i]= OpenTEff(triggerFiles[i],name);
        hists[i]->SetTitle(triggernames[i]);
    }

    return hists;
}