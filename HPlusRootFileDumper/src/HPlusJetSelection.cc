#include "HiggsAnalysis/HPlusRootFileDumper/interface/HPlusJetSelection.h"

#include <iostream>
#include <string>
#include <vector>

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/EgammaCandidates/interface/ElectronFwd.h"
#include "DataFormats/EgammaCandidates/interface/Electron.h"

#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "DataFormats/Common/interface/Handle.h"
#include <vector>
#include <algorithm>

namespace HPlusAnalysis {
  
  HPlusJetSelection::HPlusJetSelection(const edm::ParameterSet& iConfig) : 
    HPlusAnalysis::HPlusAnalysisBase("JetSelection"),
    HPlusAnalysis::HPlusSelectionBase(iConfig) {
    // Parse the list of triggers in the config file
    if (iConfig.exists("JetCollectionName")) {
      fJetCollectionName = iConfig.getParameter<edm::InputTag>("JetCollectionName");
    } else {
      throw cms::Exception("Configuration") << "JetSelection: InputTag 'JetCollectionName' is missing in config!" << std::endl;
    }
    if (iConfig.exists("CutMinNJets")) {
      fCutMinNJets = iConfig.getParameter<double>("CutMinNJets");
    } else {
      throw cms::Exception("Configuration") << "JetSelection: int value 'CutMinNJets' is missing in config!" << std::endl;
    }
    if (iConfig.exists("CutMinJetEt")) {
      fCutMinJetEt = iConfig.getParameter<double>("CutMinJetEt");
    } else {
      throw cms::Exception("Configuration") << "JetSelection: double value 'CutMinJetEt' is missing in config!" << std::endl;
    }
    if (iConfig.exists("CutMaxAbsJetEta")) {
      fCutMaxAbsJetEta = iConfig.getParameter<double>("CutMaxAbsJetEta");
    } else {
      throw cms::Exception("Configuration") << "JetSelection: double value 'CutMaxAbsJetEta' is missing in config!" << std::endl;
    }
    if (iConfig.exists("CutMaxEMFraction")) {
      fCutMaxEMFraction = iConfig.getParameter<double>("CutMaxEMFraction");
    } else {
      throw cms::Exception("Configuration") << "JetSelection: double value 'CutMaxEMFraction' is missing in config!" << std::endl;
    }
    // Initialize counters
    fCounterTest = fCounter->addCounter("TestCounter");
    fCounterJetsPriorSelection = fCounter->addCounter("All Jets");
    fCounterJetsPostSelection  = fCounter->addCounter("Selected Jets");
    fCounterJetCollectionHandleEmpty = fCounter->addCounter("Empty Jet Handle");
    fCounterError = fCounter->addCounter("Random Errors");

    std::string alias;
    // Declare produced items (class-specific):  Max Jet Et 
    produces<float>(alias = "JetSelectionMaxJetEt").setBranchAlias(alias);
  
  } //eof: HPlusAnalysis::HPlusSelectionBase(iConfig) {

  HPlusJetSelection::~HPlusJetSelection() {}
  
  void HPlusJetSelection::beginJob() {
    // Set histograms
    if (isHistogrammed()) {
      hLeadJetMaxEt = fFileService->make<TH1F>("LdgJetEt", "LdgJet Highest E_{T}",  100, 0., 200.);
    }
  }
  
  void HPlusJetSelection::endJob() {
    
  }
  

  bool HPlusJetSelection::filter(edm::Event& iEvent, const edm::EventSetup& iSetup) {
    
    bool decision = false; // filter decision true iff at least NJets survive the selection criteria.
    fCounter->addCount(fCounterTest);
    
    // ************************************************************************************************
    // FIXME: Do this for ALL data to be stored
    // std::auto_ptr<float> myHighestJetEt(new float); // highest pt of jet that has passed all criteria
    // ************************************************************************************************
    
    // Get JetCollection handle
    edm::Handle<reco::CaloJetCollection> myCaloJets;       // create an empty handle 
    iEvent.getByLabel(fJetCollectionName, myCaloJets);     // attach handle to JetCollection
    if (!myCaloJets->size()) {
      edm::LogInfo("HPlus") << "Jet handle is empty!" << std::endl;
      fCounter->addCount(fCounterJetCollectionHandleEmpty);
    return decision;
    }
    const size_t myJetCount = myCaloJets->size();
    
    // Initialisation of variables (move to header)
    std::vector<reco::CaloJet> myUnsortedJets;
    std::vector<reco::CaloJet> mySortedJets;
    std::vector<reco::CaloJet> myFilteredJets;


    // Step 1) Store all jets in a vector
    for (size_t i = 0; i < myJetCount; ++i) {
      const reco::CaloJet & myJet = (*myCaloJets)[i];
      myUnsortedJets.push_back(myJet);
      // Reference counter. Count total number of jets prior any selection in each Event.
      fCounter->addCount(fCounterJetsPriorSelection);
    }
    
//     // Loop over JetCollection
//     for (std::vector<reco::CaloJet>::const_iterator iJet = myUnsortedJets.begin(); iJet != myUnsortedJets.end(); iJet++) {
//       // Reference counter. Count total number of jets prior any selection in each Event.
//       fCounter->addCount(fCounterJetsPriorSelection);      
//     }

    // Step 2) Order Jets according to Jet Energy
    const size_t myUnsortedJetsSize = myUnsortedJets.size();
    // Call a function to take an unsorted caloJet vector and sort it according to caloJet-Energies
    if(myUnsortedJetsSize!=0){mySortedJets = sortCaloJets(myUnsortedJets, myUnsortedJetsSize);}
    const size_t mySortJetsSize = mySortedJets.size();
    
    // Step 3) Filter the now ordered jets: Apply Jet Et, Eta and EMFraction Cuts
    // Calling filtering function..
    if(mySortJetsSize==myUnsortedJetsSize){ myFilteredJets = filterCaloJets(mySortedJets, mySortJetsSize); }
    else{
      edm::LogInfo("HPlus") << "Jet handle is empty!" << std::endl;
      fCounter->addCount(fCounterError);
    }

    // Step 4) Now analyze the filtered jets.
    const size_t myFilteredJetsSize = myFilteredJets.size();
      if(myFilteredJetsSize!=0){
	// Change function decision to true
	decision = true;  // remember: if fCutMinNJets is NOT satisfied, then then "myFilteredJets" vector is returned empty!
	// Create a vector iterator for the filtered jets
	std::vector<reco::CaloJet>::const_iterator iFilteredJet;
	// Loop over all the filtered jets
	for(iFilteredJet =  myFilteredJets.begin(); iFilteredJet != myFilteredJets.end(); iFilteredJet++){
	  // Count total number of jets prio any selection in each Event.
	  fCounter->addCount(fCounterJetsPostSelection);
	  std::cout << "(*iFilteredJet).energy()= " << (*iFilteredJet).energy() << std::endl;
	}
      }
      else{ 
	//std::cout << "*** WARNING:  myFilteredJetsSize == 0 ***" << std::endl; 
      }
      
      return decision;
      
  }//eof:  HPlusJetSelection::analyze()
  
  std::vector<reco::CaloJet> HPlusJetSelection::sortCaloJets(std::vector<reco::CaloJet> caloJetsToSort, const size_t caloJetSize) {
    
    // Declare variables
    reco::CaloJet myTmpLdgJet;
    reco::CaloJet myTmpLdgJet_new;
    std::vector<reco::CaloJet> caloJetsSorted;
    std::vector<reco::CaloJet>::iterator myJet;
    
    // Store the "first" N jets [wrt energy). 
    for ( size_t i = 0; i < caloJetSize; i++) {
      for ( myJet = caloJetsToSort.begin(); myJet != caloJetsToSort.end(); ++myJet) {
	
	if( (*myJet).energy() > myTmpLdgJet.energy() ){
	  myTmpLdgJet = (*myJet);

	}
	else{}
      }
      // Store myJet as ith-LdgJet (descending order in Energy)
      caloJetsSorted.push_back(myTmpLdgJet);
      // Delete myJet from vector list
      caloJetsToSort = eraseVectorElement(caloJetsToSort, myTmpLdgJet);
      myTmpLdgJet = myTmpLdgJet_new;
    }//eof: for ( size_t i = 0; i < caloJetsToSort.size(); i++) {
    
    // Cout the sorted jet energies
    // for ( myJet = caloJetsSorted.begin(); myJet != caloJetsSorted.end(); ++myJet) {
    //   std::cout << "(*myJetSorted).energy() = " << (*myJet).energy() << std::endl;
    // }

    return caloJetsSorted;
    
  }//eof: HPlusJetSelection::sortCaloJets()

  std::vector<reco::CaloJet> HPlusJetSelection::filterCaloJets(std::vector<reco::CaloJet> caloJetsSorted, const size_t caloJetSize) {
    
    // Declare variables
    reco::CaloJet myJet;
    std::vector<reco::CaloJet> caloJetsFilteredCands;
    std::vector<reco::CaloJet> caloJetsFiltered;
    std::vector<reco::CaloJet>::iterator it_caloJetsFilteredCands;
    std::vector<reco::CaloJet>::iterator it_caloJetsFiltered;
    bool passedNJets      = false;
    bool passedJetEt      = false;
    bool passedJetEta     = false;
    bool passedEMFraction = false;  
    
    if(caloJetSize >= fCutMinNJets){
    
      std::cout << "---> Looping over filtered jets <--- " << std::endl;
      // Loop over sorted Jets and apply quality cuts
      for( it_caloJetsFilteredCands = caloJetsSorted.begin(); it_caloJetsFilteredCands != caloJetsSorted.end(); ++it_caloJetsFilteredCands) {
	
	if( (*it_caloJetsFilteredCands).energy() >= fCutMinJetEt){ passedJetEt = true;}
	if( fabs((*it_caloJetsFilteredCands).eta()) <= fCutMaxAbsJetEta){ passedJetEta = true;}
	if( (*it_caloJetsFilteredCands).emEnergyFraction() >= fCutMaxEMFraction ){ passedEMFraction = true;}
	
	// Boolean will be used to erase those jets that do not satisfy criteria
	bool jetSurvives = ( passedJetEt && passedJetEta && passedEMFraction) ;
	if(!jetSurvives){ 
	  // std::cout << "Jet did not survive " << std::endl;
	} 
	else{caloJetsFilteredCands.push_back(*it_caloJetsFilteredCands);}
					
      }
      const double myFilteredJetsSize = caloJetsFilteredCands.size();
      if( myFilteredJetsSize >= fCutMinNJets  ){ passedNJets = true;}
    }
    else{
      std::cout << "*** WARNING: caloJetSize < fCutMinNJets ***" << std::endl;
    }

    // Last criterion: Is the number of jets enough? If not return an empty vector
    if(passedNJets){ caloJetsFiltered = caloJetsFilteredCands; }
    else{
      // return an empty vector!
    }
    
    return caloJetsFiltered;
    
  }//eof: HPlusJetSelection::filterCaloJets


  std::vector<reco::CaloJet> HPlusJetSelection::eraseVectorElement( std::vector<reco::CaloJet> myJetVector, reco::CaloJet test) {

    std::vector<reco::CaloJet>::iterator it;
    int counter = 0;
    //  bool success = false;

    for ( it = myJetVector.begin(); it!=myJetVector.end(); ++it) {

      if( (*it).energy() == test.energy() ){
	
	// std::cout << " Found match. Deleting vector with (*it).energy() = " << (*it).energy()  << std::endl;
	myJetVector.erase(myJetVector.begin()+counter);
	//	success = true;
	break;
      } else{counter++;}
    }

      return myJetVector;
  }//eof: HPlusJetSelection::eraseVectorElement(
  
  /////////
  DEFINE_FWK_MODULE(HPlusJetSelection); 
  
}//eof: namespace HPlusAnalysis {


