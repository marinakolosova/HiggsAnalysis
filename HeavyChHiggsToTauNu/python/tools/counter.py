import math
import ROOT

from dataset import *

class FloatAutoFormat:
    def __init__(self, decimals=4):
        self.format = "%%%d."+str(decimals)+"g"
    def __call__(self, width):
        return self.format % width

class FloatDecimalFormat:
    def __init__(self, decimals=4):
        self.format = "%%%d."+str(decimals)+"f"
    def __call__(self, width):
        return self.format % width

class FloatExpFormat:
    def __init__(self, decimals=4):
        self.format = "%%%d."+str(decimals)+"e"
    def __call__(self, width):
        return self.format % width

class FormatText:
    def __init__(self, valuePrecision=4, errorPrecision=4,
                 begin="", separator = "  ", end = "",
                 numberFormat="g"): # f, e, g as for printf
        self.valuePrecision = valuePrecision
        self.errorPrecision = errorPrecision
        self.errorEpsilon = math.pow(10., -1.0*errorPrecision)
        self.begin = begin
        self.separator = separator
        self.end = end
        self.format = numberFormat
                 
    def beginTable(self):
        return ""

    def endTable(self):
        return ""

    def beginLine(self):
        return self.begin

    def endLine(self):
        return self.end

    def beginColumn(self):
        return ""

    def endColumn(self):
        return self.separator

    def number(self, value, error=None, errorLow=None, errorHigh=None):
        if error != None and (errorLow != None or errorHigh != None):
            raise Exception("Only either error or errorLow and errorHigh can be set")
        if errorLow != None and errorHigh == None or errorLow == None and errorHigh != None:
            raise Exception("Both errorLow and errorHigh must be set")

        fmt = "%"+str(self.valuePrecision)+"."+self.format
        ret = fmt % value
        if error == None and errorLow == None:
            return ret

        fmt = "%"+str(self.errorPrecision)+"."+self.format
        if error != None:
            ret += " +- " + fmt%error
            return ret

        if abs(errorHigh-errorLow)/errorHigh < self.errorEpsilon:
            ret += " +- " + fmt%errorLow
        else:
            ret += " + "+fmt%errorHigh + " - "+fmt%errorLow


def printCounter(counterData, formatFunction=FloatAutoFormat()):
    print counterData.formatHeader()

    for irow in xrange(0, counterData.getNrows()):
        line = counterData.formatFirstColumn(irow)

        for icol in xrange(0, counterData.getNcolumns()):
            count = counterData.getCount(irow, icol)
            if count != None:
                line += formatFunction(counterData.getColumnWidth(icol)) % count.value()
            else:
                line += " "*counterData.getColumnWidth(icol)

        print line
            
def printCounterEfficiency(counterData, formatFunction=FloatAutoFormat()):
    print counterData.formatHeader()

    prevData = [None] * counterData.getNcolumns()

    for irow in xrange(0, counterData.getNrows()):
        line = counterData.formatFirstColumn(irow)

        for icol in xrange(0, counterData.getNcolumns()):
            count = counterData.getCount(irow, icol)
            prevCount = prevData[icol]
            if count != None and prevCount != None:
                line += formatFunction(counterData.getColumnWidth(icol)) % (count.value() / prevCount.value())
            else:
                line += " "*counterData.getColumnWidth(icol)
            prevData[icol] = count

        print line


# Counter for one dataset
class SimpleCounter:
    def __init__(self, histoWrapper):
        self.histoWrapper = histoWrapper
        self.counter = None

    def normalizeToOne(self):
        if self.counter != None:
            raise Exception("Can't normalize after the counters have been created!")
        self.histoWrapper.normalizeToOne()

    def normalizeMCByCrossSection(self):
        if self.counter != None:
            raise Exception("Can't normalize after the counters have been created!")
        if self.histoWrapper.getDataset().isMC():
            self.histoWrapper.normalizeByCrossSection()

    def normalizeMCToLuminosity(self, lumi):
        if self.counter != None:
            raise Exception("Can't normalize after the counters have been created!")
        if self.histoWrapper.getDataset().isMC():
            self.histoWrapper.normalizeToLuminosity(lumi)

    def createCounter(self):
        self.counter = histoToCounter(self.histoWrapper.getHistogram())

    def getCounts(self):
        if self.counter == None:
            self.createCounter()
        return self.counter

    def getCountValue(self, name):
        if self.counter == None:
            self.createCounter()
        for c in self.counter:
            if c[0] == name:
                return c[1]
        raise Exception("No counter '%s'" % name)

# Counter for many datasets
class Counter:
    def __init__(self, histoWrappers):
        self.counters = [SimpleCounter(h) for h in histoWrappers]

    def forEachDataset(self, func):
        for c in self.counters:
            func(c)

    def normalizeToOne(self):
        self.forEachDataset(lambda x: x.normalizeToOne())

    def normalizeMCByCrossSection(self):
        self.forEachDataset(lambda x: x.normalizeMCByCrossSection())

    def normalizeMCByLuminosity(self):
        lumi = None
        for c in self.counters:
            if c.histoWrapper.getDataset().isData():
                if lumi != None:
                    raise Exception("Unable to normalize by luminosity, more than one data datasts (you might want to merge data datasets)")
                lumi = c.histoWrapper.getDataset().getLuminosity()
        if lumi == None:
            raise Exception("Unable to normalize by luminosity. no data datasets")

        self.normalizeMCToLuminosity(lumi)

    def normalizeMCToLuminosity(self, lumi):
        self.forEachDataset(lambda x: x.normalizeMCToLuminosity(lumi))

    def getCounterData(self):
        names = []

        # 2D list, counter[cut][dataset] (cut[row][column])
        counter = []

        # Loop over datasets
        for icounter, c in enumerate(self.counters):
            counts = c.getCounts()

            iname = 0
            icount = 0

            while iname < len(names) and icount < len(counts):
                # Check if the current indices give the same counter name for both
                if names[iname] == counts[icount][0]:
                    counter[iname].append(counts[icount][1])
                    iname += 1
                    icount += 1
                    continue

                # Search the list of names for the name of count
                found = False
                for i in xrange(iname, len(names)):
                    if names[i] == counts[icount][0]:
                        counter[i].append(counts[icount][1])
                        iname = i+1
                        icount += 1
                        found = True
                        continue
                if found:
                    continue

                # Count not found, insert the count after the previous
                # found name
                names.insert(iname, counts[icount][0])
                counter.insert(iname, [None]*icounter+[counts[icount][1]])
                iname += 1
                icount += 1

            if icount < len(counts):
                for name, count in counts[icount:]:
                    names.append(name)
                    counter.append([None]*icounter+[count])

            for c in counter:
                if len(c) < icounter+1:
                    c.extend([None] * (icounter+1-len(c)))

        return CounterData(names, [c.histoWrapper.getDataset().getName() for c in self.counters], counter)

    def getCountValue(self, datasetName, countName):
        for c in self.counters:
            if c.histoWrapper.getDataset().getName() == datasetName:
                return c.getCountValue(countName)

        raise Exception("No dataset '%s'" % datasetName)

    def printCounter(self, format=FloatAutoFormat()):
        printCounter(self.getCounterData(), format)

class CounterData:
    def __init__(self, countNames, columnNames, counter):
        self.countNames = countNames
        self.columnNames = columnNames
        self.counter = counter

        nameWidth = max([len(x) for x in self.countNames])
        self.countNameFormat = "%%-%ds" % (nameWidth+2)

        self.columnWidths = []
        for dname in self.columnNames:
            self.columnWidths.append(max(15, len(dname)+2))
        self.columnFormat = "%%%ds"

    def getNrows(self):
        return len(self.counter)

    def getNcolumns(self):
        return len(self.counter[0])

    def getColumnWidth(self, icol):
        return self.columnWidths[icol]

    def getCount(self, irow, icol):
        return self.counter[irow][icol]

    def formatHeader(self):
        header = self.countNameFormat % "Counter"
        for i, dname in enumerate(self.columnNames):
            header += (self.columnFormat%self.columnWidths[i]) % dname
        return header

    def formatFirstColumn(self, irow):
        return self.countNameFormat % self.countNames[irow]


def isHistogram(obj):
    return isinstance(obj, ROOT.TH1)

# Many counters
class EventCounter:
    def __init__(self, datasets):
        counterNames = {}

        if len(datasets.getAllDatasets()) == 0:
            raise Exception("No datasets")

        # Pick all possible names of counters
        counterDir = None
        for dataset in datasets.getAllDatasets():
            if counterDir == None:
                counterDir = dataset.getCounterDirectory()
            else:
                if counterDir != dataset.getCounterDirectory():
                    raise Exception("Sanity check failed, datasets have different counter directories!")

            for name in dataset.getDirectoryContent(counterDir, isHistogram):
                counterNames[name] = 1

        try:
            del counterNames["counter"]
        except KeyError:
            raise Exception("Internal error: no 'counter' histogram in the '%s' directories" % counterDir)

        self.mainCounter = Counter(datasets.getHistoWrappers(counterDir+"/counter"))
        self.subCounters = {}
        for subname in counterNames.keys():
            self.subCounters[subname] = Counter(datasets.getHistoWrappers(counterDir+"/"+subname))

        self.normalization = "None"

    def forEachCounter(self, func):
        func(self.mainCounter)
        for c in self.subCounters.itervalues():
            func(c)

    def normalizeToOne(self):
        self.forEachCounter(lambda x: x.normalizeToOne())
        self.normalization = "All normalized to unit area"

    def normalizeMCByCrossSection(self):
        self.forEachCounter(lambda x: x.normalizeMCByCrossSection())
        self.normalization = "MC normalized to cross section (pb)"

    def normalizeMCByLuminosity(self):
        self.forEachCounter(lambda x: x.normalizeMCByLuminosity())
        self.normalization = "MC normalized by data luminosity"

    def normalizeMCToLuminosity(self, lumi):
        self.forEachCounter(lambda x: x.normalizeMCToLuminosity(lumi))
        self.normalization = "MC normalized to luminosity %f pb^-1" % lumi

    def getMainCounter(self):
        return self.mainCounter

    def getMainCounterData(self):
        return self.mainCounter.getCounterData()

    def getSubCounterNames(self):
        return self.subCounters.keys()

    def getSubCounter(self, name):
        return self.subCounters[name]

    def getSubCounterData(self, name):
        return self.subCounters[name].getCounterData()

    def getNormalizationString(self):
        return self.normalization
