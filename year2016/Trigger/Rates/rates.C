#include "TSystem.h"
#include "TROOT.h"
#include "TDirectory.h"
#include "TFile.h"
#include<vector>


#include "TGraph.h"
#include "TMath.h"
#include <iostream>


void rates()
{
  
  std::vector<string> trignames;
  trignames.push_back("PAL3Mu3");
  trignames.push_back("PAL3Mu5");
  trignames.push_back("PAL3Mu7");
  trignames.push_back("PAL2Mu12");
  trignames.push_back("PADoubleMu");
  
  std::vector<float> normrate;
  normrate.push_back(1852.0);
  normrate.push_back(566.0);
  normrate.push_back(193.0);
  normrate.push_back(28.0);
  normrate.push_back(283.0);
  
  std::vector< std::vector<int> > prescale;
  // First column (1 MHz)
  std::vector<int> tmp;
  tmp.push_back(5);
  tmp.push_back(2);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);
  // Second column (0.7 MHz)
  tmp.clear();
  tmp.push_back(3);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);
  // Second column (0.5 MHz)
  tmp.clear();
  tmp.push_back(2);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);
  // Second column (0.3 MHz)
  tmp.clear();
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);
  // Second column (0.2 MHz)
  tmp.clear();
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);
  // Second column (0.1 MHz)
  tmp.clear();
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  tmp.push_back(1);
  prescale.push_back(tmp);


  Double_t x[1000], y[1000], y2[1000];
  
  for(int i=0; i<1000; i++) {
     
    x[i] = 0.0 + ( double(i) * (5.0/1000.0) );

    double exp = TMath::Exp(-1.0*(x[i]/5.0));
    double rate = 0.0;
    double rateDiMu = 0.0;
    if (exp > 0.7) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[0][0] ) + ( (normrate[1]-normrate[2])/prescale[0][1] ) + ( (normrate[2]-normrate[3])/prescale[0][2] ) + ( (normrate[3])/prescale[0][3] ) )*exp;
    }
    else if (exp > 0.5) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[1][0] ) + ( (normrate[1]-normrate[2])/prescale[1][1] ) + ( (normrate[2]-normrate[3])/prescale[1][2] ) + ( (normrate[3])/prescale[1][3] ) )*exp;
    }
    else if (exp > 0.3) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[2][0] ) + ( (normrate[1]-normrate[2])/prescale[2][1] ) + ( (normrate[2]-normrate[3])/prescale[2][2] ) + ( (normrate[3])/prescale[2][3] ) )*exp;
    }
    else if (exp > 0.2) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[3][0] ) + ( (normrate[1]-normrate[2])/prescale[3][1] ) + ( (normrate[2]-normrate[3])/prescale[3][2] ) + ( (normrate[3])/prescale[3][3] ) )*exp;
    }
    else if (exp > 0.1) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[4][0] ) + ( (normrate[1]-normrate[2])/prescale[4][1] ) + ( (normrate[2]-normrate[3])/prescale[4][2] ) + ( (normrate[3])/prescale[4][3] ) )*exp;
    }
    else if (exp > 0.0) {
      rate =  ( ( (normrate[0]-normrate[1])/prescale[5][0] ) + ( (normrate[1]-normrate[2])/prescale[5][1] ) + ( (normrate[2]-normrate[3])/prescale[5][2] ) + ( (normrate[3])/prescale[5][3] ) )*exp;
    }
    y[i] = rate;
    y2[i] =  ( normrate[4] )*exp;
  }
 

  TGraph* hRate = new TGraph(1000, x, y);
  TGraph* h2Rate = new TGraph(1000, x, y2);
  hRate->Draw();
  h2Rate->Draw();

  double mean = hRate->GetMean(2);
  double mean2 = h2Rate->GetMean(2);
  std::cout << "Single Muon average rate: " << mean << std::endl;
  std::cout << "Double Muon average rate: " << mean2 << std::endl;
}
