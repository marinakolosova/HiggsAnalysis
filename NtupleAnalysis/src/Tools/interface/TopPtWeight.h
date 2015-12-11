// -*- c++ -*-
#ifndef Tools_TopPtWeight_h
#define Tools_TopPtWeight_h

#include "Framework/interface/ParameterSet.h"
#include "DataFormat/interface/Event.h"

#include <string>

class TH1;

class TopPtWeight {
public:
  explicit TopPtWeight(boost::optional<const ParameterSet> pset);
  ~TopPtWeight();

  // Disable copying, assignment, and moving
  // Mainly because according to the design, there should be no need for them
  TopPtWeight(const TopPtWeight&) = delete;
  TopPtWeight(TopPtWeight&&) = delete;
  TopPtWeight& operator=(const TopPtWeight&) = delete;
  TopPtWeight& operator=(TopPtWeight&&) = delete;

  double getWeight(const Event& event);
  void calculateWeights(TH1*, TH1*);

private:
  double fParA;
  double fParB;
};
#endif
