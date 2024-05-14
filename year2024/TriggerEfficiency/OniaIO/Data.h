#ifndef DATA
#define DATA

#include"TClonesArray.h"
#include<vector>

#include"../TreeIO/TreeReader.h"
#include"../TreeIO/TreeWriter.h"

const int maxArraySize=100;

struct HltobjInput
{
    std::vector<float>* pt;
    std::vector<float>* eta;
    std::vector<float>* phi;
    std::vector<float>* mass;

    void registerInput(TreeReader* reader);
    HltobjInput();
    ~HltobjInput();
};

struct HltanalysisInput
{
    Long64_t event;
    Int_t run;
    void registerInput(TreeReader* reader);
};

struct OniaInput
{
    Int_t event;
    Float_t sumhf;
    Int_t centrality;
    Short_t reco_mu_size;
    Short_t reco_QQ_size;
    Short_t reco_QQ_mupl_idx[maxArraySize];
    Short_t reco_QQ_mumi_idx[maxArraySize];
    Int_t reco_mu_nTrkWMea[maxArraySize];
    Int_t reco_mu_nPixWMea[maxArraySize];
    Int_t reco_mu_SelectionType[maxArraySize];
    Float_t reco_mu_dxy[maxArraySize];
    Float_t reco_mu_dz[maxArraySize];
    TClonesArray* reco_mu_mom4;
    TClonesArray* reco_mu_L1_mom4;
    TClonesArray* reco_QQ_mom4;
    void registerInput(TreeReader* reader);
    OniaInput();
    ~OniaInput();
};

struct OniaOutput
{
    Float_t pt;
    Float_t m;
    Float_t y;
    Float_t eta;
    Float_t pt_mi;
    Float_t pt_pl;
    Float_t eta_mi;
    Float_t eta_pl;
    Float_t cent;

    void registerInput(TreeReader* reader);
    void registerOutput(TreeWriter* writer);
};


#endif
