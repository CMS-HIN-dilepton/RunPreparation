#include <iostream>
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TMath.h"
#include "TH2.h"
#include "TH1.h"
#include "TStyle.h"
#include <string>
#define REMOVE_SPACES(x) x.erase(std::remove(x.begin(), x.end(), ' '), x.end())

using namespace std;

void draw(int nMbPDs=1, int nCR=10){

  gStyle->SetOptStat(0);
  
  TString inputfile = Form("Overlaps_all_%dkhz",nCR);
  TFile *f = new TFile(Form("%s.root",inputfile.Data()),"read");
  
  const int nHistPlot = 2;
  std::stringstream ss;

  // ##### drawing
  TCanvas * cO[nHistPlot]; // %
  TCanvas * c1[nHistPlot]; // absolute
  cO[0] = new TCanvas(Form("c_tr_tr_psc_nMbPDs%d",nMbPDs),"",1500,910);
  cO[1] = new TCanvas(Form("c_pd_pd_psc_nmbPD%d",nMbPDs),"",1500,910);
  c1[0] = new TCanvas(Form("c_overlap_tr_rate_nMbPD%d",nMbPDs),"",1500,910);
  c1[1] = new TCanvas(Form("c_overlap_pd_rate_nMbPD%d",nMbPDs),"",1500,910);

  // ### histos 
  TH2D * hO[nHistPlot];
  hO[0] = (TH2D*) f->Get("h_tr_tr_psc");
  hO[1] = (TH2D*) f->Get("h_pd_pd_psc");

  TH1D * h_rate[nHistPlot];
  h_rate[0] = (TH1D*) f -> Get("h_RatesPerTr_psc");
  h_rate[1] = (TH1D*) f -> Get("h_RatesPerPD_psc");

  TH2D* h_overlap_rate[nHistPlot];
  h_overlap_rate[0] = (TH2D*)hO[0] -> Clone("h_overlap_tr_rate"); h_overlap_rate[0]->Reset();
  h_overlap_rate[1] = (TH2D*)hO[1] -> Clone("h_overlap_pd_rate"); h_overlap_rate[1]->Reset();
  
  int nBinX[nHistPlot];
  double diagonalBinCont[nHistPlot];
  double currentBinCont[nHistPlot];
  
  for(int a=0; a<nHistPlot;a++)
    {
      nBinX[a]           = hO[a]->GetNbinsX();
      diagonalBinCont[a] = 0;
      currentBinCont[a]  = 0;
      for(int i=1;i<=nBinX[a];i++)
	{
	  diagonalBinCont[a] = hO[a]->GetBinContent(i,i);
	 
	  for(int j=1;j<=hO[a]->GetNbinsY();j++)
	    {
	      // if(i==1 && j==1) diagonalBinCont[a] *= nMbPDs;
	      if(a==0) gStyle->SetPaintTextFormat(".2f");
	      else if(a==1) gStyle->SetPaintTextFormat(".1f");
	      
	      currentBinCont[a] = hO[a]->GetBinContent(i,j);
	      hO[a]->SetBinContent(i,j,1.00*double(currentBinCont[a]/diagonalBinCont[a])*100);
	      h_overlap_rate[a] -> SetBinContent(i,j,double(hO[a]->GetBinContent(i,j)/100.*h_rate[a]->GetBinContent(i)));
	    }//eachNbinsY
	}//each nBinX
    
      cO[a]->cd();
      cO[a]->SetTickx();
      cO[a]->SetTicky();
      cO[a]->SetGrid();
      cO[a]->SetBorderSize(0);
      cO[a]->SetBorderMode(0);
      cO[a]->SetFillColor(0);
      cO[a]->SetBottomMargin(0.32);
      cO[a]->SetLeftMargin(0.198);
      cO[a]->SetRightMargin(0.02);
      cO[a]->SetTopMargin(0.03);
      cO[a]->SetFrameLineColor(0);
      cO[a]->SetFrameBorderMode(0);
      cO[a]->SetFrameLineColor(0);
      cO[a]->SetFrameBorderMode(0);
    
    
      hO[a]->GetXaxis()->LabelsOption("v");
      hO[a]->GetYaxis()->LabelsOption("v");
      hO[a]->GetXaxis()->SetLabelSize(0.02);
      hO[a]->GetXaxis()->SetLabelOffset(-0.044);
      hO[a]->GetYaxis()->SetLabelSize(0.02);
      hO[a]->GetYaxis()->SetLabelOffset(-0.02);
      hO[a]->GetYaxis()->SetNdivisions(-10000);
      hO[a]->GetXaxis()->SetNdivisions(-10000);
      hO[a]->SetMarkerSize(0.8);
      hO[a]->SetTitle("");
      hO[a]->Draw("col text");
    
      h_overlap_rate[a]->GetXaxis()->LabelsOption("v");
      h_overlap_rate[a]->GetYaxis()->LabelsOption("v");
      h_overlap_rate[a]->GetXaxis()->SetLabelSize(0.02);
      h_overlap_rate[a]->GetXaxis()->SetLabelOffset(-0.044);
      h_overlap_rate[a]->GetYaxis()->SetLabelSize(0.02);
      h_overlap_rate[a]->GetYaxis()->SetLabelOffset(-0.02);
      h_overlap_rate[a]->GetYaxis()->SetNdivisions(-10000);
      h_overlap_rate[a]->GetXaxis()->SetNdivisions(-10000);
      h_overlap_rate[a]->SetMarkerSize(0.8);
      h_overlap_rate[a]->SetTitle("");
      
    if(a==1)
      {
	hO[a]->GetXaxis()->LabelsOption("v");
	hO[a]->GetYaxis()->LabelsOption("v");
	hO[a]->GetXaxis()->SetLabelSize(0.03);
	hO[a]->GetXaxis()->SetLabelOffset(0.0094);
	hO[a]->GetYaxis()->SetLabelSize(0.03);
	hO[a]->GetYaxis()->SetLabelOffset(0.005);
	hO[a]->GetYaxis()->SetNdivisions(-10000);
	hO[a]->GetXaxis()->SetNdivisions(-10000);
	hO[a]->SetMarkerSize(2.0);
	hO[a]->SetTitle("");
	hO[a]->Draw("col text");
	h_overlap_rate[a]->GetXaxis()->LabelsOption("v");
	h_overlap_rate[a]->GetYaxis()->LabelsOption("v");
	h_overlap_rate[a]->GetXaxis()->SetLabelSize(0.03);
	h_overlap_rate[a]->GetXaxis()->SetLabelOffset(0.0094);
	h_overlap_rate[a]->GetYaxis()->SetLabelSize(0.03);
	h_overlap_rate[a]->GetYaxis()->SetLabelOffset(0.005);
	h_overlap_rate[a]->GetYaxis()->SetNdivisions(-10000);
	h_overlap_rate[a]->GetXaxis()->SetNdivisions(-10000);
	h_overlap_rate[a]->SetMarkerSize(2.0);
	h_overlap_rate[a]->SetTitle("");
      }
    
    int tsize = 4;
    TPaletteAxis *palette = new TPaletteAxis(tsize*1.02,0,tsize*1.1,tsize,hO[a]);
    palette->SetLabelColor(1);
    palette->SetLabelFont(42);
    palette->SetLabelOffset(0.005);
    palette->SetLabelSize(0.045);
    palette->SetTitleOffset(1);
    palette->SetTitleSize(0.04);
    palette->SetFillColor(100);
    palette->SetFillStyle(1001);
    
    std::string outName;
    outName = "Results/" + inputfile + "_" + std::string(hO[a]->GetName()) + Form("_nMbPDs%d",nMbPDs)+".png";    
    cO[a]->SaveAs(outName.c_str());


    // ### draw absolute rate
    c1[a]->cd();
    c1[a]->SetTickx();
    c1[a]->SetTicky();
    c1[a]->SetGrid();
    c1[a]->SetBorderSize(0);
    c1[a]->SetBorderMode(0);
    c1[a]->SetFillColor(0);
    c1[a]->SetBottomMargin(0.32);
    c1[a]->SetLeftMargin(0.198);
    c1[a]->SetRightMargin(0.02);
    c1[a]->SetTopMargin(0.03);
    c1[a]->SetFrameLineColor(0);
    c1[a]->SetFrameBorderMode(0);
    c1[a]->SetFrameLineColor(0);
    c1[a]->SetFrameBorderMode(0);
    c1[a]->SetLogz();
    h_overlap_rate[a]->Draw("col text");
      
    std::string outName_rate;
    outName_rate = "Results/" + inputfile + "_" + std::string(h_overlap_rate[a]->GetName()) + Form("_nMbPDs%d",nMbPDs) + ".png";
    c1[a]->SaveAs(outName_rate.c_str());
    
    }// a-loop

  //=========== printout ==================
  const int nPD = h_overlap_rate[1]->GetNbinsX();
  TString pdLabel[nPD];
  string pdname[nPD];
  ofstream myfile (Form("result_%dkHz.txt",nCR));
  if(myfile.is_open())
    {
      myfile << "    ";
      for(int i=1; i<=nPD; i++)
	{
	  pdname[i-1] = h_overlap_rate[1]->GetYaxis()->GetBinLabel(i);
	  REMOVE_SPACES(pdname[i-1]);
	  myfile << pdname[i-1] << "    ";
	}
      myfile << endl;
      for(int i=1; i<=nPD; i++)
	{
	  myfile <<pdname[i-1]; 
	  for(int j=1; j<=nPD; j++)
	    {
	      myfile << "   " << h_overlap_rate[1]->GetBinContent(j,nPD-i+1);
	    }
	  myfile << endl;
	}
    }
  
}


