lumiMask = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306462_13TeV_PromptReco_Collisions17_JSON.txt"

#================================================================================================ 
# Class Definition
#================================================================================================ 
import os

class Dataset:
    def __init__(self, url, dbs="global", dataVersion="80Xmc", dasQuery="", lumiMask=lumiMask, name=""):
        self.URL = url
        self.DBS = dbs
        self.dataVersion = dataVersion
        if not os.path.dirname(lumiMask):
            lumiMask = os.path.join(os.environ['CMSSW_BASE'],"src/HiggsAnalysis/MiniAOD2TTree/data",lumiMask)
        self.lumiMask = lumiMask
        self.DASquery = dasQuery
	self.name = name

    def isData(self):
        if "data" in self.dataVersion:
            return True
        return False

    def getName(self):
	return self.name


#================================================================================================ 
# Data
#================================================================================================ 
datasetsTauData = []
das = ""
#datasetsTauData.append(Dataset('/Tau/Run2017A-PromptReco-v3/MINIAOD', dataVersion="92Xdata", dasQuery=das, lumiMask="Cert_294927-297723_13TeV_PromptReco_Collisions17_JSON_Run2017A.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017B-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_298996-299185_13TeV_PromptReco_Collisions17_JSON_Run2017B.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017C-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299327-302019_13TeV_PromptReco_Collisions17_JSON_Run2017C.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017D-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302023-302494_13TeV_PromptReco_Collisions17_JSON_Run2017D.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017E-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303572-304797_13TeV_PromptReco_Collisions17_JSON_Run2017E.txt"))
datasetsTauData.append(Dataset('/Tau/Run2017F-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306462_13TeV_PromptReco_Collisions17_JSON_Run2017F.txt"))

datasetsJetHTData = []
das = ""


datasetsMuonData = []
das = ""
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017A-PromptReco-v3/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_294927-297723_13TeV_PromptReco_Collisions17_JSON_Run2017A.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017B-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_297031-297101_13TeV_PromptReco_Collisions17_JSON_Run2017B.txt"))
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017B-PromptReco-v2/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_298678-299329_13TeV_PromptReco_Collisions17_JSON_Run2017B.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017C-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299368-299649_13TeV_PromptReco_Collisions17_JSON_Run2017C.txt"))
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017C-PromptReco-v2/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_299958-300676_13TeV_PromptReco_Collisions17_JSON_Run2017C.txt"))
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017C-PromptReco-v3/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_300742-302029_13TeV_PromptReco_Collisions17_JSON_Run2017C.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017D-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_302023-302494_13TeV_PromptReco_Collisions17_JSON_Run2017D.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017E-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_303572-304797_13TeV_PromptReco_Collisions17_JSON_Run2017E.txt"))
datasetsMuonData.append(Dataset('/SingleMuon/Run2017F-17Nov2017-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_305040-306462_13TeV_PromptReco_Collisions17_JSON_Run2017F.txt"))
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017G-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_306526-306657_13TeV_PromptReco_Collisions17_JSON_Run2017G.txt"))
#datasetsMuonData.append(Dataset('/SingleMuon/Run2017H-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask="Cert_306896-307082_13TeV_PromptReco_Collisions17_JSON_Run2017H.txt"))

datasetsElectronData = []
das = ""
datasetsElectronData.append(Dataset('/SingleElectron/Run2017C-PromptReco-v3/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
datasetsElectronData.append(Dataset('/SingleElectron/Run2017D-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))


datasetsZeroBiasData = []
das = ""
#datasetsZeroBiasData.append(Dataset('/ZeroBias1/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias2/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias3/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias4/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias5/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias6/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias7/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias8/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
#datasetsZeroBiasData.append(Dataset('/ZeroBias9/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))
datasetsZeroBiasData.append(Dataset('/ZeroBias10/Run2017A-PromptReco-v1/MINIAOD', dataVersion="94Xdata", dasQuery=das, lumiMask=lumiMask))





#================================================================================================ 
# MC, 94X
#================================================================================================ 
datasetsSignalTB = []
das = ""


datasetsSignalTauNu = []
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-160_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-200_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-500_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSignalTauNu.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-1000_13TeV_amcatnlo_pythia8/RunIISummer17MiniAOD-NZSFlatPU28to62_92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))


datasetsSingleTop = []
datasetsSingleTop.append(Dataset('/ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_top_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsSingleTop.append(Dataset('/ST_t-channel_antitop_4f_inclusiveDecays_TuneCP5_13TeV-powhegV2-madspin-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsSingleTop.append(Dataset('', dataVersion="94Xmc", dasQuery=das))


datasetsTop = []


datasetsTTJets = []
datasetsTTJets.append(Dataset('/TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v3/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDY = []
das = ""
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v7-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das, name="DYJetsToLL_M-50_ext1"))
#datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10_ext1-v2/MINIAODSIM', dataVersion="94Xmc", dasQuery=das, name="DYJetsToLL_M-50_ext2"))
datasetsDY.append(Dataset('/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDYJetsToQQ = []


datasetsZprime = []


datasetsWJets = []
datasetsWJets.append(Dataset('/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer17MiniAOD-92X_upgrade2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))


datasetsWJetsToQQ = []


datasetsZJetsToQQ = []


datasetsDiboson = []
datasetsDiboson.append(Dataset('/ZZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDiboson.append(Dataset('/WZ_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))
datasetsDiboson.append(Dataset('/WW_TuneCP5_13TeV-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM', dataVersion="94Xmc", dasQuery=das))

datasetsDibosonToQQ = []


datasetsQCD = []


datasetsQCDMuEnriched = []


datasetsQCDbEnriched = []


datasetsQCD_HT_GenJets5 = []


datasetsQCD_HT_BGenFilter = []


datasetsQCD_HT = []


datasetsTTWJetsToQQ = []


datasetsTTTT = []


datasetsTTBB = []


datasetsTTZToQQ = []



datasetsNeutrino = []



#================================================================================================ 
# MC, Trigger Development
#================================================================================================ 
datasetsSignalTauNu_TRGdev = []
das = "https://cmsweb.cern.ch/das/request?view=list&limit=50&instance=prod%2Fglobal&input=dataset%3D%2FChargedHiggs_*%2*%2/RAWAODSIM"
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-80_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_TTToHplusBWB_HplusToTauNu_M-160_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-200_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v2/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-500_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))
datasetsSignalTauNu_TRGdev.append(Dataset('/ChargedHiggs_HplusTB_HplusToTauNu_M-1000_13TeV_amcatnlo_pythia8/PhaseIFall16MiniAOD-FlatPU28to62HcalNZSRAW_PhaseIFall16_90X_upgrade2017_realistic_v6_C1-v1/MINIAODSIM', dataVersion="80Xmc", dasQuery=das))


#================================================================================================ 
# Dataset Grouping
#================================================================================================ 
tauLegDatasets = []
#tauLegDatasets.extend(datasetsZeroBiasData)
tauLegDatasets.extend(datasetsMuonData)
tauLegDatasets.extend(datasetsDY)
#tauLegDatasets.extend(datasetsZprime)
# tauLegDatasets.extend(datasetsWJets_reHLT)
# tauLegDatasets.extend(datasetsQCDMuEnriched_reHLT)
# tauLegDatasets.extend(datasetsH125)

tauLegSingleElectronDatasets = []
tauLegSingleElectronDatasets.extend(datasetsElectronData)

metLegDatasets = []
metLegDatasets.extend(datasetsTauData)
metLegDatasets.extend(datasetsDY)
metLegDatasets.extend(datasetsTop)
#metLegDatasets.extend(datasetsSingleTop)
metLegDatasets.extend(datasetsWJets)
metLegDatasets.extend(datasetsQCD)

l1Datasets = []
l1Datasets.extend(datasetsZeroBiasData)
l1Datasets.extend(datasetsNeutrino)
l1Datasets.extend(datasetsQCD)

signalAnalysisDatasets = []
signalAnalysisDatasets.extend(datasetsTauData)
signalAnalysisDatasets.extend(datasetsDY) 
signalAnalysisDatasets.extend(datasetsTTJets)
#signalAnalysisDatasets.extend(datasetsTop)
signalAnalysisDatasets.extend(datasetsSingleTop)
signalAnalysisDatasets.extend(datasetsWJets)  
signalAnalysisDatasets.extend(datasetsDiboson)
#signalAnalysisDatasets.extend(datasetsQCD)
#signalAnalysisDatasets.extend(datasetsSignalTauNu)
#signalAnalysisDatasets.extend(datasetsSignalTB)
#signalAnalysisDatasets.extend(datasetsSignalTauNu_TRGdev)

#signalAnalysisDatasets.extend(datasetsDY_reHLT)
#signalAnalysisDatasets.extend(datasetsTop_reHLT)
#signalAnalysisDatasets.extend(datasetsWJets_reHLT)
#signalAnalysisDatasets.extend(datasetsDiboson_reHLT)
##signalAnalysisDatasets.extend(datasetsQCD_reHLT)
#signalAnalysisDatasets.extend(datasetsSignalTauNu_reHLT)
##signalAnalysisDatasets.extend(datasetsSignalTB_reHLT)


hplus2tbAnalysisDatasets = []
hplus2tbAnalysisDatasets.extend(datasetsJetHTData)
hplus2tbAnalysisDatasets.extend(datasetsSignalTB)
hplus2tbAnalysisDatasets.extend(datasetsTop)
hplus2tbAnalysisDatasets.extend(datasetsSingleTop)
hplus2tbAnalysisDatasets.extend(datasetsDYJetsToQQ)
hplus2tbAnalysisDatasets.extend(datasetsWJetsToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsZJetsToQQ_reHLT) # PUMoriond17?
hplus2tbAnalysisDatasets.extend(datasetsDibosonToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsQCD)
hplus2tbAnalysisDatasets.extend(datasetsQCD_HT)
hplus2tbAnalysisDatasets.extend(datasetsQCDbEnriched)
hplus2tbAnalysisDatasets.extend(datasetsTTWJetsToQQ)  
hplus2tbAnalysisDatasets.extend(datasetsTTTT) 
# hplus2tbAnalysisDatasets.extend(datasetsTTBB) # PUMoriond17?
hplus2tbAnalysisDatasets.extend(datasetsTTZToQQ)
# hplus2tbAnalysisDatasets.extend(datasetsQCDMuEnriched)
# hplus2tbAnalysisDatasets.extend(datasetsQCD_HT_BGenFilter) 
# hplus2tbAnalysisDatasets.extend(datasetsQCD_HT_GenJets5) 
# hplus2tbAnalysisDatasets.extend(datasetsTTJets) #-ve weights


#================================================================================================ 
# Class Definition
#================================================================================================ 
class DatasetGroup:
    def __init__(self, analysis):
        self.verbose   = False
        self.analysis  = analysis
        self.GroupDict = {}
        self.CreateGroups()

    def SetVerbose(verbose):
        self.verbose = verbose
        return


    def Verbose(self, msg, printHeader=False):
        '''
        Simple print function. If verbose option is enabled prints, otherwise does nothing.
        '''
        if not self.verbose:
            return
        self.Print(msg, printHeader)
        return


    def Print(self, msg, printHeader=True):
        '''
        Simple print function. If verbose option is enabled prints, otherwise does nothing.
        '''
        fName = __file__.split("/")[-1]
        cName = self.__class__.__name__
        name  = fName + ": " + cName
        if printHeader:
                print "=== ", name
        print "\t", msg
        return


    def CreateGroups(self):
        '''
        Create dataset grouping in a dictionary for easy access.
        '''

        analyses = ["SignalAnalysis", "Hplus2tbAnalysis", "TauLeg", "TauLegSingleElectron", "METLeg", "L1Study", "All"]
        if self.analysis not in analyses:
            raise Exception("Unknown analysis \"%s\". Please select one of the following: \"%s" % (self.analysis, "\", \"".join(analyses) + "\".") )

        self.GroupDict["SignalAnalysis"]   = signalAnalysisDatasets
        self.GroupDict["Hplus2tbAnalysis"] = hplus2tbAnalysisDatasets
        self.GroupDict["TauLeg"]           = tauLegDatasets
        self.GroupDict["TauLegSingleElectron"] = tauLegSingleElectronDatasets
        self.GroupDict["METLeg"]           = metLegDatasets
        self.GroupDict["L1Study"]          = l1Datasets
        self.GroupDict["All"]              = signalAnalysisDatasets + hplus2tbAnalysisDatasets + metLegDatasets + metLegDatasets
        return


    def GetDatasetList(self):
        '''
        Return the dataset list according to the analysis name. 
        Uses pre-defined dictionary mapping: analysis->dataset list
        '''
        return self.GroupDict[self.analysis]


    def PrintDatasets(self, printHeader=False):
        '''
        Print all datasets for given analysis
        '''
        datasetList = self.GroupDict[self.analysis]

        if printHeader==True:
            self.Print("The datasets for analysis \"%s\" are:\n\t%s" % (self.analysis, "\n\t".join(str(d.URL) for d in datasetList) ), True)
        else:
            self.Print("\n\t".join(str(d.URL) for d in datasetList), False)
        return
