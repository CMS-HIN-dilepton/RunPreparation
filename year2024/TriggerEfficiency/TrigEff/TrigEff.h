
#include"RtypesCore.h"

#include<array>
#include"TH1.h"
#include"TTree.h"

struct Output
{
    TTree* total;
    TTree* pass;
};

struct Input
{
    TTree* oniaTree;
    TTree* hltanalysisTree;
    TTree* hltobjectTree;
    bool isL1;
    bool isDBmu;
};

const char oniaTreeName[]="hionia/myTree";
const char hltanalysisTreeName[] = "hltanalysis/HltTree";
const char hltobjDirectoryName[] = "hltobject/";

