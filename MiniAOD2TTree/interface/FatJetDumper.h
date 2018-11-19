#ifndef FatJetDumper_h
#define FatJetDumper_h

#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

#include <string>
#include <vector>

#include "TTree.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/BaseDumper.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/FourVectorDumper.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/PackedCandidate.h"

#include "HiggsAnalysis/MiniAOD2TTree/interface/QGTaggingVariables.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/TrackInfoBuilder.h"
//#include "DataFormats/BTauReco/interface/CATopJetTagInfo.h"

class QGTaggingVariables;

class FatJetDumper : public BaseDumper {
    public:
        FatJetDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets);
	~FatJetDumper();

        void book(TTree*);
	bool fill(edm::Event&, const edm::EventSetup&);
        void reset();

    private:
        /// Returns true, if the jet passes the specified jetID
        bool passJetID(int id, const pat::Jet& jet);
        
    private:
	edm::EDGetTokenT<reco::GenParticleCollection> genParticleToken;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetToken;
	edm::EDGetTokenT<edm::View<pat::Jet>> *subjetToken;
	
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJESup;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJESdown;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJERup;
        edm::EDGetTokenT<edm::View<pat::Jet>> *jetJERdown;
	
	edm::EDGetTokenT<double> rho_token;
	edm::EDGetTokenT<reco::VertexCollection> vertex_token;
	edm::EDGetTokenT<reco::VertexCompositePtrCandidateCollection> svToken;
	edm::ESHandle<TransientTrackBuilder> builder_;

        std::vector<float> *discriminators;
	std::vector<double> *userfloats;
	int nUserfloats;
	std::vector<int> *userints;
	int nUserints;
	
        std::vector<int> *hadronFlavour;
        std::vector<int> *partonFlavour;

        std::vector<bool> *jetIDloose;
        std::vector<bool> *jetIDtight;
        std::vector<bool> *jetIDtightLeptonVeto;

        std::vector<bool> *jetPUIDloose;
	std::vector<bool> *jetPUIDmedium;
	std::vector<bool> *jetPUIDtight;

        // 4-vector for generator jet
        FourVectorDumper *MCjet;
        
	// Systematics variations for tau 4-vector
	bool systVariations;
        FourVectorDumper *systJESup;
        FourVectorDumper *systJESdown;
        FourVectorDumper *systJERup;
        FourVectorDumper *systJERdown;
	
	bool fillPFCands;
	
	std::string puMitigationTool;
	std::string mcjecPath;
	std::string datajecPath;
	FactorizedJetCorrector *mcJEC;
	FactorizedJetCorrector *mcJEC_PUPPI;
	FactorizedJetCorrector *dataJEC;
	FactorizedJetCorrector *dataJEC_PUPPI;
	
	std::vector<double> *corrPrunedMass;
	std::vector<int> *numberOfDaughters;
	std::vector<int> *nSubjets;
	std::vector<double> *sdsubjet1_pt;
	std::vector<double> *sdsubjet1_eta;
	std::vector<double> *sdsubjet1_phi;
	std::vector<double> *sdsubjet1_mass;
	std::vector<double> *sdsubjet1_csv;
	std::vector<double> *sdsubjet1_deepcsv;
	std::vector<double> *sdsubjet1_axis1;
	std::vector<double> *sdsubjet1_axis2;
	std::vector<double> *sdsubjet1_ptD;
	std::vector<int> *sdsubjet1_mult;
	std::vector<double> *sdsubjet1_tau1;
	std::vector<double> *sdsubjet1_tau2;
	std::vector<double> *sdsubjet1_tau3;
	std::vector<double> *sdsubjet1_tau4;
	
	std::vector<double> *sdsubjet2_pt;
	std::vector<double> *sdsubjet2_eta;
	std::vector<double> *sdsubjet2_phi;
	std::vector<double> *sdsubjet2_mass;
	std::vector<double> *sdsubjet2_csv;
	std::vector<double> *sdsubjet2_deepcsv;
	std::vector<double> *sdsubjet2_axis1;
	std::vector<double> *sdsubjet2_axis2;
	std::vector<double> *sdsubjet2_ptD;
	std::vector<int> *sdsubjet2_mult;
	std::vector<double> *sdsubjet2_tau1;
	std::vector<double> *sdsubjet2_tau2;
	std::vector<double> *sdsubjet2_tau3;
	std::vector<double> *sdsubjet2_tau4;

	// Jet Constituent variables
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
