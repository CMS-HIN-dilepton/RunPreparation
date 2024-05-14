#pragma once
#define HLTINPUT_H

#include "TFile.h"
#include "TTree.h"
#include <string>

class HltInput{
	public :
		HltInput(){};
		~HltInput();
		HltInput(string name_file);
		TTree* getObjectTree(string name_hltobj);
		TTree* getHltTree();
		string name_opened_file;
	private :
		TFile* file_hlt;
		TTree* tree_hlt;
		friend class RateCalc;
};
