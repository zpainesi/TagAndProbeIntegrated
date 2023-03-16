import FWCore.ParameterSet.Config as cms

print("Running on MC w/o T&P")


# Not used as this is nt tag and probe
HLTLISTTAG = cms.VPSet(
    cms.PSet (
        HLT = cms.string("HLT_Ele27_WPTight_Gsf_v"),
        path1 = cms.vstring ("hltEle27WPTightGsfTrackIsoFilter"), #FIXME: to check
        path2 = cms.vstring (""),
        leg1 = cms.int32(11),
        leg2 = cms.int32(999)
        ),
)

HLTLISTPROBE = cms.VPSet(
    cms.PSet (
        HLT = cms.string("HLT_Ele27_WPTight_Gsf_v"),
        path1 = cms.vstring ("hltEle27WPTightGsfTrackIsoFilter"), #FIXME: to check
        path2 = cms.vstring (""),
        leg1 = cms.int32(11),
        leg2 = cms.int32(999)
        ),
)




Ntuplizer_noTagAndProbe = cms.EDAnalyzer("EleNtuplizer_noTagAndProbe",
    treeName = cms.string("TagAndProbe"),
    electrons      = cms.InputTag("gedGsfElectrons"),  # AOD
    # electrons      = cms.InputTag("slimmedElectrons"),   # MINIAOD
    genParticles   = cms.InputTag("genParticles"),     # AOD
    # genParticles   = cms.InputTag("prunedGenParticles"), # MINIAOD
    eleMediumIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-GeneralPurpose-V1-wp90"),
    eleLooseIdMap = cms.InputTag("egmGsfElectronIDs:mvaEleID-Spring16-HZZ-V1-wpLoose"),
    triggerSet = cms.InputTag("selectedPatTrigger"),
    triggerResultsLabel = cms.InputTag("TriggerResults", "", "HLT"),    
    L1EG = cms.InputTag("caloStage2Digis", "EGamma", "RECO"),
    L1EmuEG = cms.InputTag("simCaloStage2Digis", "MP"),
    Vertexes = cms.InputTag("offlinePrimaryVertices"),
    triggerListTag = HLTLISTTAG,
    triggerListProbe = HLTLISTPROBE,
    useGenMatch = cms.bool(True),
    useHLTMatch = cms.bool(False)
)



NtupleSeq = cms.Sequence(
    Ntuplizer_noTagAndProbe
)