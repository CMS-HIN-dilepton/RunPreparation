
#include"Helpers.h"

bool isMatched(const TLorentzVector* recoMuon, const HltobjEntry* onMuons)
{
    int onlineMuonSize= onMuons->eta.size();
    float eta=recoMuon->Eta();
    float phi=recoMuon->Phi();
    float pt=recoMuon->Pt();
    for (int i=0;i<onlineMuonSize;i++)
    {
        float deltaEta= eta - onMuons->eta[i];
        float deltaPhi= std::min(fabs(phi - onMuons->phi[i]),fabs((float)(2*TMath::Pi()-phi+onMuons->phi[i])));
        //float deltaPhi = phi - onMuons->phi[i];
        if (sqrt(deltaEta*deltaEta+deltaPhi*deltaPhi) < dRthreshold)
        {
        //    if (!dPtThresholdEnabled) 
        //        return true;
        //    if (abs(( onMuons->pt[i] - pt )/pt) < dPtThreshold) 
               return true;
        }
    }
    return false;
}

bool isInAcceptance(float pt, float abseta, bool isup)
{       
	if(isup){
		if (abseta >2.4) return false;
		if (abseta <2.4) return pt>4; 
	}
	else{
		if (abseta > 2.4 ) return false; //JPsi cut
		if (abseta < 1.2 ) return pt >3.5;
		if (1.2<abseta && abseta < 2.1 ) return pt >= 5.47-1.89*abseta;
		return pt >1.5;
	}
}
bool isPassQualityCuts(const OniaInput* in, int index)
{
    if (in->reco_mu_nPixWMea[index] <=0 ) return false;
    if (in->reco_mu_nTrkWMea[index] <=5 ) return false;
    if (in->reco_mu_dxy[index] >=0.3 ) return false;
   return (in->reco_mu_dz[index] < 20.0);
}
float findNcoll(int hiBin) {
   const int nbins = 200;
   const float Ncoll[nbins] = {1919.78, 1885.19, 1856.99, 1825.04, 1784.78, 1746.71, 1703.82, 1662.5, 1616.36, 1579.02, 1534.86, 1501.37, 1458.44, 1423.87, 1389.69, 1353.63, 1319.72, 1287.51, 1258.84, 1225.49, 1195.78, 1166.55, 1140.71, 1110.7, 1083.73, 1058.86, 1030.54, 1005.22, 978.904, 956.635, 933.093, 911.224, 887.728, 867.682, 845.888, 823.128, 802.103, 780.984, 762.997, 743.821, 724.782, 705.008, 684.918, 669.106, 650.536, 635.356, 617.694, 602.554, 586.821, 569.964, 556.196, 540.463, 525.911, 510.929, 498.874, 484.433, 472.776, 458.498, 444.539, 432.389, 420.628, 407.479, 396.521, 385.629, 374.165, 363.421, 352.297, 344.028, 333.112, 321.054, 312.064, 301.815, 293.326, 283.747, 275.412, 265.697, 258.378, 248.661, 242.796, 234.84, 226.734, 219.617, 212.156, 205.325, 198.439, 191.398, 184.682, 177.485, 171.602, 165.937, 160.209, 154.521, 149.497, 143.61, 137.743, 133.381, 128.111, 124.338, 118.93, 114.865, 110.556, 106.003, 102.698, 97.8558, 93.4104, 90.1664, 86.6085, 83.0393, 79.8933, 76.3645, 73.2382, 70.0091, 67.5678, 64.8457, 61.7102, 59.1422, 56.4246, 53.8929, 51.7162, 49.3104, 47.3088, 44.6109, 42.6843, 40.8715, 39.0845, 37.3144, 35.425, 33.7925, 32.1438, 30.715, 29.0353, 27.5403, 26.4516, 25.3269, 24.0873, 22.8437, 21.6271, 20.4867, 19.5775, 18.638, 17.7247, 16.7578, 16.1765, 14.9389, 14.2802, 13.6783, 12.9599, 12.2249, 11.6932, 11.022, 10.3871, 9.86386, 9.32372, 8.85135, 8.46894, 8.07039, 7.62505, 7.19262, 6.82553, 6.45724, 6.0716, 5.80577, 5.45966, 5.17205, 4.88161, 4.62344, 4.36325, 4.11154, 3.89572, 3.65409, 3.39633, 3.26805, 3.04014, 2.83118, 2.67305, 2.47943, 2.34147, 2.18737, 1.99697, 1.88241, 1.76099, 1.64482, 1.53348, 1.42174, 1.27572, 1.19665, 1.07725, 0.934853, 0.859419, 0.754135, 0.683542, 0.604478, 0.557281, 0.541549, 0.52138, 0.507664, 0.503227, 0.50121, 0.5, 0.5};
   return Ncoll[hiBin];
}
Int_t getHiBinFromhiHF(const Double_t hiHF)
{
    Int_t binPos = -1;
      for(int i = 0; i < nBins; ++i){
            if(hiHF >= binTable[i] && hiHF < binTable[i+1]){
                    binPos = i;
                          break; 
                              }
              }                   

        binPos = nBins - 1 - binPos;

          return (Int_t)(200*((Double_t)binPos)/((Double_t)nBins));
}
