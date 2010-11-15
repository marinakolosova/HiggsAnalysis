#!/usr/bin/env python

import os
import sys
import glob
import shutil
import tarfile
from optparse import OptionParser

import HiggsAnalysis.HeavyChHiggsToTauNu.tools.multicrab as multicrab

def main(opts, args):
    workdir = os.getcwd()
    for d in opts.dirs:
        # Go to task directory (in order to get the paths in the archive correctly easily)
        os.chdir(d)

        # Create the tar archive
        tar = tarfile.open("task.tar.gz", mode="w:gz")
        files = []
        for f in ["CMSSW_*.std*", "crab_fjr_*.xml", "Submission_*"]:
            files.extend(glob.glob(os.path.join("res", f)))
        
        files.extend(["job", "log", "share"])

        #print "\n".join(files)

        for f in files:
            tar.add(f)
        tar.close()

        # Delete the files just added to the archive
        for f in files:
            if os.path.isfile(f):
                #print "rm "+f
                os.remove(f)
            elif os.path.isdir(f):
                #print "rm -fR "+f
                shutil.rmtree(f)
            else:
                print "Not removing "+f

        os.chdir(workdir)

if __name__ == "__main__":
    parser = OptionParser(usage="Usage: %prog [options]")
    multicrab.addOptions(parser)

    (opts, args) = parser.parse_args()
    if len(opts.dirs) == 0:
        parser.error("No directories given (-d option)")

    sys.exit(main(opts, args))

