// -*- c++ -*-
#include "Framework/interface/BaseSelector.h"
#include "Framework/interface/makeTH.h"

// User
#include "Auxiliary/interface/Table.h"
#include "Auxiliary/interface/Tools.h"
#include "Tools/interface/MCTools.h"
#include "EventSelection/interface/CommonPlots.h"
#include "EventSelection/interface/EventSelections.h"

// ROOT
#include "TDirectory.h"
#include "Math/VectorUtil.h"

struct PtComparator
{
  bool operator() (const math::XYZTLorentzVector p1, const math::XYZTLorentzVector p2) const { return ( p1.pt() > p2.pt() ); }
};


class Kinematics: public BaseSelector {
public:
  explicit Kinematics(const ParameterSet& config, const TH1* skimCounters);
  virtual ~Kinematics() {}

  /// Books histograms
  virtual void book(TDirectory *dir) override;
  /// Sets up branches for reading the TTree
  virtual void setupBranches(BranchManager& branchManager) override;
  /// Called for each event
  virtual void process(Long64_t entry) override;
   
private:
  // Input parameters
  const double cfg_Verbose;
  Tools auxTools;
  
  // Counters
  Count cAllEvents;
  // Count cTrigger;
  Count cHtb_HPlus;
  Count cHtb_TQuark;
  Count cHtb_BQuark;
  Count cHtb_tbW_BQuark;
  Count cHtb_tbW_WBoson;
  Count cHtb_tbW_Wqq_Quark;
  Count cHtb_tbW_Wqq_AntiQuark;
  Count cHtb_tbW_Wqq_Leptons;
  Count cgtt_TQuark;
  Count cgbb_BQuark;
  Count cgtt_tbW_Wqq_Quark;
  Count cgtt_tbW_Wqq_AntiQuark;
  Count cgtt_tbW_Wqq_Leptons;
  Count cgtt_tbW_WBoson;
  Count cgtt_tbW_BQuark;

  
  // Non-common histograms
  WrappedTH1 *h_genMET_Et;
  WrappedTH1 *h_genMET_Phi;

  WrappedTH1 *h_genHT_GenParticles;
  WrappedTH1 *h_genHT_GenJets;  

  WrappedTH1 *h_gtt_TQuark_Pt;
  WrappedTH1 *h_gtt_tbW_WBoson_Pt;
  WrappedTH1 *h_gtt_tbW_BQuark_Pt;
  WrappedTH1 *h_gtt_tbW_Wqq_Quark_Pt;
  WrappedTH1 *h_gtt_tbW_Wqq_AntiQuark_Pt;
  WrappedTH1 *h_tbH_HPlus_Pt;
  WrappedTH1 *h_tbH_TQuark_Pt;
  WrappedTH1 *h_tbH_BQuark_Pt;
  WrappedTH1 *h_tbH_tbW_WBoson_Pt;
  WrappedTH1 *h_tbH_tbW_BQuark_Pt;
  WrappedTH1 *h_gbb_BQuark_Pt;
  WrappedTH1 *h_Htb_tbW_Wqq_Quark_Pt;
  WrappedTH1 *h_Htb_tbW_Wqq_AntiQuark_Pt;

  WrappedTH1 *h_gtt_TQuark_Eta;
  WrappedTH1 *h_gtt_tbW_WBoson_Eta;
  WrappedTH1 *h_gtt_tbW_BQuark_Eta;
  WrappedTH1 *h_gtt_tbW_Wqq_Quark_Eta;
  WrappedTH1 *h_gtt_tbW_Wqq_AntiQuark_Eta;  
  WrappedTH1 *h_tbH_HPlus_Eta;
  WrappedTH1 *h_tbH_TQuark_Eta;
  WrappedTH1 *h_tbH_BQuark_Eta;
  WrappedTH1 *h_tbH_tbW_WBoson_Eta;
  WrappedTH1 *h_tbH_tbW_BQuark_Eta;
  WrappedTH1 *h_gbb_BQuark_Eta;
  WrappedTH1 *h_Htb_tbW_Wqq_Quark_Eta;
  WrappedTH1 *h_Htb_tbW_Wqq_AntiQuark_Eta;

  WrappedTH1 *h_gtt_TQuark_Rap;
  WrappedTH1 *h_gtt_tbW_WBoson_Rap;
  WrappedTH1 *h_gtt_tbW_BQuark_Rap;
  WrappedTH1 *h_gtt_tbW_Wqq_Quark_Rap;
  WrappedTH1 *h_gtt_tbW_Wqq_AntiQuark_Rap;  
  WrappedTH1 *h_tbH_HPlus_Rap;
  WrappedTH1 *h_tbH_TQuark_Rap;
  WrappedTH1 *h_tbH_BQuark_Rap;
  WrappedTH1 *h_tbH_tbW_WBoson_Rap;
  WrappedTH1 *h_tbH_tbW_BQuark_Rap;
  WrappedTH1 *h_gbb_BQuark_Rap;
  WrappedTH1 *h_Htb_tbW_Wqq_Quark_Rap;
  WrappedTH1 *h_Htb_tbW_Wqq_AntiQuark_Rap;

  WrappedTH1 *h_gtt_TQuark_Phi;
  WrappedTH1 *h_gtt_tbW_WBoson_Phi;
  WrappedTH1 *h_gtt_tbW_BQuark_Phi;
  WrappedTH1 *h_gtt_tbW_Wqq_Quark_Phi;
  WrappedTH1 *h_gtt_tbW_Wqq_AntiQuark_Phi;  
  WrappedTH1 *h_tbH_HPlus_Phi;
  WrappedTH1 *h_tbH_TQuark_Phi;
  WrappedTH1 *h_tbH_BQuark_Phi;
  WrappedTH1 *h_tbH_tbW_WBoson_Phi;
  WrappedTH1 *h_tbH_tbW_BQuark_Phi;
  WrappedTH1 *h_gbb_BQuark_Phi;
  WrappedTH1 *h_Htb_tbW_Wqq_Quark_Phi;
  WrappedTH1 *h_Htb_tbW_Wqq_AntiQuark_Phi;
  
  WrappedTH1 *h_Htb_TQuark_Htb_BQuark_dR;
  WrappedTH1 *h_Htb_TQuark_gtt_TQuark_dR;
  WrappedTH1 *h_Htb_TQuark_gbb_BQuark_dR;

  WrappedTH1 *h_Htb_TQuark_Htb_BQuark_dEta;
  WrappedTH1 *h_Htb_TQuark_gtt_TQuark_dEta;
  WrappedTH1 *h_Htb_TQuark_gbb_BQuark_dEta;
  
  WrappedTH1 *h_Htb_TQuark_Htb_BQuark_dPhi;
  WrappedTH1 *h_Htb_TQuark_gtt_TQuark_dPhi;
  WrappedTH1 *h_Htb_TQuark_gbb_BQuark_dPhi;
  
  WrappedTH1 *h_Htb_TQuark_Htb_BQuark_dRap;
  WrappedTH1 *h_Htb_TQuark_gtt_TQuark_dRap;
  WrappedTH1 *h_Htb_TQuark_gbb_BQuark_dRap;
  
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_BQuark_dR;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_Quark_dR;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dR;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dR;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dR;
  WrappedTH1 *h_gtt_TQuark_gbb_BQuark_dR;
  WrappedTH1 *h_gtt_TQuark_gtt_tbW_BQuark_dR;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dR;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dR;

  WrappedTH1 *h_Htb_BQuark_Htb_tbW_BQuark_dEta;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_Quark_dEta;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dEta;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dEta;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dEta;
  WrappedTH1 *h_gtt_TQuark_gbb_BQuark_dEta;
  WrappedTH1 *h_gtt_TQuark_gtt_tbW_BQuark_dEta;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dEta;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dEta;

  WrappedTH1 *h_Htb_BQuark_Htb_tbW_BQuark_dPhi;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_Quark_dPhi;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dPhi;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi;
  WrappedTH1 *h_gtt_TQuark_gbb_BQuark_dPhi;
  WrappedTH1 *h_gtt_TQuark_gtt_tbW_BQuark_dPhi;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dPhi;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dPhi;
  
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_BQuark_dRap;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_Quark_dRap;
  WrappedTH1 *h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dRap;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dRap;
  WrappedTH1 *h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dRap;
  WrappedTH1 *h_gtt_TQuark_gbb_BQuark_dRap;
  WrappedTH1 *h_gtt_TQuark_gtt_tbW_BQuark_dRap;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dRap;
  WrappedTH1 *h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dRap;
  
  WrappedTH1 *h_BQuark1_Pt;
  WrappedTH1 *h_BQuark2_Pt;
  WrappedTH1 *h_BQuark3_Pt;
  WrappedTH1 *h_BQuark4_Pt;

  WrappedTH1 *h_BQuark1_Eta;
  WrappedTH1 *h_BQuark2_Eta;
  WrappedTH1 *h_BQuark3_Eta;
  WrappedTH1 *h_BQuark4_Eta;

  WrappedTH1 *h_BQuark1_Rap;
  WrappedTH1 *h_BQuark2_Rap;
  WrappedTH1 *h_BQuark3_Rap;
  WrappedTH1 *h_BQuark4_Rap;

  WrappedTH1 *h_BQuark1_Phi;
  WrappedTH1 *h_BQuark2_Phi;
  WrappedTH1 *h_BQuark3_Phi;
  WrappedTH1 *h_BQuark4_Phi;

  WrappedTH1 *h_BQuarkPair_dRMin_pT;
  WrappedTH1 *h_BQuarkPair_dRMin_dEta;
  WrappedTH1 *h_BQuarkPair_dRMin_dPhi;
  WrappedTH1 *h_BQuarkPair_dRMin_dR;
  WrappedTH1 *h_BQuarkPair_dRMin_Mass;
  
  WrappedTH1 *h_Htb_tbW_bqq_Pt;
  WrappedTH1 *h_Htb_tbW_bqq_Rap;
  WrappedTH1 *h_Htb_tbW_bqq_Mass;
  WrappedTH1 *h_gtt_tbW_bqq_Pt;
  WrappedTH1 *h_gtt_tbW_bqq_Rap;
  WrappedTH1 *h_gtt_tbW_bqq_Mass;

  WrappedTH1 *h_SelGenJet_Multiplicity;

  WrappedTH1 *h_MaxDiJetMass_Pt;
  WrappedTH1 *h_MaxDiJetMass_Eta;
  WrappedTH1 *h_MaxDiJetMass_Rap; 
  WrappedTH1 *h_MaxDiJetMass_Mass;
  WrappedTH1 *h_MaxDiJetMass_dR;
  WrappedTH1 *h_MaxDiJetMass_dRrap;
  WrappedTH1 *h_MaxDiJetMass_dEta;
  WrappedTH1 *h_MaxDiJetMass_dPhi;
  WrappedTH1 *h_MaxDiJetMass_dRap;
  WrappedTH2 *h_MaxDiJetMass_dEta_Vs_dPhi;
  WrappedTH2 *h_MaxDiJetMass_dRap_Vs_dPhi;
  
  WrappedTH1 *h_GenJet1_Pt;
  WrappedTH1 *h_GenJet2_Pt;
  WrappedTH1 *h_GenJet3_Pt;
  WrappedTH1 *h_GenJet4_Pt;
  WrappedTH1 *h_GenJet5_Pt;
  WrappedTH1 *h_GenJet6_Pt;

  WrappedTH1 *h_GenJet1_Eta;
  WrappedTH1 *h_GenJet2_Eta;
  WrappedTH1 *h_GenJet3_Eta;
  WrappedTH1 *h_GenJet4_Eta;
  WrappedTH1 *h_GenJet5_Eta;
  WrappedTH1 *h_GenJet6_Eta;

  WrappedTH1 *h_GenJet1_Rap;
  WrappedTH1 *h_GenJet2_Rap;
  WrappedTH1 *h_GenJet3_Rap;
  WrappedTH1 *h_GenJet4_Rap;
  WrappedTH1 *h_GenJet5_Rap;
  WrappedTH1 *h_GenJet6_Rap;

  // Correlations 
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet1_Pt;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet2_Pt;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet3_Pt;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet4_Pt;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet5_Pt;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet6_Pt;

  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet1_Eta;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet2_Eta;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet3_Eta;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet4_Eta;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet5_Eta;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet6_Eta;

  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet1_Rap;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet2_Rap;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet3_Rap;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet4_Rap;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet5_Rap;
  WrappedTH1 *h_AL3CJetsFromHPlus_GenJet6_Rap;

  WrappedTH2 *h_BQuark1_BQuark2_dEta_Vs_dPhi;
  WrappedTH2 *h_BQuark1_BQuark3_dEta_Vs_dPhi;
  WrappedTH2 *h_BQuark1_BQuark4_dEta_Vs_dPhi;
  WrappedTH2 *h_BQuark2_BQuark3_dEta_Vs_dPhi;
  WrappedTH2 *h_BQuark2_BQuark4_dEta_Vs_dPhi;
  WrappedTH2 *h_BQuark3_BQuark4_dEta_Vs_dPhi;

  WrappedTH2 *h_Jet1Jet2_dEta_Vs_Jet3Jet4_dEta;
  WrappedTH2 *h_Jet1Jet2_dPhi_Vs_Jet3Jet4_dPhi;  
  WrappedTH2 *h_Jet1Jet2_dEta_Vs_Jet1Jet2_Mass;
  WrappedTH2 *h_Jet3Jet4_dEta_Vs_Jet3Jet4_Mass;

};

#include "Framework/interface/SelectorFactory.h"
REGISTER_SELECTOR(Kinematics);

Kinematics::Kinematics(const ParameterSet& config, const TH1* skimCounters)
  : BaseSelector(config, skimCounters),
    cfg_Verbose(config.getParameter<bool>("verbose")),
    cAllEvents(fEventCounter.addCounter("All events")),
    cHtb_HPlus(fEventCounter.addCounter("H+")),
    cHtb_TQuark(fEventCounter.addCounter("H+->tb, t")),
    cHtb_BQuark(fEventCounter.addCounter("H+->tb, b")),
    cHtb_tbW_BQuark(fEventCounter.addCounter("H+->tb, t->bW, b")),
    cHtb_tbW_WBoson(fEventCounter.addCounter("H+->tb, t->bW, W+")),
    cHtb_tbW_Wqq_Quark(fEventCounter.addCounter("H+->tb, t->bW, W->qq, q")),
    cHtb_tbW_Wqq_AntiQuark(fEventCounter.addCounter("H+->tb, t->bW, W->qq, qbar")),
    cHtb_tbW_Wqq_Leptons(fEventCounter.addCounter("H+->tb, t->bW, W->l v")),
    cgtt_TQuark(fEventCounter.addCounter("g->tt, t")),
    cgbb_BQuark(fEventCounter.addCounter("g->bb, b")),
    cgtt_tbW_Wqq_Quark(fEventCounter.addCounter("g->tt, t->bW, W->qq, q")),
    cgtt_tbW_Wqq_AntiQuark(fEventCounter.addCounter("g->tt, t->bW, W->qq, qbar")),
    cgtt_tbW_Wqq_Leptons(fEventCounter.addCounter("g->tt, t->bW, W->l v")),
    cgtt_tbW_WBoson(fEventCounter.addCounter("g->tt, t->bW, W")),
    cgtt_tbW_BQuark(fEventCounter.addCounter("g->tt, t->bW, b"))
  
{ }

void Kinematics::book(TDirectory *dir) {

  // Event Variables
  h_genMET_Et         =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "genMET_Et"          , ";Gen E_{T}^{miss} (GeV)"       , 60,  0.0,   +300.0);
  h_genMET_Phi        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "genMET_Phi"         , ";Gen E_{T}^{miss} #phi (rads)" , 64,  -3.2,    +3.2);
  h_genHT_GenParticles=  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "genHT_GenParticles" , ";GenP H_{T} (GeV)"             ,  75,  0.0, +1500.0);
  h_genHT_GenJets     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "genHT_GenJets"      , ";GenJ H_{T} (GeV)"             ,  75,  0.0, +1500.0);
  

  // Signal GenParticles
  h_gtt_TQuark_Pt            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_Pt"           , "gtt, t-quark pT"        , 50, 0.0, 500.0);
  h_gtt_tbW_WBoson_Pt        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_WBoson_Pt"       , "gtt, tWb W-boson pT"    , 50, 0.0, 500.0);
  h_gtt_tbW_BQuark_Pt        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_Pt"       , "gtt, tWb b-quark pT"    , 50, 0.0, 500.0);
  h_gtt_tbW_Wqq_Quark_Pt     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_Quark_Pt"    , "gtt, tWb, Wqq, Q pT"    , 50, 0.0, 500.0);
  h_gtt_tbW_Wqq_AntiQuark_Pt =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_AntiQuark_Pt", "gtt, tWb, Wqq, Qbar pT" , 50, 0.0, 500.0);
  h_tbH_HPlus_Pt             =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_HPlus_Pt"            , "tbH, HPlus pT"          , 50, 0.0, 500.0);
  h_tbH_TQuark_Pt            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_TQuark_Pt"           , "tbH, t-quark pT"        , 50, 0.0, 500.0);
  h_tbH_BQuark_Pt            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_BQuark_Pt"           , "tbH, b-quark pT"        , 50, 0.0, 500.0);
  h_tbH_tbW_WBoson_Pt        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_WBoson_Pt"       , "tbH, tbW, W-boson pT"   , 50, 0.0, 500.0);
  h_tbH_tbW_BQuark_Pt        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_BQuark_Pt"       , "tbH, tbW, b-quark pT"   , 50, 0.0, 500.0);
  h_gbb_BQuark_Pt            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gbb_BQuark_Pt"           , "gtt, b-quark pT, "      , 50, 0.0, 500.0);
  h_Htb_tbW_Wqq_Quark_Pt     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_Quark_Pt"    , "Htb, tbW, Q pT, "       , 50, 0.0, 500.0);
  h_Htb_tbW_Wqq_AntiQuark_Pt =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_AntiQuark_Pt", "Htb, tbW, Qbar pT, "    , 50, 0.0, 500.0);

  //h_gtt_TQuark_Eta            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_Eta"           , "gtt, t-quark eta"        , 50, -2.5, +2.5);
  h_gtt_TQuark_Eta            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_Eta"           , "gtt, t-quark eta"        , 100, -5.0, +5.0);
  h_gtt_tbW_WBoson_Eta        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_WBoson_Eta"       , "gtt, tWb W-boson eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_BQuark_Eta        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_Eta"       , "gtt, tWb b-quark eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_Wqq_Quark_Eta     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_Quark_Eta"    , "gtt, tWb, Wqq, Q eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_Wqq_AntiQuark_Eta =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_AntiQuark_Eta", "gtt, tWb, Wqq, Qbar eta" , 100, -5.0, +5.0);
  h_tbH_HPlus_Eta             =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_HPlus_Eta"            , "tbH, HPlus eta"          , 100, -5.0, +5.0);
  h_tbH_TQuark_Eta            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_TQuark_Eta"           , "tbH, t-quark eta"        , 100, -5.0, +5.0);
  h_tbH_BQuark_Eta            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_BQuark_Eta"           , "tbH, b-quark eta"        , 100, -5.0, +5.0);
  h_tbH_tbW_WBoson_Eta        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_WBoson_Eta"       , "tbH, tbW, W-boson eta"   , 100, -5.0, +5.0);
  h_tbH_tbW_BQuark_Eta        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_BQuark_Eta"       , "tbH, tbW, b-quark eta"   , 100, -5.0, +5.0);
  h_gbb_BQuark_Eta            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gbb_BQuark_Eta"           , "gtt, b-quark eta, "      , 100, -5.0, +5.0);
  h_Htb_tbW_Wqq_Quark_Eta     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_Quark_Eta"    , "Htb, tbW, Q eta, "       , 100, -5.0, +5.0);
  h_Htb_tbW_Wqq_AntiQuark_Eta =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_AntiQuark_Eta", "Htb, tbW, Qbar eta, "    , 100, -5.0, +5.0);

  h_gtt_TQuark_Rap            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_Rap"           , "gtt, t-quark eta"        , 100, -5.0, +5.0);
  h_gtt_tbW_WBoson_Rap        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_WBoson_Rap"       , "gtt, tWb W-boson eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_BQuark_Rap        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_Rap"       , "gtt, tWb b-quark eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_Wqq_Quark_Rap     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_Quark_Rap"    , "gtt, tWb, Wqq, Q eta"    , 100, -5.0, +5.0);
  h_gtt_tbW_Wqq_AntiQuark_Rap =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_Wqq_AntiQuark_Rap", "gtt, tWb, Wqq, Qbar eta" , 100, -5.0, +5.0);
  h_tbH_HPlus_Rap             =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_HPlus_Rap"            , "tbH, HPlus eta"          , 100, -5.0, +5.0);
  h_tbH_TQuark_Rap            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_TQuark_Rap"           , "tbH, t-quark eta"        , 100, -5.0, +5.0);
  h_tbH_BQuark_Rap            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_BQuark_Rap"           , "tbH, b-quark eta"        , 100, -5.0, +5.0);
  h_tbH_tbW_WBoson_Rap        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_WBoson_Rap"       , "tbH, tbW, W-boson eta"   , 100, -5.0, +5.0);
  h_tbH_tbW_BQuark_Rap        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "tbH_tbW_BQuark_Rap"       , "tbH, tbW, b-quark eta"   , 100, -5.0, +5.0);
  h_gbb_BQuark_Rap            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gbb_BQuark_Rap"           , "gtt, b-quark eta, "      , 100, -5.0, +5.0);
  h_Htb_tbW_Wqq_Quark_Rap     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_Quark_Rap"    , "Htb, tbW, Q eta, "       , 100, -5.0, +5.0);
  h_Htb_tbW_Wqq_AntiQuark_Rap =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_Wqq_AntiQuark_Rap", "Htb, tbW, Qbar eta, "    , 100, -5.0, +5.0);

  h_gtt_TQuark_Phi            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gtt_TQuark_Phi"           , "gtt, t-quark phi"       , 64, -3.2, +3.2);
  h_gtt_tbW_WBoson_Phi        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gtt_tbW_WBoson_Phi"       , "gtt, tWb W-boson phi"   , 64, -3.2, +3.2);
  h_gtt_tbW_BQuark_Phi        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gtt_tbW_BQuark_Phi"       , "gtt, tWb b-quark phi"   , 64, -3.2, +3.2);
  h_gtt_tbW_Wqq_Quark_Phi     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gtt_tbW_Wqq_Quark_Phi"    , "gtt, tWb, Wqq, Q phi"   , 64, -3.2, +3.2);
  h_gtt_tbW_Wqq_AntiQuark_Phi =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gtt_tbW_Wqq_AntiQuark_Phi", "gtt, tWb, Wqq, Qbar phi", 64, -3.2, +3.2);
  h_tbH_HPlus_Phi             =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "tbH_HPlus_Phi"            , "tbH, HPlus phi"         , 64, -3.2, +3.2);
  h_tbH_TQuark_Phi            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "tbH_TQuark_Phi"           , "tbH, t-quark phi"       , 64, -3.2, +3.2);
  h_tbH_BQuark_Phi            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "tbH_BQuark_Phi"           , "tbH, b-quark phi"       , 64, -3.2, +3.2);
  h_tbH_tbW_WBoson_Phi        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "tbH_tbW_WBoson_Phi"       , "tbH, tbW, W-boson phi"  , 64, -3.2, +3.2);
  h_tbH_tbW_BQuark_Phi        =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "tbH_tbW_BQuark_Phi"       , "tbH, tbW, b-quark phi"  , 64, -3.2, +3.2);
  h_gbb_BQuark_Phi            =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "gbb_BQuark_Phi"           , "gtt, b-quark phi, "     , 64, -3.2, +3.2);
  h_Htb_tbW_Wqq_Quark_Phi     =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "Htb_tbW_Wqq_Quark_Phi"    , "Htb, tbW, Q phi, "      , 64, -3.2, +3.2);
  h_Htb_tbW_Wqq_AntiQuark_Phi =  fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "Htb_tbW_Wqq_AntiQuark_Phi", "Htb, tbW, Qbar phi, "   , 64, -3.2, +3.2);

  // deltaR
  h_Htb_TQuark_Htb_BQuark_dR                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_Htb_BQuark_dR"               , "dR(t, b)", 50, 0.0, +10.0);
  h_Htb_TQuark_gtt_TQuark_dR                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gtt_TQuark_dR"               , "dR(t, t)", 50, 0.0, +10.0);
  h_Htb_TQuark_gbb_BQuark_dR                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gbb_BQuark_dR"               , "dR(t, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_BQuark_dR            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_BQuark_dR"           , "dR(b, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dR         = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_Quark_dR"        , "dR(b, q)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dR     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dR"    , "dR(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dR     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dR"    , "dR(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dR", "dR(b, q)", 50, 0.0, +10.0);
  h_gtt_TQuark_gbb_BQuark_dR                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gbb_BQuark_dR"               , "dR(b, b)", 50, 0.0, +10.0);
  h_gtt_TQuark_gtt_tbW_BQuark_dR            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gtt_tbW_BQuark_dR"           , "dR(t, b)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dR     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dR"    , "dR(b, q)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dR = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dR", "dR(b, q)", 50, 0.0, +10.0);

  h_Htb_TQuark_Htb_BQuark_dEta                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_Htb_BQuark_dEta"               , "dEta(t, b)", 50, 0.0, +10.0);
  h_Htb_TQuark_gtt_TQuark_dEta                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gtt_TQuark_dEta"               , "dEta(t, t)", 50, 0.0, +10.0);
  h_Htb_TQuark_gbb_BQuark_dEta                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gbb_BQuark_dEta"               , "dEta(t, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_BQuark_dEta            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_BQuark_dEta"           , "dEta(b, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dEta         = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_Quark_dEta"        , "dEta(b, q)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dEta     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dEta"    , "dEta(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dEta     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dEta"    , "dEta(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dEta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dEta", "dEta(b, q)", 50, 0.0, +10.0);
  h_gtt_TQuark_gbb_BQuark_dEta                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gbb_BQuark_dEta"               , "dEta(b, b)", 50, 0.0, +10.0);
  h_gtt_TQuark_gtt_tbW_BQuark_dEta            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gtt_tbW_BQuark_dEta"           , "dEta(t, b)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dEta     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dEta"    , "dEta(b, q)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dEta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dEta", "dEta(b, q)", 50, 0.0, +10.0);

  h_Htb_TQuark_Htb_BQuark_dPhi                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_Htb_BQuark_dPhi"               , "dPhi(t, b)", 32, 0.0, +3.2);
  h_Htb_TQuark_gtt_TQuark_dPhi                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gtt_TQuark_dPhi"               , "dPhi(t, t)", 32, 0.0, +3.2);
  h_Htb_TQuark_gbb_BQuark_dPhi                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gbb_BQuark_dPhi"               , "dPhi(t, b)", 32, 0.0, +3.2);
  h_Htb_BQuark_Htb_tbW_BQuark_dPhi            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_BQuark_dPhi"           , "dPhi(b, b)", 32, 0.0, +3.2);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dPhi         = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_Quark_dPhi"        , "dPhi(b, q)", 32, 0.0, +3.2);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi"    , "dPhi(b, q)", 32, 0.0, +3.2);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dPhi     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dPhi"    , "dPhi(b, q)", 32, 0.0, +3.2);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi", "dPhi(b, q)", 32, 0.0, +3.2);  
  h_gtt_TQuark_gbb_BQuark_dPhi                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gbb_BQuark_dPhi"               , "dPhi(b, b)", 32, 0.0, +3.2);
  h_gtt_TQuark_gtt_tbW_BQuark_dPhi            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gtt_tbW_BQuark_dPhi"           , "dPhi(t, b)", 32, 0.0, +3.2);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dPhi     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dPhi"    , "dPhi(b, q)", 32, 0.0, +3.2);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dPhi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dPhi", "dPhi(b, q)", 32, 0.0, +3.2);

  h_Htb_TQuark_Htb_BQuark_dRap                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_Htb_BQuark_dRap"               , "dRap(t, b)", 50, 0.0, +10.0);
  h_Htb_TQuark_gtt_TQuark_dRap                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gtt_TQuark_dRap"               , "dRap(t, t)", 50, 0.0, +10.0);
  h_Htb_TQuark_gbb_BQuark_dRap                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_TQuark_gbb_BQuark_dRap"               , "dRap(t, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_BQuark_dRap            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_BQuark_dRap"           , "dRap(b, b)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dRap         = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_Quark_dRap"        , "dRap(b, q)", 50, 0.0, +10.0);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dRap     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dRap"    , "dRap(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dRap     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dRap"    , "dRap(b, q)", 50, 0.0, +10.0);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dRap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dRap", "dRap(b, q)", 50, 0.0, +10.0);
  h_gtt_TQuark_gbb_BQuark_dRap                = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gbb_BQuark_dRap"               , "dRap(b, b)", 50, 0.0, +10.0);
  h_gtt_TQuark_gtt_tbW_BQuark_dRap            = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_TQuark_gtt_tbW_BQuark_dRap"           , "dRap(t, b)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dRap     = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dRap"    , "dRap(b, q)", 50, 0.0, +10.0);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dRap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dRap", "dRap(b, q)", 50, 0.0, +10.0);
  
  // B-quarks
  h_BQuark1_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark1_Pt", "Ldg b-quark, pT"                         , 50, 0.0, +500.0);
  h_BQuark2_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark2_Pt", "Next-to-Ldg b-quark, pT"                 , 50, 0.0, +500.0);
  h_BQuark3_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark3_Pt", "Next-to-Next-to-Ldg b-quark, pT"         , 50, 0.0, +500.0);
  h_BQuark4_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark4_Pt", "Next-to-Next-to-Next-to-Ldg b-quark, pT" , 50, 0.0, +500.0);

  h_BQuark1_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark1_Eta", "Ldg b-quark, eta"                         , 100, -5.0, +5.0);
  h_BQuark2_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark2_Eta", "Next-to-Ldg b-quark, eta"                 , 100, -5.0, +5.0);
  h_BQuark3_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark3_Eta", "Next-to-Next-to-Ldg b-quark, eta"         , 100, -5.0, +5.0);
  h_BQuark4_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark4_Eta", "Next-to-Next-to-Next-to-Ldg b-quark, eta" , 100, -5.0, +5.0);

  h_BQuark1_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark1_Rap", "Ldg b-quark, eta"                         , 100, -5.0, +5.0);
  h_BQuark2_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark2_Rap", "Next-to-Ldg b-quark, eta"                 , 100, -5.0, +5.0);
  h_BQuark3_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark3_Rap", "Next-to-Next-to-Ldg b-quark, eta"         , 100, -5.0, +5.0);
  h_BQuark4_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuark4_Rap", "Next-to-Next-to-Next-to-Ldg b-quark, eta" , 100, -5.0, +5.0);

  h_BQuark1_Phi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "BQuark1_Phi", "Ldg b-quark, phi"                         , 64, -3.2, +3.2);
  h_BQuark2_Phi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "BQuark2_Phi", "Next-to-Ldg b-quark, phi"                 , 64, -3.2, +3.2);
  h_BQuark3_Phi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "BQuark3_Phi", "Next-to-Next-to-Ldg b-quark, phi"         , 64, -3.2, +3.2);
  h_BQuark4_Phi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kInformative, dir, "BQuark4_Phi", "Next-to-Next-to-Next-to-Ldg b-quark, phi" , 64, -3.2, +3.2);

  h_BQuarkPair_dRMin_pT   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuarkPair_dRMin_pT"  , ";#DeltaR_{min}(bb) p_{T} (GeV/c)"     ,  50, 0.0, +500.0);
  h_BQuarkPair_dRMin_dEta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuarkPair_dRMin_dEta", ";#DeltaR_{min}(bb) #Delta#eta"        ,  50, 0.0,  +10.0);
  h_BQuarkPair_dRMin_dPhi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuarkPair_dRMin_dPhi", ";#DeltaR_{min}(bb) #Delta#phi (rads)" ,  32, 0.0,   +3.2);
  h_BQuarkPair_dRMin_dR   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuarkPair_dRMin_dR"  , ";#DeltaR_{min}(bb) #DeltaR"           ,  50, 0.0,  +10.0);
  h_BQuarkPair_dRMin_Mass = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "BQuarkPair_dRMin_Mass", ";#DeltaR_{min}(bb) M (GeV/c^{2})"     ,  50, 0.0, +500.0);
  
  // Trijet systems
  h_Htb_tbW_bqq_Pt   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_bqq_Pt"  , ";bqq (H^{+}) p_{T} (GeV/c)" ,  50,  0.0, +500.0);
  h_Htb_tbW_bqq_Rap  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_bqq_Rap" , ";bqq (H^{+}) #omega"        , 100, -5.0,   +5.0);
  h_Htb_tbW_bqq_Mass = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "Htb_tbW_bqq_Mass", ";bqq (H^{+}) M (GeV/c^{2})" ,  50,  0.0, +500.0);
  h_gtt_tbW_bqq_Pt   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_bqq_Pt"  , ";bqq (t) p_{T} (GeV/c^{2})" ,  50,  0.0, +500.0);
  h_gtt_tbW_bqq_Rap  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_bqq_Rap" , ";bqq (t) #omega"            , 100, -5.0,   +5.0);
  h_gtt_tbW_bqq_Mass = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "gtt_tbW_bqq_Mass", ";bqq (t) M (GeV/c^{2})"     ,  50,  0.0, +500.0);  
  
  // Leading Jets
  h_Jet1Jet2_dEta_Vs_Jet3Jet4_dEta = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "Jet1Jet2_dEta_Vs_Jet3Jet4_dEta", ";#Delta#eta;#Delta#eta", 50, 0.0, 10.0, 50, 0.0,10.0);
  h_Jet1Jet2_dPhi_Vs_Jet3Jet4_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "Jet1Jet2_dPhi_Vs_Jet3Jet4_dPhi", ";#Delta#phi;#Delta#phi (rads)", 32, 0.0,  3.2, 32, 0.0, 3.2);
  h_Jet1Jet2_dEta_Vs_Jet1Jet2_Mass = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "Jet1Jet2_dEta_Vs_Jet1Jet2_Mass", ";#Delta#eta;Mass (GeV/c^{2})", 50, 0.0, +10.0,  50, 0.0, +1000.0);
  h_Jet3Jet4_dEta_Vs_Jet3Jet4_Mass = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "Jet3Jet4_dEta_Vs_Jet3Jet4_Mass", ";#Delta#eta;Mass (GeV/c^{2})", 50, 0.0, +10.0,  50, 0.0, +1000.0);
  
  // GenJets
  h_SelGenJet_Multiplicity = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "SelGenJet_Multiplicity", ";N (selected jets)" , 20, -0.5, +19.5);

  // MaxDiJet
  h_MaxDiJetMass_Pt   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_Pt"   , ";M(jj)_{max} p_{T} (GeV/c)"    ,  50,  0.0,  +500.0);
  h_MaxDiJetMass_Eta  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_Eta"  , ";M(jj)_{max} #eta"             , 100, -5.0,    +5.0);
  h_MaxDiJetMass_Rap  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_Rap"  , ";M(jj)_{max} #omega"           , 100, -5.0,    +5.0);
  h_MaxDiJetMass_Mass = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_Mass" , ";M(jj)_{max} M (GeV/c^{2})"    ,  50,  0.0, +1000.0);
  h_MaxDiJetMass_dR   = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_dR"   , ";M(jj)_{max} #DeltaR"          ,  50,  0.0,   +10.0);
  h_MaxDiJetMass_dRrap= fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_dRrap", ";M(jj)_{max} #DeltaR_{#omega}" ,  50,  0.0,   +10.0);
  h_MaxDiJetMass_dEta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_dEta" , ";M(jj)_{max} #Delta#eta"       ,  50,  0.0,   +10.0);
  h_MaxDiJetMass_dPhi = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_dPhi" , ";M(jj)_{max} #Delta#phi"       ,  32,  0.0,    +3.2);
  h_MaxDiJetMass_dRap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "MaxDiJetMass_dRap" , ";M(jj)_{max} #Delta#omega"     ,  50,  0.0,   +10.0);
  h_MaxDiJetMass_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "MaxDiJetMass_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)"  , 50, 0.0, +10.0, 32, 0.0, +3.2);
  h_MaxDiJetMass_dRap_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "MaxDiJetMass_dRap_Vs_dPhi", ";#Delta#omega;#Delta#phi (rads)", 50, 0.0, +10.0, 32, 0.0, +3.2);
  
  h_GenJet1_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet1_Pt", "Ldg genJet 1, pT"  ,  50, 0.0, +500.0);
  h_GenJet2_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet2_Pt", "Ldg genJet 2, pT"  ,  50, 0.0, +500.0);
  h_GenJet3_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet3_Pt", "Ldg genJet 3, pT"  ,  50, 0.0, +500.0);
  h_GenJet4_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet4_Pt", "Ldg genJet 4, pT"  ,  50, 0.0, +500.0);
  h_GenJet5_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet5_Pt", "Ldg genJet 5, pT"  ,  50, 0.0, +500.0);
  h_GenJet6_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet6_Pt", "Ldg genJet 6, pT"  ,  50, 0.0, +500.0);

  h_GenJet1_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet1_Eta", "Ldg genJet 1, eta", 100, -5.0, +5.0);
  h_GenJet2_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet2_Eta", "Ldg genJet 2, eta", 100, -5.0, +5.0);
  h_GenJet3_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet3_Eta", "Ldg genJet 3, eta", 100, -5.0, +5.0);
  h_GenJet4_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet4_Eta", "Ldg genJet 4, eta", 100, -5.0, +5.0);
  h_GenJet5_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet5_Eta", "Ldg genJet 5, eta", 100, -5.0, +5.0);
  h_GenJet6_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet6_Eta", "Ldg genJet 6, eta", 100, -5.0, +5.0);

  h_GenJet1_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet1_Rap", "Ldg genJet 1, rap", 100, -5.0, +5.0);
  h_GenJet2_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet2_Rap", "Ldg genJet 2, rap", 100, -5.0, +5.0);
  h_GenJet3_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet3_Rap", "Ldg genJet 3, rap", 100, -5.0, +5.0);
  h_GenJet4_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet4_Rap", "Ldg genJet 4, rap", 100, -5.0, +5.0);
  h_GenJet5_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet5_Rap", "Ldg genJet 5, rap", 100, -5.0, +5.0);
  h_GenJet6_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "GenJet6_Rap", "Ldg genJet 6, rap", 100, -5.0, +5.0);

  // Correlations
  h_BQuark1_BQuark2_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark1_BQuark2_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);
  h_BQuark1_BQuark3_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark1_BQuark3_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);
  h_BQuark1_BQuark4_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark1_BQuark4_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);
  h_BQuark2_BQuark3_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark2_BQuark3_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);
  h_BQuark2_BQuark4_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark2_BQuark4_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);
  h_BQuark3_BQuark4_dEta_Vs_dPhi = fHistoWrapper.makeTH<TH2F>(HistoLevel::kVital, dir, "BQuark3_BQuark4_dEta_Vs_dPhi", ";#Delta#eta;#Delta#phi (rads)", 100, 0.0, +10.0, 32, 0.0, +3.2);

  h_AL3CJetsFromHPlus_GenJet1_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet1_Pt" , "AL3CJetsFromHplus Jet-1, pT" , 50, 0.0, +500.0);
  h_AL3CJetsFromHPlus_GenJet2_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet2_Pt" , "AL3CJetsFromHplus Jet-2, pT" , 50, 0.0, +500.0);
  h_AL3CJetsFromHPlus_GenJet3_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet3_Pt" , "AL3CJetsFromHplus Jet-3, pT" , 50, 0.0, +500.0);
  h_AL3CJetsFromHPlus_GenJet4_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet4_Pt" , "AL3CJetsFromHplus Jet-4, pT" , 50, 0.0, +500.0); 
  h_AL3CJetsFromHPlus_GenJet5_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet5_Pt" , "AL3CJetsFromHplus Jet-5, pT" , 50, 0.0, +500.0);
  h_AL3CJetsFromHPlus_GenJet6_Pt  = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet6_Pt" , "AL3CJetsFromHplus Jet-6, pT" , 50, 0.0, +500.0);

  h_AL3CJetsFromHPlus_GenJet1_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet1_Eta", "AL3CJetsFromHplus Jet-1, eta", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet2_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet2_Eta", "AL3CJetsFromHplus Jet-2, eta", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet3_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet3_Eta", "AL3CJetsFromHplus Jet-3, eta", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet4_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet4_Eta", "AL3CJetsFromHplus Jet-4, eta", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet5_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet5_Eta", "AL3CJetsFromHplus Jet-5, eta", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet6_Eta = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet6_Eta", "AL3CJetsFromHplus Jet-6, eta", 100, -5.0, +5.0);

  h_AL3CJetsFromHPlus_GenJet1_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet1_Rap", "AL3CJetsFromHplus Jet-1, rap", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet2_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet2_Rap", "AL3CJetsFromHplus Jet-2, rap", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet3_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet3_Rap", "AL3CJetsFromHplus Jet-3, rap", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet4_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet4_Rap", "AL3CJetsFromHplus Jet-4, rap", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet5_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet5_Rap", "AL3CJetsFromHplus Jet-5, rap", 100, -5.0, +5.0);
  h_AL3CJetsFromHPlus_GenJet6_Rap = fHistoWrapper.makeTH<TH1F>(HistoLevel::kVital, dir, "AL3CJetsFromHPlus_GenJet6_Rap", "AL3CJetsFromHplus Jet-6, rap", 100, -5.0, +5.0);

  return;
}

void Kinematics::setupBranches(BranchManager& branchManager) {
  fEvent.setupBranches(branchManager);
}


void Kinematics::process(Long64_t entry) {

  if ( !fEvent.isMC() ) return;
  
  // Create MCools object
  MCTools mcTools(fEvent);
  
  // Increment Counter
  cAllEvents.increment();
  
  // Define the table
  Table table("Evt | Index | PdgId | Status | Charge | Pt | Eta | Phi | E | Vertex (mm) | Mom | Daus (Index)", "Text"); //LaTeX or Text
  // Table table("Evt | Index | PdgId | Status | Charge | Pt | Eta | Phi | E | Vertex (mm) | d0 (mm) | Lxy (mm) | Mom | Daus (Index)", "Text"); //LaTeX or Text
 
 
  // Indices
  int Htb_HPlus_index             = -1.0;
  int Htb_TQuark_index            = -1.0;
  int Htb_BQuark_index            = -1.0;
  int Htb_tbW_BQuark_index        = -1.0;
  int Htb_tbW_WBoson_index        = -1.0;
  int Htb_tbW_Wqq_Quark_index     = -1.0;
  int Htb_tbW_Wqq_AntiQuark_index = -1.0;
  int gtt_TQuark_index            = -1.0;
  int gbb_BQuark_index            = -1.0;
  int gtt_tbW_Wqq_Quark_index     = -1.0;
  int gtt_tbW_Wqq_AntiQuark_index = -1.0;
  int gtt_tbW_WBoson_index        = -1.0;
  int gtt_tbW_BQuark_index        = -1.0;
 
  // 4-momenta
  math::XYZTLorentzVector Htb_HPlus_p4;
  math::XYZTLorentzVector Htb_TQuark_p4;
  math::XYZTLorentzVector Htb_BQuark_p4;
  math::XYZTLorentzVector Htb_tbW_BQuark_p4;
  math::XYZTLorentzVector Htb_tbW_WBoson_p4;
  math::XYZTLorentzVector Htb_tbW_Wqq_Quark_p4;
  math::XYZTLorentzVector Htb_tbW_Wqq_AntiQuark_p4;
  math::XYZTLorentzVector gtt_TQuark_p4;
  math::XYZTLorentzVector gbb_BQuark_p4;
  math::XYZTLorentzVector gtt_tbW_Wqq_Quark_p4;
  math::XYZTLorentzVector gtt_tbW_Wqq_AntiQuark_p4;
  math::XYZTLorentzVector gtt_tbW_WBoson_p4;
  math::XYZTLorentzVector gtt_tbW_BQuark_p4;
  
  int row      = 0;
  bool bWToLNu = false;
  // For-loop: GenParticles
  for (int genP_index=0; genP_index < fEvent.genparticles().getGenParticles().size(); genP_index++) {

    // Create the genParticles
    genParticle p = fEvent.genparticles().getGenParticles()[genP_index];
    genParticle m;
    genParticle g;

    // Particle properties
    int genP_pdgId       = p.pdgId();
    int genP_status      = p.status();

    // Consider only status=22 (intermediate) or status=23 (outgoing) particles
    if( (genP_status != 22) && (genP_status != 23) )continue;

    // Other Particle properties
    double genP_pt       = p.pt();
    double genP_eta      = p.eta();
    double genP_phi      = p.phi();
    double genP_energy   = p.e();
    int genP_charge      = p.charge();
    double genP_vtxX     = p.vtxX()*10; // in mm
    double genP_vtxY     = p.vtxY()*10; // in mm
    double genP_vtxZ     = p.vtxZ()*10; // in mm
    // double genP_d0       = mcTools.GetD0Mag(genP_index, false); // in mm
    // double genP_Lxy      = mcTools.GetLxy(genP_index, false); // in mm
    // math::XYZTLorentzVector genP_p4;
    // genP_p4              = p.p4();    
    // TLorentzVector genP_p4Vis  = mcTools.GetVisibleP4(genP_index);
    
    // Daughter properties
    std::vector<int> genP_daughters_index    = mcTools.GetDaughters(genP_index, false);
    // std::vector<int> genP_daughters_pdgId    = mcTools.GetDaughters(genP_index, true);
    // std::vector<int> genP_allDaughters_index = mcTools.GetAllDaughters(genP_index, false);
    // std::vector<int> genP_allDaughters_pdgId = mcTools.GetAllDaughters(genP_index, true);  
    
    // Mom and Grand-mom properties    
    int genMom_index     = p.mother();
    int genMom_pdgId     = 0;
    int genGmom_index    = -1;
    if (genMom_index >= 0)
      {
	// Mom
	m = fEvent.genparticles().getGenParticles()[genMom_index];
	genMom_pdgId  = m.pdgId();

	// Grand-mom
	genGmom_index = m.mother();
	g = fEvent.genparticles().getGenParticles()[genGmom_index];
      } 

    // Print genParticle properties or  decay tree ?
    // mcTools.PrintGenParticle(genP_index);
    // mcTools.PrintDaughters(genP_index, false);
    // mcTools.PrintDaughters(genP_index, true);


    // Add table rows
    table.AddRowColumn(row, auxTools.ToString(entry)           );
    table.AddRowColumn(row, auxTools.ToString(genP_index)      );
    table.AddRowColumn(row, auxTools.ToString(genP_pdgId)      );
    table.AddRowColumn(row, auxTools.ToString(genP_status)     );
    table.AddRowColumn(row, auxTools.ToString(genP_charge)     );
    table.AddRowColumn(row, auxTools.ToString(genP_pt , 3)     );
    table.AddRowColumn(row, auxTools.ToString(genP_eta, 4)     );
    table.AddRowColumn(row, auxTools.ToString(genP_phi, 3)     );
    table.AddRowColumn(row, auxTools.ToString(genP_energy, 3)  );
    table.AddRowColumn(row, "(" + auxTools.ToString(genP_vtxX, 3) + ", " + auxTools.ToString(genP_vtxY, 3)  + ", " + auxTools.ToString(genP_vtxZ, 3) + ")" );
    // table.AddRowColumn(row, auxTools.ToString(genP_d0,  3)     );
    // table.AddRowColumn(row, auxTools.ToString(genP_Lxy, 3)     );
    table.AddRowColumn(row, auxTools.ToString(genMom_index)    );
    table.AddRowColumn(row, auxTools.ConvertIntVectorToString(genP_daughters_index) );
    row++;
	       
    
    // The following code was written based on these particles. Where needed their daughters are used
    // or if they decay to themselves their final versions are used
    // ========================================================================================================
    // Evt | Index | PdgId | Status | Pt   | Eta    | Phi     | Mom | Comments
    // ===================================================================================================
    // 0   | 4     | 37    | 22     | 378  | 0.8825 | 2.5     | 2   | H+
    // 0   | 5     | 5     | 23     | 34.4 | -1.935 | -3.08   | 2   | b flavour-excited
    // 0   | 6     | -6    | 22     | 321  | 1.783  | -0.72   | 2   | tbar associated
    // 0   | 7     | 2     | 23     | 96.9 | 1.624  | -0.128  | 2   | u spectator quark
    // 0   | 39    | 6     | 22     | 281  | 0.8383 | 2.27    | 34  | H->tb, t
    // 0   | 40    | -5    | 23     | 47.1 | 0.1406 | 2.3     | 34  | H->tb, bbar
    // 0   | 41    | -24   | 22     | 209  | 1.694  | -0.805  | 36  | g->tt, t->Wb, W-
    // 0   | 42    | -5    | 23     | 167  | 1.675  | -0.0675 | 36  | g->tt, t->Wb, bbar
    // 0   | 46    | 24    | 22     | 180  | 0.5437 | 1.98    | 39  | H->tb, t->Wb, W+
    // 0   | 47    | 5     | 23     | 120  | 1.105  | 2.71    | 39  | H->tb, t->Wb, b
    // 0   | 53    | 13    | 23     | 174  | 1.808  | -0.782  | 44  | g->tt, t->Wb, W->mu v_mu, m
    // 0   | 54    | -14   | 23     | 34.8 | 0.8297 | -0.913  | 44  | g->tt, t->Wb, W->mu v_mu, v_mu
    // 0   | 58    | -1    | 23     | 99   | 0.8182 | 2.26    | 49  | H->tb, t->Wb, W->qqbar, qbar
    // 0   | 59    | 2     | 23     | 72.7 | 0.1424 | 1.66    | 49  | H->tb, t->Wb, W->qqbar, q
    // ========================================================================================================
    
    // If particle decays to itself, get the last in the chain
    int fs_index   = mcTools.GetFinalSelf(genP_index);
    genParticle fs = fEvent.genparticles().getGenParticles()[fs_index];

    
    // B-quarks
    if(std::abs(genP_pdgId) == 5)
      {
	
	if ( mcTools.HasMother(genP_index, 37, true) ) // Has H+ mother
	  {
	    if (std::abs(genMom_pdgId) == 6) // Has top immediate mother
	      {
		// H+->tb, t->bW, b (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible! Also t->Zc and t->Zu)
		cHtb_tbW_BQuark.increment();
		Htb_tbW_BQuark_p4    = fs.p4();
		Htb_tbW_BQuark_index = fs_index;
	      }
	    else if (std::abs(genMom_pdgId) == 37) // Has top immediate mother
	      {
		// H+->tb, b
		cHtb_BQuark.increment();
		Htb_BQuark_p4    = fs.p4();
		Htb_BQuark_index = fs_index;
	      }
	    else
	      {
		// throw hplus::Exception("Logic") << "Kinematics::process() B-quark whose origins are not accounted for. Need to rethink this.";
	      }
	    
	  }// Has H+ mother
	else
	  {
	    
	    if ( (std::abs(genMom_pdgId) == 21) || (g.pdgId() == 2212) ) // Has glu immediate mother OR p grandmother
	      {
		// g->bb, b (flavour-excited )	       
		cgbb_BQuark.increment();
		gbb_BQuark_p4    = fs.p4();
		gbb_BQuark_index = fs_index;

	      }
	    else if (std::abs(genMom_pdgId) == 6) // Has top immediate mother
	      {
		// g->tt, t->bW, b (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
		cgtt_tbW_BQuark.increment();
		gtt_tbW_BQuark_p4    = fs.p4();
		gtt_tbW_BQuark_index = fs_index;

	      }
	    else if (mcTools.HasMother(genP_index, 4,  true) ) // Rare events (~1 in 1000)
	      {
		// g->bb, b (flavour-excited )
		cgbb_BQuark.increment();
		gbb_BQuark_p4    = fs.p4();
		gbb_BQuark_index = fs_index;
	      }
	    else
	      {	      
		// throw hplus::Exception("Logic") << "Kinematics::process() B-quark whose origins are not accounted for. Need to rethink this.";
	      }
	  }
	
      }// B-quarks
    else if(std::abs(genP_pdgId) == 6) // T-Quarks
      {
	
	if (std::abs(genMom_pdgId) == 37) // Has H+ mother
	  {
	    // H+->tb (From HPlus decay)
	    cHtb_TQuark.increment();
	    Htb_TQuark_p4    = fs.p4();
	    Htb_TQuark_index = fs_index;
      	  }
	else if ( (std::abs(genMom_pdgId) == 21) || (g.pdgId() == 2212) ) // Has glu immediate mother OR p grandmother
	  {	     
	    // g->tt (Associated top)
	    cgtt_TQuark.increment();
	    gtt_TQuark_p4    = fs.p4();
	    gtt_TQuark_index = fs_index; 
	  }
	else if (mcTools.HasMother(genP_index, 4,  true) ) // Rare events (~1 in 1000)
	  {
	    // g->tt (Associated top)
	    cgtt_TQuark.increment();
	    gtt_TQuark_p4    = fs.p4();
	    gtt_TQuark_index = fs_index;
	  }
	else
	  {
	    // throw hplus::Exception("Logic") << "Kinematics::process() Top quark whose origins are not accounted for. Need to rethink this.";
	  }
	
      }// T-Quarks
    else if(std::abs(genP_pdgId) == 37) //HPlus
      {

	// tb->H+, H+
	cHtb_HPlus.increment();

	Htb_HPlus_p4    = fs.p4();
	Htb_HPlus_index = fs_index;

      } // HPlus
    else if(std::abs(genP_pdgId) == 24) //W-bosons
      {
	
	if (mcTools.HasMother(genP_index, 37, true)) // Has H+ mother
	  {
	    // H+->tb, t->bW, W-boson (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
	    cHtb_tbW_WBoson.increment();
	    Htb_tbW_WBoson_p4    = fs.p4();
	    Htb_tbW_WBoson_index = fs_index;

	    // H+->tb, t->bW, W->qq (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
	    std::vector<int> daughters = mcTools.GetDaughters(fs_index, false);
	    
	    // For-loop: All daughters
	    for (unsigned short i = 0; i < daughters.size(); i++){

	      int dau_index = daughters.at(i);
	      genParticle d = fEvent.genparticles().getGenParticles()[dau_index];

	      if( mcTools.IsQuark(d.pdgId()) )
		{	
		  if (d.pdgId() > 0)
		    {
		      // Quarks
		      cHtb_tbW_Wqq_Quark.increment();
		      Htb_tbW_Wqq_Quark_p4    = d.p4();
		      Htb_tbW_Wqq_Quark_index = dau_index;
		    }
		  else
		    {
		      // Anti-Quarks
		      cHtb_tbW_Wqq_AntiQuark.increment();
		      Htb_tbW_Wqq_AntiQuark_p4    = d.p4();
		      Htb_tbW_Wqq_AntiQuark_index = dau_index;
		    }
		}
	      else if( mcTools.IsLepton(d.pdgId() ) )
		{
		  // H+->tb, t->bW, W->l v (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
		  cHtb_tbW_Wqq_Leptons.increment();
		  bWToLNu = true;
		  break;
		}
	      else
		{
		  throw hplus::Exception("Logic") << "Kinematics::process() W daughters whose origins are not accounted for. Need to rethink this.";
		}
	    } // For-loop: All daughters
	  } // Has H+ mother
	else
	  {
	    // g->tt, t->bW, W-boson (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
	    cgtt_tbW_WBoson.increment();
	    gtt_tbW_WBoson_p4    = fs.p4();
	    gtt_tbW_WBoson_index = fs_index;


	    // g->tt, t->bWH, t->bW, W->qq (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
	    std::vector<int> daughters = mcTools.GetDaughters(fs_index, false);

	    // For-loop: All daughters
	    for (unsigned short i = 0; i < daughters.size(); i++){
	      
	      int dau_index = daughters.at(i);
	      genParticle d = fEvent.genparticles().getGenParticles()[dau_index];
	      
	      if( mcTools.IsQuark(d.pdgId() ) )
	      {
		if (d.pdgId() > 0)
		  {
		    // Quarks
		    cgtt_tbW_Wqq_Quark.increment();
		    gtt_tbW_Wqq_Quark_p4    = d.p4();
		    gtt_tbW_Wqq_Quark_index = dau_index;
		  }	       
		else
		  {
		    // AntiQuarks
		    cgtt_tbW_Wqq_AntiQuark.increment();
		    gtt_tbW_Wqq_AntiQuark_p4    = d.p4();
		    gtt_tbW_Wqq_AntiQuark_index = dau_index;
		  }
	      }
	      else if( mcTools.IsLepton(d.pdgId() ) )
		{
		  // g->tt, t->bWH, t->bW, W->l v (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
		  cgtt_tbW_Wqq_Leptons.increment();
		  bWToLNu = true;
		  break;
		}
	      else
		{
		  throw hplus::Exception("Logic") << "Kinematics::process() W daughters whose origins are not accounted for. Need to rethink this.";
		}
	    }// For-loop: All daughters
	  }
	
      }//W-Bosons
    else
      {
	// throw hplus::Exception("Logic") << "Kinematics::process()";
      }    

    // Veto events with leptons from t-bW, W->l v decays
    if (bWToLNu) return;
    
  }//for-loop: genParticles


  // Booleans that characterise the event
  bool Htb_BQuark_central            = std::abs(Htb_BQuark_p4.eta()) < 2.5;
  bool Htb_tbW_BQuark_central        = std::abs(Htb_tbW_BQuark_p4.eta()) < 2.5;
  bool Htb_tbW_Wqq_Quark_central     = std::abs(Htb_tbW_Wqq_Quark_p4.eta()) < 2.5;
  bool Htb_tbW_Wqq_AntiQuark_central = std::abs(Htb_tbW_Wqq_AntiQuark_p4.eta()) < 2.5;
  bool bAL3CJetsFromHPlus            = (Htb_BQuark_central + Htb_tbW_BQuark_central + Htb_tbW_Wqq_Quark_central + Htb_tbW_Wqq_AntiQuark_central) >= 3;


  // Declare genJet related variables
  std::vector<math::XYZTLorentzVector> v_selJets_p4;
  int nSelJets   = 0;
  double genJ_HT = 0.0;

  // For-loop: GenJets
  for(GenJet j: fEvent.genjets()) {

    math::XYZTLorentzVector genJ_p4;
    genJ_p4 = j.p4();
    double genJ_pt     = j.pt();
    double genJ_eta    = j.eta();
    // double genJ_rap    = mcTools.GetRapidity(genJ_p4);
    // double genJ_pdgId  = j.pdgId();

    // Apply jet acceptance cuts
    if ( (genJ_pt < 30) || (std::abs(genJ_eta) > 2.5) ) continue;

    // Count the selected jets
    nSelJets++;

    // Save the the p4
    v_selJets_p4.push_back( genJ_p4 );
    
    // Calculate HT
    genJ_HT += genJ_pt;
    
  }

  
  // Event-based variables
  double genP_HT = Htb_BQuark_p4.pt() + Htb_tbW_BQuark_p4.pt() + Htb_tbW_Wqq_Quark_p4.pt() + Htb_tbW_Wqq_AntiQuark_p4.pt() + gbb_BQuark_p4.pt()
    + gtt_tbW_Wqq_Quark_p4.pt() + gtt_tbW_Wqq_AntiQuark_p4.pt() + gtt_tbW_BQuark_p4.pt();

  std::vector<math::XYZTLorentzVector> v_dijet_p4;
  std::vector<double> v_dijet_masses;
  std::vector<double> v_dijet_dR;
  std::vector<double> v_dijet_dRrap;
  std::vector<double> v_dijet_dEta;
  std::vector<double> v_dijet_dPhi;
  std::vector<double> v_dijet_dRap;
  
  double maxDijetMass_mass;
  math::XYZTLorentzVector maxDijetMass_p4;
  int maxDijetMass_pos;
  double maxDijetMass_dR;
  double maxDijetMass_dRrap;
  double maxDijetMass_dEta;
  double maxDijetMass_dPhi;
  double maxDijetMass_dRap;
  double maxDijetMass_rapidity;
  
  int iJet = 0;
  if (v_selJets_p4.size() > 1) {
    // For-loop: All selected jets 
    for (int i=0; i < v_selJets_p4.size(); i++)
      {
	iJet++;
	double genJ_Pt  = v_selJets_p4.at(i).pt();
	double genJ_Eta = v_selJets_p4.at(i).eta();
	double genJ_Rap = mcTools.GetRapidity(v_selJets_p4.at(i));
	
	if (iJet==1)
	  {
	    h_GenJet1_Pt -> Fill( genJ_Pt  );
	    h_GenJet1_Eta-> Fill( genJ_Eta );
	    h_GenJet1_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet1_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet1_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet1_Rap->Fill(genJ_Rap);
	      }
	  }
	else if (iJet==2)
	  {
	    h_GenJet2_Pt -> Fill( genJ_Pt  );
	    h_GenJet2_Eta-> Fill( genJ_Eta );
	    h_GenJet2_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet2_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet2_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet2_Rap->Fill(genJ_Rap);
	      }
	  }
	else if (iJet==3)
	  {
	    h_GenJet3_Pt -> Fill( genJ_Pt  );
	    h_GenJet3_Eta-> Fill( genJ_Eta );
	    h_GenJet3_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet3_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet3_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet3_Rap->Fill(genJ_Rap);
	      }
	  }
	else if (iJet==4)
	  {
	    h_GenJet4_Pt -> Fill( genJ_Pt  );
	    h_GenJet4_Eta-> Fill( genJ_Eta );
	    h_GenJet4_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet4_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet4_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet4_Rap->Fill(genJ_Rap);
	      }
	  }
	else if (iJet==5)
	  {
	    h_GenJet5_Pt -> Fill( genJ_Pt  );
	    h_GenJet5_Eta-> Fill( genJ_Eta );
	    h_GenJet5_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet5_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet5_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet5_Rap->Fill(genJ_Rap);
	      }
	  }
	else if (iJet==6)
	  {
	    h_GenJet6_Pt -> Fill( genJ_Pt  );
	    h_GenJet6_Eta-> Fill( genJ_Eta );
	    h_GenJet6_Rap-> Fill( genJ_Rap );
	    if (bAL3CJetsFromHPlus)
	      {
		h_AL3CJetsFromHPlus_GenJet6_Pt ->Fill(genJ_Pt);
		h_AL3CJetsFromHPlus_GenJet6_Eta->Fill(genJ_Eta);
		h_AL3CJetsFromHPlus_GenJet6_Rap->Fill(genJ_Rap);
	      }
	  }
	else{}
	
	// For-loop: All selected jets (nested)
	for (int j=i+1; j < v_selJets_p4.size(); j++)
	  {
	    math::XYZTLorentzVector p4_i = v_selJets_p4.at(i);
	    math::XYZTLorentzVector p4_j = v_selJets_p4.at(j);
	    math::XYZTLorentzVector p4   = p4_i + p4_j;
	    double rap_i = mcTools.GetRapidity(p4_i);
	    double rap_j = mcTools.GetRapidity(p4_j);
	    double dR    = ROOT::Math::VectorUtil::DeltaR(p4_i, p4_j);
	    double dRap  = std::fabs(rap_i - rap_j);
	    double dEta  = std::fabs(p4_i.eta() - p4_j.eta());
	    double dPhi  = std::fabs(ROOT::Math::VectorUtil::DeltaPhi(p4_i, p4_j));
	    
	    v_dijet_p4.push_back( p4 );
	    v_dijet_masses.push_back( p4.mass() );
	    v_dijet_dR.push_back( dR );
	    v_dijet_dRrap.push_back( sqrt( pow(dRap, 2) + pow(dPhi, 2) ) ); 
	    v_dijet_dEta.push_back( dEta ); 
	    v_dijet_dRap.push_back( dRap );
	    v_dijet_dPhi.push_back( dPhi );

	  }
      }

    // MaxDiJet: DiJet combination with largest mass
    maxDijetMass_pos      = std::max_element(v_dijet_masses.begin(), v_dijet_masses.end()) - v_dijet_masses.begin();
    maxDijetMass_mass     = v_dijet_masses.at(maxDijetMass_pos);
    maxDijetMass_p4       = v_dijet_p4.at(maxDijetMass_pos);
    maxDijetMass_dR       = v_dijet_dR.at(maxDijetMass_pos);
    maxDijetMass_dRrap    = v_dijet_dRrap.at(maxDijetMass_pos);
    maxDijetMass_dEta     = v_dijet_dEta.at(maxDijetMass_pos);
    maxDijetMass_dPhi     = v_dijet_dPhi.at(maxDijetMass_pos);
    maxDijetMass_dRap     = v_dijet_dRap.at(maxDijetMass_pos);
    maxDijetMass_rapidity = mcTools.GetRapidity(maxDijetMass_p4);

  }// if (v_selJets_p4.size() > 1) {

  if (v_selJets_p4.size() > 3) {
    double jet1_Eta = v_selJets_p4.at(0).eta();
    double jet2_Eta = v_selJets_p4.at(1).eta();
    double jet3_Eta = v_selJets_p4.at(2).eta();
    double jet4_Eta = v_selJets_p4.at(3).eta();

    double jet1_Phi = v_selJets_p4.at(0).phi();
    double jet2_Phi = v_selJets_p4.at(1).phi();
    double jet3_Phi = v_selJets_p4.at(2).phi();
    double jet4_Phi = v_selJets_p4.at(3).phi();

    
    h_Jet1Jet2_dEta_Vs_Jet3Jet4_dEta ->Fill(std::fabs(jet1_Eta - jet2_Eta), std::fabs(jet3_Eta - jet4_Eta));
    h_Jet1Jet2_dPhi_Vs_Jet3Jet4_dPhi ->Fill(std::fabs(jet1_Phi - jet2_Phi), std::fabs(jet3_Phi - jet4_Phi));
    h_Jet1Jet2_dEta_Vs_Jet1Jet2_Mass ->Fill(std::fabs(jet1_Eta - jet2_Eta), (v_selJets_p4.at(0) + v_selJets_p4.at(1)).mass() );
    h_Jet3Jet4_dEta_Vs_Jet3Jet4_Mass ->Fill(std::fabs(jet3_Eta - jet4_Eta), (v_selJets_p4.at(2) + v_selJets_p4.at(3)).mass() );
  }
  
  // Event-based histograms
  h_genMET_Et  ->Fill(fEvent.genMET().et()); 
  h_genMET_Phi ->Fill(fEvent.genMET().Phi());

  // Trijet systems
  math::XYZTLorentzVector Htb_tbW_bqq_p4 = Htb_BQuark_p4 + Htb_tbW_Wqq_Quark_p4 + Htb_tbW_Wqq_AntiQuark_p4;
  math::XYZTLorentzVector gtt_tbW_bqq_p4 = gtt_tbW_Wqq_Quark_p4 + gtt_tbW_Wqq_AntiQuark_p4 + gtt_tbW_BQuark_p4;
  h_Htb_tbW_bqq_Pt   ->Fill(Htb_tbW_bqq_p4.pt());
  h_Htb_tbW_bqq_Rap  ->Fill( mcTools.GetRapidity(Htb_tbW_bqq_p4) );
  h_Htb_tbW_bqq_Mass ->Fill( Htb_tbW_bqq_p4.mass() );
  
  h_gtt_tbW_bqq_Pt   ->Fill(gtt_tbW_bqq_p4.pt() );
  h_gtt_tbW_bqq_Rap  ->Fill( mcTools.GetRapidity(gtt_tbW_bqq_p4) );
  h_gtt_tbW_bqq_Mass ->Fill(gtt_tbW_bqq_p4.mass() );
  
  // Selected GenJets
  h_SelGenJet_Multiplicity      ->Fill(nSelJets);  

  // MaxDiJet
  h_MaxDiJetMass_Mass ->Fill( maxDijetMass_mass     );
  h_MaxDiJetMass_Pt   ->Fill( maxDijetMass_p4.pt()  );
  h_MaxDiJetMass_Eta  ->Fill( maxDijetMass_p4.eta() );
  h_MaxDiJetMass_Rap  ->Fill( maxDijetMass_rapidity );
  h_MaxDiJetMass_dR   ->Fill( maxDijetMass_dR       );
  h_MaxDiJetMass_dRrap->Fill( maxDijetMass_dRrap    );
  h_MaxDiJetMass_dEta ->Fill( maxDijetMass_dEta     );
  h_MaxDiJetMass_dPhi ->Fill( maxDijetMass_dPhi     );
  h_MaxDiJetMass_dRap ->Fill( maxDijetMass_dRap     );
  h_MaxDiJetMass_dEta_Vs_dPhi->Fill( maxDijetMass_dEta, maxDijetMass_dPhi );
  h_MaxDiJetMass_dRap_Vs_dPhi->Fill( maxDijetMass_dRap, maxDijetMass_dPhi );
  
  // Calculate HT
  h_genHT_GenParticles->Fill(genP_HT);
  h_genHT_GenJets->Fill(genJ_HT);
  
  
  // Print the table with genP info
  if (cfg_Verbose) table.Print();
  
  // H+->tb, t->bW, b (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible! Also t->Zc and t->Zu)
  h_tbH_tbW_BQuark_Pt ->Fill( Htb_tbW_BQuark_p4.pt()  );
  h_tbH_tbW_BQuark_Eta->Fill( Htb_tbW_BQuark_p4.eta() );
  h_tbH_tbW_BQuark_Rap->Fill( mcTools.GetRapidity(Htb_tbW_BQuark_p4) );
  h_tbH_tbW_BQuark_Phi->Fill( Htb_tbW_BQuark_p4.phi() );

  // H+->tb, b
  h_tbH_BQuark_Pt ->Fill( Htb_BQuark_p4.pt()  );
  h_tbH_BQuark_Eta->Fill( Htb_BQuark_p4.eta() );
  h_tbH_BQuark_Rap->Fill( mcTools.GetRapidity(Htb_BQuark_p4 ) );
  h_tbH_BQuark_Phi->Fill( Htb_BQuark_p4.phi() );

  // g->bb, b (flavour-excited )	       
  h_gbb_BQuark_Pt ->Fill( gbb_BQuark_p4.pt()  );
  h_gbb_BQuark_Eta->Fill( gbb_BQuark_p4.eta() );
  h_gbb_BQuark_Rap->Fill( mcTools.GetRapidity(gbb_BQuark_p4) );
  h_gbb_BQuark_Phi->Fill( gbb_BQuark_p4.phi() );

  // g->tt, t->bW, b (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
  h_gtt_tbW_BQuark_Pt ->Fill( gtt_tbW_BQuark_p4.pt()  ); 
  h_gtt_tbW_BQuark_Eta->Fill( gtt_tbW_BQuark_p4.eta() );
  h_gtt_tbW_BQuark_Rap->Fill( mcTools.GetRapidity(gtt_tbW_BQuark_p4) );
  h_gtt_tbW_BQuark_Phi->Fill( gtt_tbW_BQuark_p4.phi() );
    
  // H+->tb (From HPlus decay)
  h_tbH_TQuark_Pt ->Fill( Htb_TQuark_p4.pt()) ;
  h_tbH_TQuark_Eta->Fill( Htb_TQuark_p4.eta() );
  h_tbH_TQuark_Rap->Fill( mcTools.GetRapidity(Htb_TQuark_p4) );
  h_tbH_TQuark_Phi->Fill( Htb_TQuark_p4.phi() );

  // g->tt (Associated top)
  h_gtt_TQuark_Pt ->Fill( gtt_TQuark_p4.pt()  );
  h_gtt_TQuark_Eta->Fill( gtt_TQuark_p4.eta() );
  h_gtt_TQuark_Rap->Fill( mcTools.GetRapidity(gtt_TQuark_p4) );
  h_gtt_TQuark_Phi->Fill( gtt_TQuark_p4.phi() );
  
  // tb->H+, H+
  h_tbH_HPlus_Pt ->Fill( Htb_HPlus_p4.pt()  );
  h_tbH_HPlus_Eta->Fill( Htb_HPlus_p4.eta() );
  h_tbH_HPlus_Rap->Fill( mcTools.GetRapidity(Htb_HPlus_p4) );
  h_tbH_HPlus_Phi->Fill( Htb_HPlus_p4.phi() );
  
  // H+->tb, t->bW, W-boson (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
  h_tbH_tbW_WBoson_Pt ->Fill( Htb_tbW_WBoson_p4.pt()  );
  h_tbH_tbW_WBoson_Eta->Fill( Htb_tbW_WBoson_p4.eta() );
  h_tbH_tbW_WBoson_Rap->Fill( mcTools.GetRapidity(Htb_tbW_WBoson_p4) );
  h_tbH_tbW_WBoson_Phi->Fill( Htb_tbW_WBoson_p4.phi() );

  // H+->tb, t->bW, W-boson, Quark
  h_Htb_tbW_Wqq_Quark_Pt ->Fill( Htb_tbW_Wqq_Quark_p4.pt()  );
  h_Htb_tbW_Wqq_Quark_Eta->Fill( Htb_tbW_Wqq_Quark_p4.eta() );
  h_Htb_tbW_Wqq_Quark_Rap->Fill( mcTools.GetRapidity(Htb_tbW_Wqq_Quark_p4) );
  h_Htb_tbW_Wqq_Quark_Phi->Fill( Htb_tbW_Wqq_Quark_p4.phi() );

  // H+->tb, t->bW, W-boson, AntiQuark
  h_Htb_tbW_Wqq_AntiQuark_Pt ->Fill( Htb_tbW_Wqq_AntiQuark_p4.pt()  );
  h_Htb_tbW_Wqq_AntiQuark_Eta->Fill( Htb_tbW_Wqq_AntiQuark_p4.eta() );
  h_Htb_tbW_Wqq_AntiQuark_Rap->Fill( mcTools.GetRapidity(Htb_tbW_Wqq_AntiQuark_p4) );
  h_Htb_tbW_Wqq_AntiQuark_Phi->Fill( Htb_tbW_Wqq_AntiQuark_p4.phi() );

  // g->tt, t->bW, W-boson (NOTE: t->Wb dominant, but t->Ws and t->Wd also possible!)
  h_gtt_tbW_WBoson_Pt ->Fill( gtt_tbW_WBoson_p4.pt()  );
  h_gtt_tbW_WBoson_Eta->Fill( gtt_tbW_WBoson_p4.eta() );
  h_gtt_tbW_WBoson_Rap->Fill( mcTools.GetRapidity(gtt_tbW_WBoson_p4) );
  h_gtt_tbW_WBoson_Phi->Fill( gtt_tbW_WBoson_p4.phi() );

  // g->tt, t->bW, W->qq, Quark
  h_gtt_tbW_Wqq_Quark_Pt ->Fill( gtt_tbW_Wqq_Quark_p4.pt()  );
  h_gtt_tbW_Wqq_Quark_Eta->Fill( gtt_tbW_Wqq_Quark_p4.eta() );
  h_gtt_tbW_Wqq_Quark_Rap->Fill( mcTools.GetRapidity(gtt_tbW_Wqq_Quark_p4) );
  h_gtt_tbW_Wqq_Quark_Phi->Fill( gtt_tbW_Wqq_Quark_p4.phi() );

  // g->tt, t->bW, W->qq, AntiQuark
  h_gtt_tbW_Wqq_AntiQuark_Pt ->Fill( gtt_tbW_Wqq_AntiQuark_p4.pt()  );
  h_gtt_tbW_Wqq_AntiQuark_Eta->Fill( gtt_tbW_Wqq_AntiQuark_p4.eta() );
  h_gtt_tbW_Wqq_AntiQuark_Rap->Fill( mcTools.GetRapidity(gtt_tbW_Wqq_AntiQuark_p4) );
  h_gtt_tbW_Wqq_AntiQuark_Phi->Fill( gtt_tbW_Wqq_AntiQuark_p4.phi() );

 
  // H+->tb, t->bW, W->qq
  double dR_Htb_TQuark_Htb_BQuark                = ROOT::Math::VectorUtil::DeltaR( Htb_TQuark_p4, Htb_BQuark_p4           );
  double dR_Htb_TQuark_gtt_TQuark                = ROOT::Math::VectorUtil::DeltaR( Htb_TQuark_p4, gtt_TQuark_p4           );
  double dR_Htb_TQuark_gbb_BQuark                = ROOT::Math::VectorUtil::DeltaR( Htb_TQuark_p4, gbb_BQuark_p4           );
  double dR_Htb_BQuark_Htb_tbW_BQuark            = ROOT::Math::VectorUtil::DeltaR( Htb_BQuark_p4, Htb_tbW_BQuark_p4       );
  double dR_Htb_BQuark_Htb_tbW_Wqq_Quark         = ROOT::Math::VectorUtil::DeltaR( Htb_BQuark_p4, Htb_tbW_Wqq_Quark_p4    );
  double dR_Htb_BQuark_Htb_tbW_Wqq_AntiQuark     = ROOT::Math::VectorUtil::DeltaR( Htb_BQuark_p4, Htb_tbW_Wqq_AntiQuark_p4);
  double dR_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark     = ROOT::Math::VectorUtil::DeltaR( Htb_tbW_BQuark_p4, Htb_tbW_Wqq_Quark_p4);
  double dR_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark = ROOT::Math::VectorUtil::DeltaR( Htb_tbW_BQuark_p4, Htb_tbW_Wqq_AntiQuark_p4);

  double dEta_Htb_TQuark_Htb_BQuark                = std::fabs( Htb_TQuark_p4.eta() - Htb_BQuark_p4.eta()            );
  double dEta_Htb_TQuark_gtt_TQuark                = std::fabs( Htb_TQuark_p4.eta() - gtt_TQuark_p4.eta()            );
  double dEta_Htb_TQuark_gbb_BQuark                = std::fabs( Htb_TQuark_p4.eta() - gbb_BQuark_p4.eta()            );
  double dEta_Htb_BQuark_Htb_tbW_BQuark            = std::fabs( Htb_BQuark_p4.eta() - Htb_tbW_BQuark_p4.eta()        );
  double dEta_Htb_BQuark_Htb_tbW_Wqq_Quark         = std::fabs( Htb_BQuark_p4.eta() - Htb_tbW_Wqq_Quark_p4.eta()     );
  double dEta_Htb_BQuark_Htb_tbW_Wqq_AntiQuark     = std::fabs( Htb_BQuark_p4.eta() - Htb_tbW_Wqq_AntiQuark_p4.eta() );
  double dEta_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark     = std::fabs( Htb_tbW_BQuark_p4.eta() - Htb_tbW_Wqq_Quark_p4.eta() );
  double dEta_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark = std::fabs( Htb_tbW_BQuark_p4.eta() - Htb_tbW_Wqq_AntiQuark_p4.eta() );

  double dPhi_Htb_TQuark_Htb_BQuark                = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_TQuark_p4, Htb_BQuark_p4            ));
  double dPhi_Htb_TQuark_gtt_TQuark                = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_TQuark_p4, gtt_TQuark_p4            ));
  double dPhi_Htb_TQuark_gbb_BQuark                = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_TQuark_p4, gbb_BQuark_p4            ));
  double dPhi_Htb_BQuark_Htb_tbW_BQuark            = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_BQuark_p4, Htb_tbW_BQuark_p4        ));
  double dPhi_Htb_BQuark_Htb_tbW_Wqq_Quark         = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_BQuark_p4, Htb_tbW_Wqq_Quark_p4     ));
  double dPhi_Htb_BQuark_Htb_tbW_Wqq_AntiQuark     = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_BQuark_p4, Htb_tbW_Wqq_AntiQuark_p4 ));
  double dPhi_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark     = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_tbW_BQuark_p4, Htb_tbW_Wqq_Quark_p4 ));
  double dPhi_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( Htb_tbW_BQuark_p4, Htb_tbW_Wqq_AntiQuark_p4));

  double dRap_Htb_TQuark_Htb_BQuark                = std::fabs( mcTools.GetRapidity(Htb_TQuark_p4) - mcTools.GetRapidity(Htb_BQuark_p4)            );
  double dRap_Htb_TQuark_gtt_TQuark                = std::fabs( mcTools.GetRapidity(Htb_TQuark_p4) - mcTools.GetRapidity(gtt_TQuark_p4)            );
  double dRap_Htb_TQuark_gbb_BQuark                = std::fabs( mcTools.GetRapidity(Htb_TQuark_p4) - mcTools.GetRapidity(gbb_BQuark_p4)            );
  double dRap_Htb_BQuark_Htb_tbW_BQuark            = std::fabs( mcTools.GetRapidity(Htb_BQuark_p4) - mcTools.GetRapidity(Htb_tbW_BQuark_p4)        );
  double dRap_Htb_BQuark_Htb_tbW_Wqq_Quark         = std::fabs( mcTools.GetRapidity(Htb_BQuark_p4) - mcTools.GetRapidity(Htb_tbW_Wqq_Quark_p4)     );
  double dRap_Htb_BQuark_Htb_tbW_Wqq_AntiQuark     = std::fabs( mcTools.GetRapidity(Htb_BQuark_p4) - mcTools.GetRapidity(Htb_tbW_Wqq_AntiQuark_p4) );
  double dRap_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark     = std::fabs( mcTools.GetRapidity(Htb_tbW_BQuark_p4) - mcTools.GetRapidity(Htb_tbW_Wqq_Quark_p4 ));
  double dRap_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark = std::fabs( mcTools.GetRapidity(Htb_tbW_BQuark_p4) - mcTools.GetRapidity(Htb_tbW_Wqq_AntiQuark_p4));
  
  // Associated products
  double dR_gtt_TQuark_gbb_BQuark                = ROOT::Math::VectorUtil::DeltaR(gtt_TQuark_p4    , gbb_BQuark_p4            );
  double dR_gtt_TQuark_gtt_tbW_BQuark            = ROOT::Math::VectorUtil::DeltaR(gtt_TQuark_p4    , gtt_tbW_BQuark_p4        ); 
  double dR_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark     = ROOT::Math::VectorUtil::DeltaR(gtt_tbW_BQuark_p4, gtt_tbW_Wqq_Quark_p4     );
  double dR_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark = ROOT::Math::VectorUtil::DeltaR(gtt_tbW_BQuark_p4, gtt_tbW_Wqq_AntiQuark_p4 );

  double dEta_gtt_TQuark_gbb_BQuark                = std::fabs( gtt_TQuark_p4.eta()     - gbb_BQuark_p4.eta()            );
  double dEta_gtt_TQuark_gtt_tbW_BQuark            = std::fabs( gtt_TQuark_p4.eta()     - gtt_tbW_BQuark_p4.eta()        ); 
  double dEta_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark     = std::fabs( gtt_tbW_BQuark_p4.eta() - gtt_tbW_Wqq_Quark_p4.eta()     );
  double dEta_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark = std::fabs( gtt_tbW_BQuark_p4.eta() - gtt_tbW_Wqq_AntiQuark_p4.eta() );
  
  double dPhi_gtt_TQuark_gbb_BQuark                = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( gtt_TQuark_p4    , gbb_BQuark_p4            ));
  double dPhi_gtt_TQuark_gtt_tbW_BQuark            = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( gtt_TQuark_p4    , gtt_tbW_BQuark_p4        )); 
  double dPhi_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark     = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( gtt_tbW_BQuark_p4, gtt_tbW_Wqq_Quark_p4     ));
  double dPhi_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark = std::fabs(ROOT::Math::VectorUtil::DeltaPhi( gtt_tbW_BQuark_p4, gtt_tbW_Wqq_AntiQuark_p4 ));

  double dRap_gtt_TQuark_gbb_BQuark                = std::fabs( mcTools.GetRapidity(gtt_TQuark_p4)     - mcTools.GetRapidity(gbb_BQuark_p4)            );
  double dRap_gtt_TQuark_gtt_tbW_BQuark            = std::fabs( mcTools.GetRapidity(gtt_TQuark_p4)     - mcTools.GetRapidity(gtt_tbW_BQuark_p4)        ); 
  double dRap_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark     = std::fabs( mcTools.GetRapidity(gtt_tbW_BQuark_p4) - mcTools.GetRapidity(gtt_tbW_Wqq_Quark_p4)     );
  double dRap_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark = std::fabs( mcTools.GetRapidity(gtt_tbW_BQuark_p4) - mcTools.GetRapidity(gtt_tbW_Wqq_AntiQuark_p4) );

  // Fill dR histos
  h_Htb_TQuark_Htb_BQuark_dR                ->Fill(dR_Htb_TQuark_Htb_BQuark);
  h_Htb_TQuark_gtt_TQuark_dR                ->Fill(dR_Htb_TQuark_gtt_TQuark);
  h_Htb_TQuark_gbb_BQuark_dR                ->Fill(dR_Htb_TQuark_gbb_BQuark);
  h_Htb_BQuark_Htb_tbW_BQuark_dR            ->Fill(dR_Htb_BQuark_Htb_tbW_BQuark);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dR         ->Fill(dR_Htb_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dR     ->Fill(dR_Htb_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dR     ->Fill(dR_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dR ->Fill(dR_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_gtt_TQuark_gbb_BQuark_dR                ->Fill(dR_gtt_TQuark_gbb_BQuark);
  h_gtt_TQuark_gtt_tbW_BQuark_dR            ->Fill(dR_gtt_TQuark_gtt_tbW_BQuark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dR     ->Fill(dR_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dR ->Fill(dR_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark);

  h_Htb_TQuark_Htb_BQuark_dEta                ->Fill(dEta_Htb_TQuark_Htb_BQuark);
  h_Htb_TQuark_gtt_TQuark_dEta                ->Fill(dEta_Htb_TQuark_gtt_TQuark);
  h_Htb_TQuark_gbb_BQuark_dEta                ->Fill(dEta_Htb_TQuark_gbb_BQuark);
  h_Htb_BQuark_Htb_tbW_BQuark_dEta            ->Fill(dEta_Htb_BQuark_Htb_tbW_BQuark);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dEta         ->Fill(dEta_Htb_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dEta     ->Fill(dEta_Htb_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dEta     ->Fill(dEta_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dEta ->Fill(dEta_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_gtt_TQuark_gbb_BQuark_dEta                ->Fill(dEta_gtt_TQuark_gbb_BQuark);
  h_gtt_TQuark_gtt_tbW_BQuark_dEta            ->Fill(dEta_gtt_TQuark_gtt_tbW_BQuark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dEta     ->Fill(dEta_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dEta ->Fill(dEta_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark);

  h_Htb_TQuark_Htb_BQuark_dPhi                ->Fill(dPhi_Htb_TQuark_Htb_BQuark);
  h_Htb_TQuark_gtt_TQuark_dPhi                ->Fill(dPhi_Htb_TQuark_gtt_TQuark);
  h_Htb_TQuark_gbb_BQuark_dPhi                ->Fill(dPhi_Htb_TQuark_gbb_BQuark);
  h_Htb_BQuark_Htb_tbW_BQuark_dPhi            ->Fill(dPhi_Htb_BQuark_Htb_tbW_BQuark);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dPhi         ->Fill(dPhi_Htb_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi     ->Fill(dPhi_Htb_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dPhi     ->Fill(dPhi_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dPhi ->Fill(dPhi_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_gtt_TQuark_gbb_BQuark_dPhi                ->Fill(dPhi_gtt_TQuark_gbb_BQuark);
  h_gtt_TQuark_gtt_tbW_BQuark_dPhi            ->Fill(dPhi_gtt_TQuark_gtt_tbW_BQuark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dPhi     ->Fill(dPhi_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dPhi ->Fill(dPhi_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark);

  h_Htb_TQuark_Htb_BQuark_dRap                ->Fill(dRap_Htb_TQuark_Htb_BQuark);
  h_Htb_TQuark_gtt_TQuark_dRap                ->Fill(dRap_Htb_TQuark_gtt_TQuark);
  h_Htb_TQuark_gbb_BQuark_dRap                ->Fill(dRap_Htb_TQuark_gbb_BQuark);
  h_Htb_BQuark_Htb_tbW_BQuark_dRap            ->Fill(dRap_Htb_BQuark_Htb_tbW_BQuark);
  h_Htb_BQuark_Htb_tbW_Wqq_Quark_dRap         ->Fill(dRap_Htb_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_BQuark_Htb_tbW_Wqq_AntiQuark_dRap     ->Fill(dRap_Htb_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark_dRap     ->Fill(dRap_Htb_tbW_BQuark_Htb_tbW_Wqq_Quark);
  h_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark_dRap ->Fill(dRap_Htb_tbW_BQuark_Htb_tbW_Wqq_AntiQuark);
  h_gtt_TQuark_gbb_BQuark_dRap                ->Fill(dRap_gtt_TQuark_gbb_BQuark);
  h_gtt_TQuark_gtt_tbW_BQuark_dRap            ->Fill(dRap_gtt_TQuark_gtt_tbW_BQuark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark_dRap     ->Fill(dRap_gtt_tbW_BQuark_gtt_tbW_Wqq_Quark);
  h_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark_dRap ->Fill(dRap_gtt_tbW_BQuark_gtt_tbW_Wqq_AntiQuark);

  
  // Leading B-quarks
  std::vector<math::XYZTLorentzVector> bQuarks_p4;
  bQuarks_p4.push_back(Htb_BQuark_p4);
  bQuarks_p4.push_back(Htb_tbW_BQuark_p4);
  bQuarks_p4.push_back(gbb_BQuark_p4);
  bQuarks_p4.push_back(gtt_tbW_BQuark_p4);
  /// Sort bQuarks by pT 
  std::sort( bQuarks_p4.begin(), bQuarks_p4.end(), PtComparator() );

  // Require at least 4 b-quarks for these plots
  if (bQuarks_p4.size() < 4) return;

  double deltaRMin = 999999.9;
  int deltaRMin_i  = -1;
  int deltaRMin_j  = -1;
  
  // For-loop: All (pT-sorted) b-quarks
  for (int i = 0; i < bQuarks_p4.size(); i++)
    {

      double dEta_1_2 = std::fabs(bQuarks_p4.at(0).eta() - bQuarks_p4.at(1).eta());
      double dEta_1_3 = std::fabs(bQuarks_p4.at(0).eta() - bQuarks_p4.at(2).eta());
      double dEta_1_4 = std::fabs(bQuarks_p4.at(0).eta() - bQuarks_p4.at(3).eta());
      double dPhi_1_2 = std::fabs(bQuarks_p4.at(0).phi() - bQuarks_p4.at(1).phi());
      double dPhi_1_3 = std::fabs(bQuarks_p4.at(0).phi() - bQuarks_p4.at(2).phi());
      double dPhi_1_4 = std::fabs(bQuarks_p4.at(0).phi() - bQuarks_p4.at(3).phi());
      //
      double dEta_2_3 = std::fabs(bQuarks_p4.at(1).eta() - bQuarks_p4.at(2).eta());
      double dEta_2_4 = std::fabs(bQuarks_p4.at(1).eta() - bQuarks_p4.at(3).eta());
      double dPhi_2_3 = std::fabs(bQuarks_p4.at(1).phi() - bQuarks_p4.at(2).phi());
      double dPhi_2_4 = std::fabs(bQuarks_p4.at(1).phi() - bQuarks_p4.at(3).phi());
      //
      double dEta_3_4 = std::fabs(bQuarks_p4.at(2).eta() - bQuarks_p4.at(3).eta());
      double dPhi_3_4 = std::fabs(bQuarks_p4.at(2).phi() - bQuarks_p4.at(3).phi());
           
      // Fill 2D histos
      h_BQuark1_BQuark2_dEta_Vs_dPhi->Fill( dEta_1_2 , dPhi_1_2 );
      h_BQuark1_BQuark3_dEta_Vs_dPhi->Fill( dEta_1_3 , dPhi_1_3 );
      h_BQuark1_BQuark4_dEta_Vs_dPhi->Fill( dEta_1_4 , dPhi_1_4 );
      h_BQuark2_BQuark3_dEta_Vs_dPhi->Fill( dEta_2_3 , dPhi_2_3 );
      h_BQuark2_BQuark4_dEta_Vs_dPhi->Fill( dEta_2_4 , dPhi_2_4 );
      h_BQuark3_BQuark4_dEta_Vs_dPhi->Fill( dEta_3_4 , dPhi_3_4 );

      if (i==0)
	{
	  h_BQuark1_Pt ->Fill( bQuarks_p4.at(i).pt()  );
	  h_BQuark1_Eta->Fill( bQuarks_p4.at(i).eta() );
	  h_BQuark1_Rap->Fill( mcTools.GetRapidity(bQuarks_p4.at(i)) );
	  h_BQuark1_Phi->Fill( bQuarks_p4.at(i).phi() );
	}
      else if (i==1)
	{
	  h_BQuark2_Pt ->Fill( bQuarks_p4.at(i).pt()  );
	  h_BQuark2_Eta->Fill( bQuarks_p4.at(i).eta() );
	  h_BQuark2_Rap->Fill( mcTools.GetRapidity(bQuarks_p4.at(i)) );
	  h_BQuark2_Phi->Fill( bQuarks_p4.at(i).phi() );
	}
      else if (i==2)
	{
	  h_BQuark3_Pt ->Fill( bQuarks_p4.at(i).pt()  );
	  h_BQuark3_Eta->Fill( bQuarks_p4.at(i).eta() );
	  h_BQuark3_Rap->Fill( mcTools.GetRapidity(bQuarks_p4.at(i)) );
	  h_BQuark3_Phi->Fill( bQuarks_p4.at(i).phi() );
	}
      else if (i==3)
	{
	  h_BQuark4_Pt ->Fill( bQuarks_p4.at(i).pt()  );
	  h_BQuark4_Eta->Fill( bQuarks_p4.at(i).eta() );
	  h_BQuark4_Rap->Fill( mcTools.GetRapidity(bQuarks_p4.at(i)) );
	  h_BQuark4_Phi->Fill( bQuarks_p4.at(i).phi() );
	}
      else{}

      for (int j = i+1; j < bQuarks_p4.size(); j++)
	{
	  
	  double deltaR = ROOT::Math::VectorUtil::DeltaR(bQuarks_p4.at(i), bQuarks_p4.at(j));

	  if (deltaR < deltaRMin)
	    {
	      deltaRMin = deltaR;
	      deltaRMin_i = i;
	      deltaRMin_j = j;
	    }	  
	}      
    } // For-loop: All (pT-sorted) b-quarks

  // std::cout << "deltaRMin = " << deltaRMin << ", i = " << deltaRMin_i << ", j = " << deltaRMin_j <<  ", nbjets = " << bQuarks_p4.size() << std::endl;  
  math::XYZTLorentzVector bQuarkPair_dRMin_p4 = bQuarks_p4.at(deltaRMin_i) + bQuarks_p4.at(deltaRMin_j);
  h_BQuarkPair_dRMin_pT   ->Fill( bQuarkPair_dRMin_p4.pt() );
  h_BQuarkPair_dRMin_dEta ->Fill( std::fabs(bQuarks_p4.at(deltaRMin_i).eta() - bQuarks_p4.at(deltaRMin_j).eta()) );
  h_BQuarkPair_dRMin_dPhi ->Fill( std::fabs(ROOT::Math::VectorUtil::DeltaPhi(bQuarks_p4.at(deltaRMin_i), bQuarks_p4.at(deltaRMin_j))) );
  h_BQuarkPair_dRMin_dR   ->Fill( deltaRMin );
  h_BQuarkPair_dRMin_Mass ->Fill( bQuarkPair_dRMin_p4.mass() );
  
  return;
}