#include <iostream>
#include <vector>

vector<string> triggername = {"HLT_HIL1DoubleMuOpen_v1","HLT_HIL1DoubleMu3Open_v1","HLT_HIL1DoubleMu3p5Open_v1","HLT_HIL1DoubleMu4Open_v1","HLT_HIL1DoubleMu4p5Open_v1","HLT_HIL1DoubleMu5Open_v1","HLT_HIL1DoubleMu7Open_v1","HLT_HIL1DoubleMu10Open_v1","HLT_HIL2DoubleMuOpen_v1","HLT_HIL2DoubleMu1Open_v1","HLT_HIL2DoubleMu1p5Open_v1","HLT_HIL2DoubleMu2Open_v1","HLT_HIL2DoubleMu3Open_v1","HLT_HIL3DoubleMuOpen_v1","HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v1","HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v1","HLT_HIL3Mu12_v1"};

void compare(){

	TFile *oniafile = new TFile("/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/Oniatree_UpsilonHydjet_EmbeddedSample_CMSSW_11_3_2_20220118.root","read");
	TFile *hltfile = new TFile("/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/HLT/openHLT_DileptMu_UpsilonHydjet_Embedded_20220204.root","read");
	int triggernum = triggername.size();
	TTree *hlttree[triggernum];
	TTree *oniatree;
	vector<float> *hltpt[triggernum];
	for(int i =0; i< triggernum; i++){
		hltpt[i] = new vector<float>;
	}
	TClonesArray *Reco_mu_4mom = new TClonesArray;
	TClonesArray *Reco_mu_L1_4mom = new TClonesArray;
	TClonesArray *Reco_QQ_4mom = new TClonesArray;
	TH1D *hist = new TH1D("onia pt","onia pt;pt;counts",100,0,10);
	const TLorentzVector *mu;
	int x =0;
/*	for(auto i : triggername){
		hlttree[x] = (TTree*)hltfile -> Get(Form("hltobject/%s",i.c_str()));
		hlttree[x] -> SetBranchAddress("pt",&hltpt[x]);
		for(int j =0; j<hlttree[x] -> GetEntries(); j++){
					hlttree[x] -> GetEntry(j);
			if(hltpt[x]->size() != 0){
				for(int k =0; k<hltpt[x]->size(); k++){
					cout<<hltpt[x] -> at(k) <<endl;


				}

			}

		}
		x++;
	}
}*/

	oniatree = (TTree*) oniafile -> Get("hionia/myTree");
	short Reco_mu_size , Reco_QQ_size;
	oniatree -> SetBranchAddress("Reco_mu_L1_4mom",&Reco_mu_L1_4mom);
	oniatree -> SetBranchAddress("Reco_mu_4mom",&Reco_mu_4mom);
	oniatree -> SetBranchAddress("Reco_QQ_4mom",&Reco_QQ_4mom);
	oniatree -> SetBranchAddress("Reco_mu_size",&Reco_mu_size);
	oniatree -> SetBranchAddress("Reco_QQ_size",&Reco_QQ_size);

	x=0;
	for(int j=0; j<(oniatree -> GetEntries())/10; j++){
		oniatree -> GetEntry(j);


		for(auto i : triggername){
			//hlttree[x] -> GetEntry(j);
			bool isL1 = (i.find("L1") != std::string::npos) ? true : false;
			bool isDB = i.find("Double") != std::string::npos ? true : false;
			int size = isDB ? Reco_QQ_size : Reco_mu_size;
			for(int k=0; k<size; k++){
				if(!(isDB)){
					mu =  isL1 ? (TLorentzVector*)Reco_mu_L1_4mom->At(k) : (TLorentzVector*)Reco_mu_4mom->At(k);
				}
				if(isDB){
					mu = (TLorentzVector*)Reco_QQ_4mom -> At(k);
				}
				const float pt = mu -> Pt();
			//	cout << Form("Entry %d onia Pt value : ",j) << pt << endl;
				hist -> Fill(pt);	
			}
		//	for(int k =0; k< hltpt[x] -> size(); k++){
		//		cout << Form("Entry %d hlt Pt value : ",k) <<hltpt[x]->at(k) << endl;
		//	}
			x++;
		}
	}
	hist -> Draw();
}












