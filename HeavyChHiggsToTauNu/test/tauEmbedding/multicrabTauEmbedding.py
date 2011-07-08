#!/usr/bin/env python

import re

from HiggsAnalysis.HeavyChHiggsToTauNu.tools.multicrab import *

#step = "skim"
step = "generation"
#step = "embedding"
#step = "analysis"
#step = "analysisTau"
#step = "signalAnalysis"
#step = "muonAnalysis"
#step = "caloMetEfficiency"

dirPrefix = ""
#dirPrefix = "_TauIdScan"
#dirPrefix = "_iso05"
#dirPrefix = "_test"

#pt = "_pt30"
pt = "_pt40"

if step in ["generation", "embedding", "analysis", "signalAnalysis"]:
    dirPrefix += pt

if step == "signalAnalysis":
    #dirPrefix += "_triggerVertex2010"
    #dirPrefix += "_triggerVertex2011"
    #dirPrefix += "_trigger2010"
    #dirPrefix += "_trigger2011"
    pass

config = {"skim":           {"input": "AOD",                           "config": "muonSkim_cfg.py", "output": "skim.root"},
          "generation":     {"input": "tauembedding_skim_v11",          "config": "embed_HLT.py",    "output": "embedded_HLT.root"},
          "embedding":      {"input": "tauembedding_generation_v11_2"+pt, "config": "embed_RECO.py",   "output": "embedded_RECO.root"},
#          "analysis":       {"input": "tauembedding_embedding_v10_1"+pt,  "config": "embeddingAnalysis_cfg.py"},
          "analysisTau":    {"input": "pattuple_v17",                  "config": "tauAnalysis_cfg.py"},
#          "signalAnalysis": {"input": "tauembedding_embedding_v10_1"+pt,  "config": "../signalAnalysis_cfg.py"},
          "muonAnalysis":   {"input": "tauembedding_skim_v11",          "config": "muonAnalysisFromSkim_cfg.py"},
          "caloMetEfficiency": {"input": "tauembedding_skim_v10",         "config": "caloMetEfficiency_cfg.py"},
          }

crabcfg = "crab.cfg"
if step in ["analysis", "analysisTau", "signalAnalysis", "muonAnalysis", "caloMetEfficiency"]:
    crabcfg = "../crab_analysis.cfg"


multicrab = Multicrab(crabcfg, config[step]["config"], lumiMaskDir="..")

datasetsData2010 = [
    "Mu_136035-144114_Apr21", # HLT_Mu9
    "Mu_146428-147116_Apr21", # HLT_Mu9
    "Mu_147196-149294_Apr21", # HLT_Mu15_v1
]
datasetsData2011 = [
#    "SingleMu_160431-163261_May10",  # HLT_Mu20_v1
#    "SingleMu_163270-163869_May10",  # HLT_Mu24_v2
#    "SingleMu_165088-166150_Prompt", # HLT_Mu30_v3
#    "SingleMu_166161-166164_Prompt", # HLT_Mu40_v1
#    "SingleMu_166346-166346_Prompt", # HLT_Mu40_v2
#    "SingleMu_166374-167043_Prompt", # HLT_Mu40_v1
#    "SingleMu_167078-167784_Prompt", # HLT_Mu40_v1
]
datasetsMCnoQCD = [
#    "TTJets_TuneZ2_Summer11",
#    "WJets_TuneZ2_Summer11",
#    "DYJetsToLL_M50_TuneZ2_Summer11",
#    "TToBLNu_s-channel_TuneZ2_Summer11",
#    "TToBLNu_t-channel_TuneZ2_Summer11",
#    "TToBLNu_tW-channel_TuneZ2_Summer11",
#    "WW_TuneZ2_Summer11",
#    "WZ_TuneZ2_Summer11",
#    "ZZ_TuneZ2_Summer11",
]
datasetsMCQCD = [
#    "QCD_Pt20_MuEnriched_TuneZ2_Summer11",
]
datasetsTest = [
    "TTToHplusBWB_M120_Summer11"
]
    
datasets = []
if step in ["analysis", "analysisTau"]:
    datasets.extend(datasetsMCnoQCD)
else:
#    datasets.extend(datasetsData2010)
    datasets.extend(datasetsData2011)
    datasets.extend(datasetsMCnoQCD)
    datasets.extend(datasetsMCQCD)

#    if step in ["skim", "generation", "embedding", "caloMetEfficiency"]:
#        datasets.extend(datasetsTest)

multicrab.extendDatasets(config[step]["input"], datasets)

multicrab.appendLineAll("GRID.maxtarballsize = 15")
#if step != "skim":
#    multicrab.extendBlackWhiteListAll("ce_white_list", ["jade-cms.hip.fi"])


path_re = re.compile("_tauembedding_.*")
tauname = "_tauembedding_%s_v11_2" % step
if step in ["generation", "embedding"]:
    tauname += pt

reco_re = re.compile("(?P<reco>Reco_v\d+_[^_]+_)")

skimNjobs = {
    "WJets_TuneZ2_Summer11": 490,
    "TTJets_TuneZ2_Summer11": 490,
    "QCD_Pt20_MuEnriched_TuneZ2_Summer11": 400,
    "DYJetsToLL_M50_TuneZ2_Summer11": 150,
    "TToBLNu_s-channel_TuneZ2_Summer11": 100,
    "TToBLNu_t-channel_TuneZ2_Summer11": 100,
    "TToBLNu_tW-channel_TuneZ2_Summer11": 100,
    "WW_TuneZ2_Summer11": 100,
    "WZ_TuneZ2_Summer11": 100,
    "ZZ_TuneZ2_Summer11": 100,
    }

muonAnalysisNjobs = { # goal: 30k events/job
    "Mu_136035-144114_Dec22": 1,
    "Mu_146428-147116_Dec22": 1,
    "Mu_147196-149294_Dec22": 1,
    "SingleMu_160431-161016_Prompt": 1,
    "SingleMu_162803-162828_Prompt": 1,
    "WJets_TuneZ2_Spring11": 4,
    "TTJets_TuneZ2_Spring11": 10,
    "QCD_Pt20_MuEnriched_TuneZ2_Spring11": 20, #?
    "DYJetsToLL_M50_TuneZ2_Spring11": 8,
    "TToBLNu_s-channel_TuneZ2_Spring11": 4,
    "TToBLNu_t-channel_TuneZ2_Spring11": 4,
    "TToBLNu_tW-channel_TuneZ2_Spring11": 4,
    "WW_TuneZ2_Spring11": 6,
    "WZ_TuneZ2_Spring11": 6,
    "ZZ_TuneZ2_Spring11": 6,
    }
   

def modify(dataset):
    name = ""

    path = dataset.getDatasetPath().split("/")
    if step == "skim":
        name = path[2].replace("-", "_")
        name += "_"+path[3]
        name += tauname

        if dataset.isData():
            frun = dataset.getName().split("_")[1].split("-")[0]
            m = reco_re.search(name)
            name = reco_re.sub(m.group("reco")+frun+"_", name)

    else:
        name = path_re.sub(tauname, path[2])
        name = name.replace("local-", "")

    if dataset.isData() and step in ["generation", "embedding"]:
        dataset.appendArg("overrideBeamSpot=1")

    if step == "skim":
        try:
            dataset.setNumberOfJobs(skimNjobs[dataset.getName()])
        except KeyError:
            pass

        #if config[step]["input"] == "AOD":
        #    dataset.extendBlackWhiteList("se_white_list", ["T2_FI_HIP"])
        dataset.useServer(False)

    dataset.appendLine("USER.publish_data_name = "+name)
    dataset.appendLine("CMSSW.output_file = "+config[step]["output"])

def modifyAnalysis(dataset):
    if step == "signalAnalysis":
        dataset.appendArg("tauEmbeddingInput=1")
        dataset.appendArg("doPat=1")
#    if step == "analysisTau":
#        if dataset.getName() == "WJets":
#            dataset.setNumberOfJobs(100)

def modifyMuonAnalysis(dataset):
    try:
        dataset.setNumberOfJobs(muonAnalysisNjobs[dataset.getName()])
    except KeyError:
        pass
    

if step in ["analysis", "analysisTau","signalAnalysis"]:
    multicrab.appendLineAll("CMSSW.output_file = histograms.root")
    multicrab.forEachDataset(modifyAnalysis)
elif step in ["muonAnalysis", "caloMetEfficiency"]:
    multicrab.appendLineAll("CMSSW.output_file = histograms.root")
    multicrab.forEachDataset(modifyMuonAnalysis)
else:
    multicrab.forEachDataset(modify)

#multicrab.extendBlackWhiteListAll("se_black_list", defaultSeBlacklist)

prefix = "multicrab_"+step+dirPrefix

multicrab.createTasks(prefix=prefix)
#multicrab.createTasks(configOnly=True,prefix=prefix)
