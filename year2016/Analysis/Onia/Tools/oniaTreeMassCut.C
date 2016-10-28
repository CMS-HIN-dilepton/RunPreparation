//---mass cut to run over oniaTree---//

#include "TTree.h"
#include "TFile.h"
#include "TChain.h"
#include "TLorentzVector.h"
#include "TClonesArray.h"
#include "TDirectory.h"
#include "TString.h"
#include <iostream>

bool applySoftMuonCuts = true;
bool applyTriggerMatching = true;


TTree* massCut(TChain* told, Double_t massMin, Double_t massMax) 
{

  Long64_t nentries = told->GetEntries();
  ULong64_t       HLTriggers;
  Int_t           Reco_QQ_size = 0;
  TClonesArray   *Reco_QQ_4mom = 0;
  ULong64_t       Reco_QQ_trig[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_VtxProb[99];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_mupl_isGoodMuon[99];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_mumi_isGoodMuon[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mupl_nPixWMea[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mumi_nPixWMea[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mupl_nTrkWMea[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mumi_nTrkWMea[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mupl_dxy[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mumi_dxy[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mupl_dz[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mumi_dz[99];   //[Reco_QQ_size]
   
  Int_t           Reco_QQ_mupl_nTrkHits[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mumi_nTrkHits[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mupl_normChi2_inner[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mumi_normChi2_inner[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mupl_normChi2_global[99];   //[Reco_QQ_size]
  Float_t         Reco_QQ_mumi_normChi2_global[99];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_mupl_TrkMuArb[99];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_mumi_TrkMuArb[99];   //[Reco_QQ_size]

  TBranch        *b_HLTriggers;   //!
  TBranch        *b_Reco_QQ_size = 0;   //!
  TBranch        *b_Reco_QQ_4mom = 0;   //!
  TBranch        *b_Reco_QQ_trig;   //!
  TBranch        *b_Reco_QQ_VtxProb;   //!
  TBranch        *b_Reco_QQ_mupl_isGoodMuon;   //!
  TBranch        *b_Reco_QQ_mumi_isGoodMuon;   //!
  TBranch        *b_Reco_QQ_mupl_nPixWMea;   //!
  TBranch        *b_Reco_QQ_mumi_nPixWMea;   //!
  TBranch        *b_Reco_QQ_mupl_nTrkWMea;   //!
  TBranch        *b_Reco_QQ_mumi_nTrkWMea;   //!
  TBranch        *b_Reco_QQ_mupl_dxy;   //!
  TBranch        *b_Reco_QQ_mumi_dxy;   //!
  TBranch        *b_Reco_QQ_mupl_dz;   //!
  TBranch        *b_Reco_QQ_mumi_dz;   //!
   
  TBranch        *b_Reco_QQ_mupl_nTrkHits;   //!
  TBranch        *b_Reco_QQ_mumi_nTrkHits;   //!
  TBranch        *b_Reco_QQ_mupl_normChi2_inner;   //!
  TBranch        *b_Reco_QQ_mumi_normChi2_inner;   //!
  TBranch        *b_Reco_QQ_mupl_normChi2_global;   //!
  TBranch        *b_Reco_QQ_mumi_normChi2_global;   //!
  TBranch        *b_Reco_QQ_mupl_TrkMuArb;   //!
  TBranch        *b_Reco_QQ_mumi_TrkMuArb;   //!
 
  Int_t fCurrent = -1, count = 0;

  Reco_QQ_4mom = 0;

  told->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
  told->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  told->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  told->GetBranch("Reco_QQ_4mom")->SetAutoDelete(kFALSE);
  told->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  told->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
  told->SetBranchAddress("Reco_QQ_mupl_isGoodMuon", Reco_QQ_mupl_isGoodMuon, &b_Reco_QQ_mupl_isGoodMuon);
  told->SetBranchAddress("Reco_QQ_mumi_isGoodMuon", Reco_QQ_mumi_isGoodMuon, &b_Reco_QQ_mumi_isGoodMuon);
  told->SetBranchAddress("Reco_QQ_mupl_nPixWMea", Reco_QQ_mupl_nPixWMea, &b_Reco_QQ_mupl_nPixWMea);
  told->SetBranchAddress("Reco_QQ_mumi_nPixWMea", Reco_QQ_mumi_nPixWMea, &b_Reco_QQ_mumi_nPixWMea);
  told->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
  told->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
  told->SetBranchAddress("Reco_QQ_mupl_dxy", Reco_QQ_mupl_dxy, &b_Reco_QQ_mupl_dxy);
  told->SetBranchAddress("Reco_QQ_mumi_dxy", Reco_QQ_mumi_dxy, &b_Reco_QQ_mumi_dxy);
  told->SetBranchAddress("Reco_QQ_mupl_dz", Reco_QQ_mupl_dz, &b_Reco_QQ_mupl_dz);
  told->SetBranchAddress("Reco_QQ_mumi_dz", Reco_QQ_mumi_dz, &b_Reco_QQ_mumi_dz);

  told->SetBranchAddress("Reco_QQ_mupl_nTrkHits", Reco_QQ_mupl_nTrkHits, &b_Reco_QQ_mupl_nTrkHits);
  told->SetBranchAddress("Reco_QQ_mumi_nTrkHits", Reco_QQ_mumi_nTrkHits, &b_Reco_QQ_mumi_nTrkHits);
  told->SetBranchAddress("Reco_QQ_mupl_normChi2_global", Reco_QQ_mupl_normChi2_global, &b_Reco_QQ_mupl_normChi2_global);
  told->SetBranchAddress("Reco_QQ_mumi_normChi2_global", Reco_QQ_mumi_normChi2_global, &b_Reco_QQ_mumi_normChi2_global);
  told->SetBranchAddress("Reco_QQ_mupl_normChi2_inner", Reco_QQ_mupl_normChi2_inner, &b_Reco_QQ_mupl_normChi2_inner);
  told->SetBranchAddress("Reco_QQ_mumi_normChi2_inner", Reco_QQ_mumi_normChi2_inner, &b_Reco_QQ_mumi_normChi2_inner);
  told->SetBranchAddress("Reco_QQ_mupl_TrkMuArb", Reco_QQ_mupl_TrkMuArb, &b_Reco_QQ_mupl_TrkMuArb);
  told->SetBranchAddress("Reco_QQ_mumi_TrkMuArb", Reco_QQ_mumi_TrkMuArb, &b_Reco_QQ_mumi_TrkMuArb);


  told->GetEntry(0); 
  TTree *tnew = (TTree*)told->GetTree()->CloneTree(0); 
   
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
     
    if (jentry%1000000==0) cout << jentry << "/" << nentries << endl;
     
    Long64_t centry = told->LoadTree(jentry);
    if (centry < 0) break;
    if (told->GetTreeNumber() != fCurrent) {
      fCurrent = told->GetTreeNumber();
      cout << "[INFO] Changed to Tree number: " << fCurrent << endl; 
    }
    
    Reco_QQ_4mom->Clear();
    told->GetEntry(jentry);
     
    bool found = false;
    for (int j=0; j< Reco_QQ_size; j++){
      if (found==false) {

        bool passSoftMuonCuts2016 = ( 
                                     ( Reco_QQ_VtxProb[j] > 0.01 ) &&
                                     ( (Reco_QQ_mupl_isGoodMuon[j] == 1) && (Reco_QQ_mupl_nPixWMea[j] > 0) && (Reco_QQ_mupl_nTrkWMea[j] > 5) &&  (fabs(Reco_QQ_mupl_dxy[j]) < 0.3) && (fabs(Reco_QQ_mupl_dz[j]) < 20.) ) &&   
                                     ( (Reco_QQ_mumi_isGoodMuon[j] == 1) && (Reco_QQ_mumi_nPixWMea[j] > 0) && (Reco_QQ_mumi_nTrkWMea[j] > 5) &&  (fabs(Reco_QQ_mumi_dxy[j]) < 0.3) && (fabs(Reco_QQ_mumi_dz[j]) < 20.) )
                                      );  
         
        bool passTriggerMatching = ( 
                                    ( (HLTriggers&((ULong64_t)pow(2, 0))) == ((ULong64_t)pow(2, 0)) )  && 
                                    ( (Reco_QQ_trig[j]&((ULong64_t)pow(2, 0))) == ((ULong64_t)pow(2, 0)) )
                                     );

        TLorentzVector *DiMuon = (TLorentzVector *) Reco_QQ_4mom->At(j);
        if ( (applySoftMuonCuts ? passSoftMuonCuts2016 : true) && (applyTriggerMatching ? passTriggerMatching : true) && ( (DiMuon->M() >= massMin) && (DiMuon->M() <= massMax) ) ){     
          found = true;
          count = count +1;
        }
      } else break;
    }

    if (found==true) { tnew->Fill(); }
     
  }

  cout << "[INFO] Number of Events in New Onia Tree: " << count << endl;

  return tnew;
}


void oniaTreeMassCut(int oniamode=1) 
{

  TChain* myTree = new TChain("hionia/myTree","");     
  myTree->Add("OniaTree_DoubleMu_Run2015E-PromptReco-v1_Run_262157_262328_noCUT.root");

  Double_t massmin = -1;
  Double_t massmax = -1;

  TString signame;
  if (oniamode==1) {
    signame = TString("Jpsi");
    massmin = 2.0;
    massmax = 5.0;
  }
  else if (oniamode==2) {
    signame = TString("Upsilon");
    massmin = 9;
    massmax = 10;
  }
  TFile *fout = new TFile("OniaTree_Reduced.root","RECREATE");  
   
  TTree *myNewTree = massCut((TChain*)myTree , massmin, massmax);
 
  fout->cd();

  TDirectory *cdtof = myNewTree->mkdir("hionia");
  cdtof->cd();
  myNewTree->Write("myTree");

  fout->Write();
  fout->Close();
}


