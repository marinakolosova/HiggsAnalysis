#!/usr/bin/env python

import sys
import re
import array

import ROOT
ROOT.gROOT.SetBatch(True)

import HiggsAnalysis.HeavyChHiggsToTauNu.tools.histograms as histograms
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.tdrstyle as tdrstyle
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.styles as styles
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.plots as plots
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.limit as limit
import HiggsAnalysis.HeavyChHiggsToTauNu.tools.BRXSDatabaseInterface as BRXSDB

tanbMax = 65
#GeVUnit = "GeV/c^{2}"
GeVUnit = "GeV"

ROOT.gROOT.LoadMacro("LHCHiggsUtils.cc")

def usage():
    print
    print "### Usage:  ",sys.argv[0],"<root file>"
    print "### Example:",sys.argv[0],"mhmax.root"
    print
    sys.exit()
    
def main():
    if len(sys.argv) == 1:
        usage()

    rootfile = ""

    root_re = re.compile("(?P<rootfile>(\S*\.root))")
    match = root_re.search(sys.argv[1])
    if match:
        rootfile = match.group(0)

                                                                    
    limits = limit.BRLimits()

    # Apply TDR style
    style = tdrstyle.TDRStyle()
    if limit.forPaper:
        histograms.cmsTextMode = histograms.CMSMode.PAPER

    # Get BR limits

    masses = limits.mass
    brs    = limits.observed

    #print masses,brs
    
    db = BRXSDB.BRXSDatabaseInterface(rootfile)
    for i,m in enumerate(masses):
        db.addExperimentalBRLimit(m,brs[i])

    graphs = {}
    obs = limits.observedGraph()
    graphs["obs"] = obs
    graphs["exp"] = limits.expectedGraph()
#    graphs["exp"].SetLineStyle(2)
    graphs["exp1"] = limits.expectedBandGraph(sigma=1)
    graphs["exp2"] = limits.expectedBandGraph(sigma=2)

    # Remove m=80
    for gr in graphs.values():
        limit.cleanGraph(gr, minX=100)
        N = gr.GetN()
#        for i in range(gr.GetN()):
#            j = N - 1 - i
#            if gr.GetX()[j] > 154 and gr.GetX()[j] < 156:
#                gr.RemovePoint(j)
                
    # Get theory uncertainties on observed
    obs_th_plus = limit.getObservedPlus(obs)
    obs_th_minus = limit.getObservedMinus(obs)
    for gr in [obs_th_plus, obs_th_minus]:
        gr.SetLineWidth(2)
        gr.SetLineStyle(9)
    graphs["obs_th_plus"] = obs_th_plus
    graphs["obs_th_minus"] = obs_th_minus

    # Interpret in MSSM
    xVariable = "mHp"
####    selection = "mu==200&&Xt==2000&&m2==200"
    selection = "mu==200"
    scenario = "MSSM m_{h}^{max}"
#    scenario = "MSSM m_{h}^{max up}"
#    scenario = "MSSM m_{h}^{mod+}"
#    scenario = "MSSM m_{h}^{mod-}"
#    scenario = "MSSM #tau-phobic"        #mu=500
#    scenario = "MSSM light #tilde{#tau}" #mu=500
#    scenario = "MSSM light #tilde{t}" #mu=350
#    scenario = "MSSM low m_{H}"	  #mu=1700


    for key in graphs.keys():
#        removeNotValid = not (key in ["exp1", "exp2"])
#        graphs[key] = limit.graphToTanBeta(graphs[key], mu, removeNotValid)
#        graphs[key] = db.graphToTanBeta(graphs[key],xVariable,selection)
        graphs[key] = db.graphToTanBetaCombined(graphs[key],xVariable,selection)
#        graphs[key] = db.graphToSharpTanbExclusion(graphs[key],xVariable,selection)

    graphs["mintanb"] = db.minimumTanbGraph("mHp",selection)
#    graphs["Allowed"] = db.mhLimit("mHp",selection,"125.9+-0.6+-0.2")
    graphs["Allowed"] = db.mhLimit("mh","mHp",selection,"125.9+-3.0")
#    graphs["Allowed"] = db.mhLimit("mHA","mHp",selection,"125.9+-3.0")

    graphs["excluded"] = db.excluded(graphs["obs"],"ExcludedArea")
    
#    doPlot("limitsTanb_mh", graphs, limits, limit.mHplus(),scenario)
    doPlot("limitsmHpTanb_"+rootfile.replace(".root",""), graphs, limits, "m_{H^{+}} ("+GeVUnit+")",scenario)

#    xVariable = "mA"
#    for key in graphs.keys():
#        graphs[key] = db.graphToTanBeta(graphs[key],xVariable,selection)
#    doPlot("limitsTanb_ma", graphs, limits, limit.mA())



def doPlot(name, graphs, limits, xlabel, scenario):

    expected = graphs["exp"]
    expected.SetLineStyle(2)
    expected1 = graphs["exp1"]
    expected1.SetLineStyle(2)
    expected2 = graphs["exp2"]
    expected2.SetLineStyle(2)
        
    plot = plots.PlotBase([
            histograms.HistoGraph(graphs["obs"], "Observed", drawStyle="PL", legendStyle="lp"),
            histograms.HistoGraph(graphs["obs_th_plus"], "ObservedPlus", drawStyle="L", legendStyle="l"),
            histograms.HistoGraph(graphs["obs_th_minus"], "ObservedMinus", drawStyle="L"),
            histograms.HistoGraph(graphs["excluded"], "Excluded", drawStyle="F", legendStyle="f"),
            histograms.HistoGraph(expected, "Expected", drawStyle="L"),
            #histograms.HistoGraph(graphs["exp"], "Expected", drawStyle="L"),
####            histograms.HistoGraph(graphs["Allowed"], "Allowed by \nm_{h} = 125.9#pm3.0 "+GeVUnit, drawStyle="F", legendStyle="f"),
            histograms.HistoGraph(graphs["Allowed"], "Allowed by \nm_{H} = 125.9#pm3.0 "+GeVUnit, drawStyle="F", legendStyle="f"),
            histograms.HistoGraph(graphs["Allowed"], "AllowedCopy", drawStyle="L", legendStyle="f"),
            histograms.HistoGraph(graphs["mintanb"], "MinTanb", drawStyle="L"),
            #histograms.HistoGraph(graphs["exp1"], "Expected1", drawStyle="F", legendStyle="fl"),
            #histograms.HistoGraph(graphs["exp2"], "Expected2", drawStyle="F", legendStyle="fl"),
            histograms.HistoGraph(expected1, "Expected1", drawStyle="F", legendStyle="fl"),
            histograms.HistoGraph(expected2, "Expected2", drawStyle="F", legendStyle="fl"),
            ])

    plot.histoMgr.setHistoLegendLabelMany({
            "ObservedPlus": "Observed #pm1#sigma (th.)",
            "ObservedMinus": None,
            "Expected": None,
            "MinTanb": None,
            "AllowedCopy": None,
            "Expected1": "Expected median #pm 1#sigma",
            "Expected2": "Expected median #pm 2#sigma"
            })
#    plot.setLegend(histograms.createLegend(0.57, 0.155, 0.87, 0.355))
    plot.setLegend(histograms.createLegend(0.19, 0.60, 0.57, 0.80))
    plot.legend.SetFillColor(0)
    plot.legend.SetFillStyle(1001)
    plot.createFrame(name, opts={"ymin": 0, "ymax": tanbMax, "xmin": 100, "xmax": 160})
    plot.frame.GetXaxis().SetTitle(xlabel)
    plot.frame.GetYaxis().SetTitle(limit.tanblimit)

    plot.draw()

#    histograms.addCmsPreliminaryText()
    histograms.addEnergyText()
#    histograms.addLuminosityText(x=None, y=None, lumi=limits.getLuminosity())
    histograms.addLuminosityText(x=None, y=None, lumi="2.3-4.9")

    size = 20
    x = 0.2
    histograms.addText(x, 0.9, limit.process, size=size)
    histograms.addText(x, 0.863, limits.getFinalstateText(), size=size)
####    histograms.addText(x, 0.815, "MSSM m_{h}^{max}", size=size)
    histograms.addText(x, 0.815,scenario, size=size)
#    histograms.addText(x, 0.775, limit.BRassumption, size=size)
#    histograms.addText(x, 0.735, "#mu=%d %s"%(mu, limit.massUnit()), size=size)
    histograms.addText(0.7, 0.23, "Min "+limit.BR+"(t#rightarrowH^{+}b)#times"+limit.BR+"(H^{+}#rightarrow#tau#nu)", size=0.5*size)

    #Adding a LHC label:
    ROOT.LHCHIGGS_LABEL(0.97,0.72,1)
    histograms.addText(x, 0.55, "FeynHiggs 2.9.4", size=size)
    histograms.addText(x, 0.48, "Derived from", size=size)
    histograms.addText(x, 0.43, "CMS HIG-12-052", size=size)
#    histograms.addText(x, 0.38, "JHEP07(2012)143", size=size)
                
    plot.save()


if __name__ == "__main__":
    main()
