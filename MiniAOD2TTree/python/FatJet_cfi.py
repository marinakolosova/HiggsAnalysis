#=======x=========================================================================================
# Import modules
#================================================================================================
import FWCore.ParameterSet.Config as cms

AK8Jets = cms.PSet(
    branchname = cms.untracked.string("AK8Jets"),
    src        = cms.InputTag("selectedPatJetsAK8PFCHS"),
    subjetsrc  = cms.InputTag("selectedPatJetsAK8PFCHSSoftDropPacked"),
    systVariations = cms.bool(False), # bug => requires fix!
    srcJESup   = cms.InputTag("shiftedPatJetEnUp"),
    srcJESdown = cms.InputTag("shiftedPatJetEnDown"),
    srcJERup   = cms.InputTag("shiftedPatSmearedJetResUp"),
    srcJERdown = cms.InputTag("shiftedPatSmearedJetResDown"),
    discriminators = cms.vstring(
        "pfCombinedInclusiveSecondaryVertexV2BJetTags",
        "pfBoostedDoubleSecondaryVertexAK8BJetTags",
        "pfDeepCSVJetTags:probb",
        "pfDeepCSVJetTags:probc",
        "pfDeepCSVJetTags:probudsg",
        "pfDeepCSVJetTags:probbb",
        "pfDeepCSVJetTags:probcc",
        ),
    userFloats = cms.vstring(
        "NjettinessAK8CHS:tau1",
        "NjettinessAK8CHS:tau2",
        "NjettinessAK8CHS:tau3",
        "NjettinessAK8CHS:tau4",
        "ak8PFJetsCHSECF:ecf1",
        "ak8PFJetsCHSECF:ecf2",
        "ak8PFJetsCHSECF:ecf3",
        "ak8PFJetsCHSFilteredMass",
        "ak8PFJetsCHSPrunedMass",
        "ak8PFJetsCHSSoftDropMass",
        "ak8PFJetsCHSTrimmedMass"
        ),
    userInts = cms.vstring(
        ),
    mcjecPath   = cms.untracked.string("jec/Summer16_23Sep2016V4"),
    datajecPath = cms.untracked.string("jec/Summer16_23Sep2016BCDV4"), 
    rho         = cms.InputTag("fixedGridRhoFastjetAll"),
    vertices    = cms.InputTag("offlineSlimmedPrimaryVertices"),
    PUMitigationTool = cms.string("CHS"),
    fillPFCands = cms.bool(False),
)

AK8PuppiJets = cms.PSet(
    branchname = cms.untracked.string("AK8PuppiJets"),
    src        = cms.InputTag("selectedPatJetsAK8PFPuppi"),
    subjetsrc  = cms.InputTag("selectedPatJetsAK8PFPuppiSoftDropPacked"),
    systVariations = cms.bool(False), # bug => requires fix! 
    srcJESup   = cms.InputTag("shiftedPatJetEnUp"),
    srcJESdown = cms.InputTag("shiftedPatJetEnDown"),
    srcJERup   = cms.InputTag("shiftedPatSmearedJetResUp"),
    srcJERdown = cms.InputTag("shiftedPatSmearedJetResDown"),
    discriminators = cms.vstring(
        "pfCombinedInclusiveSecondaryVertexV2BJetTags",
        "pfBoostedDoubleSecondaryVertexAK8BJetTags",
        "pfDeepCSVJetTags:probb",
        "pfDeepCSVJetTags:probc",
        "pfDeepCSVJetTags:probudsg",
        "pfDeepCSVJetTags:probbb",
        "pfDeepCSVJetTags:probcc",
        ),
    userFloats = cms.vstring(
        "ak8PFJetsPuppiSoftDropMass",
        "ak8PFJetsPuppiPrunedMass",
        "ak8PFJetsPuppiTrimmedMass",
        "ak8PFJetsPuppiFilteredMass",
        "NjettinessAK8Puppi:tau1",
        "NjettinessAK8Puppi:tau2",
        "NjettinessAK8Puppi:tau3",
        "NjettinessAK8Puppi:tau4",
        "ak8PFJetsPuppiECF:ecf1",
        "ak8PFJetsPuppiECF:ecf2",
        ),
    userInts = cms.vstring(
        ),
    mcjecPath   = cms.untracked.string("jec/Summer16_23Sep2016V4"),
    datajecPath = cms.untracked.string("jec/Summer16_23Sep2016BCDV4"),
    rho         = cms.InputTag("fixedGridRhoFastjetAll"),
    vertices    = cms.InputTag("offlineSlimmedPrimaryVertices"),
    PUMitigationTool = cms.string("Puppi"),
    fillPFCands = cms.bool(False),
)

FatJets = cms.VPSet()
FatJets.append(AK8Jets)
#FatJets.append(AK8PuppiJets)

FatJetsNoSysVariations = cms.VPSet()
for i in range(len(FatJets)):
    pset = FatJets[i].clone()
    pset.systVariations = cms.bool(False)
    FatJetsNoSysVariations.append(pset)
