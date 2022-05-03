#ifndef ONIAIO
#define ONIAIO

#include"../TreeIO/TreeReader.h"
#include"../TreeIO/TreeWriter.h"
#include"Data.h"

template<typename InputData>
class Reader
{
    TreeReader reader;
    InputData in;

    public:
    Reader(TTree* treeInput): reader(treeInput)
    {
        in.registerInput(&reader);
    }

    void buildIndex(const char* indexName) { reader.buildIndex(indexName);}

    const InputData* readEntry(Long64_t entry)
    {
        reader.readEntry(entry);
        return &in;
    }
    Long64_t findEntryByIndex(Long64_t index) {return reader.findEntryByIndex(index);}
};

template<typename OutputData>
class Writer
{
    TreeWriter writer;

    public:
    OutputData output;

    Writer(TTree* treeInput) :  writer(treeInput)
    {
        output.registerOutput(&writer);
    }

    void writeEntry() { writer.writeEntry();}
};

#endif