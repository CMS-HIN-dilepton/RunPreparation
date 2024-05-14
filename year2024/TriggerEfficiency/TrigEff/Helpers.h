
#ifndef HELPERS
#define HELPERS

#include"TLorentzVector.h"

#include"../OniaIO/Data.h"

const float dRthreshold = 0.3f;
const float dPtThreshold = 0.3f;
const bool dPtThresholdEnabled = false;

struct HltobjEntry
{
    std::vector<float> pt;
    std::vector<float> eta;
    std::vector<float> phi;
    std::vector<float> mass;
};

bool isMatched(const TLorentzVector* recoMuon, const HltobjEntry* onMuons);
bool isInAcceptance(float pt, float abseta,bool isup);
bool isPassQualityCuts(const OniaInput* in, int index);
float findNcoll(int hiBin);
Int_t getHiBinFromhiHF(const Double_t hiHF);
#endif
