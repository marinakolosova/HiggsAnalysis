#!/usr/bin/env python

import os
import sys

from ROOT import *

import HiggsAnalysis.HeavyChHiggsToTauNu.tools.dataset as dataset
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.counter as counter
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.plots as plots

from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.DatacardColumn import DatacardColumn
from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.Extractor import *
from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.TableProducer import *
from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.TableProducer import *
from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.QCDfactorised import QCDfactorisedColumn,QCDfactorisedExtractor
from HiggsAnalysis.HeavyChHiggsToTauNu.tools.ShellStyles import *

import HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.MulticrabPathFinder as PathFinder

import HiggsAnalysis.HeavyChHiggsToTauNu.tools.dataset as dataset

from HiggsAnalysis.HeavyChHiggsToTauNu.tools.aux import sort

# main class for generating the datacards from a given cfg file

class DatacardQCDMethod:
    UNKNOWN = 0
    FACTORISED = 1
    INVERTED = 2

class DatacardDatasetMgrSourceType:
    SIGNALANALYSIS = 0
    EMBEDDING = 1
    QCDMEASUREMENT =2

class DatasetMgrCreatorManager:
    def __init__(self, opts, config, signalDsetCreator, embeddingDsetCreator, qcdDsetCreator, qcdMethodType):
        self._dsetMgrCreators = [signalDsetCreator, embeddingDsetCreator, qcdDsetCreator]
        self._dsetMgrs = []
        self._luminosities = []
        self._mainCounterTables = []
        self._qcdMethodType = qcdMethodType
        if config.ToleranceForLuminosityDifference == None:
            raise Exception(ErrorLabel()+"Input datacard should contain entry for ToleranceForLuminosityDifference (for example: ToleranceForLuminosityDifference=0.01)!"+NormalStyle())
        self._toleranceForLuminosityDifference = config.ToleranceForLuminosityDifference
        self._optionDebugConfig = opts.debugConfig

    def closeManagers(self):
        for dMgr in self._dsetMgrs:
            if dMgr != None:
                dMgr.close()

    def obtainDatasetMgrs(self, era, searchMode, optimizationMode):
        if len(self._dsetMgrs) > 0:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::obtainDatasetMgrs(...) was already called (dsetMgrs exist)!"+NormalStyle())
        for i in range(0, len(self._dsetMgrCreators)):
            if self._dsetMgrCreators[i] != None:
                # Create DatasetManager object and set pointer to the selected era, searchMode, and optimizationMode
                myDsetMgr = self._dsetMgrCreators[i].createDatasetManager(dataEra=era,searchMode=searchMode,optimizationMode=optimizationMode)
                # Normalize
                myDsetMgr.updateNAllEventsToPUWeighted()
                # Obtain luminosity
                myDsetMgr.loadLuminosities()
                myLuminosity = 0.0
                myDataDatasets = myDsetMgr.getDataDatasets()
                #print "datasets:",myDsetMgr.getDatasetNames()
                #print "datasets:",myDsetMgr.getAllDatasetNames()
                for d in myDataDatasets:
                    myLuminosity += d.getLuminosity()
                self._luminosities.append(myLuminosity)
                # Merge divided datasets
                plots.mergeRenameReorderForDataMC(myDsetMgr)
                # Show info of available datasets
                print HighlightStyle()+"Dataset merging structure for %s:%s"%(self.getDatasetMgrLabel(i),NormalStyle())
                myDsetMgr.printDatasetTree()
                # Store DatasetManager
                self._dsetMgrs.append(myDsetMgr)
            else:
                # No dsetMgrCreator, append zero pointers to retain list dimension
                self._dsetMgrs.append(None)
                self._luminosities.append(None)
        self._checkLuminosityMatching()

    def cacheMainCounterTables(self):
        # Note: needs to be called after all merging operations have been done
        for i in range(0,len(self._dsetMgrs)):
            if self.getDatasetMgr(i) == None:
                self._mainCounterTables.append(None)
            else:
                # Obtain main counter tables
                myEventCounter = counter.EventCounter(self.getDatasetMgr(i), countNameFunction=None, counters=None, mainCounterOnly=True)
                myEventCounter.normalizeMCToLuminosity(self.getLuminosity(i))
                self._mainCounterTables.append(myEventCounter.getMainCounterTable())

    def getNmax(self):
        return len(self._dsetMgrs)

    # Returns datasetMgr object, index must conform to DatacardDatasetMgrSourceType. Note: can return also a None object
    def getDatasetMgr(self, i):
        if len(self._dsetMgrs) == 0:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::obtainDatasetMgrs(...) needs to be called first!")
        if i < 0 or i >= len(self._dsetMgrs):
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::getDatasetMgr(...) index = %d is out of range!"%i)
        return self._dsetMgrs[i]

    def getDatasetMgrLabel(self, i):
        if i == DatacardDatasetMgrSourceType.SIGNALANALYSIS:
            return "Signal analysis"
        elif i == DatacardDatasetMgrSourceType.EMBEDDING:
            return "Embedding"
        elif i == DatacardDatasetMgrSourceType.QCDMEASUREMENT:
            if self._qcdMethodType == DatacardQCDMethod.FACTORISED:
                return "QCDfactorised"
            if self._qcdMethodType == DatacardQCDMethod.INVERTED:
                return "QCDinverted"
        else:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::getDatasetMgrLabel(...) index = %d is out of range!!"%i)

    def getLuminosity(self, i):
        if len(self._luminosities) == 0:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::obtainDatasetMgrs(...) needs to be called first!")
        if i < 0 or i >= len(self._dsetMgrs):
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::getLuminosity(...) index = %d is out of range!"%i)
        return self._luminosities[DatacardDatasetMgrSourceType.SIGNALANALYSIS]

    def getMainCounterTable(self, i):
        if len(self._mainCounterTables) == 0:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::cacheMainCounterTables(...) needs to be called first!")
        if i < 0 or i >= len(self._dsetMgrs):
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::getMainCounterTable(...) index = %d is out of range!"%i)
        return self._mainCounterTables[i]

    # Merges the list of datasets (if they exist) into one object. The merged group is then used to access counters and histograms
    def mergeDatasets(self, i, mergeGroupLabel, searchNames):
        if self.getDatasetMgr(i) == None:
            return
        # Obtain all dataset names
        myAllDatasetNames = self.getDatasetMgr(i).getAllDatasetNames()
        # Find datasets matching to search conditions
        myMatchedDatasetNames = []
        for searchName in searchNames:
            myFoundStatus = False
            for dset in myAllDatasetNames:
                if searchName in dset:
                    # Replace files existing in _physicalMcAdd
                    myReplacedStatus = False
                    for key in plots._physicalMcAdd:
                        if dset == key:
                            myReplacedStatus = True
                            if plots._physicalMcAdd[key] in myResult:
                                print "    Replaced dataset '%s'->'%s', exists already"%(key,plots._physicalMcAdd[key])
                            else:
                                print "    Replaced dataset '%s'->'%s'"%(key,plots._physicalMcAdd[key])
                                myMatchedDatasetNames.append(dset)
                    if not myReplacedStatus:
                        myMatchedDatasetNames.append(dset)
                    myFoundStatus = True
            if not myFoundStatus and len(myAllDatasetNames) > 0:
                print ErrorLabel()+" Dataset group '%s': cannot find datasetDefinition '%s'!"%(mergeGroupLabel,searchName)
                print "Options are: %s"%(', '.join(map(str, myAllDatasetNames)))
                raise Exception()
        #if self._optionDebugConfig:
            #print "Added to data group '%s' the following datasets:"%(mergeGroupLabel)
            #for n in myMatchedDatasetNames:
                #print "  "+n
        # Now do the merge
        self.getDatasetMgr(i).merge(mergeGroupLabel, myMatchedDatasetNames, silent=True)

    def printDatasetMgrContents(self):
        for i in range(0,len(self._dsetMgrs)):
            if self.getDatasetMgr(i) != None:
                print "DatasetMgr contains following datasets for '%s'"%self.getDatasetMgrLabel(i)
                self.getDatasetMgr(i).printInfo()

    def _checkLuminosityMatching(self):
        # Print info of luminosity
        print "\nLuminosity is set to:"
        for i in range(0,len(self._luminosities)):
            if self._luminosities[i] != None:
                print "  %s: %s%f 1/pb%s"%(self.getDatasetMgrLabel(i),HighlightStyle(),self._luminosities[i],NormalStyle())
        # Compare luminosities to signal analysis
        if len(self._luminosities) == 0:
            raise Exception(ErrorLabel()+"DatasetMgrCreatorManager::obtainDatasetMgrs(...) needs to be called first!")
        mySignalLuminosity = self._luminosities[DatacardDatasetMgrSourceType.SIGNALANALYSIS]
        for i in range(1,len(self._luminosities)):
            if self._luminosities[i] != None:
                myDiff = abs(self._luminosities[i] / mySignalLuminosity - 1.0)
                if myDiff > self._toleranceForLuminosityDifference:
                    raise Exception(ErrorLabel()+"signal and embedding luminosities differ more than 1 %!")
                elif myDiff > 0.0001:
                    print WarningLabel()+"%s and %s luminosities differ slightly (%.2f %%)!"%(self.getDatasetMgrLabel(DatacardDatasetMgrSourceType.SIGNALANALYSIS),self.getDatasetMgrLabel(i),myDiff*100.0)
        print ""

class DataCardGenerator:
    def __init__(self, opts, config, qcdMethod):
        self._opts = opts
        self._config = config
        self._QCDMethod = qcdMethod
        # Check config file
        #self._checkCfgFile() #FIXME
        print "Input datacard read and passed the tests"
        # Manager for datasetMgrCreators (DatasetMgrCreatorManager object)
        self._dsetMgrManager = None
        # Datacard columns
        self._observation = None
        self._columns = []
        # Extractor objects
        self._extractors = []
        # Control plot extractors
        self._controlPlotExtractors = []
        self._controlPlotExtractorsEWKfake = []
        # 
        #self._replaceEmbeddingWithMC = False
        #self._doSignalAnalysis = True
        #self._doEmbeddingAnalysis = True
        #self._doQCDFactorised = False
        #self._variationPostfix = optimisationVariation
        #self._dataEra = era
        #if self._QCDMethod == DatacardQCDMethod.FACTORISED:
            #self._doQCDFactorised = True
        #self._doQCDInverted = False
        #if self._QCDMethod == DatacardQCDMethod.INVERTED:
            #self._doQCDInverted = True
        # Override options from command line (not used at the moment)
        #self.overrideConfigOptionsFromCommandLine()
        #if self._QCDMethod != DatacardQCDMethod.FACTORISED and self._QCDMethod != DatacardQCDMethod.INVERTED:
            #raise Exception(ErrorLabel()+"QCD method was not properly specified when creating DataCardGenerator!")
        #if self._config.OptionReplaceEmbeddingByMC != None:
            #self._replaceEmbeddingByMC = self._config.OptionReplaceEmbeddingByMC

        # Check that all necessary parameters have been specified in config file
        myStatus = self._checkCfgFile()
        if not myStatus:
            myMsg = "Datacards will not be created for "
            if self._QCDMethod != DatacardQCDMethod.FACTORISED:
                myMsg += " QCD factorised"
            elif self._QCDMethod != DatacardQCDMethod.INVERTED:
                myMsg += " QCD inverted"
            print myMsg+" (if this is not intented, check your config!)\n"
            return
        # Construct prefix for output name
        myOutputPrefix = ""
        if self._QCDMethod == DatacardQCDMethod.FACTORISED:
            myOutputPrefix += "QCDfact"
        elif self._QCDMethod == DatacardQCDMethod.INVERTED:
            myOutputPrefix += "QCDinv"
        if self._config.OptionReplaceEmbeddingByMC:
            myOutputPrefix += "_MCEWK"
        self._outputPrefix = myOutputPrefix

        myMassRange = str(self._config.MassPoints[0])
        if len(self._config.MassPoints) > 0:
            myMassRange += "-"+str(self._config.MassPoints[len(self._config.MassPoints)-1])
        print "Cards will be generated for "+HighlightStyle()+myOutputPrefix+NormalStyle()+" in mass range "+HighlightStyle()+myMassRange+" GeV"+NormalStyle()

    #def overrideConfigOptionsFromCommandLine(self):
        # Obtain QCD measurement method

    def setDsetMgrCreators(self, signalDsetCreator, embeddingDsetCreator, qcdDsetCreator):
        self._dsetMgrManager = DatasetMgrCreatorManager(self._opts, self._config, signalDsetCreator, embeddingDsetCreator, qcdDsetCreator, self._QCDMethod)
        print "DatasetManagerCreator objects passed"

    def doDatacard(self, era, searchMode, optimizationMode, mcrabInfoOutput):
        # Prepend era, searchMode, and optimizationMode to prefix
        s = "%s_%s_"%(era, searchMode)
        if optimizationMode == "":
            s += "nominal"
        else:
            s += "%s"%optimizationMode
        self._outputPrefix = s+"_"+self._outputPrefix

        # Get dataset managers for the era / searchMode / optimizationMode combination
        self._dsetMgrManager.obtainDatasetMgrs(era, searchMode, optimizationMode)

        # Create columns (dataset groups)
        self.createDatacardColumns()
        self.checkDatacardColumns()

        # create extractors and control plot extractors
        self.createExtractors()
        self.createControlPlots()

        # do data mining to cache results into datacard column objects
        self.doDataMining()

        # Make datacards
        myProducer = TableProducer(opts=self._opts, config=self._config, outputPrefix=self._outputPrefix,
                                   luminosity=self._dsetMgrManager.getLuminosity(DatacardDatasetMgrSourceType.SIGNALANALYSIS),
                                   observation=self._observation, datasetGroups=self._columns, extractors=self._extractors,
                                   mcrabInfoOutput=mcrabInfoOutput)
        # Close files
        #self.closeFiles() # Do not close, will crash if done so, because configInfo histogram will not be found anymore !!!

        # Return name of output directory
        return myProducer.getDirectory()

    def _checkCfgFile(self):
        mymsg = ""
        if self._config.DataCardName == None:
            mymsg += "- missing field 'DataCardName' (string, describes the name of the datacard)\n"
        if self._config.Path == None:
            mymsg += "- missing field 'Path' (string, path to directory containing all multicrab directories to be used for datacards)\n"
        elif not os.path.exists(self._config.Path):
            mymsg += "- 'Path' points to directory that does not exist!\n"
        if self._config.MassPoints == None:
            mymsg += "- missing field 'MassPoints' (list of integers, mass points for which datacard is generated)!\n"
        elif len(self._config.MassPoints) == 0:
            mymsg += "- field 'MassPoints' needs to have at least one entry! (list of integers, mass points for which datacard is generated)\n"
        if self._config.BlindAnalysis == None:
            mymsg += "- field 'BlindAnalysis' needs to be set as True or False!\n"
        #if self._config.SignalAnalysis == None:
            #print WarningStyle()+"Warning: The field 'SignalAnalysis' is not specified or empty in the config file, signal analysis will be ignored"+NormalStyle()
            #self._doSignalAnalysis = False
        #if self._config.EmbeddingAnalysis == None:
            #print WarningStyle()+"Warning: The field 'EmbeddingAnalysis' is not specified or empty in the config file, embedding analysis will be ignored"+NormalStyle()
            #self._doEmbeddingAnalysis = False
            #mymsg += "- missing field 'SignalAnalysis' (string, name of EDFilter/EDAnalyzer process that produced the root files for signal analysis)\n"
        #if self._QCDMethod == DatacardQCDMethod.FACTORISED and self._config.QCDFactorisedAnalysis == None:
            #print WarningStyle()+"Warning: The field 'QCDFactorisedAnalysis' is not specified or empty in the config file, QCD factorised analysis will be ignored"+NormalStyle()
            #self._doQCDFactorised = False
            #return False
        #if self._QCDMethod == DatacardQCDMethod.INVERTED and self._config.QCDInvertedAnalysis == None:
            #print WarningStyle()+"Warning: The field 'QCDInvertedAnalysis' is not specified or empty in the config file, QCD inverted analysis will be ignored"+NormalStyle()
            #self._doQCDInverted = False
            #return False
        #if self._QCDMethod == DatacardQCDMethod.UNKNOWN:
            #mymsg += "- missing field 'QCDMeasurementMethod' (string, name of QCD measurement method, options: 'QCD factorised' or 'QCD inverted')\n"
        #if self._config.SignalRateCounter == None:
            #mymsg += "- missing field 'SignalRateCounter' (string, label of counter to be used for rate)\n"
        #if self._config.FakeRateCounter == None:
            #mymsg += "- missing field 'FakeRateCounter' (string, label of counter to be used for rate)\n"
        #if self._config.SignalShapeHisto == None:
            #mymsg += "- missing field 'SignalShapeHisto' (string, name of histogram for the shape)\n"
        #if self._config.FakeShapeHisto == None:
            #mymsg += "- missing field 'FakeShapeHisto' (string, name of histogram for the shape)\n"
        if self._config.ShapeHistogramsDimensions == None:
            mymsg += "- missing field 'ShapeHistogramsDimensions' (list of number of bins, rangeMin, rangeMax, variableBinSizeLowEdges, xtitle, ytitle)\n"
        elif not isinstance(self._config.ShapeHistogramsDimensions, dict):
            mymsg += "- field 'ShapeHistogramsDimensions' has to be of type dictionary with keys: bins, rangeMin, rangeMax, variableBinSizeLowEdges, xtitle, ytitle)\n"
        else:
            if not "bins" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key bins (int)\n"
            elif not "rangeMin" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key rangeMin (float)\n"
            elif not "rangeMax" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key rangeMax (float)\n"
            elif not "variableBinSizeLowEdges" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key variableBinSizeLowEdges (list of floats, can be empty list)\n"
            elif not "xtitle" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key xtitle (string)\n"
            elif not "ytitle" in self._config.ShapeHistogramsDimensions.keys():
                mymsg += "- field 'ShapeHistogramsDimensions' has to contain dictionary key ytitle (string)\n"
        if self._config.Observation == None:
            mymsg += "- missing field 'Observation' (ObservationInput object)\n"
        if self._config.DataGroups == None:
            mymsg += "- missing field 'DataGroups' (list of DataGroup objects)\n"
        elif len(self._config.DataGroups) == 0:
            mymsg += "- need to specify at least one DataGroup to field 'DataGroups' (list of DataGroup objects)\n"
        if self._config.Nuisances == None:
            mymsg += "- missing field 'Nuisances' (list of Nuisance objects)\n"
        elif len(self._config.Nuisances) == 0:
            mymsg += "- need to specify at least one Nuisance to field 'Nuisances' (list of Nuisance objects)\n"
        if self._config.ControlPlots == None:
            print WarningLabel()+"You did not specify any ControlPlots in the config (ControlPlots is list of ControlPlotInput objects)!"
            print "  Please check if this was intended."
        # determine if datacard was ok
        if mymsg != "":
            print ErrorStyle()+"Error in config '"+self._opts.datacard+"'!"
            print mymsg
            raise Exception()
        return True

    ## Reads datagroup definitions from columns and initialises datasets
    def createDatacardColumns(self):
        # Make datacard column object for observation
        if self._dsetMgrManager.getDatasetMgr(DatacardDatasetMgrSourceType.SIGNALANALYSIS) != None:
            #self._dsetMgrManager.mergeDatasets(DatacardDatasetMgrSourceType.SIGNALANALYSIS, myObservationName, self._config.Observation.datasetDefinition)
            #print "Making merged dataset for data group: "+HighlightStyle()+"observation"+NormalStyle()
            #self._dsetMgrManager.getDatasetMgr(DatacardDatasetMgrSourceType.SIGNALANALYSIS).merge(myObservationName, myFoundNames, keepSources=True) # note that mergeMany has already been called at this stage
            self._observation = DatacardColumn(label = "data_obs",
                                               enabledForMassPoints = self._config.MassPoints,
                                               datasetType = "Observation",
                                               datasetMgrColumn = self._config.Observation.datasetDefinition,
                                               shapeHisto = self._config.Observation.shapeHisto)
            if self._opts.debugConfig:
                self._observation.printDebug()
        else:
            # Not sure what happens after this warning :)
            print WarningLabel()+"No observation will be extracted, because signal analysis is disabled"

        # Loop over data groups to create datacard columns
        for dg in self._config.DataGroups:
            myIngoreOtherQCDMeasurementStatus = (dg.datasetType == "QCD factorised" and self._QCDMethod == DatacardQCDMethod.INVERTED) or (dg.datasetType == "QCD inverted" and self._QCDMethod == DatacardQCDMethod.FACTORISED)
            if not myIngoreOtherQCDMeasurementStatus:
                print "Constructing datacard column for data group: "+HighlightStyle()+""+dg.label+""+NormalStyle()
                myDsetMgrIndex = None
                myMergedName = ""
                myMergedNameForQCDMCEWK = ""
                #if dg.datasetType != "None" and not myIngoreOtherQCDMeasurementStatus:
                    #if dg.datasetType == "Signal":
                        #myDsetMgrIndex = DatacardDatasetMgrSourceType.SIGNALANALYSIS
                    #elif dg.datasetType == "Embedding":
                        #myDsetMgrIndex = DatacardDatasetMgrSourceType.EMBEDDING
                    #elif dg.datasetType == "QCD factorised" or dg.datasetType == "QCD inverted":
                        #myDsetMgrIndex = DatacardDatasetMgrSourceType.QCDMEASUREMENT
                    # Make merge of requested datasets
                    #if self._opts.debugConfig:
                        #print "Adding datasets to data group '"+dg.label+"':"
                        #for n in myFoundNames:
                            #print "  "+n
                    #myMergedName = "dset_"+dg.label.replace(" ","_")
                    #self._dsetMgrManager.mergeDatasets(myDsetMgrIndex, myMergedName, dg.datasetDefinitions)
                    #if dg.datasetType == "QCD factorised":
                        ## Make merged set of EWK MC datasets
                        #myMergedNameForQCDMCEWK = "dset_"+dg.label.replace(" ","_")+"_MCEWK"
                        #self._dsetMgrManager.mergeDatasets(myDsetMgrIndex, myMergedNameForQCDMCEWK, dg.MCEWKDatasetDefinitions)
                # Construct datacard column object
                myColumn = None
                if dg.datasetType == "QCD factorised":
                    myColumn = QCDfactorisedColumn(landsProcess=dg.landsProcess,
                                                   enabledForMassPoints = dg.validMassPoints,
                                                   nuisanceIds = dg.nuisances,
                                                   datasetMgrColumn = dg.datasetDefinition,
                                                   additionalNormalisationFactor = dg.additionalNormalisation,
                                                   QCDfactorisedInfo = dg.QCDfactorisedInfo,
                                                   debugMode = self._opts.debugQCD)
                elif dg.datasetType == "Embedding":
                    myColumn = DatacardColumn(label=dg.label,
                                              landsProcess=dg.landsProcess,
                                              enabledForMassPoints = dg.validMassPoints,
                                              datasetType = dg.datasetType,
                                              nuisanceIds = dg.nuisances,
                                              datasetMgrColumn = dg.datasetDefinition,
                                              additionalNormalisationFactor = dg.additionalNormalisation,
                                              shapeHisto = dg.shapeHisto)
                else: # i.e. signal analysis and QCD inverted
                    myColumn = DatacardColumn(label=dg.label,
                                              landsProcess=dg.landsProcess,
                                              enabledForMassPoints = dg.validMassPoints,
                                              datasetType = dg.datasetType,
                                              nuisanceIds = dg.nuisances,
                                              datasetMgrColumn = dg.datasetDefinition,
                                              additionalNormalisationFactor = dg.additionalNormalisation,
                                              shapeHisto = dg.shapeHisto)
                # Store column
                self._columns.append(myColumn)
                # Provide debug print
                if self._opts.debugConfig:
                    myColumn.printDebug()

        # Cache main counter tables
        self._dsetMgrManager.cacheMainCounterTables()
        print "Data groups converted to datacard columns\n"

        if self._opts.debugDatasets:
            self._dsetMgrManager.printDatasetMgrContents()

    def doDataMining(self):
        # Do data mining and cache results
        print "\nStarting data mining"
        if self._dsetMgrManager.getDatasetMgr(DatacardDatasetMgrSourceType.SIGNALANALYSIS) != None:
            # Handle observation separately
            myDsetMgr = self._dsetMgrManager.getDatasetMgr(DatacardDatasetMgrSourceType.SIGNALANALYSIS)
            myLuminosity = self._dsetMgrManager.getLuminosity(DatacardDatasetMgrSourceType.SIGNALANALYSIS)
            myMainCounterTable = self._dsetMgrManager.getMainCounterTable(DatacardDatasetMgrSourceType.SIGNALANALYSIS)
            self._observation.doDataMining(self._config,myDsetMgr,myLuminosity,myMainCounterTable,self._extractors,self._controlPlotExtractors)
        for c in self._columns:
            myDsetMgrIndex = 0
            if c.typeIsObservation() or c.typeIsSignal():
                myDsetMgrIndex = 0
            if c.typeIsEWK():
                myDsetMgrIndex = 1
            if c.typeIsQCD():
                myDsetMgrIndex = 2
            # Do mining for datacard columns (separately for EWK fake taus)
            myDsetMgr = self._dsetMgrManager.getDatasetMgr(myDsetMgrIndex)
            myLuminosity = self._dsetMgrManager.getLuminosity(myDsetMgrIndex)
            myMainCounterTable = self._dsetMgrManager.getMainCounterTable(myDsetMgrIndex)
            if c.getLandsProcess() in self._config.EWKFakeIdList:
                c.doDataMining(self._config,myDsetMgr,myLuminosity,myMainCounterTable,self._extractors,self._controlPlotExtractorsEWKfake)
            else:
                c.doDataMining(self._config,myDsetMgr,myLuminosity,myMainCounterTable,self._extractors,self._controlPlotExtractors)
        print "\nData mining has been finished, results (and histograms) have been ingeniously cached"

    ## Closes files in dataset managers
    def closeFiles(self):
        print "Closing open input files"
        self._dsetMgrManager.closeManagers()
        print "DatasetManagers closed"

    ## Check landsProcess in datacard columns
    def checkDatacardColumns(self):
        for m in self._config.MassPoints:
            i = 0
            myFirstValue = 0
            for c in sorted(self._columns, key=lambda x: x.getLandsProcess()):
                if (c.isActiveForMass(m)):
                    #print c.getLabel(), c.getLandsProcess()
                    if i == 0:
                        myFirstValue = c.getLandsProcess()
                    else:
                        if myFirstValue + i != c.getLandsProcess():
                            print ErrorLabel()+" cannot find LandS process '"+str(myFirstValue+i)+"' in data groups for mass = %d! (need to have consecutive numbers; add group with such landsProcess or check input file)"%m
                            raise Exception()
                    i += 1

    ## Creates extractors for nuisances
    def createExtractors(self):
        # Protection to create extractors only once
        if len(self._extractors) > 0:
            return

        myMode = ExtractorMode.NUISANCE
        for n in self._config.Nuisances:
            if n.function == "Constant":
                myMode = ExtractorMode.NUISANCE
                if n.upperValue > 0:
                    myMode = ExtractorMode.ASYMMETRICNUISANCE
                self._extractors.append(ConstantExtractor(exid = n.id,
                                                         constantValue = n.value,
                                                         constantUpperValue = n.upperValue,
                                                         distribution = n.distr,
                                                         description = n.label,
                                                         mode = myMode))
            elif n.function == "Counter":
                self._extractors.append(CounterExtractor(exid = n.id,
                                                        counterItem = n.counter,
                                                        distribution = n.distr,
                                                        description = n.label,
                                                        mode = myMode))
            elif n.function == "maxCounter":
                self._extractors.append(MaxCounterExtractor(exid = n.id,
                                                           counterItem = n.counter,
                                                           counterDirs = n.histoDir,
                                                           distribution = n.distr,
                                                           description = n.label,
                                                           mode = myMode))
            elif n.function == "pileupUncertainty":
                self._extractors.append(PileupUncertaintyExtractor(exid = n.id,
                                                                   counterItem = n.counter,
                                                                   counterDirs = n.histoDir,
                                                                   distribution = n.distr,
                                                                   description = n.label,
                                                                   mode = myMode))
            elif n.function == "Shape":
                self._extractors.append(ShapeExtractor(histoSpecs = self._config.ShapeHistogramsDimensions,
                                                       histoDirs = n.histoDir,
                                                       histograms = n.histo,
                                                       exid = n.id,
                                                       distribution = n.distr,
                                                       description = n.label,
                                                       mode = ExtractorMode.SHAPENUISANCE))
            elif n.function == "ScaleFactor":
                self._extractors.append(ScaleFactorExtractor(exid = n.id,
                                                            histoDirs = n.histoDir,
                                                            histograms = n.histo,
                                                            normalisation = n.norm,
                                                            addSystInQuadrature = n.addUncertaintyInQuadrature,
                                                            distribution = n.distr,
                                                            description = n.label,
                                                            mode = myMode))
            elif n.function == "Ratio":
                self._extractors.append(RatioExtractor(exid = n.id,
                                                      numeratorCounterItem = n.numerator,
                                                      denominatorCounterItem = n.denominator,
                                                      distribution = n.distr,
                                                      description = n.label,
                                                      scale = n.scaling,
                                                      mode = myMode))
            elif n.function == "QCDFactorised":
                if self._QCDMethod == DatacardQCDMethod.FACTORISED:
                    self._extractors.append(QCDfactorisedExtractor(QCDmode = n.QCDmode, exid = n.id, distribution = n.distr, description = n.label, mode = myMode))
                else:
                    # Protection; generate nuisance line even, but leave it empty
                    self._extractors.append(ConstantExtractor(exid = n.id, constantValue = 0.0, distribution = n.distr, description = n.label, mode = myMode))
            elif n.function == "QCDInverted":
                if self._QCDMethod == DatacardQCDMethod.INVERTED:
                    ####print "fixme: add QCD inverted"
                    # FIXME temp code
                    self._extractors.append(ConstantExtractor(exid = n.id, constantValue = 0.0, distribution = n.distr, description = n.label, mode = myMode))
                else:
                    # Protection; generate nuisance line even, but leave it empty
                    self._extractors.append(ConstantExtractor(exid = n.id, constantValue = 0.0, distribution = n.distr, description = n.label, mode = myMode))
            else:
                print ErrorStyle()+"Error in nuisance with id='"+n.id+"':"+NormalStyle()+" unknown or missing field function '"+n.function+"' (string)!"
                print "Options are: 'Constant', 'Counter', 'maxCounter', 'Shape', 'ScaleFactor', 'Ratio', 'QCDFactorised'"
                raise Exception()
        # Create reserved nuisances
        for n in self._config.ReservedNuisances:
            self._extractors.append(ConstantExtractor(exid = n[0], constantValue = 0.0, distribution = "lnN", description = n[1], mode = myMode))
        # Done
        print "Created Nuisances"
        self.checkNuisances()

    def checkNuisances(self):
        # Check for duplicates
        for i in range(0,len(self._extractors)):
            for j in range(0,len(self._extractors)):
                if self._extractors[i].isId(self._extractors[j].getId()) and i != j:
                    print ErrorStyle()+"Error:"+NormalStyle()+" You have defined two nuisances with id='"+self._extractors[j].getId()+"'! The id has to be unique!"
                    raise Exception()
        # Merge nuisances
        self.mergeNuisances()
        # Check consecutive id's
        #myCounter = 0
        #for n in sorted(self._extractors, key=lambda x: x.getId()):
            #if n.isPrintable():
                #myCounter += 1
                #if int(n.getId()) != myCounter:
                    #print WarningLabel()+"You have not declared a Nuisance or ReservedNuisance with id='%d'! (assuming consecutive numbers)"%myCounter
                    #myCounter = int(n.getId())

    def mergeNuisances(self):
        for mset in self._config.MergeNuisances:
            # check if nuisance with master id can be found
            myFoundStatus = False
            for n in self._extractors:
                if n.isId(mset[0]):
                    myFoundStatus = True
            if not myFoundStatus:
                print ErrorStyle()+"Error in merging Nuisances:"+NormalStyle()+" cannot find a nuisance with id '"+mset[0]+"'!"
                raise Exception()
            # assign master to slave nuisances
            for i in range(1, len(mset)):
                myFoundStatus = False
                for n in self._extractors:
                    if n.isId(mset[i]):
                        n.setAsSlave(mset[0])
                        myFoundStatus = True
                if not myFoundStatus:
                    print ErrorStyle()+"Error in merging Nuisances:"+NormalStyle()+" tried to merge '"+mset[i]+"' (slave) to '"+mset[0]+"' (master) but could not find a nuisance with id '"+mset[i]+"'!"
                    raise Exception()
        print "Merged Nuisances"


    ## Creates extractors for nuisances
    def createControlPlots(self):
        # Protection to create extractors only once
        if len(self._controlPlotExtractors) > 0:
            return

        # Loop over control plot inputs, create extractors for all other columns except QCD factorised
        for c in self._config.ControlPlots:
            self._controlPlotExtractors.append(ControlPlotExtractor(histoSpecs = c.details,
                                               histoTitle = c.title,
                                               histoDirs = c.signalHistoPath,
                                               histoNames = c.signalHistoName))
            self._controlPlotExtractorsEWKfake.append(ControlPlotExtractor(histoSpecs = c.details,
                                                      histoTitle = c.title,
                                                      histoDirs = c.EWKfakeHistoPath,
                                                      histoNames = c.EWKfakeHistoName))
