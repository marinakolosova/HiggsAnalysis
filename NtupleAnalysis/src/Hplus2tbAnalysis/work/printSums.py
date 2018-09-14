#!/usr/bin/env python
'''
DESCRIPTION:
Comparison of datasets with different PDF weights
The first multicrab in the input list is used as the reference multicrab (nominal)

USAGE:
./printSums.py -m <pseudo_mcrab> [opts]


EXAMPLES:
./printSums.py -m Hplus2tbAnalysis_Weight_Nominal,Hplus2tbAnalysis_Weight_3 -i "500"

LAST USED:
./printSums.py -m Hplus2tbAnalysis_Weight_Nominal,Hplus2tbAnalysis_Weight_3 -i "500" --url

'''
#================================================================================================ 
# Imports
#================================================================================================ 
import sys
import math
import copy
import os
from optparse import OptionParser

import getpass

import ROOT
import array

ROOT.gROOT.SetBatch(True)
from ROOT import *

import HiggsAnalysis.NtupleAnalysis.tools.dataset as dataset
import HiggsAnalysis.NtupleAnalysis.tools.histograms as histograms
import HiggsAnalysis.NtupleAnalysis.tools.counter as counter
import HiggsAnalysis.NtupleAnalysis.tools.tdrstyle as tdrstyle
import HiggsAnalysis.NtupleAnalysis.tools.styles as styles
import HiggsAnalysis.NtupleAnalysis.tools.plots as plots
import HiggsAnalysis.NtupleAnalysis.tools.crosssection as xsect
import HiggsAnalysis.NtupleAnalysis.tools.multicrabConsistencyCheck as consistencyCheck
import HiggsAnalysis.NtupleAnalysis.tools.ShellStyles as ShellStyles
import HiggsAnalysis.NtupleAnalysis.tools.aux as aux

ROOT.gErrorIgnoreLevel = ROOT.kError
#================================================================================================ 
# Function Definition
#================================================================================================ 
def Print(msg, printHeader=False):
    fName = __file__.split("/")[-1]
    if printHeader==True:
        print "=== ", fName
        print "\t", msg
    else:
        print "\t", msg
    return

def Verbose(msg, printHeader=True, verbose=False):
    if not opts.verbose:
        return
    aux.Print(msg, printHeader)
    return

def GetLumi(datasetsMgr):
    Verbose("Determininig Integrated Luminosity")
    
    lumi = 0.0
    for d in datasetsMgr.getAllDatasets():
        if d.isMC():
            continue
        else:
            lumi += d.getLuminosity()
    Verbose("Luminosity = %s (pb)" % (lumi), True)
    return lumi


def GetDatasetsFromDir(opts, i):
    Verbose("Getting datasets")
    
    print "multicrab", opts.mcrabs[i]

    if (not opts.includeOnlyTasks and not opts.excludeTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrabs[i]],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode, 
                                                        analysisName=opts.analysisName,
                                                        optimizationMode=opts.optMode)
    elif (opts.includeOnlyTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrabs[i]],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode,
                                                        analysisName=opts.analysisName,
                                                        includeOnlyTasks=opts.includeOnlyTasks,
                                                        optimizationMode=opts.optMode)
    elif (opts.excludeTasks):
        datasets = dataset.getDatasetsFromMulticrabDirs([opts.mcrabs[i]],
                                                        dataEra=opts.dataEra,
                                                        searchMode=opts.searchMode,
                                                        analysisName=opts.analysisName,
                                                        excludeTasks=opts.excludeTasks,
                                                        optimizationMode=opts.optMode)
    else:
        raise Exception("This should never be reached")
    return datasets
    

def GetHistoKwargs(h, opts):
    _moveLegend =  {"dx": -0.08, "dy": -0.45, "dh": 0.10}
    logY    = False
    _yLabel = "Events / %.0f "
    yMin    = 1e0
    if logY:
        yMaxF = 10
    else:
        yMaxF = 1.2

    _kwargs = {
        "ylabel"           : _yLabel,
        "rebinX"           : 1,
        "rebinY"           : None,
        "ratioYlabel"      : "Ratio",
        "ratio"            : True,
        "ratioCreateLegend": True,
        "ratioType"        : "errorScale",
        "ratioErrorOptions": {"numeratorStatSyst": False},
        "ratioMoveLegend"  : {"dx": -0.51, "dy": 0.03, "dh": -0.05},
        "ratioInvert"      : False,
        "addMCUncertainty" : True,
        "addLuminosityText": False,
        "addCmsText"       : True,
        "cmsExtraText"     : "Preliminary",
        "opts"             : {"ymin": yMin, "ymaxfactor": yMaxF},
        "opts2"            : {"ymin": 0.59, "ymax": 1.41},
        "log"              : logY,
        "moveLegend"       : _moveLegend,
        }

    kwargs = copy.deepcopy(_kwargs)

    if "pt" in h.lower():
        units            = "GeV/c"
        kwargs["ylabel"] = _yLabel + units
        kwargs["xlabel"] = "p_{T} (%s)" % units

    if "TetrajetMass" in h:
        units            = "GeV/c^{2}"
        kwargs["rebinX"] = 10
        kwargs["xlabel"] = "m_{jjbb} (%s)" % units
        kwargs["ylabel"] = _yLabel + units

    if "Counter" in h:
        kwargs["xlabel"] = "Weights"
        kwargs["ylabel"] = "Value"

    return kwargs
def main(opts):

    # Apply TDR style
    style = tdrstyle.TDRStyle()
    style.setOptStat(False)
    style.setGridX(False)
    style.setGridY(False)
    
    # Setup & configure the dataset manager 
    datasetsMgr = GetDatasetsFromDir(opts, 0)
    datasetsMgr.updateNAllEventsToPUWeighted()
    datasetsMgr.loadLuminosities() # from lumi.json
        
    if opts.verbose:
        datasetsMgr.PrintCrossSections()
        datasetsMgr.PrintLuminosities()

    # Set/Overwrite cross-sections
    for d in datasetsMgr.getAllDatasets():
        if "ChargedHiggs" in d.getName():
            datasetsMgr.getDataset(d.getName()).setCrossSection(1.0)

    # Merge histograms (see NtupleAnalysis/python/tools/plots.py) 
    if 1:
        plots.mergeRenameReorderForDataMC(datasetsMgr) 

    # Print datasets info summary
    datasetsMgr.PrintInfo()

    # Define the mapping histograms in numerator->denominator pairs
    VariableList = ["hCounter_WeightSums"]

    counter =  0
    opts.nDatasets = len(datasetsMgr.getAllDatasets())
    nPlots  = len(VariableList)

    # For-loop: All datasets
    for dataset in datasetsMgr.getAllDatasets():
        
        # For-looop: All variables
        for hName in VariableList:
            hPath = os.path.join(opts.folder, hName)

            counter+=1
            msg = "{:<9} {:>3} {:<1} {:<3} {:<50}".format("Histogram", "%i" % counter, "/", "%s:" % (nPlots), "%s" % (hName))
            Print(ShellStyles.SuccessStyle() + msg + ShellStyles.NormalStyle(), counter==1)
        
            PlotHistos(dataset.getName(), hPath) # For each dataset: Plot histos from different multicrabs on same canvas

    Print("All plots saved under directory %s" % (ShellStyles.NoteStyle() + aux.convertToURL(opts.saveDir, opts.url) + ShellStyles.NormalStyle()), True)
    return
            

def PlotHistos(datasetName, hPath):


    _kwargs     = GetHistoKwargs(hPath, opts)
    datasetsMgr_list = []

    j = 0
    histoList = []

    # For-loop: All pseudo-multicrabs
    while j < len(opts.mcrabs):
        
        weightpos = opts.mcrabs[j].split("_")[-1]
        
        dMgr = GetDatasetsFromDir(opts, j)
        dMgr.updateNAllEventsToPUWeighted()
        dMgr.loadLuminosities() # from lumi.json

       # Set/Overwrite cross-sections
        if  "ChargedHiggs" in datasetName:
            dMgr.getDataset(datasetName).setCrossSection(1.0)
                
        # Get dataset
        dataset = dMgr.getDataset(datasetName)
        # Get Histogram from dataset
        histo = dataset.getDatasetRootHisto(hPath).getHistogram()                
        # Set style
        styles.styles[j].apply(histo) #fixme: Define new list with styles (110 styles?)
        
        print " "
        print "-------------------------------------------"
        print "Dataset        = ", datasetName
        print "Weight position= ", weightpos
        print "Central Weight = ", histo.GetBinContent(1)
        print "Scale Weight   = ", histo.GetBinContent(2)
        print " "
        

        text = weightpos
        if j==0:
            refHisto = histograms.Histo(histo,  "Nominal",    legendStyle = "LP", drawStyle="HIST") #fix legend
        else:
            histoList.append(histograms.Histo(histo, "PDF uncert. "+text,     legendStyle = "LP", drawStyle="HIST")) #fix legend
        j = j + 1

    #Compare plots
    p = plots.ComparisonManyPlot(refHisto, histoList, saveFormats=[])
    
    saveDir = os.path.join(opts.saveDir, datasetName)
    savePath = os.path.join(saveDir, opts.optMode)
    plots.drawPlot(p, savePath, **_kwargs)
    saveName = "PDFs_"+hPath.split("/")[-1]

    # Save plot in all formats
    SavePlot(p, saveName, savePath, saveFormats = [".png", ".pdf", ".C"])

    return

def SavePlot(plot, plotName, saveDir, saveFormats = [".C", ".png", ".pdf"]):
    Verbose("Saving the plot in %s formats: %s" % (len(saveFormats), ", ".join(saveFormats) ) )

     # Check that path exists
    if not os.path.exists(saveDir):
        os.makedirs(saveDir)

    # Create the name under which plot will be saved
    saveName = os.path.join(saveDir, plotName.replace("/", "_"))

    # For-loop: All save formats
    for i, ext in enumerate(saveFormats):
        saveNameURL = saveName + ext
        saveNameURL = aux.convertToURL(saveNameURL, opts.url)
        Verbose(saveNameURL, i==0)
        plot.saveAs(saveName, formats=saveFormats)
    return


#================================================================================================ 
# Main
#================================================================================================ 
if __name__ == "__main__":
    '''
    https://docs.python.org/3/library/argparse.html
 
    name or flags...: Either a name or a list of option strings, e.g. foo or -f, --foo.
    action..........: The basic type of action to be taken when this argument is encountered at the command line.
    nargs...........: The number of command-line arguments that should be consumed.
    const...........: A constant value required by some action and nargs selections.
    default.........: The value produced if the argument is absent from the command line.
    type............: The type to which the command-line argument should be converted.
    choices.........: A container of the allowable values for the argument.
    required........: Whether or not the command-line option may be omitted (optionals only).
    help............: A brief description of what the argument does.
    metavar.........: A name for the argument in usage messages.
    dest............: The name of the attribute to be added to the object returned by parse_args().
    '''
    
    # Default Settings
    ANALYSISNAME = "Hplus2tbAnalysis"
    SEARCHMODE   = "80to1000"
    DATAERA      = "Run2016"
    OPTMODE      = ""
    BATCHMODE    = True
    PRECISION    = 3
    INTLUMI      = -1.0
    URL          = False
    SAVEDIR      = None
    VERBOSE      = False
    NORMALISE    = False
    FOLDER       = ""

    # Define the available script options
    parser = OptionParser(usage="Usage: %prog [options]")

    parser.add_option("-m", "--mcrabs", dest="mcrabs", action="store", 
                      help="Path to the multicrab directories for input")

    parser.add_option("-o", "--optMode", dest="optMode", type="string", default=OPTMODE, 
                      help="The optimization mode when analysis variation is enabled  [default: %s]" % OPTMODE)

    parser.add_option("-b", "--batchMode", dest="batchMode", action="store_false", default=BATCHMODE, 
                      help="Enables batch mode (canvas creation does NOT generate a window) [default: %s]" % BATCHMODE)

    parser.add_option("--analysisName", dest="analysisName", type="string", default=ANALYSISNAME,
                      help="Override default analysisName [default: %s]" % ANALYSISNAME)

    parser.add_option("--intLumi", dest="intLumi", type=float, default=INTLUMI,
                      help="Override the integrated lumi [default: %s]" % INTLUMI)

    parser.add_option("--searchMode", dest="searchMode", type="string", default=SEARCHMODE,
                      help="Override default searchMode [default: %s]" % SEARCHMODE)

    parser.add_option("--dataEra", dest="dataEra", type="string", default=DATAERA, 
                      help="Override default dataEra [default: %s]" % DATAERA)

    parser.add_option("--saveDir", dest="saveDir", type="string", default=SAVEDIR, 
                      help="Directory where all pltos will be saved [default: %s]" % SAVEDIR)

    parser.add_option("--url", dest="url", action="store_true", default=URL, 
                      help="Don't print the actual save path the histogram is saved, but print the URL instead [default: %s]" % URL)
    
    parser.add_option("-v", "--verbose", dest="verbose", action="store_true", default=VERBOSE, 
                      help="Enables verbose mode (for debugging purposes) [default: %s]" % VERBOSE)

    parser.add_option("-i", "--includeOnlyTasks", dest="includeOnlyTasks", action="store", 
                      help="List of datasets in mcrab to include")

    parser.add_option("-e", "--excludeTasks", dest="excludeTasks", action="store", 
                      help="List of datasets in mcrab to exclude")

    parser.add_option("-n", "--normaliseToOne", dest="normaliseToOne", action="store_true", 
                      help="Normalise the histograms to one? [default: %s]" % (NORMALISE) )

    parser.add_option("--folder", dest="folder", type="string", default = FOLDER,
                      help="ROOT file folder under which all histograms to be plotted are located [default: %s]" % (FOLDER) )

    (opts, parseArgs) = parser.parse_args()

    # Require at least two arguments (script-name, path to multicrab)
    if len(sys.argv) < 2:
        parser.print_help()
        sys.exit(1)

    if len(opts.mcrabs) == 0:
        Print("Not enough arguments passed to script execution. Printing docstring & EXIT.")
        parser.print_help()
        #print __doc__
        sys.exit(1)

    # Store all (comma-separated) pseudomulticrabs in a list
    if opts.mcrabs == None:
        Print("Not enough arguments passed to script execution. Printing docstring & EXIT.")
        parser.print_help()
        sys.exit(1)
    else:
        if "," in opts.mcrabs:
            opts.mcrabs = opts.mcrabs.split(",")    
        else:
            cwd  = os.getcwd()
            dirs = [ name for name in os.listdir(cwd) if os.path.isdir(os.path.join(cwd, name)) ]
            mcrabs = [d for d in dirs if opts.mcrabs in d and "Top" in d]
            opts.mcrabs = mcrabs


 # For-loop: All pseudomulticrab dirs
    for mcrab in opts.mcrabs:
        if not os.path.exists("%s/multicrab.cfg" % mcrab):
            msg = "No pseudo-multicrab directory found at path '%s'! Please check path or specify it with --mcrab!" % (mcrab)
            raise Exception(ShellStyles.ErrorLabel() + msg + ShellStyles.NormalStyle())
        else:
            msg = "Using pseudo-multicrab directory %s" % (ShellStyles.NoteStyle() + mcrab + ShellStyles.NormalStyle())
            Verbose(msg , True)

    # Append folder to save directory path
    if opts.saveDir == None:
        opts.saveDir = aux.getSaveDirPath(opts.mcrabs[0], prefix="", postfix="")

    # Call the main function
    main(opts)

    if not opts.batchMode:
        raw_input("=== plot_EfficiencySystTop.py: Press any key to quit ROOT ...")
