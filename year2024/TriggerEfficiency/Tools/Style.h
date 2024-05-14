#ifndef COMMONOPT_Style_jaebeom_H
#define COMMONOPT_Style_jaebeom_H

#include <Riostream.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TDirectory.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TF1.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include "TGraphAsymmErrors.h"
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TPaveText.h>
#include <TText.h>
#include <TLatex.h>
#include "TPaletteAxis.h"
#include <TCut.h>
#include <TString.h>
#include <TMath.h>
//#include <math.h>

#include <TArrow.h>
#include <TLorentzVector.h>
#include <TClonesArray.h>
#include <TLorentzRotation.h>
#include <TVector3.h>
#include <TRandom.h>
//#include "CMS_lumi_square.C"
//#include "tdrstyle.C"

////// calculation with error propagation

void DivideValue(Double_t num, Double_t numErr, Double_t den, Double_t denErr, Double_t* frac, Double_t* fracErr){
  *frac = num/den;
  *fracErr = (*frac) * TMath::Sqrt( TMath::Power(numErr/num,2) + TMath::Power(denErr/den,2) );
}

void MultiplyValue(Double_t a, Double_t aErr, Double_t b, Double_t bErr, Double_t* res, Double_t* resErr){
  *res = a*b;
  *resErr = (*res) * TMath::Sqrt( TMath::Power(aErr/a,2) + TMath::Power(bErr/b,2) );
}

void AddValue(Double_t a, Double_t aErr, Double_t b, Double_t bErr, Double_t* res, Double_t* resErr){
  *res = a+b;
  *resErr = 1 * TMath::Sqrt( TMath::Power(aErr,2) + TMath::Power(bErr,2) );
}

void SubtractValue(Double_t a, Double_t aErr, Double_t b, Double_t bErr, Double_t* res, Double_t* resErr){
  *res = a-b;
  *resErr = 1 * TMath::Sqrt( TMath::Power(aErr,2) + TMath::Power(bErr,2) );
}

////// draw lines

void dashedLine(Double_t x1=0,Double_t y1=0,Double_t x2=1,Double_t y2=1,Int_t color=1, Double_t width=1)
{
   TLine* t1 = new TLine(x1,y1,x2,y2);
   t1->SetLineWidth(width);
   t1->SetLineStyle(7);
   t1->SetLineColor(color);
   t1->Draw();
}

void solidLine(Double_t x1=0,Double_t y1=0,Double_t x2=1,Double_t y2=1,Int_t color=1, Double_t width=1)
{
  TLine* t1 = new TLine(x1,y1,x2,y2);
  t1->SetLineWidth(width);
  t1->SetLineStyle(1);
  t1->SetLineColor(color);
  t1->Draw();
}

////// SetStyle

void SetHistStyle(TH1* h, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+2, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
  h-> SetMarkerColor(colorArr[c]);
  if(m<10) h-> SetMarkerStyle(markerFullArr[m]);
  else h-> SetMarkerStyle(markerOpenArr[m-10]);
  h-> SetMarkerSize(1.0);
  h-> SetLineColor(colorArr[c]);
  h-> SetLineWidth(1.);
  h-> GetXaxis()->CenterTitle();
  h-> GetYaxis()->CenterTitle();
}

void SetHistStyleSmall(TH1* h, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+1, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
  h-> SetMarkerColor(colorArr[c]);
  if(m<10) h-> SetMarkerStyle(markerFullArr[m]);
  else h-> SetMarkerStyle(markerOpenArr[m-10]);
  h-> SetMarkerSize(0.3);
  h-> SetLineColor(colorArr[c]);
  h-> SetLineWidth(1.);
  h-> GetXaxis()->CenterTitle();
  h-> GetYaxis()->CenterTitle();
}

void SetHistStyle2D(TH2* h, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+2, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
/*  h-> SetMarkerColor(colorArr[c]);
  if(m<10) h-> SetMarkerStyle(markerFullArr[m]);
  else h-> SetMarkerStyle(markerOpenArr[m-10]);
  h-> SetMarkerSize(1.2);
  h-> SetLineColor(colorArr[c]);
  h-> SetLineWidth(1.);
*/  h-> GetXaxis()->CenterTitle();
  h-> GetYaxis()->CenterTitle();
}

void SetHistStyle2(TH1* h, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+2, kBlue+1, kOrange+7, kAzure+9, kViolet-4, kGreen+1, kPink+9, kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  //Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare};

  h-> SetMarkerColor(colorArr[c]);
  if(m<10) h-> SetMarkerStyle(markerFullArr[m]);
  else h-> SetMarkerStyle(markerOpenArr[m-10]);
  h-> SetMarkerSize(1.2);
  h-> SetLineColor(colorArr[c]);
  h-> SetLineWidth(1);
}

void SetGraphStyle(TGraph* gr, Int_t c, Int_t m) {
  //Int_t colorArr[] = { kPink-6, kBlue-2, kGreen+3, kViolet-6, kBlack };
  Int_t colorArr[] = { kPink-6, kBlue-3, kGreen+2, kViolet-6, kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullSquare, kFullDiamond, kFullCross};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};
  gr-> SetMarkerColor(colorArr[c]);
  if(m<4) gr-> SetMarkerStyle(markerFullArr[m]);
  else gr-> SetMarkerStyle(markerOpenArr[m-4]);
  if (m==2 || m==3) gr-> SetMarkerSize(2.6);
  else gr-> SetMarkerSize(1.5);
  gr-> SetLineColor(colorArr[c]);
  gr-> SetLineWidth(1);
}

void SetGraphStyle2(TGraph* gr, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+2, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
  gr-> SetMarkerColor(colorArr[c]);
  if(m<4) gr-> SetMarkerStyle(markerFullArr[m]);
  else gr-> SetMarkerStyle(markerOpenArr[m-4]);
  if (m==2 || m==3) gr-> SetMarkerSize(1.5);
  else gr-> SetMarkerSize(1.5);
  gr-> SetLineColor(colorArr[c]);
  gr-> SetLineWidth(1.);
  gr-> GetXaxis()->CenterTitle();
  gr-> GetYaxis()->CenterTitle();
}

void SetGraphStyleSmall(TGraph* gr, Int_t c, Int_t m) {
  Int_t colorArr[] = { kGray+3, kRed+2, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullTriangleUp, kFullTriangleDown, kFullSquare, kFullStar, kFullDiamond};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenTriangleUp, kOpenTriangleDown, kOpenSquare, kOpenStar, kOpenDiamond};
  gr-> SetMarkerColor(colorArr[c]);
  if(m<4) gr-> SetMarkerStyle(markerFullArr[m]);
  else gr-> SetMarkerStyle(markerOpenArr[m-4]);
  if (m==2 || m==3) gr-> SetMarkerSize(0.6);
  else gr-> SetMarkerSize(0.8);
  gr-> SetLineColor(colorArr[c]);
  gr-> SetLineWidth(1.);
  gr-> GetXaxis()->CenterTitle();
  gr-> GetYaxis()->CenterTitle();
}

void SetGraphStyleOpen(TGraph* gr, Int_t c, Int_t m, Int_t s) {
  //Int_t colorArr[] = { kPink-6, kBlue-2, kGreen+3, kViolet-6, kBlack };
  Int_t colorArr[] = { kPink-6, kBlue-3, kGreen+2, kViolet-6, kBlack };
  Int_t markerFullArr[] = {kFullCircle, kFullSquare, kFullDiamond, kFullCross};
  Int_t markerOpenArr[] = {kOpenCircle, kOpenSquare, kOpenDiamond, kOpenCross};
  gr-> SetMarkerColor(colorArr[c]);
  gr-> SetMarkerStyle(markerOpenArr[s]);
  if (m==2 || m==3) gr-> SetMarkerSize(2.6);
  else gr-> SetMarkerSize(1.5);
  gr-> SetLineColor(colorArr[c]);
  gr-> SetLineWidth(1);
}

void SetGraphStyleSys(TGraph* gr, Int_t c) {
  //Int_t colorArr[] = { kPink-6, kBlue-2, kGreen+3, kViolet-6, kBlack };
  Int_t colorArr[] = { kPink-6, kBlue-3, kGreen+2, kViolet-6, kBlack };
  Int_t colorArrSys[] = { kRed-10, kBlue-10, kGreen-10, kMagenta-10, kGray};
  gr-> SetLineColor(colorArr[c]);
  gr-> SetFillColorAlpha(colorArrSys[c],0.5);
  gr-> SetLineWidth(1);
}

void SetGraphStyleSys2(TGraph* gr, Int_t c) {
  //Int_t colorArr[] = { kPink-6, kBlue-2, kGreen+3, kViolet-6, kBlack };
  Int_t colorArr[] = {kGray+3, kRed+2, kBlue+1, kOrange+7, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack};
  Int_t colorArrSys[] = {kGray+3, kRed-3, kBlue+1, kOrange+9, kGreen+3, kAzure+9, kViolet-1, kGreen+1,kBlack};
  gr-> SetLineColor(colorArr[c]);
  gr-> SetFillColorAlpha(colorArrSys[c],0.5);
  gr-> SetLineWidth(1);
}

void drawGlobText(const char *text, float xp, float yp, int textColor=kBlack, double textSize=0.04) {
  TLatex* globtex = new TLatex();
  globtex->SetNDC();
  globtex->SetTextAlign(12); //left-center
  globtex->SetTextFont(42);
  globtex->SetTextSize(textSize);
  globtex->DrawLatex(xp, yp, text);
}

void SetLegendStyle(TLegend* l) {
  l->SetFillColor(0);
  l->SetFillStyle(4000);
  l->SetBorderSize(0);
  l->SetMargin(0.2);
  l->SetTextSize(0.029);
  l->SetTextFont(42);
}

void SetTextStyle(TPaveText* t) {
  t->SetFillColor(0);
  t->SetFillStyle(4000);
  t->SetBorderSize(0);
  t->SetMargin(0.2);
  t->SetTextSize(0.035);
}

TH1D *getHistRatio(TH1 *h1, TH1 *h2){
  int nBins1 = h1->GetNbinsX();
  int nBins2 = h2->GetNbinsX();
  if(nBins1!=nBins2){cout << "ERROR!! Inconsistent number of bins!!!" << endl;}

  TH1::SetDefaultSumw2;
  h1->Sumw2();
  h2->Sumw2();
  TH1D* h0 = (TH1D*) h1->Clone(Form("%s_ratio",h1->GetName()));
  h0->Divide(h2);
  return h0;
}


TCanvas *makeHistRatioCanvas(TH1* h0, TH1 *h1, TH1 *h2, double rup, double rdo, bool logopt){
  TCanvas* c1 = new TCanvas(Form("c_%s",h0->GetName()),"",700,700);

  SetHistStyle(h1, 0, 0);
  SetHistStyle(h2, 1, 1);
  SetHistStyle(h0, 1, 3);
  h0->SetMarkerColor(kRed);
  h0->GetYaxis()->SetLimits(rdo, rup);
  h0->GetYaxis()->SetRangeUser(rdo, rup);

  h1->GetXaxis()->SetTitle(" ");
  h1->GetXaxis()->SetTitleSize(0);
  h1->GetXaxis()->SetLabelSize(0);
  h1->GetYaxis()->SetTitleOffset(0.9);
  h1->GetYaxis()->SetTitleSize(0.07);
  h1->GetYaxis()->SetLabelSize(0.06);
  
  h0->GetXaxis()->SetTitleOffset(1.2);
  h0->GetXaxis()->SetTitleSize(0.1);
  h0->GetYaxis()->SetTitleOffset(0.62);
  h0->GetYaxis()->SetTitleSize(0.1);
  h0->GetXaxis()->SetLabelSize(0.1);
  h0->GetYaxis()->SetLabelSize(0.085);
  h0->GetYaxis()->SetNdivisions(505);
  h0->GetYaxis()->SetTickSize(0.04);
  h0->GetXaxis()->SetTickSize(0.06);

  TPad* pad1 = new TPad("pad1", "",0, 0.4, 1.0, 1.0); 
//  pad1->SetRightMargin(0.05);
  pad1->SetTopMargin(0.090);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.14);
  

  TPad* pad2 = new TPad("pad2","",0, 0, 1.0,0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetLeftMargin(0.14);
//  pad2->SetRightMargin(0.05);

  pad1->SetNumber(0);
  pad2->SetNumber(1);

  c1->cd();
  pad1->Draw();
  pad1->cd();
  if(logopt)pad1->SetLogy();
  h1->Draw("pe");
  h2->Draw("pe same");

  pad1->Update();
  c1->Update();

  c1->cd();
  pad2->Draw();
  pad2->cd();
  h0->Draw("pe");
  dashedLine(0,1,h0->GetXaxis()->GetXmax(),1,1);
  pad2->Update();
  c1->Modified();
  c1->Update();

  return c1;
}

TCanvas *makeGraphRatioCanvas(TGraphAsymmErrors* g0, TGraphAsymmErrors* g1, TGraphAsymmErrors* g2, double rup, double rdo, bool logopt){
  TCanvas* c1 = new TCanvas(Form("c_%s",g0->GetName()),"",700,700);

  SetGraphStyle(g1, 0, 0);
  SetGraphStyle(g2, 1, 1);
  SetGraphStyle(g0, 4, 4);
  g0->SetMarkerStyle(kFullCircle);
  g0->GetYaxis()->SetLimits(rdo, rup);
  g0->GetYaxis()->SetRangeUser(rdo, rup);

  g1->GetXaxis()->SetTitle(" ");
  g1->GetXaxis()->SetTitleSize(0);
  g1->GetXaxis()->SetLabelSize(0);
  g1->GetYaxis()->SetTitleOffset(0.9);
  g1->GetYaxis()->SetTitleSize(0.07);
  g1->GetYaxis()->SetLabelSize(0.06);
  
  g1->GetXaxis()->SetNdivisions(510);
  g0->GetXaxis()->SetNdivisions(510);
  
  g0->GetXaxis()->SetTitleOffset(1.2);
  g0->GetXaxis()->SetTitleSize(0.1);
  g0->GetYaxis()->SetTitleOffset(0.62);
  g0->GetYaxis()->SetTitleSize(0.1);
  g0->GetXaxis()->SetLabelSize(0.1);
  g0->GetYaxis()->SetLabelSize(0.085);
  g0->GetYaxis()->SetNdivisions(505);
  g0->GetYaxis()->SetTickSize(0.04);
  g0->GetXaxis()->SetTickSize(0.06);

  TPad* pad1 = new TPad("pad1", "",0, 0.4, 1.0, 1.0); 
//  pad1->SetRightMargin(0.05);
  pad1->SetTopMargin(0.090);
  pad1->SetBottomMargin(0);
  pad1->SetLeftMargin(0.14);
  

  TPad* pad2 = new TPad("pad2","",0, 0, 1.0,0.4);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetLeftMargin(0.14);
//  pad2->SetRightMargin(0.05);

  pad1->SetNumber(0);
  pad2->SetNumber(1);

  c1->cd();
  pad1->Draw();
  pad1->cd();
  if(logopt)pad1->SetLogy();
  g1->Draw("AP");
  g2->Draw("P");

  pad1->Update();
  c1->Update();

  c1->cd();
  pad2->Draw();
  pad2->cd();
  g0->Draw("AP");
  dashedLine(g0->GetXaxis()->GetXmin(),1,g0->GetXaxis()->GetXmax(),1,1,1);
  pad2->Update();
  c1->Modified();
  c1->Update();

  return c1;
}
  







#endif
