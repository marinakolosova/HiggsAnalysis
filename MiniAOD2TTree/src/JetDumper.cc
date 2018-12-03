#include "HiggsAnalysis/MiniAOD2TTree/interface/JetDumper.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/GenParticleTools.h"

#include "DataFormats/JetReco/interface/PileupJetIdentifier.h"
#include "HiggsAnalysis/MiniAOD2TTree/interface/NtupleAnalysis_fwd.h"

#include <unordered_map>
#include <algorithm>
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "DataFormats/Candidate/interface/VertexCompositePtrCandidate.h"

JetDumper::JetDumper(edm::ConsumesCollector&& iConsumesCollector, std::vector<edm::ParameterSet>& psets)
  : genParticleToken(iConsumesCollector.consumes<reco::GenParticleCollection>(edm::InputTag("prunedGenParticles"))),
    vtxToken(iConsumesCollector.consumes<edm::View<reco::Vertex> >(edm::InputTag("offlineSlimmedPrimaryVertices"))),
    svToken(iConsumesCollector.consumes<reco::VertexCompositePtrCandidateCollection>(edm::InputTag("slimmedSecondaryVertices"))),
    qgTaggingVariables(new QGTaggingVariables)
{
    inputCollections = psets;
    booked           = false;

    systVariations = inputCollections[0].getParameter<bool>("systVariations");
    fillPFCands = inputCollections[0].getParameter<bool>("fillPFCands");
    
    pt  = new std::vector<double>[inputCollections.size()];
    eta = new std::vector<double>[inputCollections.size()];    
    phi = new std::vector<double>[inputCollections.size()];    
    e   = new std::vector<double>[inputCollections.size()];    

    //p4 = new std::vector<reco::Candidate::LorentzVector>[inputCollections.size()];
    pdgId = new std::vector<short>[inputCollections.size()];
    hadronFlavour = new std::vector<int>[inputCollections.size()];
    partonFlavour = new std::vector<int>[inputCollections.size()];

    nDiscriminators = inputCollections[0].getParameter<std::vector<std::string> >("discriminators").size();
    discriminators = new std::vector<float>[inputCollections.size()*nDiscriminators];
    nUserfloats = inputCollections[0].getParameter<std::vector<std::string> >("userFloats").size();
    userfloats  = new std::vector<double>[inputCollections.size()*nUserfloats];
    nUserints   = inputCollections[0].getParameter<std::vector<std::string> >("userInts").size();
    userints    = new std::vector<int>[inputCollections.size()*nUserints];
    jetToken   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJESup   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJESdown = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJERup   = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    jetJERdown = new edm::EDGetTokenT<edm::View<pat::Jet> >[inputCollections.size()];
    for(size_t i = 0; i < inputCollections.size(); ++i){
        edm::InputTag inputtag = inputCollections[i].getParameter<edm::InputTag>("src");
        jetToken[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtag);

	if(systVariations){
	  edm::InputTag inputtagJESup = inputCollections[i].getParameter<edm::InputTag>("srcJESup");
          jetJESup[i]   = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJESup);

          edm::InputTag inputtagJESdown = inputCollections[i].getParameter<edm::InputTag>("srcJESdown");
          jetJESdown[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJESdown);

          edm::InputTag inputtagJERup = inputCollections[i].getParameter<edm::InputTag>("srcJERup");
          jetJERup[i]   = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJERup);
        
          edm::InputTag inputtagJERdown = inputCollections[i].getParameter<edm::InputTag>("srcJERdown");
          jetJERdown[i] = iConsumesCollector.consumes<edm::View<pat::Jet>>(inputtagJERdown);
	}
    }
    
    useFilter = false;
    for(size_t i = 0; i < inputCollections.size(); ++i){
	bool param = inputCollections[i].getUntrackedParameter<bool>("filter",false);
        if(param) useFilter = true;
    }

    jetIDloose = new std::vector<bool>[inputCollections.size()];
    jetIDtight = new std::vector<bool>[inputCollections.size()];
    jetIDtightLeptonVeto = new std::vector<bool>[inputCollections.size()];

    jetPUIDloose = new std::vector<bool>[inputCollections.size()];
    jetPUIDmedium = new std::vector<bool>[inputCollections.size()];
    jetPUIDtight = new std::vector<bool>[inputCollections.size()];
    
    originatesFromW = new std::vector<bool>[inputCollections.size()];
    originatesFromZ = new std::vector<bool>[inputCollections.size()];
    originatesFromTop = new std::vector<bool>[inputCollections.size()];
    originatesFromChargedHiggs = new std::vector<bool>[inputCollections.size()];
    originatesFromUnknown = new std::vector<bool>[inputCollections.size()]; 
    
    MCjet = new FourVectorDumper[inputCollections.size()];
    if(systVariations){
      systJESup = new FourVectorDumper[inputCollections.size()];
      systJESdown = new FourVectorDumper[inputCollections.size()];
      systJERup = new FourVectorDumper[inputCollections.size()];
      systJERdown = new FourVectorDumper[inputCollections.size()];
    }
    
    axis1 = new std::vector<double>[inputCollections.size()];
    axis2 = new std::vector<double>[inputCollections.size()];
    ptD   = new std::vector<double>[inputCollections.size()];
    mult  = new std::vector<int>[inputCollections.size()];
    pullRap = new std::vector<double>[inputCollections.size()];
    pullPhi = new std::vector<double>[inputCollections.size()];
    charge = new std::vector<double>[inputCollections.size()];
    
    if (fillPFCands){
      pfCand_pt = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_eta = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_phi = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_energy = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_hcalFraction = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_puppiWeight = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_charge = new std::vector<std::vector<int> >[inputCollections.size()];
      pfCand_pdgId = new std::vector<std::vector<int> >[inputCollections.size()];
      pfCand_pvAssociationQuality = new std::vector<std::vector<int> >[inputCollections.size()];
      pfCand_lostInnerHits = new std::vector<std::vector<int> >[inputCollections.size()];
      pfCand_dz = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dxy = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dzError = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dxyError = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_vertexNormChi2 = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_qualityMask = new std::vector<std::vector<int> >[inputCollections.size()];
      pfCand_dptdpt = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_detadeta = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dphidphi = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dxydxy = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dzdz = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dxydz = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dphidxy = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_dlambdadz = new std::vector<std::vector<double> >[inputCollections.size()];
      pfCand_minDRsv = new std::vector<std::vector<double> >[inputCollections.size()];
      track_momentum = new std::vector<std::vector<double> >[inputCollections.size()];
      track_eta = new std::vector<std::vector<double> >[inputCollections.size()];
      track_etarel = new std::vector<std::vector<double> >[inputCollections.size()];
      track_ptrel = new std::vector<std::vector<double> >[inputCollections.size()];
      track_ppar = new std::vector<std::vector<double> >[inputCollections.size()];
      track_deltar = new std::vector<std::vector<double> >[inputCollections.size()];
      track_ptratio = new std::vector<std::vector<double> >[inputCollections.size()];
      track_pparratio = new std::vector<std::vector<double> >[inputCollections.size()];
      track_sip2dval = new std::vector<std::vector<double> >[inputCollections.size()];
      track_sip2dsig = new std::vector<std::vector<double> >[inputCollections.size()];
      track_sip3dval = new std::vector<std::vector<double> >[inputCollections.size()];
      track_sip3dsig = new std::vector<std::vector<double> >[inputCollections.size()];
      track_jetdistval = new std::vector<std::vector<double> >[inputCollections.size()];
    }

}

JetDumper::~JetDumper(){}

void JetDumper::book(TTree* tree){
  booked = true;
  for(size_t i = 0; i < inputCollections.size(); ++i){
    std::string name = inputCollections[i].getUntrackedParameter<std::string>("branchname","");
    if(name.length() == 0) name = inputCollections[i].getParameter<edm::InputTag>("src").label();
    tree->Branch((name+"_pt").c_str(),&pt[i]);
    tree->Branch((name+"_eta").c_str(),&eta[i]);
    tree->Branch((name+"_phi").c_str(),&phi[i]);
    tree->Branch((name+"_e").c_str(),&e[i]);    
    //tree->Branch((name+"_p4").c_str(),&p4[i]);
    tree->Branch((name+"_pdgId").c_str(),&pdgId[i]);
    tree->Branch((name+"_hadronFlavour").c_str(),&hadronFlavour[i]);
    tree->Branch((name+"_partonFlavour").c_str(),&partonFlavour[i]);
    
    std::vector<std::string> discriminatorNames = inputCollections[i].getParameter<std::vector<std::string> >("discriminators");
    for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
      std::string branch_name = discriminatorNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      if (pos_semicolon!=std::string::npos){
	branch_name = branch_name.erase(pos_semicolon,1);
      }
      tree->Branch((name+"_"+branch_name).c_str(),&discriminators[inputCollections.size()*iDiscr+i]);
    }
    std::vector<std::string> userfloatNames = inputCollections[i].getParameter<std::vector<std::string> >("userFloats");
    for(size_t iDiscr = 0; iDiscr < userfloatNames.size(); ++iDiscr) {
      std::string branch_name = userfloatNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      branch_name = branch_name.erase(pos_semicolon,1);
      tree->Branch((name+"_"+branch_name).c_str(),&userfloats[inputCollections.size()*iDiscr+i]);
    }
    std::vector<std::string> userintNames = inputCollections[i].getParameter<std::vector<std::string> >("userInts");
    for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
      std::string branch_name = userintNames[iDiscr];
      size_t pos_semicolon = branch_name.find(":");
      branch_name = branch_name.erase(pos_semicolon,1);
      tree->Branch((name+"_"+branch_name).c_str(),&userints[inputCollections.size()*iDiscr+i]);
    }

    tree->Branch((name+"_IDloose").c_str(),&jetIDloose[i]);
    tree->Branch((name+"_IDtight").c_str(),&jetIDtight[i]);
    tree->Branch((name+"_IDtightLeptonVeto").c_str(),&jetIDtightLeptonVeto[i]);

    tree->Branch((name+"_PUIDloose").c_str(),&jetPUIDloose[i]);
    tree->Branch((name+"_PUIDmedium").c_str(),&jetPUIDmedium[i]);
    tree->Branch((name+"_PUIDtight").c_str(),&jetPUIDtight[i]);
    
    tree->Branch((name+"_originatesFromW").c_str(),&originatesFromW[i]);
    tree->Branch((name+"_originatesFromZ").c_str(),&originatesFromZ[i]);
    tree->Branch((name+"_originatesFromTop").c_str(),&originatesFromTop[i]);
    tree->Branch((name+"_originatesFromChargedHiggs").c_str(),&originatesFromChargedHiggs[i]);
    tree->Branch((name+"_originatesFromUnknown").c_str(),&originatesFromUnknown[i]);
    
    MCjet[i].book(tree, name, "MCjet");
    
    if(systVariations){
      systJESup[i].book(tree, name, "JESup");
      systJESdown[i].book(tree, name, "JESdown");
      systJERup[i].book(tree, name, "JERup");
      systJERdown[i].book(tree, name, "JERdown");
    }

    tree->Branch((name+"_axis1").c_str(), &axis1[i]);
    tree->Branch((name+"_axis2").c_str(), &axis2[i]);
    tree->Branch((name+"_ptD").c_str(),   &ptD[i]);
    tree->Branch((name+"_mult").c_str(),  &mult[i]);
    tree->Branch((name+"_pullRap").c_str(), &pullRap[i]);
    tree->Branch((name+"_pullPhi").c_str(), &pullPhi[i]);
    tree->Branch((name+"_charge").c_str(), &charge[i]);
    
    // PF Candidate variables
    if (fillPFCands){
      tree->Branch((name+"_pfCand_pt").c_str(), &pfCand_pt[i]);
      tree->Branch((name+"_pfCand_eta").c_str(), &pfCand_eta[i]);
      tree->Branch((name+"_pfCand_phi").c_str(), &pfCand_phi[i]);
      tree->Branch((name+"_pfCand_energy").c_str(), &pfCand_energy[i]);
      tree->Branch((name+"_pfCand_hcalFraction").c_str(), &pfCand_hcalFraction[i]);
      tree->Branch((name+"_pfCand_puppiWeight").c_str(), &pfCand_puppiWeight[i]);
      tree->Branch((name+"_pfCand_charge").c_str(), &pfCand_charge[i]);
      tree->Branch((name+"_pfCand_pdgId").c_str(), &pfCand_pdgId[i]);
      tree->Branch((name+"_pfCand_pvAssociationQuality").c_str(), &pfCand_pvAssociationQuality[i]);
      tree->Branch((name+"_pfCand_lostInnerHits").c_str(), &pfCand_lostInnerHits[i]);
      tree->Branch((name+"_pfCand_dz").c_str(), &pfCand_dz[i]);
      tree->Branch((name+"_pfCand_dxy").c_str(), &pfCand_dxy[i]);
      tree->Branch((name+"_pfCand_dzError").c_str(), &pfCand_dzError[i]);
      tree->Branch((name+"_pfCand_dxyError").c_str(), &pfCand_dxyError[i]);
      tree->Branch((name+"_pfCand_vertexNormChi2").c_str(), &pfCand_vertexNormChi2[i]);
      tree->Branch((name+"_pfCand_qualityMask").c_str(), &pfCand_qualityMask[i]);
      tree->Branch((name+"_pfCand_dptdpt").c_str(), &pfCand_dptdpt[i]);
      tree->Branch((name+"_pfCand_detadeta").c_str(), &pfCand_detadeta[i]);
      tree->Branch((name+"_pfCand_dphidphi").c_str(), &pfCand_dphidphi[i]);
      tree->Branch((name+"_pfCand_dxydxy").c_str(), &pfCand_dxydxy[i]);
      tree->Branch((name+"_pfCand_dzdz").c_str(), &pfCand_dzdz[i]);
      tree->Branch((name+"_pfCand_dxydz").c_str(), &pfCand_dxydz[i]);
      tree->Branch((name+"_pfCand_dphidxy").c_str(), &pfCand_dphidxy[i]);
      tree->Branch((name+"_pfCand_dlambdadz").c_str(), &pfCand_dlambdadz[i]);
      tree->Branch((name+"_pfCand_minDRsv").c_str(), &pfCand_minDRsv[i]);
      tree->Branch((name+"_track_momentum").c_str(), &track_momentum[i]);
      tree->Branch((name+"_track_eta").c_str(), &track_eta[i]);
      tree->Branch((name+"_track_etarel").c_str(), &track_etarel[i]);
      tree->Branch((name+"_track_ptrel").c_str(), &track_ptrel[i]);
      tree->Branch((name+"_track_ppar").c_str(), &track_ppar[i]);
      tree->Branch((name+"_track_deltar").c_str(), &track_deltar[i]);
      tree->Branch((name+"_track_ptratio").c_str(), &track_ptratio[i]);
      tree->Branch((name+"_track_pparratio").c_str(), &track_pparratio[i]);
      tree->Branch((name+"_track_sip2dval").c_str(), &track_sip2dval[i]);
      tree->Branch((name+"_track_sip2dsig").c_str(), &track_sip2dsig[i]);
      tree->Branch((name+"_track_sip3dval").c_str(), &track_sip3dval[i]);
      tree->Branch((name+"_track_sip3dsig").c_str(), &track_sip3dsig[i]);
      tree->Branch((name+"_track_jetdistval").c_str(), &track_jetdistval[i]);
    }

  }
}

bool JetDumper::fill(edm::Event& iEvent, const edm::EventSetup& iSetup){
    if (!booked) return true;
/*
    if (!fJECUncertainty.size()) {
      for(size_t i = 0; i < inputCollections.size(); ++i) {
        edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
        iSetup.get<JetCorrectionsRecord>().get(inputCollections[i].getParameter<std::string>("jecPayload"),JetCorParColl);
//        bool found = true;
        try {
          JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
          fJECUncertainty.push_back(new JetCorrectionUncertainty(JetCorPar));
        } catch(cms::Exception e) {
          std::cout << "Warning: cannot find cell 'Uncertainty' in JEC uncertainty table; JEC uncertainty forced to 0" << std::endl;
//          found = false;
          fJECUncertainty.push_back(nullptr);
        }

//        if (found) {
//          JetCorrectorParameters const & JetCorPar = (*JetCorParColl)["Uncertainty"];
//          fJECUncertainty.push_back(new JetCorrectionUncertainty(JetCorPar));
//        } else {
//          fJECUncertainty.push_back(nullptr);
//        }
//
      }
    }
*/
    // Get Vertices
    edm::Handle<edm::View<reco::Vertex> > vertices;
    iEvent.getByToken(vtxToken, vertices);

    // Get SVs
    edm::Handle<reco::VertexCompositePtrCandidateCollection> SVs;
    iEvent.getByToken(svToken, SVs);

    // Get Track builder
    iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", builder_);
    

    edm::Handle <reco::GenParticleCollection> genParticlesHandle;
    if (!iEvent.isRealData())
      iEvent.getByToken(genParticleToken, genParticlesHandle);

    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
        std::vector<std::string> discriminatorNames = inputCollections[ic].getParameter<std::vector<std::string> >("discriminators");
	std::vector<std::string> userfloatNames = inputCollections[ic].getParameter<std::vector<std::string> >("userFloats");
	std::vector<std::string> userintNames = inputCollections[ic].getParameter<std::vector<std::string> >("userInts");
	
        edm::Handle<edm::View<pat::Jet>> jetHandle;
        iEvent.getByToken(jetToken[ic], jetHandle);

	if(jetHandle.isValid()){

	    for(size_t i=0; i<jetHandle->size(); ++i) {
    		const pat::Jet& obj = jetHandle->at(i);

		pt[ic].push_back(obj.p4().pt());
                eta[ic].push_back(obj.p4().eta());
                phi[ic].push_back(obj.p4().phi());
                e[ic].push_back(obj.p4().energy());

		//p4[ic].push_back(obj.p4());

		for(size_t iDiscr = 0; iDiscr < discriminatorNames.size(); ++iDiscr) {
                    //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << discriminatorNames[iDiscr] << std::endl;
		    discriminators[inputCollections.size()*iDiscr+ic].push_back(obj.bDiscriminator(discriminatorNames[iDiscr]));
		}
                for(size_t iDiscr = 0; iDiscr < userfloatNames.size(); ++iDiscr) {
                    //std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userfloatNames[iDiscr] << std::endl;
                    userfloats[inputCollections.size()*iDiscr+ic].push_back(obj.userFloat(userfloatNames[iDiscr]));
                }
		for(size_t iDiscr = 0; iDiscr < userintNames.size(); ++iDiscr) {
		  // std::cout << inputCollections[ic].getUntrackedParameter<std::string>("branchname","") << " / " << userintNames[iDiscr] << std::endl;
		  userints[inputCollections.size()*iDiscr+ic].push_back(obj.userInt(userintNames[iDiscr]));
		}
		
		qgTaggingVariables->compute(&obj, true);
                axis1[ic].push_back(qgTaggingVariables->getAxis1());
                axis2[ic].push_back(qgTaggingVariables->getAxis2());
                ptD[ic].push_back(qgTaggingVariables->getPtD());
                mult[ic].push_back(qgTaggingVariables->getMult());
		pullRap[ic].push_back(qgTaggingVariables->getPullRap());
		pullPhi[ic].push_back(qgTaggingVariables->getPullPhi());
		charge[ic].push_back(qgTaggingVariables->getCharge());
		
		int genParton = 0;
		if(obj.genParton()){
		  genParton = obj.genParton()->pdgId();
		}
		pdgId[ic].push_back(genParton);
		hadronFlavour[ic].push_back(obj.hadronFlavour());
		partonFlavour[ic].push_back(obj.partonFlavour());

                // Jet ID
                jetIDloose[ic].push_back(passJetID(kJetIDLoose, obj));
                jetIDtight[ic].push_back(passJetID(kJetIDTight, obj));
                jetIDtightLeptonVeto[ic].push_back(passJetID(kJetIDTightLepVeto, obj));

		// Jet PU ID
                // https://twiki.cern.ch/twiki/bin/view/CMS/PileupJetID
               
 		double PUID = 0;
                if(obj.hasUserData("pileupJetId:fullDiscriminant")){
 		  PUID = obj.userFloat("pileupJetId:fullDiscriminant");
 		}
                int puIDflag = static_cast<int>(PUID);
		jetPUIDloose[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kLoose));
		jetPUIDmedium[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kMedium));
		jetPUIDtight[ic].push_back(PileupJetIdentifier::passJetId(puIDflag, PileupJetIdentifier::kTight));
                
                // MC origin
                bool fromW = false;
                bool fromZ = false;
                bool fromTop = false;
                bool fromHplus = false;
                bool fromUnknown = false;
                if (!iEvent.isRealData()) {
                  // Find MC parton matching to jet
                  size_t iCandidate = 0;
                  double myBestDeltaR = 9999;
                  reco::Candidate::LorentzVector jetMomentum = obj.p4();
                  for (size_t iMC=0; iMC < genParticlesHandle->size(); ++iMC) {
                    const reco::Candidate & p = (*genParticlesHandle)[iMC];
                    int absPid = std::abs(p.pdgId());
                    if (absPid >= 1 && absPid <= 5) {
                      double myDeltaR = deltaR(jetMomentum, p.p4());
                      if (myDeltaR < 0.4 && myDeltaR < myBestDeltaR) {
                        myBestDeltaR = myDeltaR;
                        iCandidate = iMC;
                      }
                    }
                  }
                  if (iCandidate > 0) {
                    // Analyze ancestry
                    const reco::Candidate & p = (*genParticlesHandle)[iCandidate];
                    std::vector<const reco::Candidate*> ancestry = GenParticleTools::findAncestry(genParticlesHandle, &p);
                    for (auto& pa: ancestry) {
                      int absPid = std::abs(pa->pdgId());
                      if (absPid == kFromW)
                        fromW = true;
                      else if (absPid == kFromZ)
                        fromZ = true;
                      else if (absPid == kFromHplus)
                        fromHplus = true;
                      else if (absPid == 6)
                        fromTop = true;
                    }
                  } else {
                    fromUnknown = true;
                  }
                } else {
                  fromUnknown = true;
                }
                originatesFromW[ic].push_back(fromW);
                originatesFromZ[ic].push_back(fromZ);
                originatesFromTop[ic].push_back(fromTop);
                originatesFromChargedHiggs[ic].push_back(fromHplus);
                originatesFromUnknown[ic].push_back(fromUnknown);
                
                // GenJet
                if (obj.genJet() != nullptr) {
                  MCjet[ic].add(obj.genJet()->pt(), obj.genJet()->eta(), obj.genJet()->phi(), obj.genJet()->energy());
                } else {
                  MCjet[ic].add(0.0, 0.0, 0.0, 0.0);
                }
                
                // Systematics
                if (systVariations && !iEvent.isRealData()) {
	          edm::Handle<edm::View<pat::Jet>> jetJESupHandle;
        	  iEvent.getByToken(jetJESup[ic], jetJESupHandle);

                  if(jetJESupHandle.isValid()){
                    const pat::Jet& sysobj = jetJESupHandle->at(i);
                    systJESup[ic].add(sysobj.p4().pt(),
                                      sysobj.p4().eta(),
                                      sysobj.p4().phi(),
                                      sysobj.p4().energy());
                  }

                  edm::Handle<edm::View<pat::Jet>> jetJESdownHandle;
                  iEvent.getByToken(jetJESdown[ic], jetJESdownHandle);
                      
                  if(jetJESdownHandle.isValid()){
                    const pat::Jet& sysobj = jetJESdownHandle->at(i);
                    systJESdown[ic].add(sysobj.p4().pt(),
                                        sysobj.p4().eta(),
                                        sysobj.p4().phi(),
                                        sysobj.p4().energy());
                  }

                  edm::Handle<edm::View<pat::Jet>> jetJERupHandle;
                  iEvent.getByToken(jetJERup[ic], jetJERupHandle);
                      
                  if(jetJERupHandle.isValid()){
                    const pat::Jet& sysobj = jetJERupHandle->at(i);
                    systJERup[ic].add(sysobj.p4().pt(),
                                      sysobj.p4().eta(),
                                      sysobj.p4().phi(),
                                      sysobj.p4().energy());
                  }
                
                  edm::Handle<edm::View<pat::Jet>> jetJERdownHandle;
                  iEvent.getByToken(jetJERdown[ic], jetJERdownHandle);
                
                  if(jetJERdownHandle.isValid()){
                    const pat::Jet& sysobj = jetJERdownHandle->at(i);  
                    systJERdown[ic].add(sysobj.p4().pt(),
                                        sysobj.p4().eta(),
                                        sysobj.p4().phi(),
                                        sysobj.p4().energy());
                  }
/*
                  // JES
                  double uncUp = 0.0;
                  double uncDown = 0.0;
                  if (fJECUncertainty[ic] != nullptr) {
                    fJECUncertainty[ic]->setJetEta(obj.eta());
                    fJECUncertainty[ic]->setJetPt(obj.pt()); // here you must use the CORRECTED jet pt
                    uncUp = fJECUncertainty[ic]->getUncertainty(true);
                  }
                  systJESup[ic].add(obj.p4().pt()*(1.0+uncUp),
                                    obj.p4().eta(),
                                    obj.p4().phi(),
                                    obj.p4().energy()*(1.0+uncUp));
                  if (fJECUncertainty[ic] != nullptr) {
                    // Yes, one needs to set pt and eta again
                    fJECUncertainty[ic]->setJetEta(obj.eta());
                    fJECUncertainty[ic]->setJetPt(obj.pt()); // here you must use the CORRECTED jet pt
                    uncDown = fJECUncertainty[ic]->getUncertainty(false);
                  }
                  systJESdown[ic].add(obj.p4().pt()*(1.0-uncDown),
                                      obj.p4().eta(),
                                      obj.p4().phi(),
                                      obj.p4().energy()*(1.0-uncDown));
                  // JER
*/                
                }

		if (fillPFCands){
		  std::vector<const pat::PackedCandidate*> chargedPFCands;
		  std::unordered_map<const pat::PackedCandidate*, TrackInfoBuilder> trackInfoMap;

		  std::vector<double> _pfCand_pt;
		  std::vector<double> _pfCand_eta;
		  std::vector<double> _pfCand_phi;
		  std::vector<double> _pfCand_energy;
		  std::vector<double> _pfCand_hcalFraction;
		  std::vector<double> _pfCand_puppiWeight;
		  std::vector<int>    _pfCand_charge;
		  std::vector<int>    _pfCand_pdgId;
		  std::vector<int>    _pfCand_pvAssociationQuality;
		  std::vector<int>    _pfCand_lostInnerHits;
		  std::vector<double> _pfCand_dz;
		  std::vector<double> _pfCand_dxy;
		  std::vector<double> _pfCand_dzError;
		  std::vector<double> _pfCand_dxyError;
		  std::vector<double> _pfCand_vertexNormChi2;
		  std::vector<int>    _pfCand_qualityMask;
		  std::vector<double> _pfCand_dptdpt;
		  std::vector<double> _pfCand_detadeta;
		  std::vector<double> _pfCand_dphidphi;
		  std::vector<double> _pfCand_dxydxy;
		  std::vector<double> _pfCand_dzdz;
		  std::vector<double> _pfCand_dxydz;
		  std::vector<double> _pfCand_dphidxy;
		  std::vector<double> _pfCand_dlambdadz;
		  std::vector<double> _pfCand_minDRsv;
		  std::vector<double> _track_momentum;
		  std::vector<double> _track_eta;
		  std::vector<double> _track_etarel;
		  std::vector<double> _track_ptrel;
		  std::vector<double> _track_ppar;
		  std::vector<double> _track_deltar;
		  std::vector<double> _track_ptratio;
		  std::vector<double> _track_pparratio;
		  std::vector<double> _track_sip2dval;
		  std::vector<double> _track_sip2dsig;
		  std::vector<double> _track_sip3dval;
		  std::vector<double> _track_sip3dsig;
		  std::vector<double> _track_jetdistval;

		  for (unsigned int id = 0, nd = obj.numberOfDaughters(); id < nd; ++id)
		    {
		      const pat::PackedCandidate &dau = dynamic_cast<const pat::PackedCandidate &>(*obj.daughter(id));
		      if (dau.charge() != 0){
			chargedPFCands.push_back(&dau);
			trackInfoMap[&dau];
			trackInfoMap[&dau].compute(builder_, dau, obj, vertices->at(0));
		      }
		      _pfCand_pt.push_back(dau.p4().pt());
		      _pfCand_eta.push_back(dau.p4().eta());
		      _pfCand_phi.push_back(dau.p4().phi());
		      _pfCand_energy.push_back(dau.p4().energy());
		      _pfCand_hcalFraction.push_back(dau.hcalFraction());
		      _pfCand_puppiWeight.push_back(dau.puppiWeight());
		      _pfCand_charge.push_back(dau.charge());
		      _pfCand_pdgId.push_back(dau.pdgId());
		      _pfCand_pvAssociationQuality.push_back(dau.pvAssociationQuality());
		      _pfCand_lostInnerHits.push_back(dau.lostInnerHits());
		      _pfCand_dz.push_back(dau.dz());
		      _pfCand_dxy.push_back(dau.dxy());

		      double _minDR = 999.0;
		      for (const auto &sv : *SVs){
			double dr = reco::deltaR(dau, sv);
			if (dr < _minDR) _minDR = dr;
		      }

		      _pfCand_minDRsv.push_back(_minDR);

		      reco::Track::CovarianceMatrix bestTrkCov;
		      if (dau.bestTrack() != nullptr){
			bestTrkCov = dau.bestTrack()->covariance();

			_pfCand_dzError.push_back(dau.bestTrack()->dzError());
			_pfCand_dxyError.push_back(dau.bestTrack()->dxyError());
			_pfCand_vertexNormChi2.push_back( checkNan((dau.bestTrack()->chi2()) / (dau.bestTrack()->ndof())) );
			_pfCand_qualityMask.push_back( dau.bestTrack()->qualityMask() );
			_pfCand_dptdpt.push_back(bestTrkCov[0][0]);
			_pfCand_detadeta.push_back(bestTrkCov[1][1]);
			_pfCand_dphidphi.push_back(bestTrkCov[2][2]);
			_pfCand_dxydxy.push_back(bestTrkCov[3][3]);
			_pfCand_dzdz.push_back(bestTrkCov[4][4]);
			_pfCand_dxydz.push_back(bestTrkCov[3][4]);
			_pfCand_dphidxy.push_back(bestTrkCov[2][3]);
			_pfCand_dlambdadz.push_back(bestTrkCov[1][4]);
		      }
		    } // Loop over PF Candidates

		  // Sort by Sip2d significance                                                                                                                                                                   
		  std::sort(chargedPFCands.begin(), chargedPFCands.end(), [&](const pat::PackedCandidate *p1, const pat::PackedCandidate *p2){
		      return trackInfoMap.at(p1).getTrackSip2dSig() > trackInfoMap.at(p2).getTrackSip2dSig();
		    });

		  for (const auto *cpf : chargedPFCands){
		    const auto &trkinfo = trackInfoMap.at(cpf);
		    _track_momentum.push_back(trkinfo.getTrackMomentum());
		    _track_eta.push_back(trkinfo.getTrackEta());
		    _track_etarel.push_back(trkinfo.getTrackEtaRel());
		    _track_ptrel.push_back(trkinfo.getTrackPtRel());
		    _track_ppar.push_back(trkinfo.getTrackPPar());
		    _track_deltar.push_back(trkinfo.getTrackDeltaR());
		    _track_ptratio.push_back(trkinfo.getTrackPtRatio());
		    _track_pparratio.push_back(trkinfo.getTrackPParRatio());
		    _track_sip2dval.push_back(trkinfo.getTrackSip2dVal());
		    _track_sip2dsig.push_back(trkinfo.getTrackSip2dSig());
		    _track_sip3dval.push_back(trkinfo.getTrackSip3dVal());
		    _track_sip3dsig.push_back(trkinfo.getTrackSip3dSig());
		    _track_jetdistval.push_back(trkinfo.getTrackJetDistVal());
		  }
		  
		  pfCand_pt[ic].push_back(_pfCand_pt);
		  pfCand_eta[ic].push_back(_pfCand_eta);
		  pfCand_phi[ic].push_back(_pfCand_phi);
		  pfCand_energy[ic].push_back(_pfCand_energy);
		  pfCand_hcalFraction[ic].push_back(_pfCand_hcalFraction);
		  pfCand_puppiWeight[ic].push_back(_pfCand_puppiWeight);
		  pfCand_charge[ic].push_back(_pfCand_charge);
		  pfCand_pdgId[ic].push_back(_pfCand_pdgId);
		  pfCand_pvAssociationQuality[ic].push_back(_pfCand_pvAssociationQuality);
		  pfCand_lostInnerHits[ic].push_back(_pfCand_lostInnerHits);
		  pfCand_dz[ic].push_back(_pfCand_dz);
		  pfCand_dxy[ic].push_back(_pfCand_dxy);
		  pfCand_dzError[ic].push_back(_pfCand_dzError);
		  pfCand_dxyError[ic].push_back(_pfCand_dxyError);
		  pfCand_vertexNormChi2[ic].push_back(_pfCand_vertexNormChi2);
		  pfCand_qualityMask[ic].push_back(_pfCand_qualityMask);
		  pfCand_dptdpt[ic].push_back(_pfCand_dptdpt);
		  pfCand_detadeta[ic].push_back(_pfCand_detadeta);
		  pfCand_dphidphi[ic].push_back(_pfCand_dphidphi);
		  pfCand_dxydxy[ic].push_back(_pfCand_dxydxy);
		  pfCand_dzdz[ic].push_back(_pfCand_dzdz);
		  pfCand_dxydz[ic].push_back(_pfCand_dxydz);
		  pfCand_dphidxy[ic].push_back(_pfCand_dphidxy);
		  pfCand_dlambdadz[ic].push_back(_pfCand_dlambdadz);
		  pfCand_minDRsv[ic].push_back(_pfCand_minDRsv);
		  track_momentum[ic].push_back(_track_momentum);
		  track_eta[ic].push_back(_track_eta);
		  track_etarel[ic].push_back(_track_etarel);
		  track_ptrel[ic].push_back(_track_ptrel);
		  track_ppar[ic].push_back(_track_ppar);
		  track_deltar[ic].push_back(_track_deltar);
		  track_ptratio[ic].push_back(_track_ptratio);
		  track_pparratio[ic].push_back(_track_pparratio);
		  track_sip2dval[ic].push_back(_track_sip2dval);
		  track_sip2dsig[ic].push_back(_track_sip2dsig);
		  track_sip3dval[ic].push_back(_track_sip3dval);
		  track_sip3dsig[ic].push_back(_track_sip3dsig);
		  track_jetdistval[ic].push_back(_track_jetdistval);
		}
		
            }
        }
    }
    return filter();
}

void JetDumper::reset(){

    for(size_t ic = 0; ic < inputCollections.size(); ++ic){
	pt[ic].clear();
	eta[ic].clear();
	phi[ic].clear();
	e[ic].clear();
//        p4[ic].clear();
        pdgId[ic].clear();
	hadronFlavour[ic].clear();
	partonFlavour[ic].clear();

        jetIDloose[ic].clear();
        jetIDtight[ic].clear();
        jetIDtightLeptonVeto[ic].clear();

        jetPUIDloose[ic].clear();
	jetPUIDmedium[ic].clear();
	jetPUIDtight[ic].clear();
        
        originatesFromW[ic].clear();
        originatesFromZ[ic].clear();
        originatesFromTop[ic].clear();
        originatesFromChargedHiggs[ic].clear();
        originatesFromUnknown[ic].clear();
        
        MCjet[ic].reset();
        // Systematics
	if(systVariations){
          systJESup[ic].reset();
          systJESdown[ic].reset();
          systJERup[ic].reset();
          systJERdown[ic].reset();
	}

	axis1[ic].clear();
        axis2[ic].clear();
        ptD[ic].clear();
        mult[ic].clear();
	pullRap[ic].clear();
	pullPhi[ic].clear();
	charge[ic].clear();
	
	if (fillPFCands)
          {
            pfCand_pt[ic].clear();
            pfCand_eta[ic].clear();
            pfCand_phi[ic].clear();
            pfCand_energy[ic].clear();
            pfCand_hcalFraction[ic].clear();
            pfCand_puppiWeight[ic].clear();
            pfCand_charge[ic].clear();
            pfCand_pdgId[ic].clear();
            pfCand_pvAssociationQuality[ic].clear();
            pfCand_lostInnerHits[ic].clear();
            pfCand_dz[ic].clear();
            pfCand_dxy[ic].clear();
            pfCand_dzError[ic].clear();
            pfCand_dxyError[ic].clear();
            pfCand_vertexNormChi2[ic].clear();
            pfCand_qualityMask[ic].clear();
            pfCand_dptdpt[ic].clear();
            pfCand_detadeta[ic].clear();
            pfCand_dphidphi[ic].clear();
            pfCand_dxydxy[ic].clear();
            pfCand_dzdz[ic].clear();
            pfCand_dxydz[ic].clear();
            pfCand_dphidxy[ic].clear();
            pfCand_dlambdadz[ic].clear();
            pfCand_minDRsv[ic].clear();
            track_momentum[ic].clear();
            track_eta[ic].clear();
            track_etarel[ic].clear();
            track_ptrel[ic].clear();
            track_ppar[ic].clear();
            track_deltar[ic].clear();
            track_ptratio[ic].clear();
            track_pparratio[ic].clear();
            track_sip2dval[ic].clear();
	    track_sip2dsig[ic].clear();
            track_sip3dval[ic].clear();
            track_sip3dsig[ic].clear();
            track_jetdistval[ic].clear();
          }
    }
    for(size_t ic = 0; ic < inputCollections.size()*nDiscriminators; ++ic){
        discriminators[ic].clear();
    }
    for(size_t ic = 0; ic < inputCollections.size()*nUserfloats; ++ic){
        userfloats[ic].clear();
    }
    for(size_t ic = 0; ic < inputCollections.size()*nUserints; ++ic){
      userints[ic].clear();
    }
}

bool JetDumper::passJetID(int id, const pat::Jet& jet) {
  // Recipy taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID (read on 14.08.2015)
  // Recipy taken from https://twiki.cern.ch/twiki/bin/view/CMS/JetID13TeVRun2016 (28.3.2018)
  double eta = fabs(jet.eta());
  if (eta < 2.7) {
    // PF Jet ID       Loose   Tight   TightLepVeto
    // Neutral Hadron Fraction < 0.99  < 0.90  < 0.90
    // Neutral EM Fraction     < 0.99  < 0.90  < 0.90
    // Number of Constituents  > 1     > 1     > 1
    // Muon Fraction           -       -       < 0.8
    int nConstituents = jet.chargedMultiplicity() + jet.electronMultiplicity()
      + jet.muonMultiplicity() + jet.neutralMultiplicity();
    if (id == kJetIDLoose) {
      if (!(jet.neutralHadronEnergyFraction() < 0.99)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.99)) return false;
      if (!(nConstituents                     > 1   )) return false;
    } else if (id == kJetIDTight) {
      if (!(jet.neutralHadronEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.90)) return false;
      if (!(nConstituents                     > 1   )) return false;      
    } else if (id == kJetIDTightLepVeto) {
      if (!(jet.neutralHadronEnergyFraction() < 0.90)) return false;
      if (!(jet.neutralEmEnergyFraction()     < 0.90)) return false;
      if (!(nConstituents                     > 1   )) return false;      
      if (!(jet.muonEnergyFraction()          < 0.80)) return false;
    }

    if (eta < 2.4) {
      if (id == kJetIDLoose) {
        if (!(jet.chargedHadronEnergyFraction() > 0.))   return false;
        if (!(jet.chargedMultiplicity()         > 0))    return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.99)) return false;
      } else if (id == kJetIDTight) {
        if (!(jet.chargedHadronEnergyFraction() > 0.))   return false;
        if (!(jet.chargedMultiplicity()         > 0))    return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.99)) return false;
      } else if (id == kJetIDTightLepVeto) {
        if (!(jet.chargedHadronEnergyFraction() > 0.))   return false;
        if (!(jet.chargedMultiplicity()         > 0))    return false;
        if (!(jet.chargedEmEnergyFraction()     < 0.90)) return false;
      }

    }

  } else {
    if (eta < 3.0) {
      if (id == kJetIDLoose) {
        if (!(jet.neutralEmEnergyFraction()     > 0.01)) return false;
        if (!(jet.neutralHadronEnergyFraction() < 0.98)) return false;
        if (!(jet.neutralMultiplicity()         > 2))    return false;
      } else {
        if (!(jet.neutralEmEnergyFraction()     > 0.01)) return false;
        if (!(jet.neutralHadronEnergyFraction() < 0.98)) return false;
        if (!(jet.neutralMultiplicity()         > 2))    return false;
      }
    }else{
      //     PF Jet ID                   Loose   Tight
      //     Neutral EM Fraction         < 0.90  < 0.90
      //     Number of Neutral Particles > 10    >10 
      if (id == kJetIDLoose) {
        if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
        if (!(jet.neutralMultiplicity()     > 10  )) return false;    
      } else {
        if (!(jet.neutralEmEnergyFraction() < 0.90)) return false;
        if (!(jet.neutralMultiplicity()     > 10  )) return false;    
      }
    } 
  }
  return true;
}


