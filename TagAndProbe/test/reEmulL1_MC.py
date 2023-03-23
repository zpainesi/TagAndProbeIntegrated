import FWCore.Utilities.FileUtils as FileUtils
from Configuration.AlCa.autoCond import autoCond
import FWCore.ParameterSet.VarParsing as VarParsing
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Config as cms
from Configuration.StandardSequences.Eras import eras
import os

options = VarParsing.VarParsing ('analysis')
options.register ('skipEvents',
                  -1, # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.int,          # string, int, or float
                  "Number of events to skip")
options.register ('JSONfile',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "JSON file (empty for no JSON)")
options.register ('caloParams',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "which caloParams to use?")
options.register ('globalTag',
                  "", # default value
                  VarParsing.VarParsing.multiplicity.singleton, # singleton or list
                  VarParsing.VarParsing.varType.string,          # string, int, or float
                  "which globalTag to use?")
options.outputFile = 'NTuple_ZeroBias.root'
options.inputFiles = []
options.maxEvents  = -999
options.parseArguments()

process = cms.Process("ZeroBias",eras.Run3)
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('TagAndProbeIntegrated.TagAndProbe.zeroBias_cff')

base = os.environ["CMSSW_BASE"]
process.GlobalTag.toGet = cms.VPSet(
        cms.PSet(record = cms.string("GEMeMapRcd"),
                       tag = cms.string("GEMeMapDummy"),
                       connect = cms.string("sqlite_file:" + base + "/src/L1Trigger/Configuration/test/GEMeMapDummy.db")
                )
)
process.muonGEMDigis.useDBEMap = True

process.GlobalTag.globaltag = options.globalTag

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        # dummy for creation
        '/store/mc/Run3Winter20DRPremixMiniAOD/VBFHToTauTau_M125_TuneCUETP8M1_14TeV_powheg_pythia8/GEN-SIM-RAW/110X_mcRun3_2021_realistic_v6-v1/20000/2D4F0AC7-86ED-1F45-8E14-58D72D98667C.root'
    ),
)

process.schedule = cms.Schedule()
    
## re-emulate starting from TPs (here we re-emulate also the TPs)
from L1Trigger.Configuration.customiseReEmul import L1TReEmulMCFromRAWSimHcalTP
process = L1TReEmulMCFromRAWSimHcalTP(process)

# from L1Trigger.Configuration.customiseReEmul import L1TReEmulMCFromRAW
# process = L1TReEmulMCFromRAW(process)

process.load(options.caloParams)

############################

if options.JSONfile:
    print("Using JSON: " , options.JSONfile)
    process.source.lumisToProcess = LumiList.LumiList(filename = options.JSONfile).getVLuminosityBlockRange()

if options.inputFiles:
    process.source.fileNames = cms.untracked.vstring(options.inputFiles)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

if options.maxEvents >= -1:
    process.maxEvents.input = cms.untracked.int32(options.maxEvents)
if options.skipEvents >= 0:
    process.source.skipEvents = cms.untracked.uint32(options.skipEvents)

process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)

process.load('EventFilter.L1TRawToDigi.caloStage2Digis_cfi')
process.caloStage2Digis.InputLabel = cms.InputTag('rawDataCollector')

process.p = cms.Path (
    process.RawToDigi +
    process.caloStage2Digis +
    process.L1TReEmul +
    process.NtupleZeroBiasSeq
)
process.schedule = cms.Schedule(process.p) # do my sequence pls

# Silence output
process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

# Adding ntuplizer
process.TFileService=cms.Service('TFileService',fileName=cms.string(options.outputFile))
