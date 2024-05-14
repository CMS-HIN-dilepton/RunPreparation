#ifndef TREEREADER
#define TREEREADER

#include"TTree.h"

class TreeReader
{
    TTree* tree;

    public:

    TreeReader(TTree* tree);

    void addInput(const std::string& varName,void* address);
    void readEntry(Long64_t entry) {  tree->GetEntry(entry);}
    Long64_t findEntryByIndex(Long64_t index) {return tree->GetEntryNumberWithIndex(index);}
    void buildIndex(const char* indexName) { tree->BuildIndex(indexName);}

};

#endif