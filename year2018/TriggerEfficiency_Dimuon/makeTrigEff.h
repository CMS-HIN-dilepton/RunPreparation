#ifndef makeTrigEff_h
#define makeTrigEff_h

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

class oniaTree {
 public :
  TTree          *fChain;   //!pointer to the analyzed TTree or TChain                                                                                                                                 
  Int_t           fCurrent; //!current Tree number in a TChain

  Float_t jpsi_m;
  Float_t jpsi_pt;
  Float_t jpsi_eta;
  Float_t jpsi_phi;
  Float_t jpsi_rap;
  int triggerIndex_PP =0;
  string treeLabel = "";

  UInt_t          eventNb;
  UInt_t          runNb;
  Int_t           Centrality;
  Int_t           nTrig;
  Int_t           trigPrescale[99];   //[nTrig]                                                                                                                                                        
  ULong64_t       HLTriggers;

  Int_t           Reco_QQ_size;
  Int_t           Reco_QQ_type[99];   //[Reco_QQ_size]                                                                                                                                                 
  Int_t           Reco_QQ_sign[99];   //[Reco_QQ_size]                                                                                                                                                 
  TClonesArray    *Reco_QQ_4mom;
  TClonesArray    *Reco_QQ_mupl_4mom;
  TClonesArray    *Reco_QQ_mumi_4mom;
  ULong64_t       Reco_QQ_trig[99];   //[Reco_QQ_size]                                                                                                                                                 
  ULong64_t       Reco_QQ_mupl_trig[99];   //[Reco_QQ_size]                                                                                                                                            
  ULong64_t       Reco_QQ_mumi_trig[99];   //[Reco_QQ_size]
  Bool_t          Reco_QQ_isCowboy[99];   //[Reco_QQ_size]                                                                                                                                             
  Float_t         Reco_QQ_ctau[99];   //[Reco_QQ_size]                                                                                                                                                 
  Float_t         Reco_QQ_ctauErr[99];   //[Reco_QQ_size]                                                                                                                                              
  Float_t         Reco_QQ_ctau3D[99];   //[Reco_QQ_size]                                                                                                                                               
  Float_t         Reco_QQ_ctauErr3D[99];   //[Reco_QQ_size]                                                                                                                                            
  Float_t         Reco_QQ_VtxProb[99];   //[Reco_QQ_size]                                                                                                                                              
  Float_t         Reco_QQ_dca[99];   //[Reco_QQ_size]                                                                                                                                                  
  Float_t         Reco_QQ_MassErr[99];   //[Reco_QQ_size]                                                                                                                                              
  TClonesArray    *Reco_QQ_vtx;
  Int_t           Reco_QQ_Ntrk[99];   //[Reco_QQ_size]                                                                                                                                                 
  Int_t           Reco_QQ_mupl_SelectionType[99];   //[Reco_QQ_size]                                                                                                                                   
  Int_t           Reco_QQ_mumi_SelectionType[99];   //[Reco_QQ_size]                                                                                                                                   
  Bool_t          Reco_QQ_mupl_isGoodMuon[99];   //[Reco_QQ_size]                                                                                                                                      
  Bool_t          Reco_QQ_mumi_isGoodMuon[99];   //[Reco_QQ_size]                                                                                                                                      
  Bool_t          Reco_QQ_mupl_highPurity[99];   //[Reco_QQ_size]                                                                                                                                      
  Bool_t          Reco_QQ_mumi_highPurity[99];   //[Reco_QQ_size]                                                                                                                                      
  Bool_t          Reco_QQ_mupl_TrkMuArb[99];   //[Reco_QQ_size]                                                                                                                                        
  Bool_t          Reco_QQ_mumi_TrkMuArb[99];   //[Reco_QQ_size]                                                                                                                                        
  Bool_t          Reco_QQ_mupl_TMOneStaTight[99];   //[Reco_QQ_size]                                                                                                                                   
  Bool_t          Reco_QQ_mumi_TMOneStaTight[99];   //[Reco_QQ_size]                                                                                                                                   
  Int_t           Reco_QQ_mupl_nPixValHits[99];   //[Reco_QQ_size]                                                                                                                                     
  Int_t           Reco_QQ_mumi_nPixValHits[99];   //[Reco_QQ_size]                                                                                                                                     
  Int_t           Reco_QQ_mupl_nMuValHits[99];   //[Reco_QQ_size]                                                                                                                                      
  Int_t           Reco_QQ_mumi_nMuValHits[99];   //[Reco_QQ_size]                                                                                                                                      
  Int_t           Reco_QQ_mupl_nTrkHits[99];   //[Reco_QQ_size]                                                                                                                                        
  Int_t           Reco_QQ_mumi_nTrkHits[99];   //[Reco_QQ_size]                                                                                                                                        
  Float_t         Reco_QQ_mupl_normChi2_inner[99];   //[Reco_QQ_size]                                                                                                                                  
  Float_t         Reco_QQ_mumi_normChi2_inner[99];   //[Reco_QQ_size]                                                                                                                                  
  Float_t         Reco_QQ_mupl_normChi2_global[99];   //[Reco_QQ_size]                                                                                                                                 
  Float_t         Reco_QQ_mumi_normChi2_global[99];   //[Reco_QQ_size]
  Int_t           Reco_QQ_mupl_nPixWMea[99];   //[Reco_QQ_size]                                                                                                                                        
  Int_t           Reco_QQ_mumi_nPixWMea[99];   //[Reco_QQ_size]                                                                                                                                        
  Int_t           Reco_QQ_mupl_nTrkWMea[99];   //[Reco_QQ_size]                                                                                                                                        
  Int_t           Reco_QQ_mumi_nTrkWMea[99];   //[Reco_QQ_size]                                                                                                                                        
  Int_t           Reco_QQ_mupl_StationsMatched[99];   //[Reco_QQ_size]                                                                                                                                 
  Int_t           Reco_QQ_mumi_StationsMatched[99];   //[Reco_QQ_size]                                                                                                                                 
  Float_t         Reco_QQ_mupl_dxy[99];   //[Reco_QQ_size]                                                                                                                                             
  Float_t         Reco_QQ_mumi_dxy[99];   //[Reco_QQ_size]                                                                                                                                             
  Float_t         Reco_QQ_mupl_dxyErr[99];   //[Reco_QQ_size]                                                                                                                                          
  Float_t         Reco_QQ_mumi_dxyErr[99];   //[Reco_QQ_size]                                                                                                                                          
  Float_t         Reco_QQ_mupl_dz[99];   //[Reco_QQ_size]                                                                                                                                              
  Float_t         Reco_QQ_mumi_dz[99];   //[Reco_QQ_size]                                                                                                                                              
  Float_t         Reco_QQ_mupl_dzErr[99];   //[Reco_QQ_size]                                                                                                                                           
  Float_t         Reco_QQ_mumi_dzErr[99];   //[Reco_QQ_size]                                                                                                                                           
  Float_t         Reco_QQ_mupl_pt_inner[99];   //[Reco_QQ_size]                                                                                                                                        
  Float_t         Reco_QQ_mumi_pt_inner[99];   //[Reco_QQ_size]                                                                                                                                        
  Float_t         Reco_QQ_mupl_pt_global[99];   //[Reco_QQ_size]                                                                                                                                       
  Float_t         Reco_QQ_mumi_pt_global[99];   //[Reco_QQ_size]                                                                                                                                       
  Float_t         Reco_QQ_mupl_ptErr_inner[99];   //[Reco_QQ_size]                                                                                                                                     
  Float_t         Reco_QQ_mumi_ptErr_inner[99];   //[Reco_QQ_size]                                                                                                                                     
  Float_t         Reco_QQ_mupl_ptErr_global[99];   //[Reco_QQ_size]                                                                                                                                    
  Float_t         Reco_QQ_mumi_ptErr_global[99];   //[Reco_QQ_size]

  Int_t           HLT_HIL1DoubleMuOpen_v1;
  Int_t           HLT_HIL1DoubleMuOpen_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_30_100_v1;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_30_100_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_40_100_v1;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_40_100_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_50_100_v1;
  Int_t           HLT_HIL1DoubleMuOpen_Centrality_50_100_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_MAXdR2p0_v1;
  Int_t           HLT_HIL1DoubleMuOpen_MAXdR2p0_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1;
  Int_t           HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_MAXdR3p5_v1;
  Int_t           HLT_HIL1DoubleMuOpen_MAXdR3p5_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_OS_v1;
  Int_t           HLT_HIL1DoubleMuOpen_OS_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_SS_v1;
  Int_t           HLT_HIL1DoubleMuOpen_SS_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_er1p6_v1;
  Int_t           HLT_HIL1DoubleMuOpen_er1p6_v1_Prescl;
  Int_t           HLT_HIL1DoubleMuOpen_OS_er1p6_v1;
  Int_t           HLT_HIL1DoubleMuOpen_OS_er1p6_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu0_v1;
  Int_t           HLT_HIL1DoubleMu0_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu2_v1;
  Int_t           HLT_HIL1DoubleMu2_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu2p5_v1;
  Int_t           HLT_HIL1DoubleMu2p5_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu3_v1;
  Int_t           HLT_HIL1DoubleMu3_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu2_OS_v1;
  Int_t           HLT_HIL1DoubleMu2_OS_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu3_OS_v1;
  Int_t           HLT_HIL1DoubleMu3_OS_v1_Prescl;
  Int_t           HLT_HIL1DoubleMu10_v1;
  Int_t           HLT_HIL1DoubleMu10_v1_Prescl;
  Int_t           HLT_HIL2_L1DoubleMu10_v1;
  Int_t           HLT_HIL2_L1DoubleMu10_v1_Prescl;
  Int_t           HLT_HIL3_L1DoubleMu10_v1;
  Int_t           HLT_HIL3_L1DoubleMu10_v1_Prescl;
  Int_t           HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1;
  Int_t           HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl;
  Int_t           HLT_HIL2DoubleMuOpen_v1;
  Int_t           HLT_HIL2DoubleMuOpen_v1_Prescl;
  Int_t           HLT_HIL3DoubleMuOpen_v1;
  Int_t           HLT_HIL3DoubleMuOpen_v1_Prescl;
  Int_t           HLT_HIL3DoubleMuOpen_M60120_v1;
  Int_t           HLT_HIL3DoubleMuOpen_M60120_v1_Prescl;
  Int_t           HLT_HIL3DoubleMuOpen_Jpsi_v1;
  Int_t           HLT_HIL3DoubleMuOpen_Jpsi_v1_Prescl;
  Int_t           HLT_HIL3DoubleMuOpen_Upsi_v1;
  Int_t           HLT_HIL3DoubleMuOpen_Upsi_v1_Prescl;
  Int_t           HLT_HIL3Mu0_L2Mu0_v1;
  Int_t           HLT_HIL3Mu0_L2Mu0_v1_Prescl;
  Int_t           HLT_HIL3Mu0_L2Mu0_testignore_v1;
  Int_t           HLT_HIL3Mu0_L2Mu0_testignore_v1_Prescl;
  Int_t           HLT_HIL3Mu2_L2Mu0_v1;
  Int_t           HLT_HIL3Mu2_L2Mu0_v1_Prescl;
  Int_t           HLT_HIL3Mu2p5_L2Mu0_v1;
  Int_t           HLT_HIL3Mu2p5_L2Mu0_v1_Prescl;
  Int_t           HLT_HIL3Mu3_L2Mu0_v1;
  Int_t           HLT_HIL3Mu3_L2Mu0_v1_Prescl;
  Int_t           HLT_HIL3Mu2p5_L1DoubleMu0_v1;
  Int_t           HLT_HIL3Mu2p5_L1DoubleMu0_v1_Prescl;
  Int_t           HLT_HIL3Mu3_L1DoubleMuOpen_v1;
  Int_t           HLT_HIL3Mu3_L1DoubleMuOpen_v1_Prescl;
  Int_t           HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1;
  Int_t           HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1_Prescl;
  Int_t           HLT_HIL3Mu3_L1DoubleMu0_v1;
  Int_t           HLT_HIL3Mu3_L1DoubleMu0_v1_Prescl;
  Int_t           HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1;
  Int_t           HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1_Prescl;
  Int_t           HLT_HIL3Mu3_L1TripleMuOpen_v1;
  Int_t           HLT_HIL3Mu3_L1TripleMuOpen_v1_Prescl;


  TBranch        *b_eventNb;   //!                                                                                                                                                                     
  TBranch        *b_runNb;   //!                                                                                                      
  TBranch        *b_Centrality;   //!                                                                                                                                                                  
  TBranch        *b_nTrig;   //!                                                                                                                                                                       
  TBranch        *b_trigPrescale;   //!                                                                                                                                                                
  TBranch        *b_HLTriggers;   //!

  TBranch        *b_Reco_QQ_size;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_type;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_sign;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_4mom;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_mupl_4mom;   //!                                                                                                                                                           
  TBranch        *b_Reco_QQ_mumi_4mom;   //!                                                                                                                                                           
  TBranch        *b_Reco_QQ_trig;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_mupl_trig;   //!                                                                                                                                                           
  TBranch        *b_Reco_QQ_mumi_trig;   //!                                                                                                                                                           
  TBranch        *b_Reco_QQ_isCowboy;   //!                                                                                                                                                            
  TBranch        *b_Reco_QQ_ctau;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_ctauErr;   //!                                                                                                                                                             
  TBranch        *b_Reco_QQ_ctau3D;   //!                                                                                                                                                              
  TBranch        *b_Reco_QQ_ctauErr3D;   //!                                                                                                                                                           
  TBranch        *b_Reco_QQ_VtxProb;   //!                                                                                                                                                             
  TBranch        *b_Reco_QQ_dca;   //!                                                                                                                                                                 
  TBranch        *b_Reco_QQ_MassErr;   //!                                                                                                                                                             
  TBranch        *b_Reco_QQ_vtx;   //!                                                                                                                                                                 
  TBranch        *b_Reco_QQ_Ntrk;   //!                                                                                                                                                                
  TBranch        *b_Reco_QQ_mupl_SelectionType;   //!                                                                                                                                                  
  TBranch        *b_Reco_QQ_mumi_SelectionType;   //!                                                                                                                                                  
  TBranch        *b_Reco_QQ_mupl_isGoodMuon;   //!
  TBranch        *b_Reco_QQ_mumi_isGoodMuon;   //!                                                                                                                                                     
  TBranch        *b_Reco_QQ_mupl_highPurity;   //!                                                                                                                                                     
  TBranch        *b_Reco_QQ_mumi_highPurity;   //!                                                                                                                                                     
  TBranch        *b_Reco_QQ_mupl_TrkMuArb;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mumi_TrkMuArb;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mupl_TMOneStaTight;   //!                                                                                                                                                  
  TBranch        *b_Reco_QQ_mumi_TMOneStaTight;   //!                                                                                                                                                  
  TBranch        *b_Reco_QQ_mupl_nPixValHits;   //!                                                                                                                                                    
  TBranch        *b_Reco_QQ_mumi_nPixValHits;   //!                                                                                                                                                    
  TBranch        *b_Reco_QQ_mupl_nMuValHits;   //!                                                                                                                                                     
  TBranch        *b_Reco_QQ_mumi_nMuValHits;   //!                                                                                                                                                     
  TBranch        *b_Reco_QQ_mupl_nTrkHits;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mumi_nTrkHits;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mupl_normChi2_inner;   //!                                                                                                                                                 
  TBranch        *b_Reco_QQ_mumi_normChi2_inner;   //!                                                                                                                                                 
  TBranch        *b_Reco_QQ_mupl_normChi2_global;   //!                                                                                                                                                
  TBranch        *b_Reco_QQ_mumi_normChi2_global;   //!                                                                                                                                                
  TBranch        *b_Reco_QQ_mupl_nPixWMea;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mumi_nPixWMea;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mupl_nTrkWMea;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mumi_nTrkWMea;   //!
  TBranch        *b_Reco_QQ_mupl_StationsMatched;   //!                                                                                                                                                
  TBranch        *b_Reco_QQ_mumi_StationsMatched;   //!                                                                                                                                                
  TBranch        *b_Reco_QQ_mupl_dxy;   //!                                                                                                                                                            
  TBranch        *b_Reco_QQ_mumi_dxy;   //!                                                                                                                                                            
  TBranch        *b_Reco_QQ_mupl_dxyErr;   //!                                                                                                                                                         
  TBranch        *b_Reco_QQ_mumi_dxyErr;   //!                                                                                                                                                         
  TBranch        *b_Reco_QQ_mupl_dz;   //!                                                                                                                                                             
  TBranch        *b_Reco_QQ_mumi_dz;   //!                                                                                                                                                             
  TBranch        *b_Reco_QQ_mupl_dzErr;   //!                                                                                                                                                          
  TBranch        *b_Reco_QQ_mumi_dzErr;   //!                                                                                                                                                          
  TBranch        *b_Reco_QQ_mupl_pt_inner;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mumi_pt_inner;   //!                                                                                                                                                       
  TBranch        *b_Reco_QQ_mupl_pt_global;   //!                                                                                                                                                      
  TBranch        *b_Reco_QQ_mumi_pt_global;   //!                                                                                                                                                      
  TBranch        *b_Reco_QQ_mupl_ptErr_inner;   //!                                                                                                                                                    
  TBranch        *b_Reco_QQ_mumi_ptErr_inner;   //!                                                                                                                                                    
  TBranch        *b_Reco_QQ_mupl_ptErr_global;   //!                                                                                                                                                   
  TBranch        *b_Reco_QQ_mumi_ptErr_global;   //!

  TBranch        *b_HLT_HIL1DoubleMuOpen_v1;   //!                                                                                                                                                     
  TBranch        *b_HLT_HIL1DoubleMuOpen_v1_Prescl;   //!                                                                                                                                              
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_30_100_v1;   //!                                                                                                                                   
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_30_100_v1_Prescl;   //!                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_40_100_v1;   //!                                                                                                                                   
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_40_100_v1_Prescl;   //!                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_50_100_v1;   //!                                                                                                                                   
  TBranch        *b_HLT_HIL1DoubleMuOpen_Centrality_50_100_v1_Prescl;   //!                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_MAXdR2p0_v1;   //!                                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_MAXdR2p0_v1_Prescl;   //!                                                                                                                                     
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1;   //!                                                                                                                                         
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl;   //!                                                                                                                                  
  TBranch        *b_HLT_HIL1DoubleMuOpen_MAXdR3p5_v1;   //!                                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_MAXdR3p5_v1_Prescl;   //!                                                                                                                                     
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_v1;   //!                                                                                                                                                  
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_v1_Prescl;   //!                                                                                                                                           
  TBranch        *b_HLT_HIL1DoubleMuOpen_SS_v1;   //!                                                                                                                                                  
  TBranch        *b_HLT_HIL1DoubleMuOpen_SS_v1_Prescl;   //!                                                                                                                                           
  TBranch        *b_HLT_HIL1DoubleMuOpen_er1p6_v1;   //!                                                                                                                                               
  TBranch        *b_HLT_HIL1DoubleMuOpen_er1p6_v1_Prescl;   //!                                                                                                                                        
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_er1p6_v1;   //!                                                                                                                                            
  TBranch        *b_HLT_HIL1DoubleMuOpen_OS_er1p6_v1_Prescl;   //!                                                          
  TBranch        *b_HLT_HIL1DoubleMu0_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL1DoubleMu0_v1_Prescl;   //!                                                                                                                                                 
  TBranch        *b_HLT_HIL1DoubleMu2_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL1DoubleMu2_v1_Prescl;   //!                                                                                                                                                 
  TBranch        *b_HLT_HIL1DoubleMu2p5_v1;   //!                                                                                                                                                      
  TBranch        *b_HLT_HIL1DoubleMu2p5_v1_Prescl;   //!                                                                                                                                               
  TBranch        *b_HLT_HIL1DoubleMu3_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL1DoubleMu3_v1_Prescl;   //!                                                                                                                                                 
  TBranch        *b_HLT_HIL1DoubleMu2_OS_v1;   //!                                                                                                                                                     
  TBranch        *b_HLT_HIL1DoubleMu2_OS_v1_Prescl;   //!                                                                                                                                              
  TBranch        *b_HLT_HIL1DoubleMu3_OS_v1;   //!                                                                                                                                                     
  TBranch        *b_HLT_HIL1DoubleMu3_OS_v1_Prescl;   //!                                                                                                                                              
  TBranch        *b_HLT_HIL1DoubleMu10_v1;   //!                                                                                                                                                       
  TBranch        *b_HLT_HIL1DoubleMu10_v1_Prescl;   //!                                                                                                                                                
  TBranch        *b_HLT_HIL2_L1DoubleMu10_v1;   //!                                                                                                                                                    
  TBranch        *b_HLT_HIL2_L1DoubleMu10_v1_Prescl;   //!                                                                                                                                             
  TBranch        *b_HLT_HIL3_L1DoubleMu10_v1;   //!                                                                                                                                                    
  TBranch        *b_HLT_HIL3_L1DoubleMu10_v1_Prescl;   //!                                                                                                                                             
  TBranch        *b_HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1;   //!                                                                                                                              
  TBranch        *b_HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl;   //!                                                                                                                       
  TBranch        *b_HLT_HIL2DoubleMuOpen_v1;   //!                                                                                                                                                   
  TBranch        *b_HLT_HIL2DoubleMuOpen_v1_Prescl;
  TBranch        *b_HLT_HIL3DoubleMuOpen_v1;   //!                                                                                                                                                     
  TBranch        *b_HLT_HIL3DoubleMuOpen_v1_Prescl;   //!                                                                                                                                              
  TBranch        *b_HLT_HIL3DoubleMuOpen_M60120_v1;   //!                                                                                                                                              
  TBranch        *b_HLT_HIL3DoubleMuOpen_M60120_v1_Prescl;   //!                                                                                                                                       
  TBranch        *b_HLT_HIL3DoubleMuOpen_Jpsi_v1;   //!                                                                                                                                                
  TBranch        *b_HLT_HIL3DoubleMuOpen_Jpsi_v1_Prescl;   //!                                                                                                                                         
  TBranch        *b_HLT_HIL3DoubleMuOpen_Upsi_v1;   //!                                                                                                                                                
  TBranch        *b_HLT_HIL3DoubleMuOpen_Upsi_v1_Prescl;   //!   
  TBranch        *b_HLT_HIL3Mu0_L2Mu0_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL3Mu0_L2Mu0_v1_Prescl;   //!                                                                                                                                                 
  TBranch        *b_HLT_HIL3Mu0_L2Mu0_testignore_v1;   //!                                                                                                                                             
  TBranch        *b_HLT_HIL3Mu0_L2Mu0_testignore_v1_Prescl;   //!                                                                                                                                      
  TBranch        *b_HLT_HIL3Mu2_L2Mu0_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL3Mu2_L2Mu0_v1_Prescl;   //!                                                                                                                                                 
  TBranch        *b_HLT_HIL3Mu2p5_L2Mu0_v1;   //!                                                                                                                                                      
  TBranch        *b_HLT_HIL3Mu2p5_L2Mu0_v1_Prescl;   //!                                                                                                                                               
  TBranch        *b_HLT_HIL3Mu3_L2Mu0_v1;   //!                                                                                                                                                        
  TBranch        *b_HLT_HIL3Mu3_L2Mu0_v1_Prescl;   //!      
  TBranch        *b_HLT_HIL3Mu2p5_L1DoubleMu0_v1;   //!                                                                                                                                                
  TBranch        *b_HLT_HIL3Mu2p5_L1DoubleMu0_v1_Prescl;   //!                                                                                                                                         
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMuOpen_v1;   //!                                                                                                                                               
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMuOpen_v1_Prescl;   //!                                                                                                                                        
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1;   //!                                                                                                                                            
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1_Prescl;   //!                                                                                                                                     
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMu0_v1;   //!                                                                                                                                                  
  TBranch        *b_HLT_HIL3Mu3_L1DoubleMu0_v1_Prescl;   //!                                                                                                                                           
  TBranch        *b_HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1;   //!                                                                                                                                        
  TBranch        *b_HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1_Prescl;   //!                                                                                                                                 
  TBranch        *b_HLT_HIL3Mu3_L1TripleMuOpen_v1;   //!                                                                                                                                               
  TBranch        *b_HLT_HIL3Mu3_L1TripleMuOpen_v1_Prescl;   //!   

  oniaTree(string fileName = "");
  virtual ~oniaTree();

  virtual Int_t    Cut(Long64_t entry);
  virtual Int_t    GetEntry(Long64_t entry);
  virtual Long64_t LoadTree(Long64_t entry);
  virtual void     Init(TTree *tree);
  //virtual void     Loop();
  virtual Bool_t   Notify();
  virtual void     Show(Long64_t entry = -1);

  virtual void     TrigEffCalc(string trigLabel = "");
  virtual void     AllEffCalc();
  virtual void     Plot(string inputName);
  virtual int      color(int i);
  virtual void     plotAll();
  virtual Bool_t   isTriggerMatch (Int_t iRecoQQ, Int_t TriggerBit);
  virtual Bool_t   isGlobalMuonInAccept2015 (TLorentzVector* Muon);
  virtual Bool_t   areMuonsInAcceptance2015 (Int_t iRecoQQ);
  virtual Bool_t   passQualityCuts2015 (Int_t iRecoQQ);
  virtual Double_t deltaR (TLorentzVector* GenMuon, TLorentzVector* RecoMuon);
};
#endif

#ifdef makeTrigEff_cxx
oniaTree::oniaTree(string fileName) : fChain(0)
{
  TFile* f(0x0);
  if (fileName.find("LowPtJpsi")!=std::string::npos){
    f = TFile::Open("/eos/cms/store/group/phys_heavyions/dileptons/gbak/HLT_v18/JpsiMM_0_15/ntuple_HLT_v18_lowpT_Jpsi/181010_210455/Oniatree_all.root");
      treeLabel = "TreeFromGr_oct11_v18x2_LowPtJpsi";
    }
  else if (fileName.find("Z")!=std::string::npos){
    f = TFile::Open("/eos/cms/store/group/phys_heavyions/dileptons/gbak/HLT_v18/Zm10m10/ntuple_HLT_v18_Z/181011_102759/Oniatree_all.root");
      treeLabel = "TreeFromGr_oct11_v18x2_Z";
  }

  else if (fileName.find("HighPtJpsi")!=std::string::npos){
    f = TFile::Open("/eos/cms/store/group/phys_heavyions/dileptons/gbak/HLT_v18/JpsiMM_15_40/ntuple_HLT_v18_Jpsi_highpT_DB/181011_184453/Oniatree_all.root");
    treeLabel = "TreeFromGr_oct11_v18x2_HighPtJpsi";
  }
  else if (fileName.find("Upsilon")!=std::string::npos){
    f = TFile::Open("/eos/cms/store/group/phys_heavyions/dileptons/gbak/HLT_v18/Ups1SMM_0_30/ntuple_HLT_v18_Y_1S_DB/181011_185040/Oniatree_all.root");
    treeLabel = "TreeFromGr_oct11_v18x2_Upsi";
}
    cout<<"[INFO] reading tree file: "<<f->GetName()<<endl;
  TTree * tree (0x0);
  TTree* hltTree (0x0);
  tree = (TTree*) f->Get("hionia/myTree");
  if(!tree){
    cout <<"error in the onia tree"<<endl;
    return;}
  hltTree = (TTree*) f->Get("hltbitanalysis/HltTree");
  if(!hltTree){
    cout <<"error in the trigger tree"<<endl;
    return;}
  tree->AddFriend(hltTree);
  Init(tree);
}

oniaTree::~oniaTree()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t oniaTree::GetEntry(Long64_t entry)
{
  // Read contents of entry.                                                                                                                                                                              
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t oniaTree::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry                                                                                                                                                                
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void oniaTree::Init(TTree *tree)
{
  Reco_QQ_4mom = 0;
  Reco_QQ_mupl_4mom = 0;
  Reco_QQ_mumi_4mom = 0;
  Reco_QQ_vtx = 0;

  // Set branch addresses and branch pointers                                                                                                                                                          
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("eventNb", &eventNb, &b_eventNb);
  fChain->SetBranchAddress("runNb", &runNb, &b_runNb);
  fChain->SetBranchAddress("Centrality", &Centrality, &b_Centrality);
  fChain->SetBranchAddress("nTrig", &nTrig, &b_nTrig);
  fChain->SetBranchAddress("trigPrescale", trigPrescale, &b_trigPrescale);
  fChain->SetBranchAddress("HLTriggers", &HLTriggers, &b_HLTriggers);
  fChain->SetBranchAddress("Reco_QQ_size", &Reco_QQ_size, &b_Reco_QQ_size);
  fChain->SetBranchAddress("Reco_QQ_type", Reco_QQ_type, &b_Reco_QQ_type);
  fChain->SetBranchAddress("Reco_QQ_sign", Reco_QQ_sign, &b_Reco_QQ_sign);
  fChain->SetBranchAddress("Reco_QQ_4mom", &Reco_QQ_4mom, &b_Reco_QQ_4mom);
  fChain->SetBranchAddress("Reco_QQ_mupl_4mom", &Reco_QQ_mupl_4mom, &b_Reco_QQ_mupl_4mom);
  fChain->SetBranchAddress("Reco_QQ_mumi_4mom", &Reco_QQ_mumi_4mom, &b_Reco_QQ_mumi_4mom);
  fChain->SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig, &b_Reco_QQ_trig);
  fChain->SetBranchAddress("Reco_QQ_mupl_trig", Reco_QQ_mupl_trig, &b_Reco_QQ_mupl_trig);
  fChain->SetBranchAddress("Reco_QQ_mumi_trig", Reco_QQ_mumi_trig, &b_Reco_QQ_mumi_trig);
  fChain->SetBranchAddress("Reco_QQ_isCowboy", Reco_QQ_isCowboy, &b_Reco_QQ_isCowboy);
  fChain->SetBranchAddress("Reco_QQ_ctau", Reco_QQ_ctau, &b_Reco_QQ_ctau);
  fChain->SetBranchAddress("Reco_QQ_ctauErr", Reco_QQ_ctauErr, &b_Reco_QQ_ctauErr);
  fChain->SetBranchAddress("Reco_QQ_ctau3D", Reco_QQ_ctau3D, &b_Reco_QQ_ctau3D);
  fChain->SetBranchAddress("Reco_QQ_ctauErr3D", Reco_QQ_ctauErr3D, &b_Reco_QQ_ctauErr3D);
  fChain->SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb, &b_Reco_QQ_VtxProb);
  fChain->SetBranchAddress("Reco_QQ_dca", Reco_QQ_dca, &b_Reco_QQ_dca);
  fChain->SetBranchAddress("Reco_QQ_MassErr", Reco_QQ_MassErr, &b_Reco_QQ_MassErr);
  fChain->SetBranchAddress("Reco_QQ_vtx", &Reco_QQ_vtx, &b_Reco_QQ_vtx);
  fChain->SetBranchAddress("Reco_QQ_Ntrk", Reco_QQ_Ntrk, &b_Reco_QQ_Ntrk);
  fChain->SetBranchAddress("Reco_QQ_mupl_SelectionType", Reco_QQ_mupl_SelectionType, &b_Reco_QQ_mupl_SelectionType);
  fChain->SetBranchAddress("Reco_QQ_mumi_SelectionType", Reco_QQ_mumi_SelectionType, &b_Reco_QQ_mumi_SelectionType);
  fChain->SetBranchAddress("Reco_QQ_mupl_isGoodMuon", Reco_QQ_mupl_isGoodMuon, &b_Reco_QQ_mupl_isGoodMuon);
  fChain->SetBranchAddress("Reco_QQ_mumi_isGoodMuon", Reco_QQ_mumi_isGoodMuon, &b_Reco_QQ_mumi_isGoodMuon);
  fChain->SetBranchAddress("Reco_QQ_mupl_highPurity", Reco_QQ_mupl_highPurity, &b_Reco_QQ_mupl_highPurity);
  fChain->SetBranchAddress("Reco_QQ_mumi_highPurity", Reco_QQ_mumi_highPurity, &b_Reco_QQ_mumi_highPurity);
  fChain->SetBranchAddress("Reco_QQ_mupl_TrkMuArb", Reco_QQ_mupl_TrkMuArb, &b_Reco_QQ_mupl_TrkMuArb);
  fChain->SetBranchAddress("Reco_QQ_mumi_TrkMuArb", Reco_QQ_mumi_TrkMuArb, &b_Reco_QQ_mumi_TrkMuArb);
  fChain->SetBranchAddress("Reco_QQ_mupl_TMOneStaTight", Reco_QQ_mupl_TMOneStaTight, &b_Reco_QQ_mupl_TMOneStaTight);
  fChain->SetBranchAddress("Reco_QQ_mumi_TMOneStaTight", Reco_QQ_mumi_TMOneStaTight, &b_Reco_QQ_mumi_TMOneStaTight);
  fChain->SetBranchAddress("Reco_QQ_mupl_nPixValHits", Reco_QQ_mupl_nPixValHits, &b_Reco_QQ_mupl_nPixValHits);
  fChain->SetBranchAddress("Reco_QQ_mumi_nPixValHits", Reco_QQ_mumi_nPixValHits, &b_Reco_QQ_mumi_nPixValHits);
  fChain->SetBranchAddress("Reco_QQ_mupl_nMuValHits", Reco_QQ_mupl_nMuValHits, &b_Reco_QQ_mupl_nMuValHits);
  fChain->SetBranchAddress("Reco_QQ_mumi_nMuValHits", Reco_QQ_mumi_nMuValHits, &b_Reco_QQ_mumi_nMuValHits);
  fChain->SetBranchAddress("Reco_QQ_mupl_nTrkHits", Reco_QQ_mupl_nTrkHits, &b_Reco_QQ_mupl_nTrkHits);
  fChain->SetBranchAddress("Reco_QQ_mumi_nTrkHits", Reco_QQ_mumi_nTrkHits, &b_Reco_QQ_mumi_nTrkHits);
  fChain->SetBranchAddress("Reco_QQ_mupl_normChi2_inner", Reco_QQ_mupl_normChi2_inner, &b_Reco_QQ_mupl_normChi2_inner);
  fChain->SetBranchAddress("Reco_QQ_mumi_normChi2_inner", Reco_QQ_mumi_normChi2_inner, &b_Reco_QQ_mumi_normChi2_inner);
  fChain->SetBranchAddress("Reco_QQ_mupl_normChi2_global", Reco_QQ_mupl_normChi2_global, &b_Reco_QQ_mupl_normChi2_global);
  fChain->SetBranchAddress("Reco_QQ_mumi_normChi2_global", Reco_QQ_mumi_normChi2_global, &b_Reco_QQ_mumi_normChi2_global);
  fChain->SetBranchAddress("Reco_QQ_mupl_nPixWMea", Reco_QQ_mupl_nPixWMea, &b_Reco_QQ_mupl_nPixWMea);
  fChain->SetBranchAddress("Reco_QQ_mumi_nPixWMea", Reco_QQ_mumi_nPixWMea, &b_Reco_QQ_mumi_nPixWMea);
  fChain->SetBranchAddress("Reco_QQ_mupl_nTrkWMea", Reco_QQ_mupl_nTrkWMea, &b_Reco_QQ_mupl_nTrkWMea);
  fChain->SetBranchAddress("Reco_QQ_mumi_nTrkWMea", Reco_QQ_mumi_nTrkWMea, &b_Reco_QQ_mumi_nTrkWMea);
  fChain->SetBranchAddress("Reco_QQ_mupl_StationsMatched", Reco_QQ_mupl_StationsMatched, &b_Reco_QQ_mupl_StationsMatched);
  fChain->SetBranchAddress("Reco_QQ_mumi_StationsMatched", Reco_QQ_mumi_StationsMatched, &b_Reco_QQ_mumi_StationsMatched);
  fChain->SetBranchAddress("Reco_QQ_mupl_dxy", Reco_QQ_mupl_dxy, &b_Reco_QQ_mupl_dxy);
  fChain->SetBranchAddress("Reco_QQ_mumi_dxy", Reco_QQ_mumi_dxy, &b_Reco_QQ_mumi_dxy);
  fChain->SetBranchAddress("Reco_QQ_mupl_dxyErr", Reco_QQ_mupl_dxyErr, &b_Reco_QQ_mupl_dxyErr);
  fChain->SetBranchAddress("Reco_QQ_mumi_dxyErr", Reco_QQ_mumi_dxyErr, &b_Reco_QQ_mumi_dxyErr);
  fChain->SetBranchAddress("Reco_QQ_mupl_dz", Reco_QQ_mupl_dz, &b_Reco_QQ_mupl_dz);
  fChain->SetBranchAddress("Reco_QQ_mumi_dz", Reco_QQ_mumi_dz, &b_Reco_QQ_mumi_dz);
  fChain->SetBranchAddress("Reco_QQ_mupl_dzErr", Reco_QQ_mupl_dzErr, &b_Reco_QQ_mupl_dzErr);
  fChain->SetBranchAddress("Reco_QQ_mumi_dzErr", Reco_QQ_mumi_dzErr, &b_Reco_QQ_mumi_dzErr);
  fChain->SetBranchAddress("Reco_QQ_mupl_pt_inner", Reco_QQ_mupl_pt_inner, &b_Reco_QQ_mupl_pt_inner);
  fChain->SetBranchAddress("Reco_QQ_mumi_pt_inner", Reco_QQ_mumi_pt_inner, &b_Reco_QQ_mumi_pt_inner);
  fChain->SetBranchAddress("Reco_QQ_mupl_pt_global", Reco_QQ_mupl_pt_global, &b_Reco_QQ_mupl_pt_global);
  fChain->SetBranchAddress("Reco_QQ_mumi_pt_global", Reco_QQ_mumi_pt_global, &b_Reco_QQ_mumi_pt_global);
  fChain->SetBranchAddress("Reco_QQ_mupl_ptErr_inner", Reco_QQ_mupl_ptErr_inner, &b_Reco_QQ_mupl_ptErr_inner);
  fChain->SetBranchAddress("Reco_QQ_mumi_ptErr_inner", Reco_QQ_mumi_ptErr_inner, &b_Reco_QQ_mumi_ptErr_inner);
  fChain->SetBranchAddress("Reco_QQ_mupl_ptErr_global", Reco_QQ_mupl_ptErr_global, &b_Reco_QQ_mupl_ptErr_global);
  fChain->SetBranchAddress("Reco_QQ_mumi_ptErr_global", Reco_QQ_mumi_ptErr_global, &b_Reco_QQ_mumi_ptErr_global);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_v1", &HLT_HIL1DoubleMuOpen_v1, &b_HLT_HIL1DoubleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_v1_Prescl", &HLT_HIL1DoubleMuOpen_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_30_100_v1", &HLT_HIL1DoubleMuOpen_Centrality_30_100_v1, &b_HLT_HIL1DoubleMuOpen_Centrality_30_100_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_30_100_v1_Prescl", &HLT_HIL1DoubleMuOpen_Centrality_30_100_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_Centrality_30_100_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_40_100_v1", &HLT_HIL1DoubleMuOpen_Centrality_40_100_v1, &b_HLT_HIL1DoubleMuOpen_Centrality_40_100_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_40_100_v1_Prescl", &HLT_HIL1DoubleMuOpen_Centrality_40_100_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_Centrality_40_100_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_50_100_v1", &HLT_HIL1DoubleMuOpen_Centrality_50_100_v1, &b_HLT_HIL1DoubleMuOpen_Centrality_50_100_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_Centrality_50_100_v1_Prescl", &HLT_HIL1DoubleMuOpen_Centrality_50_100_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_Centrality_50_100_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_MAXdR2p0_v1", &HLT_HIL1DoubleMuOpen_MAXdR2p0_v1, &b_HLT_HIL1DoubleMuOpen_MAXdR2p0_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_MAXdR2p0_v1_Prescl", &HLT_HIL1DoubleMuOpen_MAXdR2p0_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_MAXdR2p0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1", &HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1, &b_HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl", &HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_MAXdR3p5_v1", &HLT_HIL1DoubleMuOpen_MAXdR3p5_v1, &b_HLT_HIL1DoubleMuOpen_MAXdR3p5_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_MAXdR3p5_v1_Prescl", &HLT_HIL1DoubleMuOpen_MAXdR3p5_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_MAXdR3p5_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_v1", &HLT_HIL1DoubleMuOpen_OS_v1, &b_HLT_HIL1DoubleMuOpen_OS_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_v1_Prescl", &HLT_HIL1DoubleMuOpen_OS_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_OS_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_SS_v1", &HLT_HIL1DoubleMuOpen_SS_v1, &b_HLT_HIL1DoubleMuOpen_SS_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_SS_v1_Prescl", &HLT_HIL1DoubleMuOpen_SS_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_SS_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_er1p6_v1", &HLT_HIL1DoubleMuOpen_er1p6_v1, &b_HLT_HIL1DoubleMuOpen_er1p6_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_er1p6_v1_Prescl", &HLT_HIL1DoubleMuOpen_er1p6_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_er1p6_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_er1p6_v1", &HLT_HIL1DoubleMuOpen_OS_er1p6_v1, &b_HLT_HIL1DoubleMuOpen_OS_er1p6_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMuOpen_OS_er1p6_v1_Prescl", &HLT_HIL1DoubleMuOpen_OS_er1p6_v1_Prescl, &b_HLT_HIL1DoubleMuOpen_OS_er1p6_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu0_v1", &HLT_HIL1DoubleMu0_v1, &b_HLT_HIL1DoubleMu0_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu0_v1_Prescl", &HLT_HIL1DoubleMu0_v1_Prescl, &b_HLT_HIL1DoubleMu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2_v1", &HLT_HIL1DoubleMu2_v1, &b_HLT_HIL1DoubleMu2_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2_v1_Prescl", &HLT_HIL1DoubleMu2_v1_Prescl, &b_HLT_HIL1DoubleMu2_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2p5_v1", &HLT_HIL1DoubleMu2p5_v1, &b_HLT_HIL1DoubleMu2p5_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2p5_v1_Prescl", &HLT_HIL1DoubleMu2p5_v1_Prescl, &b_HLT_HIL1DoubleMu2p5_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu3_v1", &HLT_HIL1DoubleMu3_v1, &b_HLT_HIL1DoubleMu3_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu3_v1_Prescl", &HLT_HIL1DoubleMu3_v1_Prescl, &b_HLT_HIL1DoubleMu3_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2_OS_v1", &HLT_HIL1DoubleMu2_OS_v1, &b_HLT_HIL1DoubleMu2_OS_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu2_OS_v1_Prescl", &HLT_HIL1DoubleMu2_OS_v1_Prescl, &b_HLT_HIL1DoubleMu2_OS_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu3_OS_v1", &HLT_HIL1DoubleMu3_OS_v1, &b_HLT_HIL1DoubleMu3_OS_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu3_OS_v1_Prescl", &HLT_HIL1DoubleMu3_OS_v1_Prescl, &b_HLT_HIL1DoubleMu3_OS_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu10_v1", &HLT_HIL1DoubleMu10_v1, &b_HLT_HIL1DoubleMu10_v1);
  fChain->SetBranchAddress("HLT_HIL1DoubleMu10_v1_Prescl", &HLT_HIL1DoubleMu10_v1_Prescl, &b_HLT_HIL1DoubleMu10_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL2_L1DoubleMu10_v1", &HLT_HIL2_L1DoubleMu10_v1, &b_HLT_HIL2_L1DoubleMu10_v1);
  fChain->SetBranchAddress("HLT_HIL2_L1DoubleMu10_v1_Prescl", &HLT_HIL2_L1DoubleMu10_v1_Prescl, &b_HLT_HIL2_L1DoubleMu10_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3_L1DoubleMu10_v1", &HLT_HIL3_L1DoubleMu10_v1, &b_HLT_HIL3_L1DoubleMu10_v1);
  fChain->SetBranchAddress("HLT_HIL3_L1DoubleMu10_v1_Prescl", &HLT_HIL3_L1DoubleMu10_v1_Prescl, &b_HLT_HIL3_L1DoubleMu10_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1", &HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1, &b_HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1);
  fChain->SetBranchAddress("HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl", &HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl, &b_HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL2DoubleMuOpen_v1", &HLT_HIL2DoubleMuOpen_v1, &b_HLT_HIL2DoubleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL2DoubleMuOpen_v1_Prescl", &HLT_HIL2DoubleMuOpen_v1_Prescl, &b_HLT_HIL2DoubleMuOpen_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_v1", &HLT_HIL3DoubleMuOpen_v1, &b_HLT_HIL3DoubleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_v1_Prescl", &HLT_HIL3DoubleMuOpen_v1_Prescl, &b_HLT_HIL3DoubleMuOpen_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_M60120_v1", &HLT_HIL3DoubleMuOpen_M60120_v1, &b_HLT_HIL3DoubleMuOpen_M60120_v1);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_M60120_v1_Prescl", &HLT_HIL3DoubleMuOpen_M60120_v1_Prescl, &b_HLT_HIL3DoubleMuOpen_M60120_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Jpsi_v1", &HLT_HIL3DoubleMuOpen_Jpsi_v1, &b_HLT_HIL3DoubleMuOpen_Jpsi_v1);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Jpsi_v1_Prescl", &HLT_HIL3DoubleMuOpen_Jpsi_v1_Prescl, &b_HLT_HIL3DoubleMuOpen_Jpsi_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Upsi_v1", &HLT_HIL3DoubleMuOpen_Upsi_v1, &b_HLT_HIL3DoubleMuOpen_Upsi_v1);
  fChain->SetBranchAddress("HLT_HIL3DoubleMuOpen_Upsi_v1_Prescl", &HLT_HIL3DoubleMuOpen_Upsi_v1_Prescl, &b_HLT_HIL3DoubleMuOpen_Upsi_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu0_L2Mu0_v1", &HLT_HIL3Mu0_L2Mu0_v1, &b_HLT_HIL3Mu0_L2Mu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu0_L2Mu0_v1_Prescl", &HLT_HIL3Mu0_L2Mu0_v1_Prescl, &b_HLT_HIL3Mu0_L2Mu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu0_L2Mu0_testignore_v1", &HLT_HIL3Mu0_L2Mu0_testignore_v1, &b_HLT_HIL3Mu0_L2Mu0_testignore_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu0_L2Mu0_testignore_v1_Prescl", &HLT_HIL3Mu0_L2Mu0_testignore_v1_Prescl, &b_HLT_HIL3Mu0_L2Mu0_testignore_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu2_L2Mu0_v1", &HLT_HIL3Mu2_L2Mu0_v1, &b_HLT_HIL3Mu2_L2Mu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu2_L2Mu0_v1_Prescl", &HLT_HIL3Mu2_L2Mu0_v1_Prescl, &b_HLT_HIL3Mu2_L2Mu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu2p5_L2Mu0_v1", &HLT_HIL3Mu2p5_L2Mu0_v1, &b_HLT_HIL3Mu2p5_L2Mu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu2p5_L2Mu0_v1_Prescl", &HLT_HIL3Mu2p5_L2Mu0_v1_Prescl, &b_HLT_HIL3Mu2p5_L2Mu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L2Mu0_v1", &HLT_HIL3Mu3_L2Mu0_v1, &b_HLT_HIL3Mu3_L2Mu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L2Mu0_v1_Prescl", &HLT_HIL3Mu3_L2Mu0_v1_Prescl, &b_HLT_HIL3Mu3_L2Mu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu2p5_L1DoubleMu0_v1", &HLT_HIL3Mu2p5_L1DoubleMu0_v1, &b_HLT_HIL3Mu2p5_L1DoubleMu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu2p5_L1DoubleMu0_v1_Prescl", &HLT_HIL3Mu2p5_L1DoubleMu0_v1_Prescl, &b_HLT_HIL3Mu2p5_L1DoubleMu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMuOpen_v1", &HLT_HIL3Mu3_L1DoubleMuOpen_v1, &b_HLT_HIL3Mu3_L1DoubleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMuOpen_v1_Prescl", &HLT_HIL3Mu3_L1DoubleMuOpen_v1_Prescl, &b_HLT_HIL3Mu3_L1DoubleMuOpen_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1", &HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1, &b_HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1_Prescl", &HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1_Prescl, &b_HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMu0_v1", &HLT_HIL3Mu3_L1DoubleMu0_v1, &b_HLT_HIL3Mu3_L1DoubleMu0_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1DoubleMu0_v1_Prescl", &HLT_HIL3Mu3_L1DoubleMu0_v1_Prescl, &b_HLT_HIL3Mu3_L1DoubleMu0_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1", &HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1, &b_HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1_Prescl", &HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1_Prescl, &b_HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1_Prescl);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1TripleMuOpen_v1", &HLT_HIL3Mu3_L1TripleMuOpen_v1, &b_HLT_HIL3Mu3_L1TripleMuOpen_v1);
  fChain->SetBranchAddress("HLT_HIL3Mu3_L1TripleMuOpen_v1_Prescl", &HLT_HIL3Mu3_L1TripleMuOpen_v1_Prescl, &b_HLT_HIL3Mu3_L1TripleMuOpen_v1_Prescl);


  if (fChain->GetBranch("Reco_QQ_4mom"))      { fChain->GetBranch("Reco_QQ_4mom")->SetAutoDelete(false);      }
  if (fChain->GetBranch("Reco_QQ_mupl_4mom")) { fChain->GetBranch("Reco_QQ_mupl_4mom")->SetAutoDelete(false); }
  if (fChain->GetBranch("Reco_QQ_mumi_4mom")) { fChain->GetBranch("Reco_QQ_mumi_4mom")->SetAutoDelete(false); }

  fChain->SetBranchStatus("*",0);
  if (fChain->GetBranch("runNb"))             { fChain->SetBranchStatus("runNb",1);             }
  if (fChain->GetBranch("Centrality"))        { fChain->SetBranchStatus("Centrality",1);        }
  if (fChain->GetBranch("Reco_QQ_size"))      { fChain->SetBranchStatus("Reco_QQ_size",1);      }
  if (fChain->GetBranch("Reco_QQ_sign"))      { fChain->SetBranchStatus("Reco_QQ_sign",1);      }
  if (fChain->GetBranch("Reco_QQ_4mom"))      { fChain->SetBranchStatus("Reco_QQ_4mom",1);      }
  if (fChain->GetBranch("Reco_QQ_mupl_4mom")) { fChain->SetBranchStatus("Reco_QQ_mupl_4mom",1); }
  if (fChain->GetBranch("Reco_QQ_mumi_4mom")) { fChain->SetBranchStatus("Reco_QQ_mumi_4mom",1); }
  if (fChain->GetBranch("Reco_QQ_ctau"))      { fChain->SetBranchStatus("Reco_QQ_ctau",1);      }
  if (fChain->GetBranch("HLTriggers")) fChain->SetBranchStatus("HLTriggers",1);
  if (fChain->GetBranch("Reco_QQ_trig")) fChain->SetBranchStatus("Reco_QQ_trig",1);
  if (fChain->GetBranch("Reco_QQ_VtxProb")) fChain->SetBranchStatus("Reco_QQ_VtxProb",1);
  if (fChain->GetBranch("Reco_QQ_mupl_SelectionType")) fChain->SetBranchStatus("Reco_QQ_mupl_SelectionType",1);
  if (fChain->GetBranch("Reco_QQ_mumi_SelectionType")) fChain->SetBranchStatus("Reco_QQ_mumi_SelectionType",1);
  if (fChain->GetBranch("Reco_QQ_mupl_isGoodMuon")) fChain->SetBranchStatus("Reco_QQ_mupl_isGoodMuon",1);
  if (fChain->GetBranch("Reco_QQ_mumi_isGoodMuon")) fChain->SetBranchStatus("Reco_QQ_mumi_isGoodMuon",1);
  if (fChain->GetBranch("Reco_QQ_mupl_nTrkWMea")) fChain->SetBranchStatus("Reco_QQ_mupl_nTrkWMea",1);
  if (fChain->GetBranch("Reco_QQ_mumi_nTrkWMea")) fChain->SetBranchStatus("Reco_QQ_mumi_nTrkWMea",1);
  if (fChain->GetBranch("Reco_QQ_mupl_nPixWMea")) fChain->SetBranchStatus("Reco_QQ_mupl_nPixWMea",1);
  if (fChain->GetBranch("Reco_QQ_mumi_nPixWMea")) fChain->SetBranchStatus("Reco_QQ_mumi_nPixWMea",1);
  if (fChain->GetBranch("Reco_QQ_mupl_dxy")) fChain->SetBranchStatus("Reco_QQ_mupl_dxy",1);
  if (fChain->GetBranch("Reco_QQ_mumi_dxy")) fChain->SetBranchStatus("Reco_QQ_mumi_dxy",1);
  if (fChain->GetBranch("Reco_QQ_mupl_dz")) fChain->SetBranchStatus("Reco_QQ_mupl_dz",1);
  if (fChain->GetBranch("Reco_QQ_mumi_dz")) fChain->SetBranchStatus("Reco_QQ_mumi_dz",1);
  if (fChain->GetBranch("Reco_QQ_mupl_nTrkHits")) fChain->SetBranchStatus("Reco_QQ_mupl_nTrkHits",1);
  if (fChain->GetBranch("Reco_QQ_mumi_nTrkHits")) fChain->SetBranchStatus("Reco_QQ_mumi_nTrkHits",1);
  if (fChain->GetBranch("Reco_QQ_mupl_normChi2_global")) fChain->SetBranchStatus("Reco_QQ_mupl_normChi2_global",1);
  if (fChain->GetBranch("Reco_QQ_mumi_normChi2_global")) fChain->SetBranchStatus("Reco_QQ_mumi_normChi2_global",1);
  if (fChain->GetBranch("Reco_QQ_mupl_normChi2_inner")) fChain->SetBranchStatus("Reco_QQ_mupl_normChi2_inner",1);
  if (fChain->GetBranch("Reco_QQ_mumi_normChi2_inner")) fChain->SetBranchStatus("Reco_QQ_mumi_normChi2_inner",1);
  if (fChain->GetBranch("Reco_QQ_mupl_TrkMuArb")) fChain->SetBranchStatus("Reco_QQ_mupl_TrkMuArb",1);
  if (fChain->GetBranch("Reco_QQ_mumi_TrkMuArb")) fChain->SetBranchStatus("Reco_QQ_mumi_TrkMuArb",1);

  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_Centrality_30_100_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_Centrality_30_100_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_Centrality_40_100_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_Centrality_40_100_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_Centrality_50_100_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_Centrality_50_100_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_MAXdR2p0_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_MAXdR2p0_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_OS_MAXdR2p0_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_MAXdR3p5_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_MAXdR3p5_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_OS_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_OS_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_SS_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_SS_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_er1p6_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_er1p6_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMuOpen_OS_er1p6_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMuOpen_OS_er1p6_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu0_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu0_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu2_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu2_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu2p5_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu2p5_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu3_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu3_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu2_OS_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu2_OS_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu3_OS_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu3_OS_v1",1);
  if (fChain->GetBranch("HLT_HIL1DoubleMu10_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu10_v1",1);
  if (fChain->GetBranch("HLT_HIL2_L1DoubleMu10_v1")) fChain->SetBranchStatus("HLT_HIL1DoubleMu10_v1",1);
  if (fChain->GetBranch("HLT_HIL3_L1DoubleMu10_v1")) fChain->SetBranchStatus("HLT_HIL3_L1DoubleMu10_v1",1);
  if (fChain->GetBranch("HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1")) fChain->SetBranchStatus("HLT_HIL2DoubleMu_L1DoubleMuOpen_OS_MAXdR2p0_v1",1);
  if (fChain->GetBranch("HLT_HIL2DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL2DoubleMuOpen_v1",1);
  if (fChain->GetBranch("HLT_HIL3DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL3DoubleMuOpen_v1",1);
  if (fChain->GetBranch("HLT_HIL3DoubleMuOpen_M60120_v1")) fChain->SetBranchStatus("HLT_HIL3DoubleMuOpen_M60120_v1",1);
  if (fChain->GetBranch("HLT_HIL3DoubleMuOpen_Jpsi_v1")) fChain->SetBranchStatus("HLT_HIL3DoubleMuOpen_Jpsi_v1",1);
  if (fChain->GetBranch("HLT_HIL3DoubleMuOpen_Upsi_v1")) fChain->SetBranchStatus("HLT_HIL3DoubleMuOpen_Upsi_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu0_L2Mu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu0_L2Mu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu0_L2Mu0_testignore_v1")) fChain->SetBranchStatus("HLT_HIL3Mu0_L2Mu0_testignore_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu2_L2Mu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu2_L2Mu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu2p5_L2Mu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu2p5_L2Mu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3_L2Mu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3_L2Mu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu2p5_L1DoubleMu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu2p5_L1DoubleMu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3_L1DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3_L1DoubleMuOpen_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3_L1DoubleMu0_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3_L1DoubleMuOpen_OS_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3_L1DoubleMu0_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3NHitQ10_L1DoubleMuOpen_v1",1);
  if (fChain->GetBranch("HLT_HIL3Mu3_L1TripleMuOpen_v1")) fChain->SetBranchStatus("HLT_HIL3Mu3_L1TripleMuOpen_v1",1);

  Notify();
}

Bool_t oniaTree::Notify()
{
  return kTRUE;
}

void oniaTree::Show(Long64_t entry)
{
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t oniaTree::Cut(Long64_t entry)
{
  return 1;
}

Bool_t oniaTree::isTriggerMatch (Int_t iRecoQQ, Int_t TriggerBit)
{
  Bool_t cond = true;
  cond = cond && ( (HLTriggers&((ULong64_t)pow(2, TriggerBit))) == ((ULong64_t)pow(2, TriggerBit)) );
  cond = cond && ( (Reco_QQ_trig[iRecoQQ]&((ULong64_t)pow(2, TriggerBit))) == ((ULong64_t)pow(2, TriggerBit)) );
  return cond;
};

Bool_t oniaTree::isGlobalMuonInAccept2015 (TLorentzVector* Muon)
{
  if (treeLabel.find("Upsi")!=std::string::npos) 
    return (fabs(Muon->Eta()) < 2.4 && Muon->Pt() >= 4);
    else if (treeLabel.find("Z")!=std::string::npos)
      return (fabs(Muon->Eta()) < 2.4 && Muon->Pt() >= 15);
    else 
      return (fabs(Muon->Eta()) < 2.4 &&
	      ((fabs(Muon->Eta()) < 1.2 && Muon->Pt() >= 3.5) ||
	       (1.2 <= fabs(Muon->Eta()) && fabs(Muon->Eta()) < 2.1 && Muon->Pt() >= 5.77-1.89*fabs(Muon->Eta())) ||
	       (2.1 <= fabs(Muon->Eta()) && Muon->Pt() >= 1.8)));
};

Bool_t oniaTree::areMuonsInAcceptance2015 (Int_t iRecoQQ)
{
  TLorentzVector *RecoQQmupl = (TLorentzVector*) Reco_QQ_mupl_4mom->At(iRecoQQ);
  TLorentzVector *RecoQQmumi = (TLorentzVector*) Reco_QQ_mumi_4mom->At(iRecoQQ);
  return ( isGlobalMuonInAccept2015(RecoQQmupl) && isGlobalMuonInAccept2015(RecoQQmumi) );
};

Bool_t oniaTree::passQualityCuts2015 (Int_t iRecoQQ)
{
  Bool_t cond = true;
  //cond = cond && (Reco_QQ_mumi_SelectionType[iRecoQQ]&((ULong64_t)pow(2, 1)));
  //cond = cond && (Reco_QQ_mumi_SelectionType[iRecoQQ]&((ULong64_t)pow(2, 3)));
  // cond = cond && (Reco_QQ_mumi_highPurity[iRecoQQ]);                                                                                                                                                 
  cond = cond && (Reco_QQ_mumi_isGoodMuon[iRecoQQ]==1);
  cond = cond && (Reco_QQ_mumi_nTrkWMea[iRecoQQ] > 5);
  cond = cond && (Reco_QQ_mumi_nPixWMea[iRecoQQ] > 0);
  cond = cond && (fabs(Reco_QQ_mumi_dxy[iRecoQQ]) < 0.3);
  cond = cond && (fabs(Reco_QQ_mumi_dz[iRecoQQ]) < 20.);

  //cond = cond && (Reco_QQ_mupl_SelectionType[iRecoQQ]&((ULong64_t)pow(2, 1)));
  //cond = cond && (Reco_QQ_mupl_SelectionType[iRecoQQ]&((ULong64_t)pow(2, 3)));
  // cond = cond && (Reco_QQ_mupl_highPurity[iRecoQQ]);                                                                                                                                                 
  cond = cond && (Reco_QQ_mupl_isGoodMuon[iRecoQQ]==1);
  cond = cond && (Reco_QQ_mupl_nTrkWMea[iRecoQQ] > 5);
  cond = cond && (Reco_QQ_mupl_nPixWMea[iRecoQQ] > 0);
  cond = cond && (fabs(Reco_QQ_mupl_dxy[iRecoQQ]) < 0.3);
  cond = cond && (fabs(Reco_QQ_mupl_dz[iRecoQQ]) < 20.);
  cond = cond && (Reco_QQ_VtxProb[iRecoQQ] > 0.01);

  return cond;
};

Double_t oniaTree::deltaR(TLorentzVector* GenMuon, TLorentzVector* RecoMuon)
{
  double dEta = RecoMuon->Eta() - GenMuon->Eta();
  double dPhi = TVector2::Phi_mpi_pi(RecoMuon->Phi() - GenMuon->Phi());
  return ((double) TMath::Sqrt( (dEta*dEta) + (dPhi*dPhi) ) );
};

#endif // #ifdef makeTrigEff_cxx 
