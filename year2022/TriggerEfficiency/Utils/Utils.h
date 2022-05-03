#ifndef UTILS
#define UTILS

#include"TFile.h"
#include"TTree.h"
#include"TH1.h"
#include"TH2.h"
#include"TEfficiency.h"

const float padSizes[] = { 0.02f,0.1f,0.98f,0.9f };
const float canvasWidth = 1200.0f;
const float canvasHeight = 900.0f;

TFile* OpenFile(const std::string& filename);
TFile* CreateFile(const std::string& filename);
TTree* OpenTree(TFile* file ,const std::string& treeName);
TH1* OpenTH1(TFile* file ,const std::string& histName);
TEfficiency* OpenTEff(TFile* file ,const std::string& histName);

void writeToCanvas(TH1* hist,const std::string& xname,const std::string& yname, const std::string& outname, bool yLog=false);
void writeToCanvas(TEfficiency* hist,const std::string& xname,const std::string& yname, const std::string& outname);
void writeToCanvas2D(TEfficiency* hist,const std::string& xname,const std::string& yname, const std::string& outname);
void writeToCanvas(std::vector<TH1*>& hists,const std::string& title,const std::string& xname,const std::string& yname, const std::string& outname, bool yLog=false);
void writeToCanvas(std::vector<TEfficiency*>& hists,const std::string& title,const std::string& xname,const std::string& yname, const std::string& outname);

TH1* createTH1(const std::string& name,const std::string& title, const std::vector<double>& bins);
TH2* createTH2(const std::string& name,const std::string& title, const std::vector<double>& xbins, const std::vector<double>& ybins);

#endif