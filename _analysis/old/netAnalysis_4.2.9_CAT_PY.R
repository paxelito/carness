# LOAD LIBRARIES
# 	From 4.1
#		- -1 values in summary matrices have been substituted by NaN
#		- BOX plot summarizing all the simulation has been added
#		- Branch analysis hava been deleted
#		- adjCatMatrix_LIFETIME variable is not long save on file
#		- General Y in function of X graph has been introduced
#		- readline(prompt = "Pause. Press <Enter> to continue...")
#		- Average path length, clustering coefficient and [degree distribution] have to be added

library(scatterplot3d);
library(igraph);
#source("C:/Users/Tommy/Dropbox/stat_R_ACS_Develop/common_2.2lite.R");
source("/Users/laleli/Dropbox/ACS_SVN/carness/carness_simulator/_analysis/common_2.2lite.R");
#source("/Users/alessandrofilisetti/Dropbox/ACS_SVN/carness/carness_simulator/_analysis/common_2.2lite.R");

allNETgss <- function(tmpParInflux=0,tmpFolderResSubName="sim", tmpGraphFolderSuffix="", tmpTotGens=1, tmpTotSims=1, maxRctN=200000000)
{
	# Create folder where Graphs will be stored
	dir.create(paste("./__02_nets", tmpGraphFolderSuffix, sep=""));
	dir.create(paste("./__03_scaleFree", tmpGraphFolderSuffix, sep=""));
	dir.create(paste("./__04_netstat", tmpGraphFolderSuffix, sep=""));
	dir.create(paste("./__05_all", tmpGraphFolderSuffix, sep=""));
	# Compute total number of simulatons
	simFolds = dir(pattern = tmpFolderResSubName)
	#print(simFolds)
	for(tmpf in 1 : length(simFolds))
	{
		tmpSimPath = paste(getwd(),"/",simFolds[tmpf],sep="")
		print(paste("  |- Folder: ", tmpSimPath, " ---------------"));
		gssNET(1, tmpTotGens, 1, tmpTotSims, maxRctN, tmpGraphFolderSuffix, tmpSimPath, length(simFolds), tmpFolderResSubName, tmpParInflux);
	}
	overallNETsummary(tmpTotGens, length(simFolds), tmpGraphFolderSuffix, "_netAnalysis.csv", "CAT", tmpSimPath);
	rm(list=ls());
}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# -<===== FUNCTION TO ANALYZE A SINGLE SIMULATION

gssNET <- function(tmpGen, tmpTotGens, tmpSim, tmpTotSims, tmpMaxRctN, tmp___GraphFolderSuffix, tmpSimPath, tmpNsimFolds,tmpFolderResSubName, tmpParInflux)
{
	
	maxNumberOfSimulation = tmpTotSims^tmpGen;
		
	# ACCORDING TO THE maxNumberOfSimulation ZEROS IN STRING BEFORE NAME IS CREATED
	strZerosGen <- zeroBeforeStringNumber(tmpTotGens, tmpGen);
	strZerosSim <- zeroBeforeStringNumber(maxNumberOfSimulation, tmpSim);
		
	# CHECK WHETHER THIS SIMULATION HAS BEEN ALREADY ANALYZED (MAYBE BEFORE AN ERROR)
	setwd(paste("./__04_netstat", tmp___GraphFolderSuffix, sep=""));
		alreadyAnalyzed <- dir(pattern = paste("26__",tmpNsimFolds,sep=""));
		#alreadyAnalyzed <- NULL;
	setwd("./..");
	#print(alreadyAnalyzed);
	#print(length(alreadyAnalyzed))
	
	if(length(alreadyAnalyzed) == 0)
	{	
		# ------------------------------------------------------------------------------
		# CREATE A LIST OF ALL FILES ACCORDING TO THE SIMULTION AND THE TYPE OF ELEMENTS
		# ------------------------------------------------------------------------------
		
		# Structures Files
		resdir = paste(tmpSimPath, "/res", sep="")
		actDir = getwd()
		#print(resdir)
		setwd(resdir)
		speciesFileList	<- dir(pattern = paste("species_", strZerosGen, tmpGen, "_", strZerosSim, tmpSim, sep=""));		
		# Reactions (condensation and cleavage) parameters files
		print(paste("reactions_parameters_", strZerosGen, tmpGen, "_",  strZerosSim, tmpSim, sep=""))
		rctParFileList		<- dir(pattern = paste("reactions_parameters_", strZerosGen, tmpGen, "_",  strZerosSim, tmpSim, sep=""));			
		livSpeciesFileList	<- dir(pattern = paste("livingSpecies_", strZerosGen, tmpGen, "_",  strZerosSim, tmpSim, sep=""));
		livAmountFileList	<- dir(pattern = paste("livingAmount_", strZerosGen, tmpGen, "_",  strZerosSim, tmpSim, sep=""));
		livConcFileList		<- dir(pattern = paste("livingConcentration_", strZerosGen, tmpGen, "_",  strZerosSim, tmpSim, sep=""));
		
		# Create the correct filesname vector
		speciesFileList	<- correctinitialFileNameinTheList(speciesFileList, tmpGen, tmpTotGens, tmpSim, tmpTotSims, tmpMaxRctN, 1);
		
		# create iGraph file list 
		setwd(paste("../../__0_iGraph_CAT", tmp___GraphFolderSuffix, sep=""))
			
			print("           |- Load graph...");
			subStrGraph = substr(tmpSimPath,nchar(tmpSimPath)-1,nchar(tmpSimPath))
			iGraphNetFile <- dir(pattern = paste("_iGraph_CAT", subStrGraph, "_", sep=""));
			
		setwd("../")
		
		# Load the initial species structure file
		initSpecies <- data.frame(read.table(paste(tmpSimPath, "/res/", speciesFileList[1], sep=""), sep="\t"));
		dimnames(initSpecies)[2] <- list(c("IDspecies","seq","amount","diffusion","prec","compProb","cutpnt","eval", "age", "reborns","cat","sub","kpho","loadedC","fixedC"));
		#dimnames(initSpecies)[2] <- list(c("IDspecies","seq","amount","diffusion","prec","compProb","cutpnt","eval", "age", "reborns","cat","sub","kpho","loadedC"));
		# Load the initial species structure file
		lastSpecies <- data.frame(read.table(paste(tmpSimPath, "/res/", speciesFileList[length(speciesFileList)], sep=""), sep="\t"));
				
		# Load reaction parameters file
		#print(rctParFileList)
		print(paste("          |- Load Reactions data file", rctParFileList[1], "..."));
		rctParameters <- data.frame(read.table(paste(tmpSimPath, "/res/", rctParFileList[1], sep=""), sep="\t"));
		print("          |- done!");
		
		# Load species influx file
		print("          |- Influx species loading process...");
		if(tmpParInflux == 0)
		{
			influxFile <- data.frame(read.table(paste(tmpSimPath, "/res/", "_acsinflux.csv", sep=""), sep="\t"))
			influxIds <- influxFile[,1];
		}else{
			influxIds <- c(0:tmpParInflux);
		}
		#print(influxIds)
		print("          |- done!");
		
		#print(iGraphNetFile)

		# IF THERE ARE CONDENSATION OR CLEAVAGE REACTIONS
		print(length(iGraphNetFile))
		if(length(iGraphNetFile) > 0) 
		{
			# Set counter 
			thisRct_ID = 1;
			thisRct_value = 1;
			# Initialize final stat structure
			finalNetAnalysis <- matrix(0, length(iGraphNetFile) + 1, 22);
			finalNetAnalysis[1,] <- runif(22)*0;
			rctNumber <- 2;
			
			# Cycle production counter matrix initialization
			fromACS <- 0;
			fromACSprod <- 0;
			fromChain <- 0;
			fromInflux <- 0;
			
			for(iGraphFile in 1 : length(iGraphNetFile))
			{
				fromACS <- 0;
				fromACSprod <- 0;
				fromChain <- 0;
			    fromInflux <- 0;
				
				IDspeciesPresentInScc <- NULL;
				setwd(paste("./__0_iGraph_CAT", tmp___GraphFolderSuffix, sep=""))
					print(paste("          |- Read Data from ", iGraphNetFile[iGraphFile]));
						adjCatMatrix_LIFETIME <- data.frame(read.table(iGraphNetFile[iGraphFile], sep="\t"));
					print("          |- Done")
				setwd("../")
				
				# Extract reaction number and TIME from file name
				# (e.g._iGraph_CAT_1_1_000000144_4.00932.csv returns 144 and 4.00932)
				tmpRct <- as.integer(unlist(strsplit(iGraphNetFile[iGraphFile],"_"))[5]);
				tmpStrTime <- unlist(strsplit(iGraphNetFile[iGraphFile],"_"))[6];
				tmpTime <- as.double(substr(tmpStrTime, 1, nchar(tmpStrTime)-4)); 
				if(!is.finite(tmpTime))
				{
					print(iGraphNetFile[iGraphFile])
					print(unlist(strsplit(iGraphNetFile[iGraphFile],"_")))
					print(unlist(strsplit(iGraphNetFile[iGraphFile],"_"))[5])
					print(tmpRct)
					print(tmpTime)
					readline(prompt = "Pause. Press <Enter> to continue...")
				}
				
				print(paste("          |- Reaction:", tmpRct, "- Time:", tmpTime, "- Load living system parameters"));
				
				# Loading row of living parameter according to the reaction number	
				actDir = getwd()
				setwd(resdir)					
					livingSpeciesRow <- scan(livSpeciesFileList[1], skip=which(rctParameters[,1]==tmpRct)-1, nlines=1, quiet=TRUE);
					livingAmount  <- scan(livAmountFileList[1], skip=which(rctParameters[,1]==tmpRct)-1, nlines=1, quiet=TRUE);
					livingConc  <- scan(livConcFileList[1], skip=which(rctParameters[,1]==tmpRct)-1, nlines=1, quiet=TRUE);
					livingSpecies <- livingSpeciesRow[3:length(livingSpeciesRow)];
					thisRct_value <- livingSpeciesRow[1];
					thisRct_ID <- thisRct_ID + 1;
				
					
				print("          |- done!!!")
														
				# ACTUAL REACTIONS (instant lifetime) --> ADJ MATRICES INITIALIZATION
																	
				if(nrow(adjCatMatrix_LIFETIME) > 0)
				{
					# Select all catalysts
					listOfAllCat <- unique(adjCatMatrix_LIFETIME[,1]);
					# Select all products
					listOfAllPro <- unique(adjCatMatrix_LIFETIME[,2]);
					# Merge and Sort catalysts and products
					speciesInvolved_LT <- sort(unique(c(listOfAllCat, listOfAllPro)));
					mtxDimension <- length(speciesInvolved_LT); 
					# Initialise adjacence matrix
					# The first contains the interaction between catalysts and products
					# The second one contains the number of times that a reaction occurred 
					cat_adjMtx_LIFETIME <- matrix(0, mtxDimension, mtxDimension);
					rctCatMtx <- matrix(0, mtxDimension, mtxDimension);
				}
						
				# INSTANT REACTIONS (instant lifetime) --> Create adjacence matrix
					# CATALYST -> PRODUCT
					
				if(nrow(adjCatMatrix_LIFETIME) > 0)
				{							
					for(sparseMtRow in 1 : nrow(adjCatMatrix_LIFETIME))
					{
						cat <- which(speciesInvolved_LT == adjCatMatrix_LIFETIME[sparseMtRow,1]);
						pro <- which(speciesInvolved_LT == adjCatMatrix_LIFETIME[sparseMtRow,2]);
						cat_adjMtx_LIFETIME[pro, cat] <- 1;
						rctCatMtx[pro, cat] <-  adjCatMatrix_LIFETIME[sparseMtRow,6];
					}
				}else{
					cat_adjMtx_LIFETIME <- 0;
					rctCatMtx <- 0;
				}	
				
				print("        |- ACS Recognition Process...")				
						
				# -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+					
				# ACS RECOGNITION PROCESS - - - - - - - - - - - - - - - - - - - - - - - - - - + 
				# -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+--+-+-+-+
						
				# ----- CATALYST -> PRODUCT --------------------------------------------------|
					# ACTUAL REACTIONS (INSTANT LIFETIME)
				if(ncol(cat_adjMtx_LIFETIME) > 0)
				{
					cat_eig_LT <- eigen(cat_adjMtx_LIFETIME);
					ELRPcat_LIFETIME <- max(Re(cat_eig_LT$values));
					R_cat_LIFETIME <- sum(cat_adjMtx_LIFETIME) / nrow(cat_adjMtx_LIFETIME);
				}else{
					ELRPcat_LIFETIME <- 0;
					R_cat_LIFETIME <- 0;					
				}
													
				# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
			 	# IN DEGREE and OUT DEGREE - - - - - - - - - - - - - - - - - - - - - - - - - -  
				# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
				 		
				# ACTUAL REACTIONS (INSTANT LIFETIME)
				iGraphAdjCatMatrix_LIFETIME <- graph.data.frame(adjCatMatrix_LIFETIME[,1:2], directed=TRUE);
				 								 				 		 							 		
				# INDEGREE ------
				# CATALYST -> PRODUCT
				 	# ACTUAL REACTIONS (instant lifetime)
				 	catInDegree_LIFETIME <- degree(iGraphAdjCatMatrix_LIFETIME, mode="in");
				 	catINmeandegree_LIFETIME <- mean(catInDegree_LIFETIME);				 			
				 			 		
				 			
				# STRONG CONNECTED COMPONENT ANALYSIS
					# Strong connected components discovery -------------------------|
					SCC_cat_LT 	<- clusters(iGraphAdjCatMatrix_LIFETIME, "strong");
		 			# Real numerosity of strong connected components ----------------|
			 		RSCC_cat_LT	<- SCC_cat_LT$csize[SCC_cat_LT$csize > 1];
		 			# Number of loops
			 		loops_CAT_LT 	<- sum(is.loop(iGraphAdjCatMatrix_LIFETIME)*1);
		 			# Number of strong connected components -------------------------|
			 		N_SCC_cat_LT 	<- length(RSCC_cat_LT) + loops_CAT_LT;
		 			# Number of species belonging to the SCCs -------------------|
			 		N_species_SCC_cat_LT 	<- sum(RSCC_cat_LT) + loops_CAT_LT;
		 			# Percentage of species belonging to the SCCs over number of catalyst -------------------|
			 		Perc_N_SCC_cat_LT 	<- N_species_SCC_cat_LT / sum(SCC_cat_LT$csize) * 100;
		 			# Percentage of species belonging to the SCCs over the total number of species ----------|
			 		Perc_Ntot_SCC_cat_LT 	<- N_species_SCC_cat_LT / length(livingAmount) * 100;
		 			# Max Number of species in SCCs
		 			if(length(RSCC_cat_LT) > 0)
		 			{
		 				max_SCC_cat_LT <- max(RSCC_cat_LT);
		 			}else{
		 				if(loops_CAT_LT > 0){max_SCC_cat_LT <- 1;}else{max_SCC_cat_LT <- 0;}
		 			}
					if(max_SCC_cat_LT == Inf | max_SCC_cat_LT == -Inf)
					{
						print(SCC_cat_LT);
						print(RSCC_cat_LT);
						print(N_SCC_cat_LT);
						print(loops_CAT_LT);
						readline(prompt = "Pause. Press <Enter> to continue…");
					}

		 			# Min NUmber of species in SCCs
			 			if(length(RSCC_cat_LT) > 0)
			 			{
			 				min_SCC_cat_LT <- min(RSCC_cat_LT);
			 			}else{
			 				if(loops_CAT_LT > 0){min_SCC_cat_LT <- 1;}else{min_SCC_cat_LT <- 0;}
			 			}	
		 			# Mean Number species in of SCCs
			 			if(length(RSCC_cat_LT) > 0)
			 			{
			 				mean_SCC_cat_LT <- mean(RSCC_cat_LT);
			 			}else{
			 				if(loops_CAT_LT > 0){mean_SCC_cat_LT <- 1;}else{mean_SCC_cat_LT <- 0;}
			 			}
		 			# median Number species in of SCCs
			 			if(length(RSCC_cat_LT) > 0)
			 			{
			 				median_SCC_cat_LT <- median(RSCC_cat_LT);
			 			}else{
			 				if(loops_CAT_LT > 0){median_SCC_cat_LT <- 1;}else{median_SCC_cat_LT <- 0;}
			 			}					 	    # ------------------------------------------------
			 	    # Compute all vertex analysis present into the SCC
			 	    # ------------------------------------------------
			 	    
			 	    # Compute the overall number of molecules 
			 	    totMol <- sum(livingAmount);
			 	    totConc <- sum(livingConc);
			 	    NOinfluxIds <- setdiff(livingSpecies, influxIds);
			 	    totSpeciesNoInflux <- length(NOinfluxIds);
			 	    totMolNoInflux <- sum(livingAmount[!is.element(livingSpecies, influxIds)]);
			 	    totConcNoInflux <- sum(livingConc[!is.element(livingSpecies, influxIds)]);
			 	     
			 	    					 	    			 	  
			 # -----------------------------------------------    					 	    
				moleculesInCAT_SCC_LT <- 0;
				perc_moleculesInCAT_SCC_LT <- 0;
				moleculesInCAT_SCC_LT_noinflux <- 0;
				perc_moleculesInCAT_SCC_LT_noinflux <- 0;
				# If there are strongly connected components							
			 	    if(N_SCC_cat_LT > 0)
			 	    {
			 	    	css_ids <- which(SCC_cat_LT$csize > 1) - 1; 
			 	    	tot_SCC_speciesID_cat_LT <- NULL;
			 	    	loopSpecies <- get.edgelist(iGraphAdjCatMatrix_LIFETIME)[is.loop(iGraphAdjCatMatrix_LIFETIME),1];
			 	    	nLoop <- NULL;
			 	    	if(length(loopSpecies) > 0)
			 	    	{
				 	    	for(loopSpeciesID in 1 : length(loopSpecies))
				 	    	{
				 	    		nLoop <- c(nLoop, which(V(iGraphAdjCatMatrix_LIFETIME)$name == loopSpecies[loopSpeciesID]) - 1)
				 	    	}
			 	    	}
						for(i in 1 : N_SCC_cat_LT)
						{
							sng_SCC_speciesID_cat_LT <- which(SCC_cat_LT$membership == css_ids[i]) - 1;
							tot_SCC_speciesID_cat_LT <- unique(c(tot_SCC_speciesID_cat_LT, sng_SCC_speciesID_cat_LT, nLoop));
						}	
						tot_SCC_speciesVTX_cat_LT <- V(iGraphAdjCatMatrix_LIFETIME)[tot_SCC_speciesID_cat_LT];
						IDspeciesPresentInScc = as.integer(tot_SCC_speciesVTX_cat_LT$name);
						if(sum(livingAmount) > 0)
						{
							if(length(IDspeciesPresentInScc) > 0)
							{
								for(i in 1 : length(IDspeciesPresentInScc))
								{
									if(length(which(livingSpecies == IDspeciesPresentInScc[i])) > 0)
									{											
										moleculesInCAT_SCC_LT = moleculesInCAT_SCC_LT + livingAmount[which(livingSpecies == IDspeciesPresentInScc[i])];
										if(sum(IDspeciesPresentInScc[i] == NOinfluxIds) == 1)
										{
											moleculesInCAT_SCC_LT_noinflux = moleculesInCAT_SCC_LT_noinflux + livingAmount[which(livingSpecies == IDspeciesPresentInScc[i])];
										}												
									}
								}
							}
							perc_moleculesInCAT_SCC_LT <- moleculesInCAT_SCC_LT / totMol * 100;
							perc_moleculesInCAT_SCC_LT_noinflux <- moleculesInCAT_SCC_LT_noinflux / totMolNoInflux * 100;
						}else{
						    moleculesInCAT_SCC_LT <- 0;
						    perc_moleculesInCAT_SCC_LT <- 0;
						    moleculesInCAT_SCC_LT_noinflux <- 0;
						    perc_moleculesInCAT_SCC_LT_noinflux <- 0;
						}		    	
			 	    } # end  if(N_SCC_cat_LT > 0) if there are ACS
			 	    

				    # Select IDs of the species catalysed whithin and outside an ACS
				    fromACSIDs <- intersect(adjCatMatrix_LIFETIME[,2], IDspeciesPresentInScc);	
				    fromACStotNum <- sum(adjCatMatrix_LIFETIME[,2] %in% IDspeciesPresentInScc);	    
				    notFromAcsIds <- setdiff(adjCatMatrix_LIFETIME[,2], IDspeciesPresentInScc);
				    notFromACStotNum <- sum(!(adjCatMatrix_LIFETIME[,2] %in% IDspeciesPresentInScc));
				    tmpFromChain <- length(notFromAcsIds); # temporary, products of ACS have to be computed
				    
#				    print(adjCatMatrix_LIFETIME[,2])
#				    print(adjCatMatrix_LIFETIME[adjCatMatrix_LIFETIME[,2] != IDspeciesPresentInScc,2])
#				    print(notFromAcsIds)
#				    print(unique(notFromAcsIds))
#				    
#				    readline(prompt = "Pause. Press <Enter> to continue...")
				    
				    tmpFromAcsProd <- 0;    
				    # Check if the NOinfluxIds species are product of an ACS
				    if((length(adjCatMatrix_LIFETIME[,2]) > 0) && (tmpFromChain > 0))
				    {
					    for(j in 1 : tmpFromChain)
					    {
					    	if((length(IDspeciesPresentInScc) > 0))
							{
								# Select reactions catalysing species not present in the ACS
								subCatMtxToMe <- adjCatMatrix_LIFETIME[adjCatMatrix_LIFETIME[,2] == notFromAcsIds[j],];
								if((nrow(subCatMtxToMe) > 0) && (tmpFromChain > 0))
								{
									fromACStoOUTSIDEIDs <- intersect(subCatMtxToMe[,1], fromACSIDs);
									tmpFromAcsProd <- tmpFromAcsProd + length(fromACStoOUTSIDEIDs);
								}
							}
					    }						    
				    }
				    
				    # Check which living species are prodcuted by the influx species
				    tmpFromInflux <- 0;
				    if(length(influxIds) > 0)
				    {
						for(j in 1 : length(influxIds))
						{
							# Select reactions catalysing species not present in the ACS
							subCatMtxfromIN <- adjCatMatrix_LIFETIME[adjCatMatrix_LIFETIME[,1] == influxIds[j],];
							if(nrow(subCatMtxfromIN) > 0)
							{
								fromINFLUXtoPRODUCTSids <- intersect(subCatMtxfromIN[,2], NOinfluxIds);
								tmpFromInflux <- tmpFromInflux + length(fromINFLUXtoPRODUCTSids);
							}							
						}				    						    
				    }
				  

				    fromACS <- fromACStotNum;
				    fromACSprod <- tmpFromAcsProd;
				    fromChain <- notFromACStotNum - tmpFromAcsProd;
			        fromInflux <- tmpFromInflux;	
			 	    				 				 
			 	    reactionSummary <- c(tmpTime, ELRPcat_LIFETIME, R_cat_LIFETIME, 
			 	    catINmeandegree_LIFETIME, 
			 	    N_SCC_cat_LT, N_species_SCC_cat_LT, Perc_N_SCC_cat_LT, Perc_Ntot_SCC_cat_LT, 
			 	    max_SCC_cat_LT, min_SCC_cat_LT, mean_SCC_cat_LT, median_SCC_cat_LT,
			 	    moleculesInCAT_SCC_LT, perc_moleculesInCAT_SCC_LT,
			 	    moleculesInCAT_SCC_LT_noinflux, perc_moleculesInCAT_SCC_LT_noinflux, 
			 	    totMolNoInflux, totSpeciesNoInflux, fromACS, fromACSprod, fromChain, fromInflux);
			 	    finalNetAnalysis[rctNumber,] <- reactionSummary;
			 	    rm(reactionSummary);			 		    				 	    
			 	    					 	    
			 	   # In the screenshot draw networks
    							  
 				# ACTUAL REACTIONS
				setwd(actDir)
 				setwd(paste("./__03_scaleFree", tmp___GraphFolderSuffix, sep=""));
	 				catInDegreeSortedNOLIFETIME <- sort(catInDegree_LIFETIME, decreasing = TRUE);
 					scaleFreeImageName <- paste("98_", strZerosGen, toString(tmpGen), "_", subStrGraph, "_", tmpRct, "_SF_N_Net", sep = "");
 					GraphLogYplot(scaleFreeImageName, "", "Connectivity", catInDegreeSortedNOLIFETIME)
 					# ACTUAL REACTIONS (NO LIFETIME) WEIGHTED GRAPH
		 			#catInWeightDegreeSortedNOLIFETIME <- sort(catWeightInDegree_LIFETIME[,1], decreasing = TRUE);
 					#scaleFreeImageName <- paste("99_", strZerosGen, toString(tmpGen), "_", strZerosSim, toString(tmpSim), "_", tmpRct, "_WSF_N_Net", sep = "");
 					#GraphLogYplot(scaleFreeImageName, "", "connections", catInWeightDegreeSortedNOLIFETIME);
 				setwd("../");
	
		 			
		 		strTime <- toString(tmpTime)
		 		G <- toString(tmpGen);
		 		S <- toString(tmpSim);
		 			
		 		# GRAPHS REPRESENTATION
		 		# CATALYST -> PRODUCT
		 		
		 								    				    			 	   								

				
				setwd(paste("./__02_nets", tmp___GraphFolderSuffix, sep=""));
					if(N_SCC_cat_LT > 0) # NO LIFETIME
					{
						netImageName <- paste("95_", subStrGraph, "_", tmpRct, "_", strTime, "_netCAT_Y_LifeTime_", N_SCC_cat_LT, sep = "");
						graphCompleteWeightNetSCCs(adjCatMatrix_LIFETIME, netImageName, 0, 
												   influxIds, livingSpecies, livingAmount, tot_SCC_speciesVTX_cat_LT);

						onlySCCgraph <- adjCatMatrix_LIFETIME[is.element(adjCatMatrix_LIFETIME[,1],IDspeciesPresentInScc),]
						#netImageName <- paste("97_", subStrGraph, "_", tmpRct, "_", strTime, "_netCAT_Y_LifeTime_SCC_names_", N_SCC_cat_LT, sep = "");
						#graphNetsNoSCConlyNames(onlySCCgraph, netImageName, lastSpecies)
						
						netImageName <- paste("98_", subStrGraph, "_", tmpRct, "_", strTime, "_netCAT_Y_LifeTime_SCC_names_", N_SCC_cat_LT, sep = "");
						graphCompleteWeightNetONLYSCCs(onlySCCgraph, netImageName, 0, 
												   influxIds, livingSpecies, livingAmount, tot_SCC_speciesVTX_cat_LT)												
						#readline(prompt = "Pause. Press <Enter> to continue...")
					}else{
						netImageName <- paste("95_", subStrGraph, "_", tmpRct, "_", strTime, "_netCAT_Y_LifeTime_0", sep = "");
						graphCompleteWeightNet(adjCatMatrix_LIFETIME, netImageName, 0, 
											   influxIds, livingSpecies, livingAmount);
					}
					

				setwd("../");
					
 				print(paste("      |- LITE VERSIONS - Time:", tmpTime, "Reactions:", tmpRct));
 				print(paste("     |- SIM", subStrGraph, "of", tmpNsimFolds, "- Reaction", rctNumber, "of", length(iGraphNetFile), " - ", rctNumber/length(iGraphNetFile)*100, " % Completed..."));
				rctNumber <- rctNumber + 1;								
		
			}# END for(iGraphFile in 1 : length(iGraphNetFile))	 	    							
		} # END (iGraphNetFile) 	
		

			
		# WRITE TO FILE	==========================
		dimnames(finalNetAnalysis)[2] <- list(c("time", "ELRP_LIFETIME", "R_LIFETIME", "INmeandegree_LIFETIME", 
	 		    				"NumberOfSCC_LT", "speciesInSCCs_LT", "percSngInSCCs_LT", "percSpeciesInSCCs_LT", 
	 	   		 			"max_SCC_LT", "min_SCC_LT", "mean_SCC_LT", "median_SCC_LT", 
		 		    			"mol_SCC_LT", "perc_mol_SCC_LT", "mol_SCC_LT_noinflux", "perc_mol_SCC_LT_noinflux", 
		 	    				"totMolNoInflux", "totSpeciesNoInflux", "fromACS", "fromACSprod", "fromChain", "fromInflux"));					
							
		# CATALYST -> PRODUCT
		setwd(paste("./__04_netstat", tmp___GraphFolderSuffix, sep=""))
			summaryFileName <- paste("_", subStrGraph, "_netAnalysis.csv", sep="");
			write.table(finalNetAnalysis, summaryFileName, sep="\t", row.names = FALSE);		
	    	summaryFileName <- paste("_", subStrGraph, "_adjCat2ProdMtx.csv", sep="");
	    	write.table(rctCatMtx, summaryFileName, sep="\t",
	    				row.names = unlist(strsplit(toString(speciesInvolved_LT),", ",fixed=TRUE)), 
	    				col.names = unlist(strsplit(toString(speciesInvolved_LT),", ",fixed=TRUE)));
	    	# PLOT NETWORK ANALYSIS OUTCOMES ------------------------------------------
			plotSingleSimNetAnalysisGraphLITE(finalNetAnalysis, "", "", subStrGraph, "");
		setwd("../");
		
		# CLEAN VARIABLE
		rm(finalNetAnalysis);
		rm(cat_adjMtx_LIFETIME);
		rm(rctParameters);
		rm(rctCatMtx);
						
	}# END if(length(alreadyAnalyzed) == 0)
} # eof
	
# -^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^-
# SUMMARIZING STATISTICS
# -^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^--^-^-^-^-^-^-^-^-^-^-^-^-^-^-
# FUNCTION TO PLOT ALL THE SIMULATION STORY

overallNETsummary <- function(tmpTotGens, tmpTotSims, tmp_GraphFolderSuffix, tmpFile, tmpSuffix, tmpSimPath)
{
	# close all devices
	graphics.off();
	#REFORMATTING DATA STRUCTURES
				
	# ------------------------------------------------------------------------------
	# CREATE A LIST OF ALL FILES ACCORDING TO THE SIMULTION AND THE TYPE OF ELEMENTS
	# ------------------------------------------------------------------------------

	# SEARCH FOR ALL THE STATISTICS FILE
	setwd(paste("./__04_netstat", tmp_GraphFolderSuffix, sep=""))
		networkFileList  <- dir(pattern = tmpFile);
	setwd("../")
	
	TMPNSIMS <- length(networkFileList);
	# COMPUTE THE MAX NUMBER OF REACTIONS
	maxNumberOfReactions <- 0;
	maxNumberOfnodes <- 0;	
	for(tmpNsim in 1 : TMPNSIMS)
	{
		# LOAD NETWORK ANALYSIS FILE
		setwd(paste("./__04_netstat", tmp_GraphFolderSuffix, sep=""))
			netFile  <- read.csv(networkFileList[tmpNsim], sep="\t");
		setwd("../")
		
		if(tmpNsim == 1)
		{
			# prepare vector of total number of reactions per generation
			numberOfRctsVector  <- nrow(netFile);
		}else{
			numberOfRctsVector  <- c(numberOfRctsVector, nrow(netFile)); 
		} 
		if(numberOfRctsVector[tmpNsim] > maxNumberOfnodes)
		{
			# store max number of reaction to create summary structures
			maxNumberOfnodes <- numberOfRctsVector[tmpNsim];
		}
	}
	    
	if(TMPNSIMS > 1)
	{		
		print("Overall Statistics Summary");	
		
		acsTimes 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		
		ELRP_Y_lifetime 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		R_Y_lifetime 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		INmeandegree_Y_lifetime 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		
		NumberOfSCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		speciesInSCCs_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		percSngInSCCs_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		percSpeciesInSCCs_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);

		max_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		min_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		mean_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		median_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		
		mols_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		perc_mols_SCC_LT 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);	
		
		mols_SCC_LT_noinflux 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		perc_mols_SCC_LT_noinflux 	<- matrix(NaN,maxNumberOfnodes,TMPNSIMS);	
		
		totSpeciesNoInflux <-  matrix(NaN,maxNumberOfnodes,TMPNSIMS);	 
		totMolNoInflux <- matrix(NaN,maxNumberOfnodes,TMPNSIMS);	
		
		totFromACS <- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		totFromACSprod <- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		totFromChain <- matrix(NaN,maxNumberOfnodes,TMPNSIMS);
		totFromInflux <- matrix(NaN,maxNumberOfnodes,TMPNSIMS);		
		
		tmpGenerationCounter <- 1;
		previuousSims <- 0;
		for(tmpNsim in 1 : TMPNSIMS)
		{
			if(tmpNsim > ((tmpTotSims^tmpGenerationCounter) + previuousSims))
		 	{
		 		previuousSims <- tmpTotSims^tmpGenerationCounter;
		 		tmpGenerationCounter <- tmpGenerationCounter + 1;
		 	}
			setwd(paste("./__04_netstat", tmp_GraphFolderSuffix, sep=""))
				acsFile <- read.csv(networkFileList[tmpNsim], sep="\t");
			setwd("../")
			acsRange <- 1:numberOfRctsVector[tmpNsim];
			acsTimes[acsRange,tmpNsim]	<- c(acsFile[,"time"]);
			# IF THE GENERATION NUMBER IS GREATER THAN ONE PREVIOUS TIMES HAVE TO BE ADDED
			if(tmpGenerationCounter > 1)
			{
				simsDone <- 0;
				for(tmpGen in 1 : (tmpGenerationCounter-1))
				{
					simsDone <- simsDone + tmpTotSims^tmpGen;
				}
				realSimGenNumber <- tmpNsim - simsDone;
				fatherTimeCol <- ceiling(realSimGenNumber / tmpTotSims);
				fatherGeneration <- tmpGenerationCounter - 1;
				if(fatherGeneration > 1)
				{
					simsFatherDone <- 0;
					for(tmpGen in 1 : (fatherGeneration-1))
					{
						simsFatherDone <- simsFatherDone + tmpTotSims^tmpGen;
					}	
					fatherTimeCol <- fatherTimeCol + simsFatherDone;	
				}
				acsTimes[acsRange,tmpNsim] <- acsTimes[acsRange,tmpNsim] + max(acsTimes[,fatherTimeCol]);
			}
			
			ELRP_Y_lifetime[acsRange,tmpNsim] 			<- acsFile[,"ELRP_LIFETIME"];
			R_Y_lifetime[acsRange,tmpNsim] 				<- acsFile[,"R_LIFETIME"];
			INmeandegree_Y_lifetime[acsRange,tmpNsim] 	<- acsFile[,"INmeandegree_LIFETIME"];

			NumberOfSCC_LT[acsRange,tmpNsim] 		<- acsFile[,"NumberOfSCC_LT"];
			speciesInSCCs_LT[acsRange,tmpNsim] 		<- acsFile[,"speciesInSCCs_LT"];
			percSngInSCCs_LT[acsRange,tmpNsim] 		<- acsFile[,"percSngInSCCs_LT"];
			percSpeciesInSCCs_LT[acsRange,tmpNsim] 	<- acsFile[,"percSpeciesInSCCs_LT"];

			max_SCC_LT[acsRange,tmpNsim] 	<- acsFile[,"max_SCC_LT"];
			min_SCC_LT[acsRange,tmpNsim] 	<- acsFile[,"min_SCC_LT"];
			mean_SCC_LT[acsRange,tmpNsim] 	<- acsFile[,"mean_SCC_LT"];
			median_SCC_LT[acsRange,tmpNsim]	<- acsFile[,"median_SCC_LT"];			

			mols_SCC_LT[acsRange,tmpNsim] 		<- acsFile[,"mol_SCC_LT"];
			perc_mols_SCC_LT[acsRange,tmpNsim] 	<- acsFile[,"perc_mol_SCC_LT"];
			
			mols_SCC_LT_noinflux[acsRange,tmpNsim] 		<- acsFile[,"mol_SCC_LT_noinflux"];
			perc_mols_SCC_LT_noinflux[acsRange,tmpNsim] <- acsFile[,"perc_mol_SCC_LT_noinflux"];
			
			totMolNoInflux[acsRange,tmpNsim] 	<- acsFile[,"totMolNoInflux"];
			totSpeciesNoInflux[acsRange,tmpNsim]<- acsFile[,"totSpeciesNoInflux"];	
			
			totFromACS[acsRange,tmpNsim] 	<- acsFile[,"fromACS"];
			totFromACSprod[acsRange,tmpNsim]<- acsFile[,"fromACSprod"];
			totFromChain[acsRange,tmpNsim] 	<- acsFile[,"fromChain"];;
			totFromInflux[acsRange,tmpNsim] <- acsFile[,"fromInflux"];							

		}
		
		tmpMiddleFileName <- paste("ALL_", tmpSuffix, sep="");

		TMPFROM <- 0;
		TMPTO = max(acsTimes[!is.nan(acsTimes)]);
		
    print(TMPTO)
				
		# ============================== // WITHOUT CONTINOUS LIFE TIME \\ 
		setwd(paste("./__05_all", tmp_GraphFolderSuffix, sep=""));
			GTS_diff_rctN("50", paste("50_", tmpMiddleFileName, "_ELRP_Y_lifetime", sep=""), "ELRP", acsTimes, ELRP_Y_lifetime, TMPFROM, TMPTO);
			GTS_diff_rctN("51", paste("51_", tmpMiddleFileName, "_R_Y_lifetime", sep=""), "R", acsTimes, R_Y_lifetime, TMPFROM, TMPTO);
			GTS_diff_rctN("52", paste("52_", tmpMiddleFileName, "_INdegree_Y_lifetime", sep=""), "IN-degree", acsTimes, INmeandegree_Y_lifetime, TMPFROM, TMPTO);
			GTS_diff_rctN("56", paste("56_", tmpMiddleFileName, "_SCCs_LT", sep=""), "# of SCCs", acsTimes, NumberOfSCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("57", paste("57_", tmpMiddleFileName, "_N_SCCs_LT", sep=""), "Species in ACSs", acsTimes, speciesInSCCs_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("58", paste("58_", tmpMiddleFileName, "_perc_N_SCCs_LT", sep=""), "% of Species in ACSs", acsTimes, percSngInSCCs_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("59", paste("59_", tmpMiddleFileName, "_perc_Ntot_SCCs_LT", sep=""), "% of Species in ACSs", acsTimes, percSpeciesInSCCs_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("60", paste("60_", tmpMiddleFileName, "_max_SCCs_LT", sep=""), "Max number of species in ACSs", acsTimes, max_SCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("61", paste("61_", tmpMiddleFileName, "_min_SCCs_LT", sep=""), "Min number of species in ACSs", acsTimes, min_SCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("62", paste("62_", tmpMiddleFileName, "_mean_SCCs_LT", sep=""), "Mean number of species in ACSs", acsTimes, mean_SCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("63", paste("63_", tmpMiddleFileName, "_median_SCCs_LT", sep=""), "Median number of species in ACSs", acsTimes, median_SCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("64", paste("64_", tmpMiddleFileName, "_mols_SCCs_LT", sep=""), "# of molecules in ACSs", acsTimes, mols_SCC_LT, TMPFROM, TMPTO);
			GTS_diff_rctN("65", paste("65_", tmpMiddleFileName, "_perc_mols_SCCs_LT", sep=""), "% of molecules in ACSs", acsTimes, perc_mols_SCC_LT, TMPFROM, TMPTO);	
			GTS_diff_rctN("66", paste("66_", tmpMiddleFileName, "_mols_SCCs_LT_noinflux", sep=""), "# of mols (NOT INFLUX) in ACSs", acsTimes, mols_SCC_LT_noinflux, TMPFROM, TMPTO);	
			GTS_diff_rctN("70", paste("70_", tmpMiddleFileName, "_molecules_noinflux", sep=""), "# of not supplied mols", acsTimes, totMolNoInflux, TMPFROM, TMPTO); 
			GTS_diff_rctN("71", paste("71_", tmpMiddleFileName, "_species_noinflux", sep=""), "# of not supplied species", acsTimes, totSpeciesNoInflux, TMPFROM, TMPTO); 
			GTS_diff_rctN_XY("72", paste("72_", tmpMiddleFileName, "_speciesVSmols_SCC", sep=""), "Species in ACSs", "Molecules in ACSs", speciesInSCCs_LT, mols_SCC_LT)
			GTS_diff_rctN_XY("73", paste("73_", tmpMiddleFileName, "_molsNoINFLUXVSmols_SCC", sep=""), "Molecules (non influx) in ACSs", "Molecules in ACSs", mols_SCC_LT_noinflux, mols_SCC_LT)
			GTS_diff_rctN_XY("74", paste("74_", tmpMiddleFileName, "_molsNoINFLUXscc_VSmolsNOINFLUX", sep=""), "Molecules (non influx) in ACSs", "Molecules (not influx)", mols_SCC_LT_noinflux, totMolNoInflux)
			# ----------------------|
			GTSerrorBar("80", paste("80_", tmpMiddleFileName, "ERR_ELRP_Y_lifetime", sep=""), "ELRP", acsTimes, ELRP_Y_lifetime);
			GTSerrorBar("81", paste("81_", tmpMiddleFileName, "ERR_R_Y_lifetime", sep=""), "R", acsTimes, R_Y_lifetime);
			GTSerrorBar("82", paste("82_", tmpMiddleFileName, "ERR_INdegree_Y_lifetime", sep=""), "IN-degree", acsTimes, INmeandegree_Y_lifetime);
			GTSerrorBar("83", paste("83_", tmpMiddleFileName, "ERR_SCCs_LT", sep=""), "Number of ACSs", acsTimes, NumberOfSCC_LT);
			GTSerrorBar("84", paste("84_", tmpMiddleFileName, "ERR_N_SCCs_LT", sep=""), "Species in ACSs", acsTimes, speciesInSCCs_LT);
			GTSerrorBar("85", paste("85_", tmpMiddleFileName, "ERR_perc_N_SCCs_LT", sep=""), "% of Species in ACSs", acsTimes, percSngInSCCs_LT);
			GTSerrorBar("86", paste("86_", tmpMiddleFileName, "ERR_perc_Ntot_SCCs_LT", sep=""), "% of Species in ACSs", acsTimes, percSpeciesInSCCs_LT);
			GTSerrorBar("87", paste("87_", tmpMiddleFileName, "ERR_max_SCCs_LT", sep=""), "Max number of species in ACSs", acsTimes, max_SCC_LT);
			GTSerrorBar("88", paste("88_", tmpMiddleFileName, "ERR_min_SCCs_LT", sep=""), "Min number of species in ACSs", acsTimes, min_SCC_LT);
			GTSerrorBar("89", paste("89_", tmpMiddleFileName, "ERR_mean_SCCs_LT", sep=""), "Mean number of species in ACSs", acsTimes, mean_SCC_LT);
			GTSerrorBar("90", paste("90_", tmpMiddleFileName, "ERR_median_SCCs_LT", sep=""), "Median number of species in ACSs", acsTimes, median_SCC_LT);
			GTSerrorBar("91", paste("91_", tmpMiddleFileName, "ERR_mols_SCCs_LT", sep=""), "# of molecules in ACSs", acsTimes, mols_SCC_LT);
			GTSerrorBar("92", paste("92_", tmpMiddleFileName, "ERR_perc_mols_SCCs_LT", sep=""), "% of molecules in SCCs", acsTimes, perc_mols_SCC_LT);
			GTSerrorBar("93", paste("93_", tmpMiddleFileName, "ERR_mols_SCCs_LT_noinflux", sep=""), "# of mols (NOT INFLUX) in ACSs", acsTimes, mols_SCC_LT_noinflux);
			GTSerrorBar("94", paste("94_", tmpMiddleFileName, "ERR_molecules_noinflux", sep=""), "# of not supplied mols", acsTimes, totMolNoInflux);
			GTSerrorBar("95", paste("95_", tmpMiddleFileName, "ERR_species_noinflux", sep=""), "# of not supplied species", acsTimes, totSpeciesNoInflux);
			GTSerrorBar("96", paste("96_", tmpMiddleFileName, "ERR_species_inACS", sep=""), "# of species catalysed within an ACS", acsTimes, totFromACS);
			GTSerrorBar("97", paste("97_", tmpMiddleFileName, "ERR_species_fromACS", sep=""), "# of species catalysed by an ACS", acsTimes, totFromACSprod);
			GTSerrorBar("98", paste("98_", tmpMiddleFileName, "ERR_species_fromChain", sep=""), "# of species catalysed by a chain", acsTimes, totFromChain);
			GTSerrorBar("99", paste("99_", tmpMiddleFileName, "ERR_species_fromInflux", sep=""), "# of species catalysed by the influx", acsTimes, totFromInflux);
		
		setwd("../");
		setwd(paste("./__04_netstat", tmp_GraphFolderSuffix, sep=""));
			filename <- paste("__times.csv", sep="");	
			write.table(acsTimes, filename, sep="\t", row.names = FALSE, col.names = FALSE);				
			filename <- paste("__ELRPs.csv", sep="");	
			write.table(ELRP_Y_lifetime, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__Rs.csv", sep="");	
			write.table(R_Y_lifetime, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__INDEGREEs.csv", sep="");	
			write.table(INmeandegree_Y_lifetime, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__SCCs.csv", sep="");	
			write.table(NumberOfSCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__NumSCCs.csv", sep="");	
			write.table(speciesInSCCs_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__PercSPECIESinSCCs.csv", sep="");	
			write.table(percSngInSCCs_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__PercSPECIESTOTinSCCs.csv", sep="");	
			write.table(percSpeciesInSCCs_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__max_SCCs_LT.csv", sep="");	
			write.table(max_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__min_SCCs_LT.csv", sep="");	
			write.table(min_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__mean_SCCs_LT.csv", sep="");	
			write.table(mean_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__median_SCCs_LT.csv", sep="");	
			write.table(median_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__MOLECULESinSCCs.csv", sep="");	
			write.table(mols_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__percMOLSinSCCs.csv", sep="");	
			write.table(perc_mols_SCC_LT, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__MOLSnonINFLUXinSCCs.csv", sep="");	
			write.table(mols_SCC_LT_noinflux, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__MOLSnonINFLUX.csv", sep="");	
			write.table(totMolNoInflux, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__NONSUPPLIEDSPECIES.csv", sep="");	
			write.table(totSpeciesNoInflux, filename, sep="\t", row.names = FALSE, col.names = FALSE);
			filename <- paste("__producedWithinAnACS.csv", sep="");	
			write.table(totFromACS, filename, sep="\t", row.names = FALSE, col.names = FALSE);		
			filename <- paste("__producedByAnACS.csv", sep="");	
			write.table(totFromACSprod, filename, sep="\t", row.names = FALSE, col.names = FALSE);	
			filename <- paste("__producedByChain.csv", sep="");	
			write.table(totFromChain, filename, sep="\t", row.names = FALSE, col.names = FALSE);	
			filename <- paste("__producedByInflux.csv", sep="");	
			write.table(totFromInflux, filename, sep="\t", row.names = FALSE, col.names = FALSE);											
		setwd("../");
		
	}
	graphics.off();
	rm(list=ls());
	
}
