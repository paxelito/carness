#!/usr/bin/env python
# -*- coding: latin-1 -*-
'''Script to order the analysis of the divergences in time. 
'''
import sys, os # Standard librar
import glob
import numpy as np # Scientific library
from numpy import * 
from argparse import ArgumentParser
try:
    from pylab import *
except:
    pass

#�Input parameters definition 
if __name__ == '__main__':
	parser = ArgumentParser(
				description='This script re-arrange results in a more friendly way from the angle analysis in time.'
				, epilog='''File with angle trajectories are created. ''') 
	parser.add_argument('-p', '--strPath', help='Path where files are stored', default='./')
	parser.add_argument('-c', '--StrChems', help='Number of chemistries', default='4', type=int)
	parser.add_argument('-s', '--SubStr', help='Substring of the filenames to analyze', default='acsAttractorsAnalysisNOINFLUX_COSENO')
	parser.add_argument('-x', '--computeAngle', help='Select if the cos must be converted in angle', default=0, type=int)
	args = parser.parse_args()
	
	# Create absolute paths
	strPath = os.path.abspath(args.strPath)
	
	# Go into the path 
	os.chdir(strPath)	
	
	# Retrieve the list of file to analyze
	strSubStrKey = '*' + args.SubStr + '*'
	filesToAnal = sorted(glob.glob(os.path.join(strPath,strSubStrKey)))
	lenFilesToAnal = len(filesToAnal)
	numOfTraj = 0
	for n, fileToAnal in enumerate(filesToAnal):
		#�Load each element of the file in array
		x = np.array(map(list, np.loadtxt(fileToAnal, str)), float)
		xsize = x.shape
		if n == 0:
			run4Chem = xsize[0]/args.StrChems
			numOfTraj = ((run4Chem * (run4Chem-1) / 2.00) + run4Chem) * args.StrChems
			y = np.zeros((lenFilesToAnal,numOfTraj))
		# Store values in the overall matrix
		pos = 0
		chem = 1
		tmpHead = ''
		for row in range(0,xsize[0]):
			for col in range(row,run4Chem*chem):
				if args.computeAngle == 1:
					y[n,pos] = np.arccos(x[row,col]) * 360.00 / 6.28
					#if y[n,pos] > 0:
						#print fileToAnal
						#print row, " ", col, " ", x[row,col], " ", np.arccos(float(x[row,col])), " ", np.arccos(x[row,col]) * 360.00 / 6.28
						#raw_input("test")
				else:
					y[n,pos] = x[row,col]
				if (n == 0):
					tmpHead += str(chem) + '.' + str(row) + '-' + str(chem) + '.' + str(col) + '\t'
				pos += 1
			if (row == run4Chem*chem-1):
				chem += 1
				
		
	filename = "_arranged_" + args.SubStr + ".csv"
	#np.savetxt(filename, y, delimiter='\t', fmt='%.5f', header=tmpHead) (To use with numpy > 1.7.0)
	np.savetxt(filename, y, delimiter='\t', fmt='%.5f')
	print "File saved, see you next time..."