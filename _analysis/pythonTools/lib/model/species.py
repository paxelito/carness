#!/usr/bin/python
# -*- coding: latin-1 -*-

import sys, os # Standard library
import itertools as it
import numpy as np # Scientific library
from numpy import cumsum
import random as ran

_AVOGADRO_ = 6.022141e23
_REDUCEDCONCENTRATION_ = 10.0

def createCompleteSpeciesPopulation(M, alphabet):
	species = []
	for i in range(M): species.extend(map(''.join,it.product(alphabet, repeat=i+1)))
	return species

def getTotNumberOfSpeciesFromCompletePop(M):
	N = 2 ** (M + 1) - 2
	return N

def createFileSpecies(tmpFolder, args, pars, tmpScale=1, specieslist = None, tmpCatInRAF=None, tmpRafCatContribute2C=1):
	# Create species file 
	if specieslist and len(specieslist) > 1: tempSpeciesList = specieslist
	else: tempSpeciesList = createCompleteSpeciesPopulation(args.maxDim, pars[14])
	
	fname_initSpecies = os.path.join(tmpFolder, '_acsspecies.csv')
	fid_initSpecies = open(fname_initSpecies, 'w')
	# for each species
	tempFood = []
	tmpAlpha = '\t0\n'
	for idspecies, singleSpecies in enumerate(tempSpeciesList):
		lastc = "0"
		initConc = args.initAmount / (_AVOGADRO_ * pars[15])
		
		# FOOD SPECIES
		if len(singleSpecies) <= args.lastFood: 
			if args.sysType == 2: lastc = "1"
			tempFood.append(idspecies)
			initConc = args.initBufferAmount / (_AVOGADRO_ * pars[15])
		
		# Species of initial set	
		if (len(singleSpecies) > args.lastFood) & (len(singleSpecies) <= args.initSet): 
			#scalingFactor = int(args.initAmount/(10**tmpScale))
			scalingFactor = int(args.initAmount)
			if scalingFactor < 1: scalingFactor = 1
			if args.fixedConcentration == 0: initConc = np.random.poisson(scalingFactor) / (_AVOGADRO_ * pars[15])
			
		# Species with reduced concentrations	
		if len(singleSpecies) >= args.redConc: initConc = initConc / _REDUCEDCONCENTRATION_;		
	
		# Species longer than the initial set	
		if len(singleSpecies) > args.initSet: initConc = 0
		
		# Holes in initial concentrations
		if (ran.random() < args.holesperc) & (len(singleSpecies) > args.lastFood): initConc = 0
		
		# Contribute to container growth
		if (tmpCatInRAF) and (len(tmpCatInRAF)) > 0: 
			if ran.random() <= tmpRafCatContribute2C:
				if idspecies in tmpCatInRAF: 
					tmpAlpha = '\t' + str(args.alpha) + '\n'
				else: 
					tmpAlpha = '\t0\n'
			else:
				tmpAlpha = '\t0\n'		
		
		str2w = str(idspecies) + "\t" + singleSpecies + "\t"  + str(initConc) + "\t1\t1\t0\t0\t1\t0\t0\t0\t0\t0\t0\t" + lastc + tmpAlpha
		fid_initSpecies.write(str2w)   
	fid_initSpecies.close()
	return tempSpeciesList, tempFood

def weightedChoice(weights, objects):
	"""Return a random item from objects, with the weighting defined by weights 
    (which must sum to 1)."""
	cs = cumsum(weights) #An array of the weights, cumulatively summed.
	idx = sum(cs < ran.random()) #Find the index of the first weight over a random value.
	return objects[idx]