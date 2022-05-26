import FWCore.ParameterSet.Config as cms

from Configuration.Generator.Pythia8CommonSettings_cfi import *
from Configuration.Generator.MCTunes2017.PythiaCP5Settings_cfi import *

generator = cms.EDFilter("Pythia8PtGun",

    maxEventsToPrint = cms.untracked.int32(1),
    pythiaPylistVerbosity = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(False),

    PGunParameters = cms.PSet(
      ParticleID = cms.vint32(13),
      MinPt = cms.double(0),
      MaxPt = cms.double(3.0),
      MinEta = cms.double(-2.5),
      MaxEta = cms.double(2.5),
      MinPhi = cms.double(-3.14159265359),
      MaxPhi = cms.double(3.14159265359),
      AddAntiParticle = cms.bool(True)
      ),

    PythiaParameters = cms.PSet(
      pythia8CommonSettingsBlock,
      pythia8CP5SettingsBlock,
      parameterSets = cms.vstring('pythia8CommonSettings',
        'pythia8CP5Settings',
        )
      )
    )

#muplusfilter = cms.EDFilter("MCSingleParticleFilter",
#    Status = cms.untracked.vint32(1,1),
#    MinPt = cms.untracked.vdouble(0.,0.),
#    MinEta = cms.untracked.vdouble(-1.5, -1.5),
#    MaxEta = cms.untracked.vdouble(1.5, 1.5),
#    ParticleID = cms.untracked.vint32(13,13),
#    )
#
#muminusfilter = cms.EDFilter("MCSingleParticleFilter",
#    Status = cms.untracked.vint32(1,1),
#    MinPt = cms.untracked.vdouble(0.5,0.5),
#    MinEta = cms.untracked.vdouble(-1.5, -1.5),
#    MaxEta = cms.untracked.vdouble(1.5, 1.5),
#    ParticleID = cms.untracked.vint32(-13,-13),
#    )
#
ProductionFilterSequence = cms.Sequence(generator)
