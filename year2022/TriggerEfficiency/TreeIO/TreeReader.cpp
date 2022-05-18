
#include"TreeReader.h"

TreeReader::TreeReader(TTree* input): tree(input)
{
    if (tree==nullptr) throw std::invalid_argument("TreeReader: Tree is nullptr\n");
}

void TreeReader::addInput(const std::string& varName,void* address)
{
    TBranch* branch = tree->GetBranch(varName.data());
    if (branch ==nullptr)
    {
        std::string error = std::string("Branch '")+varName+ "' in tree '"+ tree->GetName()  +"' does not exist.\n";
        throw std::runtime_error(error);
    }
    branch->SetAddress(address);
}