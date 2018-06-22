// -*- c++ -*-
#ifndef EventSelection_TopTagSFCalculator_h
#define EventSelection_TopTagSFCalculator_h

#include "EventSelection/interface/BaseSelection.h"
#include "EventSelection/interface/JetSelection.h"
#include "EventSelection/interface/TopSelectionBDT.h"
#include "Framework/interface/EventCounter.h"
#include "Tools/interface/DirectionalCut.h"

#include <string>
#include <vector>
#include "TFormula.h"
#include "boost/optional.hpp"

class ParameterSet;
class HistoWrapper;
class WrappedTH1;

class TopTagSFInputItem {
public:
  TopTagSFInputItem(float ptMin, float ptMax, const std::string& formula);
  TopTagSFInputItem(float ptMin, float ptMax, float eff);
  ~TopTagSFInputItem();
  
  /// Returns true if the jet pt is in the range of this input item
  const bool matchesPtRange(float pt) const;
  /// Returns true if the jet pt is higher than the range of this input item
  const bool isGreaterThanPtRange(float pt) const { return pt > fPtMax; }
  /// Returns the input value
  const float getValueByPt(float pt) const;
  /// Returns ptmax
  const float getPtMax() const { return fPtMax; }
  /// Set as overflow bin
  void setAsOverflowBinPt();
  /// Debug
  void debug() const;
  
private:
  float fPtMin;
  float fPtMax;
  bool bIsOverflowBinPt;
  TFormula fFormula;
};

/// Mediator class between individual TopTagSFInputItem and TopTagSFCalculator
class TopTagSFInputStash {
public:
  enum TopTagJetFlavorType { 
    // README: https://hypernews.cern.ch/HyperNews/CMS/get/btag/1482/1/1/1/1/1.html
    kBJet,
    kCJet,
    // kGJet,   // obsolete (see README)
    // kUDSJet, // obsolete (see README)
    kUDSGJet,
  };
  TopTagSFInputStash();
  ~TopTagSFInputStash();
  
  /// Add input 
  void addInput(TopTagJetFlavorType flavor, float ptMin, float ptMax, const std::string& formula);
  void addInput(TopTagJetFlavorType flavor, float ptMin, float ptMax, float eff);
  /// Returns the size of the collection
  const size_t sizeOfList(TopTagJetFlavorType flavor) const { return getConstCollection(flavor).size(); }
  /// Returns value by pt
  const float getInputValueByPt(TopTagJetFlavorType flavor, float pt) const;
  /// Set maximum bins as overflow bins
  void setOverflowBinByPt(const std::string& label);
  /// Debug
  void debug() const;
  
private:
  const std::vector<TopTagSFInputItem*>& getConstCollection(TopTagJetFlavorType flavor) const;
  std::vector<TopTagSFInputItem*>& getCollection(TopTagJetFlavorType flavor);
  
  std::vector<TopTagSFInputItem*> fBToB;
  std::vector<TopTagSFInputItem*> fCToB;
  // std::vector<TopTagSFInputItem*> fGToB;
  std::vector<TopTagSFInputItem*> fUdsgToB;
};

class TopTagSFCalculator {
public:
  enum TopTagSFVariationType {
    kNominal,
    kVariationTagUp,
    kVariationMistagUp,
    kVariationTagDown,
    kVariationMistagDown,
  };

  /// Constructor
  explicit TopTagSFCalculator(const ParameterSet& config);
  /// Destructor
  virtual ~TopTagSFCalculator();
  /// Book histograms
  void bookHistograms(TDirectory* dir, HistoWrapper& histoWrapper);
  /// Calculate scale factor for the event
  const float calculateSF(const std::vector<Jet>& selectedJets, const std::vector<Jet>& selectedBJets);
  /// Returns the size of the efficiency config items
  const size_t sizeOfEfficiencyList(TopTagSFInputStash::TopTagJetFlavorType flavor, const std::string& direction) const;
  /// Returns the size of the SF config items
  const size_t sizeOfSFList(TopTagSFInputStash::TopTagJetFlavorType flavor, const std::string& direction) const;
  
private:
  /// Method for handling the efficiency input
  void handleEfficiencyInput(boost::optional<std::vector<ParameterSet>> psets);
  /// Method for handling the SF input
  void handleSFInput(boost::optional<std::vector<ParameterSet>> psets);
  /// Method for converting flavor string to flavor type
  TopTagSFInputStash::TopTagJetFlavorType getFlavorTypeForEfficiency(const std::string& str) const;
  /// Method for converting flavor string to flavor type
  TopTagSFInputStash::TopTagJetFlavorType getFlavorTypeForSF(int i) const;
  /// Find input value
  float getInputValueByPt(std::vector<TopTagSFInputItem>& container, float pt);

  /// Disentangle variation info type from config
  const TopTagSFVariationType parseVariationType(const ParameterSet& config) const;
  
  /// Systematic variation type
  const TopTagSFVariationType fVariationInfo;
  /// parton->b jet efficiencies from config
  TopTagSFInputStash fEfficiencies;
  TopTagSFInputStash fEfficienciesUp;
  TopTagSFInputStash fEfficienciesDown;
  /// parton->b jet data/MC scalefactors from config
  TopTagSFInputStash fSF;
  TopTagSFInputStash fSFUp;
  TopTagSFInputStash fSFDown;
  /// Validity of input
  bool isActive;
  // Histograms
  WrappedTH1* hTopTagSF;
  WrappedTH1* hTopTagSFRelUncert;
};

#endif