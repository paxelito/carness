import sys, os # Standard librar
import glob


def zeroBeforeStrNum(tmpl, tmpL):
	strZero = ''
	nZeros = len(str(tmpL)) - len(str(tmpl))
	if nZeros > 0:
		for i in range(0,nZeros): strZero = strZero + '0'
	return strZero
#eof

try:
	StrFrom = sys.argv[1] # Here the path of the simulation output files
	StrTo = sys.argv[2] # Here the path of the new simulation files 
except:
	print "Usage:",sys.argv[0], "infile outfile"; sys.exit(1)
	
os.chdir(StrTo)

foldersSIMS = 10; # number of simulations 
foldersREP = 10;

for i in range(1,foldersSIMS+1):

	for j in range(1,foldersREP+1):
		
		zerosSIMS = zeroBeforeStrNum(i,foldersSIMS)
		zerosREPS = zeroBeforeStrNum(j,foldersREP)
		
		folderName = "s_inv_1e-2_" + zerosSIMS + str(i) + "_" + zerosREPS + str(j)
		folderNew  = "s_inv_1e-1_" + zerosSIMS + str(i) + "_" + zerosREPS + str(j)
		if not os.path.isdir(folderName):
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
				
		
		# Create destination simulation folder
		crtSimFolder = os.path.join(StrTo,folderName)
		
		# GOES TO THE FROM FOLDER TO GET FILES
		os.chdir(os.path.join(StrFrom,folderName))
		
		# MOVE THE STATIC FILES TO THE NEW FOLDER
		fileDest = os.path.join(StrTo,folderNew,"_acsinflux.csv")
		os.system ("cp %s %s" % ("_acsinflux.csv",fileDest));
		fileDest = os.path.join(StrTo,folderNew,"_acsnrgbooleanfunctions.csv")
		os.system ("cp %s %s" % ("_acsnrgbooleanfunctions.csv",fileDest));
		
		# Goes into the ORIGIN res folder to get the final chemist files 
		os.chdir("res")
		fileDest = os.path.join(StrTo,folderNew,"acsm2s.conf")
		os.system ("cp %s %s" % ("acsm2s.conf",fileDest));
		speciesFiles = sorted(glob.glob("species_1_*"))
		fileDest = os.path.join(StrTo,folderNew,"_acsspecies.csv")
		os.system ("cp %s %s" % (speciesFiles[-1],fileDest));
		speciesFiles = sorted(glob.glob("reactions_1_*"))
		fileDest = os.path.join(StrTo,folderNew,"_acsreactions.csv")
		os.system ("cp %s %s" % (speciesFiles[-1],fileDest));
		speciesFiles = sorted(glob.glob("catalysis_1_*"))
		fileDest = os.path.join(StrTo,folderNew,"_acscatalysis.csv")
		os.system ("cp %s %s" % (speciesFiles[-1],fileDest));
		
		# Goes to the destination simulation folder 
		os.chdir(os.path.join(StrTo,folderNew))
		
		# THIS IS THE SCRIPT'S PART TO MODIFY TO SET THE NEW SIMULATIONS
		
		# SPECIES FILE
		mod = open("_acsspecies.csv").readlines()	
		id = 0
		for line in mod:
			linesplitted = line.split("\t")
			# Set concentration
			if id > 29:
				linesplitted[2] = '0'
			else:
				linesplitted[2] = '0.00110924'
			# set k_cpx
			#if linesplitted[6] > 0:
			#	linesplitted[5] = '1'
			linesplitted[8] = '0' # reborn
			linesplitted[9] = '0' # age
			mod[id] = "\t".join(linesplitted)
			id += 1	 
		try:
			file = open("_acsspecies.csv", "w")
			file.writelines(mod)
			file.close()
		except IOError:
			print "Couldn't save species file"
			
		# REACTIONS FILE
		mod = open("_acsreactions.csv").readlines()	
		id = 0
		for line in mod:
			linesplitted = line.split("\t")
			linesplitted[5] = '0' # counter
			mod[id] = "\t".join(linesplitted)
			id += 1	 
		try:
			file = open("_acsreactions.csv", "w")
			file.writelines(mod)
			file.close()
		except IOError:
			print "Couldn't save reactions file"	
			
		# CATALYSIS FILE
		mod = open("_acscatalysis.csv").readlines()	
		id = 0
		for line in mod:
			linesplitted = line.split("\t")
			linesplitted[3] = '0' # counter
			if linesplitted[4] == '5':
				linesplitted[4] = '50' # K_cond
			if linesplitted[5] == '2.5':
				linesplitted[5] = '25' # K_cond
			if linesplitted[6] == '5\n':
				linesplitted[6] = '50\n' # K_cond
			#linesplitted[5] = '25' # K_Cleavage
			#linesplitted[6] = '50\n' # Kcpx
			mod[id] = "\t".join(linesplitted)
			id += 1	 
		try:
			file = open("_acscatalysis.csv", "w")
			file.writelines(mod)
			file.close()
		except IOError:
			print "Couldn't save catalysis file"
			
		# ACSCONF FILE
		mod = open("acsm2s.conf").readlines()	
		id = 0
		for line in mod:
			if line[0] <> "#":
				linesplitted = line.split("=")
				if linesplitted[0] == 'randomSeed':
					linesplitted[1] = '0' # counter
				mod[id] = "=".join(linesplitted)
			id += 1	 
			
		try:
			file = open("acsm2s.conf", "w")
			file.writelines(mod)
			file.close()
		except IOError:
			print "Couldn't save configuration file"	
			
		
		os.chdir("../")
	
# Once that all files have been copied all configuration files are modified
# Modify configuration file
os.system("find . -name 'acsm2s.conf' -type f -exec perl -pi -e 's/revRctRatio=10/revRctRatio=1/g' {} \;");
#os.system("find . -name 'acsm2s.conf' -type f -exec perl -pi -e 's/nSIM=10/nSIM=1/g' {} \;");
#os.system("find . -name '_acscatalysis.csv' -type f -exec perl -pi -e 's/0.25/2.5/g' {} \;");
#os.system("find . -name '_acscatalysis.csv' -type f -exec perl -pi -e 's/0.5/5/g' {} \;");