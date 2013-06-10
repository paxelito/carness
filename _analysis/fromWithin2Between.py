#!/usr/bin/env python

# from 2.4.5
# the analysis is able to go though different folder organized in the same way with the same result folder

#import sys, os, shutil
import sys, os # Standard library
import glob # To manage files in directory

def zeroBeforeStrNum(tmpl, tmpL):
	strZero = ''
	nZeros = len(str(tmpL)) - len(str(tmpl))
	if nZeros > 0:
		for i in range(0,nZeros): strZero = strZero + '0'
	return strZero
#eof

# get path for placing simulation
try:
	StrPath = sys.argv[1] # Here the path of the simulation output file
	numSim = int(sys.argv[2])
	numGen = int(sys.argv[3])
except:
	print "Usage:",sys.argv[0], "infile outfile"; sys.exit(1)
	

# Moving in the simulation directory
os.chdir(StrPath)

# FOLDERS
print "Create folders..."

for i in range(1,numSim+1):

	zeroSIM = zeroBeforeStrNum(i,numSim)
	
	for j in range(1, numGen+1):
	
		zeroGEN = zeroBeforeStrNum(j,numGen)
		
		folderNew = "s_" + zeroSIM + str(i) + "_" + zeroGEN + str(j)
		
		if not os.path.isdir(folderNew):
			try:
				os.mkdir(folderNew)
			except:
				print "Impossible to create sim directory"; sys.exit(1)
				
		# Res folder creation
		os.chdir(folderNew)
		# Create iGraph directory where iGraph_CAT file will be stored
		resdir = os.path.join(os.curdir, "res")
		if not os.path.isdir(resdir):
			try:
				os.mkdir(resdir)
			except:
				print "Impossible to create result directory"; sys.exit(1)
				
		# Come back to the previous folder 
		os.chdir("../")
		
		# Move results from source to results 
		os.chdir(StrPath)
		
		
		

# Move results...
print "Move Results..."

# Move overall results...
print "Move Overall Results..."

# Move Final Files...
print "Move Final Files..."

# Copy initial files within the folders
print "Copy initial files within the folders..."



