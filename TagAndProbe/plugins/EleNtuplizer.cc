#ifndef ELENTUPLIZER_H
#define ELENTUPLIZER_H

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
#include <DataFormats/PatCandidates/interface/Photon.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTPrescaleProvider.h"
#include "DataFormats/L1Trigger/interface/EGamma.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include <DataFormats/PatCandidates/interface/GenericParticle.h>
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/TriggerResults.h"

#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include "tParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"

#define N_GEN_MAX 5000

#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Utilities/interface/EDMException.h"

//Set this variable to decide the number of triggers that you want to check simultaneously
#define NUMBER_OF_MAXIMUM_TRIGGERS 64


/*
██████  ███████  ██████ ██       █████  ██████   █████  ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██
██   ██ █████   ██      ██      ███████ ██████  ███████    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██      ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████  ██████ ███████ ██   ██ ██   ██ ██   ██    ██    ██  ██████  ██   ████
*/

class EleNtuplizer : public edm::one::EDAnalyzer<edm::one::WatchRuns> {
    public:
        /// Constructor
        explicit EleNtuplizer(const edm::ParameterSet&);
        /// Destructor
        virtual ~EleNtuplizer();

    private:
        //----edm control---
        virtual void beginJob() ;
        virtual void beginRun(edm::Run const&, edm::EventSetup const&);
        virtual void analyze(const edm::Event&, const edm::EventSetup&);
        virtual void endJob();
        virtual void endRun(edm::Run const&, edm::EventSetup const&);
        void Initialize();
        bool hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor);
        void addTheGenInfo( const edm::Handle<edm::View<reco::GenParticle>>  &genParticles);
        bool matchToTruth(const edm::Ptr<reco::GsfElectron> ele, 
                const edm::Handle<edm::View<reco::GenParticle>>  &genParticles);

        TTree *_tree;
        TTree *_triggerNamesTreeTag;
        TTree *_triggerNamesTreeProbe;

        std::string _treeName;
        ULong64_t   _indexevents;
        Int_t       _runNumber;
        Int_t       _lumi;
        Int_t       _PS_column;
        Int_t       _Nvtx;

        unsigned long _eleProbeTriggerBits;
        unsigned long _eleTagTriggerBits;

        // All Electrons
        int                _allEl_Size;
        std::vector<float> _allEl_Pt;
        std::vector<float> _allEl_Eta;
        std::vector<float> _allEl_Phi;
        std::vector<float> _allEl_SclEt;
        std::vector<float> _allEl_Charge;

        // All Photons
        std::vector<float> _allPho_Pt;
        std::vector<float> _allPho_Eta;
        std::vector<float> _allPho_Phi;
        std::vector<float> _allPho_SclEt;

        // All L1 objects
        std::vector<float> _allL1tPt;
        std::vector<float> _allL1tEta;
        std::vector<float> _allL1tIso;
        std::vector<float> _allL1tPhi;
        std::vector<float> _allL1tQual;
 

        /////////////////////////////////////////////////////////////////
        // offline ID selections & DeltaR & SeedTowerEt & TowerHoE & iem & ihad
        int _isProbeLoose;
        int _isProbeTight;
        int _isProbeMedium;

        float _Unpacked_dR;
        float _Emulated_dR;

        int _seedTowerEt;
        
        int _TowerHoE;     

        int _iem;
        int _ihad;

        int _shape;
        ////////////////////////////////////////////////////////////////

        // Probe Electrons - single
        float _eleProbePt;
        float _eleProbeEta;
        float _eleProbePhi;
        float _eleProbeSclEt;
        int   _eleProbeCharge;

        // Probe Electrons - multiple
        // std::vector<float> _eleProbePt; 
        // std::vector<float> _eleProbeEta;
        // std::vector<float> _eleProbePhi;
        // std::vector<float> _eleProbeSclEt;
        // std::vector<int>   _eleProbeCharge;

        // Probe matched hlt electrons
        float _hltPt;
        float _hltEta;
        float _hltPhi;
        int   _l1tQual;
        
        // Probe matched l1 electrons
        float _l1tPt;
        float _l1tEta;
        float _l1tPhi;
        int   _l1tIso;
        int   _l1tEmuQual;
        
        // gen electrons
        float _genE;
        float _genMass;
        float _genPt;
        float _genEta;
        float _genPhi;
        float _genClosesetZDauEt;
        float _isDaughterOfZ;
        float _isBremSafe;
        
        // Probe matched l1 emulated electrons
        float _l1tEmuPt;
        float _l1tEmuEta;
        float _l1tEmuPhi;
        int   _l1tEmuIso;
        int   _l1tEmuNTT;
        int   _l1tEmuTowerIEta;
        int   _l1tEmuTowerIPhi;
        int   _l1tEmuRawEt;
        int   _l1tEmuIsoEt;
        
        // TandAndProbe tag
        Bool_t _isTagHLTmatched;
        Bool_t _isProbeHLTmatched;
        Bool_t _isOS;
        int   _foundTag;
        float _eleTagPt;
        float _eleTagEta;
        float _eleTagPhi;
        int   _eleTagCharge;
        float _Mee;
        
        int nPhotons;
        float allPhotonPDGID[N_GEN_MAX];
        float allPhotonScEt[N_GEN_MAX];
        float allPhotonPt[N_GEN_MAX];
        float allPhotonEta[N_GEN_MAX];
        float allPhotonPhi[N_GEN_MAX];

        int nGenParticle;
        float genParticlePDGID[N_GEN_MAX];
        float genParticlePt[N_GEN_MAX];
        float genParticleEta[N_GEN_MAX];
        float genParticlePhi[N_GEN_MAX];
        float genParticleMass[N_GEN_MAX];
        float genParticleMother[N_GEN_MAX];


        /////////////////////////////////////////////////////////////////////
        int _hasL1[100];
        int _hasL1_iso[100];

        int _hasL1Emu[100];
        int _hasL1Emu_iso[100];
        int _hasL1_looseiso[100];
        int _hasL1Emu_looseiso[100];
        int _hasL1_tightiso[100];
        int _hasL1Emu_tightiso[100];
        /////////////////////////////////////////////////////////////////////
        
        // Tokes consumed by producers
        edm::EDGetTokenT< vector<pat::Photon>  >                 _photonsTag;
        edm::EDGetTokenT<edm::View<reco::GsfElectron> >          _electronsTag;
        edm::EDGetTokenT<edm::View<reco::GenParticle> >          _genParticlesTag;
        edm::EDGetTokenT<edm::ValueMap<bool>>                    _eleTightIdMapTag;
        edm::EDGetTokenT<edm::ValueMap<bool>>                    _eleMediumIdMapTag;
        edm::EDGetTokenT<edm::ValueMap<bool>>                    _eleLooseIdMapTag;
        edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> _triggerObjects;
        edm::EDGetTokenT<edm::TriggerResults>                    _triggerBits;
        edm::EDGetTokenT<l1t::EGammaBxCollection>                _L1EGTag  ;
        edm::EDGetTokenT<l1t::EGammaBxCollection>                _L1EmuEGTag  ;
        edm::EDGetTokenT<std::vector<reco::Vertex>>              _VtxTag;

        bool _useGenMatch;
        bool _useHLTMatch;

        //!Contains the parameters
        tVParameterSet _parameters_Tag;
        tVParameterSet _parameters;

        edm::InputTag _processName;
        //! Maximum
        std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleProbeTriggerBitSet;
        std::bitset<NUMBER_OF_MAXIMUM_TRIGGERS> _eleTagTriggerBitSet;

        HLTConfigProvider _hltConfig;
        HLTPrescaleProvider* _hltPrescale;


};

/*
██ ███    ███ ██████  ██      ███████ ███    ███ ███████ ███    ██ ████████  █████  ████████ ██  ██████  ███    ██
██ ████  ████ ██   ██ ██      ██      ████  ████ ██      ████   ██    ██    ██   ██    ██    ██ ██    ██ ████   ██
██ ██ ████ ██ ██████  ██      █████   ██ ████ ██ █████   ██ ██  ██    ██    ███████    ██    ██ ██    ██ ██ ██  ██
██ ██  ██  ██ ██      ██      ██      ██  ██  ██ ██      ██  ██ ██    ██    ██   ██    ██    ██ ██    ██ ██  ██ ██
██ ██      ██ ██      ███████ ███████ ██      ██ ███████ ██   ████    ██    ██   ██    ██    ██  ██████  ██   ████
*/

// ----Constructor and Destructor -----
EleNtuplizer::EleNtuplizer(const edm::ParameterSet& iConfig) :
_photonsTag        (consumes<vector<pat::Photon>>                    (iConfig.getParameter<edm::InputTag>("photons"))),
_electronsTag      (consumes<edm::View<reco::GsfElectron>>           (iConfig.getParameter<edm::InputTag>("electrons"))),
_genParticlesTag   (consumes<edm::View<reco::GenParticle>>           (iConfig.getParameter<edm::InputTag>("genParticles"))),
_eleTightIdMapTag  (consumes<edm::ValueMap<bool>>                    (iConfig.getParameter<edm::InputTag>("eleTightIdMap"))),
_eleMediumIdMapTag (consumes<edm::ValueMap<bool>>                    (iConfig.getParameter<edm::InputTag>("eleMediumIdMap"))),
_eleLooseIdMapTag  (consumes<edm::ValueMap<bool>>                    (iConfig.getParameter<edm::InputTag>("eleLooseIdMap"))),
_triggerObjects    (consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getParameter<edm::InputTag>("triggerSet"))),
_triggerBits       (consumes<edm::TriggerResults>                    (iConfig.getParameter<edm::InputTag>("triggerResultsLabel"))),
_L1EGTag           (consumes<l1t::EGammaBxCollection>                (iConfig.getParameter<edm::InputTag>("L1EG"))),
_L1EmuEGTag        (consumes<l1t::EGammaBxCollection>                (iConfig.getParameter<edm::InputTag>("L1EmuEG"))),
_VtxTag            (consumes<std::vector<reco::Vertex>>              (iConfig.getParameter<edm::InputTag>("Vertices")))
{
    _treeName = iConfig.getParameter<std::string>("treeName");
    _processName = iConfig.getParameter<edm::InputTag>("triggerResultsLabel");
    _useGenMatch = iConfig.getParameter<bool>("useGenMatch");
    _useHLTMatch = iConfig.getParameter<bool>("useHLTMatch");
    _hltPrescale = new HLTPrescaleProvider(iConfig, consumesCollector(), *this);

    TString triggerNameTag;
    edm::Service<TFileService> fs;
    _triggerNamesTreeTag = fs -> make<TTree>("triggerNamesTag", "triggerNamesTag");
    _triggerNamesTreeTag -> Branch("triggerNamesTag",&triggerNameTag);

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTListTag = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListTag");
    for (const edm::ParameterSet& parameterSet : HLTListTag)
    {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        triggerNameTag = pSet.hltPath;
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        _parameters_Tag.push_back(pSet);

        _triggerNamesTreeTag->Fill();
    }


    TString triggerNameProbe;
    _triggerNamesTreeProbe = fs -> make<TTree>("triggerNamesProbe", "triggerNamesProbe");
    _triggerNamesTreeProbe -> Branch("triggerNamesProbe",&triggerNameProbe);

    //Building the trigger arrays
    const std::vector<edm::ParameterSet>& HLTListProbe = iConfig.getParameter <std::vector<edm::ParameterSet> > ("triggerListProbe");
    for (const edm::ParameterSet& parameterSet : HLTListProbe) {
        tParameterSet pSet;
        pSet.hltPath = parameterSet.getParameter<std::string>("HLT");
        triggerNameTag = pSet.hltPath;
        pSet.hltFilters1 = parameterSet.getParameter<std::vector<std::string> >("path1");
        pSet.hltFilters2 = parameterSet.getParameter<std::vector<std::string> >("path2");
        pSet.leg1 = parameterSet.getParameter<int>("leg1");
        pSet.leg2 = parameterSet.getParameter<int>("leg2");
        _parameters.push_back(pSet);

        _triggerNamesTreeProbe -> Fill();
    }


    this -> Initialize();
    return;
}

EleNtuplizer::~EleNtuplizer()
{
    delete _hltPrescale;
}

void EleNtuplizer::beginRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    Bool_t changedConfig = false;

    if(!this -> _hltConfig.init(iRun, iSetup, this -> _processName.process(), changedConfig)){
        edm::LogError("HLTMatchingFilter") << "Initialization of HLTConfigProvider failed!!";
        return;
    }

    if(!_hltPrescale->init(iRun, iSetup, _processName.process(), changedConfig)){
        edm::LogError("HLTMatchingFilter") << "Initialization of HLTPrescaleProvider failed!!";
        return;
    }

    const edm::TriggerNames::Strings& triggerNames = _hltConfig.triggerNames();
    std::cout << " ===== LOOKING FOR THE PATH INDEXES =====" << std::endl;
    for (tParameterSet& parameter : _parameters){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
            //std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }

    std::cout << " ===== LOOKING FOR THE PATH INDEXES FOR TAG =====" << std::endl;
    for (tParameterSet& parameter : _parameters_Tag){
        const std::string& hltPath = parameter.hltPath;
        bool found = false;
        for(unsigned int j=0; j < triggerNames.size(); j++)
        {
            //std::cout << triggerNames[j] << std::endl;
            if (triggerNames[j].find(hltPath) != std::string::npos) {
                found = true;
                parameter.hltPathIndex = j;

                std::cout << "### FOUND AT INDEX #" << j << " --> " << triggerNames[j] << std::endl;
            }
        }
        if (!found) parameter.hltPathIndex = -1;
    }
}

void EleNtuplizer::Initialize() {
    _indexevents = 0;
    _runNumber = 0;
    _lumi = 0;
    _PS_column = -1;

    _eleProbePt = -1.;
    _eleProbeEta = -1.;
    _eleProbePhi = -1.;
    _eleProbeSclEt = -1.;
    _eleProbeCharge = 0;
    
    _allEl_Pt.clear();
    _allEl_Eta.clear();
    _allEl_Phi.clear();
    _allEl_SclEt.clear();
    _allEl_Charge.clear();
    _allEl_Size = 0;
    
    _eleTagPt = -1.;
    _eleTagEta = -1.;
    _eleTagPhi = -1.;
    _eleTagCharge = 0;
    _Mee = 0;
    _isTagHLTmatched = 0;
    _isProbeHLTmatched = 0;
    _hltPt = -1;
    _hltEta = 666;
    _hltPhi = 666;
    _genE = -1;
    _genMass = -1;
    _genPt =-1.0;
    _genEta = 666;
    _genPhi = -1;
    _genClosesetZDauEt = -1;
    _isDaughterOfZ = 0.0;
    _isBremSafe = 0.0;
    _l1tPt = -1;
    _l1tEta = 666;
    _l1tPhi = 666;
    _l1tQual = -1;
    _l1tIso = -1;

    _genE = -1;
    _genMass = -1;
    _genPt = 666;
    _genEta = 666;
    _genPhi = -1;

    _l1tEmuPt = -1;
    _l1tEmuEta = 666;
    _l1tEmuPhi = 666;
    _l1tEmuQual = -1;
    _l1tEmuIso = -1;
    _l1tEmuNTT = -1;
    _l1tEmuTowerIEta = 666;
    _l1tEmuTowerIPhi = 666;
    _l1tEmuRawEt = -1;
    _l1tEmuIsoEt = -1;
    _foundTag = 0;  
    _allL1tPt.clear();
    _allL1tEta.clear();
    _allL1tPhi.clear();
    _allL1tIso.clear();         
    _allL1tQual.clear();

    for(unsigned int i=0;i<N_GEN_MAX;i++){
        allPhotonPt[i] = -1;
        allPhotonEta[i] = -1;
        allPhotonPhi[i] = -1;
        allPhotonScEt[i] = -1;
    }

    _allEl_Size = -1;

    /////////////////////////////////////////////////////////////////////
    _isProbeLoose = -1;
    _isProbeTight = -1;
    _isProbeMedium = -1;

    _Unpacked_dR = -1;
    _Emulated_dR = -1;

     _seedTowerEt = -1;
  
    _TowerHoE = -666;

    _iem = -1;
    _ihad = -1;

    _shape = -2; 

    for(unsigned int i=0;i<100;i++){
        _hasL1[i] = -1;
        _hasL1_iso[i] = -1;
    }
    for(unsigned int i=0;i<100;i++){
        _hasL1Emu[i] = -1;
        _hasL1Emu_iso[i] = -1;
        _hasL1_looseiso[i] = -1;
        _hasL1Emu_looseiso[i] = -1;
        _hasL1_tightiso[i] = -1;
        _hasL1Emu_tightiso[i] =-1;
    }
    /////////////////////////////////////////////////////////////////////

}


void EleNtuplizer::beginJob()
{
    edm::Service<TFileService> fs;
    _tree = fs -> make<TTree>(this -> _treeName.c_str(), this -> _treeName.c_str());

    //Branches
    _tree -> Branch("EventNumber",&_indexevents,"EventNumber/l");
    _tree -> Branch("RunNumber",&_runNumber,"RunNumber/I");
    _tree -> Branch("lumi",&_lumi,"lumi/I");
    _tree -> Branch("PS_column",&_PS_column,"PS_column/I");
    
    _tree -> Branch("nPhotons",&nPhotons);
    _tree -> Branch("allPhotonPt"   ,  allPhotonPt ,  "allPhotonPt[nPhotons]/F");
    _tree -> Branch("allPhotonScEt"   ,  allPhotonPt ,  "allPhotonPt[nPhotons]/F");
    _tree -> Branch("allPhotonEta"  ,  allPhotonEta,  "allPhotonEta[nPhotons]/F");
    _tree -> Branch("allPhotonPhi"  ,  allPhotonPhi,  "allPhotonPhi[nPhotons]/F");
    
    _tree -> Branch("nGenParticle",&nGenParticle);
    _tree -> Branch("genParticlePDGID",  genParticlePDGID,"genParticlePDGID[nGenParticle]/F");
    _tree -> Branch("genParticlePt"   ,  genParticlePt ,  "genParticlePt[nGenParticle]/F");
    _tree -> Branch("genParticleEta"  ,  genParticleEta,  "genParticleEta[nGenParticle]/F");
    _tree -> Branch("genParticlePhi"  ,  genParticlePhi,  "genParticlePhi[nGenParticle]/F");
    _tree -> Branch("genParticleMass"  ,  genParticleMass,  "genParticleMass[nGenParticle]/F");
    _tree -> Branch("genParticleMother",  genParticleMother,  "genParticleMother[nGenParticle]/F");

    _tree -> Branch("eleProbeTriggerBits", &_eleProbeTriggerBits, "eleProbeTriggerBits/l");
    _tree -> Branch("eleTagTriggerBits", &_eleTagTriggerBits, "eleTagTriggerBits/l");
    _tree -> Branch("eleProbePt",  &_eleProbePt,  "eleProbePt/F");
    _tree -> Branch("eleProbeEta", &_eleProbeEta, "eleProbeEta/F");
    _tree -> Branch("eleProbePhi", &_eleProbePhi, "eleProbePhi/F");
    _tree -> Branch("eleProbeSclEt",  &_eleProbeSclEt,  "eleProbeSclEt/F");
    _tree -> Branch("eleProbeCharge",  &_eleProbeCharge,  "eleProbeCharge/I");
    _tree -> Branch("eleTagPt",  &_eleTagPt,  "eleTagPt/F");
    _tree -> Branch("eleTagEta", &_eleTagEta, "eleTagEta/F");
    _tree -> Branch("eleTagPhi", &_eleTagPhi, "eleTagPhi/F");
    _tree -> Branch("eleTagCharge",  &_eleTagCharge,  "eleTagCharge/I");
    _tree -> Branch("Mee",  &_Mee,  "Mee/F");
    _tree -> Branch("hltPt",  &_hltPt,  "hltPt/F");
    _tree -> Branch("hltEta", &_hltEta, "hltEta/F");
    _tree -> Branch("hltPhi", &_hltPhi, "hltPhi/F");
    _tree -> Branch("l1tPt",  &_l1tPt,  "l1tPt/F");
    _tree -> Branch("l1tEta", &_l1tEta, "l1tEta/F");
    _tree -> Branch("l1tPhi", &_l1tPhi, "l1tPhi/F");
    _tree -> Branch("l1tQual", &_l1tQual, "l1tQual/I");
    _tree -> Branch("l1tIso", &_l1tIso, "l1tIso/I");
    _tree -> Branch("genE",  &_genE,  "genE/F");
    _tree -> Branch("genMass",  &_genMass,  "genMass/F");
    _tree -> Branch("genPt",  &_genPt,  "genPt/F");
    _tree -> Branch("genEta",  &_genEta,  "genEta/F");
    _tree -> Branch("genPhi",  &_genPhi,  "genPhi/F");
    _tree -> Branch("genClosesetZDauEt",  &_genClosesetZDauEt,  "genClosesetZDauEt/F");
    _tree -> Branch("isDaughterOfZ",  &_isDaughterOfZ,  "isDaughterOfZ/F");
    _tree -> Branch("isBremSafe",  &_isBremSafe,  "isBremSafe/F");
    _tree -> Branch("l1tEmuPt",  &_l1tEmuPt,  "l1tEmuPt/F");
    _tree -> Branch("l1tEmuEta", &_l1tEmuEta, "l1tEmuEta/F");
    _tree -> Branch("l1tEmuPhi", &_l1tEmuPhi, "l1tEmuPhi/F");
    _tree -> Branch("l1tEmuQual", &_l1tEmuQual, "l1tEmuQual/I");
    _tree -> Branch("l1tEmuIso", &_l1tEmuIso, "l1tEmuIso/I");
    _tree -> Branch("l1tEmuNTT", &_l1tEmuNTT, "l1tEmuNTT/I");
    _tree -> Branch("l1tEmuTowerIEta", &_l1tEmuTowerIEta, "l1tEmuTowerIEta/I");
    _tree -> Branch("l1tEmuTowerIPhi", &_l1tEmuTowerIPhi, "l1tEmuTowerIPhi/I");
    _tree -> Branch("l1tEmuRawEt", &_l1tEmuRawEt, "l1tEmuRawEt/I");
    _tree -> Branch("l1tEmuIsoEt", &_l1tEmuIsoEt, "l1tEmuIsoEt/I");
        
    ////////////////////////////////// Pantelis offlineIDs Branches ///////////////////////////
    _tree -> Branch("isProbeLoose", &_isProbeLoose, "isProbeLoose/I");
    _tree -> Branch("isProbeTight", &_isProbeTight, "isProbeTight/I");
    _tree -> Branch("isProbeMedium", &_isProbeMedium, "isProbeMedium/I");
    _tree -> Branch("UnpackedDR", &_Unpacked_dR, "UnpackedDR/F");
    _tree -> Branch("EmulatedDR", &_Emulated_dR, "EmulatedDR/F");
    _tree -> Branch("seedTowerEt", &_seedTowerEt, "seedTowerEt/I");
    _tree -> Branch("TowerHoE", &_TowerHoE,"TowerHoE/I");
    _tree -> Branch("iem", &_iem,"iem/I");
    _tree -> Branch("ihad", &_ihad,"ihad/I");
    _tree -> Branch("shape", &_shape, "shape/I");
    ///////////////////////////////////////////////////////////////////////////////////////////  
         
    ///////////////////////////////All Electrons////////////////////////////////////////////////
    _tree -> Branch("allEl_Pt", &_allEl_Pt);//, "allElectonsPt/array");
    _tree -> Branch("allEl_Eta", &_allEl_Eta);//, "allElectonsEta/array");
    _tree -> Branch("allEl_Phi", &_allEl_Phi);//, "allElectonsPhi/array");
    _tree -> Branch("allEl_SclEt", &_allEl_SclEt);//, "allElectonsSclEt/array");
    _tree -> Branch("allEl_Charge", &_allEl_Charge);//, "allElectonsCharge/array");
    _tree -> Branch("allEl_Size", &_allEl_Size, "allEl_Size/I");

    _tree -> Branch("allL1tPt", &_allL1tPt);
    _tree -> Branch("allL1tEta", &_allL1tEta);
    _tree -> Branch("allL1tPhi", &_allL1tPhi);
    _tree -> Branch("allL1tIso", &_allL1tIso);
    _tree -> Branch("allL1tQual", &_allL1tQual);  
    ///////////////////////////////////////////////////////////////////////////////////////

    _tree -> Branch("isTagHLTmatched", &_isTagHLTmatched, "isTagHLTmatched/O");
    _tree -> Branch("isProbeHLTmatched", &_isProbeHLTmatched, "isProbeHLTmatched/O");
    _tree -> Branch("isOS", &_isOS, "isOS/O");
    _tree -> Branch("foundTag", &_foundTag, "foundTag/I");
    _tree -> Branch("Nvtx", &_Nvtx, "Nvtx/I");


    for(unsigned int i=0;i<100;i++){  
        TString name = Form("hasL1_%i",i);
        _tree -> Branch(name,  &_hasL1[i],  name+"/I");
        TString name_iso = Form("hasL1_iso_%i",i);
        _tree -> Branch(name_iso,  &_hasL1_iso[i],  name_iso+"/I");
        TString name_looseiso = Form("hasL1_looseiso_%i",i);
        _tree -> Branch(name_looseiso,  &_hasL1_looseiso[i],  name_looseiso+"/I");
        TString name_tightiso = Form("hasL1_tightiso_%i",i);
        _tree -> Branch(name_tightiso,  &_hasL1_tightiso[i],  name_tightiso+"/I");


    }
        
    /////////////////////////////// Pantelis Emulator /////////////////////////
    for (unsigned int i=0;i<100;i++){
        TString name = Form("hasL1Emu_%i",i);
        _tree -> Branch(name, &_hasL1Emu[i], name+"/I");
        TString name_iso = Form("hasL1Emu_iso%i",i);
        _tree -> Branch(name_iso, &_hasL1Emu_iso[i], name_iso+"/I");
        TString name_looseiso = Form("hasL1Emu_looseiso%i",i);
        _tree -> Branch(name_looseiso, &_hasL1Emu_looseiso[i], name_looseiso+"/I"); 
        TString name_tightiso = Form("hasL1Emu_tightiso%i",i);
        _tree -> Branch(name_tightiso, &_hasL1Emu_tightiso[i], name_tightiso+"/I");
    }  
    //////////////////////////////////////////////////////////////////////////

    return;
}


void EleNtuplizer::endJob()
{
    return;
}


void EleNtuplizer::endRun(edm::Run const& iRun, edm::EventSetup const& iSetup)
{
    return;
}


void EleNtuplizer::analyze(const edm::Event& iEvent, const edm::EventSetup& eSetup)
{
    this -> Initialize();

    _indexevents = iEvent.id().event();
    _runNumber = iEvent.id().run();
    _lumi = iEvent.luminosityBlock();
    if(!_useGenMatch) _PS_column = _hltPrescale->prescaleSet(iEvent,eSetup);

    // search for the tag in the event
    edm::Handle< vector<pat::Photon> > photons;
    edm::Handle<edm::View<reco::GsfElectron> > electrons;
    edm::Handle<edm::View<reco::GenParticle> > genParticles;
    edm::Handle<edm::ValueMap<bool> > tight_id_decisions;
    edm::Handle<edm::ValueMap<bool> > medium_id_decisions;
    edm::Handle<edm::ValueMap<bool> > loose_id_decisions;
    edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
    edm::Handle<edm::TriggerResults> triggerBits;
    edm::Handle<std::vector<reco::Vertex> >  vertices;

    iEvent.getByToken(_photonsTag, photons);
    iEvent.getByToken(_electronsTag, electrons);
    iEvent.getByToken(_eleTightIdMapTag, tight_id_decisions); 
    iEvent.getByToken(_eleMediumIdMapTag, medium_id_decisions);
    iEvent.getByToken(_eleLooseIdMapTag, loose_id_decisions);
    if(_useHLTMatch) { iEvent.getByToken(_triggerObjects, triggerObjects); }
    iEvent.getByToken(_triggerBits, triggerBits);
    iEvent.getByToken(_VtxTag,vertices);
    if(_useGenMatch) { iEvent.getByToken(_genParticlesTag, genParticles);}


    const edm::TriggerNames &names = iEvent.triggerNames(*triggerBits);

    _Nvtx = vertices->size();

    ////////////////// All Electrons /////////////////////////////////////////////////////////   

    _allEl_Size=electrons->size();
    for(unsigned int k=0; k < electrons->size(); ++k){
        const auto ele = electrons->ptrAt(k);
        _allEl_Pt.push_back(ele->pt());
        _allEl_Eta.push_back(ele->eta());
        _allEl_Phi.push_back(ele->phi());
        _allEl_SclEt.push_back((ele->superCluster()->energy()) / cosh(ele->superCluster()->eta()));
        _allEl_Charge.push_back(ele->charge());
    }

    nPhotons=photons->size();
    for(unsigned int k=0; k<photons->size(); ++k){
        const auto gamma = photons->at(k);
        allPhotonPt[k]=gamma.pt();
        allPhotonEta[k]=gamma.eta();
        allPhotonPhi[k]=gamma.phi();
        allPhotonScEt[k]=gamma.superCluster()->energy() / cosh(gamma.superCluster()->eta());
    }

    for (unsigned int iTag = 0; iTag < electrons->size(); ++iTag){

        const auto eleTag = electrons->ptrAt(iTag);

        int isTagIDMedium = (*medium_id_decisions)[eleTag];
        if(!isTagIDMedium || eleTag->p4().Pt()<30) { continue; }

        for (unsigned int iProbe = 0; iProbe < electrons->size(); ++iProbe){
            // avoid duplicate
            if(iTag==iProbe) { continue; }

            const auto eleProbe = electrons->ptrAt(iProbe);

            // skip the overlap region
            float eleProbeEta = eleProbe->p4().Eta();
            if((abs(eleProbeEta)>1.4442 && abs(eleProbeEta)<1.566)) { continue; }

            // require opposite charge
            bool isOS = (eleTag->charge() / eleProbe->charge() < 0) ? true : false;
            if(!isOS) { continue; }

            // select Z peak
            float Mee = (eleTag->p4() + eleProbe->p4()).M();
            if(!(Mee>60 && Mee<120)) { continue; }

            // apply gen matching
            if(_useGenMatch){
                if(!matchToTruth(eleProbe,genParticles)) { continue; }
            }

            _isOS = isOS;
            _Mee = Mee;
            _isProbeTight = (*tight_id_decisions)[eleProbe];
            _isProbeMedium = (*medium_id_decisions)[eleProbe];
            _isProbeLoose = (*loose_id_decisions)[eleProbe];

            //! TagAndProbe on HLT eles

            _eleProbeTriggerBitSet.reset();
            _eleTagTriggerBitSet.reset();

            if(_useHLTMatch){

                for (pat::TriggerObjectStandAlone  obj : *triggerObjects)
                {

                    if(!obj.hasCollection("hltEgammaCandidates::HLT")) continue;

                    const float dR_tag = deltaR (*eleTag, obj);
                    if ( dR_tag < 0.3)
                    {
                        obj.unpackPathNames(names);

                        const edm::TriggerNames::Strings& triggerNames = names.triggerNames();

                        //Looking for the path
                        unsigned int x = 0;
                        bool foundTrigger = false;  

                        for (const tParameterSet& parameter : _parameters_Tag)
                        {
                            if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
                            {
                                foundTrigger = true;
                                const std::vector<std::string>& filters = (parameter.hltFilters1);
                                if (this -> hasFilters(obj, filters))
                                {
                                    _hltPt = obj.pt();
                                    _hltEta = obj.eta();
                                    _hltPhi = obj.phi();
                                    _eleTagTriggerBitSet[x] = true;             
                                }
                            }
                            x++;
                        }
                        if (foundTrigger){
                            _isTagHLTmatched = true;
                            _foundTag++;
                        }
                    }


                    const float dR_probe = deltaR (*eleProbe, obj);
                                 
                    if ( dR_probe < 0.3)
                    {
                        obj.unpackPathNames(names);
                        const edm::TriggerNames::Strings& triggerNames = names.triggerNames();
                        //Looking for the path
                        unsigned int x = 0;
                        bool foundTrigger = false;
                        for (const tParameterSet& parameter : _parameters)
                        {
                            if ((parameter.hltPathIndex >= 0)&&(obj.hasPathName(triggerNames[parameter.hltPathIndex], true, false)))
                            {
                                foundTrigger = true;              
                                const std::vector<std::string>& filters = (parameter.hltFilters1);
                                if (this -> hasFilters(obj, filters))
                                {
                                    _hltPt = obj.pt();
                                    _hltEta = obj.eta();
                                    _hltPhi = obj.phi();
                                    _eleProbeTriggerBitSet[x] = true;
                                }
                            }
                            x++;
                        }
                        if (foundTrigger) _isProbeHLTmatched = true;
                    }

                }

                if(!(_isTagHLTmatched)) continue;

            }      

            //! TagAndProbe on L1T EG

            edm::Handle< BXVector<l1t::EGamma> >  L1EGHandle;
            iEvent.getByToken(_L1EGTag, L1EGHandle);

            float minDR = 0.3;

            for (l1t::EGammaBxCollection::const_iterator bx0EGIt = L1EGHandle->begin(0); bx0EGIt != L1EGHandle->end(0) ; bx0EGIt++)
            {
                const l1t::EGamma& l1tEG = *bx0EGIt;
                
                _allL1tPt.push_back(l1tEG.pt());
                _allL1tEta.push_back(l1tEG.eta());
                _allL1tPhi.push_back(l1tEG.phi());
                _allL1tIso.push_back(l1tEG.hwIso());
                _allL1tQual.push_back(l1tEG.hwQual());

                const float dR = deltaR(*eleProbe, l1tEG);
                _Unpacked_dR = dR;

                if (dR < minDR)
                {
                    minDR = dR;
                    _l1tPt = l1tEG.pt();
                    _l1tEta = l1tEG.eta();
                    _l1tPhi = l1tEG.phi();
                    _l1tIso = l1tEG.hwIso();
                    _l1tQual = l1tEG.hwQual();
                }
            }

            for(unsigned int i=0;i<100;i++){
                _hasL1[i] = (this -> _l1tPt)>=i;
                _hasL1_iso[i] = ((this -> _l1tIso) && (this -> _l1tPt)>=i);
                _hasL1_looseiso[i] = (((this -> _l1tIso)==2 || (this -> _l1tIso)==3) && (this -> _l1tPt)>=i);
                _hasL1_tightiso[i] = (((this -> _l1tIso)==1 || (this -> _l1tIso)==3) && (this -> _l1tPt)>=i);
            }

            edm::Handle< BXVector<l1t::EGamma> >  L1EmuEGHandle;
            try {iEvent.getByToken(_L1EmuEGTag, L1EmuEGHandle);} catch (...) {;}

            if (L1EmuEGHandle.isValid())
            {
                minDR = 0.3;

                for (l1t::EGammaBxCollection::const_iterator bx0EmuEGIt = L1EmuEGHandle->begin(0); bx0EmuEGIt != L1EmuEGHandle->end(0) ; bx0EmuEGIt++)
                {
                    const l1t::EGamma& l1tEmuEG = *bx0EmuEGIt;

                    const float dR = deltaR(*eleProbe, l1tEmuEG);
                    _Emulated_dR = dR;

                    if (dR < minDR)
                    {
                        minDR = dR;
                        _l1tEmuPt        = l1tEmuEG.pt();
                        _l1tEmuEta       = l1tEmuEG.eta();
                        _l1tEmuPhi       = l1tEmuEG.phi();
                        _l1tEmuIso       = l1tEmuEG.hwIso();
                        _l1tEmuNTT       = l1tEmuEG.nTT();
                        _l1tEmuQual      = l1tEmuEG.hwQual();
                        _l1tEmuTowerIEta = l1tEmuEG.towerIEta();
                        _l1tEmuTowerIPhi = l1tEmuEG.towerIPhi();
                        _l1tEmuRawEt     = l1tEmuEG.rawEt();
                        _l1tEmuIsoEt     = l1tEmuEG.isoEt();
                        // _seedTowerEt     = l1tEmuEG.seedTowerEt(); 
                        _TowerHoE        = l1tEmuEG.towerHoE();  
                        // _iem             = l1tEmuEG.seedTowerEm();
                        // _ihad            = l1tEmuEG.seedTowerHad();
                        _shape           = l1tEmuEG.shape();
                    }
                }
                      
                ///////////////////////// Pantelis Emulator ////////////////////////////////////////
                for(unsigned int i=0;i<100;i++){
                    _hasL1Emu[i] = (this -> _l1tEmuPt)>=i;
                    _hasL1Emu_iso[i] = ((this -> _l1tEmuIso) && ( this -> _l1tEmuPt)>=i);
                    _hasL1Emu_looseiso[i] = (((this -> _l1tEmuIso)==2 || (this -> _l1tEmuIso)==3) && (this -> _l1tEmuPt)>=i);
                    _hasL1Emu_tightiso[i] = (((this -> _l1tEmuIso)==1 || (this -> _l1tEmuIso)==3) && (this -> _l1tEmuPt)>=i);
                } 
                ////////////////////////////////////////////////////////////////////////////////////
                        
            }

            _eleProbePt = eleProbe->pt();
            _eleProbeEta = eleProbe->eta();
            _eleProbePhi = eleProbe->phi();
            _eleProbeSclEt = (eleProbe->superCluster()->energy()) / cosh(eleProbe->superCluster()->eta()) ;
            _eleProbeCharge = eleProbe->charge();


            _eleTagPt = eleTag->pt();
            _eleTagEta = eleTag->eta();
            _eleTagPhi = eleTag->phi();
            _eleTagCharge = eleTag->charge();


            _eleProbeTriggerBits = _eleProbeTriggerBitSet.to_ulong();
            _eleTagTriggerBits = _eleTagTriggerBitSet.to_ulong();

            nGenParticle=0;
            if(_useGenMatch) { addTheGenInfo(genParticles); }

            _tree -> Fill();
        }
    }
}


bool EleNtuplizer::hasFilters(const pat::TriggerObjectStandAlone&  obj , const std::vector<std::string>& filtersToLookFor) {

    const std::vector<std::string>& eventLabels = obj.filterLabels();
    for (const std::string& filter : filtersToLookFor)
    {
        //Looking for matching filters
        bool found = false;
        for (const std::string& label : eventLabels)
        {
            //if (label == std::string("hltOverlapFilterIsoMu17MediumIsoPFTau40Reg"))
            if (label == filter)
            {

                //std::cout << "#### FOUND FILTER " << label << " == " << filter << " ####" << std::endl;
                found = true;
            }
        }
        if(!found) return false;
    }

    return true;
}

void EleNtuplizer::addTheGenInfo( const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles  )
{


    // 
    // Explicit loop and geometric matching method
    //

    // Find the closest status 1 gen electron to the reco electron
    nGenParticle=0;

    for(size_t i=0; i<prunedGenParticles->size();i++){
        const reco::Candidate *particle = &(*prunedGenParticles)[i];
        
        // Drop everything that is not electron or not status 1
        //if( abs(particle->pdgId()) != 11 || particle->status() != 1 || particle->pt()<5)
        if(  particle->pt() < 1.5 )
            continue;
        genParticlePDGID[nGenParticle] = particle->pdgId();
        genParticlePt[nGenParticle] = particle->pt();
        genParticleEta[nGenParticle] = particle->eta();
        genParticlePhi[nGenParticle] = particle->phi();
        genParticleMass[nGenParticle] = particle->mass();
        genParticleMother[nGenParticle] = particle->mother()->pdgId();
            
        nGenParticle++;

        if (nGenParticle > N_GEN_MAX)           
        {
            std::cout<<" nGenParticle > N_GEN_MAX , Break !! \n";
        }
        }
}

bool EleNtuplizer::matchToTruth(const edm::Ptr<reco::GsfElectron> ele, 
        const edm::Handle<edm::View<reco::GenParticle>> &prunedGenParticles){

    // 
    // Explicit loop and geometric matching method
    //

    // Find the closest status 1 gen electron to the reco electron
    double dR = 999;
    const reco::Candidate *closestElectron = 0;
    int particleIndex(-1);
    for(size_t i=0; i<prunedGenParticles->size();i++){
        const reco::Candidate *particle = &(*prunedGenParticles)[i];
        // Drop everything that is not electron or not status 1
        if( abs(particle->pdgId()) != 11 || particle->status() != 1 || particle->pt()<5)
            continue;
        //
        double dRtmp = deltaR( ele->p4(), particle->p4() );
        if( dRtmp < dR ){
            dR = dRtmp;
            this->_isBremSafe=1.0;
            closestElectron = particle;
            particleIndex=i;
        for(size_t ii=0; ii<prunedGenParticles->size();ii++){
            const reco::Candidate *particle2 = &(*prunedGenParticles)[ii];
                if( particle2->pdgId() != 22  ) continue;
                if(particle2->pt() < 1.5 ) continue;
                if(deltaR(particle2->p4(),particle->p4()) < 0.5) continue;
                this->_isBremSafe=0.0;
         }
        }
    }
    // See if the closest electron (if it exists) is close enough.
    // If not, no match found.
    if( !(closestElectron != 0 && dR < 0.1) ) {
        this->_isBremSafe=0.0;
        return false;
    }
    
    const reco::Candidate *particle = &(*prunedGenParticles)[particleIndex];

    _genE    = particle->energy();
    _genMass = particle->mass();
    _genPt   = particle->pt();
    _genEta  = particle->eta();
    _genPhi  = particle->phi();
    if(particle->mother()->pdgId() == 23 ) _isDaughterOfZ=1.0;

    // storing the Z-->ee pt
    dR=0.3;
    for(size_t i=0; i<prunedGenParticles->size();i++){
        const reco::Candidate *particle = &(*prunedGenParticles)[i];
        // Drop everything that is not electron or not status 1
        if( abs(particle->pdgId()) != 11 || particle->mother()->pdgId() != 23 || particle->pt()<5)
            continue;
        //
        double dRtmp = deltaR( ele->p4(), particle->p4() );
        if( dRtmp < dR ){
            dR = dRtmp;
            _genClosesetZDauEt=particle->pt();
        }
    }


    return true;
}


#include <FWCore/Framework/interface/MakerMacros.h>
DEFINE_FWK_MODULE(EleNtuplizer);

#endif //ELENTUPLIZER_H