import FWCore.ParameterSet.Config as cms

from HiggsAnalysis.Validation.TriggerTauValidation_cfi import *

L2TauMET = TriggerTauValidation.clone()
L2TauMET.hltPathFilter = cms.InputTag("hltFilterL2TauMET25","","REDIGI39X")
#L2TauMET.hltPathFilter = cms.InputTag("hltFilterL2TauMET25")

L3TauMET = TriggerTauValidation.clone()
L3TauMET.hltPathFilter = cms.InputTag("hltFilterL3TrackIsolationSingleIsoTau20Trk15MET25","","REDIGI39X")
#L3TauMET.hltPathFilter = cms.InputTag("hltFilterL3TrackIsolationSingleIsoTau35Trk15MET25")

L3TauMETnoHLTFilter = TriggerTauValidation.clone()
L3TauMETnoHLTFilter.hltPathFilter = cms.InputTag("hltFilterL3TrackIsolationSingleIsoTau20Trk15MET25","","REDIGI39X")
L3TauMETnoHLTFilter.triggerBit = cms.string("")

TriggerValidation = cms.Sequence(
    L2TauMET *
    L3TauMET *
    L3TauMETnoHLTFilter
#    TriggerTauValidation
)
