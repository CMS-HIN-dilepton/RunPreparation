//Headers{{{
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "TAxis.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TNtuple.h"
#include "TRandom.h"
#include "TROOT.h"
#include "TString.h"
#include "TTree.h"
#include "TDirectoryFile.h"

#include "tdrstyle.C"
#include "CMS_lumi.C"
//}}}

void OniaTreeKinematicsGraphs(){


	// ******** Start measuring time ******** //
  	clock_t start, end, cpu_time;
  	start = clock();

  	// ******** Set a style for graphs (need a header file, if you don't have the file, comment it out) ******** //
  	setTDRStyle();


  	// ******** Read Onia tree ******** //
  	// (Option 1. Read local onia tree file)
  	TFile *infile = TFile::Open("/media/ahram/Local Disk/Linux/Research/OniaTree_JpsiMass_MBPD_merged_210315_ver1.root", "read");
 	TDirectoryFile *hionia = (TDirectoryFile*)infile->Get("hionia");
 	TChain *myTree = (TChain*)hionia->Get("myTree");


  	// (Option 2. Read remote files through lxplus)
  	// TFile *infile = TFile::Open("/eos/cms/store/group/phys_heavyions/jaebeom/OniaTree_JpsiMass_MBPD_merged_210315_ver1.root", "read");
 	// TDirectoryFile *hionia = (TDirectoryFile*)infile->Get("hionia");
 	// TChain *myTree = (TChain*)hionia->Get("myTree");


 	// (Reference codes)
  	// TString inputRD1 = "root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/Data2018/PbPb502TeV/TTrees/ReReco/AOD/DoubleMuon/ReReco_Oniatree_addvn_part1.root";
  	// TString inputRD2 = "root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/Data2018/PbPb502TeV/TTrees/ReReco/AOD/DoubleMuon/ReReco_Oniatree_addvn_part2.root";
  	// TString inputRD3 = "root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/Data2018/PbPb502TeV/TTrees/ReReco/AOD/DoubleMuon/ReReco_Oniatree_addvn_part3.root";
  	// TString inputRD4 = "root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/Data2018/PbPb502TeV/TTrees/ReReco/AOD/DoubleMuon/ReReco_Oniatree_addvn_part4.root";
  	// TString inputRD5 = "root://eoscms//eos/cms/store/group/phys_heavyions/dileptons/Data2018/PbPb502TeV/TTrees/ReReco/AOD/DoubleMuon/ReReco_Oniatree_addvn_part5.root";
	// TChain *myTree = new TChain("myTree"); // name of the tree
	// myTree -> Add(inputRD1.Data());
	// myTree -> Add(inputRD2.Data());
	// myTree -> Add(inputRD3.Data());
	// myTree -> Add(inputRD4.Data());
	// myTree -> Add(inputRD5.Data());
	// TChain *tree = new TChain("tree");
	// tree -> Add(inputRD1.Data());
	// tree -> Add(inputRD2.Data());
	// tree -> Add(inputRD3.Data());
	// tree -> Add(inputRD4.Data());
	// tree -> Add(inputRD5.Data());

	// myTree -> AddFriend(tree);


  	// ******** Define histograms ******** //
	TH1F *CenHist = new TH1F("CenHist", "Centrality;Centrality;", 200, 0, 200);
	TH1F *muplpTHist = new TH1F("muplpTHist", "Single #mu^{+} p_{T};p_{T} (GeV);", 200, 0, 50.);
	TH1F *mumipTHist = new TH1F("mumipTHist", "Single #mu^{-} p_{T};p_{T} (GeV);", 200, 0, 50.);
	TH1F *QQpTHist = new TH1F("QQpTHist", "Double muon p_{T};p_{T} (GeV);", 200, 0, 50.);
	TH1F *muplEtaHist = new TH1F("muplEtaHist", "Single #mu^{+} sudo rapidity (#eta);#eta;", 100, -5., 5.);
	TH1F *mumiEtaHist = new TH1F("mumiEtaHist", "Single #mu^{-} sudo rapidity (#eta);#eta;", 100, -5., 5.);
	TH1F *QQEtaHist = new TH1F("QQEtaHist", "Double muon sudorapidity (#eta);#eta;", 100, -5., 5.);
	
	// (Bit1: Double muon inclusive -> Index=0)
	// (Bit13: J/psi region -> Index=1)
	// (Bit14: Upsilon + high masses -> Index=2)
	const Int_t NTriggers = 3;
	const Int_t Bits[NTriggers] = {1, 13, 14};
	const int SelectBitsIndex = 1; // (Selected J/psi region)

	// ******** Define variables in Onia tree ******** //
    Int_t Centrality;
	ULong64_t HLTriggers;
	ULong64_t Reco_QQ_trig[1000];
	Short_t Reco_QQ_size;
	Short_t Reco_QQ_type[1000];
	Short_t Reco_QQ_sign[1000];	

	TClonesArray *CloneArr_QQ;
    Short_t Reco_QQ_mupl_idx[1000];
    Short_t Reco_QQ_mumi_idx[1000];
	TClonesArray *CloneArr_mu;
  
  	// (id variables : information from the inner track muons)
  	float_t Reco_QQ_VtxProb[1000];
    Int_t Reco_mu_nPixWMea[1000];
    Int_t Reco_mu_nTrkWMea[1000];
    float_t Reco_mu_dxy[1000];
    float_t Reco_mu_dz[1000];

	CloneArr_QQ = 0;
	CloneArr_mu = 0;

	myTree -> SetBranchAddress("Centrality", &Centrality);
	myTree -> SetBranchAddress("HLTriggers", &HLTriggers);
	myTree -> SetBranchAddress("Reco_QQ_trig", Reco_QQ_trig);
	myTree -> SetBranchAddress("Reco_QQ_size", &Reco_QQ_size);
	myTree -> SetBranchAddress("Reco_QQ_type", Reco_QQ_type);
	myTree -> SetBranchAddress("Reco_QQ_sign", &Reco_QQ_sign);

	myTree -> SetBranchAddress("Reco_QQ_4mom", &CloneArr_QQ);
	myTree -> SetBranchAddress("Reco_QQ_mupl_idx", Reco_QQ_mupl_idx);
	myTree -> SetBranchAddress("Reco_QQ_mumi_idx", Reco_QQ_mumi_idx);
	myTree -> SetBranchAddress("Reco_mu_4mom", &CloneArr_mu);

	myTree -> SetBranchAddress("Reco_QQ_VtxProb", Reco_QQ_VtxProb);
	myTree -> SetBranchAddress("Reco_mu_nPixWMea", Reco_mu_nPixWMea);
	myTree -> SetBranchAddress("Reco_mu_nTrkWMea", Reco_mu_nTrkWMea);
	myTree -> SetBranchAddress("Reco_mu_dxy", Reco_mu_dxy);
	myTree -> SetBranchAddress("Reco_mu_dz", Reco_mu_dz);

	
	// ******** Print out the total number of entries ******** //	
	double totEntries = myTree->GetEntries();
	cout << "Total Entries: " << totEntries << endl;


    // ******** Load each value in myTree and fill histograms ******** //	
	for(int i=0; i<totEntries; i++){

		// ******** Show how much % of the process has been completed ******** //	
		if(i%100000==0){
			cout << "********* " << (double)(100.*i/(totEntries)) << "% completed" << " ********" << endl;
		}

		// ******** Load the values ******** //
		myTree -> GetEntry(i);

		for(int j=0; j<Reco_QQ_size; j++){

			TLorentzVector *Reco_mupl_4mom = (TLorentzVector*) CloneArr_mu->At(Reco_QQ_mupl_idx[j]);
			TLorentzVector *Reco_mumi_4mom = (TLorentzVector*) CloneArr_mu->At(Reco_QQ_mumi_idx[j]);
			TLorentzVector *Reco_QQ_4mom = (TLorentzVector*) CloneArr_QQ->At(j);

			// ******** Apply cuts ******** //
			if( ((HLTriggers&(ULong64_t)(1<<(Bits[SelectBitsIndex]-1)))==(ULong64_t)(1<<(Bits[SelectBitsIndex]-1)))
			 && ((Reco_QQ_trig[j]&(ULong64_t)(1<<(Bits[SelectBitsIndex]-1)))==(ULong64_t)(1<<(Bits[SelectBitsIndex]-1)))

			 // (Hybrid-Soft acceptance cut, https://twiki.cern.ch/twiki/bin/view/CMS/DileptonMuonSelection#PbPb_2018_and_2017_pp_5_02_TeV)
			 &&((abs(Reco_QQ_4mom->Eta())>=0.0 && abs(Reco_QQ_4mom->Eta())<0.3  && Reco_QQ_4mom->Pt()>3.4)||
			 	(abs(Reco_QQ_4mom->Eta())>=0.3 && abs(Reco_QQ_4mom->Eta())<1.1  && Reco_QQ_4mom->Pt()>3.3)||
			 	(abs(Reco_QQ_4mom->Eta())>=1.1 && abs(Reco_QQ_4mom->Eta())<1.4  && Reco_QQ_4mom->Pt()>7.7-4.0*abs(Reco_QQ_4mom->Eta()))||
			 	(abs(Reco_QQ_4mom->Eta())>=1.4 && abs(Reco_QQ_4mom->Eta())<1.55 && Reco_QQ_4mom->Pt()>2.1)||
			 	(abs(Reco_QQ_4mom->Eta())>=1.55 && abs(Reco_QQ_4mom->Eta())<2.2 && Reco_QQ_4mom->Pt()>4.25-1.39*abs(Reco_QQ_4mom->Eta()))||
			 	(abs(Reco_QQ_4mom->Eta())>=2.2 && abs(Reco_QQ_4mom->Eta())<=2.4 && Reco_QQ_4mom->Pt()>1.2))

			 // (quality cut)
 			 /*&& (Reco_QQ_VtxProb[l]>=0.01) 				// (reconstructed dimuon vertex probabiliy > 1%)
			 && (Reco_mu_nTrkWMea[Reco_QQ_mupl_idx[l]]>5)   // (at least 6 hits in the silicon strip layers)
			 && (Reco_mu_nTrkWMea[Reco_QQ_mumi_idx[l]]>5)
			 && (Reco_mu_nPixWMea[Reco_QQ_mupl_idx[l]]>0)   // (at least 1 hit in the pixel detectors)
			 && (Reco_mu_nPixWMea[Reco_QQ_mumi_idx[l]]>0)
			 && (abs(Reco_mu_dxy[Reco_QQ_mupl_idx[l]])<0.3) // (distance btw the track and the event vertex_xy <0.3cm)
			 && (abs(Reco_mu_dxy[Reco_QQ_mumi_idx[l]])<0.3)
 			 && (abs(Reco_mu_dz[Reco_QQ_mupl_idx[l]])<20.)  // (distance btw the track and the event vertex_z <20cm)
			 && (abs(Reco_mu_dz[Reco_QQ_mumi_idx[l]])<20.)*/

			 ){

				// ******** Fill histograms ******** //
				CenHist -> Fill(Centrality);
				QQpTHist -> Fill(Reco_QQ_4mom->Pt());
				muplpTHist -> Fill(Reco_mupl_4mom->Pt());
				mumipTHist -> Fill(Reco_mumi_4mom->Pt());
				QQEtaHist -> Fill(Reco_QQ_4mom->Eta());
				muplEtaHist -> Fill(Reco_mupl_4mom->Eta());
				mumiEtaHist -> Fill(Reco_mumi_4mom->Eta());
			}

			else continue;
		}
	}

	// ******** Draw and save histograms ******** //
	TCanvas *c1 = new TCanvas("c1", "c1", 1000, 1000);
	CenHist -> Draw();
	c1 -> SaveAs("1_Centrality_AcceptanceCut.gif");
	TCanvas *c2 = new TCanvas("c2", "c2", 1000, 1000);
	QQpTHist -> Draw();
	c2 -> SaveAs("1_QQpT_AcceptanceCut.gif");
	TCanvas *c3 = new TCanvas("c3", "c3", 1000, 1000);
	muplpTHist -> Draw();
	c3 -> SaveAs("1_muplpT_AcceptanceCut.gif");
	TCanvas *c4 = new TCanvas("c4", "c4", 1000, 1000);
	mumipTHist -> Draw();
	c4 -> SaveAs("1_mumipT_AcceptanceCut.gif");
	TCanvas *c5 = new TCanvas("c5", "c5", 1000, 1000);
	QQEtaHist -> Draw();
	c5 -> SaveAs("1_QQeta_AcceptanceCut.gif");
	TCanvas *c6 = new TCanvas("c6", "c6", 1000, 1000);
	muplEtaHist -> Draw();
	c6 -> SaveAs("1_mupleta_AcceptanceCut.gif");
	TCanvas *c7 = new TCanvas("c7", "c7", 1000, 1000);
	mumiEtaHist -> Draw();			
	c7 -> SaveAs("1_mumieta_AcceptanceCut.gif");	


	// ******** End measuring time ******** //
  	end = clock();
	cpu_time = (double)(end - start)/CLOCKS_PER_SEC;
	cout << "Time elapsed: " << cpu_time/60. << "minutes" << endl;

	return;

}