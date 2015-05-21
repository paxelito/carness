#!/usr/bin/env python
# -*- coding: latin-1 -*-
'''
	Script to compute the successive cell division times and the value of each molecule in proximity of the cell division.
	Please digit::

		python <path>/acsDuplicationAnalysis.py -h

	for the SYNOPSIS of the script. 

	In particular, a folder named _0_new_allStatResults will be created into the chemistry and three files will be stored there:

	1. deltat_<CHEMISTRY>.csv: In this file the cell division time and the overall amount of molecules at each division are stored
	2. delta_ALL_<CHEMISTRY>.csv: In this file the overall amount of each molecular species at each division is stored
	3. divplot_<CHEMISTRY>.[png/eps]: If `param --graphs -g`, hence the plot of the species amount at each generation is generated. 
'''

import sys, os # Standard library
import datetime as dt
import linecache as lc
import glob
from argparse import ArgumentParser
import numpy as np # Scientific library
from numpy import * 
from lib.visual import graphics as gr
from lib.miscellaneous import utilities as ut

try:
    from pylab import *
except:
    pass
   
from lib.IO import *

if __name__ == '__main__':
	parser = ArgumentParser(
				description='Protocell division and synchronization assessment'
				, epilog='''File with angle trajectories are created. ''') 
	parser.add_argument('-p', '--StrPath', help='Path where files are stored (def: ./)', default='./')
	parser.add_argument('-l', '--lastFlux', help='Last flux ID species (def: 5)', default='5', type=int)
	parser.add_argument('-m', '--species', help='Number of species (def: 126)', default='126', type=int)
	parser.add_argument('-d', '--divisions', help='Number of divisions (def: 100)', default='100', type=int)
	parser.add_argument('-g', '--graphs', help='Draw graphs (def: 0)', action="store_true", default=False)
	parser.add_argument('-c', '--cols2plot', help='cols to plot', nargs='*', default=[], type=int)
	args = parser.parse_args()
	
	print "Simulation Results Path: ", args.StrPath
	
	StrPath = os.path.abspath(args.StrPath)
		
	tmpDirs = sort(os.listdir(StrPath))
	
	os.chdir(StrPath)
	
	#currentDir = StrPath.split("/")[-1]
	currentDir = ''
	ndn = currentDir + '_0_new_allStatResults'
	newdirAllResults = os.path.abspath(os.path.join(os.curdir, ndn))
	if not os.path.isdir(newdirAllResults):
		try:
			os.mkdir(newdirAllResults)
		except:
			print "Impossible to create statistic directory", newdirAllResults; sys.exit(1)
			
	validDir = 1
	for IDdir, tmpDir in enumerate(tmpDirs):
		dupTime = []
		totDirName = os.path.join(StrPath,tmpDir)
		if os.path.isdir(totDirName):
			# Move to the directory 
			os.chdir(newdirAllResults)
			#fid_deltat = open(f_name, 'w')
		  	os.chdir(StrPath)			
			os.chdir(totDirName)
			resDirPath = os.path.abspath(os.path.join("./", "res"))
			print " |- Results Folder: ", resDirPath
			if os.path.isdir(resDirPath):
				os.chdir(resDirPath)
				# Find the number of generations
				numberOfGen = len(glob.glob(os.path.join(resDirPath,'times_*')))
				dupTime = np.zeros((numberOfGen,2))
				dupTimeSingleX = np.zeros((numberOfGen,args.species))
								
				for idgen, ngen in enumerate(range(1,numberOfGen+1)):
					
					print "|- Generation ", idgen+1
				
					strZeros = ut.zeroBeforeStrNum(ngen, args.divisions)
					
					strSpecies = 'timeSpeciesAmount_' + strZeros + str(ngen) + '*'
					#strSpecies = 'timeSpeciesAmount_00' + strZeros + str(ngen) + '*'  
					
					# Searching for files
					speciesFiles = sorted(glob.glob(os.path.join(resDirPath,strSpecies)))
					
					for idS, sngSpeciesFile in enumerate(speciesFiles):
					
					#print '  |- Species File: ', sngSpeciesFile	
						data = np.loadtxt(open(sngSpeciesFile,"rb"),delimiter="\t")
						totX = 0
						for i in range(data.shape[1]):
							if i > args.lastFlux+3:
								totX += data[-1,i]
								
							if (i > 2) & (i < args.species+3):
								dupTimeSingleX[idgen,i-3]=data[-1,i]
							
						dupTime[idgen,0] = data[-1,1]
						dupTime[idgen,1] = totX
					  				  	
				# Creare file where store data
				f_name = os.path.join(newdirAllResults,"deltat_" + tmpDir +".csv")
			  	np.savetxt(f_name, dupTime, fmt='%.4f', delimiter='\t')
			  	f_name = os.path.join(newdirAllResults,"deltat_ALL_" + tmpDir +".csv")
			  	np.savetxt(f_name, dupTimeSingleX, fmt='%.4f', delimiter='\t')
			  	if args.graphs == 1:
			  		if len(args.cols2plot) == 0: 
			  			cols2plot = range(args.lastFlux+1,args.species)
			  		else:
			  			cols2plot = args.cols2plot[:]
			  		# Create reduce data frame
			  		reducedData = dupTimeSingleX[:,cols2plot]
			  		fn = os.path.join(newdirAllResults,"divplot_" + tmpDir)
			  		gr.PlotMatrix(fn,range(1,reducedData.shape[0]+1), reducedData, 'Divisions', 'Amount', cols2plot)

				
						
						