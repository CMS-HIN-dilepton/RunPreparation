#pragma once
#define RATECALC_H

#include "TFile.h"
#include "TTree.h"
#include "HltInput.h"

struct HltObj{
	std::vector<short>* ID;
	std::vector<float>* pt;
	std::vector<float>* eta;
	std::vector<float>* phi;
	std::vector<float>* mass;
};

class RateCalc : public HltInput {
	public :
		RateCalc(){};
		~RateCalc();
		RateCalc(string name_file);
		void setAllHLT();
		void setTriggerCuts(std::vector<double> cuts);
		void setTriggerCuts(string name_hltobj, std::vector<double> cuts);
		bool setObjectTree(string name_hltobj);
		bool setObjectTree(string name, std::vector<double> cuts);
		bool setObjectTree(std::vector<string> names);
		bool setObjectTree(std::vector<string> names, std::vector<double> cuts);
		bool unsetObjectTree(string name_hltobj);
		bool unsetObjectTree(std::vector<string> names);
		int needMuons(string name_hltobj);
		std::pair<string, std::map<double, int> > evalTrigger(string name_hltobj, int maxEvt = -1, bool set_prescl = false);
		bool evalAll( int maxEvt = -1, bool set_prescl = false );
		std::unordered_map<string, std::map<double, double> > getRates();
		std::unordered_map<string, std::map<double, int> > map_cutNpasses;
		std::map<string, bool> v_names;

	protected :
		bool checkObjectTree(string name_hltobj);
		void fillTuple(std::map<double, int>& tuple, HltObj obj, int muons);
		void initTuple(std::map<double, int>& tuple, std::vector<double> cuts);
		bool passCut(HltObj obj, double cut, int muons);
	private :
		std::unordered_map<string, std::vector<double> > map_cuts;
		std::unordered_map<string, TTree*> map_hltobj;

};

