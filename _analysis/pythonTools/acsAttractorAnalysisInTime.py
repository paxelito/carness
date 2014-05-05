#!/usr/bin/env python
# -*- coding: latin-1 -*-

'''Function to analyse the different attractors emerging from different simulations in time. 
'''

import sys, os # Standard library
import datetime as dt
import linecache as lc
import glob
import numpy as np # Scientific library
from numpy import * 

try:
    from pylab import *
except:
    pass

#--------------------------------------------------------------------------------------
# Function to create string zero string vector before graph filename. 
# According to the total number of reactions N zeros will be add before the instant reaction number 
# (e.g. reaction 130 of 10000 the string became '00130')
def zeroBeforeStrNum(tmpl, tmpL):
	strZero = ''
	nZeros = len(str(tmpL)) - len(str(tmpl))
	if nZeros > 0:
		for i in range(0,nZeros): strZero = strZero + '0'
	return strZero

# Input parameters definition 
if __name__ == '__main__':
	parser = ArgumentParser(
				description='ELDA (Emergent Levell Dynamic	 Assessment).'
				, epilog='''Copyright Alessandro Filisetti 2013 ''') 
	parser.add_argument('-p', '--StrPath', help='Simulation outcomes path', default='./')
	parser.add_argument('-l', '--tmpMaxFluxL', type=int, help='Max length of the incoming flux', default=2)
	parser.add_argument('-f', '--tmpNOF', type=int, help='Number of files for each generation', default=101)
	args = parser.parse_args()

	# Convert path in absolute path
	StrPath = os.path.abspath(args.StrPath)
	
	today = dt.date.today()
	
	print ''
	print 'ACS ATTRACTORS ANALYSER IN TIME'
	print ''
	
	# For each file species 
	for timeFileID in range(0,args.tmpNOF):
			
		tmpDirs = sort(os.listdir(StrPath))
		allSortedSpecies = [] 
		allConcentrations = [] 
		allSortedSpeciesNOINFLUX = [] 
		allConcentrationsNOINFLUX = [] 
		print '|- - - - - - - - - - - - - - - - '
		print '|- Species Files Number: ', timeFileID
		print '|- - - - - - - - - - - - - - - - '
		print '  |- STEP 1. Creating common sorted species list...'
		for tmpDir in tmpDirs:
			os.chdir(StrPath)
			totDirName = os.path.join(StrPath,tmpDir)
			if os.path.isdir(totDirName):
				# Move to the directory 
				os.chdir(totDirName)
				resDirPath = os.path.abspath(os.path.join("./", "res"))
				print "  |- Results Folder: ", resDirPath
				if os.path.isdir(resDirPath):
					os.chdir(resDirPath)
					
					# Find the number of generations
					numberOfGen = len(glob.glob(os.path.join(resDirPath,'times_*')))
					
					for ngen in range(1,numberOfGen+1):
					  
					  strZeros = zeroBeforeStrNum(ngen, numberOfGen)
					  
					  if ngen == 1:
					  	strSpeciesZero = 'species_' + strZeros + str(0) + '*'
					  	speciesFilesZero = sorted(glob.glob(os.path.join(resDirPath,strSpeciesZero)))
					  	
					  strSpecies = 'species_' + strZeros + str(ngen) + '*'
						  
					  # Searching for files
					  speciesFiles = sorted(glob.glob(os.path.join(resDirPath,strSpecies)))
					  
					  if ngen == 1:
					  	speciesFiles = speciesFilesZero + speciesFiles
					  	
					  speciesFile = speciesFiles[timeFileID]
					  
				  
					  # Open Catalysis File
					  try:
						  fidSpecies = open(speciesFile, 'r')
					  except:
						  print '  |- impossible to load ', speciesFile; sys.exit(1)
					  
					  # For each last species file
					  seq = []; conc = []; seqNOINFLUX = []
					  for sp in fidSpecies:
						  tmpID, tmpSeq, tmpConc, tmpDiff, tmpSol, tmpCpxDiss, tmpCpxCut, tmpEval, tmpAge, tmpReb, tmpCatID, tmpSubID, tmpKpho, tmpLoadConc, tmpConcLock = sp.split()
						  if (int(tmpCpxCut) == 0) & (float(tmpConc) > 0):
							  seq.append(str(tmpSeq))
							  conc.append(float(tmpConc))
							  if len(str(tmpSeq)) > args.tmpMaxFluxL:
								  seqNOINFLUX.append(str(tmpSeq))	
					  # Common ordered species List 
					  allSortedSpecies = list(set(seq) | set(allSortedSpecies))
					  allSortedSpecies.sort()	
					  # NO influx
					  allSortedSpeciesNOINFLUX = list(set(seqNOINFLUX) | set(allSortedSpeciesNOINFLUX))
					  allSortedSpeciesNOINFLUX.sort()	
					  
					  fidSpecies.close()	
				else: 
					  print "  |- no result folder has been found"
					
		print '  |- STEP 2. Creating species concentration lists according to the overall sorted species list...'		
		overallConcList = []
		overallConcListNOINFLUX = []
		numberOfFolders = 0
		for tmpDir in tmpDirs:
			os.chdir(StrPath)
			totDirName = os.path.join(StrPath,tmpDir)
			if os.path.isdir(totDirName):
				# Move to the directory 
				os.chdir(totDirName)
				resDirPath = os.path.join(totDirName, "res")
				if os.path.isdir(resDirPath):
					
					os.chdir(resDirPath)
					
					# Find the number of generations
					numberOfGen = len(glob.glob(os.path.join(resDirPath,'times_*')))
				
					for ngen in range(1,numberOfGen+1):
					  
					  numberOfFolders += 1
					  
					  strZeros = zeroBeforeStrNum(ngen, numberOfGen)
					  
					  if ngen == 1:
					  	strSpeciesZero = 'species_' + strZeros + str(0) + '*'
					  	speciesFilesZero = sorted(glob.glob(os.path.join(resDirPath,strSpeciesZero)))
					  	
					  strSpecies = 'species_' + strZeros + str(ngen) + '*'
						  
					  # Searching for files
					  speciesFiles = sorted(glob.glob(os.path.join(resDirPath,strSpecies)))
					  
					  if ngen == 1:
					  	speciesFiles = speciesFilesZero + speciesFiles
					  	
					  speciesFile = speciesFiles[timeFileID]
					  
				  
					  print " |- Species File: ", speciesFile
					  # Open Catalysis File
					  try:
						  fidSpecies = open(speciesFile, 'r')
					  except:
						  print ' |- impossible to load ', speciesFile; sys.exit(1)
					  
					  # For each last species file
					  seq = []; conc = []; speciesConc = []; speciesConcNOINFLUX = []
					  for sp in fidSpecies:
						  tmpID, tmpSeq, tmpConc, tmpDiff, tmpSol, tmpCpxDiss, tmpCpxCut, tmpEval, tmpAge, tmpReb, tmpCatID, tmpSubID, tmpKpho, tmpLoadConc, tmpConcLock = sp.split()
						  if (int(tmpCpxCut) == 0) & (float(tmpConc) > 0):
							  seq.append(str(tmpSeq))
							  conc.append(float(tmpConc))
							  
					  # Check the presence of the species in the all common species list		
					  for key in allSortedSpecies:
						  try:
							  pos = seq.index(key)
							  speciesConc.append(conc[pos])
						  except:
							  speciesConc.append(0)
					  for key2 in allSortedSpeciesNOINFLUX:
						  try:
							  pos2 = seq.index(key2)
							  speciesConcNOINFLUX.append(conc[pos2])
						  except:
							  speciesConcNOINFLUX.append(0)
					  
					  # Add the concentration list in the concentrationS list
					  overallConcList.append(speciesConc)
					  overallConcListNOINFLUX.append(speciesConcNOINFLUX)	
					  			  
					  fidSpecies.close()	
					
		print '  |- STEP 3. Compute attractors differences (in term of different multi-dimensional angles)'	
		ANG_overallResMatrix = np.zeros((numberOfFolders,numberOfFolders))
		ANG_overallResMatrixNOINFLUX = np.zeros((numberOfFolders,numberOfFolders))
		HAM_overallResMatrix = np.zeros((numberOfFolders,numberOfFolders))
		HAM_overallResMatrixNOINFLUX = np.zeros((numberOfFolders,numberOfFolders))
		EUC_overallResMatrix = np.zeros((numberOfFolders,numberOfFolders))
		EUC_overallResMatrixNOINFLUX = np.zeros((numberOfFolders,numberOfFolders))
		
		# Angle between lists is now computed
		for idx, lx in enumerate(overallConcList):
			for idy, ly in enumerate(overallConcList):
				vecX = np.array(lx)
				vecY = np.array(ly)
				# Compute coseno
				tmpCos = float(np.dot(vecX,vecY) / (np.linalg.norm(vecX) * np.linalg.norm(vecY)))
				if tmpCos >= 1.0: tmpCos = 1.0
				ANG_overallResMatrixNOINFLUX[idx,idy] = np.arccos(tmpCos)  * 360.00 / 6.28
				# HAMMING DISTANCE and EUCLIDEAN DISTANCE
				tmpHD = 0
				tmpEU = 0
				for pos, x in enumerate(lx):
					if ((x > 0.0) & (ly[pos] == 0.0)) | ((x == 0.0) & (ly[pos] > 0.0)):
						tmpHD += 1
					tmpEU += pow(x - ly[pos],2)
					
				HAM_overallResMatrix[idx,idy] = tmpHD
				EUC_overallResMatrix[idx,idy] = pow(tmpEU,0.5)		
				
		for idx, lx in enumerate(overallConcListNOINFLUX):
			for idy, ly in enumerate(overallConcListNOINFLUX):
				vecX = np.array(lx)
				vecY = np.array(ly)
				# Compute coseno
				tmpCos = float(np.dot(vecX,vecY) / (np.linalg.norm(vecX) * np.linalg.norm(vecY)))
				if tmpCos >= 1.0: tmpCos = 1.0
				ANG_overallResMatrixNOINFLUX[idx,idy] = np.arccos(tmpCos)  * 360.00 / 6.28
				# HAMMING DISTANCE and EUCLIDEAN DISTANCE
				tmpHD = 0
				tmpEU = 0
				for pos, x in enumerate(lx):
					if ((x > 0.0) & (ly[pos] == 0.0)) | ((x == 0.0) & (ly[pos] > 0.0)):
						tmpHD += 1
					tmpEU += pow(x - ly[pos],2)
					
				HAM_overallResMatrixNOINFLUX[idx,idy] = tmpHD
				EUC_overallResMatrixNOINFLUX[idx,idy] = pow(tmpEU,0.5)
		
		print '  |- STEP 3. Save Files'
		os.chdir(StrPath)
		ndn = '_0_new_allStatResults'
		newdirAllResults = os.path.join(os.curdir, ndn)
		if not os.path.isdir(newdirAllResults):
			try:
				os.mkdir(newdirAllResults)
			except:
				print "Impossible to create statistic directory", newdirAllResults; sys.exit(1)
				
		os.chdir(newdirAllResults)
		
		ndn = 'allTimes'
		newdirAllResults = os.path.join(os.curdir, ndn)
		if not os.path.isdir(newdirAllResults):
			try:
				os.mkdir(newdirAllResults)
			except:
				print "Impossible to create statistic directory", newdirAllResults; sys.exit(1)
				
		os.chdir(newdirAllResults)
		
		tmpZeroSaving = zeroBeforeStrNum(timeFileID, args.tmpNOF)
		# ''' Save concentration vectors"
		print '   |- Saving species Concentrations list...'
		outFnameStat = 'speciesVector' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		for sngSimConc in overallConcList:
			strTypes = ''
			for j in allSortedSpecies:
				strTypes += j + '\t'
			strTypes += '\n'
			for j in sngSimConc:
				strTypes += str(j) + '\t'
			strTypes += '\n'
			saveFileStat.write(strTypes)
		saveFileStat.close()
		
		# ''' Save concentration vectors (NO INFLUX)"
		print '   |- Saving species Concentrations list (NO INFLUX)...'
		outFnameStat = 'speciesVectorNOINFLUX' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		for sngSimConcNOINFLUX in overallConcListNOINFLUX:
			strTypes = ''
			for j in allSortedSpeciesNOINFLUX:
				strTypes += j + '\t'
			strTypes += '\n'
			for j in sngSimConcNOINFLUX:
				strTypes += str(j) + '\t'
			strTypes += '\n'
			saveFileStat.write(strTypes)
		saveFileStat.close()
		
		# '''Function to save statistic on file'''
		print '   |- Saving coseno...'
		outFnameStat = 'acsAttractorsAnalysis_COSENO' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(ANG_overallResMatrix[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()	
		
		print '   |- Saving coseno (NO INFLUX)...'
		outFnameStat = 'acsAttractorsAnalysisNOINFLUX_COSENO' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(ANG_overallResMatrixNOINFLUX[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()	
		
		print '   |- Saving HAMMING DISTANCES...'
		outFnameStat = 'acsAttractorsAnalysis_HAMMING' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(HAM_overallResMatrix[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()	
		
		print '   |- Saving HAMMING DISTANCES (NO INFLUX)...'
		outFnameStat = 'acsAttractorsAnalysisNOINFLUX_HAMMING' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(HAM_overallResMatrixNOINFLUX[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()	
		
		print '   |- Saving EUCLIDEAN DISTANCES...'
		outFnameStat = 'acsAttractorsAnalysis_EUCLIDEAN' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(EUC_overallResMatrix[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()	
		
		print '   |- Saving HAMMING EUCLIDEAN (NO INFLUX)...'
		outFnameStat = 'acsAttractorsAnalysisNOINFLUX_EUCLIDEAN' + str(tmpZeroSaving) + str(timeFileID) + '.csv'
		saveFileStat = open(outFnameStat, 'w')
		cnt = 0
		for i in range(numberOfFolders):
			strTypes = ''
			for j in range(numberOfFolders):
				strTypes += str(EUC_overallResMatrixNOINFLUX[j,i]) + '\t'	
			strTypes += '\n'
			saveFileStat.write(strTypes)
			cnt += 1
		saveFileStat.close()
		
		
		os.chdir(StrPath)
		
	print '|- FINISHED... SEE YOU NEXT TIME'		
			

			
					
						
				
			
			

			
    			


					
					

			
				

	
	
