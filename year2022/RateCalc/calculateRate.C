#include "RateCalc.cc"
#include "TGraph.h"
#include <ROOT/TProcessExecutor.hxx>
#include <thread>
#include <future>
#include <execution>

static int UseNCores = 40;

void calculateRate(){
	string n_file = "openHLT_Gmenu_JPsiEMB_NoSPClimit_v1230_v8.root";
	n_file = "openHLT_HIMuon_MBPD2018_v1230_v9.root";
	n_file = "openHLT_CPUlegacy_MB_1210_pre3.root";
//	string n_file = "openHLT_Gmenu_JPsi_v1230_v9.root";

	//String vector for trigger names
	std::vector<string> v_names;
	{
		RateCalc _calc = RateCalc(n_file.c_str());
		_calc.setAllHLT();
		for( auto word : _calc.v_names ){
			v_names.push_back(word.first);
		}
	}
	v_names = {"HLT_HIL3Mu0NHitQ10_L2Mu0_MAXdR3p5_M1to5_v", "HLT_HIL3Mu2p5NHitQ10_L2Mu2_M7toinf_v", "HLT_HIL1DoubleMuOpen_v", "HLT_HIL2DoubleMuOpen_v", "HLT_HIL3DoubleMuOpen_v"};

	//Enable MultiThreading, the thread executor creates threads per trigger and make use of the available CPU cores
	ROOT::EnableImplicitMT(UseNCores);
	ROOT::TThreadExecutor mpe(v_names.size());

	//Define cuts
	std::vector<double> cuts;
	for(auto idx : ROOT::TSeqI(31)){
		cuts.push_back(0.5 *(double) idx);
	}

	//Run calculator
	int max_events = 35*1e+4;
	auto extractRates = [=](int idx){
		RateCalc calc = RateCalc(n_file.c_str());
		calc.setObjectTree(v_names[idx], cuts);
		calc.evalAll(max_events);
		return calc.getRates();
	};

	//Result container
	std::unordered_map<string, std::map<double, double> > result_map;
	std::map<string, TGraph*> graps;

	//Map results
	const auto& res = mpe.Map(extractRates, ROOT::TSeqI(v_names.size()));
	for( auto idx : res ){
		for( auto item : idx ){
			result_map[item.first] = item.second;
		}
	}

	//Draw graphs
	TFile* output = new TFile("output_mbpd_2018Menu.root", "recreate");
	output->cd();
	for( auto result : result_map ){
		graps[result.first] = new TGraph();
		for( auto key_val : result.second){
			graps[result.first]->AddPoint(key_val.first, key_val.second);
		}
		graps[result.first]->SetName(result.first.c_str());
		graps[result.first]->SetMarkerStyle(kFullCircle);
		graps[result.first]->SetMarkerSize(1.2);
		graps[result.first]->GetXaxis()->SetTitle("p_T cut (GeV/c)");
		graps[result.first]->GetYaxis()->SetTitle("Rate (HLT L(N) / Total Events)");
		graps[result.first]->GetYaxis()->SetLimits(0,1);
		graps[result.first]->GetYaxis()->SetRangeUser(0,1);
		graps[result.first]->Write();
	}
	output->Close();
};
