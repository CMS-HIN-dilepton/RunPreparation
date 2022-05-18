#include "HltInput.h"

HltInput::~HltInput(){
	if( file_hlt->IsOpen() ) file_hlt->Close();
};

HltInput::HltInput( string name_file ){
	file_hlt = TFile::Open(name_file.c_str());
	tree_hlt = (TTree*) file_hlt->Get("hltanalysis/HltTree");
	name_opened_file = name_file;
};

TTree* HltInput::getObjectTree(string name_hltobj){
	return (TTree*) file_hlt->Get(Form("hltobject/%s", name_hltobj.c_str()) );
};

TTree* HltInput::getHltTree(){
	return tree_hlt;
};
