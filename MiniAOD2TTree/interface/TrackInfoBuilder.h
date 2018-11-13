#ifndef TrackInfoBuilder_h
#define TrackInfoBuilder_h

#include <cmath>
#include "TVector3.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "RecoVertex/VertexTools/interface/VertexDistance3D.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

class TrackInfoBuilder { 
 
 public:
 
  TrackInfoBuilder() {}
  virtual ~TrackInfoBuilder() {}
 
 public:
 
  const float& getTrackMomentum()   const {return trkMomentum;}   // track momentum
  const float& getTrackEta()        const {return trkEta;}        // track pseudorapidity
  const float& getTrackPhi()        const {return trkPhi;}        // track polar angle
  const float& getTrackEtaRel()     const {return trkEtaRel;}     // track pseudorapidity, relative to the jet axis
  const float& getTrackPtRel()      const {return trkPtRel;}      // track transverse momentum, relative to the jet axis
  const float& getTrackPPar()       const {return trkPPar;}       // track parallel momentum, along the jet axis
  const float& getTrackDeltaR()     const {return trkDeltaR;}     // track pseudoangular distance from the jet axis
  const float& getTrackPtRatio()    const {return trkPtRatio;}    // track transverse momentum, relative to the jet axis, normalized to its energy
  const float& getTrackPParRatio()  const {return trkPParRatio;}  // track parallel momentum, along the jet axis, normalized to its energy
  const float& getTrackSip2dVal()   const {return trkSip2dVal;}   // track 2D signed impact parameter
  const float& getTrackSip2dSig()   const {return trkSip2dSig;}   // track 2D signed impact parameter significance
  const float& getTrackSip3dVal()   const {return trkSip3dVal;}   // track 3D signed impact parameter
  const float& getTrackSip3dSig()   const {return trkSip3dSig;}   // track 3D signed impact parameter significance
  const float& getTrackJetDistVal() const {return trkJetDistVal;} // minimum track approach distance to jet axis
  const float& getTrackJetDistSig() const {return trkJetDistSig;} // minimum track approach distance to jet axis significance
  
  void compute(const edm::ESHandle<TransientTrackBuilder> builder,
	       const pat::PackedCandidate &pfc,
	       const pat::Jet &jet,
	       const reco::Vertex &pv)
  {
    math::XYZVector jetDir = jet.momentum().Unit();
    GlobalVector jetXYZVector(jet.px(),jet.py(),jet.pz());
    
    // Get pseudo track
    const auto &trk = pfc.pseudoTrack();
    
    reco::TransientTrack transientTrack(builder->build(trk));
    Measurement1D meas_ip2d = IPTools::signedTransverseImpactParameter(transientTrack, jetXYZVector, pv).second;
    Measurement1D meas_ip3d = IPTools::signedImpactParameter3D(transientTrack, jetXYZVector, pv).second;
    Measurement1D jetdist = IPTools::jetTrackDistance(transientTrack, jetXYZVector, pv).second;
    math::XYZVector trackMom = trk.momentum();
    double trackMag = std::sqrt(trackMom.Mag2());
    
    TVector3 trackMom3(trackMom.x(),trackMom.y(),trackMom.z());
    TVector3 jetDir3(jetDir.x(),jetDir.y(),jetDir.z());
    
    trkMomentum   = checkNan(trackMag);
    trkEta        = checkNan(trackMom.Eta());
    trkPhi        = checkNan(trackMom.Phi());
    trkEtaRel     = checkNan(reco::btau::etaRel(jetDir, trackMom));
    trkPtRel      = checkNan(trackMom3.Perp(jetDir3));
    trkPPar       = checkNan(jetDir.Dot(trackMom));
    trkDeltaR     = checkNan(reco::deltaR(trackMom, jetDir));
    trkPtRatio    = checkNan(trackMom3.Perp(jetDir3) / trackMag);
    trkPParRatio  = checkNan(jetDir.Dot(trackMom) / trackMag);
    trkSip2dVal   = checkNan(meas_ip2d.value());
    trkSip2dSig   = checkNan(meas_ip2d.significance());
    trkSip3dVal   = checkNan(meas_ip3d.value());
    trkSip3dSig   = checkNan(meas_ip3d.significance());
    trkJetDistVal = checkNan(jetdist.value());
    trkJetDistSig = checkNan(jetdist.significance());
  }
  
 private:
  
  float trkMomentum   = 0.0;
  float trkEta        = 0.0;
  float trkPhi        = 0.0;
  float trkEtaRel     = 0.0;
  float trkPtRel      = 0.0;
  float trkPPar       = 0.0;
  float trkDeltaR     = 0.0;
  float trkPtRatio    = 0.0;
  float trkPParRatio  = 0.0;
  float trkSip2dVal   = 0.0;
  float trkSip2dSig   = 0.0;
  float trkSip3dVal   = 0.0;
  float trkSip3dSig   = 0.0;
  float trkJetDistVal = 0.0;
  float trkJetDistSig = 0.0;
  
  
  float checkNan(const float &val)
  {
    if(std::isinf(val) || std::isnan(val))
      {     
	return 0.0;
      }
    else if(val < -1e32 || val > 1e32)
      {
	return 0.0;
      }
    return val;
  }
  
};
#endif
