from WMCore.Configuration import Configuration

config = Configuration()

config.section_("General")
config.General.requestName   = 'skim_SingleMuonHighPt_part2_v1'
config.General.transferLogs = True

config.section_("JobType")
config.JobType.pluginName  = 'Analysis'
config.JobType.psetName    = 'skim_dimuon_mass_40_AOD.py'
#config.JobType.psetName    = 'skim_dielectron_pt8_AOD.py'

config.section_("Data")
config.Data.inputDataset = '/SingleMuHighPt/Run2015E-PromptReco-v1/AOD'
#config.Data.inputDataset = '/HighPtPhoton30AndZ/Run2015E-PromptReco-v1/AOD'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 5
#config.Data.lumiMask = 'json_pp_262163-262273.txt'
config.Data.lumiMask = 'json_pp_262274-262328.txt'
config.Data.publication = True
#config.Data.outputDatasetTag = 'Run2015E-PromptReco-AOD-DimuonSkim-Mass40-262163-262273-v1'
#config.Data.outputDatasetTag = 'Run2015E-PromptReco-AOD-DielectronSkim-262163-262273-v1'
#config.Data.outputDatasetTag = 'Run2015E-PromptReco-AOD-DielectronSkim-262274-262328-v1'
config.Data.outputDatasetTag = 'Run2015E-PromptReco-AOD-DimuonSkim-Mass40-262274-262328-v1'

config.section_('Site')
config.Site.storageSite = 'T2_HU_Budapest'
