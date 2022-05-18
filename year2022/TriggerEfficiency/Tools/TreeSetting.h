#ifndef TreeSetting_h
#define TreeSetting_h

#include <iostream>
#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TROOT.h"
#include "TClonesArray.h"
#include "TChain.h"
#include "cutsAndBin.h"

using namespace std;

const long int maxBranchSize = 100000;


// import the tree to the RooDataSet
UInt_t          runNb;
UInt_t          eventNb, LS;
float           zVtx;
Int_t           Centrality;
Float_t         SumET_HF;
ULong64_t       HLTriggers;
Short_t           Reco_QQ_size;
Short_t           Reco_mu_size;
TClonesArray    *Reco_QQ_4mom;
TClonesArray    *Reco_mu_4mom;
ULong64_t       Reco_QQ_trig[maxBranchSize];   //[Reco_QQ_size]
ULong64_t       Reco_mu_trig[maxBranchSize];   //[Reco_QQ_size]
Float_t         Reco_QQ_VtxProb[maxBranchSize];   //[Reco_QQ_size]
TBranch        *b_runNb;   //!
TBranch        *b_eventNb;   //!
TBranch        *b_LS;
TBranch        *b_zVtx;   //!
TBranch        *b_Centrality;   //!
TBranch        *b_SumET_HF;
TBranch        *b_HLTriggers;   //!
TBranch        *b_Reco_QQ_size;   //!
TBranch        *b_Reco_QQ_4mom;   //!
TBranch        *b_Reco_mu_size;   //!
TBranch        *b_Reco_mu_4mom;   //!
TBranch        *b_Reco_QQ_trig;   //!
TBranch        *b_Reco_mu_trig;   //!
TBranch        *b_Reco_QQ_VtxProb;   //!

Bool_t          Reco_mu_highPurity[maxBranchSize];   //[Reco_QQ_size]
TBranch        *b_Reco_mu_highPurity;   //!

//  muon id 
Short_t           Reco_QQ_mupl_idx[maxBranchSize];
Short_t           Reco_QQ_mumi_idx[maxBranchSize];
TBranch        *b_Reco_QQ_mupl_idx;
TBranch        *b_Reco_QQ_mumi_idx;
Int_t           Reco_mu_nTrkHits[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_nTrkHits;   //!
Float_t         Reco_mu_normChi2_global[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_normChi2_global;   //!
Int_t           Reco_mu_nMuValHits[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_nMuValHits;   //!
Int_t           Reco_mu_StationsMatched[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_StationsMatched;   //!
Float_t         Reco_mu_dxy[maxBranchSize];   //[Reco_mu_size]
Float_t         Reco_mu_dxyErr[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_dxy;   //!
TBranch        *b_Reco_mu_dxyErr;   //!
Float_t         Reco_mu_dz[maxBranchSize];   //[Reco_mu_size]
Float_t         Reco_mu_dzErr[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_dz;   //!
TBranch        *b_Reco_mu_dzErr;   //!
Int_t           Reco_mu_nTrkWMea[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_nTrkWMea;   //!
Bool_t          Reco_mu_TMOneStaTight[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_TMOneStaTight;   //!
Int_t           Reco_mu_nPixWMea[maxBranchSize];   //[Reco_mu_size]
TBranch        *b_Reco_mu_nPixWMea;   //!
Short_t           Reco_QQ_sign[maxBranchSize];   //[Reco_QQ_size]
TBranch        *b_Reco_QQ_sign;   //!

Int_t           Reco_mu_nPixValHits[maxBranchSize];   //[Reco_QQ_size]
TBranch        *b_Reco_mu_nPixValHits;   //!
Float_t         Reco_mu_ptErr_global[maxBranchSize];   //[Reco_QQ_size]
TBranch        *b_Reco_mu_ptErr_global;   //!

Int_t           Reco_mu_SelectionType[maxBranchSize];
TBranch        *b_Reco_mu_SelectionType;

Float_t         Reco_QQ_ctau[maxBranchSize];
Float_t         Reco_QQ_ctau3D[maxBranchSize];
Float_t         Reco_QQ_ctauErr[maxBranchSize];
Float_t         Reco_QQ_ctauErr3D[maxBranchSize];
TBranch        *b_Reco_QQ_ctau;
TBranch        *b_Reco_QQ_ctau3D;
TBranch        *b_Reco_QQ_ctauErr;
TBranch        *b_Reco_QQ_ctauErr3D;

Float_t         Reco_QQ_MassErr[maxBranchSize];
Float_t         Reco_mu_normChi2_inner[maxBranchSize];
Float_t         Reco_mu_ptErr_inner[maxBranchSize];
TBranch        *b_Reco_QQ_MassErr;
TBranch        *b_Reco_mu_normChi2_inner;
TBranch        *b_Reco_mu_ptErr_inner;

Bool_t          Reco_QQ_isCowboy[maxBranchSize];
Float_t         Reco_QQ_cosAlpha[maxBranchSize];
Float_t         Reco_QQ_cosAlpha3D[maxBranchSize];
Float_t         Reco_QQ_dca[maxBranchSize];
TBranch        *b_Reco_QQ_isCowboy;
TBranch        *b_Reco_QQ_cosAlpha;
TBranch        *b_Reco_QQ_cosAlpha3D;
TBranch        *b_Reco_QQ_dca;

Short_t Reco_mu_charge[maxBranchSize];
TBranch *b_Reco_mu_charge;


/////////////////////////////////////////
////// Gen QQ 
/////////////////////////////////////////
Short_t           Gen_QQ_size;
Int_t           Gen_QQ_type[maxBranchSize];   //[Gen_QQ_size]
TClonesArray    *Gen_QQ_4mom;
TClonesArray    *Gen_mu_4mom;
TBranch        *b_Gen_QQ_size;   //!
TBranch        *b_Gen_QQ_type;   //!
TBranch        *b_Gen_QQ_4mom;   //!
TBranch        *b_Gen_mu_4mom;   //!
Short_t Reco_mu_whichGen[maxBranchSize];
TBranch *b_Reco_mu_whichGen;
Short_t Reco_QQ_whichGen[maxBranchSize];
TBranch *b_Reco_QQ_whichGen;
Float_t Gen_weight;
TBranch *b_Gen_weight;

Short_t Gen_QQ_mupl_idx[maxBranchSize];
Short_t Gen_QQ_mumi_idx[maxBranchSize];
TBranch *b_Gen_QQ_mupl_idx;
TBranch *b_Gen_QQ_mumi_idx;

Short_t Gen_mu_charge[maxBranchSize];
TBranch *b_Gen_mu_charge;

int fTrkMu = 3;
int fGlbMu = 1;


class SetTree
{
  public:
    SetTree(){};

    virtual ~SetTree();
    virtual void TreeSetting(TTree* tree, bool isMC);
    Bool_t SoftMuIdCut(int irqq);
    Bool_t AccTrig(int irqq);
    Bool_t AccNoTrig(int irqq);
    Bool_t SelCut(int irqq, int is);
};

SetTree::~SetTree()
{
}


void SetTree::TreeSetting(TTree* tree, bool isMC)
{
  Reco_QQ_4mom = 0;
  Reco_mu_4mom = 0;

  tree->SetBranchAddress("runNb", &runNb, &b_runNb);
  tree->SetBranchAddress("LS", &LS, &b_LS);
  tree->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
  tree->SetBranchAddress("zVtx", &zVtx, &b_zVtx);
  tree->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
  tree->SetBranchAddress("SumET_HF", &SumET_HF, &b_SumET_HF);
  tree->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
  tree->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  tree->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  tree->SetBranchAddress("Reco_mu_size", &Reco_mu_size, &b_Reco_mu_size);
  tree->SetBranchAddress("Reco_mu_4mom", &Reco_mu_4mom, &b_Reco_mu_4mom);
  tree->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  tree->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
  tree->SetBranchAddress("Reco_QQ_mupl_idx",Reco_QQ_mupl_idx,&b_Reco_QQ_mupl_idx);
  tree->SetBranchAddress("Reco_QQ_mumi_idx",Reco_QQ_mumi_idx,&b_Reco_QQ_mumi_idx);
  tree->SetBranchAddress("Reco_mu_trig", Reco_mu_trig, &b_Reco_mu_trig);
  tree->SetBranchAddress("Reco_mu_nTrkHits", Reco_mu_nTrkHits, &b_Reco_mu_nTrkHits);
  tree->SetBranchAddress("Reco_mu_normChi2_global", Reco_mu_normChi2_global, &b_Reco_mu_normChi2_global);
  tree->SetBranchAddress("Reco_mu_nMuValHits", Reco_mu_nMuValHits, &b_Reco_mu_nMuValHits);
  tree->SetBranchAddress("Reco_mu_StationsMatched", Reco_mu_StationsMatched, &b_Reco_mu_StationsMatched);
  tree->SetBranchAddress("Reco_mu_dxy", Reco_mu_dxy, &b_Reco_mu_dxy);
  tree->SetBranchAddress("Reco_mu_dxyErr", Reco_mu_dxyErr, &b_Reco_mu_dxyErr);
  tree->SetBranchAddress("Reco_mu_dz", Reco_mu_dz, &b_Reco_mu_dz);
  tree->SetBranchAddress("Reco_mu_dzErr", Reco_mu_dzErr, &b_Reco_mu_dzErr);
  tree->SetBranchAddress("Reco_mu_TMOneStaTight", Reco_mu_TMOneStaTight, &b_Reco_mu_TMOneStaTight);
  tree->SetBranchAddress("Reco_mu_nPixWMea", Reco_mu_nPixWMea, &b_Reco_mu_nPixWMea);
  tree->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  tree->SetBranchAddress("Reco_mu_nTrkWMea", Reco_mu_nTrkWMea, &b_Reco_mu_nTrkWMea);
  tree->SetBranchAddress("Reco_QQ_ctau",Reco_QQ_ctau,&b_Reco_QQ_ctau);
  tree->SetBranchAddress("Reco_QQ_ctau3D",Reco_QQ_ctau3D,&b_Reco_QQ_ctau3D);
  tree->SetBranchAddress("Reco_QQ_ctauErr",Reco_QQ_ctauErr,&b_Reco_QQ_ctauErr);
  tree->SetBranchAddress("Reco_QQ_ctauErr3D",Reco_QQ_ctauErr3D,&b_Reco_QQ_ctauErr3D);
  tree->SetBranchAddress("Reco_QQ_cosAlpha",Reco_QQ_cosAlpha,&b_Reco_QQ_cosAlpha);
  tree->SetBranchAddress("Reco_QQ_cosAlpha3D",Reco_QQ_cosAlpha3D,&b_Reco_QQ_cosAlpha3D);
  tree->SetBranchAddress("Reco_QQ_dca",Reco_QQ_dca,&b_Reco_QQ_dca);
  tree->SetBranchAddress("Reco_mu_nPixValHits", Reco_mu_nPixValHits, &b_Reco_mu_nPixValHits);
  tree->SetBranchAddress("Reco_mu_ptErr_global", Reco_mu_ptErr_global, &b_Reco_mu_ptErr_global);
  tree->SetBranchAddress("Reco_mu_SelectionType", Reco_mu_SelectionType, &b_Reco_mu_SelectionType);
  tree->SetBranchAddress("Reco_mu_highPurity", Reco_mu_highPurity, &b_Reco_mu_highPurity);
  tree->SetBranchAddress("Reco_QQ_MassErr", Reco_QQ_MassErr, &b_Reco_QQ_MassErr);
  tree->SetBranchAddress("Reco_mu_normChi2_inner", Reco_mu_normChi2_inner, &b_Reco_mu_normChi2_inner);
  tree->SetBranchAddress("Reco_mu_ptErr_inner", Reco_mu_ptErr_inner, &b_Reco_mu_ptErr_inner);
  tree->SetBranchAddress("Reco_mu_charge",Reco_mu_charge, &b_Reco_mu_charge);

  if (isMC) { 
    Gen_QQ_4mom = 0;
    Gen_mu_4mom = 0;
    tree->SetBranchAddress("Gen_QQ_size", &Gen_QQ_size, &b_Gen_QQ_size);
    tree->SetBranchAddress("Gen_QQ_type", Gen_QQ_type, &b_Gen_QQ_type);
    tree->SetBranchAddress("Gen_QQ_4mom", &Gen_QQ_4mom, &b_Gen_QQ_4mom);
    tree->SetBranchAddress("Gen_mu_4mom", &Gen_mu_4mom, &b_Gen_mu_4mom);
    tree->SetBranchAddress("Reco_mu_whichGen",Reco_mu_whichGen, &b_Reco_mu_whichGen);
    tree->SetBranchAddress("Reco_QQ_whichGen",Reco_QQ_whichGen, &b_Reco_QQ_whichGen);
    tree->SetBranchAddress("Gen_weight",&Gen_weight, &b_Gen_weight);
    tree->SetBranchAddress("Gen_QQ_mupl_idx",Gen_QQ_mupl_idx, &b_Gen_QQ_mupl_idx);
    tree->SetBranchAddress("Gen_QQ_mumi_idx",Gen_QQ_mumi_idx, &b_Gen_QQ_mumi_idx);
    tree->SetBranchAddress("Gen_mu_charge",Gen_mu_charge, &b_Gen_mu_charge);
  }

};

Bool_t SetTree::AccTrig(int irqq)
{
  TLorentzVector* mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);;
  TLorentzVector* mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);;

  double pt1 = mupl_Reco->Pt();
  double eta1 = mupl_Reco->Eta();
  double pt2 = mumi_Reco->Pt();
  double eta2 = mumi_Reco->Eta();

  bool mupl_b = IsAcceptanceQQ(pt1,eta1);
  bool mumi_b = IsAcceptanceQQ(pt2,eta2);
  
  return (mupl_b && mumi_b);
}

Bool_t SetTree::AccNoTrig(int irqq)
{
  TLorentzVector* mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);;
  TLorentzVector* mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);;

  double pt1 = mupl_Reco->Pt();
  double eta1 = mupl_Reco->Eta();
  double pt2 = mumi_Reco->Pt();
  double eta2 = mumi_Reco->Eta();
  
  bool mupl_b = IsAcceptanceNoTrig(pt1,eta1);
  bool mumi_b = IsAcceptanceNoTrig(pt2,eta2);

  return (mupl_b && mumi_b);
}



Bool_t SetTree::SoftMuIdCut(int irqq)
{
  bool passMuonTypePl = true;
  passMuonTypePl = passMuonTypePl && (Reco_mu_SelectionType[Reco_QQ_mupl_idx[irqq]]&((int)pow(2,fGlbMu)));
  passMuonTypePl = passMuonTypePl && (Reco_mu_SelectionType[Reco_QQ_mupl_idx[irqq]]&((int)pow(2,fTrkMu)));

  bool passMuonTypeMi = true;
  passMuonTypeMi = passMuonTypeMi && (Reco_mu_SelectionType[Reco_QQ_mumi_idx[irqq]]&((int)pow(2,fGlbMu)));
  passMuonTypeMi = passMuonTypeMi && (Reco_mu_SelectionType[Reco_QQ_mumi_idx[irqq]]&((int)pow(2,fTrkMu)));

  bool muplSoft = (  //(Reco_mu_TMOneStaTight[Reco_QQ_mupl_idx[irqq]]==true) &&
      (Reco_mu_nTrkWMea[Reco_QQ_mupl_idx[irqq]] > 5) &&
      (Reco_mu_nPixWMea[Reco_QQ_mupl_idx[irqq]] > 0) &&
      (fabs(Reco_mu_dxy[Reco_QQ_mupl_idx[irqq]])<0.3) &&
      (fabs(Reco_mu_dz[Reco_QQ_mupl_idx[irqq]])<20.) &&
      passMuonTypePl        //			 &&  (Reco_mu_highPurity[Reco_QQ_mupl_idx[irqq]]==true) 
      ) ; 

  bool mumiSoft = ( //(Reco_mu_TMOneStaTight[Reco_QQ_mumi_idx[irqq]]==true) &&
      (Reco_mu_nTrkWMea[Reco_QQ_mumi_idx[irqq]] > 5) &&
      (Reco_mu_nPixWMea[Reco_QQ_mumi_idx[irqq]] > 0) &&
      (fabs(Reco_mu_dxy[Reco_QQ_mumi_idx[irqq]])<0.3) &&
      (fabs(Reco_mu_dz[Reco_QQ_mumi_idx[irqq]])<20.)  && 
      passMuonTypeMi       //			 &&  (Reco_mu_highPurity[Reco_QQ_mupl_idx[irqq]]==true) 
      ) ; 

  return (muplSoft && mumiSoft);
}  

Bool_t SetTree::SelCut(int irqq, int is)
{
  bool isHBSoft = SoftMuIdCut(irqq);
  bool isAccTrig = AccTrig(irqq);
  bool isAccNoTrig = AccNoTrig(irqq);

  if(is==0){return true;}
  else if(is==1){ return isAccNoTrig;}
  else if(is==2){ return isAccTrig;}
  else if(is==3){ return (isAccNoTrig && isHBSoft);}
  else if(is==4 || is==5){ return (isAccTrig && isHBSoft);}
}  



#endif 
