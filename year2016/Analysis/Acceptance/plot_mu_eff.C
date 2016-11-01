#include "Utilities/initOniaTree.C"
#include "Utilities/eventUtil.h"

#include "TChain.h"
#include "TH1.h"
#include "TClonesArray.h"
#include "TColor.h"
#include "TFile.h"
#include "TH2D.h"
#include "TH1D.h"
#include "TChain.h"
#include "TF1.h"
#include "TStyle.h"
#include "TColor.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TLegend.h"

#include <math.h>
#include <iostream>


using namespace std;

Double_t  CurrentMuonAcceptance(Double_t *x, Double_t *par=0);
Double_t  Version1MuonAcceptance(Double_t *x, Double_t *par=0);
Double_t  Version2MuonAcceptance(Double_t *x, Double_t *par=0);


void plot_mu_eff() 
{
  gStyle->SetLegendBorderSize(0); 
  const Int_t NRGBs = 6;
  const Int_t NCont = 999;
  Double_t stops[NRGBs] = { 0.00, 0.1, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.99, 0.0, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.0, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.99, 0.0, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);
  gStyle->SetOptStat(0);

  TH1::SetDefaultSumw2(kTRUE);

  Double_t maxDeltaR = 0.05;
  Double_t maxDPtRel = 0.5;
  Bool_t   applyCuts    = true;
  Bool_t   checkTrigger = true;
  Bool_t   isJPSI       = true;
  Bool_t   isPbPb       = false;
  Bool_t   useTnPMethod = true;
  
  TChain * fChain = 0;
  if (isPbPb) {
    fChain = new TChain("hionia/myTree","");
    if (isJPSI) {
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1_Extended.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_15_30_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_JpsiMM_ptJpsi_30_Inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
    } else {
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_00_03_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_03_06_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_06_09_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_09_12_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_12_15_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
      fChain->Add("../SAMPLES/OniaTree_Pythia8_Psi2SMM_ptPsi2_15_Inf_Hydjet_MB_HINPbPbWinter16DR-75X_mcRun2_HeavyIon_v13-v1.root");
    }
  } else {
    fChain = new TChain("hionia/myTree","");
    if (isJPSI) {
      fChain->Add("../SAMPLES/OniaTree_JpsiMM_5p02TeV_TuneCUETP8M1_HINppWinter16DR-75X_mcRun2_asymptotic_ppAt5TeV_v3-v1_Extended.root");
    } else {
      fChain->Add("../SAMPLES/OniaTree_Psi2SMM_pp5p02TeV_TuneCUETP8M1_noCUT_v2.root");
    }
  }

  initOniaTree(fChain);
  
  char PATH[] = "../PLOT";
  
  TFile *fOut = 0;
  if (isPbPb) {
    if (isJPSI) {
      fOut = new TFile(Form("%s/HI_SiMuon_JPSI_%s_%s_%s.root",PATH, (applyCuts?"withCUTS":"noCUTS"), (checkTrigger?"withTRIG":"noTRIG"), (useTnPMethod?"withTNP":"noTNP")),"RECREATE");
    } else {
      fOut = new TFile(Form("%s/HI_SiMuon_PSI2S_%s_%s_%s.root",PATH, (applyCuts?"withCUTS":"noCUTS"), (checkTrigger?"withTRIG":"noTRIG"), (useTnPMethod?"withTNP":"noTNP")),"RECREATE");
    }
  } else {
    if (isJPSI) {
      fOut = new TFile(Form("%s/pp_SiMuon_JPSI_%s_%s_%s.root",PATH, (applyCuts?"withCUTS":"noCUTS"), (checkTrigger?"withTRIG":"noTRIG"), (useTnPMethod?"withTNP":"noTNP")),"RECREATE");
    } else {
      fOut = new TFile(Form("%s/pp_SiMuon_PSI2S_%s_%s_%s.root",PATH, (applyCuts?"withCUTS":"noCUTS"), (checkTrigger?"withTRIG":"noTRIG"), (useTnPMethod?"withTNP":"noTNP")),"RECREATE");
    }
  }
    
  fOut->cd();
  
  Float_t minEta = -2.4;
  /* Build Control Histograms to check distributions */
  //  TH1D* hPt   = new TH1D("hPt", "hPt; #mu^{+}#mu^{-} p_{T} [GeV/c]; Entries", 100, 0.0, 30.0);
  TH1D* hCen  = new TH1D("hCen", "hCen; Centrality; Entries", 200, 0.0, 100.0);
  
  TH2F* hRecoCut =  new TH2F("h2D_RecoCut_Total", "h2D_Gen_Total;Pt:Rapidity", 32, minEta, 2.4, 36, 0.0, 5.4);  // used 48, 54
  TH2F* hGen     =  new TH2F("h2D_Gen_Total", "h2D_Gen_Total;Pt:Rapidity", 32, minEta, 2.4, 36, 0.0, 5.4);  // used 48, 54
  TH2F* hAccEff  =  new TH2F("h2D_AccEff_Total", "; Gen Probe #mu #eta; Gen Probe #mu P_{T}  [GeV/c]", 32, minEta, 2.4, 36, 0.0, 5.4);  // used 48, 54
  
  
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntries();

  int N_OLD=0, N_NEW=0, N_TOT=0;
   
  cout << "[INFO] Starting to process: " << nentries << " entries" << endl;
  for (Long64_t jentry=0; jentry<nentries;jentry++) { 
    
    if ((jentry%1000000)==0) cout << "[INFO] Processed: " << jentry << " entries" << endl;
    Long64_t centry = fChain->LoadTree(jentry);
    if (centry < 0) break;
    if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      cout << "[INFO] Changed to Tree number: " << fCurrent << endl; 
    }
      
    Gen_mu_4mom->Clear();
    Reco_mu_4mom->Clear();
    fChain->GetEntry(jentry);

    Double_t Weight = 1.0;
    Double_t NColl = HI::findNcoll(Centrality);
    if (NColl<0.0){ 
      cout << "[ERROR] NColl was not found for Centrality = " << (Double_t(Centrality)/2.0) << endl;
      return;
    }
    Weight = ( fChain->GetWeight() * NColl );
    hCen->Fill((((Double_t)Centrality)/2.0), Weight);
    
    if (useTnPMethod){
      for (Int_t iGenMuon1=0; iGenMuon1<Gen_mu_size; iGenMuon1++) {
        for (Int_t iGenMuon2=(iGenMuon1+1); iGenMuon2<Gen_mu_size; iGenMuon2++) {
          Int_t iGenProbeMuon = GEN::findGenProbeMuon(iGenMuon1, iGenMuon2, isPbPb, maxDeltaR, maxDPtRel);
          if (iGenProbeMuon<0) continue;
          TLorentzVector* GenProbeMuon = (TLorentzVector*)Gen_mu_4mom->At(iGenProbeMuon);
          hGen->Fill((minEta==0.0 ? abs(GenProbeMuon->Eta()) : GenProbeMuon->Eta()), GenProbeMuon->Pt(), Weight);
          Int_t iMatchedRecoProbeMuon = GEN::getMatchedRecoMuon(iGenProbeMuon, maxDeltaR, maxDPtRel);  
          if ( iMatchedRecoProbeMuon>=0 ){
            if ( ( applyCuts && isSoftMuon( iMatchedRecoProbeMuon ) ) || !applyCuts ){
              if ( ( checkTrigger &&  (isTriggerMatch(iMatchedRecoProbeMuon, (isPbPb ? (int)HI::HLT_HIL1DoubleMu0_v1 : (int)PP::HLT_HIL1DoubleMu0_v1)))) || !checkTrigger ){
                TLorentzVector* RecoProbeMuon = (TLorentzVector*)Reco_mu_4mom->At(iMatchedRecoProbeMuon);
                if  (isGlobalMuonInAcceptV2(RecoProbeMuon)) {
                  N_OLD = N_OLD + 1;
                }
                if  (isGlobalMuonInAcceptV3(RecoProbeMuon)) {
                  N_NEW = N_NEW + 1;
                }
                N_TOT = N_TOT + 1; 
                hRecoCut->Fill((minEta==0.0 ? abs(GenProbeMuon->Eta()) : GenProbeMuon->Eta()), GenProbeMuon->Pt(), Weight);
              }
            }
          }
        }
      }
    } else {
      for (Int_t iGenMuon1=0; iGenMuon1<Gen_mu_size; iGenMuon1++) {
        TLorentzVector* GenMuon1 = (TLorentzVector*)Gen_mu_4mom->At(iGenMuon1);
        hGen->Fill(GenMuon1->Eta(), GenMuon1->Pt(), Weight);
        Int_t iMatchedRecoMuon1 = GEN::getMatchedRecoMuon(iGenMuon1, maxDeltaR, maxDPtRel);  
        if ( iMatchedRecoMuon1>=0 ){
          if ( ( applyCuts && isSoftMuon( iMatchedRecoMuon1 ) ) || !applyCuts ){
            if ( ( checkTrigger &&  (isTriggerMatch(iMatchedRecoMuon1, (isPbPb ? (int)HI::HLT_HIL1DoubleMu0_v1 : (int)PP::HLT_HIL1DoubleMu0_v1)))) || !checkTrigger ){
              hRecoCut->Fill(GenMuon1->Eta(), GenMuon1->Pt(), Weight);
            }
          }
        }
      }
    }
  }
  
  cout << "N_OLD : " << N_OLD << " N_NEW: " << N_NEW << " N_TOT: " << N_TOT << " DIFF " << ((double)(N_OLD-N_NEW))/((double)N_TOT) << endl;
  
  hAccEff->Divide(hRecoCut, hGen, 1.0, 1.0, "b");
  
  int N_HOLES_OLD=0, N_HOLES_NEW=0;
  for (int i=0; i<32; i++) {
    for (int j=0; j<36; j++) {
        Double_t ETA = -2.4 + (1.0 + 2.0*((double)i))*(4.8)/(64.0); 
        Double_t ETAA[] = {ETA};
        Double_t PT  =  0.0 + ((double)(j+1))*(5.4)/(36.0);
        if ((PT > CurrentMuonAcceptance(ETAA, 0)) && (CurrentMuonAcceptance(ETAA, 0)!=0)){
          if (hAccEff->GetBinContent(i+1, j+1)==0 && PT<5.0) {
            N_HOLES_OLD = N_HOLES_OLD + 1;
          }
        }
        if ((PT > Version1MuonAcceptance(ETAA, 0)) && (Version1MuonAcceptance(ETAA, 0)!=0)){
          if (hAccEff->GetBinContent(i+1, j+1)==0 && PT<5.0) {
            N_HOLES_NEW = N_HOLES_NEW + 1;
          }
        }
      }
           }
    
  cout << "N_HOLES_OLD : " << N_HOLES_OLD << " N_HOLES_NEW: " << N_HOLES_NEW << endl;

  TCanvas* c = new TCanvas("c","c",1000,1000); 
  c->cd();
  
  hAccEff->GetXaxis()->CenterTitle(kTRUE);
  hAccEff->GetXaxis()->SetTitleSize(0.04);
  hAccEff->GetXaxis()->SetTitleFont(42);
  hAccEff->GetYaxis()->SetTitleSize(0.04);
  hAccEff->GetYaxis()->SetTitleFont(42);
  hAccEff->Draw("COLZ");
  /*
  TF1 *fCurrentMuonAcceptance = new TF1("CurrentMuonAcceptance", CurrentMuonAcceptance, -2.4, 2.4, 0);
  fCurrentMuonAcceptance->SetLineColor(kBlack);
  fCurrentMuonAcceptance->SetLineWidth(8);
  fCurrentMuonAcceptance->SetNpx(10000);
  fCurrentMuonAcceptance->Draw("SAMEL");
  */
  /*
  TF1 *fVersion1MuonAcceptance = new TF1("Version1MuonAcceptance", Version1MuonAcceptance, -2.4, 2.4, 0);
  fVersion1MuonAcceptance->SetLineColor(kBlack);
  fVersion1MuonAcceptance->SetLineWidth(8);
  fVersion1MuonAcceptance->SetNpx(10000);
  fVersion1MuonAcceptance->Draw("SAMEL");
  */
  TF1 *fVersion2MuonAcceptance = new TF1("Version2MuonAcceptance", Version2MuonAcceptance, -2.4, 2.4, 0);
  fVersion2MuonAcceptance->SetLineColor(kRed+1);
  fVersion2MuonAcceptance->SetLineWidth(8);
  fVersion2MuonAcceptance->SetNpx(10000);
  fVersion2MuonAcceptance->Draw("SAMEL");

  
  
  // TLegend* leg = new TLegend(0.4 ,0.31,0.60,0.46); leg->SetTextSize(0.025);
  //  leg->AddEntry(fCurrentMuonAcceptance,"2011 Cuts","l");
  // leg->AddEntry(fVersion1MuonAcceptance,"2015 Version1 Cuts","l");
  // leg->AddEntry(fVersion2MuonAcceptance,"2015 Acceptance Cuts","l");
  // leg->Draw("SAME");
  

  c->Write("AccEff");
  c->Close();


  cout << "[INFO] Saving and Closing Output File" << endl;
  fOut->Write(); 
  fOut->Close(); 

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  cout << "COMPLETED" << endl;

};

Double_t CurrentMuonAcceptance(Double_t *x, Double_t *par)
{
   Double_t  Eta = x[0];
   if ( fabs(Eta)>2.4 ) { return 0.0; }
   if ( fabs(Eta)>=1.5 && fabs(Eta)<=2.4 ) { return (3.3667-7.0/9.0*fabs(Eta)); }
   if ( fabs(Eta)>=1.0 && fabs(Eta)<1.5 )  { return (5.8-2.4*fabs(Eta));        }
   if ( fabs(Eta)>=0.0 && fabs(Eta)<1.0 )  { return 3.4;                        }
   return 0.0;
}

Double_t Version1MuonAcceptance(Double_t *x, Double_t *par)
{
   Double_t  Eta = x[0];
   if ( fabs(Eta)>2.4 ) { return 0.0; }
   if ( fabs(Eta)>=1.6 && fabs(Eta)<=2.4 ) { return (4.2 - fabs(Eta));  }
   if ( fabs(Eta)>=1.2 && fabs(Eta)<1.6 )  { return (6.2 - 2.25*fabs(Eta));  }
   if ( fabs(Eta)>=0.0 && fabs(Eta)<1.2 )  { return 3.5;                   }
   return 0.0;
};


Double_t Version2MuonAcceptance(Double_t *x, Double_t *par)
{
   Double_t  Eta = x[0];
   if ( fabs(Eta)>2.4 ) { return 0.0; }
   if ( fabs(Eta)>=2.1 && fabs(Eta)<=2.4 ) { return 1.8;  }
   if ( fabs(Eta)>=1.2 && fabs(Eta)<=2.1 ) { return (5.77 - 1.89*fabs(Eta));  }
   if ( fabs(Eta)>=0.0 && fabs(Eta)<1.2 )  { return 3.5;                   }
   return 0.0;
};

