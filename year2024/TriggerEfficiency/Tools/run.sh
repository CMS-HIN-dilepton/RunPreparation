ONIAFILEPATH="/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/Oniatree_Upsilon_CMSSW_11_3_2_211122_v1.root"
ONIATYPE="Upsilon"
OUTPUTDIR="Tools"
mkdir -p ${OUTPUTDIR}
./getEfficiency_pure $ONIAFILEPATH $ONIATYPE $OUTPUTDIR
