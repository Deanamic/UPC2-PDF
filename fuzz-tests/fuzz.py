#!/usr/bin/env python2

from __future__ import division
import tempfile
import shutil
import os
import os.path
import subprocess

NUM_TESTS = 100

# change to script directory
# from http://stackoverflow.com/a/9350788/7757713
scriptdir = os.path.dirname(os.path.realpath(__file__))
os.chdir(scriptdir)

TEMPDIR = tempfile.mkdtemp("FUZZ-TEST")
FUZZDIR = os.path.join(TEMPDIR, "fuzz-tests")
os.mkdir(FUZZDIR)

testfiles = []
for f in os.listdir("."):
    if f.endswith(".cpp"):
        testfiles.append(f)

print "Copying files..."
shutil.copy("../content/contest/Makefile", FUZZDIR)
os.symlink(os.path.abspath("../content"), os.path.join(TEMPDIR, "content"))
for t in testfiles:
    shutil.copy(t, FUZZDIR)

print "Compiling..."
for t in testfiles:
    print t
    subprocess.check_call(["make", os.path.splitext(t)[0]], cwd = FUZZDIR)

for t in testfiles:
    print "Testing", t
    for i in xrange(NUM_TESTS):
        subprocess.check_call(["./" +os.path.splitext(t)[0], str(i)], cwd = FUZZDIR)
        if (i+1) % 10 == 0:
            print (i+1)/NUM_TESTS * 100, "% completed"
