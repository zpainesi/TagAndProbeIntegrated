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

  TTree *_tree;
  std::string _treeName;

  // -------------------------------------
  // variables to be filled in output tree
  ULong64_t _indexevents;
  Int_t     _runNumber;
  Int_t     _lumi;

  std::vector<int> _bit21;  // L1_SingleMu22
  std::vector<int> _bit25;  // L1_SingleMu25
  std::vector<int> _bit168; // L1_SingleEG36er2p5
  std::vector<int> _bit169; // L1_SingleEG38er2p5
  std::vector<int> _bit170; // L1_SingleEG40er2p5
  std::vector<int> _bit171; // L1_SingleEG42er2p5
  std::vector<int> _bit172; // L1_SingleEG45er2p5
  std::vector<int> _bit178; // L1_SingleLooseIsoEG28er2p5
  std::vector<int> _bit192; // L1_SingleIsoEG30er2p5
  std::vector<int> _bit194; // L1_SingleIsoEG32er2p5
  std::vector<int> _bit196; // L1_SingleIsoEG34er2p5
  std::vector<int> _bit218; // L1_DoubleEG_25_12_er2p5
  std::vector<int> _bit219; // L1_DoubleEG_25_12_er2p5
  std::vector<int> _bit220; // L1_DoubleEG_25_12_er2p5
  std::vector<int> _bit262; // L1_SingleIsoTau32er2p1
  std::vector<int> _bit263; // L1_SingleTau70er2p1
  std::vector<int> _bit264; // L1_SingleTau120er2p1
  std::vector<int> _bit267; // L1_DoubleTau70er2p1
  std::vector<int> _bit270; // L1_DoubleIsoTau32er2p1
  std::vector<int> _bit271; // L1_DoubleIsoTau34er2p1
  std::vector<int> _bit272; // L1_DoubleIsoTau35er2p1
  std::vector<int> _bit273; // L1_DoubleIsoTau36er2p1
  std::vector<int> _bit309; // L1_SingleJet35
  std::vector<int> _bit310; // L1_SingleJet60
  std::vector<int> _bit398; // L1_HTT120er
  std::vector<int> _bit418; // L1_ETMHF70
  std::vector<int> _bit420; // L1_ETMHF90
  std::vector<int> _bit459; // L1_ZeroBias
  std::vector<int> _bit478; // L1_LastCollisionInTrain
  std::vector<int> _bit479; // L1_FirstCollisionInTrain
  std::vector<int> _bit480; // L1_FirstCollisionInOrbit

  std::vector<float> _tauPt;
  std::vector<float> _tauEta;
  std::vector<float> _tauPhi;

  std::vector< std::vector<float> > _l1tTauPt;
  std::vector< std::vector<float> > _l1tTauEta;
  std::vector< std::vector<float> > _l1tTauPhi;
  std::vector< std::vector<int> >   _l1tTauQual;
  std::vector< std::vector<int> >   _l1tTauIso;
  std::vector< std::vector<int> >   _l1tTauIsMatched;

  std::vector<float> _jetPt;
  std::vector<float> _jetEta;
  std::vector<float> _jetPhi;

  std::vector< std::vector<float> > _l1tJetPt;
  std::vector< std::vector<float> > _l1tJetEta;
  std::vector< std::vector<float> > _l1tJetPhi;
  std::vector< std::vector<int> >   _l1tJetQual;
  std::vector< std::vector<int> >   _l1tJetIso;
  std::vector< std::vector<int> >   _l1tJetIsMatched;

  float _metEt;
  float _metPhi;

  std::vector< std::vector<short int> > _l1tSumType;
  std::vector< std::vector<float> >     _l1tSumEt;
  std::vector< std::vector<float> >     _l1tSumPhi;
  std::vector< std::vector<float> >     _l1tSumIEt;
  std::vector< std::vector<float> >     _l1tSumIPhi;

  std::vector<float> _egPt;
  std::vector<float> _egEta;
  std::vector<float> _egPhi;
  std::vector<int>   _egIsTight;
  std::vector<int>   _egIsMedium;
  std::vector<int>   _egIsLoose;

  std::vector< std::vector<float> >  _l1tEgPt;
  std::vector< std::vector<float> >  _l1tEgEta;
  std::vector< std::vector<float> >  _l1tEgPhi;
  std::vector< std::vector<int> >    _l1tEgIso;
  std::vector< std::vector<int> >    _l1tEgQual;
  std::vector< std::vector<int> >    _l1tEgIsMatched;
  std::vector< std::vector<int> >    _l1tEgBx;


  std::vector<float> _muPt;
  std::vector<float> _muEta;
  std::vector<float> _muPhi;

  std::vector< std::vector<float> > _l1tMuPt;
  std::vector< std::vector<float> > _l1tMuEta;
  std::vector< std::vector<float> > _l1tMuPhi;
  std::vector< std::vector<int> >   _l1tMuQual;
  std::vector< std::vector<int> >   _l1tMuIsMatched;

  TH1F* _muBxMatched  = new TH1F("muBxMatched",  "muBxMatched",  5, -2.5, 2.5);
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
  this -> _indexevents = 0;
  this -> _runNumber   = 0;
  this -> _lumi        = 0;

  this -> _bit21  . clear();
  this -> _bit25  . clear();
  this -> _bit168 . clear();
  this -> _bit169 . clear();
  this -> _bit170 . clear();
  this -> _bit171 . clear();
  this -> _bit172 . clear();
  this -> _bit178 . clear();
  this -> _bit192 . clear();
  this -> _bit194 . clear();
  this -> _bit196 . clear();
  this -> _bit218 . clear();
  this -> _bit219 . clear();
  this -> _bit220 . clear();
  this -> _bit262 . clear();
  this -> _bit263 . clear();
  this -> _bit264 . clear();
  this -> _bit267 . clear();
  this -> _bit270 . clear();
  this -> _bit271 . clear();
  this -> _bit272 . clear();
  this -> _bit273 . clear();
  this -> _bit309 . clear();
  this -> _bit310 . clear();
  this -> _bit398 . clear();
  this -> _bit418 . clear();
  this -> _bit420 . clear();
  this -> _bit459 . clear();
  this -> _bit478 . clear();
  this -> _bit479 . clear();
  this -> _bit480 . clear();

  this -> _tauPt  . clear();
  this -> _tauEta . clear();
  this -> _tauPhi . clear();

  this -> _l1tTauPt        . clear();
  this -> _l1tTauEta       . clear();
  this -> _l1tTauPhi       . clear();
  this -> _l1tTauQual      . clear();
  this -> _l1tTauIso       . clear();
  this -> _l1tTauIsMatched . clear();

  this -> _jetPt  . clear();
  this -> _jetEta . clear();
  this -> _jetPhi . clear();

  this -> _l1tJetPt        . clear();
  this -> _l1tJetEta       . clear();
  this -> _l1tJetPhi       . clear();
  this -> _l1tJetQual      . clear();
  this -> _l1tJetIso       . clear();
  this -> _l1tJetIsMatched . clear();

  this -> _metEt  = -1.;
  this -> _metPhi = -1.;

  this -> _l1tSumType.clear();
  this -> _l1tSumEt.clear();
  this -> _l1tSumPhi.clear();
  this -> _l1tSumIEt.clear();
  this -> _l1tSumIPhi.clear();

  this -> _egPt       . clear();
  this -> _egEta      . clear();
  this -> _egPhi      . clear();
  this -> _egIsTight  . clear();
  this -> _egIsMedium . clear();
  this -> _egIsLoose  . clear();

  this -> _l1tEgPt        . clear();
  this -> _l1tEgEta       . clear();
  this -> _l1tEgPhi       . clear();
  this -> _l1tEgQual      . clear();
  this -> _l1tEgIso       . clear();
  this -> _l1tEgIsMatched . clear();
  this -> _l1tEgBx        . clear();

  this -> _muPt  . clear();
  this -> _muEta . clear();
  this -> _muPhi . clear();

  this -> _l1tMuPt        . clear();
  this -> _l1tMuEta       . clear();
  this -> _l1tMuPhi       . clear();
  this -> _l1tMuQual      . clear();
  this -> _l1tMuIsMatched . clear();
}


void ZeroBias_Timing::beginJob()
{
  edm::Service<TFileService> fs;
  this -> _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

  //Branches
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

  return;
}


void ZeroBias_Timing::endJob()
{
  return;
}


void ZeroBias_Timing::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
  this -> _muBxMatched  -> Write();
  this -> _egBxMatched  -> Write();
  this -> _tauBxMatched -> Write();
  this -> _jetBxMatched -> Write();
  this -> _egBxMin1Matched_eta -> Write();
  this -> _egBx0Matched_eta -> Write();
  this -> _egBxPlus1Matched_eta -> Write();

  return;
}


void ZeroBias_Timing::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
  this -> Initialize();

  edm::Handle<edm::TriggerResults> METFilterResults;
  iEvent.getByToken(metFiltersPatTag_, METFilterResults);
  if(!(METFilterResults.isValid())) iEvent.getByToken(metFiltersRecoTag_, METFilterResults);

  if (GetMETFilterDecision(iEvent,METFilterResults,"Flag_goodVertices"))
    {
      _indexevents = iEvent.id().event();
      _runNumber = iEvent.id().run();
      _lumi = iEvent.luminosityBlock();

      edm::Handle<GlobalAlgBlkBxCollection> ugtHandle;
      try {iEvent.getByToken(_ugtTag, ugtHandle);}  catch (...) {;}
      if(ugtHandle.isValid())
        {
          for (int ibx = ugtHandle->getFirstBX(); ibx <= ugtHandle->getLastBX(); ++ibx)
            {
              for (BXVector<GlobalAlgBlk>::const_iterator bxUgtIt = ugtHandle->begin(ibx); bxUgtIt != ugtHandle->end(ibx) ; bxUgtIt++)
                {
                  const GlobalAlgBlk& ugt =  *bxUgtIt;

                  this -> _bit21.push_back(  ugt.getAlgoDecisionFinal(21) );  // L1_SingleMu22
                  this -> _bit25.push_back(  ugt.getAlgoDecisionFinal(25) );  // L1_SingleMu25
                  this -> _bit168.push_back( ugt.getAlgoDecisionFinal(168) ); // L1_SingleEG36er2p5
                  this -> _bit169.push_back( ugt.getAlgoDecisionFinal(169) ); // L1_SingleEG38er2p5
                  this -> _bit170.push_back( ugt.getAlgoDecisionFinal(170) ); // L1_SingleEG40er2p5
                  this -> _bit171.push_back( ugt.getAlgoDecisionFinal(171) ); // L1_SingleEG42er2p5
                  this -> _bit172.push_back( ugt.getAlgoDecisionFinal(172) ); // L1_SingleEG45er2p5
                  this -> _bit178.push_back( ugt.getAlgoDecisionFinal(178) ); // L1_SingleLooseIsoEG28er2p5
                  this -> _bit192.push_back( ugt.getAlgoDecisionFinal(192) ); // L1_SingleIsoEG30er2p5
                  this -> _bit194.push_back( ugt.getAlgoDecisionFinal(194) ); // L1_SingleIsoEG32er2p5
                  this -> _bit196.push_back( ugt.getAlgoDecisionFinal(196) ); // L1_SingleIsoEG34er2p5
                  this -> _bit218.push_back( ugt.getAlgoDecisionFinal(218) ); // L1_DoubleEG_25_12_er2p5
                  this -> _bit219.push_back( ugt.getAlgoDecisionFinal(219) ); // L1_DoubleEG_25_12_er2p5
                  this -> _bit220.push_back( ugt.getAlgoDecisionFinal(220) ); // L1_DoubleEG_25_12_er2p5
                  this -> _bit262.push_back( ugt.getAlgoDecisionFinal(262) ); // L1_SingleIsoTau32er2p1
                  this -> _bit263.push_back( ugt.getAlgoDecisionFinal(263) ); // L1_SingleTau70er2p1
                  this -> _bit264.push_back( ugt.getAlgoDecisionFinal(264) ); // L1_SingleTau120er2p1
                  this -> _bit267.push_back( ugt.getAlgoDecisionFinal(267) ); // L1_DoubleTau70er2p1
                  this -> _bit270.push_back( ugt.getAlgoDecisionFinal(270) ); // L1_DoubleIsoTau32er2p1
                  this -> _bit271.push_back( ugt.getAlgoDecisionFinal(271) ); // L1_DoubleIsoTau34er2p1
                  this -> _bit272.push_back( ugt.getAlgoDecisionFinal(272) ); // L1_DoubleIsoTau35er2p1
                  this -> _bit273.push_back( ugt.getAlgoDecisionFinal(273) ); // L1_DoubleIsoTau36er2p1
                  this -> _bit309.push_back( ugt.getAlgoDecisionFinal(309) ); // L1_SingleJet35
                  this -> _bit310.push_back( ugt.getAlgoDecisionFinal(310) ); // L1_SingleJet60
                  this -> _bit398.push_back( ugt.getAlgoDecisionFinal(398) ); // L1_HTT120er
                  this -> _bit418.push_back( ugt.getAlgoDecisionFinal(418) ); // L1_ETMHF70
                  this -> _bit420.push_back( ugt.getAlgoDecisionFinal(420) ); // L1_ETMHF90
                  this -> _bit459.push_back( ugt.getAlgoDecisionFinal(459) ); // L1_ZeroBias
                  this -> _bit478.push_back( ugt.getAlgoDecisionFinal(478) ); // L1_LastCollisionInTrain
                  this -> _bit479.push_back( ugt.getAlgoDecisionFinal(479) ); // L1_FirstCollisionInTrain
                  this -> _bit480.push_back( ugt.getAlgoDecisionFinal(480) ); // L1_FirstCollisionInOrbit
                }
            }
        }

      //------------------------------------------------------------------------------------------------

      edm::Handle<pat::TauRefVector>  tauHandle;
      try {iEvent.getByToken(_tauTag, tauHandle);}  catch (...) {;}
      
      edm::Handle< BXVector<l1t::Tau> >  L1TauHandle;
      try {iEvent.getByToken(_L1TauTag, L1TauHandle);}  catch (...) {;}

      if(L1TauHandle.isValid() && tauHandle.isValid())
        {
          for (int ibx = L1TauHandle->getFirstBX(); ibx <= L1TauHandle->getLastBX(); ++ibx)
            {
              std::vector<float> tmp_l1tTauPt;
              std::vector<float> tmp_l1tTauEta;
              std::vector<float> tmp_l1tTauPhi;
              std::vector<int>   tmp_l1tTauIso;
              std::vector<int>   tmp_l1tTauQual;
              std::vector<int>   tmp_l1tTauIsMatched;

              for (l1t::TauBxCollection::const_iterator bxTauIt = L1TauHandle->begin(ibx); bxTauIt != L1TauHandle->end(ibx) ; bxTauIt++)
                {
                  const l1t::Tau& l1tTau = *bxTauIt;
                  
                  tmp_l1tTauPt   . push_back(l1tTau.pt());
                  tmp_l1tTauEta  . push_back(l1tTau.eta());
                  tmp_l1tTauPhi  . push_back(l1tTau.phi());
                  tmp_l1tTauIso  . push_back(l1tTau.hwIso());
                  tmp_l1tTauQual . push_back(l1tTau.hwQual());

                  bool matchFound = false;
                  for (pat::TauRefVector::const_iterator tauIt = tauHandle->begin(); tauIt != tauHandle->end(); ++tauIt)
                  {
                    const pat::TauRef& tau = *tauIt;
                    if (deltaR(*tau, l1tTau)<0.5)
                      {
                        matchFound = true;
                        _tauBxMatched->Fill(ibx);
                        break;
                      }
                  }

                  if (matchFound) { tmp_l1tTauIsMatched.push_back(1); }
                  else            { tmp_l1tTauIsMatched.push_back(0); }
                }

              this -> _l1tTauPt        . push_back(tmp_l1tTauPt);
              this -> _l1tTauEta       . push_back(tmp_l1tTauEta);
              this -> _l1tTauPhi       . push_back(tmp_l1tTauPhi);
              this -> _l1tTauIso       . push_back(tmp_l1tTauIso);
              this -> _l1tTauQual      . push_back(tmp_l1tTauQual);
              this -> _l1tTauIsMatched . push_back(tmp_l1tTauIsMatched);
            }

            for (pat::TauRefVector::const_iterator tauIt = tauHandle->begin(); tauIt != tauHandle->end(); ++tauIt)
              {
                const pat::TauRef& tau = *tauIt;
                
                _tauPt  . push_back(tau->pt());
                _tauEta . push_back(tau->eta());
                _tauPhi . push_back(tau->phi());
              }
        }

      //------------------------------------------------------------------------------------------------

      edm::Handle<edm::View<pat::Jet>>  jetHandle;
      try {iEvent.getByToken(_jetTag, jetHandle);}  catch (...) {;}
      
      edm::Handle<BXVector<l1t::Jet>> l1tJetHandle;
      try {iEvent.getByToken(_l1tJetTag, l1tJetHandle);}  catch (...) {;}

      if(l1tJetHandle.isValid() && jetHandle.isValid())
        {
          for (int ibx = l1tJetHandle->getFirstBX(); ibx <= l1tJetHandle->getLastBX(); ++ibx)
            {
              std::vector<float> tmp_l1tJetPt;
              std::vector<float> tmp_l1tJetEta;
              std::vector<float> tmp_l1tJetPhi;
              std::vector<int>   tmp_l1tJetIso;
              std::vector<int>   tmp_l1tJetQual;
              std::vector<int>   tmp_l1tJetIsMatched;
              
              for(BXVector<l1t::Jet>::const_iterator bxJetIt = l1tJetHandle -> begin(ibx); bxJetIt != l1tJetHandle -> end(ibx) ; bxJetIt++)
                {
                  const l1t::Jet& l1tJet = *bxJetIt;

                  tmp_l1tJetPt   . push_back(l1tJet.pt());
                  tmp_l1tJetEta  . push_back(l1tJet.eta());
                  tmp_l1tJetPhi  . push_back(l1tJet.phi());
                  tmp_l1tJetIso  . push_back(l1tJet.hwIso());
                  tmp_l1tJetQual . push_back(l1tJet.hwQual());

                  bool matchFound = false;
                  for (edm::View<pat::Jet>::const_iterator jetIt = jetHandle->begin(); jetIt != jetHandle->end(); ++jetIt)
                    {
                      const pat::Jet& jet = *jetIt;

                      if (deltaR(jet, l1tJet)<0.5 && (l1tJet.pt()>100. && l1tJet.pt()<150.))
                        { 
                          matchFound = true;
                          _jetBxMatched->Fill(ibx);
                          break;
                        }
                    }

                  if (matchFound) { tmp_l1tJetIsMatched.push_back(1); }
                  else            { tmp_l1tJetIsMatched.push_back(0); }
                }

              this -> _l1tJetPt        . push_back(tmp_l1tJetPt);
              this -> _l1tJetEta       . push_back(tmp_l1tJetEta);
              this -> _l1tJetPhi       . push_back(tmp_l1tJetPhi);
              this -> _l1tJetIso       . push_back(tmp_l1tJetIso);
              this -> _l1tJetQual      . push_back(tmp_l1tJetQual);
              this -> _l1tJetIsMatched . push_back(tmp_l1tJetIsMatched);
            }

            for (edm::View<pat::Jet>::const_iterator jetIt = jetHandle->begin(); jetIt != jetHandle->end(); ++jetIt)
              {
                const pat::Jet& jet = *jetIt;
                
                _jetPt  . push_back(jet.pt());
                _jetEta . push_back(jet.eta());
                _jetPhi . push_back(jet.phi());
              }
        }

      //------------------------------------------------------------------------------------------------

      edm::Handle<pat::METCollection> metHandle;
      try {iEvent.getByToken (_metTag, metHandle); }  catch (...) {;}
      const pat::MET met = (*metHandle)[0];

      _metEt  = met.pt();
      _metPhi = met.phi();

      edm::Handle<BXVector<l1t::EtSum>> l1tSumHandle;
      try {iEvent.getByToken(this -> _l1tSumTag, l1tSumHandle);}  catch (...) {;}

      if(l1tSumHandle.isValid())
        {
          for (int ibx = l1tSumHandle->getFirstBX(); ibx <= l1tSumHandle->getLastBX(); ++ibx)
            {
              std::vector<short int> tmp_l1tSumType;
              std::vector<float>     tmp_l1tSumEt;
              std::vector<float>     tmp_l1tSumPhi;
              std::vector<float>     tmp_l1tSumIEt;
              std::vector<float>     tmp_l1tSumIPhi;

              for(BXVector<l1t::EtSum>::const_iterator bxSumIt = l1tSumHandle->begin(ibx); bxSumIt != l1tSumHandle->end(ibx) ; bxSumIt++)
                {
                  const l1t::EtSum& l1tSum = *bxSumIt;

                  tmp_l1tSumType  . push_back(l1tSum.getType());
                  tmp_l1tSumEt    . push_back(l1tSum.et());
                  tmp_l1tSumPhi   . push_back(l1tSum.phi());
                  tmp_l1tSumIEt   . push_back(l1tSum.hwPt());
                  tmp_l1tSumIPhi  . push_back(l1tSum.hwPhi());
                }
              
              this -> _l1tSumType      . push_back(tmp_l1tSumType);
              this -> _l1tSumEt        . push_back(tmp_l1tSumEt);
              this -> _l1tSumPhi       . push_back(tmp_l1tSumPhi);
              this -> _l1tSumIEt       . push_back(tmp_l1tSumIEt);
              this -> _l1tSumIPhi      . push_back(tmp_l1tSumIPhi);
            }
        }

      //------------------------------------------------------------------------------------------------

      edm::Handle<edm::View<reco::GsfElectron> > eleHandle;
      try {iEvent.getByToken(_eleTag, eleHandle);}  catch (...) {;}
      
      edm::Handle< BXVector<l1t::EGamma> >  L1EGHandle;
      try {iEvent.getByToken(_L1EGTag, L1EGHandle);}  catch (...) {;}

      if(L1EGHandle.isValid() && eleHandle.isValid())
        {
          int counter_bx_haris=0;
          for (int ibx = L1EGHandle->getFirstBX(); ibx <= L1EGHandle->getLastBX(); ++ibx)
            {
              counter_bx_haris++;
              std::cout << std::endl << "OUT: bxCount= "<< counter_bx_haris;
              std::vector<float>  tmp_l1tEGPt;
              std::vector<float>  tmp_l1tEGEta;
              std::vector<float>  tmp_l1tEGPhi;
              std::vector<int>    tmp_l1tEGIso;
              std::vector<int>    tmp_l1tEGQual;
              std::vector<int>    tmp_l1tEGIsMatched;
              std::vector<int>    tmp_l1tEGBx;
              int counter_haris=0;
              for (l1t::EGammaBxCollection::const_iterator bxEGIt = L1EGHandle->begin(ibx); bxEGIt != L1EGHandle->end(ibx) ; bxEGIt++)
                {
                  const l1t::EGamma& l1tEG = *bxEGIt;
                  counter_haris++;
                  tmp_l1tEGPt   . push_back(l1tEG.pt());
                  tmp_l1tEGEta  . push_back(l1tEG.eta());
                  tmp_l1tEGPhi  . push_back(l1tEG.phi());
                  tmp_l1tEGIso  . push_back(l1tEG.hwIso());
                  tmp_l1tEGQual . push_back(l1tEG.hwQual());
                  tmp_l1tEGBx   . push_back(ibx);
                  std::cout << std::endl << "OUT: Count= "<< counter_haris;
                  std::cout << std::endl << "OUT: The pt of eg is " << l1tEG.pt();
                  std::cout << std::endl << "OUT: The eta of eg is " << l1tEG.eta();
                  std::cout << std::endl << "OUT: The phi of eg is " << l1tEG.phi();
                  std::cout << std::endl << "OUT: The iso of eg is " << l1tEG.hwIso();
                  std::cout << std::endl << "OUT: The qual of eg is " << l1tEG.hwQual();
                  std::cout << std::endl << "OUT: The BX of eg is " << ibx;


                  bool matchFound = false;
                  for (edm::View<reco::GsfElectron>::const_iterator eleIt = eleHandle->begin(); eleIt != eleHandle->end(); ++eleIt)
                    {
                      const reco::GsfElectron& ele = *eleIt;
                      if (deltaR(ele, l1tEG)<0.5)
                        {
                          matchFound = true;
                          if(ibx==-1)_egBxMin1Matched_eta->Fill(l1tEG.eta());
                          if(ibx==0)_egBx0Matched_eta->Fill(l1tEG.eta());
                          if(ibx==1)_egBxPlus1Matched_eta->Fill(l1tEG.eta() );
                          
                          _egBxMatched->Fill(ibx);
                          //std::cout << std::endl << "IN: The BX of eg is " << ibx;

                          break;
                        }
                    }

                  if (matchFound) { tmp_l1tEGIsMatched.push_back(1); }
                  else            { tmp_l1tEGIsMatched.push_back(0); }
                }

              this -> _l1tEgPt          . push_back(tmp_l1tEGPt);
              this -> _l1tEgEta         . push_back(tmp_l1tEGEta);
              this -> _l1tEgPhi         . push_back(tmp_l1tEGPhi);
              this -> _l1tEgIso         . push_back(tmp_l1tEGIso);
              this -> _l1tEgQual        . push_back(tmp_l1tEGQual);
              this -> _l1tEgIsMatched   . push_back(tmp_l1tEGIsMatched);
              this -> _l1tEgBx   . push_back(tmp_l1tEGBx);
            }

            edm::Handle<edm::ValueMap<bool> > eleTightIdHandle;
            edm::Handle<edm::ValueMap<bool> > eleMediumIdHandle;
            edm::Handle<edm::ValueMap<bool> > eleLooseIdHandle;
            iEvent.getByToken(_eleTightIdTag,  eleTightIdHandle); 
            iEvent.getByToken(_eleMediumIdTag, eleMediumIdHandle);
            iEvent.getByToken(_eleLooseIdTag,  eleLooseIdHandle);
            
            // short int idx = 0;
          int counter_offl=0;
            for (edm::View<reco::GsfElectron>::const_iterator eleIt = eleHandle->begin(); eleIt != eleHandle->end(); ++eleIt)
              {
                const reco::GsfElectron& ele = *eleIt;
                // const auto elePtr = eleHandle->ptrAt(idx); ++idx;
                counter_offl++;
                _egPt  . push_back(ele.pt());
                _egEta . push_back(ele.eta());
                _egPhi . push_back(ele.phi());
                std::cout<<std::endl<<"Offline counter: "<<counter_offl;
                std::cout << std::endl << "The offl pt of eg is " << ele.pt();
                std::cout << std::endl << "The offl eta of eg is " << ele.eta();
                std::cout << std::endl << "The offl phi of eg is " << ele.phi();

                

                // _egIsTight  . push_back( (*eleTightIdHandle)[*elePtr] );
                // _egIsMedium . push_back( (*eleMediumIdHandle)[*elePtr] );
                // _egIsLoose  . push_back( (*eleLooseIdHandle)[*elePtr] );
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
              std::vector<float> tmp_l1tMuPt;
              std::vector<float> tmp_l1tMuEta;
              std::vector<float> tmp_l1tMuPhi;
              std::vector<int>   tmp_l1tMuQual;
              std::vector<int>   tmp_l1tMuIsMatched;

              for (l1t::MuonBxCollection::const_iterator bx0MuIt = L1MuHandle->begin(ibx); bx0MuIt != L1MuHandle->end(ibx) ; bx0MuIt++)
                {
                  const l1t::Muon& l1tMu = *bx0MuIt;
                  
                  if (l1tMu.hwQual()!=12) { continue; }

                  tmp_l1tMuPt   . push_back(l1tMu.pt());
                  tmp_l1tMuEta  . push_back(l1tMu.eta());
                  tmp_l1tMuPhi  . push_back(l1tMu.phi());
                  tmp_l1tMuQual . push_back(l1tMu.hwQual());

                  bool matchFound = false;
                  for (pat::MuonRefVector::const_iterator muIt = muonHandle->begin(); muIt != muonHandle->end(); ++muIt)
                  {
                    const pat::MuonRef& mu = *muIt;
                    if (deltaR(*mu, l1tMu)<0.5 && (l1tMu.pt()>10. && l1tMu.pt()<21.))
                      {
                        matchFound = true;
                        _muBxMatched->Fill(ibx);
                        break;
                      }
                  }

                  if (matchFound) { tmp_l1tMuIsMatched.push_back(1); }
                  else            { tmp_l1tMuIsMatched.push_back(0); }
                }

              this -> _l1tMuPt        . push_back(tmp_l1tMuPt);
              this -> _l1tMuEta       . push_back(tmp_l1tMuEta);
              this -> _l1tMuPhi       . push_back(tmp_l1tMuPhi);
              this -> _l1tMuQual      . push_back(tmp_l1tMuQual);  
              this -> _l1tMuIsMatched . push_back(tmp_l1tMuIsMatched);
            }

            for (pat::MuonRefVector::const_iterator muIt = muonHandle->begin(); muIt != muonHandle->end(); ++muIt)
              {
                const pat::MuonRef& mu = *muIt;
                
                _muPt  . push_back(mu->pt());
                _muEta . push_back(mu->eta());
                _muPhi . push_back(mu->phi());
              }

        }

      this -> _tree -> Fill();
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
