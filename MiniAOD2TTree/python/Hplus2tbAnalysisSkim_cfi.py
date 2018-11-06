import FWCore.ParameterSet.Config as cms

skim = cms.EDFilter("Hplus2tbAnalysisSkim",
    Verbose        = cms.bool(False),
    TriggerResults = cms.InputTag("TriggerResults::HLT"),
    HLTPaths       = cms.vstring(
        "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_v",
        "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0_v",
        "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_v",
        "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_v",
        "HLT_PFHT380_SixPFJet32_v",
        "HLT_PFHT430_SixJet40_BTagCSV_p080_v",
        "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_v",
        "HLT_PFHT430_SixPFJet40_v",
        "HLT_PFHT350_v",
        "HLT_PFHT250_v",
        "HLT_PFHT370_v",
        "HLT_PFHT430_v",
        "HLT_PFHT380_SixJet32_v",
        "HLT_PFHT430_SixJet40_v",
        "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1_v",
        "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1_v",
        "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1_v",
        "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1_v",
        "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2_v",
        "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2_v",
        "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2_v",
        "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2_v",
        "HLT_QuadPFJet98_83_71_15_v",
        "HLT_QuadPFJet103_88_75_15_v",
        "HLT_QuadPFJet105_88_76_15_v",
        "HLT_QuadPFJet111_90_80_15_v",
        "HLT_PFHT1050_v",
        "HLT_PFJet500_v",
        ),
    # Jets (https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_13_TeV_data)
    JetCollection  = cms.InputTag("slimmedJets"),
    JetUserFloats  = cms.vstring(
	"pileupJetId:fullDiscriminant", #currently disabled
    ),
    JetEtCut       = cms.double(20.0),
    JetEtaCut      = cms.double(2.4),
    NJets          = cms.int32(0),
       
    # PF Candidates
    PackedCandidatesCollection = cms.InputTag("packedPFCandidates"),
                    
    # Vertex
    VertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices"),

    # Electrons (https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedElectronIdentificationRun2)
    ElectronCollection   = cms.InputTag("slimmedElectrons"),
    ElectronID           = cms.string("cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
    ElectronMVA          = cms.InputTag("electronMVAValueMapProducer:ElectronMVAEstimatorRun2Spring16GeneralPurposeV1Values"),
    ElectronRhoSource    = cms.InputTag("fixedGridRhoFastjetCentralNeutral"),
    ElectronMiniRelIsoEA = cms.double(0.2), # MIT cut is at 0.40. Allow wiggle room by cutting at LOWER value
    ElectronPtCut        = cms.double(10.0),
    ElectronEtaCut       = cms.double(2.1),
    ElectronNCut         = cms.int32(0),

    # Muons (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2)
    MuonCollection   = cms.InputTag("slimmedMuons"),
    MuonID           = cms.string("Loose"),
    MuonMiniRelIsoEA = cms.double(0.2),  # MIT cut is at 0.40. Allow wiggle room by cutting at LOWER value
    MuonPtCut        = cms.double(10.0),
    MuonEtaCut       = cms.double(2.4),
    MuonNCut         = cms.int32(0),

    # Taus
    TauCollection     = cms.InputTag("slimmedTaus"),
    TauDiscriminators = cms.vstring(
        "decayModeFinding",
        "byVLooseIsolationMVArun2v1DBoldDMwLT",
        ),
    TauPtCut  = cms.double(20),
    TauEtaCut = cms.double(2.3),
    TauNCut   = cms.int32(999),

)
