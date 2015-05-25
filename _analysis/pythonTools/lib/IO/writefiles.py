#!/usr/bin/python
# -*- coding: latin-1 -*-

import sys, os # Standard librar
import glob
import numpy as np # Scientific library
import random as ran
import cPickle as pickle
from numpy import * 
from argparse import ArgumentParser
try:
    from pylab import *
except:
    pass
   
def saveRandomSeed(tmpPath):
	'''Function to save the random seed'''
	
	with open(os.path.join(tmpPath,"rndstate.dat"), 'wb') as f:
		pickle.dump(ran.getstate(), f)

def write_init_raf_list(fid, rafinfo, folder):
	fid.write(folder + "\nCLOSURE -> ")
	map(lambda x: fid.write((str(int(x)) + ' ')), rafinfo[0])
	fid.write("\nRAF -> ")
	map(lambda x: fid.write((str(int(x)) + ' ')), rafinfo[2])
	fid.write("\nCATALYSTS -> ")
	map(lambda x: fid.write((str(int(x)) + ' ')), rafinfo[3])
	fid.write("\n\n")
	
def write_init_raf_all(fid, rafinfo, folder, rcts, cats):
	fid.write(folder + "\n")
	for i,r in enumerate(rafinfo[2]):
		if rcts[r,1] == 1: 
			str2w = str(int(rcts[r,2])) + " -> " + str(int(rcts[r,3])) + " + " + str(int(rcts[r,4])) + ", " + str(int(rafinfo[3][i])) + "\n"
			fid.write(str2w)
		else:
			str2w = str(int(rcts[r,3])) + " + " + str(int(rcts[r,4])) + " -> " + str(int(rcts[r,2])) + ", " + str(int(rafinfo[3][i])) + "\n"
			fid.write(str2w)
	fid.write("\n\n")

def write_acsCatalysis_file(path_file, catStr):
	print "\t|- save Catalysis file"
	fileName = os.path.join(path_file, '_acscatalysis.csv')
	np.savetxt(fileName, catStr, delimiter='\t', fmt='%d\t%d\t%d\t%d\t%f\t%f\t%f\t%d')

def write_acsReactions_file(path_file, rctStr, spontRatio=None, kspontass=None, kspontdiss=None):
	print "\t|- save Reaction file"
	if spontRatio and spontRatio > 0:
		for rct in rctStr:
			if ran.random() < spontRatio:
				if rct[1] == 1:rct[7] = kspontdiss
				else: rct[7] = kspontass
		
	fileName = os.path.join(path_file, '_acsreactions.csv')
	np.savetxt(fileName, rctStr, delimiter='\t', fmt='%d\t%d\t%d\t%d\t%d\t%d\t%d\t%.10f')

def write_and_createInfluxFile(path_file, args, tmpFood):
	print "\t|- Save influx file"
	fname_influx = os.path.join(path_file, '_acsinflux.csv')
	fid_influx = open(fname_influx, 'w')
	prob = 1. / len(tmpFood)
	for id, f in enumerate(tmpFood):

		if args.systemArchitecture != 3:
			str2w = str(f) + "\t" + str(prob) + "\n"
		else:
			str2w = str(f) + "\t" + str(args.extconc) + "\t" + str(args.k_membrane) + "\n"
			
		fid_influx.write(str2w)   
	fid_influx.close()

def write_and_create_std_nrgFile(path_file):
	print "\t|- Save energy file"
	fname_nrg = os.path.join(path_file, '_acsnrgbooleanfunctions.csv')
	fid_nrg = open(fname_nrg, 'w')
	str2w = "239\t1\n"
	fid_nrg.write(str2w)   
	fid_nrg.close()
	
def writeAllFilesAndCreateResFolder(pathFile, resFolderName, cats, rcts, food, spontRatio=None, kspontass=None, kspontdiss=None, conf=False):
	
	print "|- Save Structures"
	
	newdirAllResults = os.path.join(pathFile, resFolderName)
	if not os.path.isdir(newdirAllResults):
		try: os.mkdir(newdirAllResults)
		except: print "Impossible to create statistic directory", newdirAllResults; sys.exit(1)
		
	if conf == True: write_acsms_file(pathFile, conf)
	write_and_createInfluxFile(pathFile, food)
	write_and_create_std_nrgFile(pathFile)
	write_acsCatalysis_file(pathFile, cats)
	write_acsReactions_file(pathFile, rcts, spontRatio, kspontass, kspontdiss)
	
def write_acsms_file(path_file, params):
	print "\t|- save conf file"
	fname_conf = os.path.join(path_file, 'acsm2s.conf')
	fid_conf = open(fname_conf, 'w')
	
	fid_conf.write("# =================\n# ACSM2S PARAMETERS\n# =================\n\n# -----------------\n# SYSTEM PARAMETERS\n# -----------------\n\n")
	str2w = "systemArchitecture="+str(params['systemArchitecture'])+"\n"; fid_conf.write(str2w);
	str2w = "nGEN="+str(params['nGEN'])+"\n"; fid_conf.write(str2w);
	str2w = "nSIM="+str(params['nSIM'])+"\n"; fid_conf.write(str2w);
	str2w = "nSeconds="+str(params['nSeconds'])+"\n"; fid_conf.write(str2w);
	str2w = "nReactions="+str(params['nReactions'])+"\n"; fid_conf.write(str2w);
	str2w = "nHours="+str(params['nHours'])+"\n"; fid_conf.write(str2w);
	str2w = "nAttempts="+str(params['nAttempts'])+"\n"; fid_conf.write(str2w);
	str2w = "randomSeed="+str(params['randomSeed'])+"\n"; fid_conf.write(str2w);
	str2w = "debugLevel="+str(params['debugLevel'])+"\n"; fid_conf.write(str2w);
	str2w = "timeStructuresSavingInterval="+str(params['timeStructuresSavingInterval'])+"\n"; fid_conf.write(str2w);
	str2w = "fileTimesSaveInterval="+str(params['fileTimesSaveInterval'])+"\n"; fid_conf.write(str2w);
	str2w = "fileAmountSaveInterval="+str(params['fileAmountSaveInterval'])+"\n"; fid_conf.write(str2w);
	str2w = "newSpeciesProbMinThreshold="+str(params['newSpeciesProbMinThreshold'])+"\n"; fid_conf.write(str2w);
	str2w = "lastFiringDiskSpeciesID="+str(params['lastFiringDiskSpeciesID'])+"\n"; fid_conf.write(str2w);
	str2w = "overallConcentration="+str(params['overallConcentration'])+"\n"; fid_conf.write(str2w);
	str2w = "ECConcentration="+str(params['ECConcentration'])+"\n"; fid_conf.write(str2w);
	str2w = "alphabet="+str(params['alphabet'])+"\n"; fid_conf.write(str2w);
	str2w = "volume="+str(params['volume'])+"\n"; fid_conf.write(str2w);
	str2w = "volumeGrowth="+str(params['volumeGrowth'])+"\n"; fid_conf.write(str2w);
	str2w = "stochDivision="+str(params['stochDivision'])+"\n"; fid_conf.write(str2w);
	str2w = "theta="+str(params['theta'])+"\n"; fid_conf.write(str2w);
	str2w = "energy="+str(params['energy'])+"\n"; fid_conf.write(str2w);
	str2w = "ratioSpeciesEnergizable="+str(params['ratioSpeciesEnergizable'])+"\n"; fid_conf.write(str2w);
	str2w = "nonCatalyticMaxLength="+str(params['nonCatalyticMaxLength'])+"\n"; fid_conf.write(str2w);
	str2w = "reactionProbability="+str(params['reactionProbability'])+"\n"; fid_conf.write(str2w);
	str2w = "cleavageProbability="+str(params['cleavageProbability'])+"\n"; fid_conf.write(str2w);
	str2w = "main_rev_rct_allowed="+str(params['main_rev_rct_allowed'])+"\n"; fid_conf.write(str2w);
	str2w = "reverseReactions="+str(params['reverseReactions'])+"\n"; fid_conf.write(str2w);
	str2w = "revRctRatio="+str(params['revRctRatio'])+"\n"; fid_conf.write(str2w);
	str2w = "spontRct="+str(params['spontRct'])+"\n"; fid_conf.write(str2w);
	str2w = "K_ass="+str(params['K_ass'])+"\n"; fid_conf.write(str2w);
	str2w = "K_diss="+str(params['K_diss'])+"\n"; fid_conf.write(str2w);
	str2w = "K_cpx="+str(params['K_cpx'])+"\n"; fid_conf.write(str2w);
	str2w = "K_cpxDiss="+str(params['K_cpxDiss'])+"\n"; fid_conf.write(str2w);
	str2w = "K_nrg="+str(params['K_nrg'])+"\n"; fid_conf.write(str2w);
	str2w = "K_nrg_decay="+str(params['K_nrg_decay'])+"\n"; fid_conf.write(str2w);
	str2w = "K_spont_ass="+str(params['K_spont_ass'])+"\n"; fid_conf.write(str2w);
	str2w = "K_spont_diss="+str(params['K_spont_diss'])+"\n"; fid_conf.write(str2w);
	str2w = "moleculeDecay_KineticConstant="+str(params['moleculeDecay_KineticConstant'])+"\n"; fid_conf.write(str2w);
	str2w = "diffusion_contribute="+str(params['diffusion_contribute'])+"\n"; fid_conf.write(str2w);
	str2w = "solubility_threshold="+str(params['solubility_threshold'])+"\n"; fid_conf.write(str2w);
	str2w = "influx_rate="+str(params['influx_rate'])+"\n"; fid_conf.write(str2w);
	str2w = "maxLOut="+str(params['maxLOut'])+"\n"; fid_conf.write(str2w);
	str2w = "saveReactionParameters="+str(params['saveReactionParameters'])+"\n"; fid_conf.write(str2w);
	str2w = "randomInitSpeciesConcentration="+str(params['randomInitSpeciesConcentration'])+"\n"; fid_conf.write(str2w);
 
	fid_conf.close()
