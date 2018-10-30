#define makeTrigEff_HLTbitanalyzer_cxx
#define _USE_MATH_DEFINES
#include "makeTrigEff_HLTbitanalyzer.h"

void oniaTree::AllEffCalc(){
      TrigEffCalc("HLT_HIL1DoubleMuOpen");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_Centrality_30_100");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_Centrality_40_100");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_Centrality_50_100");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_MAXdR2p0");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_OS_MAXdR2p0");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_MAXdR3p5");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_OS");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_SS");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_er1p6");
      TrigEffCalc("HLT_HIL1DoubleMuOpen_OS_er1p6");
      TrigEffCalc("HLT_HIL1DoubleMu0");
      TrigEffCalc("HLT_HIL1DoubleMu2");
      TrigEffCalc("HLT_HIL1DoubleMu2p5");
      TrigEffCalc("HLT_HIL1DoubleMu3");
      TrigEffCalc("HLT_HIL1DoubleMu2_OS");
      TrigEffCalc("HLT_HIL1DoubleMu3_OS");
      TrigEffCalc("HLT_HIL1DoubleMu10");
      TrigEffCalc("HLT_HIL2_L1DoubleMu10");
      TrigEffCalc("HLT_HIL3_L1DoubleMu10");
      TrigEffCalc("HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0");
      TrigEffCalc("HLT_HIL2DoubleMuOpen");
      TrigEffCalc("HLT_HIL3DoubleMuOpen");
      TrigEffCalc("HLT_HIL3DoubleMuOpen_M60120");
      TrigEffCalc("HLT_HIL3DoubleMuOpen_Jpsi");
      TrigEffCalc("HLT_HIL3DoubleMuOpen_Upsi");
      TrigEffCalc("HLT_HIL3Mu0_L2Mu0");
      TrigEffCalc("HLT_HIL3Mu0_L2Mu0_testignore");
      TrigEffCalc("HLT_HIL3Mu2_L2Mu0");
      TrigEffCalc("HLT_HIL3Mu2p5_L2Mu0");
      TrigEffCalc("HLT_HIL3Mu3_L2Mu0");
      TrigEffCalc("HLT_HIL3Mu2p5_L1DoubleMu0");
      TrigEffCalc("HLT_HIL3Mu3_L1DoubleMuOpen");
      TrigEffCalc("HLT_HIL3Mu3_L1DoubleMuOpen_OS");
      TrigEffCalc("HLT_HIL3Mu3_L1DoubleMu0");
      TrigEffCalc("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen");
      TrigEffCalc("HLT_HIL3Mu3_L1TripleMuOpen");
}

void oniaTree::TrigEffCalc (string trigLabel) {
string trig_v18x2 [] =
  {
    "HLT_HIL1DoubleMuOpen",
    "HLT_HIL1DoubleMuOpen_Centrality_30_100",
    "HLT_HIL1DoubleMuOpen_Centrality_40_100",
    "HLT_HIL1DoubleMuOpen_Centrality_50_100",
    "HLT_HIL1DoubleMuOpen_MAXdR2p0",
    "HLT_HIL1DoubleMuOpen_OS_MAXdR2p0",
    "HLT_HIL1DoubleMuOpen_MAXdR3p5",
    "HLT_HIL1DoubleMuOpen_OS",
    "HLT_HIL1DoubleMuOpen_SS",
    "HLT_HIL1DoubleMuOpen_er1p6",
    "HLT_HIL1DoubleMuOpen_OS_er1p6",
    "HLT_HIL1DoubleMu0",
    "HLT_HIL1DoubleMu2",
    "HLT_HIL1DoubleMu2p5",
    "HLT_HIL1DoubleMu3",
    "HLT_HIL1DoubleMu2_OS",
    "HLT_HIL1DoubleMu3_OS",
    "HLT_HIL1DoubleMu10",
    "HLT_HIL2_L1DoubleMu10",
    "HLT_HIL3_L1DoubleMu10",
    "HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0",
    "HLT_HIL2DoubleMuOpen",
    "HLT_HIL3DoubleMuOpen",
    "HLT_HIL3DoubleMuOpen_M60120",
    "HLT_HIL3DoubleMuOpen_Jpsi",
    "HLT_HIL3DoubleMuOpen_Upsi",
    "HLT_HIL3Mu0_L2Mu0",
    "HLT_HIL3Mu0_L2Mu0_testignore",
    "HLT_HIL3Mu2_L2Mu0",
    "HLT_HIL3Mu2p5_L2Mu0",
    "HLT_HIL3Mu3_L2Mu0",
    "HLT_HIL3Mu2p5_L1DoubleMu0",
    "HLT_HIL3Mu3_L1DoubleMuOpen",
    "HLT_HIL3Mu3_L1DoubleMuOpen_OS",
    "HLT_HIL3Mu3_L1DoubleMu0",
    "HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen",
    "HLT_HIL3Mu3_L1TripleMuOpen"
  };
 
 bool TrigMatch = false;
   int nTrig = sizeof(trig_v18x2)/sizeof(trig_v18x2[0]);
   for (int i=0; i<nTrig; i++)
     if (trigLabel.find(trig_v18x2[i])!=std::string::npos && trig_v18x2[i].find(trigLabel)!=std::string::npos) {
       triggerIndex_PP = i;
       }
 
 cout<<"[INFO] Calculating efficiency for trigger "<<trigLabel<<" with index "<<triggerIndex_PP<< " from tree "<<treeLabel<<endl;
  //Double_t ptbins []={0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5, 8, 8.5, 9, 9.5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 24, 27, 30};
 Double_t ptbins []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 17.5, 20, 22.5, 25, 30, 35, 40, 50, 60, 70, 80, 100};
  //Double_t ybins []= {-2.4, -2.2, -2, -1.8, -1.6, -1.4, -1.2, -1, -0.8, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.8, 1, 1.2, 1.4, 1.6, 1.8, 2, 2.2, 2.4};
  Double_t ybins []= {-2.4, -2, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2, 2.4};

  int nptbins = sizeof(ptbins)/sizeof(double)-1;
  int nybins = sizeof(ybins)/sizeof(double)-1;

  TH1F* hdeno_pt = new TH1F ("hdeno_pt", "Trigger Efficiency vs p_{t}^{#mu#mu}; p_{t}^{#mu#mu}(GeV/c); Efficiency", nptbins, ptbins); hdeno_pt->Sumw2();
  TH1F* hnum_pt = new TH1F ("hnum_pt", "Trigger Efficiency vs p_{t}^{#mu#mu}; p_{t}^{#mu#mu}(GeV/c); Efficiency", nptbins, ptbins); hnum_pt->Sumw2();
  TH1F* hdeno_y = new TH1F ("hdeno_y","Trigger Efficiency vs y^{#mu#mu}; y^{#mu#mu}(GeV/c); Efficiency", nybins, ybins); hdeno_y->Sumw2();
  TH1F* hnum_y = new TH1F ("hnum_y","Trigger Efficiency vs y^{#mu#mu}; y^{#mu#mu}(GeV/c); Efficiency", nybins, ybins); hnum_y->Sumw2();

  Long64_t nentries =fChain->GetEntries();
  //nentries = 1000000;

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
      if (jentry%1000000==0) cout<<"[INFO] "<<jentry<<"/"<<nentries<<endl;
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      int TriggBits [] =
      {
	HLT_HIL1DoubleMuOpen_v1,
	HLT_HIL1DoubleMuOpen_Centrality_30_100_v1,
	HLT_HIL1DoubleMuOpen_Centrality_40_100_v1,
	HLT_HIL1DoubleMuOpen_Centrality_50_100_v1,
	HLT_HIL1DoubleMuOpen_MAXdR2p0_v1,
	HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1,
	HLT_HIL1DoubleMuOpen_MAXdR3p5_v1,
	HLT_HIL1DoubleMuOpen_OS_v1,
	HLT_HIL1DoubleMuOpen_SS_v1,
	HLT_HIL1DoubleMuOpen_er1p6_v1,
	HLT_HIL1DoubleMuOpen_OS_er1p6_v1,
	HLT_HIL1DoubleMu0_v1,
	HLT_HIL1DoubleMu2_v1,
	HLT_HIL1DoubleMu2p5_v1,
	HLT_HIL1DoubleMu3_v1,
	HLT_HIL1DoubleMu2_OS_v1,
	HLT_HIL1DoubleMu3_OS_v1,
	HLT_HIL1DoubleMu10_v1,
	HLT_HIL2_L1DoubleMu10_v1,
	HLT_HIL3_L1DoubleMu10_v1,
	HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1,
	HLT_HIL2DoubleMuOpen_v1,
	HLT_HIL3DoubleMuOpen_v1,
	HLT_HIL3DoubleMuOpen_M60120_v1,
	HLT_HIL3DoubleMuOpen_Jpsi_v1,
	HLT_HIL3DoubleMuOpen_Upsi_v1,
	HLT_HIL3Mu0_L2Mu0_v1,
	HLT_HIL3Mu0_L2Mu0_testignore_v1,
	HLT_HIL3Mu2_L2Mu0_v1,
	HLT_HIL3Mu2p5_L2Mu0_v1,
	HLT_HIL3Mu3_L2Mu0_v1,
	HLT_HIL3Mu2p5_L1DoubleMu0_v1,
	HLT_HIL3Mu3_L1DoubleMuOpen_v1,
	HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1,
	HLT_HIL3Mu3_L1DoubleMu0_v1,
	HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1,
	HLT_HIL3Mu3_L1TripleMuOpen_v1
      };

      for (int iQQ=0; iQQ<Reco_QQ_size; iQQ++)
        {
          TLorentzVector *RecoQQ4mom = (TLorentzVector*) Reco_QQ_4mom->At(iQQ);

          jpsi_m=RecoQQ4mom->M();
          jpsi_pt = RecoQQ4mom->Pt();
          jpsi_rap = RecoQQ4mom->Rapidity();

	  if (abs(jpsi_rap)>2.4) continue;
	  if (treeLabel.find("Upsi")==std::string::npos && treeLabel.find("Z")==std::string::npos) //if it is not z or upsilon
	    if (jpsi_pt<3) continue;
          if (!areMuonsInAcceptance2015(iQQ)) continue;
	  if (!passQualityCuts2015(iQQ)) continue;
	  hdeno_pt->Fill(jpsi_pt);
	  if (treeLabel.find("Upsi")==std::string::npos && treeLabel.find("Z")==std::string::npos){ //if it is not z or upsilon  
	    if (jpsi_pt>6.5)
	      hdeno_y->Fill(jpsi_rap);
	  }
	  else 
	    hdeno_y->Fill(jpsi_rap);
	
	  if (TriggBits [triggerIndex_PP] == 0) continue;    
	  //if (!( (HLTriggers&((ULong64_t)pow(2, triggerIndex_PP))) == ((ULong64_t)pow(2, triggerIndex_PP)) )) continue; 
	  //if (!( (Reco_QQ_trig[iQQ]&((ULong64_t)pow(2, triggerIndex_PP))) == ((ULong64_t)pow(2, triggerIndex_PP)) )) continue;
	  
          hnum_pt->Fill(jpsi_pt);
	  if (treeLabel.find("Upsi")==std::string::npos && treeLabel.find("Z")==std::string::npos){ //if it is not z or upsilon  
	    if (jpsi_pt>6.5)
	      hnum_y->Fill(jpsi_rap);
	  }
	  else 
	    hnum_y->Fill(jpsi_rap);
        }
    }
  TEfficiency* ptEff = new TEfficiency("ptEff","Trigger Efficiency vs p_{t}^{#mu#mu}; p_{t}^{#mu#mu}(GeV/c); Efficiency", nptbins, ptbins);
  if(TEfficiency::CheckConsistency(*hnum_pt,*hdeno_pt))
    ptEff = new TEfficiency (*hnum_pt,*hdeno_pt);
  else
    cout<<"inconsistent histograms for trigger efficiency in fct of pt"<<endl;

  TEfficiency* yEff = new TEfficiency("yEff","Trigger Efficiency vs y^{#mu#mu}; y^{#mu#mu}(GeV/c); Efficiency", nybins, ybins);
  if(TEfficiency::CheckConsistency(*hnum_y,*hdeno_y))
    yEff = new TEfficiency (*hnum_y,*hdeno_y);
  else
    cout<<"inconsistent histograms for trigger efficiency in fct of y"<<endl;

  gSystem->mkdir("FilesTrigEff");
  TFile* fsave = new TFile (Form("FilesTrigEff/TrigEff_%s_%s.root", treeLabel.c_str(), trigLabel.c_str()), "RECREATE");
  ptEff->Write("TrigEffVsPt");
  yEff->Write("TrigEffVsY");
  fsave->Close();

  delete hdeno_pt; delete hnum_pt; delete hdeno_y; delete hnum_y;
}

void oniaTree::Plot(string inputName) {
  gStyle->SetOptStat(0);

  Double_t ptbins []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15};
  Double_t ptbins_high []= {15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40};
  Double_t ptbins_Upsi []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 17.5, 20, 25, 30, 40, 50};
  Double_t ptbins_Z []= {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12.5, 15, 16, 17, 18, 19, 20, 22.5, 25, 30, 40, 50, 60, 70, 80, 100};

  Double_t ybins []= {-2.4, -2, -1.6, -1.2, -0.8, -0.4, 0, 0.4, 0.8, 1.2, 1.6, 2, 2.4};
  int nptbins = sizeof(ptbins)/sizeof(double)-1;
  int nybins = sizeof(ybins)/sizeof(double)-1;

  TFile* fTrig = NULL;

  TEfficiency* ptEff = NULL;;
  TEfficiency* yEff = NULL;

  TCanvas* ptCan = new TCanvas ("ptCan","",1000,1000);
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
    if (colInd == 1) {
      treeLabel = line;
      continue;
    }
    fTrig = TFile::Open(Form("FilesTrigEff/TrigEff_%s_%s.root", treeLabel.c_str(), line.c_str()));
    ptEff = (TEfficiency*) fTrig->Get("TrigEffVsPt");
    yEff = (TEfficiency*) fTrig->Get("TrigEffVsY");
      
    ptCan->cd();
    ptEff->SetMarkerColor(color(colInd-2));
    ptEff->SetMarkerStyle(24+colInd);
    ptEff->SetMarkerSize(2);
    ptEff->SetLineColor(color(colInd-2));
    ptEff->SetLineWidth(2);
    ptleg->AddEntry(ptEff, Form("%s",line.c_str()), "lp");
    ptEff->Draw("same");

    yCan->cd();
    yEff->SetMarkerColor(color(colInd-2));
    yEff->SetMarkerStyle(24+colInd);
    yEff->SetMarkerSize(2);
    yEff->SetLineColor(color(colInd-2));
    yEff->SetLineWidth(2);
    yleg->AddEntry(yEff, Form("%s",line.c_str()), "lp");
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
  gSystem->mkdir(Form("PlotsTrigEff/%s",treeLabel.c_str()));
  ptCan->SaveAs(Form("PlotsTrigEff/%s/trigEffVsPt_%s.pdf", treeLabel.c_str(), inputName.c_str()));
  yCan->SaveAs(Form("PlotsTrigEff/%s/trigEffVsY_%s.pdf", treeLabel.c_str(), inputName.c_str()));
 
  delete ptAxis; delete yAxis;
}


int oniaTree::color(int i) {
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

void oniaTree::plotAll() {
  //Plot("input_Z_LXDoubleMuOpen_HLTv26");
  Plot("input_LowPtJpsi_L1DoubleMuOpen_MAXdRX_HLTv18");
  Plot("input_LowPtJpsi_L1DoubleMuOpen_Signs_HLTv18");
  Plot("input_LowPtJpsi_L1DoubleMuOpen_er1p6_HLTv18");
  Plot("input_LowPtJpsi_L1DoubleMuX_HLTv18");
  Plot("input_LowPtJpsi_X_L1DoubleMu10_HLTv18");
  Plot("input_LowPtJpsi_L3MuX_L2Mu0_HLTv18");
  Plot("input_LowPtJpsi_L3Mu2p5_X_HLTv18");
  Plot("input_LowPtJpsi_L3Mu3_X_HLTv18");

  Plot("input_HighPtJpsi_L1DoubleMuOpen_MAXdRX_HLTv18");
  Plot("input_HighPtJpsi_L1DoubleMuOpen_Signs_HLTv18");
  Plot("input_HighPtJpsi_L1DoubleMuOpen_er1p6_HLTv18");
  Plot("input_HighPtJpsi_L1DoubleMuX_HLTv18");
  Plot("input_HighPtJpsi_X_L1DoubleMu10_HLTv18");
  Plot("input_HighPtJpsi_L3MuX_L2Mu0_HLTv18");
  Plot("input_HighPtJpsi_L3Mu2p5_X_HLTv18");
  Plot("input_HighPtJpsi_L3Mu3_X_HLTv18");

  Plot("input_Z_L1DoubleMuOpen_MAXdRX_HLTv18");
  Plot("input_Z_L1DoubleMuOpen_Signs_HLTv18");
  Plot("input_Z_L1DoubleMuOpen_er1p6_HLTv18");
  Plot("input_Z_L1DoubleMuX_HLTv18");
  Plot("input_Z_X_L1DoubleMu10_HLTv18");
  Plot("input_Z_L3MuX_L2Mu0_HLTv18");
  Plot("input_Z_L3Mu2p5_X_HLTv18");
  Plot("input_Z_L3Mu3_X_HLTv18");

  Plot("input_Upsilon_L1DoubleMuOpen_MAXdRX_HLTv18");
  Plot("input_Upsilon_L1DoubleMuOpen_Signs_HLTv18");
  Plot("input_Upsilon_L1DoubleMuOpen_er1p6_HLTv18");
  Plot("input_Upsilon_L1DoubleMuX_HLTv18");
  Plot("input_Upsilon_X_L1DoubleMu10_HLTv18");
  Plot("input_Upsilon_L3MuX_L2Mu0_HLTv18");
  Plot("input_Upsilon_L3Mu2p5_X_HLTv18");
  Plot("input_Upsilon_L3Mu3_X_HLTv18");

}
