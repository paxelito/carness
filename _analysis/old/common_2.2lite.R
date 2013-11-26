# LOAD LIBRARIES
# 	From 4.1
#		- -1 values in summary matrices have been substituted by NaN
#		- Box Bar plot for summarive all the simulation has been added
#		- General Y in function of X graph has been introduced

# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^-
#   GENERAL FUNCTIONS network --> clusters(ag, "strong")
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^-

require(Hmisc)


	# SET WHO MANY ZEROS GO AT THE BEGIN OF THE FILE/IMAGE NAME
	zeroBeforeStringNumber <- function(tmpTotN, tmpCurrentN)
	{
		tmpZeroReturned <- "";
		if(tmpCurrentN == 0)
		{
			tmpCurrentN <- 1;	
		}
		zerosToAdd <- trunc(log10(tmpTotN)) - trunc(log10(tmpCurrentN));
		if(zerosToAdd > 0)
		{
		for(i in 1 : zerosToAdd)
			{
				tmpZeroReturned <- paste(tmpZeroReturned, "0", sep="");
			}
		}
		return(tmpZeroReturned);	
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

	# CORRECT FILE LIST TO ADD INITIALIZATION FILE ACCORDING TO THE GENERATION NUMBER
	correctinitialFileNameinTheList <- function(tmpFileList, tmpGen, tmpTotGens, tmpSim, tmpTotSims, tmpMaxRctN, fileType)
	{
		# COMPUTE PREVIOUS FINAL SIMULATION INITIAL STRUCTURES
		initFather = ceiling(tmpSim / tmpTotSims);
		
		maxNumberOfSimulation = tmpTotSims^tmpGen;
		# ACCORDING TO THE maxNumberOfSimulation ZEROS IN STRING BEFORE NAME IS CREATED
		strZerosGen <- zeroBeforeStringNumber(tmpTotGens, tmpGen);	
		strZerosSim <- zeroBeforeStringNumber(maxNumberOfSimulation, tmpTotSims);
		strZerosRct <- zeroBeforeStringNumber(tmpMaxRctN, 0);
		
		if(tmpGen > 1)
		{
			if(tmpSim <= tmpTotSims^(tmpGen-1)) # IF THE SYSTEM CONSIDERS ALSO WRONG INITIALIZATION FILE
			{
				if(fileType == 1) # IF THE FILE LIST CONTAINS A WRONG FILE NAME (THE FIRST ONE)
				{
					tmpNewFileList <- paste("species_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");
				}else if(fileType == 2)
				{
					tmpNewFileList <- paste("reactions_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");	
				}else{
					tmpNewFileList <- paste("catalysis_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");
				}
				tmpNewFileList <- c(tmpNewFileList, tmpFileList[2:length(tmpFileList)]);
				tmpFileList <- tmpNewFileList;			
			}else{
				if(fileType == 1) # IF THE FILE LIST DOES NOT CONTAIN A WRONG FILE NAME
				{
					tmpNewFileList <- paste("species_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");
				}else if(fileType == 2)
				{
					tmpNewFileList <- paste("reactions_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");	
				}else{
					tmpNewFileList <- paste("catalysis_",strZerosGen,tmpGen,"_",strZerosSim,initFather,"_",strZerosRct,"0.csv", sep="");
				}
				tmpNewFileList <- c(tmpNewFileList, tmpFileList);
				tmpFileList <- tmpNewFileList;
			}								
		}else{
			if(fileType == 1) # IF THE FILE LIST REGARDS THE FIRST GENERATION
			{
				tmpNewFileList <- paste("species_",strZerosGen,"0_",strZerosSim,"0_",strZerosRct,"0.csv", sep="");
			}else if(fileType == 2)
			{
				tmpNewFileList <- paste("reactions_",strZerosGen,"0_",strZerosSim,"0_",strZerosRct,"0.csv", sep="");	
			}else{
				tmpNewFileList <- paste("catalysis_",strZerosGen,"0_",strZerosSim,"0_",strZerosRct,"0.csv", sep="");
			}
			tmpNewFileList <- c(tmpNewFileList, tmpFileList);
			tmpFileList <- tmpNewFileList;	
		}
		return(tmpFileList);
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
	
	checkAndOptimizeTimeSeries <- function(tmpTimesToAnal)
	{
		#check timesToAnal
		# FOR EACH TIME VALUE
		if(length(tmpTimesToAnal) > 1)
		{
			for(j in 2 : length(tmpTimesToAnal))
			{
				if(tmpTimesToAnal[j] != 0) # IF SOME REACTION OCCURS
				{
					if(tmpTimesToAnal[j] <= tmpTimesToAnal[j-1]) # IF THE TIME VALUE OF REACTION J IS EQUAL (MINOR-EQUAL FOR SURE) TO J-1
					{
						if(j < length(tmpTimesToAnal)) # IF THE REACTION J IS NOT THE LAST ONE
			       			{
			       				flagOk <- FALSE;
		    	   				count <- 1;
		       					while(flagOk == FALSE)# UNTIL A GREATER TIME WILL BE FIND
		       					{
		       						if(j+count > length(tmpTimesToAnal))
		       						{
		       							position <- j;
		       						}else{
		       							position <- j+count;
		       						}
		   	    					# TO ADD IS AN INTERMEDIATE VALUE BETWEEN TWO TIMES  
		   	    					if(position == j)
		   	    					{
		   	    						toAdd <- tmpTimesToAnal[j] - tmpTimesToAnal[j-1] * 1.0e-7;
		   	    					}else{
		    	   						toAdd <- ((tmpTimesToAnal[position] - tmpTimesToAnal[j]) / (count+1));
		   	    					}
		       						if(toAdd <= 0)
		       						{
		       							count <- count + 1;
		       						}else{
		       							flagOk <- TRUE;	
			       						tmpTimesToAnal[j] <- tmpTimesToAnal[j] + toAdd;
			       					}
			       					if(tmpTimesToAnal[position] == 0) # IF THE SYSTEM STOP THE EVOLUTION
		    	   					{
		       							flagOk <- TRUE;
		       							tmpTimesToAnal[j] <- tmpTimesToAnal[j-1] + tmpTimesToAnal[j-1] * 1.0e-7;
		       						}
		       						if(tmpTimesToAnal[position] == -1)
		       						{
		     	  							flagOk <- TRUE;
		       						}	       						
		       					}			
						}else{ # IF THE REACTION J IS THE LAST ONE
							tmpTimesToAnal[j] <- tmpTimesToAnal[j] + tmpTimesToAnal[j] * 1.0e-7;
						}
					}
				}else{
					tmpTimesToAnal[j] <- -1;	
				}
			}
		}
		return(tmpTimesToAnal)	
	}

# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# GENERAL GRAPHIC FUNCTION
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
	
	DrawThisGraph <- function(strGraphName)
	{
		#png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600, res = 300);
		#png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600);
		postscript(file = paste(strGraphName, ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, family="Times");
		#pdf(file = paste(strGraphName, ".pdf", sep = ""), onefile = FALSE, width = 8, height = 6);
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

	DrawThisGraphPNG <- function(strGraphName)
	{
		#png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600, res = 300);
		png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600);
		#postscript(file = paste(strGraphName, ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE);
		#pdf(file = paste(strGraphName, ".pdf", sep = ""), onefile = FALSE, width = 8, height = 6);
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\	

		DrawThisGraphNoFont <- function(strGraphName)
	{
		#png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600, res = 300);
		#png(filename = paste(strGraphName, ".png", sep = ""), width = 800, height = 600);
		postscript(file = paste(strGraphName, ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, family="Times", fonts=c("serif", "Palatino"));
		#pdf(file = paste(strGraphName, ".pdf", sep = ""), onefile = FALSE, width = 8, height = 6);
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

	DrawLegend <- function(tmpMtxToControl, tmpTextLegend)
	{
		tmpLegendColors = 1:(ncol(tmpMtxToControl));
		tmpLineType = 1:(ncol(tmpMtxToControl));
		legend("topleft", , tmpTextLegend, col=tmpLegendColors, lty=tmpLineType, cex = 1.5, lwd=3);
	}
	


# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# GRAPH TIME SERIES WITH DIFFERENT NUMBER OF REACTIONS
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

	GTS_diff_rctN <- function(tmpPrint, tmpName, tmpYlab, tmpTimes, tmpTimeSeries, tmpFrom, tmpTo)
	{
		possibleColors <- c("red","blue","green","purple","yellow","maroon","orange","cyan","magenta",
								  "lavender","grey","brown","azure","seashell","thistle","violet","turquoise",
								  "ivory","gold","cornsilk");
		DrawThisGraph(tmpName);
		# Select only real data from the matrix and then select only values present in the specific time interval
		realTimeToPlot <- tmpTimes[!is.nan(tmpTimes[,1]),1];
		realDataToPlot <- tmpTimeSeries[!is.nan(tmpTimeSeries[,1]) ,1];
		timeRange <- (realTimeToPlot > tmpFrom & realTimeToPlot < tmpTo);
		realTimeToPlot <- realTimeToPlot[timeRange];
		realDataToPlot <- realDataToPlot[timeRange];
		ylimit = c(0,max(tmpTimeSeries[!is.nan(tmpTimeSeries)]));
		xlimit = c(0,max(tmpTimes[!is.nan(tmpTimes)]));
		par(mar=c(5.1,5.1,2,2));
		plot(realTimeToPlot, realDataToPlot, xlab = expression("Time"), ylab = tmpYlab, type="b", col = possibleColors[1], font = 5, 
		    cex.lab = 2, cex.axis = 2, xlim = xlimit, ylim = ylimit, family="Times", cex=0.5, lty=2, lwd=3, frame.plot = FALSE);
		for(timeSerie in 2 : ncol(tmpTimeSeries))
		{
			realTimeToPlot <- tmpTimes[!is.nan(tmpTimes[,timeSerie]) , timeSerie];
			realDataToPlot <- tmpTimeSeries[!is.nan(tmpTimeSeries[,timeSerie]), timeSerie];
			timeRange <- (realTimeToPlot > tmpFrom & realTimeToPlot < tmpTo);
			realTimeToPlot <- realTimeToPlot[timeRange];
			realDataToPlot <- realDataToPlot[timeRange];
			lines(realTimeToPlot, realDataToPlot, type="b", col = possibleColors[timeSerie], cex=0.5, lty=2, lwd=3);
		}
		grid();
		dev.off();
		rm(tmpTimes)
		rm(tmpTimeSeries)
	}
	
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# GRAPH TIME SERIES WITH DIFFERENT NUMBER OF REACTIONS
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

	GTS_diff_rctN_XY <- function(tmpPrint, tmpName, tmpXlab, tmpYlab, tmpX, tmpY)
	{
		possibleColors <- c("red","blue","green","purple","yellow","maroon","orange","cyan","magenta",
								  "lavender","grey","brown","azure","seashell","thistle","violet","turquoise",
								  "ivory","gold","cornsilk");
		possibleSymbols <- c("*",".", "o","O","0","+","-","@","%","#");
		nex <- length(possibleSymbols)
    	np  <- 26 + nex
    	ipch <- 0:(np-1)
    	pch <- as.list(ipch)
		if(nex > 0) pch[26+ 1:nex] <- as.list(possibleSymbols)
		
		DrawThisGraph(tmpName);
		# Select only real data from the matrix and then select only values present in the needed time interval
		realXToPlot <- tmpX[tmpX[,1] != NaN ,1];
		realYToPlot <- tmpY[tmpY[,1] != NaN ,1];
		ylimit = c(0,max(tmpY[!is.nan(tmpY)]));
		xlimit = c(0,max(tmpX[!is.nan(tmpX)]));
		par(mar=c(5.1,5.1,2,2));
		plot(realXToPlot, realYToPlot, xlab = tmpXlab, ylab = tmpYlab, type="n", font = 5, 
		     cex.lab = 2, cex.axis = 2, xlim = xlimit, ylim = ylimit, family="Times", cex=0.5, lty=2, lwd=3, frame.plot = FALSE);
		for(timeSerie in 1 : ncol(tmpX))
		{
			pc <- pch[[timeSerie]]
			realXToPlot <- tmpX[!is.nan(tmpX[,timeSerie]), timeSerie];
			realYToPlot <- tmpY[!is.nan(tmpY[,timeSerie]), timeSerie];
			points(realXToPlot, realYToPlot, type="p",col = "lightgray", pch = pc, cex=0.5, lty=2, lwd=3);
		}
		grid();
		dev.off();
		rm(tmpXlab)
		rm(tmpYlab)
	}

# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# GRAPH TIME SERIES WITH DIFFERENT NUMBER OF REACTIONS
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

	GTSerrorBar <- function(tmpPrint, tmpName, tmpYlab, tmpTimes, tmpTimeSeries)
	{
		DrawThisGraph(tmpName);
		# Select only real data from the matrix and then select only values present in the needed time interval
		# Compute average of all data
		AVGdata <- rowMeans(tmpTimeSeries, na.rm=TRUE);
		AVGtime <- rowMeans(tmpTimes, na.rm=TRUE);
		ERRdata <- sd(t(tmpTimeSeries), na.rm=TRUE)#/(rowSums(!is.nan(tmpTimeSeries))^0.5)
		ERRtime <- sd(t(tmpTimes), na.rm=TRUE)#/(rowSums(!is.nan(tmpTimes))^0.5)
		
		AVGdata[is.nan(AVGdata)] <- 0;
		ERRdata[is.nan(ERRdata)] <- 0;

		ylimi = 1;
		if(!is.nan(max(AVGdata)))
		{
			ylimi = max(AVGdata);
			ylimi = ylimi * 1.2;	
		}
		ylimit = c(0,ylimi);
		xlimit = c(0,max(AVGtime));
		par(mar=c(5.1,5.1,2,2));
		errbar(AVGtime, AVGdata, AVGdata+ERRdata, AVGdata-ERRdata, xlab = expression("Time"), ylab = tmpYlab, type="l", font = 5, 
		     cex.lab = 2, cex.axis = 2, xlim = xlimit, ylim = ylimit, family="Times", cex=0.5, lty=2, lwd=1, frame.plot = FALSE);
		     lines(AVGtime, AVGdata, lwd=2)
		#points(AVGtime, apply(tmpTimeSeries,1,max), type="p", cex=0.5, lty=2, lwd=3);
		#points(AVGtime, apply(tmpTimeSeries,1,min), type="p", cex=0.5, lty=2, lwd=3);
		
		#boxplot(t(tmpTimeSeries), xaxt="n", ylab=tmpYlab, xlab="Time", col="light grey", cex.axis = 2, cex.lab = 2)
		#xticks <- seq(0,length(AVGtime)-1, (length(AVGtime)-1)/10)
		#xLabels = round(seq(0,max(AVGtime), max(AVGtime)/10),1)
		#axis(1, at = xticks, las = 1, cex.axis = 2, labels = xLabels)
		#grid();
		dev.off();
		rm(tmpTimes)
		rm(tmpTimeSeries)
	}	
	
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# GRAPH TIME SERIES WITH DIFFERENT NUMBER OF REACTIONS
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

	GTSboxPlot <- function(tmpPrint, tmpName, tmpYlab, tmpTimes, tmpTimeSeries)
	{
		DrawThisGraph(tmpName);
		# Select only real data from the matrix and then select only values present in the needed time interval
		# Compute average of all data
		AVGdata <- rowMeans(tmpTimeSeries, na.rm=TRUE);
		AVGtime <- rowMeans(tmpTimes, na.rm=TRUE);
		ERRdata <- sd(t(tmpTimeSeries), na.rm=TRUE)/(rowSums(!is.nan(tmpTimeSeries))^0.5)
		ERRtime <- sd(t(tmpTimes), na.rm=TRUE)/(rowSums(!is.nan(tmpTimes))^0.5)
		
		AVGdata[is.nan(AVGdata)] <- 0;
		ERRdata[is.nan(ERRdata)] <- 0;

		ylimit = c(0,max(AVGdata)+max(ERRdata));
		xlimit = c(0,max(AVGtime));
		par(mar=c(5.1,5.1,2,2));
		#errbar(AVGtime, AVGdata, AVGdata+ERRdata, AVGdata-ERRdata, xlab = expression("Time"), ylab = tmpYlab, type="l", font = 5, 
		#     cex.lab = 2, cex.axis = 2, xlim = xlimit, ylim = ylimit, family="Times", cex=0.5, lty=1, lwd=3, frame.plot = FALSE);
		#points(AVGtime, apply(tmpTimeSeries,1,max), type="p", cex=0.5, lty=2, lwd=3);
		#points(AVGtime, apply(tmpTimeSeries,1,min), type="p", cex=0.5, lty=2, lwd=3);
		
		boxplot(t(tmpTimeSeries), xaxt="n", ylab=tmpYlab, xlab="Time", col="light grey", cex.axis = 2, cex.lab = 2)
		xticks <- seq(0,length(AVGtime)-1, (length(AVGtime)-1)/10)
		xLabels = round(seq(0,max(AVGtime), max(AVGtime)/10),1)
		axis(1, at = xticks, las = 1, cex.axis = 2, labels = xLabels)
		#grid();
		dev.off();
		rm(tmpTimes)
		rm(tmpTimeSeries)
	}
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

	GraphTimeSeries <- function(tmpPrint, tmpName, tmpMain, tmpYlab, tmpTimes, tmpTimeSeries)
	{
		DrawThisGraph(tmpName);
		par(mar=c(5.1,5.1,2,2));
		matplot(tmpTimes, tmpTimeSeries, main = tmpMain, xlab = expression("Time"), ylab = tmpYlab, type="b", cex=0.5, font = 5, cex.lab = 2, cex.axis = 2, lwd = 3, frame.plot = FALSE, family="Times");
		grid(lwd=2);
		rm(tmpTimes)
		rm(tmpTimeSeries)
		dev.off();
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

	GraphTimeSeriesL <- function(tmpPrint, tmpName, tmpMain, tmpYlab, tmpTimes, tmpTimeSeries)
	{
		DrawThisGraph(tmpName);
		par(mar=c(5.1,5.1,2,2));
		matplot(tmpTimes, tmpTimeSeries, main = tmpMain, xlab = expression("Time"), ylab = tmpYlab, type="l", cex=0.5, font = 5, cex.lab = 2, cex.axis = 2, lwd = 3, frame.plot = FALSE, family="Times");
		grid(lwd=2);
		rm(tmpTimes)
		rm(tmpTimeSeries)
		dev.off();
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
	
	GraphTimeSeriesWithLegend <- function(tmpPrint, tmpName, tmpMain, tmpYlab, tmpTimes, tmpTimeSeries, tmpLegend)
	{
		DrawThisGraph(tmpName);
		par(mar=c(5.1,5.1,2,2));
		matplot(tmpTimes, tmpTimeSeries, main = tmpMain, xlab = expression("Time"), ylab = tmpYlab, type="l", cex=0.5, font = 5, cex.lab = 2, cex.axis = 2, lwd = 3, frame.plot = FALSE, family="Times");
		grid(lwd=2);
		DrawLegend(tmpTimeSeries, tmpLegend);
		dev.off();
		rm(tmpTimes)
		rm(tmpTimeSeries)
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
	
	GraphAllTimeSeries <- function(tmpPrint, tmpFileName, tmpMain, tmpYlab, tmpTimes, MtxSpeciesSpace)
	{
		columns <- max(MtxSpeciesSpace[,1])+1;
		times <- unique(MtxSpeciesSpace[,2]);
		timeSeries <- matrix(0, length(times), columns); 
		for(i in 1 : nrow(MtxSpeciesSpace))
		{
			timeSeries[which(times==MtxSpeciesSpace[i,2]), MtxSpeciesSpace[i,1]+1] <- MtxSpeciesSpace[i,3];
		}
		GraphTimeSeries(tmpPrint, tmpFileName, "", "Molecules", times, timeSeries);
		rm(MtxSpeciesSpace)
		rm(timeSeries)	
	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
	
	GraphAllTimeSeriesL <- function(tmpPrint, tmpFileName, tmpMain, tmpYlab, tmpTimes, MtxSpeciesSpace)
	{
		columns <- max(MtxSpeciesSpace[,1])+1;
		times <- unique(MtxSpeciesSpace[,2]);
		timeSeries <- matrix(0, length(times), columns); 
		for(i in 1 : nrow(MtxSpeciesSpace))
		{
			timeSeries[which(times==MtxSpeciesSpace[i,2]), MtxSpeciesSpace[i,1]+1] <- MtxSpeciesSpace[i,3];
		}
		GraphTimeSeriesL(tmpPrint, tmpFileName, "", "Molecules", times, timeSeries);
		rm(MtxSpeciesSpace)
		rm(timeSeries)	
	}

# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--
# 3D GRAPHIC FUNCTIONS
# -^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^---^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--^--

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

GraphSpecies3DSpace <- function(MtxSpeciesSpace, tmpImageName, tmpMain, tmpX, tmpY, tmpZ)
{
	# Select only the records within the time range	
	DrawThisGraph(tmpImageName);
	scatterplot3d(MtxSpeciesSpace[, 1], MtxSpeciesSpace[, 2], MtxSpeciesSpace[, 3], cex.symbol=1, xlab = tmpX, ylab = tmpY, zlab = tmpZ, highlight.3d = TRUE, type="h", family="Times", cex.lab=1, cex.axis=1, las=1, box=FALSE);
	title(main = tmpMain);
	rm(MtxSpeciesSpace);
	dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

#--------------------------
# FUNCTION TO CRETE 2D PLOT d3SizeDistFileList, speciesSpaceImagesName, "", "Species Length", "Amount", TMPNSIMS, TMPFROM, TMPTO
#--------------------------
GraphSpecies2Dplot <- function(tmpPrint, tmpFileName, tmpImageName, tmpMain, tmpX, tmpY, tmpNsims, tmpFrom, tmpTo)
{
	possibleColors <- c("red","blue","green","purple","yellow","maroon","orange","cyan","magenta","lavender","grey","brown","azure","seashell","thistle","violet","turquoise","ivory","gold","cornsilk");	
	DrawThisGraph(tmpImageName);
	
	#SELECT GRAPH LIMITS
	xmax <- 0;
	ymax <- 0;
	for(i in 1 : tmpNsims)
	{
			MtxSpeciesSpace <- read.csv(tmpFileName[i], sep="\t");
			timeToEvaluate <- max(MtxSpeciesSpace[,"time"]);
			MtxSpeciesSpace <- MtxSpeciesSpace[MtxSpeciesSpace[,2] == timeToEvaluate,];
			if(max(MtxSpeciesSpace[,"Length"]) > xmax)
			{
				xmax <- max(MtxSpeciesSpace[,"Length"]);
			}
			if(max(MtxSpeciesSpace[,"amount"]) > ymax)
			{
				ymax <- max(MtxSpeciesSpace[,"amount"]);
			}			
			rm(MtxSpeciesSpace);
	}	
	
	xlimit = c(0, xmax);
	ylimit = c(0, ymax);	
	
	#DRAW GRAPH
	for(i in 1 : tmpNsims)
	{
		if(i == 1)
		{
			MtxSpeciesSpace <- read.csv(tmpFileName[i], sep="\t");
			timeToEvaluate <- max(MtxSpeciesSpace[,"time"]);
			MtxSpeciesSpace <- MtxSpeciesSpace[MtxSpeciesSpace[,2] == timeToEvaluate,];
			par(mar=c(5.1,5.1,2,2));
			plot(MtxSpeciesSpace[,"Length"], MtxSpeciesSpace[,"amount"], xlab = tmpX, ylab = tmpY, type="p", font = 5, cex.lab = 2, cex.axis = 2, ylim = ylimit, xlim = xlimit, family="Times");
		}else{
			MtxSpeciesSpace <- read.csv(tmpFileName[i], sep="\t");
			timeToEvaluate <- max(MtxSpeciesSpace[,"time"]);
			MtxSpeciesSpace <- MtxSpeciesSpace[MtxSpeciesSpace[,2] == timeToEvaluate,];
			lines(MtxSpeciesSpace[,"Length"], MtxSpeciesSpace[,"amount"], type="p", col = possibleColors[i]);			
		}	
		rm(MtxSpeciesSpace);
	}
	grid();
	dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
#--------------------------------
# FUNCTION TO CRETE 3D LANDSCAPES
#--------------------------------

GraphSpecies3DSpaceLandscape <- function(MtxSpeciesSpace, tmpImageName, tmp_times, tmpMain, tmpX, tmpY, tmpZ)
{
	
	if(length(tmp_times) > 1)
	{
		# IF THE FIRST ID SPECIES IS 0, THEN ALL THE ID ARE INCREMENTED TO ADAPT THEM TO R
		if(sum(MtxSpeciesSpace[,1] == 0) > 0)
		{
			MtxSpeciesSpace[,1] <-MtxSpeciesSpace[,1] + 1;
		}
		timesIDs <- seq(1, length(tmp_times));
		timesToAnal <- tmp_times;
		zMatrix <- matrix(0, max(MtxSpeciesSpace[,1]), length(tmp_times));
		for(i in 1 : nrow(MtxSpeciesSpace))
		{	
			zMatrix[MtxSpeciesSpace[i,1], timesIDs[MtxSpeciesSpace[i,2]==timesToAnal]] =  MtxSpeciesSpace[i,3];
		}
	
		#check timesToAnal
		#timesToAnal <- checkAndOptimizeTimeSeries(timesToAnal);
		DrawThisGraph(tmpImageName);
		tmpXaxis <- seq(1:max(MtxSpeciesSpace[,1]));
		tmpYaxis <- timesToAnal; 
		persp(tmpXaxis, tmpYaxis, zMatrix, theta = 30, phi = 30, expand = 0.5, col = "lightblue", ltheta = 120, shade = 0.75, ticktype = "detailed", xlab = tmpX, ylab = tmpY, zlab = tmpZ)
		title(main = tmpMain);
		rm(MtxSpeciesSpace);
	}else{
		print("WARNING: There are not eanough time steps in the interval, hence this graphs is not useful");	
	}
	dev.off();
	
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
#-----------------------------------------------------------------------------------------
# FUNCTION TO CRETE 3D LANDSCAPES WITHOUT CONSIDERING TIME INTERVALS BUT REGULAR INTERVALS
#-----------------------------------------------------------------------------------------

GraphSpecies3DSpaceLandscapeNoTime <- function(MtxSpeciesSpace, tmpImageName, tmp_times, tmpMain, tmpX, tmpY, tmpZ)
{
	if(length(tmp_times) > 1)
	{
			# IF THE FIRST ID SPECIES IS 0, THEN ALL THE ID ARE INCREMENTED TO ADAPT THEM TO  R
		if(sum(MtxSpeciesSpace[,1] == 0) > 0)
		{
			MtxSpeciesSpace[,1] <-MtxSpeciesSpace[,1] + 1;
		}
		zMatrix <- matrix(0, max(MtxSpeciesSpace[, 1]), length(tmp_times));
		timesIDs <- seq(1, length(tmp_times));
		timesToAnal <- tmp_times;
		for(i in 1 : nrow(MtxSpeciesSpace))
		{	
			zMatrix[MtxSpeciesSpace[i,1], timesIDs[MtxSpeciesSpace[i,2]==timesToAnal]] =  MtxSpeciesSpace[i,3];
		}
	
		DrawThisGraph(tmpImageName);
		tmpXaxis <- seq(1:max(MtxSpeciesSpace[,1]));
		tmpYaxis <- timesIDs; 
		persp(tmpXaxis, tmpYaxis, zMatrix, theta = 30, phi = 30, expand = 0.5, col = "lightblue", ltheta = 120, shade = 0.75, ticktype = "detailed", xlab = tmpX, ylab = tmpY, zlab = tmpZ)
		title(main = tmpMain);
		rm(MtxSpeciesSpace);
	}else{
		print("WARNING: There are not eanough time steps in the interval, hence this graphs is not useful");	
	}
	dev.off();
	
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
#
#	graphNet <- function(tmpAdjStr, tmpImgName)
#	{
#		 TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
#		igraphAdjStr <- graph.data.frame(tmpAdjStr, directed=TRUE);
#		plot.igraph(igraphAdjStr, vertex.size=2, layout=layout.kamada.kawai);
#		dev.off()
#	}
	
# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# DRAW NET STARTING FROM A STRUCTURE CONTAINING THE ADJACENCE MATRIX IN THE FIRST TWO COLUMNS 
graphNet <- function(tmpAdjStr, tmpImgName)
{
	DrawThisGraphPNG(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	#coords <- layout.fruchterman.reingold(igraphAdjStr, dim=3) ;
	#rglplot(igraphAdjStr, layout=coords, vertex.label=V(igraphAdjStr)$name) ;
	plot.igraph(igraphAdjStr, vertex.size=6, layout=layout.fruchterman.reingold, vertex.label=V(igraphAdjStr)$name);
	dev.off();
}


# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# DRAW A WEIGHTED NET STARTING FROM A STRUCTURE CONTAINING THE ADJACENCE MATRIX IN THE FIRST TWO COLUMNS 
graphWeightNet <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	weightNormalized <- (tmpAdjStr[,6] / max(tmpAdjStr[,6])) * 5;
	igraphAdjStr <- set.edge.attribute(igraphAdjStr, "weight", value=c(weightNormalized));
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2) ;
	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label=tmpAdjStr[,6], edge.label.cex=0.6, edge.width=E(igraphAdjStr)$weight, edge.arrow.size=0.3);
	dev.off();
	#readline(prompt = "Pause. Press <Enter> to continue...")
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# DRAW A WEIGHTED NET STARTING FROM A STRUCTURE CONTAINING THE ADJACENCE MATRIX IN THE FIRST TWO COLUMNS 
graphCompleteWeightNet <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs, tmpLiving, tmpAmount)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	weightNormalized <- (tmpAdjStr[,6] / max(tmpAdjStr[,6])) * 5;
	igraphAdjStr <- set.edge.attribute(igraphAdjStr, "weight", value=c(weightNormalized));
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2) ;
	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	# Set vertex default size
	V(igraphAdjStr)$size <- 0;
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$size <- 10;
	# According to the total amount of each species vertex size is updated
	for(i in 1 : length(tmpLiving))
	{
		if(sum(is.element(tmpInfluxSpeciesIDs, tmpLiving[i])) == 0)
		{
			V(igraphAdjStr)[as.integer(V(igraphAdjStr)$name) == tmpLiving[i]]$size <- 5 + (tmpAmount[i]/sum(tmpAmount) * 30);
		}
	}
	plot.igraph(igraphAdjStr, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label=tmpAdjStr[,6], edge.label.cex=0.6, edge.width=E(igraphAdjStr)$weight, edge.arrow.size=0.3);
	dev.off();
	#readline(prompt = "Pause. Press <Enter> to continue...")
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# DRAW A WEIGHTED NET STARTING FROM A STRUCTURE CONTAINING THE ADJACENCE MATRIX IN THE FIRST TWO COLUMNS 
graphWeightNetSCCs <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs, tmpSCCs)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	weightNormalized <- (tmpAdjStr[,6] / max(tmpAdjStr[,6])) * 5;
	igraphAdjStr <- set.edge.attribute(igraphAdjStr, "weight", value=c(weightNormalized));
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2) ;
	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	V(igraphAdjStr)[tmpSCCs]$color <- "blue";
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label=tmpAdjStr[,6], edge.label.cex=0.6, edge.width=E(igraphAdjStr)$weight, edge.arrow.size=0.3);
	dev.off();
	#readline(prompt = "Pause. Press <Enter> to continue...")
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# DRAW A COMPLETE WEIGHTED NET (REACTION OCCURANCES AND CONCENTRATIONS) 
# STARTING FROM A STRUCTURE CONTAINING THE ADJACENCE MATRIX IN THE FIRST TWO COLUMNS 
graphCompleteWeightNetSCCs <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs, tmpLiving, tmpAmount, tmpSCCs)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	weightNormalized <- (tmpAdjStr[,6] / max(tmpAdjStr[,6])) * 5;
	igraphAdjStr <- set.edge.attribute(igraphAdjStr, "weight", value=c(weightNormalized));
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2) ;
	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	V(igraphAdjStr)[tmpSCCs]$color <- "blue";
	# Set vertex default size
	V(igraphAdjStr)$size <- 0;
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$size <- 10;
	# According to the total amount of each species vertex size is updated
	for(i in 1 : length(tmpLiving))
	{
		if(sum(is.element(tmpInfluxSpeciesIDs, tmpLiving[i])) == 0)
		{
			V(igraphAdjStr)[as.integer(V(igraphAdjStr)$name) == tmpLiving[i]]$size <- 5 + (tmpAmount[i]/sum(tmpAmount) * 30);
		}
	}
	plot.igraph(igraphAdjStr, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label=tmpAdjStr[,6], edge.label.cex=0.6, edge.width=E(igraphAdjStr)$weight, edge.arrow.size=0.3);
	dev.off();
	#readline(prompt = "Pause. Press <Enter> to continue...")
}

graphCompleteWeightNetONLYSCCs <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs, tmpLiving, tmpAmount, tmpSCCs)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	weightNormalized <- (tmpAdjStr[,6] / max(tmpAdjStr[,6])) * 5;
	igraphAdjStr <- set.edge.attribute(igraphAdjStr, "weight", value=c(weightNormalized));
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2) ;
	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, as.integer(tmpSCCs$name))]$color <- "blue";
	# Set vertex default size
	V(igraphAdjStr)$size <- 0;
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$size <- 10;
	# According to the total amount of each species vertex size is updated
	for(i in 1 : length(tmpLiving))
	{
		if(sum(is.element(tmpInfluxSpeciesIDs, tmpLiving[i])) == 0)
		{
			V(igraphAdjStr)[as.integer(V(igraphAdjStr)$name) == tmpLiving[i]]$size <- 5 + (tmpAmount[i]/sum(tmpAmount) * 30);
		}
	}
	plot.igraph(igraphAdjStr, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label=tmpAdjStr[,6], edge.label.cex=0.6, edge.width=E(igraphAdjStr)$weight, edge.arrow.size=0.3);
	dev.off();
	#readline(prompt = "Pause. Press <Enter> to continue...")
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\	
# DRAW A NET STARTING FROM THE FIRING DISK 	
graphPossibleNet <- function(tmpAdjStr, tmpImgName, tmp___LastFiringDiskSpeciesID, tmpInfluxSpeciesIDs)
{
	DrawThisGraphNoFont(tmpImgName);
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpAdjStr[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2);
	V(igraphAdjStr)[as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID]$color <- "red";
#	print(V(igraphAdjStr))
#	print(V(igraphAdjStr)$name)
#	print(tmpInfluxSpeciesIDs)
#	print(is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs));
	V(igraphAdjStr)[is.element(V(igraphAdjStr)$name, tmpInfluxSpeciesIDs)]$color <- "green";
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, 
				edge.label.cex=0.6, edge.arrow.size=0.7);
	dev.off();

}



# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\	
# DRAW two nets (with ID and with sequence) coloring nodes belonging to the SCCs 
graphNets <- function(tmpGraphMtx, tmpImgName, tmp_Species, tmpSng_css_ids)
{
	postscript(file = paste(tmpImgName[1], ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpGraphMtx[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2);
	#V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	V(igraphAdjStr)[tmpSng_css_ids]$color <- "red";
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, edge.arrow.size=0.5);
	dev.off();
	
	postscript(file = paste(tmpImgName[2], ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=tmp_Species[as.integer(V(igraphAdjStr)$name)+1,2], edge.arrow.size=0.5);
	dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\	
# DRAW two nets (with ID and with sequence) 
graphNetsNoSCC <- function(tmpGraphMtx, tmpImgName, tmp_Species)
{
	postscript(file = paste(tmpImgName[1], ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpGraphMtx[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2);
	#V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, edge.arrow.size=0.5);
	dev.off();
	
	postscript(file = paste(tmpImgName[2], ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=tmp_Species[as.integer(V(igraphAdjStr)$name)+1,2], edge.arrow.size=0.5);
	dev.off();
}

graphNetsNoSCConlyNames <- function(tmpGraphMtx, tmpImgName, tmp_Species)
{
#	postscript(file = paste(tmpImgName[1], ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	# TRANSFORM ADJSTRUCTURE IN IGRAPH STRUCTURE
	adjStr <- tmpGraphMtx[,1:2];
	igraphAdjStr <- graph.data.frame(adjStr, directed=TRUE);
	coords <- layout.fruchterman.reingold(igraphAdjStr, dim=2);
#	V(igraphAdjStr)[ as.integer(V(igraphAdjStr)$name) <= tmp___LastFiringDiskSpeciesID ]$color <- "red";
#	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=V(igraphAdjStr)$name, edge.arrow.size=0.5);
#	dev.off();
	
	postscript(file = paste(tmpImgName, ".eps", sep = ""), width = 8, height = 6, onefile = FALSE, horizontal = FALSE, fonts=c("serif", "Palatino"));
	#print(tmp_Species[as.integer(V(igraphAdjStr)$name)+1,2])
	plot.igraph(igraphAdjStr, vertex.size=6, vertex.label.cex=0.6, layout=coords, vertex.label=tmp_Species[as.integer(V(igraphAdjStr)$name)+1,2], edge.arrow.size=0.5);
	dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# 

plotSingleSimNetAnalysisGraph <- function(tmpFinalNetAnalysis, tmpStrZeroGen, tmp_gen, tmpStrZeroSim, tmp_sim, tmpRctTypes)
{
	# PLOT EIGEN ANALYSIS ------------------------------------------
	if(nrow(tmpFinalNetAnalysis) > 1)
	{
	
	# ACTUAL REACTIONS 
	acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_acsDetection", sep = "");
	legend <- c("ELRP","R");
	GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,2:3], legend);
	
	# PLOT IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_Degree", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,4:5], legend);
	
	# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_WeightDegree", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,6:7], legend);
	
	
	# POSSIBLE REACTIONS
	# PLOT EIGEN ANALYSIS ------------------------------------------
	acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_acsDetection_N_lifetime", sep = "");
	legend <- c("ELRP","R");
	GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,8:9], legend);
	
	# PLOT IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_Degree_N_lifetime", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,10:11], legend);
	
	# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_WeightDegree_N_lifetime", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,12:13], legend);
	
	# POSSIBLE REACTIONS
	# PLOT EIGEN ANALYSIS ------------------------------------------
	acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_acsDetection_Y_lifetime", sep = "");
	legend <- c("ELRP","R");
	GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,14:15], legend);
	
	# PLOT IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_Degree_Y_lifetime", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,16:17], legend);
	
	# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_IO_WeightDegree_Y_lifetime", sep = "");
	legend <- c("IN-DEGREE", "OUT-DEGREE");
	GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,18:19], legend);
	
	# PLOT SCC -----------------------------------------------
	acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,20]);
	acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,21]);
	acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,22]);		
	acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_N_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,23]);
	acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_N_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,24]);
	acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_N_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,25]);
	acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_N_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of catalysts in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,26]);
	acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_N_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of catalysts in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,27]);
	acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_N_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of catalysts in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,28]);
	acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_Ntot_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,29]);
	acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_Ntot_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,30]);
	acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_Ntot_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,31]);
	
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_MMMM_SCCs", sep = "");
	legend <- c("Max", "Min", "Mean", "Median");
	GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,32:35], legend);
	
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_MMMM_SCCs_NLT", sep = "");
	legend <- c("Max", "Min", "Mean", "Median");
	GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,36:39], legend);
	
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_MMMM_SCCs_LT", sep = "");
	legend <- c("Max", "Min", "Mean", "Median");
	GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,40:43], legend);	
	
	# MOLECULES IN SCCs
	acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,44]);
	acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,45]);
	acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,46]);
	acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,47]);
	acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_NLT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,48]);
	acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,49]);		
	
	# MOLECULES IN SCCs and not belonging to tha influx
	acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,50]);
	acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_NLT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,51]);
	acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_LT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,52]);
	acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,53]);
	acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_NLT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,54]);
	acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_LT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,55]);
	
	# Number of molecules not belonging to the INFLUX
	acsImageName <- paste("24_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_molecules_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of not supplied molecules", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,56]);
	acsImageName <- paste("25_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_species_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of not supplied species", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,57]);		
	} # end if(nrow(tmpFinalNetAnalysis) > 1)
	
	# reactions histograms tmpRctTypes
	histImageName <- paste("26_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_reactionsTypeFrequence", sep = "");
	makeHistogram(histImageName, tmpRctTypes, 2, c("Condensation","Cleavage"));
}

plotSubSingleSimNetAnalysisGraph <- function(tmpFinalNetAnalysis, tmpStrZeroGen, tmp_gen, tmpStrZeroSim, tmp_sim)
{
	# PLOT EIGEN ANALYSIS ------------------------------------------
	if(nrow(tmpFinalNetAnalysis) > 1)
	{
	
		# ACTUAL REACTIONS 
		acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_acsDetection", sep = "");
		legend <- c("ELRP","R");
		GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,2:3], legend);
		
		# PLOT IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_Degree", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,4:5], legend);
		
		# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_WeightDegree", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,6:7], legend);
		
		
		# POSSIBLE REACTIONS
		# PLOT EIGEN ANALYSIS ------------------------------------------
		acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_acsDetection_N_lifetime", sep = "");
		legend <- c("ELRP","R");
		GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,8:9], legend);
		
		# PLOT IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_Degree_N_lifetime", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,10:11], legend);
		
		# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_WeightDegree_N_lifetime", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,12:13], legend);
		
		# POSSIBLE REACTIONS
		# PLOT EIGEN ANALYSIS ------------------------------------------
		acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_acsDetection_Y_lifetime", sep = "");
		legend <- c("ELRP","R");
		GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,14:15], legend);
		
		# PLOT IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_Degree_Y_lifetime", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing IO-degree", acsImageName, "", "IO-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,16:17], legend);
		
		# PLOT WEIGHTED IN and OUT-DEGREE -----------------------------------------------
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_IO_WeightDegree_Y_lifetime", sep = "");
		legend <- c("IN-DEGREE", "OUT-DEGREE");
		GraphTimeSeriesWithLegend("  Graphing in-degree", acsImageName, "", "IO-W-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,18:19], legend);
	
		# PLOT SCC -----------------------------------------------
		acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,20]);
		acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,21]);
		acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,22]);
		acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_N_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,23]);
		acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_N_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,24]);
		acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_N_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,25]);
		acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_N_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of substrates in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,26]);
		acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_N_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of substrates in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,27]);
		acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_N_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of substrates in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,28]);
		acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_Ntot_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,29]);
		acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_Ntot_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,30]);
		acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_Ntot_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,31]);	
		
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_MMMM_SCCs", sep = "");
		legend <- c("Max", "Min", "Mean", "Median");
		GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,32:35], legend);
		
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_MMMM_SCCs_NLT", sep = "");
		legend <- c("Max", "Min", "Mean", "Median");
		GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,36:39], legend);
		
		acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_MMMM_SCCs_LT", sep = "");
		legend <- c("Max", "Min", "Mean", "Median");
		GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,40:43], legend);	
		
		# MOLECULES IN SCCs
		acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,44]);
		acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,45]);
		acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,46]);
		acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,47]);
		acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC_NLT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,48]);
		acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC_LT", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,49]);	
		
		# MOLECULES IN SCCs and not present in the ACS
		acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,50]);
		acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC_NLT_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,51]);
		acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_mols_SCC_LT_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,52]);
		acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,53]);
		acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC_NLT_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,54]);
		acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_SUB_perc_mols_SCC_LT_noinflux", sep = "");
		GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,55]);			
		
	} # end if(nrow(tmpFinalNetAnalysis) > 1)
}

plotSingleSimNetAnalysisGraphLITE <- function(tmpFinalNetAnalysis, tmpStrZeroGen, tmp_gen, tmpStrZeroSim, tmp_sim)
{
	# PLOT EIGEN ANALYSIS ------------------------------------------
	if(nrow(tmpFinalNetAnalysis) > 1)
	{
	
	# ACTUAL REACTIONS
	# PLOT EIGEN ANALYSIS ------------------------------------------
	acsImageName <- paste("13_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_acsDetection_Y_lifetime", sep = "");
	legend <- c("ELRP","R");
	GraphTimeSeriesWithLegend("  Graphing ACS detecting results", acsImageName, "", "R and ELRP", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,2:3], legend);
	
	# PLOT IN and OUT-DEGREE -----------------------------------------------
	acsImageName <- paste("14_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_INDegree_Y_lifetime", sep = "");
	legend <- c("IN-DEGREE");
	GraphTimeSeriesL("  Graphing IN-degree", acsImageName, "", "IN-degree", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,4]);
	
	# PLOT SCC -----------------------------------------------
	acsImageName <- paste("16_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,5]);		
	acsImageName <- paste("17_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_N_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "Species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,6]);
	acsImageName <- paste("18_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_N_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of catalysts in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,7]);
	acsImageName <- paste("19_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_Ntot_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,8]);
	
	acsImageName <- paste("15_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_MMMM_SCCs_LT", sep = "");
	legend <- c("Max", "Min", "Mean", "Median");
	GraphTimeSeriesWithLegend("  Graphing SCC MMMM", acsImageName, "", "# Of species in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,9:12], legend);	
	
	# MOLECULES IN SCCs
	acsImageName <- paste("20_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,13]);
	acsImageName <- paste("21_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_LT", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Molecules in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,14]);		
	
	# MOLECULES IN SCCs and not belonging to tha influx
	acsImageName <- paste("22_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_mols_SCC_LT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,15]);
	acsImageName <- paste("23_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_CAT_perc_mols_SCC_LT_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "% of Mols (NO INFLUX) in SCCs", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,16]);
	
	# Number of molecules not belonging to the INFLUX
	acsImageName <- paste("24_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_molecules_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of not supplied molecules", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,17]);
	acsImageName <- paste("25_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_species_noinflux", sep = "");
	GraphTimeSeriesL("  Graphing SCC", acsImageName, "", "# of not supplied species", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,18]);	
	
	acsImageName <- paste("26_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_from", sep = "");
	legend <- c("From ACS", "ACS product", "From chains", "from Influx");
	GraphTimeSeriesWithLegend("  Graphing production from", acsImageName, "", "# of species catalysed ", tmpFinalNetAnalysis[,1], tmpFinalNetAnalysis[,19:22], legend);	
	} # end if(nrow(tmpFinalNetAnalysis) > 1)
	
	# reactions histograms tmpRctTypes
	#histImageName <- paste("26_", tmpStrZeroGen, toString(tmp_gen), "_", tmpStrZeroSim, toString(tmp_sim), "_reactionsTypeFrequence", sep = "");
	#makeHistogram(histImageName, tmpRctTypes, 2, c("Condensation","Cleavage"));
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

makeHistogram <- function(tmpImageName, dataToHist, tmpNclass, labs)
{
	DrawThisGraph(tmpImageName);
	par(mar=c(5.1,5.1,2,2));
	hist(dataToHist, tmpNclass, labels=labs, main="", xlab="Reaction Type (< 0.5 Condensation, > 0.5 Cleavage)", cex.lab = 2, cex.axis = 2, family="Times");
	rm(dataToHist);
		dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\

makeDefaultHistogram <- function(tmpImageName, dataToHist)
{
	DrawThisGraph(tmpImageName);
	par(mar=c(5.1,5.1,2,2));
	hist(dataToHist, main="", xlab="Age", ylab="Number of species", cex.lab = 2, cex.axis = 2, family="Times");
	rm(dataToHist);
	dev.off();
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# Function to plot species on the X axis and something on log scale on Y-axis

GraphLogYplot <- function(tmpName, tmpMain, tmpYlab, tmpValues)
{
	DrawThisGraph(tmpName);
	tmpValues = tmpValues[tmpValues > 0];
	if(length(tmpValues) > 0)
	{
		plot(tmpValues, main = tmpMain, xlab = expression("Species"), ylab = tmpYlab, log="y", type="b", cex=0.5, 
			font = 5, cex.lab = 2, cex.axis = 2, lwd = 3, frame.plot = FALSE, family="Times");
		grid(lwd=2);
		dev.off();
		rm(tmpValues);
	}
}

# ------------------------------------------------------------------------------------------------------------------/
# ------------------------------------------------------------------------------------------------------------------\
# Compute total number of possibile reactions
totNumberOfReactions <- function(A, M)
{
	tot = 0;
	cleavage <- 0;
	species <- A;
	for(i in 2 : M)
	{
			cleavage <- cleavage + ((i-1)*(A^i));
			species <- species + (A^i);
	}	
	condensation <- species^2;
	print(species);
	tot <- cleavage + condensation;
	return(tot);
}
