// -*- c++ -*-
#ifndef EventSelection_METSelection_h
#define EventSelection_METSelection_h

#include "EventSelection/interface/BaseSelection.h"
#include "DataFormat/interface/MET.h"
#include "Framework/interface/EventCounter.h"
#include "Tools/interface/DirectionalCut.h"

#include <string>
#include <vector>

class ParameterSet;
class CommonPlots;
class Event;
class EventCounter;
class HistoWrapper;
class WrappedTH1;
class WrappedTH2;

class METSelection: public BaseSelection {
public:
  enum METType {
    kGenMET,
    kL1MET,
    kCaloMET,
    kType1MET
  };
  
    /**
    * Class to encapsulate the access to the data members of
    * TauSelection. If you want to add a new accessor, add it here
    * and keep all the data of TauSelection private.
    */
  class Data {
  public:
    // The reason for pointer instead of reference is that const
    // reference allows temporaries, while const pointer does not.
    // Here the object pointed-to must live longer than this object.
    Data();
    ~Data();

    const bool passedSelection() const { return bPassedSelection; }
    const math::XYVectorD& getMET() const;

    friend class METSelection;

  private:
    /// Boolean for passing selection
    bool bPassedSelection;
    /// MET collection for storing MET object (as p2, because one needs to be able to manipulate it)
    std::vector<math::XYVectorD> fSelectedMET;
  };
  
  // Main class
  explicit METSelection(const ParameterSet& config, EventCounter& eventCounter, HistoWrapper& histoWrapper, CommonPlots* commonPlots, const std::string& postfix = "");
  virtual ~METSelection();

  virtual void bookHistograms(TDirectory* dir);
  
  /// Use silentAnalyze if you do not want to fill histograms or increment counters
  Data silentAnalyze(const Event& event, int nVertices);
  /// analyze does fill histograms and incrementes counters
  Data analyze(const Event& event, int nVertices);

private:
  Data privateAnalyze(const Event& iEvent, int nVertices);

  // Input parameters
  const DirectionalCut<float> fMETCut;
  const bool bApplyPhiCorrections;
  METType fMETType;
  
  // Event counter for passing selection
  Count cPassedMETSelection;
  // Histograms
};

#endif