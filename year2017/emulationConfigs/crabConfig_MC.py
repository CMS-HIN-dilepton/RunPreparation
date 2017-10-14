#file path will be:
#outLFNDirBase/inputDataset/requestName/time_tag/...
from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.requestName = '2017pp502_muHLTemulation_20171013'
#config.General.workArea = 'crab_projects'
config.JobType.psetName = 'hlt92X_MC.py'
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['rssLimit']
#config.JobType.pyCfgParams = ['noprint']
#config.JobType.outputFiles = ['.root']
config.JobType.numCores = 4
config.Data.inputDataset = '/Pythia8_PrJPsi_pp_CUETP8M1_5020GeV/gsfs-RECO__201711010-b3ceaa6c7c762fab18b245ad1faf35c4/USER'
config.Data.useParent = True
config.Data.totalUnits = -1
config.Data.unitsPerJob = 3000
#config.Data.totalUnits = 300
#config.Data.unitsPerJob = 100
config.Data.splitting = 'EventAwareLumiBased'
config.Data.inputDBS = 'phys03'
config.Data.publication = True
config.Data.outLFNDirBase = '/store/user/twang/2017pp502HLTemulation'
config.Site.storageSite = 'T2_US_MIT'
#config.Data.outLFNDirBase = '/store/group/phys_heavyions/HeavyFlavourRun2/'
#config.Data.outLFNDirBase = '/store/user/twang/2017pp502HLTemulation'
#config.Site.storageSite = 'T2_CH_CERN'
#config.Site.whitelist = ['T2_US_MIT']
#config.Data.allowNonValidInputDataset = True
