const char* triggername[28] = {"HLT_PAL1DoubleMu0_HighQ_v1", 
   "HLT_PAL1DoubleMu0_MGT1_v1",
   "HLT_PAL1DoubleMu0_v1",
   "HLT_PAL1DoubleMu10_v1",
   "HLT_PAL1DoubleMuOpen_OS_v1",
   "HLT_PAL1DoubleMuOpen_SS_v1",
   "HLT_PAL1DoubleMuOpen_v1",
   "HLT_PAL2DoubleMu0_v1",
   "HLT_PAL2DoubleMu10_v1",
   "HLT_PAL2Mu12_v1",
   "HLT_PAL2Mu15_v1",
   "HLT_PAL3DoubleMu0_HIon_v1",
   "HLT_PAL3DoubleMu0_v1",
   "HLT_PAL3DoubleMu10_v1",
   "HLT_PAL3Mu15_v1",
   "HLT_PAL3Mu3_v1",
   "HLT_PAL3Mu5_v1",
   "HLT_PAL3Mu7_v1",
   "L1_DoubleMu0_BptxAND (bit 28)",
   "L1_DoubleMu0_MassGT1_BptxAND (bit 30)",
   "L1_DoubleMu10_BptxAND (bit 33)",
   "L1_DoubleMu10_Mass60to150_BptxAND (bit 34)",
   "L1_DoubleMuOpen_BptxAND (bit 26)",
   "L1_DoubleMuOpen_OS_BptxAND (bit 31)",
   "L1_DoubleMuOpen_SS_BptxAND (bit 32)",
   "L1_SingleMu3_BptxAND (bit 19)",
   "L1_SingleMu5_BptxAND (bit 21)",
   "L1_SingleMu7_BptxAND (bit 23)"};
double exprates[28] = {96, 
   130,
   160,
   2,
   136,
   96,
   243,
   116,
   0,
   28,
   15,
   36,
   44,
   0,
   8,
   1856,
   564,
   190,
   166,
   140,
   2,
   0,
   319,
   200,
   110,
   10395,
   3188,
   1092};

double factor = 1.;

void checkrates(const char* filename="dqm.root") {
   TFile *f = TFile::Open(filename);
   if (!f) return;

   TCanvas *c1 = new TCanvas();
   gStyle->SetOptTitle(1);

   for (int i=0; i<28; i++) {
      TH1F *h = (TH1F*) f->Get(triggername[i]);
      if (!h) continue;
      TF1 *f = new TF1("pol","pol0",0,h->GetXaxis()->GetXmax());
      h->Fit(f);
      f->SetLineColor(kRed);
      float fittedrate = f->GetParameter(0);
      h->GetYaxis()->SetRangeUser(0,1.5*TMath::Max((Float_t) (exprates[i]/factor),(Float_t) fittedrate)+10);
      h->SetMarkerColor(kRed);
      h->SetLineColor(kBlack);
      h->Draw();
      f->Draw("same");
      TLine *line = new TLine(1,exprates[i]/factor,h->GetNbinsX(),exprates[i]/factor);
      line->SetLineColor(kBlue);
      line->Draw();
      TLatex tl1; tl1.SetTextColor(kBlue); tl1.DrawLatexNDC(0.2,0.85,Form("Expected at 1MHz: %.2f",exprates[i]/factor));
      TLatex tl2; tl2.SetTextColor(kRed); tl2.DrawLatexNDC(0.2,0.8,Form("Observed at 1MHz: %.2f",fittedrate));
      TLatex tl3; tl2.SetTextColor(kBlack); tl2.DrawLatexNDC(0.2,0.75,Form("Ratio: %.2f",fittedrate/(exprates[i]/factor)));
      c1->SaveAs(Form("%s.pdf",triggername[i]));
      delete f;
   }
   f->Close();
}
