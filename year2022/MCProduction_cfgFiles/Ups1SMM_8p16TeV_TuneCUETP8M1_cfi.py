import FWCore.ParameterSet.Config as cms
from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.Pythia8CUEP8M1Settings_cfi import *

generator = cms.EDFilter("Pythia8GeneratorFilter",
                         pythiaPylistVerbosity = cms.untracked.int32(0),
                         filterEfficiency = cms.untracked.double(0.109),
                         pythiaHepMCVerbosity = cms.untracked.bool(False),
                         crossSection = cms.untracked.double(1430000.0),
                         comEnergy = cms.double(8160.0),
                         maxEventsToPrint = cms.untracked.int32(0),
                         PythiaParameters = cms.PSet(
        pythia8CommonSettingsBlock,
        pythia8CUEP8M1SettingsBlock,
        processParameters = cms.vstring(
            'Bottomonium:states(3S1) = 553', # filter on 553 and prevents other onium states decaying to 553, so we should turn the others off
            'Bottomonium:all = on',
            'Bottomonium:O(3S1)[3S1(1)] = 9.28',
            'Bottomonium:O(3S1)[3S1(8)] = 0.15',
            'Bottomonium:O(3S1)[1S0(8)] = 0.02',
            'Bottomonium:O(3S1)[3P0(8)] = 0.02',
            '553:onMode = off',            # ignore cross-section re-weighting (CSAMODE=6) since selecting wanted decay mode
            '553:onIfAny = 13 -13',
            'PhaseSpace:pTHatMin = 2.',
            ),
        parameterSets = cms.vstring('pythia8CommonSettings',
                                    'pythia8CUEP8M1Settings',
                                    'processParameters',
                                    )
        )
)


# Next two muon filter are derived from muon reconstruction
oniafilter = cms.EDFilter("PythiaFilter",
    Status = cms.untracked.int32(2),
    MaxEta = cms.untracked.double(1000.0),
    MinEta = cms.untracked.double(-1000.0),
    MinPt = cms.untracked.double(0.0),
    MaxPt = cms.untracked.double(30.0),
    ParticleID = cms.untracked.int32(553)
)

mumugenfilter = cms.EDFilter("MCParticlePairFilter",
    Status = cms.untracked.vint32(1, 1),
    MinP = cms.untracked.vdouble(2.5, 2.5),
    MaxEta = cms.untracked.vdouble(2.5, 2.5),
    MinEta = cms.untracked.vdouble(-2.5, -2.5),
    ParticleCharge = cms.untracked.int32(-1),
    ParticleID1 = cms.untracked.vint32(13),
    ParticleID2 = cms.untracked.vint32(13),
    BetaBoost = cms.untracked.double(0.434)
)



ProductionFilterSequence = cms.Sequence(generator*oniafilter*mumugenfilter)
