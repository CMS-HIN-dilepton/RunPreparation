import FWCore.ParameterSet.Config as cms
generator = cms.EDFilter("Pythia8PtGun",
      PGunParameters = cms.PSet(
         MinPt = cms.double(0.),
         MaxPt = cms.double(30.),
         ParticleID = cms.vint32(443),
         MaxEta = cms.double(2.5),
         MaxPhi = cms.double(3.14159265359),
         MinEta = cms.double(-2.5),
         MinPhi = cms.double(-3.14159265359), ## in radians
         AddAntiParticle = cms.bool(False)
         ),
      Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts
      psethack = cms.string('single jpsi pt 30'),
      firstRun = cms.untracked.uint32(1),
      PythiaParameters = cms.PSet(
         jpsiDecay = cms.vstring(
            '443:onMode = off',
            '443:onIfAny = 13',
            ),
         parameterSets = cms.vstring('jpsiDecay')
         )
      )
