#path to reco file
ONIAFILEPATH="/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/Oniatree_Jpsi_CMSSW_11_3_2.root" 
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_Jpsi_EMBEDDED_CMSSW_11_3_2.root"
#ONIAFILEPATH="/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/Oniatree_Upsilon_CMSSW_11_3_2_211122_v1.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_UpsilonHydjet_EmbeddedSample_CMSSW_11_3_2_20220210.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/OniaTree_SingleMuGun_HydjetEmb_Run32021_3_100_merged.root"

#path to hltobj triggers file
TRIGGERFILEPATH="/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger//HLT/openHLT_DileptMu_JPsi_v1.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_DileptMu_JPsi_Embedded_v1.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_output_muonL3_legacy_PGHdj_highpt.root"
#TRIGGERFILEPATH="/eos/home-s/soohwan/junseok2/CMSSW_11_3_2/src/rootfiles/datasets/trigger/HLT/openHLT_DileptMu_Up_20211126_v1.root"
#for CMSSW_12_3_0_pre1 samples 
#path to reco file
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_Jpsi_CMSSW_11_3_2.root" 
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_DATA2018MBPD2_CMSSW_12_3_0.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_Upsilon_CMSSW_11_3_2_211122_v1.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_Jpsi_Embedded_CMSSW_12_3_0_pre1_20220312.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/Oniatree_UpsilonHydjet_EmbeddedSample_CMSSW_11_3_2_20220210.root"
#ONIAFILEPATH="../rootfiles/datasets/trigger/OniaTree_SingleMuGun_HydjetEmb_Run32021_3_100_merged.root"

#path to hltobj triggers file
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_DileptMu_JPsi_v1.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_HLTMU_121X_NewImpl_JPsiEMB.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_data2018_newUnstable.root"
#TRIGGERFILEPATH="/eos/home-s/soohwan/HLT-Dev_Run3/CMSSW_123X_build_v2/CMSSW_12_3_0/src/HLTrigger/Configuration/test/workstation/openHLT_Gmenu_JPsiEMB_v1230.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_DileptMu_Up_20211126_v1.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_DileptMu_Upsilon_Embedded_20220207_v1.root"
#TRIGGERFILEPATH="../rootfiles/datasets/trigger/HLT/openHLT_output_muonL3_legacy_PGHdj_highpt.root"

#path to directory to place output
#OUTPUTPATH="../rootfiles/analysis/Triggerstudy_JPsi_CMSSW_11_3_2_220427_v2"
#OUTPUTPATH="../rootfiles/analysis/Triggerstudy_data2018_CMSSW_12_3_0_220421_v5"
#OUTPUTPATH="/eos/home-s/soohwan/HLT-Dev_Run3/CMSSW_123X_build_v2/CMSSW_12_3_0/src/HLTrigger/Configuration/test/workstation/Gmenu_trig_eff"
#OUTPUTPATH="../rootfiles/analysis/Upsilon_20220210_test1"
#OUTPUTPATH="../rootfiles/analysis/SingleMu_legacy_PGHdj_highpt"
OUTPUTPATH="../rootfiles/analysis/test_JPsi"
#reco file is low pt or high pt : "lowpt" or "highpt"
PTRANGE="highpt"
#maximum number of cores/threads to use simultaneusly, one core/thread process one trigger
MAXJOBS=7
#type of particles ex) Y(1S)="Up", J/Psi="JPsi", same acceptance cut was applied except for Y(1S)
TYPE="JPsi"

./GetTriggersName $TRIGGERFILEPATH

#list of triggers to process, listed in file triggersLx.txt
TRIGGERSL1=$( cat triggersL1.txt )
TRIGGERSL2=$( cat triggersL2.txt )
TRIGGERSL3=$( cat triggersL3.txt )
TRIGGERS=( ${TRIGGERSL1[@]} ${TRIGGERSL2[@]} ${TRIGGERSL3[@]} )

OUTPUTDIR="${OUTPUTPATH}/$( basename ${ONIAFILEPATH%.*})"

mkdir -p ${OUTPUTDIR}

echo "Get RecoID/Gen True fficiency"
./Tools/getEfficiency_pure $ONIAFILEPATH $TYPE $OUTPUTDIR

echo "Full HLT Trigger efficiency study"

#do the processing

echo "processing..."
echo "reading reco file '${ONIAFILEPATH}'"
echo "reading hltobj file '${TRIGGERFILEPATH}'"
echo "output to:"
echo "  ${OUTPUTDIR}"

for TRIGGERNAME in ${TRIGGERS[@]}
do
    OUTPATH="${OUTPUTDIR}/${TRIGGERNAME}"
    mkdir -p $OUTPATH
    echo "processing ${TRIGGERNAME}"
    ./trigeff.sh ${ONIAFILEPATH} ${TRIGGERFILEPATH} ${TRIGGERNAME} $OUTPATH $PTRANGE $TYPE &> "${OUTPATH}/output.log"  &
    JOBS=( $(jobs -p) )
    JOBNUM="${#JOBS[@]}"
    if [ $MAXJOBS = $JOBNUM ]
    then
#        wait -n
	wait
    fi
done
wait

./PlotEff/ploteff "-multi" "${OUTPUTDIR}" $TRIGGERSL1 "${OUTPUTDIR}/triggersL1" 
./PlotEff/ploteff "-multi" "${OUTPUTDIR}" $TRIGGERSL2 "${OUTPUTDIR}/triggersL2"
./PlotEff/ploteff "-multi" "${OUTPUTDIR}" $TRIGGERSL3 "${OUTPUTDIR}/triggersL3"
mkdir "${OUTPUTDIR}/report"
cp "HelperScripts/exampleReport.tex" "${OUTPUTDIR}/report/presentation.tex"
cd "${OUTPUTDIR}/report"
pdflatex -interaction batchmode "presentation.tex"
echo "all done"
