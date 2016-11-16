
#include "TROOT.h"
#include "TKey.h"
#include "TFile.h"
#include "TSystem.h"
#include "TTree.h"

double minpval = 0.01;

void CompDir(TDirectory *t1, TDirectory *tref, int run1, int runref);
void CompHist(TH1 *h1, TH1 *href, int run1, int runref);
      
void CompDir(TDirectory *t1, TDirectory *tref, int run1, int runref) {
   t1->cd();
   //loop on all entries of this directory
   TKey *key;
   TIter nextkey(t1->GetListOfKeys());
   while ((key = (TKey*)nextkey())) {
      const char *classname = key->GetClassName();
      TClass *cl = gROOT->GetClass(classname);
      if (!cl) continue;
      if (cl->InheritsFrom("TDirectory")) {
         t1->cd(key->GetName());
         TDirectory *subdir = gDirectory;
         tref->cd(key->GetName());
         TDirectory *subdirref = gDirectory;
         CompDir(subdir,subdirref,run1,runref);
      } else if (TString(classname) == "TH1F") {
         TH1 *h1 = (TH1*)t1->Get(key->GetName());
         TH1 *href = (TH1*)tref->Get(key->GetName());
         CompHist(h1,href,run1,runref);
      } else {
         // do nothing
     }
  }
}

void CompHist(TH1 *h1, TH1 *href, int run1, int runref) {
   if (!h1 || !href || h1->Integral()==0 || href->Integral()==0) return;
   // first check if both histograms are compatible
   Stat_t s[TH1F::kNstat];
   h1->GetStats(s);// s[1] sum of squares of weights, s[0] sum of weights
   Double_t sumBinContent1 = s[0];
   Double_t effEntries1 = (s[1] ? s[0] * s[0] / s[1] : 0.0);
   href->GetStats(s);// s[1] sum of squares of weights, s[0] sum of weights
   Double_t sumBinContent2 = s[0];
   Double_t effEntries2 = (s[1] ? s[0] * s[0] / s[1] : 0.0);
   float pval_chi2=1, pval_ks=1,pval_ad=1;
   bool iswt = (sumBinContent1==0 || effEntries1==0 || sumBinContent2==0 || effEntries2==0 || TMath::Abs(sumBinContent1 - effEntries1) != 0 || TMath::Abs(sumBinContent2 - effEntries2) != 0);
   if (iswt) {
      // weighted histograms
      pval_chi2 = h1->Chi2Test(href,"WW");
      // pval_ks = h1->KolmogorovTest(href);
   } else {
      // unweighted histograms
      pval_ks = h1->KolmogorovTest(href);
      pval_ad = h1->AndersonDarlingTest(href);
      // double int1 = h1->Integral();
      // double intref = href->Integral(); 
      // if (int1==0 || intref==0) return;
      // h1->Scale(1./int1);
      // href->Scale(1./intref);
      // pval_chi2 = h1->Chi2Test(href,"NORM UU");
   }

   if (pval_chi2>minpval && pval_ks>minpval) return;

   // looks like we have a discrepancy! let's plot the histograms and print the output
   cout << h1->GetTitle() << ": p-val(chi2) = " << pval_chi2 << ", p-val(KS) = " << pval_ks << ", pval_ad = " << pval_ad << endl;

   TCanvas *c1 = new TCanvas();
   href->SetLineColor(kRed);
   if (!iswt) href->DrawNormalized();
   else href->Draw();
   c1->Update();
   // Retrieve the stat box
   TPaveStats *ps = (TPaveStats*)c1->GetPrimitive("stats");
   ps->SetName("statsref");
   ps->SetTextColor(kRed);
   ps->SetX1NDC(0.8);
   ps->SetX2NDC(1.);
   ps->SetY1NDC(0.6);
   ps->SetY2NDC(0.8);

   h1->SetLineColor(kBlack);
   if (!iswt) h1->DrawNormalized("sames");
   else h1->Draw("sames");
   c1->Update();
   TPaveStats *psref = (TPaveStats*)c1->GetPrimitive("stats");
   psref->SetName("stats1");
   psref->SetX1NDC(0.8);
   psref->SetX2NDC(1.);
   psref->SetY1NDC(0.8);
   psref->SetY2NDC(1.);
   c1->Modified();
   c1->Update();

   TLatex *txt = new TLatex();
   if (!iswt) txt->DrawLatexNDC(0.02,0.02,Form("p(KS) = %f, p(AD) = %f",pval_ks,pval_ad));
   else txt->DrawLatexNDC(0.02,0.02,Form("p(#chi^{2}) = %f",pval_chi2));

   c1->SaveAs(Form("%s_%i_%i.png",h1->GetName(),run1,runref));
   delete c1;
}

void compare(const char* name1, const char* nameref, int run1, int runref) {
   gStyle->SetOptStat();
   gStyle->SetOptTitle();

   TFile *f1 = new TFile(name1);
   if (!f1) return;
   TFile *fref = new TFile(nameref);
   if (!fref) return;

   TDirectory *t1 = (TDirectory*) f1->Get("Run summary");
   if (!t1) return;
   TDirectory *tref = (TDirectory*) fref->Get("Run summary");
   if (!tref) return;

   CompDir(t1,tref,run1,runref);
}
