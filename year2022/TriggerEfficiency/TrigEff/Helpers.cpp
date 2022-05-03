
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

bool isInAcceptance(float pt, float abseta)
{
	//	if (abseta >2.4) return false;
	//	if (abseta <2.4) return pt>4; 

	if (abseta > 2.4 ) return false; //JPsi cut
	if (abseta < 1.2 ) return pt >3.5;
	if (1.2<abseta && abseta < 2.1 ) return pt >= 5.47-1.89*abseta;
	return pt >1.5;
}
bool isPassQualityCuts(const OniaInput* in, int index)
{
    if (in->reco_mu_nPixWMea[index] <=0 ) return false;
    if (in->reco_mu_nTrkWMea[index] <=5 ) return false;
    if (in->reco_mu_dxy[index] >=0.3 ) return false;
    return (in->reco_mu_dz[index] < 20.0);
}
