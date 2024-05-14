#include <iostream>
#include <TApplication.h>
#include <TLorentzVector.h>
#include "commonUtility.h"
#include "cutsAndBin.h"
#include "Style.h"
#include "TreeSetting.h"

using namespace std;
bool isInAcceptance(float pt, float abseta, bool isUp)
{	if(isUp){
             if (abseta >2.4) return false;
             if (abseta <2.4) return pt>3.5;
	}
	else{
        if (abseta > 2.4 ) return false; //JPsi cut
        if (abseta < 1.2 ) return pt >3.5;
        if (1.2<abseta && abseta < 2.1 ) return pt >= 5.47-1.89*abseta;
        return pt >1.5;
	}
}
bool dimuonrapidity(float pt, float absrap, bool isUp,bool isfwdard){
	if(isUp){
		if(absrap<2.4) return pt>0;
		return false;
	}
	else{
		if(!(isfwdard)){if(absrap<2.4) return pt>6.5;}
		else{if(absrap>1.6 && absrap<2.4) return pt>3;}
		return false;
	}
	
	
	
}
void getEfficiency_pure(const char* oniafilepath, const char* oniatype, const char* outputdir) {
  gROOT->SetBatch(1);
  gStyle->SetOptStat(0);
  gStyle -> SetEndErrorSize(2);
  gStyle -> SetLegendBorderSize(0);
  bool isUp = ((std::string)oniatype).find("Up") != std::string::npos;
  int kTrigSel = 4;
  float ptLow = 0.0;
  float ptHigh = 30.0;
  float yLow = 0.0;
  float yHigh = 2.4;

  float muPtCut = 3.5;
  float muEtaCut = 2.4;
  float dimuRapCut = 2.4;

  float massLow = 8.8;
  float massHigh = 10.2;

 // if(state==2){massLow = 9.3; massHigh = 10.7;}
  //else if(state==3){massLow = 9.6; massHigh = 11;}

  double min = 0;
  double max = ptHigh;

  int nPtBin_;
  double *ptBin_;
  
 // bool SR=true;

  //input files
  TString inputMC;
//  if(state==1){
//    inputMC =  "/home/jun502s/TriggerEfficiency/dataset/Oniatree_JPsi_CMSSW_12_2_0_pre3_20220223.root";
//    nPtBin_ = nPtBins1S; ptBin_ =ptbin1S;
//  }  
//  else if(state==2){
//    inputMC =  "/home/jun502s/TriggerEfficiency/dataset/Oniatree_Upsilon_CMSSW_12_2_0_pre3_20220223.root";
//    nPtBin_ = nPtBins1S; ptBin_ =ptbin1S;
// //   if(SR){nPtBin_ = nPtBins3S; ptBin_ =ptbin3S;}
//  }
//  else if(state==3){
//   // inputMC =  "/home/jun502s/TriggerEfficiency/dataset/Oniatree_Jpsi_Embedded_CMSSW_12_2_0_pre3_20220223.root";
//     inputMC =	"/home/jun502s/TriggerEfficiency/dataset/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root";
//
//    nPtBin_ = nPtBins1S; ptBin_ =ptbin1S;
//  }
//  else if(state==4){
//    inputMC =  "/home/jun502s/TriggerEfficiency/dataset/Oniatree_Upsilon_Embedded_CMSSW_12_2_0_pre3_20220223.root";
//    nPtBin_ = nPtBins1S; ptBin_ =ptbin1S;
//  }
  inputMC = (TString)oniafilepath;
  TChain* mytree = new TChain("hionia/myTree"); 
  mytree->Add(inputMC.Data());
  
  //SetBranchAddress
  SetTree settree_;
  settree_.TreeSetting(mytree,1);

  TH1D* hpt_gen_pt = new TH1D("hpt_gen_pt","hpt_gen_pt",30,0,30);
  TH1D* hpt_gen_y = new TH1D("hpt_gen_y","hpt_gen_y",30,-2.4,2.4);
  TH1D* hpt_gen_fwd_pt = new TH1D("hpt_gen_fwd_pt","hpt_gen_fwd_pt",30,0,30);
  TH1D* hpt_reco_pt = new TH1D("hpt_reco_pt","hpt_reco_pt",30,0,30);
  TH1D* hpt_reco_y = new TH1D("hpt_reco_y","hpt_reco_y",30,-2.4,2.4);
  TH1D* hpt_reco_fwd_pt = new TH1D("hpt_reco_fwd_pt","hpt_reco_fwd_pt",30,0,30);


  hpt_gen_y->Sumw2();
  hpt_reco_y->Sumw2();
  hpt_gen_y->GetXaxis()->SetTitle("y");
  hpt_reco_y->GetXaxis()->SetTitle("y");
  hpt_gen_pt->Sumw2();
  hpt_reco_pt->Sumw2();
  hpt_gen_pt->GetXaxis()->SetTitle("pT");
  hpt_reco_pt->GetXaxis()->SetTitle("pT");
  hpt_gen_fwd_pt->Sumw2();
  hpt_reco_fwd_pt->Sumw2();
  hpt_gen_fwd_pt->GetXaxis()->SetTitle("pT");
  hpt_reco_fwd_pt->GetXaxis()->SetTitle("pT");
  hpt_reco_fwd_pt->SetTitle("Efficiency vs pT in foward endcap");
  hpt_reco_pt->SetTitle("Efficiency vs pT");
  hpt_reco_y ->SetTitle("Efficiency vs y");
  
  TLorentzVector* JP_Gen= new TLorentzVector;
  TLorentzVector* mupl_Gen = new TLorentzVector;
  TLorentzVector* mumi_Gen = new TLorentzVector;

  TLorentzVector* JP_Reco = new TLorentzVector;
  TLorentzVector* mupl_Reco = new TLorentzVector;
  TLorentzVector* mumi_Reco = new TLorentzVector;

  double weight = 1;
  double tnp_weight = 1;
  double pt_weight = 1;
  
  double ptr, pt1r, pt2r, eta1r, eta2r, yr ,etar;
  double ptg, pt1g, pt2g, eta1g, eta2g, yg ,etag;

  const int nevt = mytree->GetEntries();
  cout << "Total Events : " << nevt << endl;
  for(int iev=0; iev<nevt ; ++iev)
  {
    if(iev%1000==0) cout << ">>>>> EVENT " << iev << " / " << mytree->GetEntries() <<  " ("<<(int)(100.*iev/mytree->GetEntries()) << "%)" << endl;

    mytree->GetEntry(iev);
    weight = Gen_weight;
    
    for(int igen = 0; igen<Gen_QQ_size; igen++){
      JP_Gen = (TLorentzVector*) Gen_QQ_4mom->At(igen);
      mupl_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mupl_idx[igen]);
      mumi_Gen = (TLorentzVector*) Gen_mu_4mom->At(Gen_QQ_mumi_idx[igen]);

      ptg = JP_Gen->Pt();
      yg = JP_Gen->Rapidity();
      pt1g = mupl_Gen->Pt();
      pt2g = mumi_Gen->Pt();
      eta1g = mupl_Gen->Eta();
      eta2g = mumi_Gen->Eta();

      if(fabs(yg)>dimuRapCut || ptg>ptHigh) continue;
      if(!(isInAcceptance(pt1g,fabs(eta1g),isUp)) || !(isInAcceptance(pt2g,fabs(eta2g),isUp))) continue;
      if(Gen_mu_charge[Gen_QQ_mupl_idx[igen]]*Gen_mu_charge[Gen_QQ_mumi_idx[igen]]>0) continue;
      if((dimuonrapidity(ptg,fabs(yg),isUp,1))){ hpt_gen_fwd_pt -> Fill(ptg,weight);}
      if((dimuonrapidity(ptg,fabs(yg),isUp,0))) hpt_gen_pt -> Fill(ptg,weight);
      if(isUp){
	if(ptg>0) hpt_gen_y -> Fill(yg,weight);
	}
      else{if(ptg>6.5) hpt_gen_y -> Fill(yg,weight);
	}

//      if(fabs(etag1g)>muEtaCut || fabs(etag2g)>muEtaCut) continue;
//      if(pt1g < muPtCut || pt2g < muPtCut) continue;

	}

    weight = Gen_weight;
    for (Int_t irqq=0; irqq<Reco_QQ_size; ++irqq){
      JP_Reco = (TLorentzVector*) Reco_QQ_4mom->At(irqq);
      mupl_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mupl_idx[irqq]);
      mumi_Reco = (TLorentzVector*) Reco_mu_4mom->At(Reco_QQ_mumi_idx[irqq]);
      
      bool HLTFilterPass=false;
      if( (Reco_QQ_trig[irqq]&((ULong64_t)pow(2, kTrigSel))) == ((ULong64_t)pow(2, kTrigSel)) ) HLTFilterPass=true;

      if(Reco_mu_whichGen[Reco_QQ_mupl_idx[irqq]] == -1) continue;
      if(Reco_mu_whichGen[Reco_QQ_mupl_idx[irqq]] == -1) continue;
      if(Reco_QQ_whichGen[irqq] == -1) continue;
      if(Reco_QQ_sign[irqq]!=0) continue;

      if( Reco_QQ_VtxProb[irqq]  < 0.01 ) continue;
      
      ptr     = JP_Reco->Pt();
      yr      = JP_Reco->Rapidity();
      pt1r  = mupl_Reco->Pt();
      pt2r  = mumi_Reco->Pt();
      eta1r = mupl_Reco->Eta();
      eta2r = mumi_Reco->Eta();

      if(fabs(yr)>dimuRapCut || ptr>ptHigh) continue;
      if(!(isInAcceptance(pt1r,fabs(eta1r),isUp)) || !(isInAcceptance(pt2r,fabs(eta2r),isUp))) continue;
      if(!settree_.SoftMuIdCut(irqq)) continue;
      //if(!(dimuonrapidity(ptr,fabs(yr),isUp))) continue;
      if((dimuonrapidity(ptr,fabs(yr),isUp,1))) hpt_reco_fwd_pt -> Fill(ptr,weight);
      if((dimuonrapidity(ptr,fabs(yr),isUp,0))) hpt_reco_pt -> Fill(ptr,weight);
      if(isUp){
	if(ptr>0) hpt_reco_y -> Fill(yr,weight);
	}
      else{if(ptr>6.5) hpt_reco_y -> Fill(yr,weight);
	}
  //    if(fabs(etar1r)>muEtaCut || fabs(etar2r)>muEtaCut) continue;
  //    if(pt1r < muPtCut || pt2r < muPtCut) continue;
    }
  }


  //Divide
  TH1D* hpt_eff;
  TH1D* hpt_eff_y;
  TH1D* hpt_eff_pt;
  TH1D* hpt_eff_fwd_pt;
  
  hpt_eff_y = (TH1D*)hpt_reco_y->Clone("hpt_eff_y");
  hpt_eff_pt = (TH1D*)hpt_reco_pt->Clone("hpt_eff_pt");
  hpt_eff_fwd_pt = (TH1D*)hpt_reco_fwd_pt->Clone("hpt_eff_fwd_pt");
 // hpt_eff_Trig = (TH1D*)hpt_reco->Clone("hpt_eff_Trig");

  hpt_eff_pt->Divide(hpt_eff_pt, hpt_gen_pt, 1, 1, "B");
//  hpt_eff_int->Divide(hpt_eff_int, hpt_gen_int, 1, 1, "B");
  hpt_eff_y->Divide(hpt_eff_y, hpt_gen_y, 1, 1, "B");
  hpt_eff_fwd_pt->Divide(hpt_eff_fwd_pt,hpt_gen_fwd_pt, 1, 1, "B");
  //hpt_eff_Trig->Divide(hpt_eff_Trig, hpt_reco_NoTrig, 1, 1, "B");

//  TCanvas * cpt_eff = new TCanvas("cpt_eff","cpt_eff",0,400,400,400);
//  cpt_eff->cd();
//  hpt_eff->Draw();
  TLegend *legend1 = new TLegend(0.6,0.2,0.85,0.5);
  TLegend *legend2 = new TLegend(0.6,0.2,0.85,0.5);
  legend1 -> AddEntry(hpt_eff_pt,Form("%s #left|y#right|<2.4",oniatype));
  if(!(isUp))legend1 -> AddEntry(hpt_eff_fwd_pt,Form("%s 1.6<#left|y#right|<2.4",oniatype));
  legend2 -> AddEntry(hpt_eff_y,Form("pT>6.5 %s",oniatype));
  legend1 -> SetTextSize(0.035);
  legend2 -> SetTextSize(0.035);
  
/*  TLatex *t1;
  TLatex *t2;
  TLatex *t3;
  if(!(isUp)){
  	t1 = new TLatex(0.5,0.4,Form("%s |y|<2.4",type.at(state-1).c_str()));
  	t2 = new TLatex(0.5,0.3,Form("%s 1.6<|y|<2.4",type.at(state-1).c_str()));
  	t3 = new TLatex(0.5,0.85,Form("%s pT>6.5",type.at(state-1).c_str()));
	}
  else{ 
  	t1 = new TLatex(0.5,0.4,Form("%s |y|<2.4",type.at(state-1).c_str()));
  	t2 = new TLatex(0.5,0.3,"");
  	t3 = new TLatex(0.5,0.85,Form("%s pT>0",type.at(state-1).c_str()));
      }
  t1->SetTextColor(kRed);
  t1->SetTextSize(0.04);
  t1->SetTextAlign(22);
  t1 -> SetNDC();
  t2->SetTextColor(kGreen);
  t2->SetTextSize(0.04);
  t2->SetTextAlign(22);
  t2 -> SetNDC();
  t3->SetTextColor(kBlack);
  t3->SetTextSize(0.04);
  t3->SetTextAlign(22);
  t3 -> SetNDC(); */
  hpt_eff_pt -> SetLineColor(kRed);
  hpt_eff_fwd_pt -> SetLineColor(kGreen);
  hpt_eff_pt ->GetYaxis()-> SetRangeUser(0,1);
  hpt_eff_fwd_pt -> GetYaxis()-> SetRangeUser(0,1);
  hpt_eff_y -> SetLineColor(kBlack);
  hpt_eff_y -> GetYaxis()-> SetRangeUser(0,1);
  hpt_eff_pt -> GetYaxis() -> SetTitle("efficiency");
  hpt_eff_y -> GetYaxis() -> SetTitle("efficiency");
  hpt_eff_fwd_pt -> GetYaxis() -> SetTitle("efficiency");
  TCanvas * cpt_eff_pt = new TCanvas("cpt_eff_pt","cpt_eff_pt",0,0,1920,1080);
  cpt_eff_pt->cd();
  hpt_eff_pt->Draw("E1PL");
  if(!(isUp))hpt_eff_fwd_pt -> Draw("E1PLsame");
  legend1 -> Draw("same");
//  t1 -> Draw();
//  t2 -> Draw();
  TCanvas *cvs_eff_y = new TCanvas("cpt_eff_y","cpt_eff_y",1920,0,1920,1080);
  cvs_eff_y->cd();
  hpt_eff_y -> Draw("E1PL");
  legend2 -> Draw("same");
 // t3 -> Draw("same");  
  cvs_eff_y -> SaveAs(Form("%s/%s_efficiency_vs_rapidity.png",outputdir,oniatype));
  cpt_eff_pt -> SaveAs(Form("%s/%s_efficiency_vs_pt.png",outputdir,oniatype));

  //TString outFileName = Form("mc_eff_vs_pt_TnP%d_PtW%d_OfficialMC_Y%dS_muPtCut%.1f",isTnP,isPtWeight,state,muPtCut);
 // TString outFileName = Form("mc_eff_vs_pt_%s_muPtCut%.1f",type.at(state-1).c_str(),muPtCut);
  //if(state==2&&SR==true) outFileName = outFileName + "_SR";
//  TFile* outFile = new TFile(Form("%s.root",outFileName.Data()),"RECREATE");
 // hpt_eff->Write();
 // hpt_eff_NoTrig->Write();
//  hpt_eff_Trig->Write();
 // hpt_reco_NoTrig->Write();
 // hpt_reco->Write();
//  hpt_gen_int->Write();
//  hpt_reco_int->Write();
//  hpt_eff_int->Write();
 // hpt_gen->Write();
 // outFile->Close();

}
int main(int argc, char** argv){
	
	getEfficiency_pure(argv[1],argv[2],argv[3]);
	return 0;
}
//void StandaloneApplication(int argc, char** argv){
//	
//	getEfficiency_pure(argv[1],argv[2],argv[3]);
//}
//int main(int argc, char** argv) {
//   TApplication app("ROOT Application", &argc, argv);
//   StandaloneApplication(app.Argc(), app.Argv());
//   app.Run();
//   return 0;
//}
//
