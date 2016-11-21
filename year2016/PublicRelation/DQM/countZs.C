void countZs(const char* filename, int run1=1, int run2=0, float lumi=0, bool add=false) {
   TFile *file = new TFile(filename);
   if (!file) return;
   
   TCanvas *c1 = new TCanvas();
   c1->cd();

   TH1F *h = (TH1F*) file->Get("Run summary/DiMuonHistograms/GlbGlbMuon_HM");
   h->GetYaxis()->SetRangeUser(0,200);
   h->Draw();

   TF1 *f = new TF1("f","gaus(0)+pol2(3)",70,110);
   f->SetParName(0,"norm");
   f->SetParName(1,"mass");
   f->SetParName(2,"width");
   f->SetParameters(1.16028e+02,9.07785e+01,2.11556e+00,-2.17600e+01,9.67443e-01,-6.98382e-03);
   f->SetParLimits(0,0,1e6);
   f->SetParLimits(1,85,95);
   f->SetParLimits(2,1.5,5);
   h->Fit(f,"","",70,110);
   h->GetYaxis()->SetRangeUser(0,200);
   c1->Update();

   TF1 *f2 = new TF1("f2","gaus(0)",70,110);
   f2->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
   int integral = (int) (f2->Integral(70,110) / h->GetBinWidth(2));

   TLatex *tl = new TLatex();
   tl->DrawLatexNDC(0.1,0.95,Form("pPb 8TeV [%i-%i, %.1f nb^{-1}]",run1,run2,lumi));
   tl->DrawLatexNDC(0.18,0.75,Form("%i Z bosons",integral));
   tl->DrawLatexNDC(0.18,0.7,Form("(#sigma = %.1f nb)",integral/lumi));

   if (!add) c1->SaveAs(Form("plotZ_%i_%i.pdf",run1,run2));
   else c1->SaveAs("plotZ.gif+100");

   file->Close();
}
