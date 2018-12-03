// -*- c++ -*-
#include "Framework/interface/BaseSelector.h"
#include "Framework/interface/makeTH.h"

#include "EventSelection/interface/CommonPlots.h"
#include "EventSelection/interface/EventSelections.h"

#include "TDirectory.h"

class JetTriggersSF: public BaseSelector {
public:
  explicit JetTriggersSF(const ParameterSet& config, const TH1* skimCounters);
  virtual ~JetTriggersSF();

  /// Books histograms
  virtual void book(TDirectory *dir) override;
  /// Sets up branches for reading the TTree
  virtual void setupBranches(BranchManager& branchManager) override;
  /// Called for each event
  virtual void process(Long64_t entry) override;

  double DeltaEta(double eta1, double eta2);
  double DeltaPhi(double phi1, double phi2);

  double DeltaR(double eta1, double eta2,
		double phi1, double phi2);
    
private:
  // Common plots
  CommonPlots fCommonPlots;
  
  // Event selection classes and event counters (in same order like they are applied)
  Count cAllEvents;
  Count cControlTrigger; 
  METFilterSelection fMETFilterSelection;
  Count cVertexSelection;
  ElectronSelection fElectronSelection;
  MuonSelection fMuonSelection;
  TauSelection fTauSelection;
  JetSelection fJetSelection;
  BJetSelection fBJetSelection;
  Count cBTaggingSFCounter;
  METSelection fMETSelection;
  TopSelectionBDT fTopSelection;
  Count cSelected;
  
  Count cTrigger_1BTagCSV;     // (HLT_PFHT430_SixJet40_BTagCSV_p080 || HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5)
  Count cTrigger_2BTagCSV;     // (HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2 || HLT_PFHT380_SixJet32_DoubleBTagCSV_p075) 
  Count cTrigger_2BTagDeepCSV; // (HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2)
  Count cTrigger_3BTagCSV;     // (HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0 || HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07)
  Count cTrigger_OR;           //  OR of all the above triggers (without DoubleDeepCSV)
  Count cTrigger_ORwDeepCSV;   //  OR of all the above triggers (with DoubleDeepCSV)
  Count cTrigger_OR_PFJet500;  // (All the above || HLT_PFJet500)
  Count cTrigger_OR_PFHT1050;  // (All the above || HLT_PFHT1050)
  Count cTrigger_OR_All;       // (All the above || HLT_PFJet500 || HLT_PFHT1050)
  Count cTrigger_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF; // (All the above || HLT_PFJet500 || HLT_PFHT1050 || All QuadPFJetX_BTagCSV_Y_VBF)
  Count cTrigger_OR_All_with_AK8PFHT800_TrimMass50;    // (All the above || HLT_PFJet500 || HLT_PFHT1050 || AK8PFHT800_TrimMass50)
  Count cTrigger_OR_All_with_AK8PFJet400_TrimMass30;   // (All the above || HLT_PFJet500 || HLT_PFHT1050 || AK8PFJet400_TrimMass30)
  Count cTrigger_OR_All_Everything;                    // (All the above || HLT_PFJet500 || HLT_PFHT1050 || AK8PFJet400_TrimMass30 || AK8PFHT800_TrimMass50 || All QuadPFJetX_BTagCSV_Y_VBF )
  //
  Count cTrigger_PFHT250;
  Count cTrigger_PFHT320;
  Count cTrigger_PFHT370;
  Count cTrigger_PFHT430;
  Count cTrigger_PFHT510;
  Count cTrigger_PFHT590;
  Count cTrigger_PFHT680;
  Count cTrigger_PFHT780;
  Count cTrigger_PFHT890;
  Count cTrigger_PFHT1050;
  Count cTrigger_PFJet140;
  Count cTrigger_PFJet200;
  Count cTrigger_PFJet260;
  Count cTrigger_PFJet320;
  Count cTrigger_PFJet400;
  Count cTrigger_PFJet450;
  Count cTrigger_PFJet500;
  Count cTrigger_PFJet550;
  Count cTrigger_PFHT430_SixPFJet40;
  Count cTrigger_PFHT380_SixPFJet32;
  Count cTrigger_PFHT300_QuadJet_75_60_45_40;
  // With Boosted Triggers
  Count cTrigger_AK8PFHT750_TrimMass50;   
  Count cTrigger_AK8PFHT800_TrimMass50;  // Unprescaled
  Count cTrigger_AK8PFHT850_TrimMass50;  // Unprescaled
  Count cTrigger_AK8PFHT900_TrimMass50;  // Unprescaled
  Count cTrigger_AK8PFJet360_TrimMass30; 
  Count cTrigger_AK8PFJet380_TrimMass30;
  Count cTrigger_AK8PFJet400_TrimMass30; // Unprescaled 
  Count cTrigger_AK8PFJet420_TrimMass30; // Unprescaled
  Count cTrigger_AK8PFJet500;            // Unprescaled
  Count cTrigger_AK8PFJet550;            // Unprescaled
  Count cTrigger_DoublePFJets350_CaloBTagCSV_p33; 
  // Only in the last period 2017 (unprescaled)
  // More info from https://cmswbm.cern.ch/cmsdb/servlet/PrescaleChangePaths?RUN=305405
  // First seen online run 305404 (v4.0.0/HLT/V1)
  // Last seen online run 306460 (v4.2.1/HLT/V2)
  Count cTrigger_QuadPFJet103_88_75_15;
  Count cTrigger_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  Count cTrigger_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  Count cTrigger_QuadPFJet105_88_76_15;
  Count cTrigger_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  Count cTrigger_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  Count cTrigger_QuadPFJet111_90_80_15;
  Count cTrigger_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  Count cTrigger_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  Count cTrigger_QuadPFJet98_83_71_15;
  Count cTrigger_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  Count cTrigger_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  
  // Histogram Settings
  const HistogramSettings cfg_PtBinSetting;
  const HistogramSettings cfg_EtaBinSetting;
    
  // Strings to store trigger names
  std::string TriggerName;
  std::string SingleBTagCSV_v1;
  std::string SingleBTagCSV_v2;
  std::string DoubleBTagCSV_v1;
  std::string DoubleBTagCSV_v2;
  std::string TripleBTagCSV_v1;
  std::string TripleBTagCSV_v2;
  std::string DoubleBTagDeepCSV;
  std::string PFJet500;
  std::string PFHT1050;
  
  //Histograms 
  WrappedTH1* hdRminJetM;
  
  //---------------------------------------------------------------------
  //   Denominators  
  //---------------------------------------------------------------------
  //   6thJet Pt,Eta,Phi, ... Event HT,PU,JetMulti,bJetMulti, AllJetCSV
  WrappedTH1* hDen_pt6thJet_RefTrg_OfflineSel;
  WrappedTH1* hDen_eta6thJet_RefTrg_OfflineSel;
  WrappedTH1* hDen_phi6thJet_RefTrg_OfflineSel;
  WrappedTH1* hDen_Ht_RefTrg_OfflineSel;
  WrappedTH1* hDen_pu_RefTrg_OfflineSel;
  WrappedTH1* hDen_nBTagJets_RefTrg_OfflineSel;
  WrappedTH1* hDen_CSV_RefTrg_OfflineSel;
  WrappedTH1* hDen_DeepCSV_RefTrg_OfflineSel;
  WrappedTH1* hDen_JetMulti_RefTrg_OfflineSel;
  //---------------------------------------------------------------------
  
  //---------------------------------------------------------------------  
  // Numerators, 1-BTag, 2-BTag, OR, OR+Jet450
  //---------------------------------------------------------------------
  // 6th jet pt
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;
  
  // 6th jet eta
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_Everything;  
  //
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  // 6th jet phi
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  // Ht
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;
  

  //PU
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  //B-Jet Multi
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  //Jet CSV
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_CSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  //Jet Deep CSV
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_Everything;
  
  //
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  //Jet Multi
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_Signal1BTagCSV;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagCSV;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagDeepCSV;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_Signal3BTagCSV;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalORwDeepCSV;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFJet500;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFHT1050;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_Everything;
  //
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT250;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT320;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT370;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT510;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT590;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT680;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT780;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT890;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT1050;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet140;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet200;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet260;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet320;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet400;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet450;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet500;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet550;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet500;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet550;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2;
  WrappedTH1* hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;

  //---------------------------------------------------------------------
  


  /*
  
  //---------------------------------------------------------------------
  // TrgEfficiency in slices of Ht and the pt of the 6th Jet  
  //---------------------------------------------------------------------
  // In slices of HT
  WrappedTH1* h_Den_pt6thJet_Vs_450ht600_RefTrg_OfflineSel;
  WrappedTH1* h_Den_pt6thJet_Vs_600ht800_RefTrg_OfflineSel;
  WrappedTH1* h_Den_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel;
  WrappedTH1* h_Den_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel;
  WrappedTH1* h_Den_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel;
  WrappedTH1* h_Den_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel;

  WrappedTH1* h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_1BTag;

  WrappedTH1* h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_2BTag;

  WrappedTH1* h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_OR;
  
  // In slices of Pt of the 6th Jet
  //WrappedTH1* h_Den_ht_Vs_30pt40_RefTrg_OfflineSel;
  WrappedTH1* h_Den_ht_Vs_40pt50_RefTrg_OfflineSel;
  WrappedTH1* h_Den_ht_Vs_50pt60_RefTrg_OfflineSel;
  WrappedTH1* h_Den_ht_Vs_60pt70_RefTrg_OfflineSel;
  WrappedTH1* h_Den_ht_Vs_70pt90_RefTrg_OfflineSel;
  WrappedTH1* h_Den_ht_Vs_90pt120_RefTrg_OfflineSel;

  //WrappedTH1* h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_1BTag;
  WrappedTH1* h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_1BTag;

  //WrappedTH1* h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_2BTag;
  WrappedTH1* h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_2BTag;

  //WrappedTH1* h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_OR;
  WrappedTH1* h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_OR;
  //---------------------------------------------------------------------
  */
  
};

#include "Framework/interface/SelectorFactory.h"
REGISTER_SELECTOR(JetTriggersSF);

JetTriggersSF::JetTriggersSF(const ParameterSet& config, const TH1* skimCounters)
  : BaseSelector(config, skimCounters),
    //cfg_PrelimTopMVACut(config, "FakeBMeasurement.minTopMVACut"),
    fCommonPlots(config.getParameter<ParameterSet>("CommonPlots"), CommonPlots::kHplus2tbAnalysis, fHistoWrapper), 
    cAllEvents(fEventCounter.addCounter("all events")),
    cControlTrigger(fEventCounter.addCounter("passed cntrl trg")),
    fMETFilterSelection(config.getParameter<ParameterSet>("METFilter"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cVertexSelection(fEventCounter.addCounter("passed PV")),
    fElectronSelection(config.getParameter<ParameterSet>("ElectronSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fMuonSelection(config.getParameter<ParameterSet>("MuonSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fTauSelection(config.getParameter<ParameterSet>("TauSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, "Veto"),
    fJetSelection(config.getParameter<ParameterSet>("JetSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    fBJetSelection(config.getParameter<ParameterSet>("BJetSelection"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cBTaggingSFCounter(fEventCounter.addCounter("b tag SF")),
    fMETSelection(config.getParameter<ParameterSet>("METSelection")), // no subcounter in main counter 
    fTopSelection(config.getParameter<ParameterSet>("TopSelectionBDT"), fEventCounter, fHistoWrapper, &fCommonPlots, ""),
    cSelected(fEventCounter.addCounter("Selected Events")),
    cTrigger_1BTagCSV(fEventCounter.addCounter("passed sig 1BTagCSV")),
    cTrigger_2BTagCSV(fEventCounter.addCounter("passed sig 2BTagCSV")),
    cTrigger_2BTagDeepCSV(fEventCounter.addCounter("passed sig 2BTagDeepCSV")),
    cTrigger_3BTagCSV(fEventCounter.addCounter("passed sig 3BTagCSV")),
    cTrigger_OR(fEventCounter.addCounter("passed sig OR")),
    cTrigger_ORwDeepCSV(fEventCounter.addCounter("passed sig OR w 2BTagDeepCSV")),
    cTrigger_OR_PFJet500(fEventCounter.addCounter("passed sig OR + PFJet450")),
    cTrigger_OR_PFHT1050(fEventCounter.addCounter("passed sig OR + PFHT1050")),
    cTrigger_OR_All(fEventCounter.addCounter("passed sig OR + PFJet450 + PFHT1050")),
    cTrigger_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF(fEventCounter.addCounter("passed sig OR + PFJet450 + PFHT1050")),
    cTrigger_OR_All_with_AK8PFHT800_TrimMass50(fEventCounter.addCounter("passed sig OR + AK8PFHT800_TrimMass50")),
    cTrigger_OR_All_with_AK8PFJet400_TrimMass30(fEventCounter.addCounter("passed sig OR + AK8PFJet400_TrimMass30")),
    cTrigger_OR_All_Everything(fEventCounter.addCounter("passed all the studied triggers - including AK8")),
    cTrigger_PFHT250(fEventCounter.addCounter("passed PFHT250")),
    cTrigger_PFHT320(fEventCounter.addCounter("passed PFHT320")),
    cTrigger_PFHT370(fEventCounter.addCounter("passed PFHT370")),
    cTrigger_PFHT430(fEventCounter.addCounter("passed PFHT430")),
    cTrigger_PFHT510(fEventCounter.addCounter("passed PFHT510")),
    cTrigger_PFHT590(fEventCounter.addCounter("passed PFHT590")),
    cTrigger_PFHT680(fEventCounter.addCounter("passed PFHT680")),
    cTrigger_PFHT780(fEventCounter.addCounter("passed PFHT780")),
    cTrigger_PFHT890(fEventCounter.addCounter("passed PFHT890")),
    cTrigger_PFHT1050(fEventCounter.addCounter("passed PFHT1050")),
    cTrigger_PFJet140(fEventCounter.addCounter("passed PFJet140")),
    cTrigger_PFJet200(fEventCounter.addCounter("passed PFJet200")),
    cTrigger_PFJet260(fEventCounter.addCounter("passed PFJet260")),
    cTrigger_PFJet320(fEventCounter.addCounter("passed PFJet320")),
    cTrigger_PFJet400(fEventCounter.addCounter("passed PFJet400")),
    cTrigger_PFJet450(fEventCounter.addCounter("passed PFJet450")),
    cTrigger_PFJet500(fEventCounter.addCounter("passed PFJet500")),
    cTrigger_PFJet550(fEventCounter.addCounter("passed PFJet550")),
    cTrigger_PFHT430_SixPFJet40(fEventCounter.addCounter("passed PFHT430_SixPFJet40")),
    cTrigger_PFHT380_SixPFJet32(fEventCounter.addCounter("passed PFHT380_SixPFJet32")),
    cTrigger_PFHT300_QuadJet_75_60_45_40(fEventCounter.addCounter("passed PFHT300_QuadJet_75_60_45_40")),
    cTrigger_AK8PFHT750_TrimMass50(fEventCounter.addCounter("passed AK8PFHT750_TrimMass50")),
    cTrigger_AK8PFHT800_TrimMass50(fEventCounter.addCounter("passed AK8PFHT800_TrimMass50")),
    cTrigger_AK8PFHT850_TrimMass50(fEventCounter.addCounter("passed AK8PFHT850_TrimMass50")),
    cTrigger_AK8PFHT900_TrimMass50(fEventCounter.addCounter("passed AK8PFHT900_TrimMass50")),
    cTrigger_AK8PFJet360_TrimMass30(fEventCounter.addCounter("passed AK8PFJet360_TrimMass30")),
    cTrigger_AK8PFJet380_TrimMass30(fEventCounter.addCounter("passed AK8PFJet380_TrimMass30")),
    cTrigger_AK8PFJet400_TrimMass30(fEventCounter.addCounter("passed AK8PFJet400_TrimMass30")),
    cTrigger_AK8PFJet420_TrimMass30(fEventCounter.addCounter("passed AK8PFJet420_TrimMass30")),
    cTrigger_AK8PFJet500(fEventCounter.addCounter("passed AK8PFJet500")),
    cTrigger_AK8PFJet550(fEventCounter.addCounter("passed AK8PFJet550")),
    cTrigger_DoublePFJets350_CaloBTagCSV_p33(fEventCounter.addCounter("passed DoublePFJets350_CaloBTagCSV_p33")),
    cTrigger_QuadPFJet103_88_75_15(fEventCounter.addCounter("passed QuadPFJet103_88_75_15")),
    cTrigger_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2(fEventCounter.addCounter("passed QuadPFJet103_88_75_15_BTagCSV_p013_VBF2")),
    cTrigger_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1(fEventCounter.addCounter("passed QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1")),
    cTrigger_QuadPFJet105_88_76_15(fEventCounter.addCounter("passed QuadPFJet105_88_76_15")),
    cTrigger_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2(fEventCounter.addCounter("passed QuadPFJet105_88_76_15_BTagCSV_p013_VBF2")),
    cTrigger_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1(fEventCounter.addCounter("passed QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1")),
    cTrigger_QuadPFJet111_90_80_15(fEventCounter.addCounter("passed QuadPFJet111_90_80_15")),
    cTrigger_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2(fEventCounter.addCounter("passed QuadPFJet111_90_80_15_BTagCSV_p013_VBF2")),
    cTrigger_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1(fEventCounter.addCounter("passed QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1")),
    cTrigger_QuadPFJet98_83_71_15(fEventCounter.addCounter("passed QuadPFJet98_83_71_15")),
    cTrigger_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2(fEventCounter.addCounter("passed QuadPFJet98_83_71_15_BTagCSV_p013_VBF2")),
    cTrigger_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1(fEventCounter.addCounter("passed QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1")),
    cfg_PtBinSetting(config.getParameter<ParameterSet>("CommonPlots.ptBins")),
    cfg_EtaBinSetting(config.getParameter<ParameterSet>("CommonPlots.etaBins"))
{
}

JetTriggersSF::~JetTriggersSF()
{
}

void JetTriggersSF::book(TDirectory *dir) {

  
  // Book common plots histograms
  fCommonPlots.book(dir, isData());

  // Book histograms in event selection classes
  fMETFilterSelection.bookHistograms(dir);
  fElectronSelection.bookHistograms(dir);
  fMuonSelection.bookHistograms(dir);
  fTauSelection.bookHistograms(dir);
  fJetSelection.bookHistograms(dir);
  fBJetSelection.bookHistograms(dir);
  fMETSelection.bookHistograms(dir);
  fTopSelection.bookHistograms(dir);
  
  // Book non-common histograms
  
  // Fixed Binning
  double xbins_pt[28] = {20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 55, 60, 65, 70, 80, 90, 100, 110, 120, 150, 200, 250};
  int nxbins_pt       = 26;
  double xbins_ht[38] = {200,220,240,260,280,300,320,340,360,380,400,420,440,460,480,500,520,540,560,580,600,620,640,660,680,700,725,750,775,800,850,900,950,1000,1100,1400,1700,2000};
  int nxbins_ht       = 37;
  double xbins_b[7]   = {-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 9.5};
  int nxbins_b        = 6;
  double etaMax = 3.0;
  int nxbins_eta = 30;
  double phiMax = 4.0;
  int nxbins_phi = 30;
  
  hdRminJetM = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hdRminJetM" , "dR", 250, 0, 5);
  
  //---------------------------------------------------------------------
  //   Denominators  
  //---------------------------------------------------------------------
  hDen_pt6thJet_RefTrg_OfflineSel  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_pt6thJet_RefTrg_OfflineSel", "pt", nxbins_pt, xbins_pt);
  hDen_eta6thJet_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_eta6thJet_RefTrg_OfflineSel", "eta", nxbins_eta, -1*etaMax , etaMax);
  hDen_phi6thJet_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_phi6thJet_RefTrg_OfflineSel", "phi", nxbins_phi, -1*phiMax , phiMax);
  hDen_Ht_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_Ht_RefTrg_OfflineSel", "ht", nxbins_ht, xbins_ht);
  hDen_pu_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_pu_RefTrg_OfflineSel","pu", 15, 0, 80);
  hDen_nBTagJets_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_nBTagJets_RefTrg_OfflineSel", "nbtagjets", nxbins_b, xbins_b);
  hDen_CSV_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_CSV_RefTrg_OfflineSel", "CSV", 20, 0, 1); 
  hDen_JetMulti_RefTrg_OfflineSel = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hDen_JetMulti_RefTrg_OfflineSel", "nJets", 10, 4.5, 14.5);
  
  //---------------------------------------------------------------------
  // Numerators
  //---------------------------------------------------------------------
  
  //6th Jet pt
  hNum_pt6thJet_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_Signal1BTagCSV", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagCSV", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_Signal3BTagCSV", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalORwDeepCSV", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFJet500", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All", "pt", nxbins_pt, xbins_pt);
  //
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_Everything", "pt", nxbins_pt, xbins_pt);
  //
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT250", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT320", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT370", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT510", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT590", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT680", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT780", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT890", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT1050", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet140", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet200", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet260", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet320", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet400", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet450", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet500", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet550", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "pt", nxbins_pt, xbins_pt);
  hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "pt", nxbins_pt, xbins_pt);
  
  
  //6th Jet eta
  hNum_eta6thJet_RefTrg_OfflineSel_Signal1BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_Signal1BTagCSV", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagCSV", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_Signal3BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_Signal3BTagCSV", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR          = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalORwDeepCSV  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalORwDeepCSV", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFJet500", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All      = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All", "eta", nxbins_eta, -1*etaMax , etaMax);
  //
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_Everything", "eta", nxbins_eta, -1*etaMax , etaMax);
  //
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT250", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT320", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT370", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT510", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT590", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT680", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT780", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT890", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT1050", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet140", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet200", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet260", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet320", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet400", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet450", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet500", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet550", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "eta", nxbins_eta, -1*etaMax, etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "eta", nxbins_eta, -1*etaMax, etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "eta", nxbins_eta, -1*etaMax, etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "eta", nxbins_eta, -1*etaMax , etaMax);
  hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "eta", nxbins_eta, -1*etaMax, etaMax);
  

  //6th Jet phi
  hNum_phi6thJet_RefTrg_OfflineSel_Signal1BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_Signal1BTagCSV", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagCSV", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_Signal3BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_Signal3BTagCSV", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR          = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalORwDeepCSV  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalORwDeepCSV", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFJet500", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All      = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All", "phi", nxbins_phi, -1*phiMax , phiMax);
  //
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_Everything", "phi", nxbins_phi, -1*phiMax , phiMax);
  //
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT250", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT320", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT370", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT510", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT590", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT680", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT780", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT890", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT1050", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet140", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet200", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet260", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet320", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet400", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet450", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet500", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet550", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "phi", nxbins_phi, -1*phiMax, phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "phi", nxbins_phi, -1*phiMax, phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "phi", nxbins_phi, -1*phiMax, phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "phi", nxbins_phi, -1*phiMax , phiMax);
  hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "phi", nxbins_phi, -1*phiMax, phiMax);
  
  
  
  
  //HT
  hNum_Ht_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_Signal1BTagCSV", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_Signal2BTagCSV", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_Signal2BTagDeepCSV", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_Signal3BTagCSV", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalORwDeepCSV", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_PFJet500", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_PFHT1050", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_All", "Ht", nxbins_ht, xbins_ht);
  //
  hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_SignalOR_All_Everything", "Ht", nxbins_ht, xbins_ht);
  //
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT250", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT320", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT370", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT510", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT590", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT680", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT780", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT890", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT1050", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet140", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet200", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet260", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet320", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet400", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet450", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet500", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFJet550", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet500", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet550", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "Ht", nxbins_ht, xbins_ht);
  hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "Ht", nxbins_ht, xbins_ht);
  
  //PU
  hNum_pu_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_Signal1BTagCSV", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_Signal2BTagCSV", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_Signal2BTagDeepCSV", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_Signal3BTagCSV", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalORwDeepCSV", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_PFJet500", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_PFHT1050", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_All", "pu", 15, 0, 80);
  
  //
  hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_SignalOR_All_Everything", "pu", 15, 0, 80);
  //
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT250", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT320", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT370", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT430", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT510", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT590", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT680", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT780", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT890", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT1050", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet140", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet200", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet260", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet320", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet400", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet450", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet500", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFJet550", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet500", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet550", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "pu", 15, 0, 80);
  hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "pu", 15, 0, 80);
  
  //b-Jet Multi
  hNum_nBTagJets_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_Signal1BTagCSV", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagCSV", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagDeepCSV", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_Signal3BTagCSV", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalORwDeepCSV", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFJet500", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFHT1050", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All", "nbtagjets", nxbins_b, xbins_b);
  //
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything", "nbtagjets", nxbins_b, xbins_b);
  //
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "nbtagjets", nxbins_b, xbins_b);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "nbtagjets", nxbins_b, xbins_b);
  


  //Jet CSV
  hNum_CSV_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_Signal1BTagCSV", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_Signal2BTagCSV", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_Signal2BTagDeepCSV", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_Signal3BTagCSV", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_SignalOR", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_SignalORwDeepCSV", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_SignalOR_PFJet500", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_SignalOR_PFHT1050", "CSV", 20, 0, 1);
  hNum_CSV_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_CSV_RefTrg_OfflineSel_SignalOR_All", "CSV", 20, 0, 1);
  
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything", "CSV", 20, 0, 1);
  //
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "CSV", 20, 0, 1);
  hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "CSV", 20, 0, 1);
  
  //Jet Deep CSV
  hNum_DeepCSV_RefTrg_OfflineSel_Signal1BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_Signal1BTagCSV", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagCSV", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagDeepCSV = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_Signal2BTagDeepCSV", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_Signal3BTagCSV     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_Signal3BTagCSV", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR           = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalORwDeepCSV   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalORwDeepCSV", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFJet500  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFJet500", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFHT1050  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_PFHT1050", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All       = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All", "Deep CSV", 20, 0, 1);
  
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_SignalOR_All_Everything", "Deep CSV", 20, 0, 1);
  //
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT250", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT320", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT370", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT510", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT590", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT680", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT780", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT890", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT1050", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet140", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet200", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet260", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet320", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet400", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet450", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet500", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFJet550", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet500", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_AK8PFJet550", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "Deep CSV", 20, 0, 1);
  hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_DeepCSV_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "Deep CSV", 20, 0, 1);
  
  //Jet Multi
  hNum_JetMulti_RefTrg_OfflineSel_Signal1BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_Signal1BTagCSV", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagCSV", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagDeepCSV= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagDeepCSV", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_Signal3BTagCSV    = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_Signal3BTagCSV", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR          = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalORwDeepCSV  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalORwDeepCSV", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFJet500", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFHT1050", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All      = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All", "nJets", 10, 4.5, 14.5);
  //
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_Everything = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_Everything", "nJets", 10, 4.5, 14.5);
  //
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT250 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT250", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT320", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT370 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT370", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT510 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT510", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT590 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT590", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT680 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT680", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT780 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT780", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT890 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT890", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT1050 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT1050", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet140 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet140", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet200 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet200", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet260 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet260", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet320 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet320", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet400 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet400", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet450 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet450", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet500", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet550", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet500 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet500", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet550 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet550", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2", "nJets", 10, 4.5, 14.5);
  hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1", "nJets", 10, 4.5, 14.5);
  
  
  
  /*
  //---------------------------------------------------------------------
  // In slices of HT and the pt of the 6th Jet
  //---------------------------------------------------------------------
  // in slices of the pt of the 6th jet
  //---------------------------------------------------------------------
  //h_Den_ht_Vs_30pt40_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Den_ht_Vs_30pt40_RefTrg_OfflineSel","ht",nxbins_ht, xbins_ht);
  h_Den_ht_Vs_40pt50_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Den_ht_Vs_40pt50_RefTrg_OfflineSel","ht",nxbins_ht, xbins_ht);
  h_Den_ht_Vs_50pt60_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Den_ht_Vs_50pt60_RefTrg_OfflineSel","ht",nxbins_ht, xbins_ht);
  h_Den_ht_Vs_60pt70_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Den_ht_Vs_60pt70_RefTrg_OfflineSel","ht",nxbins_ht, xbins_ht);
  h_Den_ht_Vs_70pt90_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Den_ht_Vs_70pt90_RefTrg_OfflineSel","ht",nxbins_ht, xbins_ht);
  h_Den_ht_Vs_90pt120_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Den_ht_Vs_90pt120_RefTrg_OfflineSel","ht",nxbins_ht,xbins_ht);
  
  //h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_30pt40_RefTrg_OfflineSel_1BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_40pt50_RefTrg_OfflineSel_1BTag","ht in pt slices",  nxbins_ht, xbins_ht);
  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_50pt60_RefTrg_OfflineSel_1BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_60pt70_RefTrg_OfflineSel_1BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_70pt90_RefTrg_OfflineSel_1BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_1BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_90pt120_RefTrg_OfflineSel_1BTag","ht in pt slices", nxbins_ht, xbins_ht);
  
  //h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_30pt40_RefTrg_OfflineSel_2BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_40pt50_RefTrg_OfflineSel_2BTag","ht in pt slices",  nxbins_ht, xbins_ht);
  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_50pt60_RefTrg_OfflineSel_2BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_60pt70_RefTrg_OfflineSel_2BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_70pt90_RefTrg_OfflineSel_2BTag","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_2BTag= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_90pt120_RefTrg_OfflineSel_2BTag","ht in pt slices", nxbins_ht, xbins_ht);
  
  //h_Num_ht_Vs_30pt40_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_30pt40_RefTrg_OfflineSel_OR","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_40pt50_RefTrg_OfflineSel_OR","ht in pt slices",  nxbins_ht, xbins_ht);
  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_50pt60_RefTrg_OfflineSel_OR","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_60pt70_RefTrg_OfflineSel_OR","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_70pt90_RefTrg_OfflineSel_OR","ht in pt slices", nxbins_ht, xbins_ht);
  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir,"Num_ht_Vs_90pt120_RefTrg_OfflineSel_OR","ht in pt slices", nxbins_ht, xbins_ht);
  
  //---------------------------------------------------------------------
  // in slices of ht
  //---------------------------------------------------------------------
  h_Den_pt6thJet_Vs_450ht600_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_450ht600_RefTrg_OfflineSel","pt",nxbins_pt,xbins_pt);
  h_Den_pt6thJet_Vs_600ht800_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_600ht800_RefTrg_OfflineSel","pt",nxbins_pt,xbins_pt);
  h_Den_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel","pt",nxbins_pt,xbins_pt); 
  h_Den_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel", "pt", nxbins_pt, xbins_pt);
  h_Den_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel", "pt", nxbins_pt, xbins_pt);
  h_Den_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel=fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital,dir,"Den_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel", "pt", nxbins_pt, xbins_pt);
  
  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_1BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_1BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_1BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_1BTag", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_1BTag", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_1BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_1BTag", "pt",nxbins_pt, xbins_pt);
  
  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_2BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_2BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_2BTag", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_2BTag", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_2BTag", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_2BTag = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_2BTag", "pt",nxbins_pt, xbins_pt);
  
  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_OR", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_OR", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_OR", "pt", nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_OR", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_OR", "pt",nxbins_pt, xbins_pt);
  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_OR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_OR", "pt",nxbins_pt, xbins_pt);
  //---------------------------------------------------------------------
  */
  
  return;
}


void JetTriggersSF::setupBranches(BranchManager& branchManager) {
  fEvent.setupBranches(branchManager);
  return;
}


void JetTriggersSF::process(Long64_t entry) {
  
  //====== Initialize
  fCommonPlots.initialize();
  fCommonPlots.setFactorisationBinForEvent(std::vector<float> {});
  cAllEvents.increment();

  // ===============================================================================================
  //  1) Apply Reference Trigger
  // ===============================================================================================
  if (0) std::cout<<"=== Control Trigger" << std::endl;
  if ( !(fEvent.passTriggerDecision()) ) return;
  cControlTrigger.increment();
  
  //================================================================================================
  // 2) MET filters (to remove events with spurious sources of fake MET)
  //================================================================================================
  if (0) std::cout << "=== MET Filter" << std::endl;
  const METFilterSelection::Data metFilterData = fMETFilterSelection.analyze(fEvent);
  if (!metFilterData.passedSelection()) return;
  fCommonPlots.fillControlPlotsAfterMETFilter(fEvent);
  
  //================================================================================================
  // 3) Primarty Vertex (Check that a PV exists)
  //================================================================================================
  if (0) std::cout << "=== Vertices" << std::endl;
  int nVertices = fEvent.vertexInfo().value();
  if (nVertices < 1) return;
  cVertexSelection.increment();
  fCommonPlots.fillControlPlotsAtVertexSelection(fEvent);
  
  //================================================================================================
  // 4) Electron veto (Fully hadronic + orthogonality)
  //================================================================================================
  if (0) std::cout << "=== Electron veto" << std::endl;
  const ElectronSelection::Data eData = fElectronSelection.analyze(fEvent);
  if (eData.hasIdentifiedElectrons()) return;
  
  //================================================================================================
  // 5) Muon selection
  //================================================================================================
  if (0) std::cout << "=== Muon selection" << std::endl;
  const MuonSelection::Data muData = fMuonSelection.analyze(fEvent);
  if (!muData.hasIdentifiedMuons()) return;
  if (muData.getSelectedMuons().size()>1) return;
  
  //================================================================================================
  // 6) Tau veto (HToTauNu Orthogonality)
  //================================================================================================
  if (0) std::cout << "=== Tau Veto" << std::endl;
  const TauSelection::Data tauData = fTauSelection.analyze(fEvent);
  if (tauData.hasIdentifiedTaus() ) return;
  
  //================================================================================================ 
  // 7) Jet selection
  //================================================================================================
  if (0) std::cout << "=== Jet selection" << std::endl;
  const JetSelection::Data jetData = fJetSelection.analyzeWithoutTau(fEvent);
  if (!jetData.passedSelection()) return;
  fCommonPlots.fillControlPlotsAfterTopologicalSelections(fEvent, true);
  
  //================================================================================================
  // 8) BJet selection
  //================================================================================================
  if (0) std::cout << "=== BJet selection" << std::endl;
  const BJetSelection::Data bjetData = fBJetSelection.analyze(fEvent, jetData);
  if (!bjetData.passedSelection()) return;
  // fCommonPlots.fillControlPlotsAfterBJetSelection(fEvent, bjetData); 
  
  //================================================================================================
  // 9) BJet SF
  //================================================================================================
  //if (0) std::cout << "=== BJet SF" << std::endl;
  //if (fEvent.isMC())
  //  {
  //    fEventWeight.multiplyWeight(bjetData.getBTaggingScaleFactorEventWeight());
  //  }
  //cBTaggingSFCounter.increment();
  
  
  //================================================================================================
  // - MET selection
  //================================================================================================
  if (0) std::cout << "=== MET selection" << std::endl;
  const METSelection::Data METData = fMETSelection.silentAnalyze(fEvent, nVertices);
  // if (!METData.passedSelection()) return; 
  
  //================================================================================================   
  // Mu Isolation from selected jets.  
  //================================================================================================
  Double_t dRMin = 100.0;
  
  for(Size_t imu =0; imu < muData.getSelectedMuons().size(); imu++)
    {
      Double_t MuEta = muData.getSelectedMuons().at(imu).eta();
      Double_t MuPhi = muData.getSelectedMuons().at(imu).phi();	
      for(Size_t ijet = 0; ijet<jetData.getSelectedJets().size(); ijet++)
	{
	  Double_t JetEta = jetData.getSelectedJets().at(ijet).eta();
	  Double_t JetPhi = jetData.getSelectedJets().at(ijet).phi();
	  
	  Double_t dRJetMu =  DeltaR(MuEta, JetEta, MuPhi, JetPhi);
	  
	  if(dRJetMu < dRMin)
	    {
	      dRMin = dRJetMu;
	    }
	}//loop on jets
    }//loop on Mu
  
  hdRminJetM->Fill(dRMin);
  
  // comment these out to run withouf dR cut
  if(dRMin < 0.4) return;
  
  //======================================================================================================
  // All Selections: TopSelection & QGLR Selection & FatJetSelection not needed for the eff. measurement
  //======================================================================================================
  if (0) std::cout << "=== All Selections" << std::endl;
  cSelected.increment();
  
  //================================================================================================
  // Measurement dependent offline selection 
  //================================================================================================   
  /*
    The efficiency measurement w.r.t Ht and pt6th jet are measured without applying cuts to these variables.
    The initial selection is loose w.r.t these variables.  
  */
  
  Bool_t isEffvsPT = false;
  Bool_t isEffvsHT = false;
  
  Double_t HT_selJets = jetData.HT(); 
  Double_t pt_6thJet = jetData.getSelectedJets().at(5).pt();
  Double_t pt_7thJet = jetData.getSelectedJets().at(6).pt();
  
  // Measuring Eff Vs. Ht, standard jet pt cut applied on events. pt cut  [40.0, 40.0, 40.0, 40.0, 40.0, 40.0, 30.0] 
  if(pt_6thJet > 40.0 && pt_7thJet > 30.0)
    isEffvsHT= true;
  
  // Measuring Eff Vs. pt6thJet, standard Ht cut applied on events. Ht cut 500.0 
  if(HT_selJets >= 500.0)
    isEffvsPT = true;
  
  // Measuring Eff Vs. other variables, standard cut on pt and Ht is applied on the events.
  Bool_t isEffvsOthers = isEffvsPT and isEffvsHT; 
  
  //================================================================================================   
  // Signal triggers  
  //================================================================================================   
  if (0) std::cout << "=== Signal Trigger" << std::endl;

  SingleBTagCSV_v1 = "HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5";
  SingleBTagCSV_v2 = "HLT_PFHT430_SixJet40_BTagCSV_p080";
  bool Passed_SingleBTagCSV    = fEvent.passHLTDecisionByName(SingleBTagCSV_v1) or fEvent.passHLTDecisionByName(SingleBTagCSV_v2);
  
  DoubleBTagCSV_v1 = "HLT_PFHT380_SixJet32_DoubleBTagCSV_p075";
  DoubleBTagCSV_v2 = "HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2";
  bool Passed_DoubleBTagCSV    = fEvent.passHLTDecisionByName(DoubleBTagCSV_v1) or fEvent.passHLTDecisionByName(DoubleBTagCSV_v2);
  
  TripleBTagCSV_v1 = "HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07";
  TripleBTagCSV_v2 = "HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0";
  bool Passed_TripleBTagCSV    = fEvent.passHLTDecisionByName(TripleBTagCSV_v1) or fEvent.passHLTDecisionByName(TripleBTagCSV_v2);
  
  DoubleBTagDeepCSV= "HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2";
  bool Passed_DoubleBTagDeepCSV= fEvent.passHLTDecisionByName(DoubleBTagDeepCSV);
  
  PFJet500 = "HLT_PFJet500";
  bool Passed_PFJet500 = fEvent.passHLTDecisionByName(PFJet500);
  
  PFHT1050 = "HLT_PFHT1050";
  bool Passed_PFHT1050 = fEvent.passHLTDecisionByName(PFHT1050);
  
  TriggerName = "HLT_PFHT250"; bool Passed_HLT_PFHT250 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT320"; bool Passed_HLT_PFHT320 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT370"; bool Passed_HLT_PFHT370 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT430"; bool Passed_HLT_PFHT430 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT510"; bool Passed_HLT_PFHT510 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT590"; bool Passed_HLT_PFHT590 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT680"; bool Passed_HLT_PFHT680 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT780"; bool Passed_HLT_PFHT780 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT890"; bool Passed_HLT_PFHT890 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT1050"; bool Passed_HLT_PFHT1050 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet140"; bool Passed_HLT_PFJet140 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet200"; bool Passed_HLT_PFJet200 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet260"; bool Passed_HLT_PFJet260 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet320"; bool Passed_HLT_PFJet320 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet400"; bool Passed_HLT_PFJet400 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet450"; bool Passed_HLT_PFJet450 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet500"; bool Passed_HLT_PFJet500 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFJet550"; bool Passed_HLT_PFJet550 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT430_SixPFJet40"; bool Passed_HLT_PFHT430_SixPFJet40 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT380_SixPFJet32"; bool Passed_HLT_PFHT380_SixPFJet32 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_PFHT300_QuadJet_75_60_45_40"; bool Passed_HLT_PFHT300_QuadJet_75_60_45_40 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFHT750_TrimMass50"; bool Passed_HLT_AK8PFHT750_TrimMass50 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFHT800_TrimMass50"; bool Passed_HLT_AK8PFHT800_TrimMass50 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFHT850_TrimMass50"; bool Passed_HLT_AK8PFHT850_TrimMass50 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFHT900_TrimMass50"; bool Passed_HLT_AK8PFHT900_TrimMass50 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet360_TrimMass30"; bool Passed_HLT_AK8PFJet360_TrimMass30 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet380_TrimMass30"; bool Passed_HLT_AK8PFJet380_TrimMass30 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet400_TrimMass30"; bool Passed_HLT_AK8PFJet400_TrimMass30 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet420_TrimMass30"; bool Passed_HLT_AK8PFJet420_TrimMass30 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet500";            bool Passed_HLT_AK8PFJet500 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_AK8PFJet550";            bool Passed_HLT_AK8PFJet550 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_DoublePFJets350_CaloBTagCSV_p33"; bool Passed_HLT_DoublePFJets350_CaloBTagCSV_p33 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet103_88_75_15";  bool Passed_HLT_QuadPFJet103_88_75_15 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2"; bool Passed_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1"; bool Passed_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet105_88_76_15";  bool Passed_HLT_QuadPFJet105_88_76_15 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2"; bool Passed_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1"; bool Passed_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet111_90_80_15";  bool Passed_HLT_QuadPFJet111_90_80_15 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2"; bool Passed_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1"; bool Passed_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet98_83_71_15";   bool Passed_HLT_QuadPFJet98_83_71_15 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2"; bool Passed_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 = fEvent.passHLTDecisionByName(TriggerName);
  TriggerName = "HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1"; bool Passed_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 = fEvent.passHLTDecisionByName(TriggerName);
  
  bool Passed_QuadPFJetX_BTagCSV_Y_VBF = Passed_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 or Passed_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 or Passed_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 or Passed_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 or Passed_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 or Passed_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 or Passed_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 or Passed_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1;
  bool Passed_AK8PFHT800_TrimMass50  = Passed_HLT_AK8PFHT800_TrimMass50;
  bool Passed_AK8PFJet400_TrimMass30 = Passed_HLT_AK8PFJet400_TrimMass30;
  
  // ===============================================================================================
  bool Passed_OR = Passed_SingleBTagCSV or Passed_DoubleBTagCSV or Passed_TripleBTagCSV;
  bool Passed_ORwDeepCSV  = Passed_OR or Passed_DoubleBTagDeepCSV;
  bool Passed_OR_PFJet500 = Passed_ORwDeepCSV or Passed_PFJet500;
  bool Passed_OR_PFHT1050 = Passed_ORwDeepCSV or Passed_PFHT1050;
  bool Passed_OR_All      = Passed_ORwDeepCSV or Passed_PFJet500 or Passed_PFHT1050;
  bool Passed_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF = Passed_ORwDeepCSV or Passed_PFJet500 or Passed_PFHT1050 or Passed_QuadPFJetX_BTagCSV_Y_VBF;
  bool Passed_OR_All_with_AK8PFHT800_TrimMass50 = Passed_ORwDeepCSV or Passed_PFJet500 or Passed_PFHT1050 or Passed_AK8PFHT800_TrimMass50;
  bool Passed_OR_All_with_AK8PFJet400_TrimMass30= Passed_ORwDeepCSV or Passed_PFJet500 or Passed_PFHT1050 or Passed_AK8PFJet400_TrimMass30;
  bool Passed_OR_All_Everything = Passed_ORwDeepCSV or Passed_PFJet500 or Passed_PFHT1050 or Passed_AK8PFJet400_TrimMass30 or Passed_AK8PFHT800_TrimMass50 or Passed_QuadPFJetX_BTagCSV_Y_VBF;
  // ===============================================================================================
  
  



  // *************************************
  // Fill Counters
  // *************************************
  if (Passed_SingleBTagCSV)     cTrigger_1BTagCSV.increment();
  if (Passed_DoubleBTagCSV)     cTrigger_2BTagCSV.increment();
  if (Passed_DoubleBTagDeepCSV) cTrigger_2BTagDeepCSV.increment();
  if (Passed_TripleBTagCSV)     cTrigger_3BTagCSV.increment();
  if (Passed_OR)                cTrigger_OR.increment();
  if (Passed_ORwDeepCSV)        cTrigger_ORwDeepCSV.increment();
  if (Passed_OR_PFJet500)       cTrigger_OR_PFJet500.increment();
  if (Passed_OR_PFHT1050)       cTrigger_OR_PFHT1050.increment();
  if (Passed_OR_All)            cTrigger_OR_All.increment();
  if (Passed_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF) cTrigger_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF.increment();
  if (Passed_OR_All_with_AK8PFHT800_TrimMass50)    cTrigger_OR_All_with_AK8PFHT800_TrimMass50.increment();
  if (Passed_OR_All_with_AK8PFJet400_TrimMass30)   cTrigger_OR_All_with_AK8PFJet400_TrimMass30.increment();
  if (Passed_OR_All_Everything)                    cTrigger_OR_All_Everything.increment();
  
  if (Passed_HLT_PFHT250) cTrigger_PFHT250.increment();
  if (Passed_HLT_PFHT320) cTrigger_PFHT320.increment();
  if (Passed_HLT_PFHT370) cTrigger_PFHT370.increment();
  if (Passed_HLT_PFHT430) cTrigger_PFHT430.increment();
  if (Passed_HLT_PFHT510) cTrigger_PFHT510.increment();
  if (Passed_HLT_PFHT590) cTrigger_PFHT590.increment();
  if (Passed_HLT_PFHT680) cTrigger_PFHT680.increment();
  if (Passed_HLT_PFHT780) cTrigger_PFHT780.increment();
  if (Passed_HLT_PFHT890) cTrigger_PFHT890.increment();
  if (Passed_HLT_PFHT1050) cTrigger_PFHT1050.increment();
  if (Passed_HLT_PFJet140) cTrigger_PFJet140.increment();
  if (Passed_HLT_PFJet200) cTrigger_PFJet200.increment();
  if (Passed_HLT_PFJet260) cTrigger_PFJet260.increment();
  if (Passed_HLT_PFJet320) cTrigger_PFJet320.increment();
  if (Passed_HLT_PFJet400) cTrigger_PFJet400.increment();
  if (Passed_HLT_PFJet450) cTrigger_PFJet450.increment();
  if (Passed_HLT_PFJet500) cTrigger_PFJet500.increment();
  if (Passed_HLT_PFJet550) cTrigger_PFJet550.increment();
  if (Passed_HLT_PFHT430_SixPFJet40) cTrigger_PFHT430_SixPFJet40.increment();
  if (Passed_HLT_PFHT380_SixPFJet32) cTrigger_PFHT380_SixPFJet32.increment();
  if (Passed_HLT_PFHT300_QuadJet_75_60_45_40) cTrigger_PFHT300_QuadJet_75_60_45_40.increment();
  if (Passed_HLT_AK8PFHT750_TrimMass50) cTrigger_AK8PFHT750_TrimMass50.increment();
  if (Passed_HLT_AK8PFHT800_TrimMass50) cTrigger_AK8PFHT800_TrimMass50.increment();
  if (Passed_HLT_AK8PFHT850_TrimMass50) cTrigger_AK8PFHT850_TrimMass50.increment();
  if (Passed_HLT_AK8PFHT900_TrimMass50) cTrigger_AK8PFHT900_TrimMass50.increment();
  if (Passed_HLT_AK8PFJet360_TrimMass30) cTrigger_AK8PFJet360_TrimMass30.increment();
  if (Passed_HLT_AK8PFJet380_TrimMass30) cTrigger_AK8PFJet380_TrimMass30.increment();
  if (Passed_HLT_AK8PFJet400_TrimMass30) cTrigger_AK8PFJet400_TrimMass30.increment();
  if (Passed_HLT_AK8PFJet420_TrimMass30) cTrigger_AK8PFJet420_TrimMass30.increment();
  if (Passed_HLT_AK8PFJet500) cTrigger_AK8PFJet500.increment();
  if (Passed_HLT_AK8PFJet550) cTrigger_AK8PFJet550.increment();
  if (Passed_HLT_DoublePFJets350_CaloBTagCSV_p33) cTrigger_DoublePFJets350_CaloBTagCSV_p33.increment();
  if (Passed_HLT_QuadPFJet103_88_75_15) cTrigger_QuadPFJet103_88_75_15.increment();
  if (Passed_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2) cTrigger_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2.increment();
  if (Passed_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1) cTrigger_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1.increment();
  if (Passed_HLT_QuadPFJet105_88_76_15) cTrigger_QuadPFJet105_88_76_15.increment();
  if (Passed_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2) cTrigger_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2.increment();
  if (Passed_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1) cTrigger_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1.increment();
  if (Passed_HLT_QuadPFJet111_90_80_15) cTrigger_QuadPFJet111_90_80_15.increment();
  if (Passed_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2) cTrigger_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2.increment();
  if (Passed_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1) cTrigger_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1.increment();
  if (Passed_HLT_QuadPFJet98_83_71_15) cTrigger_QuadPFJet98_83_71_15.increment();
  if (Passed_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2) cTrigger_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2.increment();
  if (Passed_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1) cTrigger_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1.increment();
  

  // ===============================================================================================
  //   Accessing variables to measure Trigger Efficiency
  // ===============================================================================================
  double Pt6thJet  = jetData.getSelectedJets().at(5).pt();
  double Eta6thJet = jetData.getSelectedJets().at(5).eta();
  double Phi6thJet = jetData.getSelectedJets().at(5).phi();
  double HT        = jetData.HT();
  int    PU        = nVertices;
  int    nBTagJets = bjetData.getNumberOfSelectedBJets();
  int    nJets     = jetData.getSelectedJets().size();

  // ===============================================================================================
  // Measurement Trigger Efficiencies
  // ===============================================================================================
  
  // Fill Denominator Plots
  if(isEffvsPT)
    {
      hDen_pt6thJet_RefTrg_OfflineSel   -> Fill(Pt6thJet);
    }
  
  if(isEffvsHT)
    {
      hDen_Ht_RefTrg_OfflineSel         -> Fill(HT);
    }
  
  if(isEffvsOthers)
    {
      hDen_eta6thJet_RefTrg_OfflineSel  -> Fill(Eta6thJet);
      hDen_phi6thJet_RefTrg_OfflineSel  -> Fill(Phi6thJet);
      hDen_pu_RefTrg_OfflineSel         -> Fill(PU);
      hDen_nBTagJets_RefTrg_OfflineSel  -> Fill(nBTagJets);
      hDen_JetMulti_RefTrg_OfflineSel   -> Fill(nJets);
    }
  
  // Single B-Tag Trigger 
  if (Passed_SingleBTagCSV)
    {
      if(isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(Pt6thJet);
      if(isEffvsHT) hNum_Ht_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(HT);
      if(isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_Signal1BTagCSV -> Fill(nJets);
	}
    }
  
  // Double B-Tag Trigger 
  if (Passed_DoubleBTagCSV)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagCSV -> Fill(nJets);
	}
    }
  
  // Double B-Tag Trigger 
  if (Passed_DoubleBTagDeepCSV)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_Signal2BTagDeepCSV -> Fill(nJets);
	}
    }
  
  // Double B-Tag Trigger 
  if (Passed_TripleBTagCSV)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_Signal3BTagCSV -> Fill(nJets);
	}
    }
  
  // OR Trigger
  if (Passed_OR)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR  -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR  -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR         -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR  -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR   -> Fill(nJets);
	}
    }

  // OR Trigger + 2BTagDeepCSV
  if (Passed_ORwDeepCSV)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalORwDeepCSV -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalORwDeepCSV -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalORwDeepCSV -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalORwDeepCSV -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalORwDeepCSV        -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalORwDeepCSV -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalORwDeepCSV  -> Fill(nJets);
	}
    }
  
  // OR + PFJet500 Trigger 
  if (Passed_OR_PFJet500)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFJet500 -> Fill(nJets);
	}
    }
  
  // OR + PFHT1050 Trigger 
  if (Passed_OR_PFHT1050)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_PFHT1050 -> Fill(nJets);
	}
    }
  
  
  // OR + PFJet500 + PFHT1050
  if (Passed_OR_All)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_All -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_All -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All -> Fill(nJets);
	}
    }
  
  // OR + PFJet500 + PFHT1050 + All QuadPFJetX_BTagCSV_Y_VBF 
  if (Passed_OR_All_with_QuadPFJetX_BTagCSV_Y_VBF)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF       -> Fill(HT); 
	  if (isEffvsOthers)
	    {
	      hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF -> Fill(Eta6thJet);
	      hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF -> Fill(Phi6thJet);
	      hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF        -> Fill(PU);
	      hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF -> Fill(nBTagJets);
	      hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_QuadPFJetX_BTagCSV_Y_VBF  -> Fill(nJets);
	    }
    }
  
  if (Passed_OR_All_with_AK8PFHT800_TrimMass50)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50       -> Fill(HT);
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50        -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50 -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFHT800_TrimMass50  -> Fill(nJets);
	}
    }
  
  if (Passed_OR_All_with_AK8PFJet400_TrimMass30)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30       -> Fill(HT); 
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30        -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30 -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_with_AK8PFJet400_TrimMass30  -> Fill(nJets);
	}
    }
  
  if (Passed_OR_All_Everything)
    {
      if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_SignalOR_All_Everything -> Fill(Pt6thJet);
      if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_SignalOR_All_Everything       -> Fill(HT); 
      if (isEffvsOthers)
	{
	  hNum_eta6thJet_RefTrg_OfflineSel_SignalOR_All_Everything -> Fill(Eta6thJet);
	  hNum_phi6thJet_RefTrg_OfflineSel_SignalOR_All_Everything -> Fill(Phi6thJet);
	  hNum_pu_RefTrg_OfflineSel_SignalOR_All_Everything        -> Fill(PU);
	  hNum_nBTagJets_RefTrg_OfflineSel_SignalOR_All_Everything -> Fill(nBTagJets);
	  hNum_JetMulti_RefTrg_OfflineSel_SignalOR_All_Everything  -> Fill(nJets);
	}
    }
  
  
  if (Passed_HLT_PFHT250){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT250 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT250 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT250 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT250 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT250        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT250 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT250  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT320){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT320 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT320 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT320 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT320 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT320        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT320 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT320  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT370){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT370 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT370 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT370 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT370 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT370        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT370 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT370  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT430){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT430        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT510){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT510 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT510 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT510 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT510 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT510        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT510 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT510  -> Fill(nJets);
      }
  }
  if (Passed_HLT_PFHT590){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT590 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT590 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT590 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT590 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT590        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT590 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT590  -> Fill(nJets);	
      }
  }
  
  if (Passed_HLT_PFHT680){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT680 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT680 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT680 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT680 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT680        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT680 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT680  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT780){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT780 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT780 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT780 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT780 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT780        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT780 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT780  -> Fill(nJets);	
      }
  }
  
  if (Passed_HLT_PFHT890){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT890 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT890 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT890 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT890 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT890        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT890 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT890  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFHT1050){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT1050 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT1050 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT1050 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT1050 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT1050        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT1050 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT1050  -> Fill(nJets);	
      }
  }
  
  if (Passed_HLT_PFJet140){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet140 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet140 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet140 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet140 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet140        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet140 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet140  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFJet200){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet200 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet200 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet200 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet200 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet200        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet200 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet200  -> Fill(nJets);	
      }
  }
  
  if (Passed_HLT_PFJet260){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet260 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet260 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet260 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet260 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet260        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet260 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet260  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFJet320){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet320 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet320 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet320 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet320 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet320        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet320 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet320  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFJet400){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet400 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet400 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet400 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet400 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet400        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet400 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet400  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFJet450){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet450 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet450 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet450 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet450 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet450        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet450 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet450  -> Fill(nJets);
      }
  }
  
  if (Passed_HLT_PFJet500){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet500 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet500 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet500 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet500 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet500        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet500 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet500  -> Fill(nJets);
      }
  }
  if (Passed_HLT_PFJet550){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFJet550 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFJet550 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFJet550 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFJet550 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFJet550        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFJet550 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFJet550  -> Fill(nJets);
      }
  }
  if (Passed_HLT_PFHT430_SixPFJet40){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT430_SixPFJet40  -> Fill(nJets);
      }
  }
  if (Passed_HLT_PFHT380_SixPFJet32){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT380_SixPFJet32  -> Fill(nJets);
      }
  }
  if (Passed_HLT_PFHT300_QuadJet_75_60_45_40){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_PFHT300_QuadJet_75_60_45_40  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFHT750_TrimMass50){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT750_TrimMass50  -> Fill(nJets);	
      }
  }
  if (Passed_HLT_AK8PFHT800_TrimMass50){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT800_TrimMass50  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFHT850_TrimMass50){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 -> Fill(HT);
    if (isEffvsOthers)
       {
	 hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 -> Fill(Eta6thJet);
	 hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 -> Fill(Phi6thJet);
	 hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50        -> Fill(PU);
	 hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50 -> Fill(nBTagJets);
	 hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT850_TrimMass50  -> Fill(nJets);
       }
  }
  if (Passed_HLT_AK8PFHT900_TrimMass50){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFHT900_TrimMass50  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFJet360_TrimMass30){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet360_TrimMass30  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFJet380_TrimMass30){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 ->Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet380_TrimMass30  -> Fill(nJets);
      }
  }

  if (Passed_HLT_AK8PFJet400_TrimMass30){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet400_TrimMass30  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFJet420_TrimMass30){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet420_TrimMass30  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFJet500){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet500 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet500 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet500        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet500 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet500  -> Fill(nJets);
      }
  }
  if (Passed_HLT_AK8PFJet550){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_AK8PFJet550 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_AK8PFJet550 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_AK8PFJet550        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_AK8PFJet550 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_AK8PFJet550  -> Fill(nJets);
      }
  }
  if (Passed_HLT_DoublePFJets350_CaloBTagCSV_p33){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_DoublePFJets350_CaloBTagCSV_p33  -> Fill(nJets);
	
      }
  }
  if (Passed_HLT_QuadPFJet103_88_75_15){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 -> Fill(HT);
    if (isEffvsOthers)
      {	
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_BTagCSV_p013_VBF2  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet103_88_75_15_DoubleBTagCSV_p013_p08_VBF1  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet105_88_76_15){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_88_76_15_BTagCSV_p013_VBF2  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet105_90_76_15_DoubleBTagCSV_p013_p08_VBF1  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet111_90_80_15){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_BTagCSV_p013_VBF2  -> Fill(nJets);
      }
    
  }
  if (Passed_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet111_90_80_15_DoubleBTagCSV_p013_p08_VBF1  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet98_83_71_15){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_BTagCSV_p013_VBF2  -> Fill(nJets);
      }
  }
  if (Passed_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1){
    if (isEffvsPT) hNum_pt6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Pt6thJet);
    if (isEffvsHT) hNum_Ht_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(HT);
    if (isEffvsOthers)
      {
	hNum_eta6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Eta6thJet);
	hNum_phi6thJet_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(Phi6thJet);
	hNum_pu_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1        -> Fill(PU);
	hNum_nBTagJets_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1 -> Fill(nBTagJets);
	hNum_JetMulti_RefTrg_OfflineSel_HLT_QuadPFJet98_83_71_15_DoubleBTagCSV_p013_p08_VBF1  -> Fill(nJets);
      }
  }
  
  

  /*
  // ----------------------------------------------------------
  //  Fill Plots with slices in HT and the Pt of the 6th Jet
  // ----------------------------------------------------------
  
  // Slices of HT
  if (HT>=450 && HT<600)
    {
      if(0) std::cout<<"\n\tHT>=450 && HT<600\t"<<HT<<std::endl;
      
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_450ht600_RefTrg_OfflineSel -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_450ht600_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	} 
    }
  else if (HT>=600 && HT<800)
    {
      if(0) std::cout<<"\n\tHT>=600 && HT<800\t"<<HT<<std::endl;
      
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_600ht800_RefTrg_OfflineSel -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_600ht800_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	} 
    }
  else if (HT>=800 && HT<1000)
    {
      if(0) std::cout<<"\n\tHT>=800 && HT<1000\t"<<HT<<std::endl;
      
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel  -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_800ht1000_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	} 
    }  
  else if (HT>=1000 && HT<1250)
    {
      if(0) std::cout<<"\n\tHT>=1000 && HT<1250\t"<<HT<<std::endl;
      
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel  -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_1000ht1250_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	} 
    }   
  else if (HT>=1250 && HT<1500)
    {
      if(0) std::cout<<"\n\tHT>=1250 && HT<1500\t"<<HT<<std::endl;
      
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_1250ht1500_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	} 
    }  
  else if (HT>=1500 && HT<2000)
    {
      if(0) std::cout<<"\n\tHT>=1500 && HT<2000\t"<<HT<<std::endl;
            
      // Fill Denominator Plots
      h_Den_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel -> Fill(Pt6thJet);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_1BTag -> Fill(Pt6thJet);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_2BTag -> Fill(Pt6thJet);
	}
      if (Passed_OR)
	{
	  h_Num_pt6thJet_Vs_1500ht2000_RefTrg_OfflineSel_OR -> Fill(Pt6thJet);
	}
    }
  
  
  if(Pt6thJet>=40 && Pt6thJet<50)
    {
      if(0) std::cout<<"\n\tPt6thJet>=40 && Pt6thJet<50\t"<<Pt6thJet<<std::endl;      
      
      // Fill Denominator Plots
      h_Den_ht_Vs_40pt50_RefTrg_OfflineSel -> Fill(HT);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_1BTag -> Fill(HT);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_2BTag -> Fill(HT);
	}
      if (Passed_OR)
	{
	  h_Num_ht_Vs_40pt50_RefTrg_OfflineSel_OR -> Fill(HT);
	}
    }
  
  if(Pt6thJet>=50 && Pt6thJet<60)
    {
      if(0) std::cout<<"\n\tPt6thJet>=50 && Pt6thJet<60\t"<<Pt6thJet<<std::endl;      
                  
      // Fill Denominator Plots
      h_Den_ht_Vs_50pt60_RefTrg_OfflineSel -> Fill(HT);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_1BTag -> Fill(HT);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_2BTag -> Fill(HT);
	}
      if (Passed_OR)
	{
	  h_Num_ht_Vs_50pt60_RefTrg_OfflineSel_OR -> Fill(HT);
	}
    }
  
  if(Pt6thJet>=60 && Pt6thJet<70)
    {
      if(0) std::cout<<"\n\tPt6thJet>=60 && Pt6thJet<70\t"<<Pt6thJet<<std::endl;      
                        
      // Fill Denominator Plots
      h_Den_ht_Vs_60pt70_RefTrg_OfflineSel -> Fill(HT);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_1BTag -> Fill(HT);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_2BTag -> Fill(HT);
	}
      if (Passed_OR)
	{
	  h_Num_ht_Vs_60pt70_RefTrg_OfflineSel_OR -> Fill(HT);
	}
    }
 
  if(Pt6thJet>=70 && Pt6thJet<90)
    {
      if(0) std::cout<<"\n\tPt6thJet>=70 && Pt6thJet<90\t"<<Pt6thJet<<std::endl;      
                        
      // Fill Denominator Plots
      h_Den_ht_Vs_70pt90_RefTrg_OfflineSel -> Fill(HT);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_1BTag -> Fill(HT);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_2BTag -> Fill(HT);
	}
      if (Passed_OR)
	{
	  h_Num_ht_Vs_70pt90_RefTrg_OfflineSel_OR -> Fill(HT);
	}
    }
  
  if(Pt6thJet>=90 && Pt6thJet<120)
    {
      if(0) std::cout<<"\n\tPt6thJet>=90 && Pt6thJet<120\t"<<Pt6thJet<<std::endl;      
      
      // Fill Denominator Plots
      h_Den_ht_Vs_90pt120_RefTrg_OfflineSel -> Fill(HT);
      
      // Fill Numerator Plots
      if (Passed_HLT_PFHT450_SixJet40_BTagCSV_p056)
	{
	  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_1BTag -> Fill(HT);
	}
      if (Passed_HLT_PFHT400_SixJet30_DoubleBTagCSV_p056)
	{
	  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_2BTag -> Fill(HT);
	}
      if (Passed_OR)
	{
	  h_Num_ht_Vs_90pt120_RefTrg_OfflineSel_OR -> Fill(HT);
	}
    }
  
  */
  
  




  //================================================================================================
  // Finalize
  //================================================================================================
  fEventSaver.save();
}


double JetTriggersSF::DeltaEta(double eta1, double eta2)
{
  // See: https://cmssdt.cern.ch/SDT/doxygen/CMSSW_4_4_2/doc/html/d1/d92/DataFormats_2Math_2interface_2deltaPhi_8h_source.html       
  double deltaEta = fabs ( eta1 - eta2 );
  return deltaEta;

}

double JetTriggersSF::DeltaPhi(double phi1, double phi2)
{
  // See: https://cmssdt.cern.ch/SDT/doxygen/CMSSW_4_4_2/doc/html/d1/d92/DataFormats_2Math_2interface_2deltaPhi_8h_source.html
  double PI = 3.14159265;
  double result = phi1 - phi2;
  while (result > PI) result -= 2*PI;
  while (result <= -PI) result += 2*PI;

  return result;
}

double JetTriggersSF::DeltaR(double eta1, double eta2,
                             double phi1, double phi2)
{

  double dEta = DeltaEta(eta1, eta2);
  double dPhi = DeltaPhi(phi1, phi2);
  double dR = TMath::Sqrt(TMath::Power(dEta,2)+TMath::Power(dPhi,2));

  return dR;
}

