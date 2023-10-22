#ifndef ZeroBias_Timing_H
#define ZeroBias_Timing_H

#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <TNtuple.h>
#include <TString.h>
#include <bitset>
#include "TH1F.h"
#include "TH1.h"


#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/Frameworkfwd.h>
#include <FWCore/Framework/interface/Event.h>
#include <FWCore/Framework/interface/ESHandle.h>
#include <FWCore/Utilities/interface/InputTag.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include <DataFormats/PatCandidates/interface/Tau.h>
#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/MET.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "DataFormats/L1Trigger/interface/Tau.h"
#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/L1Trigger/interface/Muon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/L1TGlobal/interface/GlobalAlgBlk.h"

#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/EDMException.h"


/*
  ██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
  ██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
  ██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
  ██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class ZeroBias_Timing : public edm::one::EDAnalyzer<edm::one::WatchRuns, edm::one::SharedResources> {
public:
  /// Constructor
  explicit ZeroBias_Timing(const edm::ParameterSet&);
  /// Destructor
  virtual ~ZeroBias_Timing();

private:
  //----edm control---
  virtual void beginJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob();
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual bool GetMETFilterDecision(const edm::Event& iEvent, edm::Handle<edm::TriggerResults> METFilterResults, TString studiedfilter);
  void Initialize();

 // TTree *_tree;
  TTree *_tree2;
  TTree *_tree3;
  TTree *_tree4;
  TTree *_tree5;

  std::string _treeName;

  // -------------------------------------
  // variables to be filled in output tree

///// variables to be filled in the second/third/fourth trees
ULong64_t _indexevents2;
  Int_t     _runNumber2;
  Int_t     _lumi2;

ULong64_t _indexevents3;
  Int_t     _runNumber3;
  Int_t     _lumi3;

ULong64_t _indexevents4;
  Int_t     _runNumber4;
  Int_t     _lumi4;

ULong64_t _indexevents5;
  Int_t     _runNumber5;
  Int_t     _lumi5;


  float _tauPt2;
  float _tauEta2;
  float _tauPhi2;
  float _l1tTauPt2;
  float _l1tTauEta2;
  float _l1tTauPhi2;
  Int_t   _l1tTauQual2;
  Int_t   _l1tTauIso2;
  Int_t   _l1tTauIsMatched2;
  Int_t _l1tTauBx2;
  Int_t _IsUnpref_Tau2;
  std::vector<int> _bit_tau{506};


  float _jetPt2;
  float _jetEta2;
  float _jetPhi2;
  float _l1tJetPt2;
  float _l1tJetEta2;
  float _l1tJetPhi2;
  Int_t  _l1tJetQual2;
  Int_t   _l1tJetIso2;
  Int_t  _l1tJetIsMatched2;
  Int_t    _l1tJetBx2;
  Int_t _IsUnpref_Jet2;
  std::vector<int> _bit_jet{506};

  float _metEt2;
  float _metPhi2;

  Int_t _l1tSumType2;
  float    _l1tSumEt2;
  float     _l1tSumPhi2;
  float   _l1tSumIEt2;
  float    _l1tSumIPhi2;

  float _egPt2;
  float _egEta2;
  float _egPhi2;
  Int_t   _egIsTight2;
  Int_t  _egIsMedium2;
  Int_t  _egIsLoose2;
  float  _l1tEgPt2;
  float  _l1tEgEta2;
  float  _l1tEgPhi2;
  Int_t   _l1tEgIso2;
  Int_t   _l1tEgQual2;
  Int_t   _l1tEgIsMatched2;
  Int_t    _l1tEgBx2;
  Int_t _IsUnpref_Eg2;
  std::vector<int> _bit_eg{506};


  float _muPt2;
  float _muEta2;
  float _muPhi2;
  float _l1tMuPt2;
  float _l1tMuEta2;
  float _l1tMuPhi2;
  Int_t   _l1tMuQual2;
  Int_t  _l1tMuIsMatched2;
  Int_t    _l1tMuBx2;
  Int_t _IsUnpref_Mu2;
  std::vector<int> _bit_mu{506};


//// histos to be filled in the output
  TH1F* _muBxMatched_g20  = new TH1F("muBxMatched_g20",  "muBxMatched_g20",  5, -2.5, 2.5);
  TH1F* _muBxMatched_8_25  = new TH1F("muBxMatched_8_25",  "muBxMatched_8_25",  5, -2.5, 2.5);
  TH1F* _egBxMatched  = new TH1F("egBxMatched",  "egBxMatched",  5, -2.5, 2.5);
  TH1F* _tauBxMatched = new TH1F("tauBxMatched", "tauBxMatched", 5, -2.5, 2.5);
  TH1F* _jetBxMatched = new TH1F("jetBxMatched", "jetBxMatched", 5, -2.5, 2.5);
  //TH2F* _muBxMatched_eta_phi = new TH2F("muBxMatched_eta_phi","muBxMatched_eta_phi", 100, -5 , 5, 72,-3.1416,3.1416);
  TH1F* _egBx0Matched_eta = new TH1F("egBx0Matched_eta","egBx0Matched_eta", 100, -5 , 5);
  TH1F* _egBxMin1Matched_eta = new TH1F("egBxMin1Matched_eta","egBxMin1Matched_eta", 100, -5 , 5);
  TH1F* _egBxPlus1Matched_eta = new TH1F("egBxPlus1Matched_eta","egBxPlus1Matched_eta", 100, -5 , 5);
  //TH2F* _tauBxMatched_eta_phi = new TH2F("tauBxMatched_eta_phi","tauBxMatched_eta_phi", 100, -5 , 5, 72,-3.1416,3.1416);
  //TH2F* _jetBxMatched_eta_phi = new TH2F("jetBxMatched_eta_phi","jetBxMatched_eta_phi", 100, -5 , 5, 72,-3.1416,3.1416);

  edm::EDGetTokenT<GlobalAlgBlkBxCollection> _ugtTag;

  edm::EDGetTokenT<GlobalExtBlkBxCollection> _UnprefirableEventToken;

  edm::EDGetTokenT<l1t::MuonBxCollection>   _L1MuTag;
  edm::EDGetTokenT<l1t::EGammaBxCollection> _L1EGTag;
  edm::EDGetTokenT<l1t::TauBxCollection>    _L1TauTag;
  edm::EDGetTokenT<l1t::JetBxCollection>    _l1tJetTag;
  edm::EDGetTokenT<l1t::EtSumBxCollection>  _l1tSumTag;
  
  edm::EDGetTokenT<pat::MuonRefVector>            _muTag;
  edm::EDGetTokenT<edm::View<reco::GsfElectron> > _eleTag;
  edm::EDGetTokenT<pat::TauRefVector>             _tauTag;
  edm::EDGetTokenT<edm::View<pat::Jet>>           _jetTag;
  edm::EDGetTokenT<pat::METCollection>            _metTag;

  edm::EDGetTokenT<edm::ValueMap<bool>> _eleTightIdTag;
  edm::EDGetTokenT<edm::ValueMap<bool>> _eleMediumIdTag;
  edm::EDGetTokenT<edm::ValueMap<bool>> _eleLooseIdTag;

  edm::EDGetTokenT<edm::TriggerResults> metFiltersPatTag_;
  edm::EDGetTokenT<edm::TriggerResults> metFiltersRecoTag_;

 bool Flag_IsUnprefirable;

Int_t counter_unprefEvents=0;
};

/*
  ██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
  ██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
  ██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
  ██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
  ██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
ZeroBias_Timing::ZeroBias_Timing(const edm::ParameterSet& iConfig) :
  _ugtTag    (consumes<GlobalAlgBlkBxCollection>     (iConfig.getParameter<edm::InputTag>("l1uGT"))),

  _UnprefirableEventToken(consumes<GlobalExtBlkBxCollection>(edm::InputTag("simGtExtUnprefireable"))),
  
  _L1MuTag   (consumes<l1t::MuonBxCollection>        (iConfig.getParameter<edm::InputTag>("l1Mu"))),
  _L1EGTag   (consumes<l1t::EGammaBxCollection>      (iConfig.getParameter<edm::InputTag>("l1EG"))),
  _L1TauTag  (consumes<l1t::TauBxCollection>         (iConfig.getParameter<edm::InputTag>("l1Tau"))),
  _l1tJetTag (consumes<l1t::JetBxCollection>         (iConfig.getParameter<edm::InputTag>("l1Jet"))),
  _l1tSumTag (consumes<l1t::EtSumBxCollection>       (iConfig.getParameter<edm::InputTag>("l1Sum"))),
  
  _muTag     (consumes<pat::MuonRefVector>           (iConfig.getParameter<edm::InputTag>("mu"))),
  _eleTag    (consumes<edm::View<reco::GsfElectron>> (iConfig.getParameter<edm::InputTag>("eG"))),
  _tauTag    (consumes<pat::TauRefVector>            (iConfig.getParameter<edm::InputTag>("tau"))),
  _jetTag    (consumes<edm::View<pat::Jet>>          (iConfig.getParameter<edm::InputTag>("jet"))),
  _metTag    (consumes<pat::METCollection>           (iConfig.getParameter<edm::InputTag>("sum"))),

  _eleTightIdTag  (consumes<edm::ValueMap<bool>>     (iConfig.getParameter<edm::InputTag>("eleTightId"))),
  _eleMediumIdTag (consumes<edm::ValueMap<bool>>     (iConfig.getParameter<edm::InputTag>("eleMediumId"))),
  _eleLooseIdTag  (consumes<edm::ValueMap<bool>>     (iConfig.getParameter<edm::InputTag>("eleLooseId"))), 

  metFiltersPatTag_  (consumes<edm::TriggerResults>       (iConfig.getParameter<edm::InputTag>("METFiltersPAT"))),
  metFiltersRecoTag_ (consumes<edm::TriggerResults>       (iConfig.getParameter<edm::InputTag>("METFiltersRECO")))
{
  usesResource("TFileService");
  this -> _treeName = iConfig.getParameter<std::string>("treeName");
  this -> Initialize();
  return;
}

ZeroBias_Timing::~ZeroBias_Timing()
{}

void ZeroBias_Timing::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{}

void ZeroBias_Timing::Initialize()
{
  //second/third/fourth/fifth tree (L1BX)
  this -> _indexevents2 = 0;
  this -> _runNumber2   = 0;
  this -> _lumi2        = 0;

  this -> _indexevents3 = 0;
  this -> _runNumber3   = 0;
  this -> _lumi3        = 0;

  this -> _indexevents4 = 0;
  this -> _runNumber4   = 0;
  this -> _lumi4        = 0;

  this -> _indexevents5 = 0;
  this -> _runNumber5   = 0;
  this -> _lumi5        = 0;

  this -> _jetPt2  = 0;
  this -> _jetEta2 = 0;
  this -> _jetPhi2 = 0;
  this -> _l1tJetPt2        = 0;
  this -> _l1tJetEta2      = 0;
  this -> _l1tJetPhi2       = 0;
  this -> _l1tJetQual2   = 0;
  this -> _l1tJetIso2     = 0;
  this -> _l1tJetIsMatched2 = 0;
  this -> _IsUnpref_Jet2 =0;
  this -> _bit_jet . clear();


  this -> _metEt2  = -1.;
  this -> _metPhi2 = -1.;
  this -> _l1tSumType2= 0;
  this -> _l1tSumEt2= 0;
  this -> _l1tSumPhi2= 0;
  this -> _l1tSumIEt2= 0;
  this -> _l1tSumIPhi2= 0;

  this -> _egPt2       = 0;
  this -> _egEta2     = 0;
  this -> _egPhi2     = 0;
  this -> _egIsTight2  = 0;
  this -> _egIsMedium2 = 0;
  this -> _egIsLoose2  = 0;
  this -> _l1tEgPt2       = 0;
  this -> _l1tEgEta2     = 0;
  this -> _l1tEgPhi2       = 0;
  this -> _l1tEgQual2    = 0;
  this -> _l1tEgIso2   = 0;
  this -> _l1tEgIsMatched2 = 0;
  this -> _l1tEgBx2        = 0;
  this -> _IsUnpref_Eg2 =0;
  this -> _bit_eg . clear();


  this -> _muPt2  = 0;
  this -> _muEta2 = 0;
  this -> _muPhi2 = 0;
  this -> _l1tMuPt2        = 0;
  this -> _l1tMuEta2     = 0;
  this -> _l1tMuPhi2       = 0;
  this -> _l1tMuQual2      = 0;
  this -> _l1tMuIsMatched2 = 0;
  this -> _l1tMuBx2 = 0;
  this -> _IsUnpref_Mu2 =0;
  this -> _bit_mu . clear();


  this -> _tauPt2  = 0;
  this -> _tauEta2 = 0;
  this -> _tauPhi2 = 0;
  this -> _l1tTauPt2        = 0;
  this -> _l1tTauEta2     = 0;
  this -> _l1tTauPhi2       = 0;
  this -> _l1tTauQual2      = 0;
  this -> _l1tTauIsMatched2 = 0;
  this -> _l1tTauBx2 = 0;
  this -> _IsUnpref_Tau2 =0;
  this -> _bit_tau . clear();

}


void ZeroBias_Timing::beginJob()
{
  edm::Service<TFileService> fs;
  //this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());
  this -> _tree2 = fs -> make<TTree>("EG","EG");
  this -> _tree3 = fs -> make<TTree>("Mu","Mu");
  this -> _tree4 = fs -> make<TTree>("Jet","Jet");
  this -> _tree5 = fs -> make<TTree>("Tau","Tau");
 


  //Branches of first tree (ZeroBias_Timing)
  /*
  this -> _tree -> Branch("EventNumber",  &_indexevents);
  this -> _tree -> Branch("RunNumber",  &_runNumber);
  this -> _tree -> Branch("lumi",  &_lumi);

  this -> _tree -> Branch("bit21",  &_bit21);
  this -> _tree -> Branch("bit25",  &_bit25);
  this -> _tree -> Branch("bit168", &_bit168);
  this -> _tree -> Branch("bit169", &_bit169);
  this -> _tree -> Branch("bit170", &_bit170);
  this -> _tree -> Branch("bit171", &_bit171);
  this -> _tree -> Branch("bit172", &_bit172);
  this -> _tree -> Branch("bit178", &_bit178);
  this -> _tree -> Branch("bit192", &_bit192);
  this -> _tree -> Branch("bit194", &_bit194);
  this -> _tree -> Branch("bit196", &_bit196);
  this -> _tree -> Branch("bit218", &_bit218);
  this -> _tree -> Branch("bit219", &_bit219);
  this -> _tree -> Branch("bit220", &_bit220);
  this -> _tree -> Branch("bit262", &_bit262);
  this -> _tree -> Branch("bit263", &_bit263);
  this -> _tree -> Branch("bit264", &_bit264);
  this -> _tree -> Branch("bit267", &_bit267);
  this -> _tree -> Branch("bit270", &_bit270);
  this -> _tree -> Branch("bit271", &_bit271);
  this -> _tree -> Branch("bit272", &_bit272);
  this -> _tree -> Branch("bit273", &_bit273);
  this -> _tree -> Branch("bit309", &_bit309);
  this -> _tree -> Branch("bit310", &_bit310);
  this -> _tree -> Branch("bit398", &_bit398);
  this -> _tree -> Branch("bit418", &_bit418);
  this -> _tree -> Branch("bit420", &_bit420);
  this -> _tree -> Branch("bit459", &_bit459);
  this -> _tree -> Branch("bit478", &_bit478);
  this -> _tree -> Branch("bit479", &_bit479);
  this -> _tree -> Branch("bit480", &_bit480);

  this -> _tree -> Branch("tauPt",  &_tauPt);
  this -> _tree -> Branch("tauEta", &_tauEta);
  this -> _tree -> Branch("tauPhi", &_tauPhi);

  this -> _tree -> Branch("l1tTauPt",  &_l1tTauPt);
  this -> _tree -> Branch("l1tTauEta", &_l1tTauEta);
  this -> _tree -> Branch("l1tTauPhi", &_l1tTauPhi);
  this -> _tree -> Branch("l1tTauQual", &_l1tTauQual);
  this -> _tree -> Branch("l1tTauIso", &_l1tTauIso);
  this -> _tree -> Branch("l1tTauIsMatched", &_l1tTauIsMatched);

  this -> _tree -> Branch("jetPt",  &_jetPt);
  this -> _tree -> Branch("jetEta", &_jetEta);
  this -> _tree -> Branch("jetPhi", &_jetPhi);

  this -> _tree -> Branch("l1tJetPt",  &_l1tJetPt);
  this -> _tree -> Branch("l1tJetEta", &_l1tJetEta);
  this -> _tree -> Branch("l1tJetPhi", &_l1tJetPhi);
  this -> _tree -> Branch("l1tJetQual", &_l1tJetQual);
  this -> _tree -> Branch("l1tJetIso", &_l1tJetIso);
  this -> _tree -> Branch("l1tJetIsMatched", &_l1tJetIsMatched);

  this -> _tree -> Branch("metEt",  &_metEt);
  this -> _tree -> Branch("metPhi",  &_metPhi);

  this -> _tree -> Branch("l1tSumType", &_l1tSumType);
  this -> _tree -> Branch("l1tSumEt", &_l1tSumEt);
  this -> _tree -> Branch("l1tSumPhi", &_l1tSumPhi);
  this -> _tree -> Branch("l1tSumIEt", &_l1tSumIEt);
  this -> _tree -> Branch("l1tSumIPhi", &_l1tSumIPhi);

  this -> _tree -> Branch("egPt",       &_egPt);
  this -> _tree -> Branch("egEta",      &_egEta);
  this -> _tree -> Branch("egPhi",      &_egPhi);
  this -> _tree -> Branch("egIsTight",  &_egIsTight);
  this -> _tree -> Branch("egIsMedium", &_egIsMedium);
  this -> _tree -> Branch("egIsLoose",  &_egIsLoose);

  this -> _tree -> Branch("l1tEgPt",        &_l1tEgPt);
  this -> _tree -> Branch("l1tEgEta",       &_l1tEgEta);
  this -> _tree -> Branch("l1tEgPhi",       &_l1tEgPhi);
  this -> _tree -> Branch("l1tEgQual",      &_l1tEgQual);
  this -> _tree -> Branch("l1tEgIso",       &_l1tEgIso);
  this -> _tree -> Branch("l1tEgIsMatched", &_l1tEgIsMatched);
  this -> _tree -> Branch("l1tEgBx", &_l1tEgBx);
  
  this -> _tree -> Branch("muPt",  &_muPt);
  this -> _tree -> Branch("muEta", &_muEta);
  this -> _tree -> Branch("muPhi", &_muPhi);

  this -> _tree -> Branch("l1tMuPt",  &_l1tMuPt);
  this -> _tree -> Branch("l1tMuEta", &_l1tMuEta);
  this -> _tree -> Branch("l1tMuPhi", &_l1tMuPhi);
  this -> _tree -> Branch("l1tMuQual", &_l1tMuQual);
  this -> _tree -> Branch("l1tMuIsMatched", &_l1tMuIsMatched);
*/
  //Branches of second tree (eg)
  this -> _tree2 -> Branch("EventNumber",  &_indexevents2);
  this -> _tree2 -> Branch("RunNumber",  &_runNumber2);
  this -> _tree2 -> Branch("lumi",  &_lumi2);
  this -> _tree2 -> Branch("egPt",       &_egPt2);
  this -> _tree2 -> Branch("egEta",      &_egEta2);
  this -> _tree2 -> Branch("egPhi",      &_egPhi2);
  //this -> _tree2 -> Branch("egIsTight",  &_egIsTight2);
  //this -> _tree2 -> Branch("egIsMedium", &_egIsMedium2);
  //this -> _tree2 -> Branch("egIsLoose",  &_egIsLoose2);
  this -> _tree2 -> Branch("l1tEgPt",        &_l1tEgPt2);
  this -> _tree2 -> Branch("l1tEgEta",       &_l1tEgEta2);
  this -> _tree2 -> Branch("l1tEgPhi",       &_l1tEgPhi2);
  this -> _tree2 -> Branch("l1tEgQual",      &_l1tEgQual2);
  this -> _tree2 -> Branch("l1tEgIso",       &_l1tEgIso2);
  this -> _tree2 -> Branch("l1tEgIsMatched", &_l1tEgIsMatched2);
  this -> _tree2 -> Branch("l1tEgBx", &_l1tEgBx2);
  this -> _tree2 -> Branch("IsUnprefirableEvent", &_IsUnpref_Eg2);
  this -> _tree2 -> Branch("L1t_bit",&_bit_eg);

  //branches of third tree (mu)
  this -> _tree3 -> Branch("EventNumber",  &_indexevents3);
  this -> _tree3 -> Branch("RunNumber",  &_runNumber3);
  this -> _tree3 -> Branch("lumi",  &_lumi3);
  this -> _tree3 -> Branch("muPt",  &_muPt2);
  this -> _tree3 -> Branch("muEta", &_muEta2);
  this -> _tree3 -> Branch("muPhi", &_muPhi2);
  this -> _tree3 -> Branch("l1tMuPt",  &_l1tMuPt2);
  this -> _tree3 -> Branch("l1tMuEta", &_l1tMuEta2);
  this -> _tree3 -> Branch("l1tMuPhi", &_l1tMuPhi2);
  this -> _tree3 -> Branch("l1tMuQual", &_l1tMuQual2);
  this -> _tree3 -> Branch("l1tMuIsMatched", &_l1tMuIsMatched2);
  this -> _tree3 -> Branch("l1tMuBx", &_l1tMuBx2);
  this -> _tree3 -> Branch("IsUnprefirableEvent", &_IsUnpref_Mu2);
  this -> _tree3 -> Branch("L1t_bit",&_bit_mu);


  //branches of fourth tree (jet)
  this -> _tree4 -> Branch("EventNumber",  &_indexevents4);
  this -> _tree4 -> Branch("RunNumber",  &_runNumber4);
  this -> _tree4 -> Branch("lumi",  &_lumi4);
  this -> _tree4 -> Branch("jetPt",  &_jetPt2);
  this -> _tree4 -> Branch("jetEta", &_jetEta2);
  this -> _tree4 -> Branch("jetPhi", &_jetPhi2);
  this -> _tree4 -> Branch("l1tJetPt",  &_l1tJetPt2);
  this -> _tree4 -> Branch("l1tJetEta", &_l1tJetEta2);
  this -> _tree4 -> Branch("l1tJetPhi", &_l1tJetPhi2);
  this -> _tree4 -> Branch("l1tJetQual", &_l1tJetQual2);
  this -> _tree4 -> Branch("l1tJetIso", &_l1tJetIso2);
  this -> _tree4 -> Branch("l1tJetIsMatched", &_l1tJetIsMatched2);
  this -> _tree4 -> Branch("l1tJetBx", &_l1tJetBx2);
  this -> _tree4 -> Branch("IsUnprefirableEvent", &_IsUnpref_Jet2);
  this -> _tree4 -> Branch("L1t_bit",&_bit_jet);


  //branches of fifth tree (taus)
  this -> _tree5 -> Branch("EventNumber",  &_indexevents4);
  this -> _tree5 -> Branch("RunNumber",  &_runNumber4);
  this -> _tree5 -> Branch("lumi",  &_lumi4);
  this -> _tree5 -> Branch("tauPt",  &_tauPt2);
  this -> _tree5 -> Branch("tauEta", &_tauEta2);
  this -> _tree5 -> Branch("tauPhi", &_tauPhi2);
  this -> _tree5 -> Branch("l1tTauPt",  &_l1tTauPt2);
  this -> _tree5 -> Branch("l1tTauEta", &_l1tTauEta2);
  this -> _tree5 -> Branch("l1tTauPhi", &_l1tTauPhi2);
  this -> _tree5 -> Branch("l1tTauQual", &_l1tTauQual2);
  this -> _tree5 -> Branch("l1tTauIso", &_l1tTauIso2);
  this -> _tree5 -> Branch("l1tTauIsMatched", &_l1tTauIsMatched2);
  this -> _tree5 -> Branch("l1tTauBx", &_l1tTauBx2);
  this -> _tree5 -> Branch("IsUnprefirableEvent", &_IsUnpref_Tau2);
  this -> _tree5 -> Branch("L1t_bit",&_bit_tau);


  return;
}


void ZeroBias_Timing::endJob()
{
  return;
}


void ZeroBias_Timing::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  this -> _muBxMatched_8_25  -> Write();
  this -> _muBxMatched_g20  -> Write();
  this -> _egBxMatched  -> Write();
  this -> _tauBxMatched -> Write();
  this -> _jetBxMatched -> Write();
  this -> _egBxMin1Matched_eta -> Write();
  this -> _egBx0Matched_eta -> Write();
  this -> _egBxPlus1Matched_eta -> Write();

  std::cout<<"Sum if Unpref Events = "<<counter_unprefEvents <<std::endl;


  return;
}

// ------------ method called for each event  ------------
void ZeroBias_Timing::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
  this -> Initialize();

  edm::Handle<edm::TriggerResults> METFilterResults;
  iEvent.getByToken(metFiltersPatTag_, METFilterResults);
  if(!(METFilterResults.isValid())) iEvent.getByToken(metFiltersRecoTag_, METFilterResults);

  if (GetMETFilterDecision(iEvent,METFilterResults,"Flag_goodVertices"))
    {
      _indexevents2 = iEvent.id().event();
      _runNumber2 = iEvent.id().run();
      _lumi2 = iEvent.luminosityBlock();
      _indexevents3 = iEvent.id().event();
      _runNumber3 = iEvent.id().run();
      _lumi3 = iEvent.luminosityBlock();
      _indexevents4 = iEvent.id().event();
      _runNumber4 = iEvent.id().run();
      _lumi4 = iEvent.luminosityBlock();
       _indexevents5 = iEvent.id().event();
      _runNumber5 = iEvent.id().run();
      _lumi5 = iEvent.luminosityBlock();
      

      //------------------------------------------------------------------------------------------------

      //Unprefirable
      Flag_IsUnprefirable = false;
      edm::Handle<GlobalExtBlkBxCollection> handleUnprefEventResults;
      iEvent.getByToken(_UnprefirableEventToken, handleUnprefEventResults);
      if(handleUnprefEventResults.isValid()){
        if (handleUnprefEventResults->size() != 0) {
          Flag_IsUnprefirable = handleUnprefEventResults->at(0, 0).getExternalDecision(GlobalExtBlk::maxExternalConditions-1);
        }
      }

        if(Flag_IsUnprefirable)counter_unprefEvents++;
   //   std::cout<<"IsUnprefirableEvent = "<<Flag_IsUnprefirable<<std::endl;

      // Taus
      edm::Handle<pat::TauRefVector>  tauHandle;
      try {iEvent.getByToken(_tauTag, tauHandle);}  catch (...) {;}
      
      edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
      try {iEvent.getByToken(_L1TauTag, L1TauHandle);}  catch (...) {;}

      edm::Handle<GlobalAlgBlkBxCollection> ugtHandle;
      try {iEvent.getByToken(_ugtTag, ugtHandle);}  catch (...) {;}

      if(L1TauHandle.isValid() && tauHandle.isValid() && ugtHandle.isValid())
        {
          for (int ibx = L1TauHandle->getFirstBX(); ibx <= L1TauHandle->getLastBX(); ++ibx)
            {
            
              for (l1t::TauBxCollection::const_iterator bxTauIt = L1TauHandle->begin(ibx); bxTauIt != L1TauHandle->end(ibx) ; bxTauIt++)
                {
                  const l1t::Tau& l1tTau = *bxTauIt;
               
                  for (pat::TauRefVector::const_iterator tauIt = tauHandle->begin(); tauIt != tauHandle->end(); ++tauIt)
                  {
                    const pat::TauRef& tau = *tauIt;
                    if (deltaR(*tau, l1tTau)<0.3)
                      {
                        for (BXVector<GlobalAlgBlk>::const_iterator bxUgtIt = ugtHandle->begin(ibx); bxUgtIt != ugtHandle->end(ibx) ; bxUgtIt++)
                        {
                            const GlobalAlgBlk& ugt =  *bxUgtIt;
                            for(int indeX=0; indeX<=506; indeX++)
                              {
                                this -> _bit_tau[indeX] =  ugt.getAlgoDecisionFinal(indeX);  // L1_SingleMu22
                                std::cout<<" index= "<<indeX<<std::endl;
                                std::cout<<"Bit= "<<ugt.getAlgoDecisionFinal(indeX)<<std::endl;
                              }
                        }
                      
                        _tauPt2=tau->pt();
                          _tauEta2=tau->eta();
                          _tauPhi2=tau->phi();
                          
                          _l1tTauPt2=l1tTau.pt();
                          _l1tTauEta2=l1tTau.eta();
                            _l1tTauPhi2=l1tTau.phi();
                            _l1tTauQual2=l1tTau.hwQual();
                          _l1tTauIso2=l1tTau.hwIso();
                          _l1tTauIsMatched2=1;
                          _l1tTauBx2=ibx;
                         _IsUnpref_Tau2=Flag_IsUnprefirable;
                          this -> _tree5 -> Fill();
                           if(tau->pt()>40. && tau->pt()<60. && l1tTau.pt()>43. && l1tTau.pt()<63. && tau->eta()<2.1)_tauBxMatched->Fill(ibx); /////////// SOS  ////////////////
                          break;
                      }
                  }         
                }
            }
        }

      
      //// Jets
     
      edm::Handle<edm::View<pat::Jet>>  jetHandle;
      try {iEvent.getByToken(_jetTag, jetHandle);}  catch (...) {;}
      
      edm::Handle<BXVector<l1t::Jet>> l1tJetHandle;
      try {iEvent.getByToken(_l1tJetTag, l1tJetHandle);}  catch (...) {;}

      if(l1tJetHandle.isValid() && jetHandle.isValid())
        {
          for (int ibx = l1tJetHandle->getFirstBX(); ibx <= l1tJetHandle->getLastBX(); ++ibx)
            {
           
              for(BXVector<l1t::Jet>::const_iterator bxJetIt = l1tJetHandle -> begin(ibx); bxJetIt != l1tJetHandle -> end(ibx) ; bxJetIt++)
                {
                  const l1t::Jet& l1tJet = *bxJetIt;

                  for (edm::View<pat::Jet>::const_iterator jetIt = jetHandle->begin(); jetIt != jetHandle->end(); ++jetIt)
                    {
                      const pat::Jet& jet = *jetIt;
                      if (deltaR(jet, l1tJet)<0.3)
                        { 

                          _jetPt2=jet.pt();
                          _jetEta2=jet.eta();
                          _jetPhi2=jet.phi();
                          
                          _l1tJetPt2=l1tJet.pt();
                          _l1tJetEta2=l1tJet.eta();
                            _l1tJetPhi2=l1tJet.phi();
                            _l1tJetQual2=l1tJet.hwQual();
                          _l1tJetIso2=l1tJet.hwIso();
                          _l1tJetIsMatched2=1;
                          _l1tJetBx2=ibx;
                          _IsUnpref_Jet2=Flag_IsUnprefirable;
                          this -> _tree4 -> Fill();
                           if(jet.pt()>90. && jet.pt()<160. && l1tJet.pt()>100. && l1tJet.pt()<150.)_jetBxMatched->Fill(ibx);
                          break;
                        }
                    }
                }

            }
        }

    
      //------------------------------------------------------------------------------------------------

      edm::Handle<edm::View<reco::GsfElectron> > eleHandle;
      try {iEvent.getByToken(_eleTag, eleHandle);}  catch (...) {;}
      
      edm::Handle< BXVector<l1t::EGamma> >  L1EGHandle;
      try {iEvent.getByToken(_L1EGTag, L1EGHandle);}  catch (...) {;}
/*
            edm::Handle<edm::ValueMap<bool> > eleTightIdHandle;
            edm::Handle<edm::ValueMap<bool> > eleMediumIdHandle;
            edm::Handle<edm::ValueMap<bool> > eleLooseIdHandle;
            iEvent.getByToken(_eleTightIdTag,  eleTightIdHandle); 
            iEvent.getByToken(_eleMediumIdTag, eleMediumIdHandle);
            iEvent.getByToken(_eleLooseIdTag,  eleLooseIdHandle);
  */        
      if(L1EGHandle.isValid() && eleHandle.isValid())
        {
          for (int ibx = L1EGHandle->getFirstBX(); ibx <= L1EGHandle->getLastBX(); ++ibx)
            {
              for (l1t::EGammaBxCollection::const_iterator bxEGIt = L1EGHandle->begin(ibx); bxEGIt != L1EGHandle->end(ibx) ; bxEGIt++)
                {
                  const l1t::EGamma& l1tEG = *bxEGIt;
                  for (edm::View<reco::GsfElectron>::const_iterator eleIt = eleHandle->begin(); eleIt != eleHandle->end(); ++eleIt)
                    {
                      const reco::GsfElectron& ele = *eleIt;
                      if (deltaR(ele, l1tEG)<0.3)
                        {
                          _l1tEgPt2=l1tEG.pt();
                          _l1tEgEta2=l1tEG.eta();
                          _l1tEgPhi2=l1tEG.phi();
                          _l1tEgIso2=l1tEG.hwIso();
                          _l1tEgQual2=l1tEG.hwQual();
                          _l1tEgIsMatched2=1;
                           _IsUnpref_Eg2=Flag_IsUnprefirable;
                            _l1tEgBx2=ibx;
                          
                       //   _egIsTight2=(*eleTightIdHandle)[*elePtr];
                       //   _egIsMedium2=(*eleMediumIdHandle)[*elePtr];
                       //   _egIsLoose2=(*eleLooseIdHandle)[*elePtr]; 
                          _egPt2=ele.pt();
                          _egEta2=ele.eta();
                            _egPhi2=ele.phi(); 
                          this -> _tree2 -> Fill();
                          
                          if(l1tEG.pt()>15. && l1tEG.pt()<26. && ele.pt()>12. && ele.pt()<23.){
                              _egBxMatched->Fill(ibx);
                              if(ibx==-1)_egBxMin1Matched_eta->Fill(ele.eta());
                              if(ibx==0)_egBx0Matched_eta->Fill(ele.eta());
                              if(ibx==1)_egBxPlus1Matched_eta->Fill(ele.eta() );
                          }
                          break;
                        }
                    }
                }
            }         
        }
      //------------------------------------------------------------------------------------------------

      edm::Handle<pat::MuonRefVector> muonHandle;
      try {iEvent.getByToken(_muTag, muonHandle);}  catch (...) {;}
      
      edm::Handle< BXVector<l1t::Muon> >  L1MuHandle;
      try {iEvent.getByToken(_L1MuTag, L1MuHandle);}  catch (...) {;}


      if(L1MuHandle.isValid() && muonHandle.isValid())
        {
          for (int ibx = L1MuHandle->getFirstBX(); ibx <= L1MuHandle->getLastBX(); ++ibx)
            {
            
              for (l1t::MuonBxCollection::const_iterator bx0MuIt = L1MuHandle->begin(ibx); bx0MuIt != L1MuHandle->end(ibx) ; bx0MuIt++)
                {
                  const l1t::Muon& l1tMu = *bx0MuIt;
                  
                  if (l1tMu.hwQual()!=12) { continue; }
                  for (pat::MuonRefVector::const_iterator muIt = muonHandle->begin(); muIt != muonHandle->end(); ++muIt)
                  {
                    const pat::MuonRef& mu = *muIt;
                    if (deltaR(*mu, l1tMu)<0.3)
                      {
                          _l1tMuPt2=l1tMu.pt();
                            _l1tMuEta2=l1tMu.eta();
                        _l1tMuPhi2=l1tMu.phi();
                            _l1tMuQual2=l1tMu.hwQual();
                        _l1tMuIsMatched2=1;
                        _l1tMuBx2=ibx;
                         _IsUnpref_Mu2=Flag_IsUnprefirable;
                        
                        _muPt2=mu->pt();
                        _muEta2=mu->eta();
                        _muPhi2=mu->phi();

                        this -> _tree3 -> Fill();

                        if(l1tMu.pt()>10. && l1tMu.pt()<21. && mu->pt()>8. && mu->pt()<25. )_muBxMatched_8_25->Fill(ibx);
                        if(l1tMu.pt()>22. && mu->pt()>20.)_muBxMatched_g20->Fill(ibx);

                        break;
                      }                   
                  }     
                }
            }
           }

     // this -> _tree -> Fill();
    }
}

bool ZeroBias_Timing::GetMETFilterDecision(const edm::Event& iEvent,edm::Handle<edm::TriggerResults> METFilterResults, TString studiedfilter){
  
  if( !METFilterResults.failedToGet() ) {
    int N_MetFilters = METFilterResults->size();
    const edm::TriggerNames & metfilterName = iEvent.triggerNames(*METFilterResults);
    for( int i_Metfilter = 0; i_Metfilter < N_MetFilters; ++i_Metfilter ) {
      TString MetfilterPath =metfilterName.triggerName(i_Metfilter);
      //      cout << MetfilterPath<<endl;
      if(MetfilterPath.Index(studiedfilter) >=0)  return METFilterResults.product()->accept(i_Metfilter);

    }
  }
   return true; 
}

#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(ZeroBias_Timing);

#endif //ZeroBias_Timing_H
