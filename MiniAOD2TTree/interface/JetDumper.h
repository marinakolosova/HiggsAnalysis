#ifndef JetDumper_h
#define JetDumper_h

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"

#include <string>
#include <vector>

#include "TTree.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/BaseDumper.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/FourVectorDumper.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "HiggsAnalysis/MiniAOD2TTree/interface/TrackInfoBuilder.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/QGTaggingVariables.h"
class QGTaggingVariables;

class JetDumper : public BaseDumper {
    public:
	JetDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets);
	~JetDumper();

        void book(TTree*);
	bool fill(edm::Event&, const edm::EventSetup&);
        void reset();

    private:
        /// Returns true, if the jet passes the specified jetID
        bool passJetID(int id, const pat::Jet& jet);
        
    private:
	edm::EDGetTokenT<reco::GenParticleCollection> genParticleToken;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetToken;

        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJESup;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJESdown;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJERup;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJERdown;
	
	edm::EDGetTokenT<edm::View<reco::Vertex> > vtxToken;
	edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> svToken;
	edm::ESHandle<TransientTrackBuilder> builder_;
	
        std::vector<float> *discriminators;
        std::vector<double> *userfloats;
	int nUserfloats;
	std::vector<int> *userints;
	int nUserints;
        //std::vector<JetCorrectionUncertainty*> fJECUncertainty;
	
        std::vector<int> *hadronFlavour;
        std::vector<int> *partonFlavour;

        std::vector<bool> *jetIDloose;
        std::vector<bool> *jetIDtight;
        std::vector<bool> *jetIDtightLeptonVeto;

        std::vector<bool> *jetPUIDloose;
	std::vector<bool> *jetPUIDmedium;
	std::vector<bool> *jetPUIDtight;

        // MC origin
        std::vector<bool> *originatesFromW;
        std::vector<bool> *originatesFromZ;
        std::vector<bool> *originatesFromTop;
        std::vector<bool> *originatesFromChargedHiggs;
        std::vector<bool> *originatesFromUnknown;
        
        // 4-vector for generator jet
        FourVectorDumper *MCjet;
        
        // Systematics variations for tau 4-vector
	bool systVariations;
        FourVectorDumper *systJESup;
        FourVectorDumper *systJESdown;
        FourVectorDumper *systJERup;
        FourVectorDumper *systJERdown;	
	
	// QGTagging variables
	std::vector<double> *axis1;
	std::vector<double> *axis2;
	std::vector<double> *ptD;
	std::vector<int> *mult;
	
	// Jet Constituent variables
	bool fillPFCands;
	std::vector<std::vector<double>> *pfCand_pt;
	std::vector<std::vector<double>> *pfCand_eta;
	std::vector<std::vector<double>> *pfCand_phi;
	std::vector<std::vector<double>> *pfCand_energy;
	std::vector<std::vector<double>> *pfCand_hcalFraction;
	std::vector<std::vector<double>> *pfCand_puppiWeight;
	std::vector<std::vector<int>>    *pfCand_charge;
	std::vector<std::vector<int>>    *pfCand_pdgId;
	std::vector<std::vector<int>>    *pfCand_pvAssociationQuality;
	std::vector<std::vector<int>>    *pfCand_lostInnerHits;
	std::vector<std::vector<double>> *pfCand_dz;
	std::vector<std::vector<double>> *pfCand_dxy;
	std::vector<std::vector<double>> *pfCand_dzError;
	std::vector<std::vector<double>> *pfCand_dxyError;
	std::vector<std::vector<double>> *pfCand_vertexNormChi2;
	std::vector<std::vector<int>>    *pfCand_qualityMask;
	std::vector<std::vector<double>> *pfCand_dptdpt;
	std::vector<std::vector<double>> *pfCand_detadeta;
	std::vector<std::vector<double>> *pfCand_dphidphi;
	std::vector<std::vector<double>> *pfCand_dxydxy;
	std::vector<std::vector<double>> *pfCand_dzdz;
	std::vector<std::vector<double>> *pfCand_dxydz;
	std::vector<std::vector<double>> *pfCand_dphidxy;
	std::vector<std::vector<double>> *pfCand_dlambdadz;
	std::vector<std::vector<double>> *pfCand_minDRsv;
	std::vector<std::vector<double>> *track_momentum;
	std::vector<std::vector<double>> *track_eta;
	std::vector<std::vector<double>> *track_etarel;
	std::vector<std::vector<double>> *track_ptrel;
	std::vector<std::vector<double>> *track_ppar;
	std::vector<std::vector<double>> *track_deltar;
	std::vector<std::vector<double>> *track_ptratio;
	std::vector<std::vector<double>> *track_pparratio;
	std::vector<std::vector<double>> *track_sip2dval;
	std::vector<std::vector<double>> *track_sip2dsig;
	std::vector<std::vector<double>> *track_sip3dval;
	std::vector<std::vector<double>> *track_sip3dsig;
	std::vector<std::vector<double>> *track_jetdistval;
	
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

 protected:
        QGTaggingVariables* qgTaggingVariables;
};
#endif
