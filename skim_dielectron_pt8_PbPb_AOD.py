import FWCore.ParameterSet.Config as cms
process = cms.Process('SKIM')

process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.source = cms.Source ("PoolSource",
    fileNames = cms.untracked.vstring ('file:/afs/cern.ch/user/a/azsigmon/public/C4E70D58-8B99-E511-8353-02163E013523.root'),
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

import HLTrigger.HLTfilters.hltHighLevel_cfi
process.hltZEEHI = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltZEEHI.HLTPaths = ['HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_v*', 'HLT_HIDoublePhoton15_Eta1p5_Mass50_1000_R9HECut_v*', 'HLT_HIDoublePhoton15_Eta2p1_Mass50_1000_R9Cut_v*', 'HLT_HIDoublePhoton15_Eta2p5_Mass50_1000_R9SigmaHECut_v*']
process.hltZEEHI.throw = False
process.hltZEEHI.andOr = True

process.dielectronFilter = cms.EDFilter("PtMinGsfElectronCountFilter",
    src = cms.InputTag("gedGsfElectronsTmp"),
    ptMin = cms.double(8.0),
    minNumber = cms.uint32(2)
)

process.zEESkimSequence = cms.Sequence(
    process.hltZEEHI *
    process.dielectronFilter
)

process.filterstep = cms.Path(process.zEESkimSequence)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string ("Dielectron_Skim_pt8.root"),
    outputCommands = cms.untracked.vstring('keep *'),
    SelectEvents = cms.untracked.PSet(
         SelectEvents = cms.vstring(
             'filterstep')
    ),
)

process.outputstep = cms.EndPath(process.out)
