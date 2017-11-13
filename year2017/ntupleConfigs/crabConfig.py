#file path will be:
#outLFNDirBase/inputDataset/requestName/time_tag/...
from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.requestName = '2017pp502_Onia_20171031'

config.General.workArea = 'crab_projects_PrJPsi_pp'
#config.General.workArea = 'crab_projects_NonPrJPsi_pp'
#config.General.workArea = 'crab_projects_JPsiGun_pp'
#config.General.workArea = 'crab_projects_MuGun_pp'
#config.General.workArea = 'crab_projects_Zm10m10_pp'

config.JobType.psetName = 'hiOniaForest_PPRef_92X_MC_cfg.py'
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['rssLimit']
#config.JobType.pyCfgParams = ['noprint']
#config.JobType.outputFiles = ['.root']
#config.JobType.numCores = 4
config.JobType.maxMemoryMB = 4000

config.Data.inputDataset = '/Pythia8_PrJPsi_pp_CUETP8M1_5020GeV/twang-crab_2017pp502_muHLTemulation_20171025-e4ed28ee23e9818f2ed2dda59a3e4582/USER'
#config.Data.inputDataset = '/Pythia8_NonPrJPsi_pp_CUETP8M1_5020GeV/twang-crab_2017pp502_muHLTemulation_20171025-e4ed28ee23e9818f2ed2dda59a3e4582/USER'
#config.Data.inputDataset = '/Pythia8_JPsiGun_pp_5020GeV/twang-crab_2017pp502_muHLTemulation_20171025-e4ed28ee23e9818f2ed2dda59a3e4582/USER'
#config.Data.inputDataset = '/Pythia8_MuGun_pp_5020GeV/twang-crab_2017pp502_muHLTemulation_20171025-e4ed28ee23e9818f2ed2dda59a3e4582/USER'
#config.Data.inputDataset = '/Pythia8_Zm10m10_pp_CUETP8M1_5020GeV/twang-crab_2017pp502_muHLTemulation_20171025-e4ed28ee23e9818f2ed2dda59a3e4582/USER'

#config.Data.useParent = True
config.Data.totalUnits = -1
config.Data.unitsPerJob = 10000
config.Data.splitting = 'EventAwareLumiBased'
config.Data.inputDBS = 'phys03'
#config.Data.publication = True
#config.Data.outLFNDirBase = '/store/user/twang/2017pp502HLTemulation'
#config.Site.storageSite = 'T2_US_MIT'
#config.Data.outLFNDirBase = '/store/group/phys_heavyions/HeavyFlavourRun2/'
config.Data.outLFNDirBase = '/store/user/twang/2017pp502Onia'
config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T2_US_MIT']
#config.Data.allowNonValidInputDataset = True
