#!/usr/bin/python
# -*- coding: latin-1 -*-

import sys, os # Standard library
import itertools as it
import numpy as np # Scientific library
from numpy import cumsum
import random as ran

_AVOGADRO_ = 6.022141e23

def createCompleteSpeciesPopulation(M, alphabet):
	species = []
	for i in range(M): species.extend(map(''.join,it.product(alphabet, repeat=i+1)))
	return species

def getTotNumberOfSpeciesFromCompletePop(M):
	N = 2 ** (M + 1) - 2
	return N

def createFileSpecies(tmpFolder, args, pars, tmpScale=1, specieslist = None):
	# Create species file 
	if specieslist and len(specieslist) > 1: tempSpeciesList = specieslist
	else: tempSpeciesList = createCompleteSpeciesPopulation(args.maxDim, pars[14])
	
	fname_initSpecies = os.path.join(tmpFolder, '_acsspecies.csv')
	fid_initSpecies = open(fname_initSpecies, 'w')
	# for each species
	tempFood = []
	for id, singleSpecies in enumerate(tempSpeciesList):
		lastc = "0"
		initConc = args.initAmount / (_AVOGADRO_ * pars[15])
		if len(singleSpecies) <= args.lastFood: 
			lastc = "1"
			tempFood.append(id)
		if (len(singleSpecies) > args.lastFood) & (len(singleSpecies) <= args.initSet): 
			scalingFactor = int(args.initAmount/(10**tmpScale))
			if scalingFactor < 1: scalingFactor = 1
			initConc = np.random.poisson(scalingFactor) / (_AVOGADRO_ * pars[15])
		if len(singleSpecies) > args.initSet: initConc = 0
		str2w = str(id) + "\t" + singleSpecies + "\t"  + str(initConc) + "\t1\t1\t0\t0\t1\t0\t0\t0\t0\t0\t0\t" + lastc + "\n"
		fid_initSpecies.write(str2w)   
	fid_initSpecies.close()
	return tempSpeciesList, tempFood

def weightedChoice(weights, objects):
    """Return a random item from objects, with the weighting defined by weights 
    (which must sum to 1)."""
    cs = cumsum(weights) #An array of the weights, cumulatively summed.
    idx = sum(cs < ran.random()) #Find the index of the first weight over a random value.
    return objects[idx]