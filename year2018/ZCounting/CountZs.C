#include <iostream>
#include <fstream>

using namespace std;
//###void countZs(const char* filename, int run1=1, int run2=0, float lumi=0, bool add=false) {
//###void countZs(const char* filename="DQM_V0001_R000325112__HIDoubleMuon__Tier0_REPLAY_vocms015-PromptReco-v216__DQMIO.root", int run1=325112, int run2=325112, float lumi=1000, bool add=false) {

void CountZs(int run1=326381, int run2=326452, bool add=true, TString listn="runlist_2018PbPb_20181109") {

		  ifstream flist;
		  TFile *file;
		  TString filename;
		  int run;
		  float lumi;	
		  float lumiadd=0.0;
			flist.open(listn.Data());

		  TCanvas *c1 = new TCanvas("c1","",800,800);
		  c1->SetTopMargin(0.07);
		  c1->SetBottomMargin(0.12);
		  c1->SetLeftMargin(0.14);
		  c1->SetRightMargin(0.05);
		  ifstream fini;
		  TString filenameini;
		  int runini;
		  float lumiini;	
		  fini.open(listn.Data());	
		  fini >> runini >> filenameini >> lumiini;
			
		  TFile* finini = new TFile(Form("DQMFiles/%s",filenameini.Data()));
		  TH1F *htot = (TH1F*)finini->Get(Form("DQMData/Run %i/Muons/Run summary/diMuonHistograms/GlbGlbMuon_HM",runini));
////////

//		  while (!flist.eof()) { //needed }
		  while (flist) { //needed }


		  flist >> run >> filename >> lumi;
		  if (run==-999) break;
		  std::cout << "Run : " << run << " , " << filename << " , Lumi : " << lumi << " nb^{-1}" << std::endl;
		  if (run<run1 || run>run2) continue;
		  file = new TFile(Form("DQMFiles/%s",filename.Data()));
		  if (!file) continue;

		  c1->cd();

		  gStyle->SetOptTitle(0);
		  gStyle->SetOptStat(0);

		  //###TH1F *h = (TH1F*) file->Get("Run summary/DiMuonHistograms/GlbGlbMuon_HM");
		  TH1F *h = (TH1F*) file->Get(Form("DQMData/Run %i/Muons/Run summary/diMuonHistograms/GlbGlbMuon_HM",run));
		  //###   h->GetYaxis()->SetRangeUser(0,200);
		  if (run!=run1) htot->Add(h);
		  lumiadd+=lumi;
		  h->SetFillColor(kTeal+3);
		  h->GetXaxis()->SetTitle("InvMass_{GLB,GLB} (GeV/c)");
		  h->GetYaxis()->SetTitle("Entries");
		  h->GetXaxis()->SetTitleSize(0.045);
		  h->GetYaxis()->SetTitleSize(0.045);
		  h->GetXaxis()->SetLabelSize(0.035);
		  h->GetYaxis()->SetLabelSize(0.035);

		  h->SetAxisRange(0.0, h->GetMaximum()*1.5, "Y");

		  h->Draw("HIST");

		  TF1 *f = new TF1("f","gaus(0)+pol2(3)",70,110);
		  f->SetParName(0,"norm");
		  f->SetParName(1,"mass");
		  f->SetParName(2,"width");
		  //   f->SetParameters(1.16028e+02,9.07785e+01,2.11556e+00,-2.17600e+01,9.67443e-01,-6.98382e-03);
		  f->SetParLimits(0,0,1e6);
		  f->SetParLimits(1,85,95);
		  f->SetParLimits(2,1.5,5);
		  h->Fit(f,"","",70,110);
		  //###   h->GetYaxis()->SetRangeUser(0,200);
		  c1->Update();

		  TF1 *f2 = new TF1("f2","gaus(0)",70,110);
		  f2->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
		  f2->Draw("same");
		  int integral = (int) (f2->Integral(70,110) / h->GetBinWidth(2));

		  int justcount = h->Integral();


		  TLatex *tl_top = new TLatex();
		  //###tl->DrawLatexNDC(0.1,0.95,Form("pPb 8TeV [%i-%i, %.1f nb^{-1}]",run1,run2,lumi));
		  tl_top->SetTextSize(0.035);
		  tl_top->SetTextFont(42);


		  //   tl_top->DrawLatexNDC(0.20,0.94,Form("2018 PbPb 5.02 TeV [%i-%i, %.1f nb^{-1}]",run1,run2,lumi));
		  //   tl_top->DrawLatexNDC(0.20,0.94,Form("2018 PbPb (%.1f nb^{-1} , 5.02 TeV) [%i-%i]",lumi,run1,run2));
		  tl_top->DrawLatexNDC(0.20,0.94,Form("2018 PbPb (%.1f nb^{-1} , 5.02 TeV) [Run : %i]",lumi,run));

		  TLatex *tl_CMS = new TLatex();
		  tl_CMS->SetTextSize(0.060);//0.040
		  tl_CMS->SetTextFont(61);
		  tl_CMS->DrawLatexNDC(0.18,0.86,"CMS");

		  TLatex *tl_CMSpl = new TLatex();
		  tl_CMSpl->SetTextSize(0.060*0.76);
		  tl_CMSpl->SetTextFont(52);
		  tl_CMSpl->DrawLatexNDC(0.18,0.81,"Preliminary");

		  TLatex *tl_body = new TLatex();
		  tl_body->SetTextSize(0.035);
		  tl_body->SetTextFont(42);

		  tl_body->DrawLatexNDC(0.18,0.75,Form("%i Z bosons (from counting)",justcount));
		  tl_body->DrawLatexNDC(0.18,0.71,Form("%i Z bosons (from fitting)",integral));
		  tl_body->DrawLatexNDC(0.18,0.67,Form("(#sigma = %.1f nb)",integral/lumi));
		  c1->SaveAs(Form("figures_runbyrun/plotZ_%i.pdf",run));
		  c1->SaveAs(Form("figures_runbyrun/plotZ_%i.png",run));

{
		  htot->SetFillColor(kTeal+3);
		  htot->GetXaxis()->SetTitle("InvMass_{GLB,GLB} (GeV/c)");
		  htot->GetYaxis()->SetTitle("Entries");
		  htot->GetXaxis()->SetTitleSize(0.045);
		  htot->GetYaxis()->SetTitleSize(0.045);
		  htot->GetXaxis()->SetLabelSize(0.035);
		  htot->GetYaxis()->SetLabelSize(0.035);

		  //h->SetAxisRange(0.0, h->GetMaximum()*1.5, "Y");
		  htot->SetAxisRange(0.0, 15.0, "Y");


		  htot->Draw("HIST");

		  TF1 *fadd = new TF1("fadd","gaus(0)+pol2(3)",70,110);
		  fadd->SetParName(0,"norm");
		  fadd->SetParName(1,"mass");
		  fadd->SetParName(2,"width");
		  //   f->SetParameters(1.16028e+02,9.07785e+01,2.11556e+00,-2.17600e+01,9.67443e-01,-6.98382e-03);
		  fadd->SetParLimits(0,0,1e6);
		  fadd->SetParLimits(1,85,95);
		  fadd->SetParLimits(2,1.5,5);
		  htot->Fit(fadd,"","",70,110);
		  //###   h->GetYaxis()->SetRangeUser(0,200);
		  c1->Update();

		  TF1 *f2add = new TF1("f2add","gaus(0)",70,110);
		  f2add->SetParameters(fadd->GetParameter(0),fadd->GetParameter(1),fadd->GetParameter(2));
		  f2add->Draw("same");
		  int integraladd = (int) (f2add->Integral(70,110) / htot->GetBinWidth(2));

		  int justcountadd = htot->Integral();


		  TLatex *tl_topadd = new TLatex();
		  //###tl->DrawLatexNDC(0.1,0.95,Form("pPb 8TeV [%i-%i, %.1f nb^{-1}]",run1,run2,lumi));
		  tl_topadd->SetTextSize(0.032);
		  tl_topadd->SetTextFont(42);
		  //   tl_top->DrawLatexNDC(0.20,0.94,Form("2018 PbPb 5.02 TeV [%i-%i, %.1f nb^{-1}]",run1,run2,lumi));
		  //   tl_top->DrawLatexNDC(0.20,0.94,Form("2018 PbPb (%.1f nb^{-1} , 5.02 TeV) [%i-%i]",lumi,run1,run2));
		  tl_topadd->DrawLatexNDC(0.15,0.94,Form("2018 PbPb (%.1f nb^{-1} , 5.02 TeV) [Run : %i-%i]",lumiadd,run1,run));

		  TLatex *tl_CMSadd = new TLatex();
		  tl_CMSadd->SetTextSize(0.060);//0.040
		  tl_CMSadd->SetTextFont(61);
		  tl_CMSadd->DrawLatexNDC(0.18,0.86,"CMS");

		  TLatex *tl_CMSpladd = new TLatex();
		  tl_CMSpladd->SetTextSize(0.060*0.76);
		  tl_CMSpladd->SetTextFont(52);
		  tl_CMSpladd->DrawLatexNDC(0.18,0.81,"Preliminary");

		  TLatex *tl_bodyadd = new TLatex();
		  tl_bodyadd->SetTextSize(0.035);
		  tl_bodyadd->SetTextFont(42);

		  tl_bodyadd->DrawLatexNDC(0.18,0.75,Form("%i Z bosons (from counting)",justcountadd));
		  tl_bodyadd->DrawLatexNDC(0.18,0.71,Form("%i Z bosons (from fitting)",integraladd));
		  tl_bodyadd->DrawLatexNDC(0.18,0.67,Form("(#sigma = %.1f nb)",integraladd/lumiadd));
	  	  if (add) c1->SaveAs("figures_wholerun/plotZadd.gif+100");


		  c1->SaveAs(Form("figures_wholerun/plotZ_%i_%i.pdf",run1,run));
		  c1->SaveAs(Form("figures_wholerun/plotZ_%i_%i.png",run1,run));



}
//		  if (add) c1->SaveAs("plotZ.gif+100");

		  file->Close();
}
		 flist.close();
}
