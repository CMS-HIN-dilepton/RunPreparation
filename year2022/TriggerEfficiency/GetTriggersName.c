#include <iostream>
#include <string>
#include <fstream>
void GetTriggersName(){
	TFile *oniafile = TFile::Open("/eos/home-s/soohwan/HLT-Dev_Run3/CMSSW_123X_build_v2/CMSSW_12_3_0_pre1/src/HLTrigger/Configuration/test/workstation/openHLT_data2018_newUnstable.root");
	std::ofstream triggerL1("triggersL1.txt");
	std::ofstream triggerL2("triggersL2.txt");
	std::ofstream triggerL3("triggersL3.txt");

	//TFile *oniafile = TFile::Open(oniafilename);
	TTree *tree = (TTree*)  oniafile -> Get("hltanalysis/HltTree");
	auto x = tree -> GetListOfBranches();
/*	for( auto i : *x ){
		if(((string)(i->GetName())).find("HLT") != std::string::npos && ((string)(i->GetName())).find("Pre") ==std::string::npos){
			std::cout << i->GetName() << std::endl;
		}
	}*/

	for( auto i : *x ){
		if(((string)(i->GetName())).find("HLT") != std::string::npos && ((string)(i->GetName())).find("Pre") ==std::string::npos && ((string)(i->GetName())).find("HIL1") !=std::string::npos){
			triggerL1 << ((string)i->GetName()) <<endl;
		}
}
			triggerL1.close();
	for( auto i : *x ){
		if(((string)(i->GetName())).find("HLT") != std::string::npos && ((string)(i->GetName())).find("Pre") ==std::string::npos && ((string)(i->GetName())).find("HIL2") !=std::string::npos){
			triggerL2 << ((string)i->GetName()) <<endl;
		}
}
			triggerL2.close();
	for( auto i : *x ){
		if(((string)(i->GetName())).find("HLT") != std::string::npos && ((string)(i->GetName())).find("Pre") ==std::string::npos && ((string)(i->GetName())).find("HIL3") !=std::string::npos){
			triggerL3 << ((string)i->GetName()) <<endl;
		}
}
			triggerL3.close();
}

