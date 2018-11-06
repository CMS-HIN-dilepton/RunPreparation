#include "TSystem.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include "TClonesArray.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <math.h>
#include <TPaveText.h>
#include "RooCategory.h"
#include "RooNumIntConfig.h"
#include "RooPlotable.h"
#include <TUnfold.h>
#include <TLorentzVector.h>
#include <vector>
#include <TRandom.h>
#include <TF1.h>
#include <TObjArray.h>
#include <TEfficiency.h>
#include "TLegend.h"
#include <fstream>

using namespace std;

int color(int i) {
  if (i==0) return kMagenta+1;
  else if (i==1) return kBlue+1;
  else if (i==2) return kRed+1;
  else if (i==3) return kCyan+1;
  else if (i==4) return kGreen+1;
  else if (i==5) return kOrange+1;
  else if (i==6) return 28;
  else if (i==7) return kBlack;
  else if (i==8) return kAzure+1;
  else if (i==9) return kYellow+1;
  else return kBlack;
}


void plotQuickly(string inputName) {
  gStyle->SetOptStat(0);

  Double_t ptbins []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15};
  Double_t ptbins_high []= {15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40};
  Double_t ptbins_Upsi []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 17.5, 20, 25, 30, 40, 50};
  Double_t ptbins_Z []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40, 50, 60, 70, 80, 100};

  Double_t ybins []= {-2.4, -2, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2, 2.4};
  int nptbins = sizeof(ptbins)/sizeof(double)-1;
  int nybins = sizeof(ybins)/sizeof(double)-1;

  TFile* fTrig = NULL;

  TEfficiency* ptEff = NULL;
  TEfficiency* ptEff_mid = NULL;
  TEfficiency* ptEff_fwd = NULL;
  TEfficiency* yEff = NULL;

  TCanvas* ptCan = new TCanvas ("ptCan","",1000,1000);
  TCanvas* ptCan_mid = new TCanvas ("ptCan_mid","",1000,1000);
  TCanvas* ptCan_fwd = new TCanvas ("ptCan_fwd","",1000,1000);

  TH1F* ptAxis = new TH1F("ptAxis","Trigger Efficiency Vs pt",nptbins, ptbins);
  if (inputName.find("High")!=std::string::npos){
    nptbins = sizeof(ptbins_high)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis","Trigger Efficiency Vs pt",nptbins, ptbins_high);
  }
  else if (inputName.find("Upsi")!=std::string::npos){
    nptbins = sizeof(ptbins_Upsi)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis","Trigger Efficiency Vs pt",nptbins, ptbins_Upsi);
  }
  else if (inputName.find("Z")!=std::string::npos){
    nptbins = sizeof(ptbins_Z)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis","Trigger Efficiency Vs pt",nptbins, ptbins_Z);
  }
  ptAxis->GetYaxis()->SetRangeUser(0, 1.2);
  ptAxis->GetYaxis()->SetTitle("Efficiency");
  ptAxis->GetXaxis()->SetTitle("p_{t}^{#mu#mu}(GeV/c)");
  ptAxis->GetXaxis()->SetNdivisions(505);
  ptAxis->GetXaxis()->CenterTitle(true);
  ptAxis->GetYaxis()->CenterTitle(true);

  TCanvas* yCan = new TCanvas ("yCan","",1000,1000);
  TH1F* yAxis = new TH1F("yAxis","Trigger Efficiency Vs rapidity",nybins, ybins);
  yAxis->GetYaxis()->SetRangeUser(0, 1.2);
  yAxis->GetYaxis()->SetTitle("Efficiency");
  yAxis->GetXaxis()->SetTitle("y^{#mu#mu}");
  yAxis->GetXaxis()->SetNdivisions(505);
  yAxis->GetXaxis()->CenterTitle(true);
  yAxis->GetYaxis()->CenterTitle(true);

  TLegend* ptleg = new TLegend(0.4,0.15,0.9,0.5);//(0.62,0.3,0.88,0.45);                                                                                                                                
  TLegend* yleg = new TLegend(0.4,0.15,0.9,0.5);

  ptCan->cd();
  ptAxis->Draw();
  ptCan_mid->cd();
  ptAxis->Draw();
  ptCan_fwd->cd();
  ptAxis->Draw();
  yCan->cd();
  yAxis->Draw();

  ifstream file(Form("InputPlotFiles/%s.txt",inputName.c_str()));
  if ((file.good())) cout<<"[INFO] Reading trigger names from input file"<< inputName<<endl;
  else {
    cout<<"[ERROR] Problem reading trigger names from input file"<< inputName<<endl;
    return;
  }
  string line;
  int colInd = 0;
  string plotLabel = "";

  while (file.good()) {
    getline(file,line);
    if (line.size()==0) break;
    colInd ++;
    plotLabel = plotLabel + "_" + line;
    fTrig = TFile::Open(Form("FilesTrigEff/TrigEff_%s.root", line.c_str()));
    ptEff = (TEfficiency*) fTrig->Get("TrigEffVsPt");
    ptEff_mid = (TEfficiency*) fTrig->Get("TrigEffVsPtMid");
    ptEff_fwd = (TEfficiency*) fTrig->Get("TrigEffVsPtFwd");
    yEff = (TEfficiency*) fTrig->Get("TrigEffVsY");

    ptCan->cd();
    ptEff->SetMarkerColor(color(colInd-2));
    ptEff->SetMarkerStyle(24+colInd);
    ptEff->SetMarkerSize(2);
    ptEff->SetLineColor(color(colInd-2));
    ptEff->SetLineWidth(2);
    ptleg->AddEntry(ptEff, Form("%s",(line.find("New")!=std::string::npos)?"New":"Default"), "lp");
    ptEff->Draw("same");

    ptCan_mid->cd();
    ptEff_mid->SetMarkerColor(color(colInd-2));
    ptEff_mid->SetMarkerStyle(24+colInd);
    ptEff_mid->SetMarkerSize(2);
    ptEff_mid->SetLineColor(color(colInd-2));
    ptEff_mid->SetLineWidth(2);
    //ptleg->AddEntry(ptEff, Form("%s",line.c_str()), "lp"); 
    ptEff_mid->Draw("same");
    ptCan_fwd->cd();
    ptEff_fwd->SetMarkerColor(color(colInd-2));
    ptEff_fwd->SetMarkerStyle(24+colInd);
    ptEff_fwd->SetMarkerSize(2);
    ptEff_fwd->SetLineColor(color(colInd-2));
    ptEff_fwd->SetLineWidth(2);
    //ptleg->AddEntry(ptEff, Form("%s",line.c_str()), "lp");
    ptEff_fwd->Draw("same");

    yCan->cd();
    yEff->SetMarkerColor(color(colInd-2));
    yEff->SetMarkerStyle(24+colInd);
    yEff->SetMarkerSize(2);
    yEff->SetLineColor(color(colInd-2));
    yEff->SetLineWidth(2);
    yleg->AddEntry(yEff, Form("%s",(line.find("New")!=std::string::npos)?"New":"Default"), "lp");
    yEff->Draw("same");

    fTrig->Close();
  }

  ptCan->cd();
  TLine * lpty1 = new TLine (ptbins[0],1,ptbins[nptbins],1);
  if (inputName.find("High")!=std::string::npos)
    lpty1 = new TLine (ptbins_high[0],1,ptbins_high[nptbins],1);
  else if (inputName.find("Upsi")!=std::string::npos)
    lpty1 = new TLine (ptbins_Upsi[0],1,ptbins_Upsi[nptbins],1);
  else if (inputName.find("Z")!=std::string::npos)
    lpty1 = new TLine (ptbins_Z[0],1,ptbins_Z[nptbins],1);

  lpty1->SetLineColor(kRed);
  lpty1->SetLineStyle(2);
  lpty1->SetLineWidth(2);
  ptleg->SetBorderSize(0);
  ptleg->SetFillStyle(0);
  ptleg->Draw("same");
  lpty1->Draw("same");

  ptCan_mid->cd();
  ptleg->Draw("same");
  lpty1->Draw("same");

  ptCan_fwd->cd();
  ptleg->Draw("same");
  lpty1->Draw("same");

  yCan->cd();
  TLine * lyy1 = new TLine (ybins[0],1,ybins[nybins],1);
  lyy1->SetLineColor(kRed);
  lyy1->SetLineStyle(2);
  lyy1->SetLineWidth(2);
  yleg->SetBorderSize(0);
  yleg->SetFillStyle(0);
  yleg->Draw("same");
  lyy1->Draw("same");

  gSystem->mkdir("PlotsTrigEff");
  gSystem->mkdir("PlotsTrigEff/Mix");
  ptCan->SaveAs(Form("PlotsTrigEff/Mix/trigEffVsPt_%s.pdf", inputName.c_str()));
  ptAxis->SetTitle("Trigger Efficiency Vs pt |y|<1.6");
  ptCan_mid->SaveAs(Form("PlotsTrigEff/Mix/trigEffVsPtMid_%s.pdf", inputName.c_str()));
  ptAxis->SetTitle("Trigger Efficiency Vs pt 1.6<|y|<2.4");
  ptCan_fwd->SaveAs(Form("PlotsTrigEff/Mix/trigEffVsPtFwd_%s.pdf", inputName.c_str()));
  yCan->SaveAs(Form("PlotsTrigEff/Mix/trigEffVsY_%s.pdf", inputName.c_str()));

  delete ptAxis; delete yAxis;
}

void plotRatio(string inputName, string inputNew, string inputDef)
{
  gStyle->SetOptStat(0);

  Double_t ptbins []= {3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15};
  Double_t ptbins_high []= {15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40};
  Double_t ptbins_Upsi []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 17.5, 20, 25, 30, 40, 50};
  Double_t ptbins_Z []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40, 50, 60, 70, 80, 100};

  Double_t ybins []= {-2.4, -2, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2, 2.4};
  int nptbins = sizeof(ptbins)/sizeof(double)-1;
  int nybins = sizeof(ybins)/sizeof(double)-1;

  TFile* fTrig = NULL;

  TEfficiency* ptEffDef = NULL;
  TEfficiency* ptEffNew = NULL;
  TEfficiency* yEffDef = NULL;
  TEfficiency* yEffNew = NULL;

  TCanvas* ptCan = new TCanvas ("ptCan","",900,1000);

  TH1F* ptAxis = new TH1F("ptAxis",Form("%s",inputName.c_str()),nptbins, ptbins);
  if (inputName.find("High")!=std::string::npos){
    nptbins = sizeof(ptbins_high)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis",Form("%s",inputName.c_str()),nptbins, ptbins_high);
  }
  else if (inputName.find("Upsi")!=std::string::npos){
    nptbins = sizeof(ptbins_Upsi)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis",Form("%s",inputName.c_str()),nptbins, ptbins_Upsi);
  }
  else if (inputName.find("Z")!=std::string::npos){
    nptbins = sizeof(ptbins_Z)/sizeof(double)-1;
    ptAxis = new TH1F("ptAxis",Form("%s",inputName.c_str()),nptbins, ptbins_Z);
  }

  nptbins = sizeof(ptbins)/sizeof(double)-1;
  TH1F* ptPull = new TH1F("ptPull"," ",nptbins, ptbins);
  if (inputName.find("High")!=std::string::npos){
    nptbins = sizeof(ptbins_high)/sizeof(double)-1;
    ptPull = new TH1F("ptPull"," ",nptbins, ptbins_high);
  }
  else if (inputName.find("Upsi")!=std::string::npos){
    nptbins = sizeof(ptbins_Upsi)/sizeof(double)-1;
    ptPull = new TH1F("ptPull"," ",nptbins, ptbins_Upsi);
  }
  else if (inputName.find("Z")!=std::string::npos){
    nptbins = sizeof(ptbins_Z)/sizeof(double)-1;
    ptPull = new TH1F("ptPull"," ",nptbins, ptbins_Z);
  }

  ptAxis->GetYaxis()->SetRangeUser(0, 1.2);
  ptAxis->GetYaxis()->SetTitle("Efficiency");
  ptAxis->GetXaxis()->SetTitle(" ");
  ptAxis->GetXaxis()->SetNdivisions(505);
  ptAxis->GetXaxis()->CenterTitle(true);
  ptAxis->GetYaxis()->CenterTitle(true);

  ptPull->GetYaxis()->SetRangeUser(0.88, 1.12);
  ptPull->GetYaxis()->SetTitle("New/Online");
  ptPull->GetXaxis()->SetTitle("p_{t}^{#mu#mu}(GeV/c)");
  ptPull->GetXaxis()->SetNdivisions(505);
  ptPull->GetXaxis()->CenterTitle(true);
  ptPull->GetYaxis()->CenterTitle(true);
  ptPull->GetYaxis()->SetNdivisions(505);
  ptPull->GetYaxis()->SetTitleSize(25);
  ptPull->GetYaxis()->SetTitleFont(43);
  ptPull->GetYaxis()->SetTitleOffset(1.4);
  ptPull->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
  ptPull->GetYaxis()->SetLabelSize(20);

  ptPull->GetXaxis()->SetNdivisions(505);
  ptPull->GetXaxis()->SetTitleSize(25);
  ptPull->GetXaxis()->SetTitleFont(43);
  ptPull->GetXaxis()->SetTitleOffset(2);
  ptPull->GetXaxis()->SetLabelFont(43); 
  ptPull->GetXaxis()->SetLabelSize(25);

  TCanvas* yCan = new TCanvas ("yCan","",900,1000);
  TH1F* yAxis = new TH1F("yAxis","Trigger Efficiencyn Vs rapidity",nybins, ybins);
  yAxis->GetYaxis()->SetRangeUser(0.8, 1.2);
  yAxis->GetYaxis()->SetTitle("New/Online");
  yAxis->GetXaxis()->SetTitle("y^{#mu#mu}");
  yAxis->GetXaxis()->SetNdivisions(505);
  yAxis->GetXaxis()->CenterTitle(true);
  yAxis->GetYaxis()->CenterTitle(true);

  TLegend* ptleg = new TLegend(0.5,0.25,0.9,0.35);//(0.62,0.3,0.88,0.45);
  TLegend* yleg = new TLegend(0.4,0.15,0.9,0.5);

  TFile* fNew = TFile::Open(Form("%s",inputNew.c_str()));
  TFile* fDef = TFile::Open(Form("%s",inputDef.c_str()));

  ptEffNew = (TEfficiency*) fNew->Get("TrigEffVsPt");
  ptEffDef = (TEfficiency*) fDef->Get("TrigEffVsPt");

  ptEffNew->SetMarkerColor(kRed);
  ptEffNew->SetMarkerStyle(kFullSquare);
  ptEffNew->SetMarkerSize(1);
  ptEffNew->SetLineColor(kRed+2);
  ptEffNew->SetLineWidth(2);
  ptleg->AddEntry(ptEffNew, "New L3Reco", "lp");

  ptEffDef->SetMarkerColor(kGreen+3);
  ptEffDef->SetMarkerStyle(kOpenSquare);
  ptEffDef->SetMarkerSize(1);
  ptEffDef->SetLineColor(kGreen+3);
  ptEffDef->SetLineWidth(2);
  ptleg->AddEntry(ptEffDef, "Online v1.0", "lp");

  ptCan->cd();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0.01); 
  //pad1->SetGridx();         
  pad1->Draw();
  pad1->cd();
  ptAxis->SetStats(0);
  ptAxis->Draw();

  ptEffNew->Draw("same");
  ptEffDef->Draw("same");
  ptleg->SetBorderSize(0);
  ptleg->SetFillStyle(0);
  ptleg->Draw("same");


  yEffNew = (TEfficiency*) fNew->Get("TrigEffVsY");
  yEffDef = (TEfficiency*) fDef->Get("TrigEffVsY");

  for (int i = 0; i<nptbins; i++) {
    double pt = ptbins[i];
    if (inputName.find("High")!=std::string::npos) pt = ptbins_high[i];
    else if (inputName.find("Upsi")!=std::string::npos) pt = ptbins_Upsi[i];
    else if (inputName.find("Z")!=std::string::npos) pt = ptbins_Z[i];
    ptPull->SetBinContent(ptPull->FindBin(pt),ptEffNew->GetEfficiency(ptEffNew->FindFixBin(pt))*1.0/ptEffDef->GetEfficiency(ptEffDef->FindFixBin(pt)));
    ptPull->SetBinError(ptPull->FindBin(pt),sqrt(pow(ptEffNew->GetEfficiencyErrorLow(ptEffNew->FindFixBin(pt)),2)+pow(ptEffDef->GetEfficiencyErrorLow(ptEffDef->FindFixBin(pt)),2)));
  }
  
  for (int i = 0; i<nybins; i++) {
    double y = ybins[i];
    yAxis->SetBinContent(yAxis->FindBin(y),yEffNew->GetEfficiency(yEffNew->FindFixBin(y))*1.0/yEffDef->GetEfficiency(yEffDef->FindFixBin(y))); 
    yAxis->SetBinError(yAxis->FindBin(y),sqrt(pow(yEffNew->GetEfficiencyErrorLow(yEffNew->FindFixBin(y)),2)+pow(yEffDef->GetEfficiencyErrorLow(yEffDef->FindFixBin(y)),2)));
  }

  ptCan->cd();
  //ptPull->GetYaxis()->SetRangeUser(0.88, 1.12);
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetTopMargin(0.01);
  //pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();
  ptPull->Draw();

  TLine * lpty1 = new TLine (ptbins[0],1,ptbins[nptbins],1);
  if (inputName.find("High")!=std::string::npos)
    lpty1 = new TLine (ptbins_high[0],1,ptbins_high[nptbins],1);
  else if (inputName.find("Upsi")!=std::string::npos)
    lpty1 = new TLine (ptbins_Upsi[0],1,ptbins_Upsi[nptbins],1);
  else if (inputName.find("Z")!=std::string::npos)
    lpty1 = new TLine (ptbins_Z[0],1,ptbins_Z[nptbins],1);
  lpty1->SetLineColor(kRed);
  lpty1->SetLineStyle(2);
  lpty1->SetLineWidth(2);
  lpty1->Draw("same");

  ptPull->SetMarkerColor(kBlue);
  ptPull->SetMarkerStyle(kFullCircle);
  ptPull->SetMarkerSize(1);
  ptPull->SetLineColor(kBlue+2);
  ptPull->SetLineWidth(2);
  ptPull->Draw("same");

  yCan->cd();
  yAxis->Draw();
  TLine * lyy1 = new TLine (ybins[0],1,ybins[nybins],1);
  lyy1->SetLineColor(kRed);
  lyy1->SetLineStyle(2);
  lyy1->SetLineWidth(2);
  lyy1->Draw("same");
  yAxis->SetMarkerColor(kBlue);
  yAxis->SetMarkerStyle(kFullCircle);
  yAxis->SetMarkerSize(1);
  yAxis->SetLineColor(kBlue+2);
  yAxis->SetLineWidth(2);
  yAxis->Draw("same");

  ptCan->SaveAs(Form("PlotsTrigEff/Mix/trigRatioVsPt_%s.pdf", inputName.c_str()));
  yCan->SaveAs(Form("PlotsTrigEff/Mix/trigRatioVsY_%s.pdf", inputName.c_str()));
}
