# TagAndProbe
Set of tools to evaluate eg/tau trigger performance on T&amp;P, and produce Layer-2 calibrations
This is based on the following two prior tools:
1. https://github.com/jonamotta/TauTagAndProbe
2. https://github.com/jonamotta/TauObjectsOptimization

## Install instructions
```bash
cmsrel CMSSW_13_0_0_pre2
cd CMSSW_13_0_0_pre2/src
cmsenv
git cms-init
git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline l1t-integration-CMSSW_13_0_0_pre2
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v141-CMSSW_13_0_0_pre2
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TCalorimeter.git L1Trigger/L1TCalorimeter/data

git clone git@github.com:jonamotta/TagAndProbeIntegrated.git -b CMSSW_13_0_0_pre2-l1t-integration-v142

git cms-checkdeps -A -a

scram b -j 12
```

L1T emulation relevant GlobalTags in CMSSW_12_4_0 are:
* for run2 data reprocessing '124X_dataRun2_v2'
* for run2 mc '123X_mcRun2_asymptotic_v1'
* for run3 mc '130X_mcRun3_2022_realistic_v3'
* for run3 data, use latest prompt GT here: https://twiki.cern.ch/twiki/bin/view/CMS/LatestOnlineGTs


## Tool utilization
To do the optimization two things are needed:
* L1 objects (sometimes re-emulated) that are extracted from the RAW tier (in principle, non-re-emulated L1 objects can also be extracted from MiniAOD, but for consistency we never do that)
* Offline objects that are extracted from the AOD or MiniAOD tier

### Production of the input objects
To produce the input NTuples to the optimization the `TauTagAndProbe` package is used. The useful scripts for this are mainly in the `test` subfolder.

Jobs on ***RAW*** are submitted using `submitOnTier3_reEmulL1_zeroBias.py` which in turn launches `reEmulL1_X.py`
Before launching this you need to fix
* the Global Tag
* the configuration of the L1Calorimeter (`process.load("L1Trigger.L1TCalorimeter.caloStage2Params_20XX_vX_X_XXX_cfi")`)

Jobs on ***MiniAOD*** are submitted using `submitOnTier3.py` which in turn launches `test_noTagAndProbe.py`
Before launching this you need to fix
* the Global Tag

Jobs on ***Data*** are submitted using `submitOnTier3_reEmulL1_zeroBias.py` which in turn launches `reEmulL1_X.py`.
Before launching this you need to fix
* the `isMC` flag
* the input folder and file list

For Monte Carlo (MC), we implemented a truth matching rather than a Tag & Probe technique which would dramatically and artificially decrease the available statistics.

After having produced the input object `hadd` all the files.

### Optimization
The optimization is run in several sequential steps:
* Merge of the two inputs, match of the L1 objects to the offline ones, compression of the variables
* Calculation of the calibration, pruduction of its LUTs, and its application
* Calculation of the isolation, pruduction of its LUTs, and its application
* Prodution of turnon curves
* Evaluation of the L1 rate

Due to the package's lack of forward-compatibility with CMSSW, the optimzation is run into CMSSW_11_0_2.