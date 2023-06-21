import FWCore.ParameterSet.Config as cms

print("Running on data")

##------------------------------------------------------------------------------------------------
## good taus
goodTaus = cms.EDFilter("PATTauRefSelector",
    src = cms.InputTag("slimmedTaus"),
    cut = cms.string(
        'pt>10 && abs(eta)<2.1 '
        # '&& abs(charge)>0 && abs(charge)<2 ' #sometimes 2 prongs have charge != 1
        # '&& tauID("decayModeFinding")>0.5 '
        # '&& tauID("byMediumDeepTau2017v2p1VSjet")>0.5 '
        # '&& tauID("byMediumDeepTau2017v2p1VSmu")>0.5 '
        # '&& tauID("byLooseDeepTau2017v2p1VSe")>0.5 '
    ),
    filter = cms.bool(False)
)

#------------------------------------------------------------------------------------------------
## good eles
goodEles = cms.EDFilter("PATElectronSelector",
    src = cms.InputTag("slimmedElectrons"),
    cut = cms.string(
        '(abs(eta)<1.4442 || ( abs(eta)>1.566 && abs(eta)<2.5 )) && pt> 12 && pt<23'
    ),
    filter = cms.bool(False)
)

##------------------------------------------------------------------------------------------------
## good mus (tight)
goodMus = cms.EDFilter("PATMuonRefSelector",
    src = cms.InputTag("slimmedMuons"),
    cut = cms.string(
        'abs(dB)<0.2'
        # 'pt>10 && abs(eta)<2.4'
        # '&& (isPFMuon>0) && (isGlobalMuon = 1) && (numberOfMatchedStations() > 1)'
        # '&& (abs(dB)<0.2)  && ((isolationR03().sumPt/pt)<0.1)'
        # '&& (globalTrack().normalizedChi2() < 10) && (globalTrack().hitPattern().numberOfValidMuonHits()>0)'
        # '&& (innerTrack().hitPattern().numberOfValidPixelHits() > 0)&& (innerTrack().hitPattern().trackerLayersWithMeasurement() > 5)'
    ),
    filter = cms.bool(False)
)

## good mus (loose)
# looseMus = cms.EDFilter("PATMuonSelector",
#     src = cms.InputTag("slimmedMuons", "", "RECO"),
#     cut = cms.string(
#         'pt>20 && abs(eta)<2.4'
#         'charge!=0'
#     ),
#     filter = cms.bool(True)
# )
# allPatTracks = patGenericParticles.clone(
#     src = cms.InputTag("looseMus"),
#     # isolation configurables
#     userIsolation = cms.PSet(
#         tracker = cms.PSet(
#         veto = cms.double(0.015),
#         src = cms.InputTag("tkIsoDepositTk"),
#         deltaR = cms.double(0.3),
#         ),
#       ),
#     isoDeposits = cms.PSet(
#         tracker = cms.InputTag("tkIsoDepositTk"),
#         ),
#     )
# goodMus = cms.EDFilter("PATGenericParticleSelector",  
#     src = cms.InputTag("allPatTracks"), 
#     cut = cms.string("(userIsolation('pat::TrackIso')/pt)<0.4"),
#     filter = cms.bool(True)
#     )

##------------------------------------------------------------------------------------------------
## good jets
goodJets = cms.EDFilter("PATJetSelector",
    src = cms.InputTag("slimmedJets"),
    cut = cms.string(
        'pt>20.'
        # 'pt>30 && abs(eta)<5.2'
        # '&& isPFJet > 0.5 '
    ),
    filter = cms.bool(False)
)

##------------------------------------------------------------------------------------------------
## EDAnalyzer
ZeroBias_Timing = cms.EDAnalyzer("ZeroBias_Timing",
    treeName = cms.string("ZeroBias"),

    l1uGT = cms.InputTag("gtStage2Digis"),
    
    l1Mu  = cms.InputTag("gmtStage2Digis",  "Muon"),
    l1EG  = cms.InputTag("caloStage2Digis", "EGamma"),
    l1Tau = cms.InputTag("caloStage2Digis", "Tau"),
    l1Jet = cms.InputTag("caloStage2Digis", "Jet"),
    l1Sum = cms.InputTag("caloStage2Digis", "EtSum"),

    mu  = cms.InputTag("goodMus"),
    eG  = cms.InputTag("goodEles"),
    tau = cms.InputTag("goodTaus"),
    jet = cms.InputTag("goodJets"),
    sum = cms.InputTag("slimmedMETs"),

    eleTightId  = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp80"),
    eleMediumId = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wp90"),
    eleLooseId  = cms.InputTag("egmGsfElectronIDs:mvaEleID-Fall17-iso-V2-wpLoose"),

    METFiltersPAT = cms.InputTag("TriggerResults::PAT"),
    METFiltersRECO = cms.InputTag("TriggerResults::RECO"),

    stageL1Trigger = cms.uint32(2)
)


sequence = cms.Sequence(
    goodMus   +
    goodEles  +
    goodTaus  +
    goodJets  +
    ZeroBias_Timing
)
