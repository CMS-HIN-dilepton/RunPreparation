import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing


#----------------------------------------------------------------------------

# Setup Settings for ONIA FOREST:

HLTProcess     = "MYHLT"    # Name of HLT process 
isMC           = True     # if input is MONTECARLO: True or if it's DATA: False
muonSelection  = "Trk"    # Single muon selection: Glb(isGlobal), GlbTrk(isGlobal&&isTracker), Trk(isTracker) are availale

triggerList    = {
    # Double Muon Trigger List
    'DoubleMuonTrigger' : cms.vstring(
        "HLT_HIL1DoubleMuOpen_v1",
        "HLT_HIL1DoubleMuOpen_OS_v1",
        "HLT_HIL1DoubleMuOpen_SS_v1",
        "HLT_HIL1DoubleMu0_v1",
        "HLT_HIL1DoubleMu0_HighQ_v1",
        "HLT_HIL1DoubleMu10_v1",
        "HLT_HIL2DoubleMu0_v1",
        "HLT_HIL2DoubleMu10_v1",
        "HLT_HIL3DoubleMu0_v1",
        "HLT_HIL3DoubleMu10_v1",
        ),
    # Double Muon Filter List
    'DoubleMuonFilter'  : cms.vstring(
        "hltL1fL1sDoubleMuOpenL1Filtered0",
        "hltL1fL1sDoubleMuOpenOSL1Filtered0",
        "hltL1fL1sDoubleMuOpenSSL1Filtered0",
        "hltL1fL1sDoubleMu0L1Filtered0",
        "hltL1fL1sDoubleMu0L1HighQFiltered0",
        "hltL1fL1sDoubleMu10L1Filtered0",
        "hltL2fL1sDoubleMu0L1f0L2Filtered0",
        "hltL2fL1sDoubleMu10L1f0L2Filtered10",
        "hltL3fL1sDoubleMu0L1f0L2f0L3Filtered0",
        "hltL3fL1sDoubleMu10L1f0L2f0L3Filtered10",
        ),
    # Double Muon Trigger List
    'SingleMuonTrigger' : cms.vstring(
        "HLT_HIL1Mu3_v1",
        "HLT_HIL1Mu5_v1",
        "HLT_HIL1Mu7_v1",
        "HLT_HIL1Mu12_v1",
        "HLT_HIL1Mu16_v1",
        "HLT_HIL2Mu3_v1",
        "HLT_HIL2Mu3_NHitQ10_v1",
        "HLT_HIL2Mu5_v1",
        "HLT_HIL2Mu5_NHitQ10_v1",
        "HLT_HIL2Mu7_v1",
        "HLT_HIL2Mu12_v1",
        "HLT_HIL2Mu15_v1",
        "HLT_HIL2Mu20_v1",
        "HLT_HIL3Mu3_v1",
        "HLT_HIL3Mu3_NHitQ10_v1",
        "HLT_HIL3Mu5_v1",
        "HLT_HIL3Mu5_NHitQ10_v1",
        "HLT_HIL3Mu7_v1",
        "HLT_HIL3Mu12_v1",
        "HLT_HIL3Mu15_v1",
        "HLT_HIL3Mu20_v1",
        "HLT_HIL3Mu3_Track1_Jpsi_v1",
        "HLT_HIL3Mu5_Track1_Jpsi_v1",
        "HLT_HIL3Mu3_Track1_v1",
        "HLT_HIL3Mu5_Track1_v1",
        ),
    # Single Muon Filter List
    'SingleMuonFilter'  : cms.vstring(
        "hltL1fL1sSingleMu3L1Filtered0",
        "hltL1fL1sSingleMu5L1Filtered0",
        "hltL1fL1sSingleMu7L1Filtered0",
        "hltL1fL1sSingleMu12L1Filtered0",
        "hltL1fL1sSingleMu16L1Filtered0",
        "hltL2fL1sSingleMu3L1f0L2Filtered3",
        "hltL2fL1sSingleMu3L1f0L2NHitQ10L2Filtered3",
        "hltL2fL1sSingleMu3OR5L1f0L2Filtered5",
        "hltL2fL1sSingleMu3OR5L1f0L2NHitQ10L2Filtered5",
        "hltL2fL1sSingleMu3OR5L1f0L2Filtered7",
        "hltL2fL1sSingleMu7L1f0L2Filtered12",
        "hltL2fL1sSingleMu7L1f0L2Filtered15",
        "hltL2fL1sSingleMu7L1f0L2Filtered20",
        "hltL3fL1sSingleMu3L1f0L2f0L3Filtered3",
        "hltL3fL1sSingleMu3L1f0L2f0L3NHitQ10L3Filtered3",
        "hltL3fL1sSingleMu3OR5L1f0L2f0L3Filtered5",
        "hltL3fL1sSingleMu3OR5L1f0L2f0L3NHitQ10L3Filtered5",
        "hltL3fL1sSingleMu3OR5L1f0L2f0L3Filtered7",
        "hltL3fL1sSingleMu7L1f0L2f0L3Filtered12",
        "hltL3fL1sSingleMu7L1f0L2f0L3Filtered15",
        "hltL3fL1sSingleMu7L1f0L2f0L3Filtered20",
        "hltMu3Track1JpsiTrackMassFiltered",
        "hltMu5Track1JpsiTrackMassFiltered",
        "hltMu3Track1MassFiltered0",
        "hltMu5Track1MassFiltered0",
        )
    }

if isMC:
    globalTag = '92X_upgrade2017_realistic_v11'
else:
    globalTag = '92X_dataRun2_PromptLike_v5'

#----------------------------------------------------------------------------


# set up process
process = cms.Process("TriggerAnalysis")

# setup 'analysis'  options
options = VarParsing.VarParsing ('analysis')

# Input and Output File Names
options.outputFile = "OniaForest.root"
options.secondaryOutputFile = "Jpsi_DataSet.root"
options.inputFiles = 'file:step3_PAHLT.root'
options.maxEvents = -1 # -1 means all events

# Get and parse the command line arguments
options.parseArguments()

# load the Geometry and Magnetic Field
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.MagneticField_cff")
process.load('Configuration.StandardSequences.Reconstruction_cff')

# Global Tag:
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, globalTag, '')

#----------------------------------------------------------------------------

# For OniaTree Analyzer
from HiAnalysis.HiOnia.oniaTreeAnalyzer_cff import oniaTreeAnalyzer
oniaTreeAnalyzer(process, muonTriggerList=triggerList, HLTProName=HLTProcess, muonSelection=muonSelection, useL1Stage2=True, isMC=isMC, outputFileName=options.outputFile)

#----------------------------------------------------------------------------

# For HLTBitAnalyzer
process.load("HLTrigger.HLTanalyzers.HLTBitAnalyser_cfi")
process.hltbitanalysis.HLTProcessName              = HLTProcess
process.hltbitanalysis.hltresults                  = cms.InputTag("TriggerResults","",HLTProcess)
process.hltbitanalysis.l1tAlgBlkInputTag           = cms.InputTag("hltGtStage2Digis","",HLTProcess)
process.hltbitanalysis.l1tExtBlkInputTag           = cms.InputTag("hltGtStage2Digis","",HLTProcess)
process.hltbitanalysis.gObjectMapRecord            = cms.InputTag("hltGtStage2ObjectMap","",HLTProcess)
process.hltbitanalysis.gmtStage2Digis              = cms.string("hltGtStage2Digis")
process.hltbitanalysis.caloStage2Digis             = cms.string("hltGtStage2Digis")
process.hltbitanalysis.UseL1Stage2                 = cms.untracked.bool(True)
process.hltbitanalysis.getPrescales                = cms.untracked.bool(False)
process.hltbitanalysis.getL1InfoFromEventSetup     = cms.untracked.bool(False)
process.hltbitanalysis.UseTFileService             = cms.untracked.bool(True)
process.hltbitanalysis.RunParameters.HistogramFile = cms.untracked.string(options.outputFile)
process.hltbitanalysis.RunParameters.isData        = cms.untracked.bool(not isMC)
process.hltbitanalysis.RunParameters.Monte         = cms.bool(isMC)
process.hltbitanalysis.RunParameters.GenTracks     = cms.bool(False)
process.hltBitAna = cms.EndPath(process.hltbitanalysis)
if (HLTProcess == "HLT") :
    process.hltbitanalysis.l1tAlgBlkInputTag = cms.InputTag("gtStage2Digis","","RECO")
    process.hltbitanalysis.l1tExtBlkInputTag = cms.InputTag("gtStage2Digis","","RECO")
    process.hltbitanalysis.gmtStage2Digis    = cms.string("gtStage2Digis")
    process.hltbitanalysis.caloStage2Digis   = cms.string("gtStage2Digis")

#----------------------------------------------------------------------------

# For HLTObject Analyzer
process.load("HeavyIonsAnalysis.EventAnalysis.hltobject_cfi")
process.hltobject.processName = cms.string(HLTProcess)
process.hltobject.treeName = cms.string(options.outputFile)
process.hltobject.loadTriggersFromHLT = cms.untracked.bool(False)
process.hltobject.triggerNames = triggerList['DoubleMuonTrigger'] + triggerList['SingleMuonTrigger']
process.hltobject.triggerResults = cms.InputTag("TriggerResults","",HLTProcess)
process.hltobject.triggerEvent   = cms.InputTag("hltTriggerSummaryAOD","",HLTProcess)
process.hltObjectAna = cms.EndPath(process.hltobject)

#----------------------------------------------------------------------------

#Options:
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring( options.inputFiles ),
                            )
process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string( options.outputFile )
                                   )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.schedule  = cms.Schedule( process.oniaTreeAna , process.hltBitAna , process.hltObjectAna )
