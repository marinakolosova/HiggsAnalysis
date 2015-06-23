// -*- c++ -*-
#include "EventSelection/interface/AngularCuts.h"

#include "Framework/interface/ParameterSet.h"
#include "EventSelection/interface/CommonPlots.h"
#include "DataFormat/interface/Event.h"
#include "Framework/interface/HistoWrapper.h"
#include "Framework/interface/Exception.h"

#include "Math/VectorUtil.h"

#include <sstream>
#include <cmath>

AngularCutsBase::Data::Data() 
: bPassedSelection(false) { }

AngularCutsBase::Data::~Data() { }

bool AngularCutsBase::Data::passedSelectionOnJet(size_t n) const {
  if (n > nMaxJets)
    throw hplus::Exception("assert") << "AngularCuts::Data: Requested passedSelectionOnJet on jet " << n << ", but maximum is " << nMaxJets;
  if (n > fPassedCutStatus.size())
    return false;
  return fPassedCutStatus[n];
}

double AngularCutsBase::Data::getDeltaPhiJetMET(size_t n) const {
  if (n > nMaxJets)
    throw hplus::Exception("assert") << "AngularCuts::Data: Requested DeltaPhi(Jet,MET) on jet " << n << ", but maximum is " << nMaxJets;
  if (n > fDeltaPhiJetMET.size())
    return -1.0;
  return fDeltaPhiJetMET[n];
}

double AngularCutsBase::Data::get1DCutVariable(size_t n) const {
  if (n > nMaxJets)
    throw hplus::Exception("assert") << "AngularCuts::Data: Requested get1DCutVariable on jet " << n << ", but maximum is " << nMaxJets;
  if (n > f1DCutVariables.size())
    return -1.0;
  return f1DCutVariables[n];
}

AngularCutsBase::AngularCutsBase(const ParameterSet& config, EventCounter& eventCounter, HistoWrapper& histoWrapper, CommonPlots* commonPlots, const std::string prefix, const AngularCutsBase::AngularCutsType type, const std::string& postfix)
: BaseSelection(eventCounter, histoWrapper, commonPlots, prefix+postfix),
  // Input parameters
  nConsideredJets(static_cast<size_t>(config.getParameter<int>("nConsideredJets"))),
  bEnableOptimizationPlots(config.getParameter<bool>("enableOptimizationPlots")),
  sPrefix(prefix),
  fType(type),
  cPassedAngularCuts(eventCounter.addCounter("passed angular cuts / "+prefix+" ("+postfix+")")),
  cSubAllEvents(eventCounter.addSubCounter("angular cuts / "+prefix+" ("+postfix+")", "All events"))
{
  // Check validity of parameters
  if (static_cast<size_t>(nConsideredJets) > nMaxJets)
    throw hplus::Exception("config") << "AngularCuts: Requested cuts on " << nConsideredJets << " jets, but maximum is " << nMaxJets;
  if (fType == kUndefined)
    throw hplus::Exception("assert") << "AngularCutsBase type has not been properly defined!";
  // Obtain cut points from config
  size_t maxIndex = std::min(nMaxJets, nConsideredJets);
  std::stringstream s;
  for (size_t i = 0; i < maxIndex; ++i) {
    s.str("");
    s << "cutValueJet" << i+1;
    fCutValue.push_back(static_cast<double>(config.getParameter<float>(s.str())));
  }
  // Subcounters
  for (size_t i = 0; i < nMaxJets; ++i) {
    s.str("");
    s << "Passed cut on jet " << i+1;
    cSubPassedCuts.push_back(eventCounter.addSubCounter("angular cuts / "+prefix+" ("+postfix+")", s.str()));
  }
}

AngularCutsBase::~AngularCutsBase() { }

void AngularCutsBase::bookHistograms(TDirectory* dir) {
  TDirectory* subdir = fHistoWrapper.mkdir(HistoLevel::kDebug, dir, "AngularCuts_"+sPrefix+"_"+sPostfix);
  if (bEnableOptimizationPlots) {
    std::stringstream sName;
    std::stringstream sLabel;
    for (size_t i = 0; i < nMaxJets; ++i) {
      sName.str("");
      sLabel.str("");
      sName << "AngularCuts_" << sPrefix << "_jet" << i+1;
      sLabel << "AngularCuts_" << sPrefix << "_jet" << i+1 << ";#Delta#phi(#tau,MET), ^{o};#Delta#phi(jet_{" << i+1 << "},MET), ^{o}";
      hOptimizationPlots.push_back(fHistoWrapper.makeTH<TH2F>(HistoLevel::kDebug, subdir, sName.str().c_str(), sLabel.str().c_str(),
                                                             18,0.,180.,18,0.,180.));
    }
  }
}

AngularCutsBase::Data AngularCutsBase::silentAnalyze(const Event& event, const TauSelection::Data& tauData, const JetSelection::Data& jetData, const METSelection::Data& metData) {
  ensureSilentAnalyzeAllowed(event.eventID());
  // Disable histogram filling and counter
  disableHistogramsAndCounters();
  Data myData = privateAnalyze(tauData, jetData, metData);
  enableHistogramsAndCounters();
  return myData;
}

AngularCutsBase::Data AngularCutsBase::analyze(const Event& event, const TauSelection::Data& tauData, const JetSelection::Data& jetData, const METSelection::Data& metData) {
  ensureAnalyzeAllowed(event.eventID());
  return privateAnalyze(tauData, jetData, metData);
}

AngularCutsBase::Data AngularCutsBase::privateAnalyze(const TauSelection::Data& tauData, const JetSelection::Data& jetData, const METSelection::Data& metData) {
  Data output;
  cSubAllEvents.increment();
  output.bPassedSelection = true;
  // Calculate delta phi between MET and tau
  output.fDeltaPhiTauMET = std::fabs(ROOT::Math::VectorUtil::DeltaPhi(tauData.getSelectedTau().p4(), metData.getMET())*57.29578);
  size_t maxIndex = std::min(nMaxJets, jetData.getSelectedJets().size());
  for (size_t i = 0; i < maxIndex; ++i) {
    // Calculate delta phi between MET and jet
    double dphi = std::fabs(ROOT::Math::VectorUtil::DeltaPhi(jetData.getSelectedJets()[i].p4(), metData.getMET())*57.29578);
    output.fDeltaPhiJetMET.push_back(dphi);
    if (bEnableOptimizationPlots)
      hOptimizationPlots[i]->Fill(output.fDeltaPhiTauMET, dphi);
    // Make cut
    if (i < nConsideredJets) {
      bool passedStatus = true;
      if (fType == kCollinear)
        passedStatus = doCollinearCuts(output.fDeltaPhiTauMET, dphi, fCutValue[i], output.f1DCutVariables);
      else if (fType == kBackToBack)
        passedStatus = doBackToBackCuts(output.fDeltaPhiTauMET, dphi, fCutValue[i], output.f1DCutVariables);
      output.bPassedSelection = output.bPassedSelection && passedStatus;
      if (output.bPassedSelection)
        cSubPassedCuts[i].increment();
    }
    output.fPassedCutStatus.push_back(output.bPassedSelection);
  }
  // Fill main counter if passed
  if (output.bPassedSelection)
    cPassedAngularCuts.increment();
  // Return data object
  return output;
}

bool AngularCutsBase::doCollinearCuts(const double deltaPhiTauMET, const double deltaPhiJetMET, double cutValue, std::vector< double > results) {
  double x = deltaPhiJetMET - 180.0;
  double value = std::sqrt(x*x + deltaPhiTauMET*deltaPhiTauMET);
  results.push_back(value);
  return value > cutValue;
}

bool AngularCutsBase::doBackToBackCuts(const double deltaPhiTauMET, const double deltaPhiJetMET, double cutValue, std::vector< double > results) {
  double x = deltaPhiTauMET - 180.0;
  double value = std::sqrt(x*x + deltaPhiJetMET*deltaPhiJetMET);
  results.push_back(value);
  return value > cutValue;
}

AngularCutsCollinear::AngularCutsCollinear(const ParameterSet& config, EventCounter& eventCounter, HistoWrapper& histoWrapper, CommonPlots* commonPlots, const std::string& postfix)
: AngularCutsBase(config, eventCounter, histoWrapper, commonPlots, "Collinear", AngularCutsBase::kCollinear, postfix) { }

AngularCutsCollinear::~AngularCutsCollinear() { }

AngularCutsBackToBack::AngularCutsBackToBack(const ParameterSet& config, EventCounter& eventCounter, HistoWrapper& histoWrapper, CommonPlots* commonPlots, const std::string& postfix)
: AngularCutsBase(config, eventCounter, histoWrapper, commonPlots, "BackToBack", AngularCutsBase::kBackToBack, postfix) { }

AngularCutsBackToBack::~AngularCutsBackToBack() { }
