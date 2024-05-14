#ifndef TREEWRITER
#define TREEWRITER

#include"TTree.h"

class TreeWriter
{
    TTree* tree;

    public:

    TreeWriter(TTree* tree);

    void addOutput(const std::string& varName,Int_t* address);
    void addOutput(const std::string& varName,Float_t* address);

    void writeEntry() { tree->Fill();}
};

#endif