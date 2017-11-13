import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing


#----------------------------------------------------------------------------

# Setup Settings for ONIA FOREST:

HLTProcess     = "HLT"    # Name of HLT process 
isMC           = True     # if input is MONTECARLO: True or if it's DATA: False
muonSelection  = "Trk"    # Single muon selection: Glb(isGlobal), GlbTrk(isGlobal&&isTracker), Trk(isTracker) are availale

triggerList    = {
    # Double Muon Trigger List
    'DoubleMuonTrigger' : cms.vstring(),
    # Double Muon Filter List
    'DoubleMuonFilter'  : cms.vstring(),
    # Double Muon Trigger List
    'SingleMuonTrigger' : cms.vstring(),
    # Single Muon Filter List
    'SingleMuonFilter'  : cms.vstring()
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
options.inputFiles = '/store/user/gsfs/Pythia8_JPsiGun_pp_5020GeV/RECO__201711010/171011_011033/0000/step3_pp_RAW2DIGI_L1Reco_RECO_1.root'
options.secondaryInputFiles = '/store/user/gsfs/Pythia8_JPsiGun_pp_5020GeV/RAW_20171010/171010_124128/0000/step2_pp_DIGI_L1_DIGI2RAW_HLT_1.root'
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
process.hltbitanalysis.HLTProcessName = HLTProcess
process.hltbitanalysis.hltresults = cms.InputTag("TriggerResults","",HLTProcess)
process.hltbitanalysis.l1tAlgBlkInputTag = cms.InputTag("hltGtStage2Digis","",HLTProcess)
process.hltbitanalysis.l1tExtBlkInputTag = cms.InputTag("hltGtStage2Digis","",HLTProcess)
process.hltbitanalysis.gObjectMapRecord  = cms.InputTag("hltGtStage2ObjectMap","",HLTProcess)
process.hltbitanalysis.RunParameters.HistogramFile = cms.untracked.string(options.outputFile)
process.hltbitanalysis.RunParameters.isData = cms.untracked.bool(not isMC)
process.hltbitanalysis.RunParameters.Monte = cms.bool(isMC)
process.hltbitanalysis.RunParameters.GenTracks = cms.bool(False)
process.hltbitanalysis.RunParameters.UseL1Stage2 = cms.bool(True)
process.hltbitanalysis.UseTFileService = cms.untracked.bool(True)
process.hltBitAna = cms.EndPath(process.hltbitanalysis)
if (HLTProcess == "HLT") :
    process.hltbitanalysis.l1tAlgBlkInputTag = cms.InputTag("gtStage2Digis","","RECO")
    process.hltbitanalysis.l1tExtBlkInputTag = cms.InputTag("gtStage2Digis","","RECO")
    process.hltbitanalysis.gObjectMapRecord  = cms.InputTag("gtStage2ObjectMap","","RECO")
    process.hltbitanalysis.gmtStage2Digis    = cms.string("gmtStage2Digis")
    process.hltbitanalysis.caloStage2Digis   = cms.string("caloStage2Digis")

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
process.source    = cms.Source("PoolSource",
                               fileNames = cms.untracked.vstring( options.inputFiles ),
                               secondaryFileNames = cms.untracked.vstring( options.secondaryInputFiles )
                               )
process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string( options.outputFile )
                                   )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.schedule = cms.Schedule( process.oniaTreeAna , process.hltBitAna , process.hltObjectAna )
