## \package DatacardColumn
# Class collecting information about a column to be produced in the datacard
#

import os

from HiggsAnalysis.HeavyChHiggsToTauNu.datacardtools.MulticrabPathFinder import MulticrabDirectoryDataType

# DatacardColumn class
class DatacardColumn():
    ## Constructor
    def __init__(self,
                 label = "",
                 landsProcess = -999,
                 enabledForMassPoints = [],
                 datasetType = 0,
                 rateCounter = "",
                 nuisances = [],
                 datasetMgr = None,
                 datasetMgrColumn = "",
                 datasetMgrColumnForQCDMCEWK = "",
                 additionalNormalisationFactor = 1.0,
                 dirPrefix = "",
                 shapeHisto = ""):
        self._label = label
        self._landsProcess = landsProcess
        self._enabledForMassPoints = enabledForMassPoints
        if (datasetTypeInternal >= -1):
            self_datasetType = datasetTypeInternal
        else:
            if datasetType == "Signal":
                self._datasetType = MulticrabDirectoryDataType.SIGNAL
            elif datasetType == "Embedding":
                self._datasetType = MulticrabDirectoryDataType.EMBEDDING
            elif datasetType == "QCD factorised":
                self._datasetType = MulticrabDirectoryDataType.QCDFACTORISED
            elif datasetType == "QCD inverted":
                self._datasetType = MulticrabDirectoryDataType.QCDINVERTED
            elif datasetType == "None":
                self._datasetType = MulticrabDirectoryDataType.DUMMY
            else:
                self._datasetType = MulticrabDirectoryDataType.UNKNOWN
        self._rateCounter = rateCounter
        self._nuisances = nuisances
        self._datasetMgr = datasetMgr
        self._datasetMgrColumn = datasetMgrColumn
        self._datasetMgrColumnForQCDMCEWK  = datasetMgrColumnForQCDMCEWK
        self._additionalNormalisationFactor = additionalNormalisationFactor
        self._dirPrefix = dirPrefix
        self._shapeHisto = shapeHisto
        
        self.checkInputValidity()

    def checkInputValidity(self):
        myMsg = ""
        if self._label == "":
            myMsg += "Missing or empty field 'label'! (string) to be printed on a column in datacard\n"
        if self._landsProcess == -999:
            myMsg += "Missing or empty field 'landsProcess'! (integer) to be printed as process in datacard\n"
        if len(self._enabledForMassPoints) == 0:
            myMsg += "Missing or empty field 'enabledForMassPoints'! (list of integers) specifies for which mass points the column is enabled\n"
        if self._datasetType == MulticrabDirectoryDataType.UNKNOWN:
            myMsg += "Wrong 'datasetType' specified! Valid options are 'Signal', 'Embedding', 'QCD factorised', 'QCD inverted', and 'None'\n"
        if self._datasetMgrColumn == "":
            myMsg += "No dataset names defined!\n"
        if self._datasetType == MulticrabDirectoryDataType.SIGNAL or self._datasetType == MulticrabDirectoryDataType.EMBEDDING:
            if self._rateCounter == "":
                myMsg += "Missing or empty field 'rateCounter'! (string) Counter for rate to be used for column\n"
        elif self._datasetType == MulticrabDirectoryDataType.QCDFACTORISED:
            # rate handled as spedial case, extra datasetMgrColumn are required for EWK MC
            if len(self._datasetMgrColumnForQCDMCEWK) == 0:
                myMsg += "No datasets defined for MC EWK in data group for QCD factorised!\n"
        elif self._datasetType == MulticrabDirectoryDataType.QCDINVERTED:
            myMsg += "FIXME: QCD inverted not implemented yet\n" # FIXME
        if self._datasetType != MulticrabDirectoryDataType.DUMMY:
            if len(self._nuisances) == 0:
                myMsg += "Missing or empty field 'nuisances'! (list of strings) Id's for nuisances to be used for column\n"
            if self._shapeHisto == "":
                myMsg += "Missing or empty field 'shapeHisto'! (string) Name of histogram for shape \n"

        if myMsg != "":
            print "Error (data gropu ='"+self._label_+"'):\n"+myMsg
            sys.exit()

    ## Returns true if column has a nuisance
    def hasNuisance(self, id):
        return id in self._nuisances

    ## Returns true if column is enabled for given mass point
    def isActiveForMass(self, mass):
        return mass in self._enabledForMassPoints

    ## Returns rate for column (as string)
    def getRateData(self):
        #FIXME
        print "getRate not yet implemented"
        return 0;

    ## Returns nuisance for column (as string)
    def getNuisanceData(self, id):
        for nid in self._nuisances:
            if id == nid:
                print "not implemented yet" #FIXME
                #return nid.doExtract(self._datasetMgrColumn
        return ""

    ##
    def setShapeHistoToRootFile(self, rootfile):
        print "setShapeHistoToRootFile not yet implemented"
        #FIXME

    ## \var _additionalNormalisationFactor
    # Normalisation factor is multiplied by this factor (needed for EWK)
    ## \var _label
    # Label of column to be printed in datacard
    ## \var _enabledForMassPoints
    # List of mass points for which the column is enabled
    ## \var _rateId
    # Id of rate object
    ## \var _nuisances
    # List of nuisance Id's
    ## \var _datasetMgr
    # Path to files
    # FIXME continue doc