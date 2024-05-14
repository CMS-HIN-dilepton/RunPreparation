
#include"TreeWriter.h"

TreeWriter::TreeWriter(TTree* input): tree(input)
{
    if (tree==nullptr) throw std::invalid_argument("TreeReader: Tree is nullptr\n");
}

void TreeWriter::addOutput(const std::string& varName,Int_t* address)
{
    tree->Branch(varName.data(),address);
}

void TreeWriter::addOutput(const std::string& varName,Float_t* address)
{
    tree->Branch(varName.data(),address);
}