# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: openHLT --python_file openHLT.py --data --era Run2_2016 --geometry=Extended2016,Extended2016Reco --process reHLT --conditions=auto:run2_hlt --step L1REPACK:Full,HLT:PIon --no_exec -n 5
import FWCore.ParameterSet.Config as cms

from Configuration.StandardSequences.Eras import eras

process = cms.Process('reHLT',eras.Run2_2016)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2016Reco_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.SimL1EmulatorRepack_Full_cff')
process.load('HLTrigger.Configuration.HLT_PIon_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(5)
)

# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/data/Run2016D/DoubleMuon/RAW/v2/000/276/807/00000/505AE997-924A-E611-96CA-02163E0128A1.root'),
    secondaryFileNames = cms.untracked.vstring()
)

process.options = cms.untracked.PSet(

)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('openHLT nevts:5'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    fileName = cms.untracked.string('openHLT_L1REPACK_HLT.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_hlt', '')

# Path and EndPath definitions
process.L1RePack_step = cms.Path(process.SimL1Emulator)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

# override the GlobalTag's L1T menu from an Xml file
from HLTrigger.Configuration.CustomConfigs import L1XML
process = L1XML(process,"L1Menu_HeavyIons2016_v0_CHARGEFIXED.xml")

# Schedule definition
process.schedule = cms.Schedule(process.L1RePack_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.RECOSIMoutput_step])

process.load("HLTrigger.HLTanalyzers.HLTAnalyser_cfi")
process.hltanalysis.RunParameters.HistogramFile = cms.untracked.string("openHLT.root")
process.hltanalysis.gObjectMapRecord = cms.InputTag( 'hltGtStage2ObjectMap','','reHLT' )
process.hltanalysis.hltresults = cms.InputTag( 'TriggerResults','','reHLT')
process.hltanalysis.HLTProcessName = cms.string('reHLT')
process.hltanalysis.muonFilters = cms.VInputTag(
    cms.InputTag("hltL1sDoubleMu0BptxAND",""),                            # 0
    cms.InputTag("hltL1sDoubleMu0MassGT1BptxAND",""),                     # 1
    cms.InputTag("hltL1sDoubleMu10BptxAND",""),                           # 2
    cms.InputTag("hltL1sDoubleMuOpenOSBptxAND",""),                       # 3
    cms.InputTag("hltL1sDoubleMuOpenSSBptxAND",""),                       # 4
    cms.InputTag("hltL1sDoubleMuOpenBptxAND",""),                         # 5
    cms.InputTag("hltL1sSingleMu3BptxAND",""),                            # 6
    cms.InputTag("hltL1sSingleMu5BptxAND",""),                            # 7
    cms.InputTag("hltL1sSingleMu7BptxAND",""),                            # 8
    cms.InputTag("hltL1fL1sDoubleMuOpenBptxANDL1Filtered0",""),           # 10
    cms.InputTag("hltL2fL1sDoubleMuOpenBptxANDL1f0L2Filtered0",""),       # 11
    cms.InputTag("hltL3fL1sDoubleMuOpenBptxANDL1f0L2f0L3Filtered0",""),   # 12
    );
process.hltanalysis.muon = cms.InputTag("muons")
process.hltanalysis.caloStage2Digis = cms.string("hltCaloStage2Digis")
process.hltanalysis.gmtStage2Digis = cms.string("hltGmtStage2Digis")
process.hltanalysis.MuCandTag2 = cms.InputTag("hltL2MuonCandidates")
process.hltanalysis.MuCandTag3 = cms.InputTag("hltL3MuonCandidates")
process.hltanalysis.L3TkTracksFromL2OIStateTag = cms.InputTag("hltL3TkTracksFromL2OIState")
process.hltanalysis.L3TkTracksFromL2OIHitTag = cms.InputTag("hltL3TkTracksFromL2OIHit")
process.hltanalysis.UseTFileService = cms.untracked.bool(True)
process.hltAnalysis = cms.EndPath(
    process.HLTL1UnpackerSequence +    # L1 Objects
    process.HLTL2muonrecoSequence +    # L2 Muons
    process.HLTL3muonrecoSequence +    # L3 Muons
    process.hltanalysis
    )
process.TFileService = cms.Service("TFileService", fileName=cms.string("openHLT.root"))

from PhysicsTools.PatAlgos.tools.helpers import massSearchReplaceAnyInputTag, cloneProcessingSnippet
cloneProcessingSnippet(process, process.hltAnalysis, "UNPACK")
massSearchReplaceAnyInputTag(process.hltAnalysisUNPACK,"rawDataCollector","rawDataCollector::LHC")
process.hltanalysisUNPACK.hltresults = cms.InputTag( 'TriggerResults','','HLT')
process.hltanalysisUNPACK.HLTProcessName = cms.string('HLT')
process.hltanalysisUNPACK.caloStage2Digis = cms.string("hltCaloStage2DigisUNPACK")
process.hltanalysisUNPACK.gmtStage2Digis = cms.string("hltGmtStage2DigisUNPACK")
process.hltAnalysisUNPACKED = cms.EndPath(process.hltAnalysisUNPACK)

process.HLTL1UnpackerSequence.replace(process.hltGtStage2Digis, process.hltGtStage2DigisUNPACK*process.hltGtStage2Digis)
process.hltGtStage2ObjectMap.ExtInputTag = cms.InputTag("hltGtStage2DigisUNPACK")

process.schedule = cms.Schedule(process.L1RePack_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step, process.hltAnalysis, process.hltAnalysisUNPACKED])



