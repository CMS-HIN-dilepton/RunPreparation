import FWCore.ParameterSet.Config as cms
import FWCore.ParameterSet.VarParsing as VarParsing


#----------------------------------------------------------------------------

# Setup Settings for ONIA FOREST:

HLTProcess     = "HLT"    # Name of HLT process 
#isMC           = True     # if input is MONTECARLO: True or if it's DATA: False
isMC           = False     # if input is MONTECARLO: True or if it's DATA: False
muonSelection  = "Trk"    # Single muon selection: Glb(isGlobal), GlbTrk(isGlobal&&isTracker), Trk(isTracker) are availale

triggerList    = {
    # Double Muon Trigger List
    'DoubleMuonTrigger' : cms.vstring(),
    # Double Muon Filter List
    'DoubleMuonFilter'  : cms.vstring(),
    # Double Muon Trigger List
    'SingleMuonTrigger' : cms.vstring(),
    # Single Muon Filter List
    'SingleMuonFilter'  : cms.vstring(),
    }

if isMC:
#    globalTag = 'auto:run2_mc'
	globalTag = 'phase1_2017_realistic'
else:
#    globalTag = 'auto:run2_hlt'
    globalTag = 'auto:run2_data_promptlike'

#----------------------------------------------------------------------------


# set up process
process = cms.Process("TriggerAnalysis")

# setup 'analysis'  options
options = VarParsing.VarParsing ('analysis')

# Input and Output File Names
options.outputFile = "OniaForest.root"
options.secondaryOutputFile = "Jpsi_DataSet.root"
#options.inputFiles =  'file:/afs/cern.ch/work/e/echapon/public/RunPrep2017/step3_gunJpsi_RAW2DIGI_L1Reco_RECO.root'
#options.inputFiles =  '/store/data/Run2017C/DoubleMuon/AOD/PromptReco-v2/000/300/079/00000/60A3189C-1477-E711-94A8-02163E01A54D.root'
options.inputFiles =  '/store/data/Run2017C/SingleMuon/AOD/PromptReco-v2/000/300/079/00000/56C762D5-0877-E711-9CE2-02163E0141C5.root'
#options.inputFiles = '/store/relval/CMSSW_9_2_12/RelValZMM_13/GEN-SIM-RECO/PU25ns_92X_upgrade2017_realistic_v11-v1/00000/32D2F2F0-E59D-E711-BCFF-0025905B85DE.root'
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
                               fileNames = cms.untracked.vstring( options.inputFiles )
                               )
process.TFileService = cms.Service("TFileService", 
                                   fileName = cms.string( options.outputFile )
                                   )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.maxEvents) )
process.options   = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.schedule  = cms.Schedule( process.oniaTreeAna , process.hltBitAna , process.hltObjectAna )
