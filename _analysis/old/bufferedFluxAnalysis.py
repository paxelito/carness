#!/usr/bin/env python
'''Function to observe the flux dynamics in protocell representation. Since the flux is buffered the actual dynamics of the flux is lose'''

import sys, os # Standard library
import datetime as dt
import glob
import numpy as np # Scientific library
from numpy import * 

try:
    from pylab import *
except:
    pass			

# get path for placing simulation
# INPUT PARAMETERS
try:
	StrPath = sys.argv[1] # Here the path of the simulation output file
	tmpResFold = sys.argv[2] # Subfolder containing all the simulation outcomes
except:
	print "Usage:",sys.argv[0], "infile outfile"; sys.exit(1)
	
print "|- Simulation Results Path: ", StrPath

today = dt.date.today()

#cmdFileName = StrPath + '/' + str(today) + '_' + str(threshold) + '_convOverThreshold_' + str(decayTime) + '.csv'
#if  os.path.isfile(cmdFileName):
#	os.remove(cmdFileName)
	
simF = StrPath + '/' + tmpResFold + '*'
tmpDirs = sort(glob.glob(simF))
	
#cmdFileFid = open(cmdFileName, 'a')

#strToWrite = "\tReaction Probability" + "\tEnergy Concentration" + "\tMean Over Threshold" + "\tTot over Threshold" + "\tReal ACSs" + "\tin ACSs" + "\tLeaves" + "\tby Chain" + "\tOverlap" + "\tAutocatalysis" + "\tin ACSs (W)" + "\tLeaves (W)" + "\tby Chain (W)" + "\tOverlap (W)" + "\tAutocatalysis (W)" +"\t[ACS]" + "\t[Leaves]" + "\t[Chains]" + "\t[Self]" + "\tEndo Cond" + "\tCond" + "\tEndo Cleavage" + "\tCleavage" + "\tWasted species" + "\n"
#cmdFileFid.write(strToWrite)

newdir = os.path.join(os.curdir, '0_statistics')
if not os.path.isdir(newdir):
	try:
		os.mkdir(newdir)
	except:
		print "Impossible to create iGraph directory"; sys.exit(1)
		
matrixTimeLITE = np.zeros((101,len(tmpDirs)))
matrixFluxLITE = np.zeros((101,len(tmpDirs)))
matrixAbsLITE = np.zeros((101,len(tmpDirs)))
matrixExpLITE = np.zeros((101,len(tmpDirs)))	

tmpDirsCnt = 0			

for tmpDir in tmpDirs:
	print "|- SIMULATION FOLDER ",tmpDir
	
	if os.path.isdir(tmpDir):
	
		print '\t|- Going into res folder...'
		
		if os.path.isdir(os.path.join(tmpDir, "res")):
			os.chdir(os.path.join(tmpDir, "res"))	
			
			# Searching for files
			speciesFiles = sort(glob.glob('species_*'))
									
			print "\t|- Loading buffered species from", speciesFiles[0]
		
			# Open Species File
			try:
				fidSpecies = open(speciesFiles[0], 'r')
			except:
				print '\timpossible to load ', speciesFile; sys.exit(1)
		
			# For each last species file
				ok = 0
			fluxIndexes = []
			fluxLengths = []
		
			for sp in fidSpecies:
		
				tmpID, tmpSeq, tmpConc, tmpDiff, tmpSol, tmpCpxDiss, tmpCpxCut, tmpEval, tmpAge, tmpReb, tmpCatID, tmpSubID, tmpKpho, tmpLoadConc, tmpConcFixed = sp.split()
			
				index = int(tmpID)
				speciesSeq = len(tmpSeq)
				concFixed = int(tmpConcFixed)
			
				if concFixed == 1:
					fluxIndexes.append(index)
					fluxLengths.append(speciesSeq)
					
			fidSpecies.close()	
	
			# Create the file list
			fileslist = sort(glob.glob('reactions_parameters_*'))
			rctParFileNum = 1
			rctID = 1
			
			totFluxDyn = []
			absorbedBricks = []
			tempAbsorbedBricks = 0
			expelledBricks = []
			tempExpelledBricks = 0
			totTimes = []
			
			#top For Global saving
			totFluxDyn_LITE = []
			absorbedBricks_LITE = []
			expelledBricks_LITE = []
			totTimes_LITE = []
			
			# For each file
			for file in fileslist:
				
				#open file
				print '\t|- Opening file ', file
				fid = open(file, 'r')
				
				okmonitor = 1 # flag to control the monitor output
				oksaveLite = 0 # Flag to control the 10 seconds saving process
								
				for line in fid:
				
					deltaRct = 0
										
					# Load single reaction parameters
					# tmpReaction, tmpTime, tmpcc, tmpCat, tmpMol_I, tmpMol_II, tmpMol_III, tmpEC, tmpECload = line.split()
					tmpReaction, tmpTime, tmpcc, tmpCat, tmpMol_I, tmpMol_II, tmpMol_III, tmpLoadedMols, tmpLoadedMolsConc, tmpGillMean, tmpGillSD, tmpGillEntropy, tmpNSP, tmpRevRatio = line.split()
					reaction = int(tmpReaction)
					rtime = float(tmpTime)
					cc = int(tmpcc) 
					cat = int(tmpCat)
					mol_I = int(tmpMol_I)
					mol_II = int(tmpMol_II)
					mol_III = int(tmpMol_III)
					loadedMolsConc = float(tmpLoadedMolsConc)
					loadedMols = int(tmpLoadedMols)
					gillMean = float(tmpGillMean)
					gillSD = float(tmpGillSD)
					gillEntropy = float(tmpGillEntropy)
								
					if (cc == 0)|(cc == 7): # CONDENSATION and ENDO CONDENSATION
						if mol_I in fluxIndexes:
							deltaRct = deltaRct - fluxLengths[fluxIndexes.index(mol_I)]
							tempExpelledBricks = tempExpelledBricks + fluxLengths[fluxIndexes.index(mol_I)]
						if mol_II in fluxIndexes:
							deltaRct = deltaRct + fluxLengths[fluxIndexes.index(mol_II)]
							tempAbsorbedBricks = tempAbsorbedBricks + fluxLengths[fluxIndexes.index(mol_II)]
						if mol_III in fluxIndexes:
							deltaRct = deltaRct + fluxLengths[fluxIndexes.index(mol_III)]
							tempAbsorbedBricks = tempAbsorbedBricks + fluxLengths[fluxIndexes.index(mol_III)]
																					
					else: # CLEAVAGE (The same of condensation expected for the double computation due to the presence of two products
						if mol_I in fluxIndexes:
							deltaRct = deltaRct + fluxLengths[fluxIndexes.index(mol_I)]
							tempAbsorbedBricks = tempAbsorbedBricks + fluxLengths[fluxIndexes.index(mol_I)]
						if mol_II in fluxIndexes:
							deltaRct = deltaRct - fluxLengths[fluxIndexes.index(mol_II)]
							tempExpelledBricks = tempExpelledBricks + fluxLengths[fluxIndexes.index(mol_II)]
						if mol_III in fluxIndexes:
							deltaRct = deltaRct - fluxLengths[fluxIndexes.index(mol_III)]
							tempExpelledBricks = tempExpelledBricks + fluxLengths[fluxIndexes.index(mol_III)]
					
					if rctID == 1:
						totFluxDyn.append(deltaRct)
					else:
						totFluxDyn.append(totFluxDyn[-1] + deltaRct)
					absorbedBricks.append(tempAbsorbedBricks)
					expelledBricks.append(tempExpelledBricks)
					totTimes.append(rtime)
					
					if (round(rtime) % 100 == 0) & (okmonitor == 1):
						print '\t\t ', rtime, ' delta flux: ', deltaRct, ' tot: ', totFluxDyn[rctID-1], ' exp bricks: ', tempExpelledBricks, ' absorbed bricks: ', tempAbsorbedBricks
						okmonitor = 0		
					if (round(rtime)) % 100 == 1:
						okmonitor = 1	
						
					# Saving data to create a shorter report
					if rtime >= oksaveLite * 10:
						totFluxDyn_LITE.append(totFluxDyn[-1])
						absorbedBricks_LITE.append(absorbedBricks[-1])
						expelledBricks_LITE.append(expelledBricks[-1])
						totTimes_LITE.append(totTimes[-1])
						oksaveLite = oksaveLite + 1			
					
					# Reactions counters is updated			
					rctID = rctID + 1	
				
				# Always save the last step
				if len(totFluxDyn_LITE) < 101:
					totFluxDyn_LITE.append(totFluxDyn[-1])
					absorbedBricks_LITE.append(absorbedBricks[-1])
					expelledBricks_LITE.append(expelledBricks[-1])
					totTimes_LITE.append(totTimes[-1])
										
				savingMatrix = np.zeros((len(totTimes),4))
				savingMatrix[:,0] = totTimes
				savingMatrix[:,1] = totFluxDyn
				savingMatrix[:,2] = absorbedBricks
				savingMatrix[:,3] = expelledBricks				
					
				# Save results in folder 0_statistics
				tmpDirSplit = tmpDir.split("/")
				cmdFileName = StrPath + '0_statistics/0_fluxDynamics_' + tmpDirSplit[-1] + '.csv'
				if  os.path.isfile(cmdFileName):
					os.remove(cmdFileName)
				cmdFileFid = open(cmdFileName, 'a')
				np.savetxt(cmdFileFid, savingMatrix, '%.4f\t%d\t%d\t%d')
				cmdFileFid.close()
				
			matrixTimeLITE[:,tmpDirsCnt] = totTimes_LITE
			matrixFluxLITE[:,tmpDirsCnt] = totFluxDyn_LITE
			matrixAbsLITE[:,tmpDirsCnt] = absorbedBricks_LITE
			matrixExpLITE[:,tmpDirsCnt] = expelledBricks_LITE	

			tmpDirsCnt = tmpDirsCnt + 1	
				
cmdFileName = StrPath + '0_statistics/0_fluxDynamics_ALL_times.csv'
if  os.path.isfile(cmdFileName):
	os.remove(cmdFileName)
cmdFileFid = open(cmdFileName, 'a')
np.savetxt(cmdFileFid, matrixTimeLITE, '%.4f\t')
cmdFileFid.close()			
					
cmdFileName = StrPath + '0_statistics/0_fluxDynamics_ALL_deltaflux.csv'
if  os.path.isfile(cmdFileName):
	os.remove(cmdFileName)
cmdFileFid = open(cmdFileName, 'a')
np.savetxt(cmdFileFid, matrixFluxLITE, '%d\t')
cmdFileFid.close()	

cmdFileName = StrPath + '0_statistics/0_fluxDynamics_ALL_absorbed.csv'
if  os.path.isfile(cmdFileName):
	os.remove(cmdFileName)
cmdFileFid = open(cmdFileName, 'a')
np.savetxt(cmdFileFid, absorbedBricks_LITE, '%d\t')
cmdFileFid.close()	

cmdFileName = StrPath + '0_statistics/0_fluxDynamics_ALL_expelled.csv'
if  os.path.isfile(cmdFileName):
	os.remove(cmdFileName)
cmdFileFid = open(cmdFileName, 'a')
np.savetxt(cmdFileFid, expelledBricks_LITE, '%d\t')
cmdFileFid.close()	