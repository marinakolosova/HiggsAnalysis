// -*- c++ -*-
#ifndef HiggsAnalysis_HeavyChHiggsToTauNu_SignalAnalysis_h
#define HiggsAnalysis_HeavyChHiggsToTauNu_SignalAnalysis_h

#include "HiggsAnalysis/HeavyChHiggsToTauNu/interface/EventCounter.h"

namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}

namespace HPlus {
  class SignalAnalysis {
  public:
    explicit SignalAnalysis(const edm::ParameterSet& iConfig, EventCounter& eventCounter);
    ~SignalAnalysis();

    // Interface towards the EDProducer
    void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);

  private:
    void analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup);

    Count count1;
    Count count2;
  };
}

#endif
