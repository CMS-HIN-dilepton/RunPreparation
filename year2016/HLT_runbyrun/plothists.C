//example of macro illustrating how to superimpose two histograms
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1.h"
#include "TGaxis.h"
#include "TRandom.h"

void plothists(const char* filename)
{
   //example of macro illustrating how to superimpose two histograms
   //with different scales in the "same" pad.
   // To see the output of this macro, click begin_html <a href="gif/twoscales.gif" >here</a> end_html
   //Author: Rene Brun

   gStyle->SetPadLeftMargin(0.1);
   gStyle->SetPadRightMargin(0.1);
   gStyle->SetTitleYOffset(0.15);
   gStyle->SetTitleOffset(0.15);
   gStyle->SetTitleYSize(0.06);
   gStyle->SetLabelSize(0.08);
   gStyle->SetLabelSize(0.05,"X");
   gStyle->cd();

   TCanvas *c1 = new TCanvas("c1","hists with different scales",600,400);
   c1->SetTicky(kFALSE);
   c1->SetGridy(kTRUE);


   TFile *f = new TFile(filename);
   if (!f || !f->IsOpen()) return;

   vector<TH1*> hists;
   TIter next(f->GetListOfKeys());
   TKey *key;
   while ((key = (TKey*)next())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      
      // it must be an histogram
      if (!cl->InheritsFrom("TH1")) continue;
      TH1 *h = (TH1*)key->ReadObj();
      if (TString(h->GetName()) != "lumi") hists.push_back(h);
   }
   if (hists.size()==0) return;

   TH1 *h1 = hists[0];
   double maxy = h1->GetMaximum();
   for (int i=1; i<hists.size(); i++) maxy = max(maxy,hists[i]->GetMaximum());

   h1->GetYaxis()->SetRangeUser(0,1.1*maxy);
   h1->GetYaxis()->SetTitleSize(0.05);
   h1->GetYaxis()->SetLabelSize(0.05);
   h1->GetXaxis()->SetLabelSize(0.04);

   for (int i=0; i<hists.size(); i++) {
      hists[i]->SetLineWidth(2);
      int color = 0;
      if (i==0) color = kBlack;
      else if (i%11==1) color = kRed+1+(i/11);
      else if (i%11==2) color = kBlue+1+(i/11);
      else if (i%11==3) color = kGreen+1+(i/11);
      else if (i%11==4) color = kOrange+1+(i/11);
      else if (i%11==5) color = kViolet+1+(i/11);
      else if (i%11==6) color = kTeal+1+(i/11);
      else if (i%11==7) color = kPink+1+(i/11);
      else if (i%11==8) color = kAzure+1+(i/11);
      else if (i%11==9) color = kSpring+1+(i/11);
      else if (i%11==10) color = kMagenta+1+(i/11);
      else if (i%11==0) color = kCyan+1+(i/11);

      hists[i]->SetLineColor(color);
      hists[i]->SetMarkerColor(color);
      hists[i]->SetMarkerSize(0);
   }
   h1->Draw("L");
   for (int i=1; i<hists.size(); i++) hists[i]->Draw("L same");
   c1->Update();

   //create lumi filled with the bins integral of h1
   TH1F *lumi = (TH1F*) f->Get("lumi");

   //scale lumi to the pad coordinates
   Float_t rightmax = 1.2*lumi->GetMaximum();
   Float_t scale = gPad->GetUymax()/rightmax;
   lumi->SetLineColor(kYellow+1);
   lumi->SetFillColor(kYellow+1);
   lumi->Scale(scale);
   lumi->Draw("BOX same");

   //draw an axis on the right side
   TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
         gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
   axis->SetTitle(lumi->GetYaxis()->GetTitle());
   axis->SetLineColor(kYellow+2);
   axis->SetLabelColor(kYellow+2);
   axis->SetTitleColor(kYellow+2);
   axis->Draw();

   h1->Draw("AXIS same");
   h1->Draw("L same");
   for (int i=1; i<hists.size(); i++) hists[i]->Draw("L same");

   TLegend *tleg = new TLegend(0.13,0.49,0.49,0.87);
   tleg->SetBorderSize(0);
   tleg->AddEntry(lumi,"Luminosity","f");
   for (int i=0; i<hists.size(); i++) tleg->AddEntry(hists[i],hists[i]->GetName(),"l");
   tleg->Draw();

   c1->SaveAs("plot.pdf");
   c1->SaveAs("plot.root");
}
