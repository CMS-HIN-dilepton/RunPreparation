

void OniaTreeQA() {
  
  // Et distribution
  TCanvas* HFETcnv = new TCanvas("HFETcnv","HFET",500,500);
  myTree->Draw("SumET_HF>>histoHFET(150,0,300)","Reco_QQ_trig&1==1","");
  histoHFET->SetXTitle("Sum ET (GeV)");

  TCanvas* HFETPlusMinuscnv = new TCanvas("HFETPlusMinuscnv","HFETplusminus",500,500);
  myTree->Draw("SumET_HFplus:SumET_HFminus>>histoHFPlusMinus(150,0,200,150,0,200)","Reco_QQ_trig&1==1","colz");
  histoHFPlusMinus->SetXTitle("Sum ET HF minus (GeV)");
  histoHFPlusMinus->SetYTitle("Sum ET HF plus (GeV)");

  TCanvas* ETNtracksCnv = new TCanvas("ETNtracksCnv","ET",500,500);
  myTree->Draw("SumET_HF:Ntracks>>histoHFETNtracks(100,0,350,100,0,350","Reco_QQ_trig&1==1","colz");
  histoHFETNtracks->SetXTitle("Ntracks");
  histoHFETNtracks->SetYTitle("Sum ET HF (GeV)");

  TCanvas* zVtxCnv = new TCanvas("zVtxCnv","zVtz",500,500);
  myTree->Draw("zVtx>>histoZVtx(100,-20,20)","Reco_QQ_trig&1==1","");
  histoZVtx->SetXTitle("z_{vtx} (cm)");

  TCanvas* CentralityCnv = new TCanvas("CentralityCnv","Centrality",500,500);
  myTree->Draw("Centrality>>histoCentrality(200,0,200)","Reco_QQ_trig&1==1","");
  gPad->SetLogy();
  histoCentrality->SetXTitle("centrality bin");
  
  TCanvas* CentralityHFCnv = new TCanvas("CentralityHFCnv","Centrality vs HF", 500,500);
  myTree->Draw("Centrality:SumET_HF>>histoCentralityHF(100,0,300,200,0,200)","Reco_QQ_trig&1==1","colz");
  histoCentralityHF->SetXTitle("centrality bin");
  histoCentralityHF->SetYTitle("Sum ET HF");
  
  
  TCanvas* NpixNPixelTracksCnv = new TCanvas("NpixNPixelTracksCnv","Npix vs N pixel tracks",500,500);
  myTree->Draw("Npix:NpixelTracks>>histoNpixNpixelTracks(5,0,5,20,0,2000)","Reco_QQ_trig&1==1","colz");
  histoNpixNpixelTracks->SetXTitle("NpixelTrack");
  histoNpixNpixelTracks->SetYTitle("Npix");


  TF1* corr1 = new TF1("corr1","pol1(0)",0,5000);
  corr1->SetParameters(0,16);
  corr1->Draw("same");
  
  
  TCanvas* RecoQQSizeCnv = new TCanvas("RecoQQSizeCnv","RecoQQSize",500,500);
  myTree->Draw("Reco_QQ_size>>histoRecoQQSize(30,0,30)","Reco_QQ_trig&1==1","");
  gPad->SetLogy();
  histoRecoQQSize->SetXTitle("Reco_QQ_size");
  int pairs;
  for (int i=2; i<9; ++i) {
    pairs= TMath::Binomial(i,2); 
    //cout << "Npairs for " << i << " tracks = " << Form("%d",pairs) << endl;
    TLatex* ltx = new TLatex(pairs,1e3,Form("%d",pairs)); // horrible hack..
    ltx->Draw();
  }
  TLatex* ltx2 = new TLatex(15,3e3,"#left( #splitline{n}{2} #right)");
  ltx2->Draw();

  TCanvas* qqSignCnv = new TCanvas("qqSignCnv","qq Sign",500,500);
  myTree->Draw("Reco_QQ_sign>>histoQQsign(5,0,5)","Reco_QQ_trig&1==1");
  histoQQsign->SetXTitle("Reco_QQ_sign");


  TCanvas* nPixValHitsCnv = new TCanvas("nPixValHitsCnv","nPix Valid Hits",500,500);
  myTree->Draw("Reco_mu_nPixValHits>>histonPixValHits(10,0,10)","Reco_QQ_trig&1==1");
  histonPixValHits->SetXTitle("Reco_mu_nPixValHits");

  TCanvas* nPixValHitsEtaCnv = new TCanvas("nPixValHitsEtaCnv","nPix Valid Hits vs Eta",500,500);
  myTree->Draw("Reco_mu_nPixValHits:Reco_mu_4mom.Eta()>>histonPixValHitsEta(30,-3,3,10,0,10)","Reco_QQ_trig&1==1","colz");
  histonPixValHitsEta->SetXTitle("#eta_{#mu}");
  histonPixValHitsEta->SetYTitle("Reco_mu_nPixValHits");

  TCanvas* nMuValHitsCnv = new TCanvas("nMuValHitsCnv","nMu Valid Hits",500,500);
  myTree->Draw("Reco_mu_nMuValHits>>histonMuValHits(55,0,55)","Reco_QQ_trig&1==1");
  histonMuValHits->SetXTitle("Reco_mu_nMuValHits");

  TCanvas* nTrkHitsCnv = new TCanvas("nTrkHitsCnv","nTrack Hits",500,500);
  myTree->Draw("Reco_mu_nTrkHits>>histonTrkHits(32,0,32)","Reco_QQ_trig&1==1");
  histonTrkHits->SetXTitle("Reco_mu_nTrkHits");

  TCanvas* muStationMatchCnv = new TCanvas("muStationMatchCnv","Mu Stations Matched",500,500);
  myTree->Draw("Reco_mu_StationsMatched>>histoMuStationsMatched(6,0,6)","Reco_QQ_trig&1==1");
  histoMuStationsMatched->SetXTitle("Reco_mu_StationsMatched");
  
  TCanvas* muEtaCnv = new TCanvas("muEtaCnv","Mu Eta",500,500);
  myTree->Draw("Reco_mu_4mom.Eta()>>histoMuEta(30,-3,3)","Reco_QQ_trig&1==1");
  histoMuEta->SetXTitle("#eta_{#mu}");

  TCanvas* muPtEtaCnv = new TCanvas("muPtEtaCnv","Mu Pt vs Eta",500,500);
  myTree->Draw("Reco_mu_4mom.Pt():Reco_mu_4mom.Eta()>>histoMuPtEta(30,-3,3,30,0,30)","Reco_QQ_trig&1==1","colz");
  histoMuPtEta->SetXTitle("#eta_{#mu}");
  histoMuPtEta->SetYTitle("p_{T}^{#mu}");

  TCanvas* muPhiEtaCnv = new TCanvas("muPhiEtaCnv","Mu Phi vs Eta",500,500);
  myTree->Draw("Reco_mu_4mom.Phi():Reco_mu_4mom.Eta()>>histoMuPhiEta(30,-3,3,30,-3.15,3.15)","Reco_QQ_trig&1==1","colz");
  histoMuPhiEta->SetXTitle("#eta_{#mu}");
  histoMuPhiEta->SetYTitle("#phi_{#mu}");

  TCanvas* massCnv = new TCanvas("massCnv","dimuon mass",500,500);
  myTree->Draw("Reco_QQ_4mom.M()>>histoOniaMass(100,2,14)","Reco_QQ_trig&1==1&&Reco_QQ_mupl_nPixValHits>2&&Reco_QQ_mumi_nPixValHits>2&&Reco_QQ_mupl_StationsMatched>2&&Reco_QQ_mumi_StationsMatched>2","");
  histoOniaMass->SetXTitle("mass (Gev/c^{2})");
  histoOniaMass->GetXaxis()->SetNdivisions(220);

  TCanvas* cosThetaCnv = new TCanvas("cosThetaCnv","Opening angle",500,500);
  myTree->Draw("((Reco_QQ_mupl_4mom.Px()*Reco_QQ_mumi_4mom.Px())+(Reco_QQ_mupl_4mom.Py()*Reco_QQ_mumi_4mom.Py())+(Reco_QQ_mupl_4mom.Pz()*Reco_QQ_mumi_4mom.Pz()))/(Reco_QQ_mupl_4mom.Vect().Mag()*Reco_QQ_mumi_4mom.Vect().Mag())>>histoCosTheta(220,-1.1,1.1)","Reco_QQ_trig&1==1","");
  histoCosTheta->SetXTitle("cos(#theta_{#mu#mu})");
  histoCosTheta->GetXaxis()->SetNdivisions(220);

  TCanvas* cosThetaRapCnv = new TCanvas("cosThetaRapCnv","Opening Angle vs Rapidity",500,500);
  myTree->Draw("((Reco_QQ_mupl_4mom.Px()*Reco_QQ_mumi_4mom.Px())+(Reco_QQ_mupl_4mom.Py()*Reco_QQ_mumi_4mom.Py())+(Reco_QQ_mupl_4mom.Pz()*Reco_QQ_mumi_4mom.Pz()))/(Reco_QQ_mupl_4mom.Vect().Mag()*Reco_QQ_mumi_4mom.Vect().Mag()):Reco_QQ_4mom.Rapidity()>>histoCosThetaRap(30,-3,3,110,-1.1,1.1)","Reco_QQ_trig&1==1","colz");
  histoCosThetaRap->SetXTitle("y_{#mu#mu}");
  histoCosThetaRap->SetYTitle("cos(#theta_{#mu#mu})");


  // TCanvas* rpAngCnv = new TCanvas("rpAngCnv","rpAng",500,500);
  // myTree->Draw("rpAng>>histoRPang","Reco_QQ_trig&1==1");
  
  return;
}
/*
******************************************************************************
*Tree    :myTree    : My TTree of dimuons                                    *
*Entries :     8990 : Total =        28191430 bytes  File  Size =   13724030 *
*        :          : Tree compression factor =   2.04                       *
******************************************************************************
*Br    0 :eventNb   : eventNb/i                                              *
*Entries :     8990 : Total  Size=      61606 bytes  File Size  =      56024 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    1 :runNb     : runNb/i                                                *
*Entries :     8990 : Total  Size=      61070 bytes  File Size  =      25584 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.17     *
*............................................................................*
*Br    2 :LS        : LS/i                                                   *
*Entries :     8990 : Total  Size=      60266 bytes  File Size  =      29426 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.86     *
*............................................................................*
*Br    3 :zVtx      : zVtx/F                                                 *
*Entries :     8990 : Total  Size=      62056 bytes  File Size  =      55232 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br    4 :nPV       : nPV/F                                                  *
*Entries :     8990 : Total  Size=      60534 bytes  File Size  =      29913 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.84     *
*............................................................................*
*Br    5 :Centrality : Centrality/I                                          *
*Entries :     8990 : Total  Size=      63676 bytes  File Size  =      43846 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.30     *
*............................................................................*
*Br    6 :nTrig     : nTrig/I                                                *
*Entries :     8990 : Total  Size=      61070 bytes  File Size  =      25559 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.17     *
*............................................................................*
*Br    7 :trigPrescale : trigPrescale[nTrig]/I                               *
*Entries :     8990 : Total  Size=     748382 bytes  File Size  =      58397 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=  12.72     *
*............................................................................*
*Br    8 :HLTriggers : HLTriggers/l                                          *
*Entries :     8990 : Total  Size=      98378 bytes  File Size  =      47672 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.95     *
*............................................................................*
*Br    9 :Npix      : Npix/I                                                 *
*Entries :     8990 : Total  Size=      60802 bytes  File Size  =      48584 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.14     *
*............................................................................*
*Br   10 :NpixelTracks : NpixelTracks/I                                      *
*Entries :     8990 : Total  Size=      62946 bytes  File Size  =      26699 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.15     *
*............................................................................*
*Br   11 :Ntracks   : Ntracks/I                                              *
*Entries :     8990 : Total  Size=      62866 bytes  File Size  =      44085 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.27     *
*............................................................................*
*Br   12 :SumET_HF  : SumET_HF/F                                             *
*Entries :     8990 : Total  Size=      63136 bytes  File Size  =      56288 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   13 :SumET_HFplus : SumET_HFplus/F                                      *
*Entries :     8990 : Total  Size=      64216 bytes  File Size  =      57344 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   14 :SumET_HFminus : SumET_HFminus/F                                    *
*Entries :     8990 : Total  Size=      64486 bytes  File Size  =      57608 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   15 :SumET_HFplusEta4 : SumET_HFplusEta4/F                              *
*Entries :     8990 : Total  Size=      64018 bytes  File Size  =      58400 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   16 :SumET_HFminusEta4 : SumET_HFminusEta4/F                            *
*Entries :     8990 : Total  Size=      64286 bytes  File Size  =      58664 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   17 :SumET_ET  : SumET_ET/F                                             *
*Entries :     8990 : Total  Size=      61874 bytes  File Size  =      56288 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   18 :SumET_EE  : SumET_EE/F                                             *
*Entries :     8990 : Total  Size=      61874 bytes  File Size  =      56288 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   19 :SumET_EB  : SumET_EB/F                                             *
*Entries :     8990 : Total  Size=      61874 bytes  File Size  =      56288 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   20 :SumET_EEplus : SumET_EEplus/F                                      *
*Entries :     8990 : Total  Size=      62946 bytes  File Size  =      57344 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   21 :SumET_EEminus : SumET_EEminus/F                                    *
*Entries :     8990 : Total  Size=      63214 bytes  File Size  =      57608 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   22 :SumET_ZDC : SumET_ZDC/F                                            *
*Entries :     8990 : Total  Size=      62142 bytes  File Size  =      56552 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   23 :SumET_ZDCplus : SumET_ZDCplus/F                                    *
*Entries :     8990 : Total  Size=      63214 bytes  File Size  =      57608 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   24 :SumET_ZDCminus : SumET_ZDCminus/F                                  *
*Entries :     8990 : Total  Size=      63482 bytes  File Size  =      57872 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.00     *
*............................................................................*
*Br   25 :Reco_QQ_size : Reco_QQ_size/I                                      *
*Entries :     8990 : Total  Size=      64216 bytes  File Size  =      36222 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.58     *
*............................................................................*
*Br   26 :Reco_QQ_type : Reco_QQ_type[Reco_QQ_size]/I                        *
*Entries :     8990 : Total  Size=     182258 bytes  File Size  =      51473 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.43     *
*............................................................................*
*Br   27 :Reco_QQ_sign : Reco_QQ_sign[Reco_QQ_size]/I                        *
*Entries :     8990 : Total  Size=     182258 bytes  File Size  =      68477 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.58     *
*............................................................................*
*Br   28 :Reco_QQ_4mom : TClonesArray                                        *
*Entries :     8990 : Total  Size=    2610478 bytes  File Size  =    1094302 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.38     *
*............................................................................*
*Br   29 :Reco_QQ_mupl_4mom : TClonesArray                                   *
*Entries :     8990 : Total  Size=    2611823 bytes  File Size  =     696861 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.73     *
*............................................................................*
*Br   30 :Reco_QQ_mumi_4mom : TClonesArray                                   *
*Entries :     8990 : Total  Size=    2611823 bytes  File Size  =     699080 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.72     *
*............................................................................*
*Br   31 :Reco_QQ_trig : Reco_QQ_trig[Reco_QQ_size]/l                        *
*Entries :     8990 : Total  Size=     300939 bytes  File Size  =      93055 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.16     *
*............................................................................*
*Br   32 :Reco_QQ_mupl_trig : Reco_QQ_mupl_trig[Reco_QQ_size]/l              *
*Entries :     8990 : Total  Size=     300701 bytes  File Size  =      86590 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.41     *
*............................................................................*
*Br   33 :Reco_QQ_mumi_trig : Reco_QQ_mumi_trig[Reco_QQ_size]/l              *
*Entries :     8990 : Total  Size=     300701 bytes  File Size  =      93061 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.17     *
*............................................................................*
*Br   34 :Reco_QQ_isCowboy : Reco_QQ_isCowboy[Reco_QQ_size]/O                *
*Entries :     8990 : Total  Size=      95515 bytes  File Size  =      56513 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br   35 :Reco_QQ_ctau : Reco_QQ_ctau[Reco_QQ_size]/F                        *
*Entries :     8990 : Total  Size=     182265 bytes  File Size  =     169251 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.04     *
*............................................................................*
*Br   36 :Reco_QQ_ctauErr : Reco_QQ_ctauErr[Reco_QQ_size]/F                  *
*Entries :     8990 : Total  Size=     183069 bytes  File Size  =     164830 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br   37 :Reco_QQ_ctau3D : Reco_QQ_ctau3D[Reco_QQ_size]/F                    *
*Entries :     8990 : Total  Size=     182801 bytes  File Size  =     169956 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.04     *
*............................................................................*
*Br   38 :Reco_QQ_ctauErr3D : Reco_QQ_ctauErr3D[Reco_QQ_size]/F              *
*Entries :     8990 : Total  Size=     183605 bytes  File Size  =     165833 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.07     *
*............................................................................*
*Br   39 :Reco_QQ_VtxProb : Reco_QQ_VtxProb[Reco_QQ_size]/F                  *
*Entries :     8990 : Total  Size=     183069 bytes  File Size  =     161252 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.10     *
*............................................................................*
*Br   40 :Reco_QQ_dca : Reco_QQ_dca[Reco_QQ_size]/F                          *
*Entries :     8990 : Total  Size=     181997 bytes  File Size  =     159275 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.11     *
*............................................................................*
*Br   41 :Reco_QQ_MassErr : Reco_QQ_MassErr[Reco_QQ_size]/F                  *
*Entries :     8990 : Total  Size=     183069 bytes  File Size  =     164326 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br   42 :Reco_QQ_vtx : TClonesArray                                         *
*Entries :     8990 : Total  Size=    1798769 bytes  File Size  =     503401 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.56     *
*............................................................................*
*Br   43 :Reco_QQ_Ntrk : Reco_QQ_Ntrk[Reco_QQ_size]/I                        *
*Entries :     8990 : Total  Size=     182258 bytes  File Size  =      74603 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.37     *
*............................................................................*
*Br   44 :Reco_QQ_mupl_SelectionType :                                       *
*         | Reco_QQ_mupl_SelectionType[Reco_QQ_size]/I                       *
*Entries :     8990 : Total  Size=     186010 bytes  File Size  =      92969 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.94     *
*............................................................................*
*Br   45 :Reco_QQ_mumi_SelectionType :                                       *
*         | Reco_QQ_mumi_SelectionType[Reco_QQ_size]/I                       *
*Entries :     8990 : Total  Size=     186010 bytes  File Size  =      94342 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.91     *
*............................................................................*
*Br   46 :Reco_QQ_mupl_isGoodMuon : Reco_QQ_mupl_isGoodMuon[Reco_QQ_size]/O  *
*Entries :     8990 : Total  Size=      97391 bytes  File Size  =      58394 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.57     *
*............................................................................*
*Br   47 :Reco_QQ_mumi_isGoodMuon : Reco_QQ_mumi_isGoodMuon[Reco_QQ_size]/O  *
*Entries :     8990 : Total  Size=      97391 bytes  File Size  =      58344 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.57     *
*............................................................................*
*Br   48 :Reco_QQ_mupl_highPurity : Reco_QQ_mupl_highPurity[Reco_QQ_size]/O  *
*Entries :     8990 : Total  Size=      97391 bytes  File Size  =      50865 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.80     *
*............................................................................*
*Br   49 :Reco_QQ_mumi_highPurity : Reco_QQ_mumi_highPurity[Reco_QQ_size]/O  *
*Entries :     8990 : Total  Size=      97391 bytes  File Size  =      51017 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.80     *
*............................................................................*
*Br   50 :Reco_QQ_mupl_TrkMuArb : Reco_QQ_mupl_TrkMuArb[Reco_QQ_size]/O      *
*Entries :     8990 : Total  Size=      96855 bytes  File Size  =      57815 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.58     *
*............................................................................*
*Br   51 :Reco_QQ_mumi_TrkMuArb : Reco_QQ_mumi_TrkMuArb[Reco_QQ_size]/O      *
*Entries :     8990 : Total  Size=      96855 bytes  File Size  =      57665 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.58     *
*............................................................................*
*Br   52 :Reco_QQ_mupl_TMOneStaTight :                                       *
*         | Reco_QQ_mupl_TMOneStaTight[Reco_QQ_size]/O                       *
*Entries :     8990 : Total  Size=      98195 bytes  File Size  =      59189 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.56     *
*............................................................................*
*Br   53 :Reco_QQ_mumi_TMOneStaTight :                                       *
*         | Reco_QQ_mumi_TMOneStaTight[Reco_QQ_size]/O                       *
*Entries :     8990 : Total  Size=      98195 bytes  File Size  =      59135 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.56     *
*............................................................................*
*Br   54 :Reco_QQ_mupl_nPixValHits : Reco_QQ_mupl_nPixValHits[Reco_QQ_size]/I*
*Entries :     8990 : Total  Size=     185474 bytes  File Size  =      77325 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.32     *
*............................................................................*
*Br   55 :Reco_QQ_mumi_nPixValHits : Reco_QQ_mumi_nPixValHits[Reco_QQ_size]/I*
*Entries :     8990 : Total  Size=     185474 bytes  File Size  =      77118 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.33     *
*............................................................................*
*Br   56 :Reco_QQ_mupl_nMuValHits : Reco_QQ_mupl_nMuValHits[Reco_QQ_size]/I  *
*Entries :     8990 : Total  Size=     185206 bytes  File Size  =      78378 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.29     *
*............................................................................*
*Br   57 :Reco_QQ_mumi_nMuValHits : Reco_QQ_mumi_nMuValHits[Reco_QQ_size]/I  *
*Entries :     8990 : Total  Size=     185206 bytes  File Size  =      85148 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.11     *
*............................................................................*
*Br   58 :Reco_QQ_mupl_nTrkHits : Reco_QQ_mupl_nTrkHits[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      85888 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.08     *
*............................................................................*
*Br   59 :Reco_QQ_mumi_nTrkHits : Reco_QQ_mumi_nTrkHits[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      86133 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.08     *
*............................................................................*
*Br   60 :Reco_QQ_mupl_normChi2_inner :                                      *
*         | Reco_QQ_mupl_normChi2_inner[Reco_QQ_size]/F                      *
*Entries :     8990 : Total  Size=     186285 bytes  File Size  =     129755 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.39     *
*............................................................................*
*Br   61 :Reco_QQ_mumi_normChi2_inner :                                      *
*         | Reco_QQ_mumi_normChi2_inner[Reco_QQ_size]/F                      *
*Entries :     8990 : Total  Size=     186285 bytes  File Size  =     130402 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.38     *
*............................................................................*
*Br   62 :Reco_QQ_mupl_normChi2_global :                                     *
*         | Reco_QQ_mupl_normChi2_global[Reco_QQ_size]/F                     *
*Entries :     8990 : Total  Size=     186553 bytes  File Size  =      93321 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.94     *
*............................................................................*
*Br   63 :Reco_QQ_mumi_normChi2_global :                                     *
*         | Reco_QQ_mumi_normChi2_global[Reco_QQ_size]/F                     *
*Entries :     8990 : Total  Size=     186553 bytes  File Size  =     106424 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.70     *
*............................................................................*
*Br   64 :Reco_QQ_mupl_nPixWMea : Reco_QQ_mupl_nPixWMea[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      73952 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.42     *
*............................................................................*
*Br   65 :Reco_QQ_mumi_nPixWMea : Reco_QQ_mumi_nPixWMea[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      73495 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.43     *
*............................................................................*
*Br   66 :Reco_QQ_mupl_nTrkWMea : Reco_QQ_mupl_nTrkWMea[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      82956 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.16     *
*............................................................................*
*Br   67 :Reco_QQ_mumi_nTrkWMea : Reco_QQ_mumi_nTrkWMea[Reco_QQ_size]/I      *
*Entries :     8990 : Total  Size=     184670 bytes  File Size  =      82814 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.16     *
*............................................................................*
*Br   68 :Reco_QQ_mupl_StationsMatched :                                     *
*         | Reco_QQ_mupl_StationsMatched[Reco_QQ_size]/I                     *
*Entries :     8990 : Total  Size=     186546 bytes  File Size  =      77582 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.33     *
*............................................................................*
*Br   69 :Reco_QQ_mumi_StationsMatched :                                     *
*         | Reco_QQ_mumi_StationsMatched[Reco_QQ_size]/I                     *
*Entries :     8990 : Total  Size=     186546 bytes  File Size  =      79423 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.28     *
*............................................................................*
*Br   70 :Reco_QQ_mupl_dxy : Reco_QQ_mupl_dxy[Reco_QQ_size]/F                *
*Entries :     8990 : Total  Size=     183337 bytes  File Size  =     162602 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.09     *
*............................................................................*
*Br   71 :Reco_QQ_mumi_dxy : Reco_QQ_mumi_dxy[Reco_QQ_size]/F                *
*Entries :     8990 : Total  Size=     183337 bytes  File Size  =     161807 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.10     *
*............................................................................*
*Br   72 :Reco_QQ_mupl_dxyErr : Reco_QQ_mupl_dxyErr[Reco_QQ_size]/F          *
*Entries :     8990 : Total  Size=     184141 bytes  File Size  =     129609 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.38     *
*............................................................................*
*Br   73 :Reco_QQ_mumi_dxyErr : Reco_QQ_mumi_dxyErr[Reco_QQ_size]/F          *
*Entries :     8990 : Total  Size=     184141 bytes  File Size  =     130029 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br   74 :Reco_QQ_mupl_dz : Reco_QQ_mupl_dz[Reco_QQ_size]/F                  *
*Entries :     8990 : Total  Size=     183069 bytes  File Size  =     164621 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br   75 :Reco_QQ_mumi_dz : Reco_QQ_mumi_dz[Reco_QQ_size]/F                  *
*Entries :     8990 : Total  Size=     183069 bytes  File Size  =     163676 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br   76 :Reco_QQ_mupl_dzErr : Reco_QQ_mupl_dzErr[Reco_QQ_size]/F            *
*Entries :     8990 : Total  Size=     183873 bytes  File Size  =     130044 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br   77 :Reco_QQ_mumi_dzErr : Reco_QQ_mumi_dzErr[Reco_QQ_size]/F            *
*Entries :     8990 : Total  Size=     183873 bytes  File Size  =     130569 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.36     *
*............................................................................*
*Br   78 :Reco_QQ_mupl_pt_inner : Reco_QQ_mupl_pt_inner[Reco_QQ_size]/F      *
*Entries :     8990 : Total  Size=     184677 bytes  File Size  =     129556 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.38     *
*............................................................................*
*Br   79 :Reco_QQ_mumi_pt_inner : Reco_QQ_mumi_pt_inner[Reco_QQ_size]/F      *
*Entries :     8990 : Total  Size=     184677 bytes  File Size  =     130394 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br   80 :Reco_QQ_mupl_pt_global : Reco_QQ_mupl_pt_global[Reco_QQ_size]/F    *
*Entries :     8990 : Total  Size=     184945 bytes  File Size  =      91840 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.95     *
*............................................................................*
*Br   81 :Reco_QQ_mumi_pt_global : Reco_QQ_mumi_pt_global[Reco_QQ_size]/F    *
*Entries :     8990 : Total  Size=     184945 bytes  File Size  =     105118 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.70     *
*............................................................................*
*Br   82 :Reco_QQ_mupl_ptErr_inner : Reco_QQ_mupl_ptErr_inner[Reco_QQ_size]/F*
*Entries :     8990 : Total  Size=     185481 bytes  File Size  =     130601 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.38     *
*............................................................................*
*Br   83 :Reco_QQ_mumi_ptErr_inner : Reco_QQ_mumi_ptErr_inner[Reco_QQ_size]/F*
*Entries :     8990 : Total  Size=     185481 bytes  File Size  =     130964 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.37     *
*............................................................................*
*Br   84 :Reco_QQ_mupl_ptErr_global :                                        *
*         | Reco_QQ_mupl_ptErr_global[Reco_QQ_size]/F                        *
*Entries :     8990 : Total  Size=     185749 bytes  File Size  =      92521 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.95     *
*............................................................................*
*Br   85 :Reco_QQ_mumi_ptErr_global :                                        *
*         | Reco_QQ_mumi_ptErr_global[Reco_QQ_size]/F                        *
*Entries :     8990 : Total  Size=     185749 bytes  File Size  =     105615 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.70     *
*............................................................................*
*Br   86 :Reco_mu_size : Reco_mu_size/I                                      *
*Entries :     8990 : Total  Size=      62946 bytes  File Size  =      35976 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.59     *
*............................................................................*
*Br   87 :Reco_mu_type : Reco_mu_type[Reco_mu_size]/I                        *
*Entries :     8990 : Total  Size=     168582 bytes  File Size  =      50689 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   3.21     *
*............................................................................*
*Br   88 :Reco_mu_SelectionType : Reco_mu_SelectionType[Reco_mu_size]/I      *
*Entries :     8990 : Total  Size=     170994 bytes  File Size  =      95198 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.74     *
*............................................................................*
*Br   89 :Reco_mu_charge : Reco_mu_charge[Reco_mu_size]/I                    *
*Entries :     8990 : Total  Size=     169118 bytes  File Size  =      67403 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.42     *
*............................................................................*
*Br   90 :Reco_mu_4mom : TClonesArray                                        *
*Entries :     8990 : Total  Size=    2387723 bytes  File Size  =     983258 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.42     *
*............................................................................*
*Br   91 :Reco_mu_trig : Reco_mu_trig[Reco_mu_size]/l                        *
*Entries :     8990 : Total  Size=     272009 bytes  File Size  =      91821 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.90     *
*............................................................................*
*Br   92 :Reco_mu_isGoodMuon : Reco_mu_isGoodMuon[Reco_mu_size]/O            *
*Entries :     8990 : Total  Size=      92632 bytes  File Size  =      57083 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.52     *
*............................................................................*
*Br   93 :Reco_mu_highPurity : Reco_mu_highPurity[Reco_mu_size]/O            *
*Entries :     8990 : Total  Size=      92632 bytes  File Size  =      50653 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.72     *
*............................................................................*
*Br   94 :Reco_mu_TrkMuArb : Reco_mu_TrkMuArb[Reco_mu_size]/O                *
*Entries :     8990 : Total  Size=      92096 bytes  File Size  =      56461 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.53     *
*............................................................................*
*Br   95 :Reco_mu_TMOneStaTight : Reco_mu_TMOneStaTight[Reco_mu_size]/O      *
*Entries :     8990 : Total  Size=      93436 bytes  File Size  =      57876 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.52     *
*............................................................................*
*Br   96 :Reco_mu_nPixValHits : Reco_mu_nPixValHits[Reco_mu_size]/I          *
*Entries :     8990 : Total  Size=     170458 bytes  File Size  =      74996 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.20     *
*............................................................................*
*Br   97 :Reco_mu_nMuValHits : Reco_mu_nMuValHits[Reco_mu_size]/I            *
*Entries :     8990 : Total  Size=     170190 bytes  File Size  =      84098 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.96     *
*............................................................................*
*Br   98 :Reco_mu_nTrkHits : Reco_mu_nTrkHits[Reco_mu_size]/I                *
*Entries :     8990 : Total  Size=     169654 bytes  File Size  =      85631 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.91     *
*............................................................................*
*Br   99 :Reco_mu_normChi2_inner : Reco_mu_normChi2_inner[Reco_mu_size]/F    *
*Entries :     8990 : Total  Size=     171269 bytes  File Size  =     150020 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.10     *
*............................................................................*
*Br  100 :Reco_mu_normChi2_global : Reco_mu_normChi2_global[Reco_mu_size]/F  *
*Entries :     8990 : Total  Size=     171537 bytes  File Size  =     114766 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.44     *
*............................................................................*
*Br  101 :Reco_mu_nPixWMea : Reco_mu_nPixWMea[Reco_mu_size]/I                *
*Entries :     8990 : Total  Size=     169654 bytes  File Size  =      71696 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.29     *
*............................................................................*
*Br  102 :Reco_mu_nTrkWMea : Reco_mu_nTrkWMea[Reco_mu_size]/I                *
*Entries :     8990 : Total  Size=     169654 bytes  File Size  =      81502 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.01     *
*............................................................................*
*Br  103 :Reco_mu_StationsMatched : Reco_mu_StationsMatched[Reco_mu_size]/I  *
*Entries :     8990 : Total  Size=     171530 bytes  File Size  =      76439 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   2.17     *
*............................................................................*
*Br  104 :Reco_mu_dxy : Reco_mu_dxy[Reco_mu_size]/F                          *
*Entries :     8990 : Total  Size=     168321 bytes  File Size  =     154561 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.05     *
*............................................................................*
*Br  105 :Reco_mu_dxyErr : Reco_mu_dxyErr[Reco_mu_size]/F                    *
*Entries :     8990 : Total  Size=     169125 bytes  File Size  =     150208 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.09     *
*............................................................................*
*Br  106 :Reco_mu_dz : Reco_mu_dz[Reco_mu_size]/F                            *
*Entries :     8990 : Total  Size=     168053 bytes  File Size  =     154597 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.05     *
*............................................................................*
*Br  107 :Reco_mu_dzErr : Reco_mu_dzErr[Reco_mu_size]/F                      *
*Entries :     8990 : Total  Size=     168857 bytes  File Size  =     150956 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.08     *
*............................................................................*
*Br  108 :Reco_mu_pt_inner : Reco_mu_pt_inner[Reco_mu_size]/F                *
*Entries :     8990 : Total  Size=     169661 bytes  File Size  =     149866 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.09     *
*............................................................................*
*Br  109 :Reco_mu_pt_global : Reco_mu_pt_global[Reco_mu_size]/F              *
*Entries :     8990 : Total  Size=     169929 bytes  File Size  =     113966 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.44     *
*............................................................................*
*Br  110 :Reco_mu_ptErr_inner : Reco_mu_ptErr_inner[Reco_mu_size]/F          *
*Entries :     8990 : Total  Size=     170465 bytes  File Size  =     150544 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.09     *
*............................................................................*
*Br  111 :Reco_mu_ptErr_global : Reco_mu_ptErr_global[Reco_mu_size]/F        *
*Entries :     8990 : Total  Size=     170733 bytes  File Size  =     114163 *
*Baskets :      264 : Basket Size=      32000 bytes  Compression=   1.45     *
*............................................................................*
*/

