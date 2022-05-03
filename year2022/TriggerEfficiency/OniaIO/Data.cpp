
#include"Data.h"

HltobjInput::HltobjInput()
{
    eta= new std::vector<float>();
    pt= new std::vector<float>();
    phi= new std::vector<float>();
    mass= new std::vector<float>();
}

HltobjInput::~HltobjInput()
{
    delete eta;
    delete pt;
    delete phi;
    delete mass;
}

void HltobjInput::registerInput(TreeReader* reader)
{
    reader->addInput("eta",&eta);
    reader->addInput("pt",&pt);
    reader->addInput("phi",&phi);
    reader->addInput("mass",&mass);
}

void HltanalysisInput::registerInput(TreeReader* reader)
{
    reader->addInput("Event",&event);
    reader->addInput("Run",&run);
}

OniaInput::OniaInput()
{
    reco_mu_mom4 = new TClonesArray("TLorentzVector");
    reco_mu_L1_mom4 = new TClonesArray("TLorentzVector");
    reco_QQ_mom4 = new TClonesArray("TLorentzVector");
}

void OniaInput::registerInput(TreeReader* reader)
{
    reader->addInput("eventNb",&event);
    reader->addInput("SumET_HF",&sumhf);
    reader->addInput("Centrality",&centrality);

    reader->addInput("Reco_mu_size", &reco_mu_size);
    reader->addInput("Reco_QQ_size", &reco_QQ_size);
    reader->addInput("Reco_mu_nTrkWMea",&reco_mu_nTrkWMea);
    reader->addInput("Reco_mu_nPixWMea",&reco_mu_nPixWMea);
    reader->addInput("Reco_mu_dxy",&reco_mu_dxy);
    reader->addInput("Reco_mu_dz",&reco_mu_dz);
    reader->addInput("Reco_mu_4mom",&(reco_mu_mom4));
    reader->addInput("Reco_mu_L1_4mom", &(reco_mu_L1_mom4));
    reader->addInput("Reco_QQ_4mom",&(reco_QQ_mom4));
    reader->addInput("Reco_QQ_mupl_idx",&reco_QQ_mupl_idx);
    reader->addInput("Reco_QQ_mumi_idx",&reco_QQ_mumi_idx);

}

OniaInput::~OniaInput()
{
    delete reco_mu_mom4;
    delete reco_mu_L1_mom4;
    delete reco_QQ_mom4;
}

void OniaOutput::registerOutput(TreeWriter* writer)
{
    writer->addOutput("pt",&pt);
    writer->addOutput("y",&y);
    writer->addOutput("cent",&cent);
    writer->addOutput("eta",&eta);
    writer->addOutput("pt_pl",&pt_pl);
    writer->addOutput("pt_mi",&pt_mi);
    writer->addOutput("m",&m);
    writer->addOutput("eta_pl",&eta_pl);
    writer->addOutput("eta_mi",&eta_mi);
}

void OniaOutput::registerInput(TreeReader* reader)
{
    reader->addInput("pt",&pt);
    reader->addInput("y",&y);
    reader->addInput("cent",&cent);
    reader->addInput("eta",&eta);
    reader->addInput("m",&m);
}
