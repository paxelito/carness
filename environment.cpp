/**  \class environment
 * \author Alessandro Filisetti
 * \version 2.4
 * \date 2010-06-10
 */
#include "environment.h"

/* ************
|
|	CONSTRUCTORS
|
****************/

/**
 Test environment costructor
 @version 2.4
 @date 2010-06-27
 @param tmpRndDoubleGen randomGenerator reference
*/
environment::environment()
{
	//TR onlyEnvironmentCreation = 0;
	nGEN = 1;
	nSIM = 1;
	nReactions = 100;
	//TR initialPopulationNumber = 30;
	complexFormationSymmetry = 0;
	timeStructuresSavingInterval = 1;
        fileTimesSaveInterval = 0;
	//TR initialMaxLength = 4;
	reactionProbability = 0.01;
	cleavageProbability = 0.5;
	cleavage_KineticConstant = 1.5;
	complex_KineticConstant = 0.01;
	condensation_KineticConstant = 0.5;
	complexDeg_KineticConstant = 0.001;
	moleculeDecay_KineticConstant = 0.1;
	solubility_threshold = 0;
	diffusion_contribute = 1;
	//TR influx = 1;
	influx_rate = 0.5;
	alphabet = "AB";
	randomSeed = 100;
	debugLevel = 1;
	timeSinceTheLastInFlux = 0;
	actualTime = 0;
	energy = 0;
	ratioSpeciesEnergizable = 0;
	// --------------------------
	decimalMoleculesToLoad = 0;
	decimalMoleculesToUNLOAD = 0;
	decimalMoleculesToEfflux = 0;
	numberOfSpecies = 0;
	numberOfNewSpecies = 0;
	numberOfMolecules = 0;
	numberOfNewMolecules = 0;
	numberOfCpx = 0;
	numberOfCpxMols = 0;
	gillespieTotalScore = 0;
	maxLOut = 0;
    internalTimesStoredCounter = 0;
    nHours = 5;
    nAttempts = 5;
    Currentattempts = 0;
    revRctRatio = 1000;
}

/**
 Environment Constructor
 @version 1.0
 @param tmpInitialPath
 */
environment::environment(QString tmpInitialPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::environment start" << endl;

	// CONFIGURATION FILE PATH CREATION
	QString confFilePath = tmpInitialPath + "acsm2s.conf";
	QTextStream prompt(stdout);
	if(debugLevel >= RUNNING_VERSION){prompt << "|- Configuration File path --> " << confFilePath << endl;}
	//OPEN FILE
	QFile fid(confFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("environment", "ERROR: Configuration file has not been found, please check path!!!");
//	   exit(EXIT_FAILURE);
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("=");
			// SYSTEM PARAMETERS
            if(strLineSpletted[0] == "nGEN") nGEN = strLineSpletted[1].toInt();
			if(strLineSpletted[0] == "nSIM") nSIM = strLineSpletted[1].toInt();
            if(strLineSpletted[0] == "nSeconds") nSeconds = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "nReactions") nReactions = strLineSpletted[1].toInt();
			if(strLineSpletted[0] == "randomSeed") randomSeed = strLineSpletted[1].toInt();
            if(strLineSpletted[0] == "debugLevel") debugLevel = strLineSpletted[1].toInt();
			if(strLineSpletted[0] == "timeStructuresSavingInterval") timeStructuresSavingInterval = strLineSpletted[1].toDouble();
            if(strLineSpletted[0] == "fileTimesSaveInterval") fileTimesSaveInterval = strLineSpletted[1].toDouble();
            if(strLineSpletted[0] == "nHours") nHours = strLineSpletted[1].toInt();
            if(strLineSpletted[0] == "nAttempts") nAttempts = strLineSpletted[1].toInt();
			
			// ENVIRONMENTAL PARAMETERS
			if(strLineSpletted[0] == "lastFiringDiskSpeciesID") lastFiringDiskSpeciesID = strLineSpletted[1].toInt(); // DA ELIMINARE CON ATTENZIONE
            if(strLineSpletted[0] == "overallConcentration") overallConcentration = strLineSpletted[1].toDouble(); // DA ELIMINARE CON ATTENZIONE
			if(strLineSpletted[0] == "ECConcentration") ECConcentration = strLineSpletted[1].toDouble(); // DA TRASFORMARE NELLA VARIABILE INDICANTE LA QUANTITA DI CARRIER SEMPRE PRESENTI
			if(strLineSpletted[0] == "alphabet") alphabet = strLineSpletted[1].QString::toStdString();
			if(strLineSpletted[0] == "volume") volume = strLineSpletted[1].toDouble();
			
			// DYNAMIC PARAMETERS
			if(strLineSpletted[0] == "energy") energy = strLineSpletted[1].toInt(); // DA ELIMINARE CON ATTENZIONE, IL TUTTO VERRA' SOSTITUITO DALLA FUNZIONE BOOLEANA
			if(strLineSpletted[0] == "ratioSpeciesEnergizable") ratioSpeciesEnergizable = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "complexFormationSymmetry") complexFormationSymmetry = strLineSpletted[1].toInt();	
			if(strLineSpletted[0] == "nonCatalyticMaxLength") nonCatalyticMaxLength = strLineSpletted[1].toInt();	
			if(strLineSpletted[0] == "reactionProbability") reactionProbability = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "cleavageProbability") cleavageProbability = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "reverseReactions") reverseReactions = strLineSpletted[1].toInt();
            if(strLineSpletted[0] == "revRctRatio") revRctRatio = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "K_ass") K_ass = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "K_diss") K_diss = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "K_cpx") K_cpx = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "K_cpxDiss") K_cpxDiss = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "K_nrg") K_nrg = strLineSpletted[1].toDouble(); // DA ELIMINARE CON ATTENZIONE
			if(strLineSpletted[0] == "K_nrg_decay") K_nrg_decay = strLineSpletted[1].toDouble(); // DA ELIMINARE CON ATTENZIONE
			if(strLineSpletted[0] == "moleculeDecay_KineticConstant") moleculeDecay_KineticConstant = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "maxLOut") maxLOut = strLineSpletted[1].toInt();
			if(strLineSpletted[0] == "solubility_threshold") solubility_threshold = strLineSpletted[1].toInt();
			if(strLineSpletted[0] == "diffusion_contribute") diffusion_contribute = strLineSpletted[1].toDouble();
			if(strLineSpletted[0] == "influx_rate") influx_rate = strLineSpletted[1].toDouble();
						
		}
	}

        if(nSeconds < timeStructuresSavingInterval)
            ExitWithError("environment::environment","No Structures will be saved during the simulation");

        if(nSeconds < fileTimesSaveInterval)
            ExitWithError("environment::environment","No times file will be saved during the simulation");
	
	if(debugLevel >= RUNNING_VERSION)
		showGlobalParameter();
	//IF RANDOM SEED IS 0 IT HAS TO BE CREATED RANDOMLY 
	if(randomSeed == 0)
	{
		//randomSeed = getIntRandom(1, RANDOMRANGE, tmpRndDoubleGen);
		srand(time(0));
		randomSeed = rand();
		if(debugLevel >= RUNNING_VERSION)
			cout << "|- New random seed -> " << randomSeed << endl;
        }
	
	if(energy == 1) 
            nrgBoolFlag = ENERGYBASED;
        else
            nrgBoolFlag = ENERGYFREE;
	
	// INITIALIZE THE REFILL TIMER
	timeSinceTheLastInFlux = 0;
	// INITIALIZE TIME TO 0
	actualTime = 0;
	
	numberOfSpecies = 0;
	numberOfNewSpecies = 0;
	numberOfMolecules = 0;
	numberOfNewMolecules = 0;
	numberOfCpx = 0;
	numberOfCpxMols = 0;
	decimalMoleculesToEfflux = 0;
	decimalMoleculesToLoad = 0;
	decimalMoleculesToUNLOAD = 0;
	gillespieTotalScore = 0;
        gillespieNewSpeciesScore = 0;
        ratioBetweenNewGillTotGill = 0;
        internalTimesStoredCounter = 0;
        // TO BE PARAMETRIZED
        Currentattempts = 0;
	resetReactionsCounter();
		
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::environment end" << endl;

}

/* ************************
 |
 |	CREATION FUNCTIONS
 |
 *************************/

/**
 Initial molecule population creation. If the number of species stored in the configuration file is grater than the possible 
 number of species according to the alphabet and maximum length all species up to the MAX length will be created
 @version 1.0
 @param MTRand& tmpRndDoubleGen
 */
//TR void environment::createInitialMoleculesPopulation(MTRand& tmpRndDoubleGen)
//{
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulation start" << endl;
//
//	unsigned int alphabetLength = alphabet.length();
//	totalPossibleNumberOfSpecies = 0;
//	//TOTAL NUMBER OF POSSIBLE SPECIES COMPUTATION
//	int si; //Signed i
//	for(unsigned int i = 1; i <= initialMaxLength; ++i)
//	{
//		si = i;
//		totalPossibleNumberOfSpecies += pow(acs_double(alphabetLength),si);
//	}
//	//PROBABILITY LENGTH SPECIES COMPUTATION
//	const int LENGTHS = initialMaxLength;
//	acs_double proportionalInitialLengthProbability[LENGTHS];
//	for(unsigned int i = 0; i < initialMaxLength; ++i)
//	{
//		si=i;
//		if(i == 0)
//			proportionalInitialLengthProbability[i] = pow(acs_double(alphabetLength),si+1) / totalPossibleNumberOfSpecies;
//		else
//			proportionalInitialLengthProbability[i] = proportionalInitialLengthProbability[i-1] + (pow(acs_double(alphabetLength),si+1) / totalPossibleNumberOfSpecies);	
//		
//	}
//	
//	
//	//acs_int initialAmount;						// initial species amount
//	acs_double initialConcentration;			// initial concentration
//	acs_int newSpeciesLenght;					// length of the new molecule
//	acs_int monomerID;							// monomer identificator during cycles
//	acs_longInt speciesID;						// species identificator during cycles
//	acs_int fixedSpeciesID;						// fixed species identificator during the creation of monomers species
//	acs_int speciesMonomerPos;					// identificator or the monomer position inside the species during the single species creation
//	string newSpeciesSequence;					// temp variable containing the new species sequence creation
//	acs_double tmpDiffusionContribute;			// Diffusion renforcmente contribute. This value is proportional to the length of the species	
//	acs_int tmpSolubility;		// Precipitation contribute. This value is proportional to the length of the the species
//	
//	// MOLECULES CREATION
//		// IN ANY CASE MONOMERS ARE CREATED AS SPECIES
//	for(fixedSpeciesID = 0; fixedSpeciesID < alphabetLength; fixedSpeciesID++)
//	{
//		newSpeciesSequence = alphabet.substr(fixedSpeciesID, 1);
//		initialConcentration = createInitialConcentration(alphabetLength, 1);
//		// PRECIPITATION AND DIFFUSION CONTRIBUTE COMPUTATION
//		tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, 1);
//                tmpSolubility = setSolubility(1, tmpRndDoubleGen);
//		allSpecies.push_back(species(fixedSpeciesID, newSpeciesSequence, initialConcentration, tmpDiffusionContribute, tmpSolubility, 0, 0, 0, volume, K_nrg));
//                incNumberOfSpecies(); // incSpeciesProcedure(fixedSpeciesID) cannot be use due to the initialConcentration != 1 molecule
//		numberOfMolecules += allSpecies.at(fixedSpeciesID).getAmount();
//	}
//	
//	// ALL THE OTHERS MOLECULES WILL BE CREATED
//		// IF THE NUMBER OF INITIAL SPECIES IS LESS THAN THE NUMBER OF POSSIBILE SPECIES SPECIES AND SPECIES LENGTH WILL BE CREATED RANDOMLY
//		// OTHERWISE ALL SPECIES ACCORDING TO ALPHABET AND MAXIMUM LENGHT WILL BE CREATED
//	if(debugLevel >= RUNNING_VERSION){cout << "|- TOTAL CONCEIVABLE NUMBER OF SPECIES: " << totalPossibleNumberOfSpecies << endl;}
//	
//	if(initialPopulationNumber < totalPossibleNumberOfSpecies)
//	{
//		if(debugLevel >= RUNNING_VERSION){cout << "|- The system is going to create " << initialPopulationNumber << " species" << endl;}
//		
//		bool flagEqualSeqBetweenTwoSpecies;	// flag variable that check whether the sequence is already present
//		bool flagSpeciesStored;				// boolean variable necessary to stop while iteration
//		const long int ENDEAVOURS = 100;			// Max number of temptative to perform before to compute the next molecule if the molecule is already present
//		int endeavourCounter;				// Endeavours counter
//		
//		acs_longInt realSpeciesID = fixedSpeciesID; //THIS COUNTER IS CREATED IN RELATION TO THE POSSIBILITY TO HAVE HOLE IN NUMERATION DUE TO 
//													//THE CREATION OF ALREADY PRESENT SPECIES
//		for(speciesID = fixedSpeciesID; speciesID < initialPopulationNumber; speciesID++)
//		{
//			if(debugLevel >= SMALL_DEBUG)
//				cout << "Species Number " << speciesID << endl;
//			flagSpeciesStored = false;
//			endeavourCounter = 1;
//			flagEqualSeqBetweenTwoSpecies = true;
//			while(flagSpeciesStored == false && endeavourCounter <= ENDEAVOURS)
//			{
//				//SELECT RANDOMLY ACCORDING TO WEIGHT PROBABILITY THE LENGTH OF THE NEW MOLECULE
//				//The value of the function is incremented because the function returns the position of the weight vector
//				newSpeciesLenght = returnSelectionIdFromAWeightProbVector(proportionalInitialLengthProbability, tmpRndDoubleGen) + 1;
//				//CREATE RANDOM MOLECULE SEQUENCE
//				monomerID = getIntRandom(0, alphabetLength-1, tmpRndDoubleGen);
//				newSpeciesSequence = alphabet.substr(monomerID,1);
//				if (newSpeciesLenght > 1)
//				{
//					for(speciesMonomerPos = 2; speciesMonomerPos <= newSpeciesLenght; speciesMonomerPos++)
//					{
//						//Create sequence
//						monomerID = getIntRandom(0, alphabetLength-1, tmpRndDoubleGen);
//						newSpeciesSequence += alphabet.substr(monomerID, 1);
//					}
//				}
//				//CHECK WHETHER THE SPECIES IS ALREADY PRESENT
//				for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)	
//				{
//					if(allSpecies.at(i).getSequence() == newSpeciesSequence)
//					{
//						flagEqualSeqBetweenTwoSpecies = false;
//						if(debugLevel >= 3)
//							cout << endeavourCounter << " " << i << " " << allSpecies.at(i).getSequence() << " " << newSpeciesSequence << endl;
//						endeavourCounter++;
//						break;
//					}else{
//						flagEqualSeqBetweenTwoSpecies = true; //Otherwise the system searching for the equal species until ENDEAVOURS will be reached
//					}
//				}		
//				//CREATE NEW MOLECULE OBJECT AND STORE IT INTO THE ENVIRONMENT SPECIES VECTOR
//				if(flagEqualSeqBetweenTwoSpecies == true)
//				{
//					// The initial amount is inversaly proportional to the length
//					initialConcentration = createInitialConcentration(alphabetLength, newSpeciesLenght);					
//					// PRECIPITATION AND DIFFUSION CONTRIBUTE COMPUTATION
//					tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, newSpeciesLenght);
//                                        tmpSolubility = setSolubility(newSpeciesLenght, tmpRndDoubleGen);
//					allSpecies.push_back(species(realSpeciesID, newSpeciesSequence, initialConcentration, tmpDiffusionContribute, tmpSolubility, 0, 0, 0, volume, K_nrg));
//					flagSpeciesStored = true;
//                                        if(initialConcentration > 0)
//                                            numberOfSpecies++;
//					numberOfMolecules += allSpecies.at(realSpeciesID).getAmount();
//					realSpeciesID++;
//				}
//			}
//		}
//		
//		if(debugLevel >= RUNNING_VERSION){cout << "\t|-" << (acs_longInt)allSpecies.size() << " SPECIES HAS BEEN CREATED" << endl;}
//		
//	}else{
//		// ALL POSSIBILE SPECIES CREATION
//		if(debugLevel == RUNNING_VERSION){ cout << "|- ALL POSSIBILE SPECIES CREATION (initial number of species has been set greater than the conceivable number)" << endl;}
//		
//		//initialize temporary Vector to store species population
//		vector<species> tmpAllSpecies;
//		// UPdate species ID considering monomers
//		speciesID = fixedSpeciesID;
//		// Declare boolean remove flag variable and removedSpeciesLengths iterator
//		int removedSpeciesLengths;
//		for(unsigned int tmpSpeciesLength = 2; tmpSpeciesLength <= initialMaxLength; tmpSpeciesLength++)
//		{ //For each possibile initial species length
//			//CREATE A TEMPORARY COPY OF THE SPECIES VECTOR
//			tmpAllSpecies = allSpecies;
//			//REMOVE ALL NOT NECESSARY (THE ONES WITH LENGTH < tmpSpeciesLength - 1) SPECIES FROM THE TEMPORARY VECTOR
//			removedSpeciesLengths = 1;
//			if (tmpSpeciesLength > 1)
//			{
//				while (tmpAllSpecies.at(0).getSequence().length() < (tmpSpeciesLength - 1))
//				{
//					    tmpAllSpecies.removeFirst();
//				}
//			}
//			
//			for(unsigned int tmpAlphabetPosition = 0; tmpAlphabetPosition < alphabetLength; tmpAlphabetPosition++)
//			{ //for each possibile monomer
//				if(debugLevel >= HIGH_DEBUG){cout << "\t\t\t|- Monomer to add -> " << alphabet[tmpAlphabetPosition] << endl;}
//				
//				// TO CRATE ALL POSSIBILE SPECIES UP TO LENGTH M RECURSIVELY MONOMERS WILL BE ADDED AT THE END OF THE PRESENT SPECIES
//				for(acs_longInt i = 0; i < (acs_longInt)tmpAllSpecies.size(); i++)
//				{
//					newSpeciesSequence = tmpAllSpecies.at(i).getSequence() + alphabet[tmpAlphabetPosition];
//					if(debugLevel >= HIGH_DEBUG){cout << "\t\t\t\t" << tmpAllSpecies.at(i).getSequence() << 
//														" + " << alphabet[tmpAlphabetPosition] << " = " << 
//														newSpeciesSequence << endl;}
//					
//					// The initial amount is inversaly proportional to the length
//					newSpeciesLenght = newSpeciesSequence.length();
//					initialConcentration = createInitialConcentration(alphabetLength, newSpeciesLenght);	
//					// PRECIPITATION AND DIFFUSION CONTRIBUTE COMPUTATION
//					tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, newSpeciesLenght);
//                                        tmpSolubility = setSolubility(newSpeciesLenght, tmpRndDoubleGen);
//					allSpecies.push_back(species(speciesID, newSpeciesSequence, initialConcentration, tmpDiffusionContribute, 
//												 tmpSolubility, 0, 0, 0, volume, K_nrg));
//                                        if(initialConcentration > 0)
//                                            numberOfSpecies++;
//					numberOfMolecules += allSpecies.at(speciesID).getAmount();
//					speciesID++; //update species ID
//				}				
//			}
//		}
//	}
//	
//	// FIRING DISK STORING, INFLUX CREATION AND PROBABILITY VECTOR FOR A NUTRIENT TO BE SELECTED IS CREATED
//	firingDisk = allSpecies;
//	this->getNutrientsFromTheFiringDisk();
//	if(debugLevel >= SMALL_DEBUG){printNutrientsAndProbability();}
//	if((initialMaxLength > influx) & (influx > 0))
//	{
//		this->nutrientsAmountsFixing();
//	}
//	
//	if(debugLevel >= SMALL_DEBUG){printNutrientsAndProbability();}
//	
//	if(debugLevel >= RUNNING_VERSION){cout << "\t\t\t|- DONE!!! " << endl;}
//	
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulation end" << endl;
//
//}// eof createInitialMoleculesPopulation

/**
 initial layer initialization
 @version 1.0
 @param MTRand& tmpRndDoubleGen
*/
//void environment::createReactionsLayer(MTRand& tmpRndDoubleGen)
//{
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createReactionsLayer start" << endl;
//
//	if(debugLevel >= RUNNING_VERSION){cout << "|- Reactions Layer creation..." << endl;}
//	
//	// COPY ALL THE SPECIES IN A TEMPORARY VECTOR
//	vector<acs_longInt> allPresentSpecies;
//
//	for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
//	{
//			allPresentSpecies.push_back(i);
//	}
//	
//	// COMPUTE TOTAL NUMBER OF CONCEIVABLE REACTIONS
//	acs_longInt totalNumberOfConcevableReactions = 0;
//	if((acs_longInt)allPresentSpecies.size() > 0)
//	{
//		for(acs_longInt sID = 0; sID < (acs_longInt)allPresentSpecies.size(); sID++)
//		{
//			totalNumberOfConcevableReactions += allSpecies.at(allPresentSpecies.at(sID)).getSequenceLength() - 1;
//		}	
//	
//		totalNumberOfConcevableReactions += pow((double)allPresentSpecies.size(), 2.0);
//	}
//	
//	if(debugLevel >= SMALL_DEBUG){printAllSpeciesIdAndSequence();}
//	
//	if(debugLevel >= RUNNING_VERSION){cout << "|- Total number of conceivable reactions: " << totalNumberOfConcevableReactions << endl;}
//	
//	//FOR EACH SPECIES
//	acs_int reactionsForThisSpecies;
//	for(acs_longInt sID = 0; sID < (acs_longInt)allPresentSpecies.size(); sID++)
//	{
//		
//		// Only species longer than nonCatalyticMaxLength can catalyse reactions!!!
//		if(allSpecies.at(allPresentSpecies.at(sID)).getSequenceLength() > nonCatalyticMaxLength)
//		{
//			reactionsForThisSpecies = computeSngSpeciesRctsNumber(totalNumberOfConcevableReactions, tmpRndDoubleGen);
//		}else{
//			reactionsForThisSpecies = 0;
//		}
//		
//		// CREATE REACTIONS FOR THIS SPECIFIC SPECIES
//		if(debugLevel >= RUNNING_VERSION){cout << "\t|- Creating reactions for species : " << sID << "[" << allSpecies.at(sID).getSequence() << "]" << endl;}
//		if(reactionsForThisSpecies > 0)
//		{
//			if(!createReactionsForThisSpecies(sID, reactionsForThisSpecies, tmpRndDoubleGen, allPresentSpecies, NEWREACTIONS))
//			{	
//				ExitWithError("createReactionsForThisSpecies", "	|- !*!*!*! Problem with the reactions creation");
//			}else{
//				allSpecies[sID].setEvaluated(); // IF the reactions have been created the molecules evalutation is setting on 1
//			}
//		}else{
//			allSpecies[sID].setEvaluated(); // IF the reactions have been created the molecules evalutation is setting on 1		
//		}
//	}
//	if(debugLevel >= RUNNING_VERSION){cout << "\t\t\t|- DONE!!! " << endl;}
//
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createReactionsLayer end" << endl;
//
//}//eof

/**
 Compute number of reaction catalysd by a catalyst according to the total number of reactions and reactions probabilities
 @version 1.0
 @param acs_int tmpTotalNumberOfReactions Total number of conceivable reactions
 @param acs_double tmpRctsProb reaction probability
 */
acs_int environment::computeSngSpeciesRctsNumber(acs_longInt tmpTotalNumberOfReactions, MTRand& tmpRndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::computeSngSpeciesRctsNumber start" << endl;

	acs_int temp_tmpReactionsForThisSpecies; 
	acs_int tmpReactionsForThisSpecies; 
	
	temp_tmpReactionsForThisSpecies = tmpTotalNumberOfReactions * reactionProbability;
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "!MESSAGE :: Reaction for this species BEFORE stochastic fluctuation: " << temp_tmpReactionsForThisSpecies << endl;
	
	if(temp_tmpReactionsForThisSpecies <= 100)
	{
		//tmpReactionsForThisSpecies = random_poisson((acs_double)temp_tmpReactionsForThisSpecies	, tmpRndDoubleGen);
		tmpReactionsForThisSpecies = random_binomial(tmpTotalNumberOfReactions, reactionProbability, tmpRndDoubleGen);
	}else {
		tmpReactionsForThisSpecies = temp_tmpReactionsForThisSpecies;
	}
		
	if(tmpReactionsForThisSpecies <= 0)
		tmpReactionsForThisSpecies = 0;
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "!MESSAGE :: Reaction for this species AFTER stochastic fluctuation: " << tmpReactionsForThisSpecies << endl;
		
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::computeSngSpeciesRctsNumber end" << endl;

	return tmpReactionsForThisSpecies;
	

}//eof


/**
 Creation of all the reactions related to one specific species
 @version 1.1
 @date 2011/07/07
 @param acs_longInt tmpsID species vector ID
 @param acs_int tmpReactionsForThisSpecies number of reactions to create for this species
 @param MTRand& tmp_RndDoubleGen random number generator
 @param vector<acs_longInt>& tmpIDOfCandidateSpecies ID of the species avalaible for the reaction
 @param acs_int tmpRctCreationType NEWREACTION or UPGRADEREACTIONS
 */
bool environment::createReactionsForThisSpecies(acs_longInt tmpsID, acs_int tmpReactionsForThisSpecies, MTRand& tmp_RndDoubleGen, 
                                                vector<acs_longInt>& tmpIDOfCandidateSpecies, acs_int tmpRctCreationType)
{	
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::createReactionsForThisSpecies start" << endl;

    acs_int reactionType;
    acs_longInt ids_I = 0;
    acs_longInt ids_II = 0;
    acs_longInt ids_III = 0;
    acs_double tmpK_ass; // Declare three kinetic variable to initialize according to the presence of not of the reverse reations
    acs_double tmpK_diss;
    acs_double tmpK_cpx;
    acs_longInt id_reaction;
    acs_int tempEnergyRctType = ESOERGONIC;
    acs_int nrgRctBoolFncID;
    acs_int tmpEnergizable = NOTENERGIZABLE;
    bool validReactionFlag = false; // this flag is true if all possible steps of the reaction creation have been satisfied
    bool toProceed = true; // Variable to check whether it is possibile proceeding with the creation reaction or not
    acs_int rctCreationAttemptCounter = 0; // Number of tentative to create a reaction
	
    // CREATE A TEMPORARY VECTOR CONTAINING ALL USEFUL SPECIES
    vector<acs_longInt> speciesAvailableForReactions;
    vector<acs_longInt> speciesAvailableForCleavageReactions;
	
    for(acs_longInt i = 0; i < (acs_longInt)tmpIDOfCandidateSpecies.size(); i++)
    {
       try{
            if(allSpecies.at(tmpIDOfCandidateSpecies.at(i)).getComplexCutPnt() == 0)
            {
                    if(tmpRctCreationType == NEWREACTIONS) // If this is a reactions for a new species
                    {
                            speciesAvailableForReactions.push_back(tmpIDOfCandidateSpecies.at(i));
                    }else{
                            // OLD SPECIES REACTIONS UPDATING PROCESS CAN INVOLVE SPECIES NEVER CONSIDERED BEFORE BY THIS SPECIES
                            if((tmpIDOfCandidateSpecies.at(i) > ((acs_int)firingDisk.size() - 1)) && (tmpIDOfCandidateSpecies.at(i) > tmpsID))
                                    speciesAvailableForReactions.push_back(tmpIDOfCandidateSpecies.at(i));
                    }
            }else{
                    ExitWithError("createReactionsForThisSpecies", "A Complex Cannot be envolved in a reaction as product or substrate");
            }
        }catch(exception&e)
        {
            cout << "createReactionsForThisSpecies allSpecies.at(tmpIDOfCandidateSpecies.at(i)).getComplexCutPnt()" << endl;
            cout << "Vectorsize " << tmpIDOfCandidateSpecies.size()<<" - position " << i << endl;
            cerr << "exceptioncaught:" << e.what() << endl;
            ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
        }

    }

    if((acs_longInt)speciesAvailableForReactions.size() > 0) // If at least one species may be interact with this species
    {
    // COPY AVALAIBLE SPECIES VECTOR INTO AVALAIBLE FOR CLEAVAGE
        speciesAvailableForCleavageReactions = speciesAvailableForReactions;

        if(debugLevel >= SMALL_DEBUG)
        {
                cout << "\t\t|- " << allSpecies.at(tmpsID).getID() + 1 << "th Species (ID " << allSpecies.at(tmpsID).getID() << ") - " <<
                (acs_longInt)tmpIDOfCandidateSpecies.size() << " Candidate substrates - Number of Reactions: " << tmpReactionsForThisSpecies <<
                " - Total Reactions: " << (acs_longInt)allReactions.size() <<  endl;
        }

        if(debugLevel >= SMALL_DEBUG)
        {
                cout << "\t ----------------------------------------------" << endl;
                cout << "\t ----------------------------------------------" << endl;
        }
        for(acs_int IDrct = 0; IDrct < tmpReactionsForThisSpecies; IDrct++) // FOR EACH REACTION
        {
            if(debugLevel >= SMALL_DEBUG)
            {
                    cout << "\t ----------------------------------------------" << endl;
                    cout << "\t|- Species " << tmpsID << " - Reaction Number " << IDrct <<
                    " of " << tmpReactionsForThisSpecies << endl;
            }
            rctCreationAttemptCounter = 0;
            validReactionFlag = false;
            while(!validReactionFlag && (rctCreationAttemptCounter < 200))
            {
                    tempEnergyRctType = ESOERGONIC;
                    validReactionFlag = false; //RESET VALIDATION FLAG IN ORDER TO NOT CREATE WRONG REACTIONS
                    toProceed = true;

                    if(rctCreationAttemptCounter == 0)
                    {
                            // If this is the first temptative to create a reaction reaction direction is randomly choosen
                            reactionType = selectWhetherCleavageOrCond(tmp_RndDoubleGen);
                    }

                    //------------------------------ CLEAVAGE REACTION -------------------------------------------------|

                    if(reactionType == CLEAVAGE)
                    {
                       acs_longInt substratePosID;
                       if((acs_longInt)speciesAvailableForCleavageReactions.size() > 0) //IF THERE ARE SPECIES AVALAIBLE for CLEAVAGE
                        {
                            // Select species to hydrolize
                           substratePosID = returnUniformSelection_LONG_IdFromVector(speciesAvailableForCleavageReactions, tmp_RndDoubleGen);
                           acs_int substrateLength;
                           try{
                               substrateLength = allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getSequence().length();
                           }catch(exception&e){
                               cout << "createReactionsForThisSpecies allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID))…" << endl;
                               cout << "Vectorsize "<<allSpecies.size()<<" - position "<<speciesAvailableForCleavageReactions.at(substratePosID)<<endl;
                               cerr << "exceptioncaught:"<<e.what()<<endl;
                               ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                           }

                           string product_I;
                           string product_II;
                           if(substrateLength > 1) //IF THE SUBSTRATE IS LONGER THAN 1
                           {
                               if(debugLevel >= SMALL_DEBUG)
                               {
                                    //cout << "\t\t -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;
                                    //cout << "\t\t|- Reaction: " << IDrct << " CLEAVAGE REACTION:" << endl;
                                    //cout << "\t\t\t|- SUBSTRATE pos: " << substratePosID << " | SUBSTRATE ID: " <<
                                    //allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getID() << " | SEQUENCE: " <<
                                    //allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getSequence() << endl;
                                    //cout << "\t\t\t|- Total number of avalaible cleavage: " << (acs_longInt)speciesAvailableForCleavageReactions.size() << endl;
                               }
                                //SELECT CUTTING POINT AND CREATE THE TWO PRODUCTS
                                acs_int cuttingPoint = getIntRandom(1, substrateLength - 1, tmp_RndDoubleGen);

                                try{
                                    product_I = allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getSequence().substr(0, cuttingPoint);
                                    product_II = allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getSequence().substr(cuttingPoint, allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID)).getSequence().length() - cuttingPoint);
                                }catch(exception&e){
                                    cout << "createReactionsForThisSpecies allSpecies.at(speciesAvailableForCleavageReactions.at(substratePosID))…" << endl;
                                    cout << "Vectorsize "<<allSpecies.size()<<" - position "<<speciesAvailableForCleavageReactions.at(substratePosID)<<endl;
                                    cerr << "exceptioncaught in if(substrateLength > 1):"<<e.what()<<endl;
                                    ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                                }

                                if(debugLevel >= MEDIUM_DEBUG)
                                {
                                    cout << "\t\t\t\t|- Product 1: " << product_I << endl;
                                    cout << "\t\t\t\t|- Product 2: " << product_II << endl;
                                }

                                // Try here is not necessary since it has been used 20 rows above
                                ids_I = speciesAvailableForCleavageReactions.at(substratePosID); //substrate vector allSpecies position

                                // CHECK WHETHER THE NEW PRODUCT IS ALREADY PRESENT AND IF IT ISN'T REACTION IS STORED. IF IT IS, ITS ID BECAME THE VALUE TO STORE INTO THE REACTIONS,
                                // OTHERWISE A NEW ID WILL BE CREATED
                                ids_II = returnPosSpeciesAlreadyPresent(product_I);
                                if(product_I != product_II) // IF PRODUCTS ARE DIFFERENT
                                {
                                    ids_III = returnPosSpeciesAlreadyPresent(product_II);
                                    // IF BOTH PRODUCTS ARE NEW THE ID OF HTE SECOND ONE IN INCREMENTED BY 1
                                    if(ids_II == ids_III)
                                            ids_III++;
                                }else{
                                    ids_III = ids_II;
                                }

                                // This code segment has been commented since the introduction of the external initializator.
                                // SELF REPLICATION IS AVOIDED INTO THE FIRING DISK, IF ONE OF THE PRODUCTS IS A CATALYST (IN THE FIRING DISK) THE REACTION IS NOT POSSIBLE
//                                  if(tmpsID <= ((acs_int)firingDisk.size() - 1))
//                                  {
//                                      if(tmpsID == ids_II) toProceed = false;
//					if(tmpsID == ids_III) toProceed = false;
//
//					// CHECK IF THE CANDIDATE PRODUCTS ALREADY CATALYSE THE CATALYST IN ORDER TO AVOID MUTUAL CATALYSIS
//					if(toProceed) toProceed = checkIfOnlyMutualCatalysis(tmpsID, ids_II);
//                                      if(toProceed && (ids_II != ids_III)) toProceed = checkIfOnlyMutualCatalysis(tmpsID, ids_III);
//                                  }

                                if(debugLevel >= MEDIUM_DEBUG)
                                {
                                        cout << "\t\t\t\t|- ID 1: " << ids_II << endl;
                                        cout << "\t\t\t\t|- ID 2: " << ids_III << endl;
                                }

                                // ONE SPECIES CAN NOT CATALYZE BOTH FORWARD AND BACKWARD REACTIONS
                                if(toProceed)
                                {
                                    if(!notInverseReactionAlreadyCatalyzed(CLEAVAGE, ids_I, ids_II))
                                    {
                                        validReactionFlag = false; // BACKWARD REACTION IS ALREADY CATALIZED!!!
                                        if(debugLevel == SMALL_DEBUG)
                                                cout << "\t\t\tFound COND reverse reaction - " << validReactionFlag <<  " -  tentativi - " << rctCreationAttemptCounter <<
                                                " - Numero " << IDrct << endl;
                                    }else{
                                      if(ids_II == (acs_longInt)allSpecies.size()) //IF THE POSITION RETURNED IS EQUAL TO THE SIZE OF vector ALLSPECIES, IT MEANS THAT THE SPECIES IS NOT PRESENT
                                        {
                                                if(tmp_RndDoubleGen() < ratioSpeciesEnergizable){tmpEnergizable=ENERGIZABLE;}else{tmpEnergizable=NOTENERGIZABLE;}
                                                allSpecies.push_back(species(ids_II, product_I, (acs_longInt)0, 0, 0, 0, 0, 0, volume, 0, tmpEnergizable, influx_rate, maxLOut));
                                        }
                                      if(ids_III == (acs_longInt)allSpecies.size()) //IF THE POSITION RETURNED IS EQUAL TO THE SIZE OF vector ALLSPECIES, IT MEANS THAT THE SPECIES IS NOT PRESENT
                                        {
                                                if(tmp_RndDoubleGen() < ratioSpeciesEnergizable){tmpEnergizable=ENERGIZABLE;}else{tmpEnergizable=NOTENERGIZABLE;}
                                                allSpecies.push_back(species(ids_III, product_II, (acs_longInt)0, 0, 0, 0, 0, 0, volume, 0, tmpEnergizable, influx_rate, maxLOut));
                                        }
                                        validReactionFlag = true;
                                    }
                                }else{
                                        validReactionFlag = false;
                                }
                            }
                            // REMOVE THIS SUBSTRATE FOR THE AVALAIBLE SUBSTRATE
                            // speciesAvailableForCleavageReactions.removeAt(substratePosID);
                            speciesAvailableForCleavageReactions.erase(speciesAvailableForCleavageReactions.begin()+substratePosID);
                        }

                    //------------------------------ CONDENSATION REACTION -------------------------------------------------|

                    }else{
                        acs_longInt substratePosID_I;
                        acs_longInt substratePosID_II;
                        string product;
                        if((acs_longInt)speciesAvailableForReactions.size() > 0) // IF THERE ARE SPECIES
                        {
                            substratePosID_I = returnUniformSelection_LONG_IdFromVector(speciesAvailableForReactions, tmp_RndDoubleGen);
                            substratePosID_II = returnUniformSelection_LONG_IdFromVector(speciesAvailableForReactions, tmp_RndDoubleGen);

                            if(debugLevel >= SMALL_DEBUG)
                            {
                                cout << "\t\t -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-" << endl;
                                cout << "\t\t|- Reaction: " << IDrct << " CONDENSATION REACTION:" << endl;
                                cout << "\t\t\t|- SUBSTRATE 1 ID: " << allSpecies.at(speciesAvailableForReactions.at(substratePosID_I)).getID()
                                         << " | SEQUENCE: " << allSpecies.at(speciesAvailableForReactions.at(substratePosID_I)).getSequence() << endl;
                                cout << "\t\t\t|- SUBSTRATE 2 ID: " << allSpecies.at(speciesAvailableForReactions.at(substratePosID_II)).getID()
                                         << " | SEQUENCE: " << allSpecies.at(speciesAvailableForReactions.at(substratePosID_II)).getSequence() << endl;
                            }

                            //PRODUCT CREATION
                            try{
                                product = allSpecies.at(speciesAvailableForReactions.at(substratePosID_I)).getSequence() +
                                                        allSpecies.at(speciesAvailableForReactions.at(substratePosID_II)).getSequence();
                            }catch(exception&e){
                                cout << "allSpecies.at(speciesAvailableForReactions.at(substratePosID_I)).getSequence() + allSpecies.at(speciesAvailableForReactions.at(substratePosID_II)).getSequence();" << endl;
                                cout << "Vectorsize "<<allSpecies.size()<<" - position "<<speciesAvailableForCleavageReactions.at(substratePosID_I)<<endl;
                                cerr << "exceptioncaught in if(substrateLength > 1):"<<e.what()<<endl;
                                ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                            }

                            if(debugLevel >= SMALL_DEBUG)
                                cout << "\t\t\t\t|- Product: " << product << endl;

                            ids_I = returnPosSpeciesAlreadyPresent(product);

                            if(tmpsID <= ((acs_int)firingDisk.size() - 1))
                            {
                                if(tmpsID == ids_I) toProceed = false;

                                // CHECK WHETHER THE CANDIDATE PRODUCT ALREADY CATALYSES THE CATALYST
//					if(toProceed) toProceed = checkIfOnlyMutualCatalysis(tmpsID, ids_I);
                            }

                            if(toProceed)
                            {
                                // ONE SPECIES CAN NOT CATALYZE BOTH ONE REACTION AND THE INVERTED ONE
                                try{
                                    ids_II = speciesAvailableForReactions.at(substratePosID_I);
                                }catch(exception&e){
                                    cout << "speciesAvailableForReactions.at(substratePosID_I)" << endl;
                                    cout << "Vectorsize "<<speciesAvailableForReactions.size()<<" - position "<<substratePosID_I<<endl;
                                    cerr << "ids_II = speciesAvailableForReactions.at(substratePosID_I);"<<e.what()<<endl;
                                    ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                                }

                                try{
                                    ids_III = speciesAvailableForReactions.at(substratePosID_II);
                                }catch(exception&e){
                                    cout << "speciesAvailableForReactions.at(substratePosID_II)" << endl;
                                    cout << "Vectorsize "<<speciesAvailableForReactions.size()<<" - position "<<substratePosID_II<<endl;
                                    cerr << "ids_II = speciesAvailableForReactions.at(substratePosID_II);"<<e.what()<<endl;
                                    ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                                }

                                if(!notInverseReactionAlreadyCatalyzed(CONDENSATION, ids_I, ids_II))
                                {
                                    validReactionFlag = false;
                                    if(debugLevel == SMALL_DEBUG)
                                         cout << "\t\t\tFound clavage reverse reaction - " << validReactionFlag <<  " -  tentativi - " << rctCreationAttemptCounter <<
                                         " - Numero " << IDrct << endl;
                                }else{
                                    if(ids_I == (acs_longInt)allSpecies.size()) //IF THE POSITION RETURNED IS EQUAL TO THE SIZE OF VECOTR ALLSPECIES, IT MEANS THAT THE SPECIES IS NOT PRESENT
                                    {
                                            if(tmp_RndDoubleGen() < ratioSpeciesEnergizable){tmpEnergizable=ENERGIZABLE;}else{tmpEnergizable=NOTENERGIZABLE;}
                                            allSpecies.push_back(species(ids_I, product, (acs_longInt)0, 0, 0, 0, 0, 0, volume, 0, tmpEnergizable, influx_rate, maxLOut));
                                    }
                                    validReactionFlag = true;
                                }
                            }else{
                                validReactionFlag = false;
                            }
                        }

                    }

                    if(debugLevel == SMALL_DEBUG)
                        cout << "\t\t\tReaction validity: " << validReactionFlag << " - attempts " << rctCreationAttemptCounter << endl;

                    // IF ALL IT'S OK REACTION AND CATALYSIS ARE STORED

                    if(validReactionFlag == true)
                    {
                        // SINCE THE SPECIES HAS BEEN CREATED, NOW I HAVE TO CHECK WHETHER THE REACTION IS ALREADY PRESENT.
                        if(getNumberOfReactions() > 0)
                        {
                            id_reaction = returnPosReactionAlreadyPresent(reactionType, ids_I, ids_II, ids_III);
                        }else{
                            id_reaction = 0;
                        }

                        if(id_reaction == getNumberOfReactions())
                        {
                            if(debugLevel == SMALL_DEBUG)
                                cout << "\t\t\tStoring Reactions and Assagning catalysis for reaction " << IDrct << " - ID REACTION STORED: " << id_reaction << endl;
                            // IF THE ENERGY IS CONSIDERED
                            // According to the energy parameter and the reaction type the energetic type is assigned
                            if(nrgBoolFlag == ENERGYBASED)
                            {
                                if(nrgBooleanFunctions.size() > 0)
                                {
                                    nrgRctBoolFncID = returnSelectionIdFromAWeightProbVectorAlreadyNormalized(nrgBoolFncsProb2BeSelected,tmp_RndDoubleGen);
                                    try{
                                        tempEnergyRctType = nrgBooleanFunctions.at(nrgRctBoolFncID);
                                    }catch(exception&e){
                                        cout << "tempEnergyRctType = nrgBooleanFunctions.at(nrgRctBoolFncID);" << endl;
                                        cout << "Vectorsize "<<nrgBooleanFunctions.size()<<" - position "<<nrgRctBoolFncID<<endl;
                                        cerr << "tempEnergyRctType = nrgBooleanFunctions.at(nrgRctBoolFncID);"<<e.what()<<endl;
                                        ExitWithError("createReactionsForThisSpecies","exceptionerrorthrown");
                                    }
                                }else{
                                    // If the vector contains only 1 element, the first one is selected
                                    tempEnergyRctType = nrgBooleanFunctions.front();
                                }
                            }
                            // IF IT IS NOT PRESENT THE VECTOR ALLREACTIONS AND THE VECTOR ALLCATALYSIS ARE UPDATED
                            allReactions.push_back(reactions(id_reaction, reactionType, ids_I, ids_II, ids_III, 0, tempEnergyRctType));
                            if(reverseReactions == true)
                            {
                                if(reactionType == CONDENSATION)
                                {
                                    tmpK_ass = K_ass;
                                    tmpK_diss = K_diss / revRctRatio;
                                    tmpK_cpx = K_cpx;
                                }else{ //Cleavage reaction
                                    tmpK_ass = K_ass / revRctRatio;
                                    tmpK_diss = K_diss;
                                    tmpK_cpx = K_cpx / revRctRatio;
                                }
                            }else{ // reverseReactions == FALSE
                                tmpK_ass = K_ass;
                                tmpK_diss = K_diss;
                                tmpK_cpx = K_cpx;
                            }
                            allCatalysis.push_back(catalysis(getNumberOfCatalysis(), tmpsID, id_reaction, 0, tmpK_ass, tmpK_diss, tmpK_cpx));
                        }else{ // OTHERWISE ONLY THE VECTOR ALLCATALYSIS IS UPDATED
                            if(reverseReactions == true)
                            {
                                if(reactionType == CONDENSATION)
                                {
                                    tmpK_ass = K_ass;
                                    tmpK_diss = K_diss / revRctRatio;
                                    tmpK_cpx = K_cpx;
                                }else{ //Cleavage reaction
                                    tmpK_ass = K_ass / revRctRatio;
                                    tmpK_diss = K_diss;
                                    tmpK_cpx = K_cpx / revRctRatio;
                                }
                            }else{ // reverseReactions == FALSE
                                tmpK_ass = K_ass;
                                tmpK_diss = K_diss;
                                tmpK_cpx = K_cpx;
                            }
                            if(debugLevel == SMALL_DEBUG)
                                cout << "\t\t\tAssagning catalysis for reaction " << IDrct << endl;
                            //Check if this reaction is not already catalysed by this species
                            if(!checkIfTheReactionIsAlreadyCatalyzedByThisSpecies(tmpsID, id_reaction))
                                allCatalysis.push_back(catalysis(getNumberOfCatalysis(), tmpsID, id_reaction, 0, tmpK_ass, tmpK_diss, tmpK_cpx));
                        }
                    }else{
                            rctCreationAttemptCounter++;
                    }// if(validReactionFlag)
            } //while(!validReactionFlag)
        } // end for(acs_int IDrct = 0; IDrct < tmpReactionsForThisSpecies; IDrct++)
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::createReactionsForThisSpecies end" << endl;


    return true;
}

/**
 Select reaction type (cleavage or condensation) according to the cleavage probability
 @version 1.0
 @param acs_int tmpTotalNumberOfReactions Total number of conceivable reactions
 @param acs_double tmpRctsProb reaction probability
 */
acs_int environment::selectWhetherCleavageOrCond(MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::selectWhetherCleavageOrCond start" << endl;
	
	acs_int tmpReactionType = CONDENSATION; //set condensation as default value
	acs_double rndCleavProm = tmp__RndDoubleGen();	
	if(rndCleavProm < cleavageProbability)
	{
		tmpReactionType = CLEAVAGE;
	}	
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::selectWhetherCleavageOrCond end" << endl;

	return tmpReactionType;
}

/**
 Initial molecule population creation from file using standard C++ libraries
 @version 1.0
 @param string tmpSpeciesFilePath file path
 */
bool environment::createInitialMoleculesPopulationFromFileSTD(string tmpSpeciesFilePath)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromFileSTD start" << endl;
    // SPECIES FILE PATH CREATION
    string SpeciesFilePath = tmpSpeciesFilePath + "_acsspecies.csv";
    ifstream myfile;
    myfile.open(SpeciesFilePath.c_str());
    string strID, strCod, strConc, strDiff, strPrec, strK_cpx, strCpxBin, strEval, strAge, strReb, strCatID, strCpxID, strPho, strChar, strLock;
    while (myfile.good())
    {
        getline(myfile, strID, '\t');
        getline(myfile, strCod, '\t');
        getline(myfile, strConc, '\t');
        getline(myfile, strDiff, '\t');
        getline(myfile, strPrec, '\t');
        getline(myfile, strK_cpx, '\t');
        getline(myfile, strCpxBin, '\t');
        getline(myfile, strEval, '\t');
        getline(myfile, strAge, '\t');
        getline(myfile, strReb, '\t');
        getline(myfile, strCatID, '\t');
        getline(myfile, strCpxID, '\t');
        getline(myfile, strPho, '\t');
        getline(myfile, strChar, '\t');
        getline(myfile, strLock, '\n');

        cout << strID << " "<< strCod<<  " |"<< strConc<< "| "<<  strDiff<< " "<<  strPrec<< " "<<  strK_cpx<<" "<<  strCpxBin<< " "<<
                strEval<<  " "<< strAge<<  " "<< strReb<< " "<<  strCatID<<  " "<< strCpxID<<  " "<< strPho<< " "<<  strChar<<  " "<< strLock << endl;

        string prova;
        prova = "3.333333e-06";
        cout << "test " << prova << " " << prova.c_str() << " " << atof(prova.c_str()) << endl;
        cout << strConc.c_str() << " 1st" << endl;
        cout << atof(strConc.c_str()) << " 2nd" << endl;
        cout << (acs_double)atof(strConc.c_str()) << " 3rd" << endl;
        allSpecies.push_back(species((acs_longInt)atol(strID.c_str()), strCod, (acs_double)atof(strConc.c_str()),
                                     (acs_double)atof(strDiff.c_str()),(acs_int)atoi(strPrec.c_str()),
                                     (acs_double)atof(strK_cpx.c_str()), (acs_int)atoi(strCpxBin.c_str()),
                                     (acs_int)atoi(strEval.c_str()), (acs_double)atof(strAge.c_str()),atoi(strReb.c_str()), volume,
                                     (acs_longInt)atol(strCatID.c_str()), (acs_longInt)atol(strCpxID.c_str()),
                                     (acs_double)atof(strPho.c_str()), (acs_double)atof(strChar.c_str()),
                                     (acs_int)atoi(strLock.c_str()), influx_rate, maxLOut));
        try{
            if(allSpecies.at((acs_longInt)atoi(strID.c_str())).getComplexCutPnt() == 0)
            {
                if(allSpecies.at((acs_longInt)atoi(strID.c_str())).getAmount() > 0)
                    numberOfSpecies++;

                numberOfMolecules += allSpecies.at((acs_longInt)atoi(strID.c_str())).getAmount();
                if(((acs_longInt)atoi(strID.c_str()) > lastFiringDiskSpeciesID) &&
                   (allSpecies.at((acs_longInt)atoi(strID.c_str())).getAmount() > 0))
                {
                    numberOfNewSpecies++;
                    numberOfNewMolecules += allSpecies.at((acs_longInt)atoi(strID.c_str())).getAmount();
                }
            }else{ // If the species is a complex
                incNumberOfCpx();
                numberOfCpxMols += allSpecies.at((acs_longInt)atoi(strID.c_str())).getAmount();
            }
        }catch(exception&e){
            cout << "allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt()..." << endl;
            cout << "Vectorsize " << allSpecies.size() << " - position "<< (acs_longInt)atoi(strID.c_str()) << endl;
            cerr << "allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt().."<<e.what()<<endl;
            ExitWithError("createInitialMoleculesPopulationFromFile","exceptionerrorthrown");
        }
    }
    myfile.close();
    // FIRING DISK STORING, NUTRIENTS CREATION AND PROBABILITY VECTOR FOR A NUTRIENT TO BE SELECTED IS CREATED
    for(acs_int singleSpecies = 0; singleSpecies < (acs_int)allSpecies.size(); singleSpecies++)
    {
        if(allSpecies.at(singleSpecies).getID() <= getLastFiringDiskSpeciesID())
            firingDisk.push_back(allSpecies.at(singleSpecies));
    }
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromFile end" << endl;

    return true;
}//eof createInitialPopulationFromFileSTD



/**
 Initial molecule population creation from file
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialMoleculesPopulationFromFile(QString tmpSpeciesFilePath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromFile start" << endl;

	// CONFIGURATION FILE PATH CREATION
	QString SpeciesFilePath = tmpSpeciesFilePath + "_acsspecies.csv";
	QTextStream prompt(stdout);
	prompt << "Loading species sequences from " << SpeciesFilePath << endl;
	//OPEN FILE
	QFile fid(SpeciesFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromFile", "File has not been found");
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
            QString strLine = in.readLine();
            if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
            {
                QStringList strLineSpletted = strLine.split("\t");
                allSpecies.push_back(species((acs_longInt)strLineSpletted[0].toInt(), strLineSpletted[1].QString::toStdString(),
                                             (acs_double)strLineSpletted[2].toDouble(), (acs_double)strLineSpletted[3].toDouble(),
                                             (acs_double)strLineSpletted[4].toDouble(), (acs_double)strLineSpletted[5].toDouble(),
                                             (acs_longInt)strLineSpletted[6].toInt(), strLineSpletted[7].toInt(),
                                             (acs_double)strLineSpletted[8].toDouble(), strLineSpletted[9].toInt(), volume,
                                             (acs_double)strLineSpletted[10].toDouble(), (acs_double)strLineSpletted[11].toDouble(),
                                             (acs_double)strLineSpletted[12].toDouble(), (acs_double)strLineSpletted[13].toDouble(),
                                             (acs_int)strLineSpletted[14].toInt(), influx_rate, maxLOut));
                try{
                    if(allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt() == 0)
                    {
                        if(allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount() > 0)
                            numberOfSpecies++;

                        numberOfMolecules += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
                        if(((acs_longInt)strLineSpletted[0].toInt() > lastFiringDiskSpeciesID) &&
                           (allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount() > 0))
                        {
                            numberOfNewSpecies++;
                            numberOfNewMolecules += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
                        }
                    }else{ // If the species is a complex
                        incNumberOfCpx();
                        numberOfCpxMols += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
                    }
                }catch(exception&e){
                    cout << "allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt()..." << endl;
                    cout << "Vectorsize " << allSpecies.size() << " - position "<< (acs_longInt)strLineSpletted[0].toInt() << endl;
                    cerr << "allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt().."<<e.what()<<endl;
                    ExitWithError("createInitialMoleculesPopulationFromFile","exceptionerrorthrown");
                }
            }
        }
	
	fid.close();
	// FIRING DISK STORING, NUTRIENTS CREATION AND PROBABILITY VECTOR FOR A NUTRIENT TO BE SELECTED IS CREATED
	for(acs_int singleSpecies = 0; singleSpecies < (acs_int)allSpecies.size(); singleSpecies++)
	{
		if(allSpecies.at(singleSpecies).getID() <= getLastFiringDiskSpeciesID())
			firingDisk.push_back(allSpecies.at(singleSpecies));
	}	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromFile end" << endl;
	
	return true;
}//eof createInitialPopulationFromFile

/**
 Initial molecule population creation. Species are uploaed from a SPECIFIC file created using actual generation and simuation
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialMoleculesPopulationFromSpecificFile(QString tmpSpeciesFilePath, acs_int tmpActGEN, acs_int tmpActSIM)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromSpecificFile start" << endl;
	
	QString strCurrentGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpActGEN);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpActGEN)), tmpActSIM);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, 0);
	// CONFIGURATION FILE PATH CREATION
	QString SpeciesFilePath = tmpSpeciesFilePath + "species_" + strZeroGenBefore + strCurrentGen.setNum(tmpActGEN) + 
															"_" +  strZeroSimBefore + strCurrentSim.setNum(tmpActSIM) + 
															"_" +  strZeroStepBefore + strCurrentStep.setNum(0)	+ ".csv";
	QTextStream prompt(stdout);
	if(debugLevel >= MINIMAL_PROMPT)
	{
		prompt << endl << "\t\t|- Loading species structure from " << SpeciesFilePath << endl;
	}
	//OPEN FILE
	QFile fid(SpeciesFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "File has not been found");
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			allSpecies.push_back(species((acs_longInt)strLineSpletted[0].toInt(), strLineSpletted[1].QString::toStdString(), 
                                                     (acs_double)strLineSpletted[2].toDouble(), (acs_double)strLineSpletted[3].toDouble(),
                                                     (acs_double)strLineSpletted[4].toDouble(), (acs_double)strLineSpletted[5].toDouble(),
                                                     (acs_longInt)strLineSpletted[6].toInt(), strLineSpletted[7].toInt(),
                                                     (acs_double)strLineSpletted[8].toDouble(), strLineSpletted[9].toInt(), volume,
                                                     (acs_double)strLineSpletted[10].toDouble(), (acs_double)strLineSpletted[11].toDouble(),
                                                     (acs_double)strLineSpletted[12].toDouble(), (acs_double)strLineSpletted[13].toDouble(),
                                                     (acs_int)strLineSpletted[14].toInt(), influx_rate, maxLOut));
			if(allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getComplexCutPnt() == 0)
			{
                if(allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount() > 0) numberOfSpecies++;
				numberOfMolecules += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
                if(((acs_longInt)strLineSpletted[0].toInt() > lastFiringDiskSpeciesID) && (allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount() > 0))
				{
					numberOfNewSpecies++;
					numberOfNewMolecules += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
				}
			}else{ // If the species is a complex
				incNumberOfCpx();
				numberOfCpxMols += allSpecies.at((acs_longInt)strLineSpletted[0].toInt()).getAmount();
			}
		}
	}	
	
	fid.close();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialMoleculesPopulationFromSpecificFile end" << endl;
	
	return true;
}//eof createInitialPopulationFromFile

/**
 Create influx layer from file
 @version 1.0
 @param QString tmpInfluxFilePath file path
 @date 2010-05-18
 
*/
bool environment::createInfluxLayersFromFile(QString tmpInfluxFilePath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInfluxLayersFromFile start" << endl;
	// INFLUX FILE PATH CREATION
	QString InfluxFilePath = tmpInfluxFilePath + "_acsinflux.csv";
	QTextStream prompt(stdout);
	prompt << "Loading influx layer from " << InfluxFilePath << endl;
	//OPEN FILE
	QFile fid(InfluxFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInfluxLayersFromFile", "File _influx.csv has not been found");
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			nutrientsForInflux.push_back(strLineSpletted[0].toInt());
            nutrientsProb2BeSelected.push_back(strLineSpletted[1].toDouble());
		}
	}	
	
	fid.close();
	
	if(debugLevel >= SMALL_DEBUG){printNutrientsAndProbability();}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInfluxLayersFromFile end" << endl;
	return true;
}

/**
 load energy boolean function (in decimal format)
 @version 1.0
 @param QString tmpInfluxFilePath file path
 @date 2011-04-13

*/
bool environment::createNrgBooleanFunctionsFromFile(QString tmpInfluxFilePath)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createNrgBooleanFunctionsFromFile start" << endl;
    // INFLUX FILE PATH CREATION
    QString InfluxFilePath = tmpInfluxFilePath + "_acsnrgbooleanfunctions.csv";
    QTextStream prompt(stdout);
    prompt << "Loading energy Boolean functions from " << InfluxFilePath << endl;
    //OPEN FILE
    QFile fid(InfluxFilePath);
    if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
            ExitWithError("createNrgBooleanFunctionsFromFile", "File _acsnrgbooleanfunctions.csv has not been found");

    QTextStream in(&fid);
    while(!in.atEnd())
    {
            QString strLine = in.readLine();
            if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
            {
                    QStringList strLineSpletted = strLine.split("\t");
                    nrgBooleanFunctions.push_back(strLineSpletted[0].toInt());
                    nrgBoolFncsProb2BeSelected.push_back(strLineSpletted[1].toDouble());
            }
    }

    fid.close();

    if(debugLevel >= SMALL_DEBUG){printNutrientsAndProbability();}

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createNrgBooleanFunctionsFromFile end" << endl;
    return true;
}

/**
 Initial reactions layer creation from file
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialReactionsLayerFromFile(QString tmpReactionsFilePath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialReactionsLayerFromFile start" << endl;

	// CONFIGURATION FILE PATH CREATION
	QString ReactionsFilePath = tmpReactionsFilePath + "_acsreactions.csv";
	QTextStream prompt(stdout);
	prompt << "Loading reactions layer from " << ReactionsFilePath << endl;
	//OPEN FILE
	QFile fid(ReactionsFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "File has not been found");
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			allReactions.push_back(reactions((acs_longInt)strLineSpletted[0].toInt(), (acs_longInt)strLineSpletted[1].toInt(), 
											 (acs_longInt)strLineSpletted[2].toInt(), (acs_longInt)strLineSpletted[3].toInt(), 
											 (acs_longInt)strLineSpletted[4].toInt(), (acs_longInt)strLineSpletted[5].toInt(),
                                                                                         (acs_double)strLineSpletted[6].toInt()));
		}
	}
	
	fid.close();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialReactionsLayerFromFile end" << endl;

	return true;
}//eof createInitialPopulationFromFile

/**
 Initial reactions layer creation from SPECIFIC file
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialReactionsLayerFromSpecificFile(QString tmpReactionsFilePath, acs_int tmpActGEN, acs_int tmpActSIM)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialReactionsLayerFromSpecificFile start" << endl;
	
	// CONFIGURATION FILE PATH CREATION
	QString strCurrentGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpActGEN);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpActGEN)), tmpActSIM);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, 0);
	// CONFIGURATION FILE PATH CREATION
	QString ReactionsFilePath = tmpReactionsFilePath + "reactions_" + strZeroGenBefore + strCurrentGen.setNum(tmpActGEN) + 
													"_" +  strZeroSimBefore + strCurrentSim.setNum(tmpActSIM) + 
													"_" +  strZeroStepBefore + strCurrentStep.setNum(0)	+ ".csv";
	QTextStream prompt(stdout);
	if(debugLevel >= MINIMAL_PROMPT)
	{
		prompt << "\t\t|- Loading reactions layer from " << ReactionsFilePath << endl;
	}
	//OPEN FILE
	QFile fid(ReactionsFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "File has not been found");
	
	QTextStream in(&fid);
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			allReactions.push_back(reactions((acs_longInt)strLineSpletted[0].toInt(), (acs_longInt)strLineSpletted[1].toInt(), 
											 (acs_longInt)strLineSpletted[2].toInt(), (acs_longInt)strLineSpletted[3].toInt(), 
											 (acs_longInt)strLineSpletted[4].toInt(), (acs_longInt)strLineSpletted[5].toInt(),
                                                                                         (acs_double)strLineSpletted[6].toInt()));
		}
	}
	
	fid.close();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialReactionsLayerFromSpecificFile end" << endl;
	
	return true;
}//eof createInitialreactionsLayerFromSpecificFile

/**
 Initial catalysis layer creation from file
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialCatalysisLayerFromFile(QString tmpCatalysisFilePath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialCatalysisLayerFromFile start" << endl;

	// CONFIGURATION FILE PATH CREATION
	QString CatalysisFilePath = tmpCatalysisFilePath + "_acscatalysis.csv";
	QTextStream prompt(stdout);
	prompt << "Loading catalysis layer from " << CatalysisFilePath << endl;
	//OPEN FILE
	QFile fid(CatalysisFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "File has not been found");
	
	QTextStream in(&fid);
	int catalysisID = 1;
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			allCatalysis.push_back(catalysis((acs_longInt)strLineSpletted[0].toInt(), (acs_longInt)strLineSpletted[1].toInt(), 
											 (acs_longInt)strLineSpletted[2].toInt(), (acs_longInt)strLineSpletted[3].toInt(),
											 (acs_double)strLineSpletted[4].toDouble(), (acs_double)strLineSpletted[5].toDouble(), 
											 (acs_double)strLineSpletted[6].toDouble()));
			catalysisID++;
		}
	}
	
	fid.close();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialCatalysisLayerFromFile end" << endl;

	return true;
}//eof createInitialPopulationFromFile

/**
 Initial catalysis layer creation from SPECIFIC file
 @version 1.0
 @param QString tmpSpeciesFilePath file path
 */
bool environment::createInitialCatalysisLayerFromSpecificFile(QString tmpCatalysisFilePath, acs_int tmpActGEN, acs_int tmpActSIM)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialCatalysisLayerFromSpecificFile start" << endl;
	
	// CONFIGURATION FILE PATH CREATION
	QString strCurrentGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpActGEN);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpActGEN)), tmpActSIM);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, 0);
	// CONFIGURATION FILE PATH CREATION
	QString CatalysisFilePath = tmpCatalysisFilePath + "catalysis_" + strZeroGenBefore + strCurrentGen.setNum(tmpActGEN) + 
                                                                "_" +  strZeroSimBefore + strCurrentSim.setNum(tmpActSIM) +
                                                                "_" +  strZeroStepBefore + strCurrentStep.setNum(0)	+ ".csv";
	
	QTextStream prompt(stdout);
	if(debugLevel >= MINIMAL_PROMPT)
	{
		prompt << "\t\t|- Loading catalysis layer from " << CatalysisFilePath << endl;
	}
	//OPEN FILE
	QFile fid(CatalysisFilePath);
	if(!fid.open(QIODevice::ReadOnly | QIODevice::Text))
		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "File has not been found");
	
	QTextStream in(&fid);
	int catalysisID = 1;
	while(!in.atEnd())
	{
		QString strLine = in.readLine();
		if((strLine.contains("#") == false) && (strLine.isEmpty() == false) && (strLine.isNull() == false))
		{
			QStringList strLineSpletted = strLine.split("\t");
			allCatalysis.push_back(catalysis((acs_longInt)strLineSpletted[0].toInt(), (acs_longInt)strLineSpletted[1].toInt(), 
                                                         (acs_longInt)strLineSpletted[2].toInt(), (acs_longInt)strLineSpletted[3].toInt(),
                                                         (acs_double)strLineSpletted[4].toDouble(), (acs_double)strLineSpletted[5].toDouble(),
                                                         (acs_double)strLineSpletted[6].toDouble()));
			catalysisID++;
		}
	}
	
	fid.close();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::createInitialCatalysisLayerFromSpecificFile end" << endl;
	
	return true;
}//eof createInitialCatalysisLayerFromSpecificFile

/**
 Create the initial amount of the molecules belonging to a particular species according to the species length
 @version 1.0
 @param tmpAlphabetLength Number of symbols in the alphabet
 @param tmpSpeciesLength Lenght of the species
 */
//TR acs_longInt environment::createInitialAmount(int tmpAlphabetLength, int tmpSpeciesLength)
//{
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::createInitialAmount start" << endl;
//	
//	acs_longInt tmpInitialAmount;
//	if(initialAmountDistribution == PROPORTIONALMOLECULEAMOUNT)
//	{
//		tmpInitialAmount = overallConcentration / totalPossibleNumberOfSpecies;
//		
//	}else if(initialAmountDistribution == UNIFORMMOLECULEAMOUNT)
//	{
//		// tmpInitialAmount = Al^{Lmax-Ls}
//		tmpInitialAmount = pow(acs_double(tmpAlphabetLength), int(initialMaxLength - tmpSpeciesLength)) * overallConcentration;
//	
//	}else{ // INVPROPORTIONALMOLECULEAMOUNT
//		
//		// tmpInitialAmount = Al^2{Lmax-Ls}
//		tmpInitialAmount = pow(acs_double(tmpAlphabetLength), 2 * int(initialMaxLength - tmpSpeciesLength)) * overallConcentration;
//
//	}
//	
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::createInitialAmount end" << endl;
//
//	return tmpInitialAmount;
//}

/**
 Create the initial concentration of the species according to the species length, the alphabet and the overall concentration
 @version 1.0
 @param tmpAlphabetLength Number of symbols in the alphabet
 @param tmpSpeciesLength Lenght of the species
 */
//TR acs_double environment::createInitialConcentration(int tmpAlphabetLength, int tmpSpeciesLength)
//{
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::createInitialConcentration start" << endl;
//	
//	acs_double tmpInitialConcentration;
//	
//	if(initialAmountDistribution == PROPORTIONALMOLECULEAMOUNT)
//	{
//		tmpInitialConcentration = overallConcentration / (lastFiringDiskSpeciesID + 1);
//		
//	}else if(initialAmountDistribution == UNIFORMMOLECULEAMOUNT)
//	{
//		// The overall concentration is uniformly distributed between the different lengths
//		acs_double tmpSngLengthConcentration = overallConcentration / initialMaxLength;
//	    acs_double numberOfSpeciesOfLengthL = pow(acs_double(tmpAlphabetLength), tmpSpeciesLength);
//		tmpInitialConcentration = tmpSngLengthConcentration / numberOfSpeciesOfLengthL;
//		
//	}else{ // INVPROPORTIONALMOLECULEAMOUNT
//		
//		// Starting from length 1, each length use the 2/3 of the reamining concentration
//		acs_double numberOfSpeciesOfLengthL = pow(acs_double(tmpAlphabetLength), tmpSpeciesLength);
//		if((unsigned)tmpSpeciesLength == initialMaxLength)
//		{
//			tmpInitialConcentration = (overallConcentration * pow(pow(double(3), double(-1)), double(tmpSpeciesLength - 1))) / numberOfSpeciesOfLengthL;
//		}else {
//			tmpInitialConcentration = (overallConcentration * 
//									  (pow(pow(double(3), double(-1)), double(tmpSpeciesLength - 1)) - 
//									  pow(pow(double(3), double(-1)),double(tmpSpeciesLength)))) / numberOfSpeciesOfLengthL;
//
//		}		
//	}
//	
//	
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::createInitialConcentration end" << endl;
//	
//	return tmpInitialConcentration;
//	
//}

/**
 Create the diffusion constant renforcement according to the species length
 @version 1.0
 @param tmpDiffEnh diffusion enhancement from parameters
 @param MTRand& tmp_RndDoubleGen random number generator
 @param tmpNewSpeciesLength Lenght of the species
 */
acs_double environment::createDiffusionRenforcement(acs_double tmpDiffEnh, acs_int tmpNewSpeciesLength)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::createDiffusionRenforcement start" << endl;

	// THEORETICALLY DIFFUSION GOES WITH THE ROOT OF THE LENGTH, SO DIFFUSION KINETIC CONSTANT
	// IS EQUAL TO L^(-TMPDIFFENH)
	acs_double tmpDiffusionRenforcement = pow((double)tmpNewSpeciesLength, -(double)tmpDiffEnh);
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::createDiffusionRenforcement end" << endl;

	
	return tmpDiffusionRenforcement;
}

/**
 Create the precipitation constant renforcement according to the species length
 @version 2.5.1
 @param tmpPreEnh precipitation enhancement from parameters
 @param MTRand& tmp_RndDoubleGen random number generator
 @param tmpNewSpeciesLength Lenght of the species
 */
bool environment::setSolubility(acs_int tmpNewSpeciesLength, MTRand& tmpRndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::setSolubility start" << endl;

	bool tmpSolubility = true;
//	acs_double tmpDice;
//	acs_double lengthToLogistic;
	
        if(solubility_threshold > 0)
	{	
//		tmpDice = tmpRndDoubleGen();
//		lengthToLogistic = 1 / (1 + pow(NEP, (double)solubility_threshold-tmpNewSpeciesLength));
//		if(tmpDice < lengthToLogistic)
//		{
//			tmpSolubility = false;
//		}
                // COMMENT THIS LINE IF YOU WANT TO REACTIVATE THE TANH FUNCTION
                if(tmpNewSpeciesLength >= solubility_threshold)
                    tmpSolubility = false;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\tenvironment::setSolubility end" << endl;
	
	return tmpSolubility;
}

/**
 This functions returns the ID of the species whether this one is already present, otherwise the new ID is created as the 
 number of elements in the species vector
 @version 1.0
 @param tmpNewSequence New sequence to evaluate
 @param MTRand& tmp_RndDoubleGen random number generator
 @param tmpNewSpeciesLength Lenght of the species
 */
acs_longInt environment::returnPosSpeciesAlreadyPresent(string tmpNewSequence)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::returnPosSpeciesAlreadyPresent start" << endl;

	acs_longInt tmpPosition = (acs_longInt)allSpecies.size();
	for(acs_longInt i = 0; i < getNumberOfTheoreticalSpecies(); i++)
	{
		if(allSpecies.at(i).getSequence() == tmpNewSequence)
		{
			if(allSpecies.at(i).getComplexCutPnt() == 0)
			{
				tmpPosition = i;
				break;
			}
		}
	}	
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::returnPosSpeciesAlreadyPresent end" << endl;

	return tmpPosition;
}

/**
 Return the reaction ID if the reaction is already present, otherwise it returns the new reaction ID
 @version 1.0
 @param acs_int tmpReactionType rection type (cleavage or condensation)
 @param acs_longInt tmpIds_I species I ID
 @param acs_longInt tmpIds_II species II ID
 @param acs_longInt tmpIds_III species III ID
 */
acs_longInt environment::returnPosReactionAlreadyPresent(acs_int tmpReactionType, acs_longInt tmpIds_I, acs_longInt tmpIds_II, acs_longInt tmpIds_III)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::returnPosReactionAlreadyPresent start" << endl;

	acs_longInt reactionPos = (acs_longInt)allReactions.size();
	for(acs_longInt i = 0; i < getNumberOfReactions(); i++) //FOR EACH REACTION
	{
		if(allReactions.at(i).getType() == tmpReactionType) //IF THE TYPE IS THE SAME
		{
			if(allReactions.at(i).getSpecies_I() == tmpIds_I) //IF THE FIRST SPECIES IS THE SAME
			{
				// IF THE SECOND AND THE THIRD SPECIES ARE THE SAME, THE POSITION DOESN'T MATTER 
				if( (allReactions.at(i).getSpecies_II() == tmpIds_II && allReactions.at(i).getSpecies_III() == tmpIds_III) ||
					(allReactions.at(i).getSpecies_II() == tmpIds_III && allReactions.at(i).getSpecies_III() == tmpIds_II)) 
				{
					reactionPos = i;
					break;
				}
			}
		}	
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::returnPosReactionAlreadyPresent end" << endl;
	
	return reactionPos;
}

/**
 If the reaction is not new this function checks if the reactions has been already catalysed by this species
 @version 1.0
 @param acs_int tmpSPeciesID catalyst ID
 @param tmpIdReaction reaction ID
 */
bool environment::checkIfTheReactionIsAlreadyCatalyzedByThisSpecies(acs_longInt tmpSPeciesID, acs_longInt tmpIdReaction)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::checkIfTheReactionIsAlreadyCatalyzedByThisSpecies start" << endl;

	bool tmpAlreadyCatFlag = false;
	for(acs_longInt i = 0; i < getNumberOfCatalysis(); i++)
	{
		if(allCatalysis.at(i).getCat() == tmpSPeciesID)
		{
			if(allCatalysis.at(i).getReactionID() == tmpIdReaction)
			{
				tmpAlreadyCatFlag = true;
				break;
			}
		}
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::checkIfTheReactionIsAlreadyCatalyzedByThisSpecies end" << endl;
	
	return tmpAlreadyCatFlag;

}

/**
 This function return false if the tmpCandidateProduct is a catalyst of tmpCat
 @version 1.0 - last update 2009/10/08 - build 009
 
 */
bool environment::checkIfOnlyMutualCatalysis(acs_int tmpCat, acs_int tmpCandidateProduct)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::checkIfOnlyMutualCatalysis start" << endl;
	bool tmpNoMutualCatalysis = true;
	for(acs_longInt i = 0; i < getNumberOfCatalysis(); i++)
	{
		// Select reaction for the candidate product
		if(allCatalysis.at(i).getCat() == tmpCandidateProduct)
		{
			if(allReactions.at(allCatalysis.at(i).getReactionID()).getType() == 0) // Condensation
			{
				if(allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I() == tmpCat)
				{
					tmpNoMutualCatalysis = false;
					break;
				}
			}else{	// Cleavage
				if(allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II() == tmpCat || 
				   allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_III() == tmpCat)
				{
					tmpNoMutualCatalysis = false;
					break;
				}				
			}
		}
	}
	

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\t\t\tenvironment::checkIfOnlyMutualCatalysis end" << endl;
	return tmpNoMutualCatalysis;
}


/**
 This function check the coherence of the data structures. IF IT FAULTS THE SYSTEM RETURNS ERROR!!!
 IT IS VERY RECOMMENDED RUN THIS FUNCTION ALWAYS AFTER THE INITIALIZATION
 @version 1.1
 @date 2011-04-13
 */
bool environment::structureCoherenceCheckUp()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::structureCoherenceCheckUp start" << endl;
	
	bool flagControl = true;
	
	if(debugLevel >= RUNNING_VERSION)
	{
		cout << endl;
		cout << "|- STRUCTURE COHERENCE CONTROL |" << endl;
	
	// ===================================
	// SPECIES STRUCTURE COHERENCE CONTROL
	// ===================================
	
		cout << "\t|- SPECIES STRUCTURE" << endl;
		cout << "\t\t|- Searching for Incoherences, double entries and incorrect ID progression... ";
	}
	for(acs_longInt i = 0; i < getNumberOfTheoreticalSpecies(); i++)
	{
		for(acs_longInt j= 0; j < getNumberOfTheoreticalSpecies(); j++)
		{
			if(i != j) // A Species is definitely equal to itself
			{
				if(allSpecies.at(i).getSequence() == allSpecies.at(j).getSequence())
				{ // IF THE SEQUENCE IS THE SAME THE CUTTING POINT HAS TO BE CHECKED
					if(debugLevel >= SMALL_DEBUG)
					{
						cout << endl << "\t\t\t |- The sequence of " <<  allSpecies.at(i).getSequence() << " [ID" << i << "] is the same of "
							 <<   allSpecies.at(i).getSequence() << " [ID" << j << "]... check CUTTING POINT"; 
					}
				   if(allSpecies.at(i).getComplexCutPnt() == allSpecies.at(j).getComplexCutPnt())
				   {
					   flagControl = false;
					   cout << endl << "\t\t\t|- ERROR: Species " << allSpecies.at(i).getID() << " is a duplicate of species "
							<< allSpecies.at(j).getID() << ": The two cutting points are NOT different: "
							<< allSpecies.at(i).getComplexCutPnt()  << " and " << allSpecies.at(j).getComplexCutPnt()  << endl;
					   break;
				   }else{
					   if(debugLevel >= SMALL_DEBUG)
					   {
						   cout << endl << "\t\t\t|- NO PROBLEN: The two cutting points are different: " << allSpecies.at(i).getComplexCutPnt()
								<< " and " << allSpecies.at(j).getComplexCutPnt()  << endl;
					   }
				   }
				}
			}
		}
		if(debugLevel >= RUNNING_VERSION)
		{
			if(i == getNumberOfTheoreticalSpecies())
			{
				if(flagControl == true)
					cout << endl << "\t\t\t|- No Double entries... OK!" << endl;
			}
		}
		
		if(debugLevel >= SMALL_DEBUG)
		{
			cout << endl << "ID: " << allSpecies.at(i).getID() << "\t"
			<< "SEQ: " << allSpecies.at(i).getSequence() << "\t"
			<< "AMOUNT: " << allSpecies.at(i).getAmount() << "\t"
			<< "DIFF: " << allSpecies.at(i).getDiffusionEnh() << "\t"
			<< "PREC: " << allSpecies.at(i).getSolubility() << "\t"
			<< "COM DEG: " << allSpecies.at(i).getComplexDegEnh() << "\t"
			<< "CUT PNT: " << allSpecies.at(i).getComplexCutPnt() << "\t"
			<< "EVAL: " << allSpecies.at(i).getEvaluated();
		}
                //SINGLE CHECKS, with the following TRY all allSpecies.at(i) are checked
                try{
                    if(allSpecies.at(i).getID() != i) //CHECK ID PROGRESSION
                    {
                        flagControl = false;
                        cout << endl << "\t\t\tERROR: SPECIES ID progression in not right: ID " << allSpecies.at(i).getID() << " could be equal to " << i << endl;
                    }
                }catch(exception&e){
                    cout << "structureCoherenceCheckUp allSpecies.at(i)…" << endl;
                    cout << "Vectorsize " << allSpecies.size() << " - position " << i << endl;
                    cerr << "exceptioncaught:" << e.what() << endl;
                    ExitWithError("structureCoherenceCheckUp","exceptionerrorthrown");
               }

		if(allSpecies.at(i).getComplexCutPnt() > 0 && allSpecies.at(i).getEvaluated() > 0) // COMPLEX CANNOT BE EVALUATED
		{
			flagControl = false;
			cout << endl << "Species " << allSpecies.at(i).getID() << " is a complex and cannot be evaluated!!!" << endl;
		}
		// IF THERE ARE MOLECULE BELONGING TO THE SPECIES, THE SPECIES HAD TO BE EVALUATED
		if(allSpecies.at(i).getAmount() > 0 &&  allSpecies.at(i).getComplexCutPnt() == 0 && allSpecies.at(i).getEvaluated() == 0) 
		{
			flagControl = false;
			cout << endl << "Species " << allSpecies.at(i).getSequence() << "(ID" << i << ") has "
				 <<  allSpecies.at(i).getAmount() << " and it wasn't evaluated!!!" << endl;
		}	
		// A COMPLEX HAS TO BE EOLUBILITY SET TO 1
		if(allSpecies.at(i).getComplexCutPnt() > 0 && allSpecies.at(i).getSolubility() == PRECIPITATED) 
		{
			flagControl = false;
			cout << endl << "Complex " << allSpecies.at(i).getSequence() << "(ID" << i << ") has to be solubility set to 1!!!" << endl;
		}			
	}
	
	if(debugLevel >= RUNNING_VERSION)
	{
		//Previous Test
		cout << endl << "\t\t\t|- ID Progression... OK!" << endl;
		cout << "\t\t\t|- Complexes not evaluated... OK!" << endl;
		cout << "\t\t\t|- Living Species Evaluated... OK!" << endl;
		cout << "\t\t\t|- Complex Solubility... OK!" << endl;
	}
	
	// ===================================
	// IF THE SYSTEM IS OPEN
	// ===================================
	
        if(influx_rate > 0)
	{
            if(flagControl) // IF THE PREVIOUS CONTROL WAS OK REACTION CONTROL WILL BE PERFORMED
            {
                if(debugLevel == RUNNING_VERSION)
                {
                    //Check reactions structures
                    cout << "\t|- INFLUX LAYER STRUCTURE" << endl;
                    cout << "\t\t|- Searching for firing disk lacking coupling with the influx species and incorrect cumulative probability... ";
                }
                acs_int tempPresentSpeciesTOT = 0;
                acs_int tempInfluxID = 0;

                for(vector<acs_int>::iterator tmpAllNutrientsIter = nutrientsForInflux.begin(); tmpAllNutrientsIter != nutrientsForInflux.end(); tmpAllNutrientsIter++)
                {
                    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
                    {
                        if(*tmpAllNutrientsIter == tmpAllSpeciesIter->getID())
                        {
                                tempPresentSpeciesTOT += 1;
                                break;
                        }
                    }
                    tempInfluxID += 1;
                }

                if(tempInfluxID != tempPresentSpeciesTOT)
                {
                    flagControl = false;
                    cout << endl << "\t\t\tERROR: Not all the influx species are prenset in the firing fisk";
                }else{
                    if(debugLevel == RUNNING_VERSION)
                    {
                            cout << endl << "\t\t\t|- Influx Species are already present in the firing disk... OK!" << endl;

                    }
                }
            }
	}
	
	// ===================================
	// IF THERE ARE REACTIONS
	// ===================================

	
	if((acs_longInt)allReactions.size() > 0)
	{
            if(debugLevel == RUNNING_VERSION)
            {
                //Check reactions structures
                cout << "\t|- REACTIONS LAYER STRUCTURE" << endl;
                cout << "\t\t|- Searching for duplicate, incorrect reactions products and ID progression... ";
            }

            if(flagControl) // IF THE PREVIOUS CONTROL WAS OK REACTION CONTROL WILL BE PERFORMED
            {
                string tmpStr1; // TEMPORARY TEST STRING 1
                string tmpStr2; // TEMPORARY TEST STRING 2
                string tmpStr3; // TEMPORARY TEST STRING 3
                string tmpStrtot; // TEMPORARY CONCATENATION OF STR2 AND STR3
                acs_double tmpClConRatio = 0;

                // FOR ALL REACTIONS
                for(acs_longInt i = 0; i < getNumberOfReactions() - 1; i++)
                {
                    if (allReactions.at(i).getType() == 1) {
                            tmpClConRatio++;
                    }

                    if(debugLevel >= MEDIUM_DEBUG)
                    {
                        cout << endl << "ID: " << allReactions.at(i).getID() <<
                                        "\tType: " << allReactions.at(i).getType() <<
                                        "\tMOL 1: " << allReactions.at(i).getSpecies_I() <<
                                        "\tMOL 2: " << allReactions.at(i).getSpecies_II() <<
                                        "\tMOL 3: " << allReactions.at(i).getSpecies_III() <<
                                        "\tOccurence: " << allReactions.at(i).getEvents() <<
                                        "\tEquilibrium constant: " << allReactions.at(i).getEnergyType();
                    }

                    // CHECK ID PROGRESSION
                    if(allReactions.at(i).getID() != i)
                    {
                        flagControl = false;
                        cout << endl << "\t\t\tERROR: REACTION ID progression in not right: ID " << allReactions.at(i).getID() <<
                        " could be equal to " << i << endl;
                        //break;
                    }

                    // CHECK THAT SUBSTRATES ARE NOT INVOLVED IN REACTIONS
                    try{
                        if(allSpecies.at(allReactions.at(i).getSpecies_I()).getComplexCutPnt() > 0)
                        {
                                flagControl = false;
                                cout << endl << "\t\t\tERROR: Reaction " << i << ", Species " << allReactions.at(i).getSpecies_I() << " ia a complex, then it can not be affected by any reaction!!!" << endl;
                        }
                    }catch(exception&e){
                        cout << "structureCoherenceCheckUp allSpecies.at(allReactions.at(i).getSpecies_I())…" << endl;
                        cout << "Vectorsize " << allSpecies.size() <<" - position "<< i << endl;
                        cerr << "exceptioncaught:"<<e.what()<<endl;
                        ExitWithError("structureCoherenceCheckUp","exceptionerrorthrown");
                   }

                   try{
                        if(allSpecies.at(allReactions.at(i).getSpecies_II()).getComplexCutPnt() > 0)
                        {
                                flagControl = false;
                                cout << endl << "\t\t\tERROR: Reaction " << i << ", Species " << allReactions.at(i).getSpecies_II() << " ia a complex, then it can not be affected by any reaction!!!" << endl;
                        }
                    }catch(exception&e){
                        cout << "if(allSpecies.at(allReactions.at(i).getSpecies_II()).getComplexCutPnt() > 0)" << endl;
                        cout << "Vectorsize "<<allSpecies.size()<<" - position " << i << endl;
                        cerr << "exceptioncaught:"<<e.what()<<endl;
                        ExitWithError("structureCoherenceCheckUp","exceptionerrorthrown");
                   }

                   try{
                        if(allSpecies.at(allReactions.at(i).getSpecies_III()).getComplexCutPnt() > 0)
                        {
                                flagControl = false;
                                cout << endl << "\t\t\tERROR: Reaction " << i << ", Species " << allReactions.at(i).getSpecies_III() << " ia a complex, then it can not be affected by any reaction!!!" << endl;
                        }
                    }catch(exception&e){
                        cout << "if(allSpecies.at(allReactions.at(i).getSpecies_III()).getComplexCutPnt() > 0)" << endl;
                        cout << "Vectorsize "<<allSpecies.size()<<" - position " << i << endl;
                        cerr << "exceptioncaught:"<<e.what()<<endl;
                        ExitWithError("structureCoherenceCheckUp","exceptionerrorthrown");
                   }

                    // CHECK COMPOSITION COHERENCE
                    tmpStr1 = allSpecies.at(allReactions.at(i).getSpecies_I()).getSequence();
                    tmpStr2 = allSpecies.at(allReactions.at(i).getSpecies_II()).getSequence();
                    tmpStr3 = allSpecies.at(allReactions.at(i).getSpecies_III()).getSequence();
                    tmpStrtot = tmpStr2 + tmpStr3;

                    if(tmpStr1 != tmpStrtot)
                    {
                            flagControl = false;
                            if(debugLevel >= RUNNING_VERSION)
                                    cout << endl << "\t\t\tERROR in reaction " << i << " - Type: " << allReactions.at(i).getType() << endl;
                                    cout << "\t\t\t\t: " << tmpStr1 << "[" << allReactions.at(i).getSpecies_I() << "] cannot be product or substrate of " << tmpStr2 << "[" << allReactions.at(i).getSpecies_II()
                                    << "] + " << tmpStr3 << "[" << allReactions.at(i).getSpecies_III() << "]";
                    }

                    // SEARCHING FOR DUPLICATE REACTIONS
                    for(acs_longInt j = 0; j < getNumberOfReactions(); j++)
                    {
                        if( i != j)// A single reaction is definitely equal to itself
                        {
                            try{
                                if(allReactions.at(i).getType() == allReactions.at(j).getType())
                                {
                                    if(allReactions.at(i).getSpecies_I() == allReactions.at(j).getSpecies_I())
                                    {
                                        if((allReactions.at(i).getSpecies_II() == allReactions.at(j).getSpecies_II() &&
                                            allReactions.at(i).getSpecies_III() == allReactions.at(j).getSpecies_III()) ||
                                            (allReactions.at(i).getSpecies_II() == allReactions.at(j).getSpecies_III() &&
                                             allReactions.at(i).getSpecies_III() == allReactions.at(j).getSpecies_II()))
                                        {
                                            flagControl = false;
                                            cout << endl << "\t\t\tERROR: Reaction " << allReactions.at(i).getID() << " is a duplicate of reaction " << allReactions.at(j).getID();
                                            break;
                                        }
                                    } // end if(allReactions.at(i).getSpecies_I() == allReactions.at(j).getSpecies_I())
                                } // end if(allReactions.at(i).getType() == allReactions.at(j).getType())
                            }catch(exception&e){
                                cout << "allReactions.at(i).get..." << endl;
                                cout << "Vectorsize "<<allReactions.size()<<" - position " << i << endl;
                                cerr << "exceptioncaught:"<<e.what()<<endl;
                                ExitWithError("structureCoherenceCheckUp","exceptionerrorthrown");
                           }
                        } // end if( i != j)
                    } // end for(acs_longInt j = 0; j < getNumberOfReactions(); j++)
                } // end for(acs_longInt i = 0; i < getNumberOfReactions() - 1; i++)
                cout << endl << "\t\t\t|- Ratio between cleavage and condensation reactions:" << tmpClConRatio / getNumberOfReactions() * 100;

            } // end if(flagControl)


            // ===================================
            // IF THERE ARE CATALYSIS
            // ===================================

            if(flagControl)
            {
                if(debugLevel >= RUNNING_VERSION)
                {
                    // PREVIOUS CHECK
                    cout << endl
                    << "\t\t\t|- Id Progression... OK!" << endl
                    << "\t\t\t|- No Double reactions... OK!" << endl
                    << "\t\t\t|- Substrates are not involved in reactions... OK!" << endl
                    << "\t\t\t|- Reaction coherence... OK!" << endl;
                    if (energy == 1) {
                            cout << "\t\t\t|- ENERGY TYPE control... OK!" << endl;
                    }
                    // CATALYSIS STRUCTURE CHECK
                    cout << "\t|- CATALYSIS LAYER STRUCTURE" << endl;
                    cout << "\t\t|- Searching for duplicate, incorrect ID progression... ";
                }
                for(acs_longInt i = 0; i < getNumberOfCatalysis() - 1; i++)
                {
                    // NO COMPLEX CATALYST CONTROL
                    if(allSpecies.at(allCatalysis.at(i).getCat()).getComplexCutPnt() > 0)
                    {
                        //A COMPLEX CANNOT CATALYZE ANY REACTION
                        flagControl = false;
                        cout << "Catalysis number " << i << ": A complex cannot catalyse any reaction, catalyst " << allCatalysis.at(i).getCat() << " is a complex!!! " << endl;
                        break;
                    }
                    // NO DOUBLE ENTRIES CONTROL
                    for(acs_longInt j= 0; j < getNumberOfCatalysis(); j++)
                    {
                        if(i != j) // A Species is definitely equal to itself
                        {
                            if(allCatalysis.at(i).getCat() == allCatalysis.at(j).getCat())
                            {
                                if(allCatalysis.at(i).getReactionID() == allCatalysis.at(j).getReactionID())
                                {
                                    flagControl = false;
                                    cout << endl << "\t\t\tERROR: Catalysis " << allCatalysis.at(i).getCatId() << " is a duplicate of catalysis " << allCatalysis.at(j).getCatId()  << endl;
                                    break;
                                }
                            }
                        }
                    }

                    // PROGRESSION CONTROL
                    if(allCatalysis.at(i).getCatId() != i)
                    {
                        flagControl = false;
                        cout << endl << "\t\t\tERROR: CATALYSIS ID progression in not right: ID " << allCatalysis.at(i).getCatId() <<
                        " could be equal to " << i << endl;
                        //break;
                    }

                    // NOT INVERSE REACTIONS CONTROL
                    if(allReactions.at(allCatalysis.at(i).getReactionID()).getType() == CLEAVAGE)
                    { // CLEAVAGE
                        if(!notInverseReactionAlreadyCatalyzed(CLEAVAGE,
                                                               allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I(),
                                                               allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II()))
                        {
                                flagControl = false;
                                cout << endl << "\t\t\tERROR: Rct Type: " <<  CLEAVAGE  <<
                                " - Catalisys: " << i << " - Catalyst: " <<  allCatalysis.at(i).getCat() <<
                                " - S1: " << allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I() <<
                                " - S2: " << allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II() <<
                                " - Reaction " << allCatalysis.at(i).getReactionID() << endl << "\t\t\t\t" <<
                                ": Both forward and backward reaction are catalyzed!!!" << endl <<
                                "\t\t\t\t" << "-----------------------------------------------------" << endl;
                                //break;
                        }
                        // NO SELF-CATALYSIS CONTROL
//					if(allCatalysis.at(i).getCat() < (acs_longInt)firingDisk.size())
//					{
//						if((allCatalysis.at(i).getCat() == allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II()) ||
//						   (allCatalysis.at(i).getCat() == allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_III()))
//						{
//							cout << "WARNING*** CLEAVAGE -> Species " << allCatalysis.at(i).getCatId() << " is a firing disk species and it cannot catalize the formation of itself: cat ID " 
//							     << i << " - Rct ID " << allCatalysis.at(i).getReactionID() << endl;
//							//flagControl = false;
//						}
//					}
                    }else{ // CONDENSATION
                            if(!notInverseReactionAlreadyCatalyzed(CONDENSATION,
                                                   allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I(),
                                                   allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II()))
                            {
                                    flagControl = false;
                                    cout << endl << "\t\t\tERROR: Rct Type: " << CONDENSATION <<
                                    " - Catalisys: " << i << " - Catalyst: " <<  allCatalysis.at(i).getCat() <<
                                    " - S1: " << allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I() <<
                                    " - S2: " << allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_II() <<
                                    " - Reaction " << allCatalysis.at(i).getReactionID() << endl << "\t\t\t\t" <<
                                    ": Both forward and backward reaction are catalyzed!!!" << endl <<
                                    "\t\t\t\t" << "-----------------------------------------------------" << endl;
                                    //break;
                            }
                            // NO SELF-CATALYSIS CONTROL
//					if(allCatalysis.at(i).getCat() < (acs_longInt)firingDisk.size())
//					{
//						if((allCatalysis.at(i).getCat() == allReactions.at(allCatalysis.at(i).getReactionID()).getSpecies_I()))
//						{
//							cout << "WARNING*** CONDENSATION -> Species " << allCatalysis.at(i).getCatId() << " is a firing disk species and it cannot catalize the formation of itself: cat ID " 
//							<< i << " - Rct ID " << allCatalysis.at(i).getReactionID() << endl;
//							//flagControl = false;
//						}
//					} // end if(allCatalysis.at(i).getCatId() < (acs_longInt)firingDisk.size())		 			
                    } // end if(allReactions.at(allCatalysis.at(i).getReactionID()).getType() == CLEAVAGE)
                } // end for(acs_longInt i = 0; i < getNumberOfCatalysis() - 1; i++)
            } // end if(flagControl)
	}else{
		cout << "NO REACTIONS...";
	}
	
	if(flagControl)
	{
		if(debugLevel >= RUNNING_VERSION)
		{
			cout << endl
				<< "\t\t\t|- No doubles in catalysis structures... OK!" << endl
				<< "\t\t\t|- Id Progression... OK!" << endl
				<< "\t\t\t|- No inverse reactions are catalyzed by the same species... OK!" << endl
				<< "\t\t\t|- Reactions not catalyzed by complexes... OK!" << endl
				<< "\t\t\t|- No Autocatalysis into the firing disk... OK!" << endl;
		}
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::structureCoherenceCheckUp end" << endl;
	
	return flagControl;

}

/**
 Check if the reaction catalyze both one reaction and the inverted one
 @version 1.0
 */
bool environment::notInverseReactionAlreadyCatalyzed(acs_int tmpRct, acs_longInt tmpID_I, acs_longInt tmpID_II)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::notInverseReactionAlreadyCatalyzed start" << endl;
	
	// BOOLEAN VARIABLE CONTROL
	bool reactionFlag = true;
	
	int tmpRevRctType = CLEAVAGE;
	if(tmpRct == CLEAVAGE)
		tmpRevRctType = CONDENSATION;
	
	for(acs_int tmpMMRctId = 0; tmpMMRctId < (acs_longInt)allReactions.size(); tmpMMRctId++)
	{
            try{
                if(allReactions.at(tmpMMRctId).getType() == (unsigned)tmpRevRctType)
                {
                    //IF THE INVERTED REACTION IS ALREADY CATALYSED
                    if((allReactions.at(tmpMMRctId).getSpecies_I() == tmpID_I) &&
                       (allReactions.at(tmpMMRctId).getSpecies_II() == tmpID_II))
                    {
                        if(debugLevel >= SMALL_DEBUG)
                        {
                            cout << endl <<
                            "\t\t\t *** WARNING: The system is trying to create a reverse reaction of type " << tmpRct <<
                            " with S1 " << tmpID_I << " and S2 " << tmpID_II << endl <<
                            "\t\t\t\t but in the system is already present the reverse reaction with ID " << tmpMMRctId <<
                            " of type " << allReactions.at(tmpMMRctId).getType() <<
                            " with S1 " << allReactions.at(tmpMMRctId).getSpecies_I() <<
                            " and S2 " << allReactions.at(tmpMMRctId).getSpecies_II() << endl;
                        }
                        reactionFlag = false;
                        break;
                    }
                }
            }catch(exception&e){
                cout << "allReactions.at(tmpMMRctId).getType() == (unsigned)tmpRevRctType)" << endl;
                cout << "Vectorsize "<<allSpecies.size()<<" - position " << tmpMMRctId << endl;
                cerr << "exceptioncaught:"<<e.what()<<endl;
                ExitWithError("notInverseReactionAlreadyCatalyzed","exceptionerrorthrown");
           }
	}	
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::notInverseReactionAlreadyCatalyzed end" << endl;

	return reactionFlag;
}

/**
  Return TRUE if there are sufficient molecules for the reaction. It is used for the reaction in which catalyst and substrate are the same
  molecules
  @version 1.0
  @date 2011.07.25
  @param tmpMI
  @param tmpMII
  @param tmpQI
  @param tmpQII
  */
bool environment::checkAvailability(acs_longInt tmpMI, acs_longInt tmpMII, acs_longInt tmpQI, acs_longInt tmpQII)
{
    bool flagVar = false;
    if(tmpMI == tmpMII)
    {
        if(debugLevel == HIGH_DEBUG)
        {
            cout << "\t\t|- Catalyst and Substrate are the same, ID#" << tmpMI << " " << tmpMII << endl;
            cout << "\t\t|- Amounts --> " << tmpQI << " " << tmpQII << endl;
        }
        if(tmpQI != tmpQII)
            ExitWithError("checkAvailability", "!!! The species are the same, ALSO THE QUANTITIES MUST BE THE SAME");
        if(tmpQI >= 2)
            flagVar = true;
    }else{
        flagVar = true;
    }


    return flagVar;
}

/**
 Perform all the gillespie algorithm procedure
 @version 1.5
 @date 2011.02.12
 @param tmpRndDoubleGen random numbers generator
 @param tmpTimeElapsed Computation time elapsed from the T0
 @param tmpActGEN actual generation
 @param tmpActSIM actual simulation
 @param tmpActSTEP actual step (reaction)
 @param tmpStoringPath path where results are stored
*/
bool environment::performGillespieComputation(MTRand& tmpRndDoubleGen, QTime& tmpTimeElapsed, acs_int tmpActGEN, acs_int tmpActSIM, acs_int tmpActSTEP, QString tmpStoringPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::performGillespieComputation start" << endl;
	
	bool flagControl = true; //Check flag
	bool sameSpecies = false; // true if I'm computing the score of a reaction involving the same species as catalyst and substrate
	acs_double temp_score; // Gillespie score
        gillespieTotalScore = 0; // Initialize (or reset) the overall Gillespie score
        gillespieNewSpeciesScore = 0; // Initialize (or reset) the sum of the Gillespie scores creating new species
        ratioBetweenNewGillTotGill = 0;
        reverseReactionsGillScore = 0; // the sum of the gillespie scores related to the reverse reactions
        ratioBetweenReverseAndTotalScore = 0; // Ratio between the reverse reaction scores and all the reaction scores
	acs_longInt temp_mol_I; // temp_mol_I II III and IV will contain the molecules IDs according to the different reactions
	acs_longInt temp_mol_II;
	acs_longInt temp_mol_III;
	acs_longInt temp_mol_IV;
	
	acs_longInt temp_substrateAmount; // These variables will contain the different amounts of the different species
	acs_longInt temp_cpxAmount;
	
	acs_longInt temp_catAmount_charged;
	acs_longInt temp_catAmount_NotCharged;
	acs_longInt temp_catAmount_TOT;
	
	acs_longInt temp_substrateAmount_charged;
	acs_longInt temp_substrateAmount_NotCharged;
	acs_longInt temp_substrateAmount_TOT;
	
	acs_int temp_rctType; // Reaction type (condensation, endo_condensation, complex_formation, endo_complex_formation, cleavage, endo_cleavage)
	acs_longInt temp_reactionID; 
	acs_longInt temp_catalysisID;
	acs_longInt reaction_u; // This variable will contain the ID of the reaction selected amond all the possible one contained in the Gillespie algorithm
	acs_double tempTime; // Temporary Delta T
	acs_longInt tmpCatalyst_ID; //temporary catalyst produced degrading the complex to searching for the substrate in condensation reaction
	acs_longInt tmpSubstrate_ID; //temporary substrate produced degrading the complex to searching for the second substrate of the condensation reaction
	acs_double tmpDeltaT; // Time interval between two successive generation

	string nrgBooleanFunction = ""; // This string contains the energetic boolean function of the selected reaction
	
	// TRANSFORM KINETIC CONSTANTS IN GILLESPIE KINETIC CONSTANTS (THEY ARE RESCALED ACCORDING TO THE VOLUME)
	
	/* ------------------------------------------\
	// GILLESPIE STRUCTURE CREATION				 ||==----
	// ------------------------------------------*/
	
	// FOR EACH SINGLE SPECIES ALL POSSIBLE REACTIONS INVOLVING IT IS COMPUTED.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
	
	// Initialize Time for the Gillespie Algorithm
	gillespiePartialTimer.start();
	
	for(acs_longInt mid = 0; mid < (acs_longInt)allSpecies.size(); mid++)
	{
	
		sameSpecies = false; // This flag will be true is a second order reaction will involve the same species 
		
	// MID IS THE CATALYST
		
	// UPDATE SPECIES AGE .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
		
		if((allSpecies.at(mid).getAmount() > 0) && (allSpecies.at(mid).getComplexCutPnt() == 0))
		{
                    // tmpActSTEP is the simulation step
                    if(tmpActSTEP > 2)
                    {
                        allSpecies.at(mid).setNewAge(reactionsTime.at((reactionsTime.size() - 1)) - reactionsTime.at((reactionsTime.size() - 2)));
                    }
		}else{
                    allSpecies.at(mid).setNewAge(0); // IF THE SPECIES IS DEAD THE AGE OF LAST DEATH REMAINS
		}
		
		if((allSpecies.at(mid).getAmount() > 0) && (allSpecies.at(mid).getSolubility() == SOLUBLE)) // If there are some molecule belonging to this species
		{
			
	// DISSOCIATION IF COMPLEX .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
			
                    if(allSpecies.at(mid).getComplexCutPnt() > 0)
                    {

                        // In this step all the molecules are taken into account. Selection between loaded and unloaded type will be performed
                        // in the reaction perform process according to the numerosity of each category
                        temp_score = allSpecies.at(mid).getAmount() * allSpecies.at(mid).getComplexDegEnh();
                        temp_mol_I = mid;
                        temp_mol_II = tmpCatalyst_ID = allSpecies.at(mid).getCatalyst_ID();	// Recover catalyst ID from the complex
                        temp_mol_III = tmpSubstrate_ID = allSpecies.at(mid).getSubstrate_ID();	// Recover substrate ID from the complex
                        temp_mol_IV = 0;
                        temp_rctType = COMPLEXDEGRADATION;
                        temp_reactionID = 0;
                        temp_catalysisID = 0;

                        if(temp_score > 0) // If score is grater than one
                        {
                            if(debugLevel >= MEDIUM_DEBUG)
                                cout << "\t\t\t|- COMPLEX DISSOCIATION: " << temp_score << endl;

                            allGillespieScores.push_back(gillespie((acs_longInt)allGillespieScores.size(), temp_rctType,
                                                       temp_score, temp_mol_I, temp_mol_II, temp_mol_III,
                                                       temp_mol_IV, temp_reactionID, temp_catalysisID));
                            gillespieTotalScore += temp_score;
                            gillespieCumulativeStepScoreList.push_back(gillespieTotalScore);
                        }
                    }
			
	 // IF THERE ARE REACTIONS *********************************************************************************************************
			
                    if((acs_longInt)allCatalysis.size() > 0)
                    {
                        for(acs_longInt idCat = 0; idCat < (acs_longInt)allCatalysis.size(); idCat++)
                        {
                            if(allCatalysis.at(idCat).getCat() == mid)
                            {

                                // Retrive the energetic boolean function of the reaction
                                try{
                                    nrgBooleanFunction = dec2bin(allReactions.at(allCatalysis.at(idCat).getReactionID()).getEnergyType());
                                }catch(exception&e){
                                    cout << "nrgBooleanFunction = dec2bin(allReactions.at(allCatalysis.at(idCat).getReactionID()).getEnergyType());" << endl;
                                    cout << "Vectorsize "<<allReactions.size() << " - position " << allCatalysis.at(idCat).getReactionID() << endl;
                                    cerr << "exceptioncaught:" << e.what() << endl;
                                    ExitWithError("performGillespieComputation","exceptionerrorthrown");
                               }

    //\-- CLEAVAGE .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

                                //IF CLEAVAGE REACTION (if reverse reactions are enabled reaction is computed as well)
                               // TRY HAS BEEN ALREADY USED
                                if((allReactions.at(allCatalysis.at(idCat).getReactionID()).getType() == CLEAVAGE) || (reverseReactions == true))
                                {
                                    temp_mol_I = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_I();     // SUBSTRATE
                                    temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II();   // PRODUCT 1
                                    temp_mol_III = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_III(); // PRODUCT 2
                                    temp_mol_IV = mid;	// CATALYST
                                    temp_reactionID = allCatalysis.at(idCat).getReactionID(); // REACTION ID
                                    temp_catalysisID = idCat;

                                    // Compute the overall number of molecules for the species involved
                                    temp_catAmount_TOT = allSpecies.at(mid).getAmount();
                                    temp_catAmount_charged = allSpecies.at(mid).getChargeMols();
                                    temp_catAmount_NotCharged = allSpecies.at(mid).getNOTchargeMols();

                                   try{
                                        temp_substrateAmount_TOT = allSpecies.at(temp_mol_I).getAmount();
                                        temp_substrateAmount_charged = allSpecies.at(temp_mol_I).getChargeMols();
                                        temp_substrateAmount_NotCharged = allSpecies.at(temp_mol_I).getNOTchargeMols();
                                    }catch(exception&e){
                                        cout << "temp_substrateAmount_TOT = allSpecies.at(temp_mol_I).getAmount();" << endl;
                                        cout << "Vectorsize "<< allSpecies.size() << " - position " << temp_mol_I << endl;
                                        cerr << "exceptioncaught:" << e.what() << endl;
                                        ExitWithError("performGillespieComputation","exceptionerrorthrown");
                                   }

            // Gillespie record creation according to the energy configuration
                                    if(nrgBoolFlag == ENERGYBASED)
                                    {

                                        // CATALYST NOT LOADED, SUBSTRATE LOADED (- -)
                                        if(nrgBooleanFunction[11] == TRUENRG)
                                        if(checkAvailability(mid, temp_mol_I, temp_catAmount_NotCharged, temp_substrateAmount_NotCharged))
                                            performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_NotCharged, mid, temp_mol_I, idCat, CLEAVAGE,
                                                   temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                   true);

                                        // CATALYST NOT LOADED, SUBSTRATE LOADED (- +)
                                        if(nrgBooleanFunction[10] == TRUENRG)
                                                performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_charged, mid, temp_mol_I, idCat, ENDO_CLEAVAGE,
                                                                                                                   temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, SUBSTRATELOAD, temp_reactionID,
                                                                                                                   false);
                                        // CATALYST NOT LOADED, SUBSTRATE LOADED (+ -)
                                        if(nrgBooleanFunction[9] == TRUENRG)
                                                performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_NotCharged, mid, temp_mol_I, idCat, ENDO_CLEAVAGE,
                                                                                                                   temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, CATALYSTLOAD, temp_reactionID,
                                                                                                                   false);

                                        // CATALYST NOT LOADED, SUBSTRATE LOADED (+ +)
                                        if(nrgBooleanFunction[8] == TRUENRG)
                                            if(checkAvailability(mid, temp_mol_I, temp_catAmount_charged, temp_substrateAmount_charged))
                                                performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_charged, mid, temp_mol_I, idCat, ENDO_CLEAVAGE,
                                                 temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, BOTHLOAD, temp_reactionID,
                                                   true);
                                    }else{
                                            // CATALYST NOT LOADED, SUBSTRATE NOT LOADED
                                        if(checkAvailability(mid, temp_mol_I, temp_catAmount_TOT, temp_substrateAmount_TOT))
                                            performSingleGilleSpieIntroduction(temp_catAmount_TOT, temp_substrateAmount_TOT, mid, temp_mol_I, idCat, CLEAVAGE,
                                                                               temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                                               true);
                                    }
                                } // end getType() == CLEAVAGE

    //\-- OVERALL CONDENSATION .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

                                    // IF THIS IS A CONDENSATION REACTION (if reverse reactions are enabled reaction is comuputed as well)
                                    if((allReactions.at(allCatalysis.at(idCat).getReactionID()).getType() == CONDENSATION) || (reverseReactions == true))
                                    {

            //\-- COMPLEX CREATION	.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

                                        temp_mol_I = mid; // Catalyst
                                        temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II(); // First substrate
                                        temp_mol_III = 0; // This variable contains the number of energized molecules (0 ++ 2 +- 4 -+ 6 --)
                                        temp_mol_IV = 0;
                                        temp_reactionID = allCatalysis.at(idCat).getReactionID();
                                        temp_catalysisID = idCat;

                //\-- FIRST AND SECOND SUBSTRATE  -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

                                        // Compute the overall number of molecules for the species involved
                                        temp_catAmount_TOT = allSpecies.at(mid).getAmount();
                                        temp_catAmount_charged = allSpecies.at(mid).getChargeMols();
                                        temp_catAmount_NotCharged = allSpecies.at(mid).getNOTchargeMols();

                                        temp_substrateAmount_TOT = allSpecies.at(temp_mol_II).getAmount();
                                        temp_substrateAmount_charged = allSpecies.at(temp_mol_II).getChargeMols();
                                        temp_substrateAmount_NotCharged = allSpecies.at(temp_mol_II).getNOTchargeMols();

                                        if(nrgBoolFlag == ENERGYBASED)
                                        {

                                            // CATALYST LOADED, SUBSTRATE LOADED (+ + ...)
                                            if((nrgBooleanFunction[0] == TRUENRG) || (nrgBooleanFunction[1] == TRUENRG))
                                            if(checkAvailability(mid, temp_mol_II, temp_catAmount_charged, temp_substrateAmount_charged))
                                                performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_charged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                        temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, BOTHLOAD, temp_reactionID,
                                                        true);

                                            // CATALYST LOADED, SUBSTRATE NOT LOADED (+ - ...)
                                            if((nrgBooleanFunction[2] == TRUENRG) || (nrgBooleanFunction[3] == TRUENRG))
                                                    performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_NotCharged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                                                                                            temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, CATALYSTLOAD, temp_reactionID,
                                                                                                                            false);

                                            // CATALYST NOT LOADED, SUBSTRATE LOADED (- + ...)
                                            if((nrgBooleanFunction[4] == TRUENRG) || (nrgBooleanFunction[5] == TRUENRG))
                                                    performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_charged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                                                                                            temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, SUBSTRATELOAD, temp_reactionID,
                                                                                                                            false);

                                            // CATALYST NOT LOADED, SUBSTRATE NOT LOADED (- - ...)
                                            if((nrgBooleanFunction[6] == TRUENRG) || (nrgBooleanFunction[7] == TRUENRG))
                                                if(checkAvailability(mid, temp_mol_II, temp_catAmount_NotCharged, temp_substrateAmount_NotCharged))
                                                    performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_NotCharged, mid, temp_mol_II, idCat, COMPLEXFORMATION,
                                                        temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                        true);

                                            // SECOND SUBSTRATE
                                            if(complexFormationSymmetry)
                                            {
                                                    temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_III(); // Second Substrate
                                                                            temp_substrateAmount_charged = allSpecies.at(temp_mol_II).getChargeMols();
                                                                            temp_substrateAmount_NotCharged = allSpecies.at(temp_mol_II).getNOTchargeMols();

                                                    // CATALYST LOADED, SUBSTRATE LOADED (+ + ...)
                                                    if((nrgBooleanFunction[0] == TRUENRG) || (nrgBooleanFunction[2] == TRUENRG))
                                                    if(checkAvailability(mid, temp_mol_II, temp_catAmount_charged, temp_substrateAmount_charged))
                                                        performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_charged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                            temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, BOTHLOAD, temp_reactionID,
                                                            true);

                                                    // CATALYST LOADED, SUBSTRATE NOT LOADED (+ - ...)
                                                    if((nrgBooleanFunction[1] == TRUENRG) || (nrgBooleanFunction[3] == TRUENRG))
                                                            performSingleGilleSpieIntroduction(temp_catAmount_charged, temp_substrateAmount_NotCharged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                                                                                                    temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, CATALYSTLOAD, temp_reactionID,
                                                                                                                                    false);

                                                    // CATALYST NOT LOADED, SUBSTRATE LOADED (- + ...)
                                                    if((nrgBooleanFunction[4] == TRUENRG) || (nrgBooleanFunction[6] == TRUENRG))
                                                            performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_charged, mid, temp_mol_II, idCat, ENDO_COMPLEXFORMATION,
                                                                                                                                    temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, SUBSTRATELOAD, temp_reactionID,
                                                                                                                                    false);

                                                    // CATALYST NOT LOADED, SUBSTRATE NOT LOADED (- - ...)
                                                    if((nrgBooleanFunction[5] == TRUENRG) || (nrgBooleanFunction[7] == TRUENRG))
                                                    if(checkAvailability(mid, temp_mol_II, temp_catAmount_NotCharged, temp_substrateAmount_NotCharged))
                                                         performSingleGilleSpieIntroduction(temp_catAmount_NotCharged, temp_substrateAmount_NotCharged, mid, temp_mol_II, idCat, COMPLEXFORMATION,
                                                            temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                            true);
                                            }

                                        }else{ // NO ENERGY
                                           if(checkAvailability(mid, temp_mol_II, temp_catAmount_TOT, temp_substrateAmount_TOT))
                                                performSingleGilleSpieIntroduction(temp_catAmount_TOT, temp_substrateAmount_TOT, mid, temp_mol_II, idCat, COMPLEXFORMATION,
                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                       true);
                                            if(complexFormationSymmetry)
                                            {
                                                //Change substrate
                                                temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_III(); // First substrate
                                                   temp_substrateAmount_TOT = allSpecies.at(temp_mol_II).getAmount();
                                                   if(checkAvailability(mid, temp_mol_II, temp_catAmount_TOT, temp_substrateAmount_TOT))
                                                        performSingleGilleSpieIntroduction(temp_catAmount_TOT, temp_substrateAmount_TOT, mid, temp_mol_II, idCat, COMPLEXFORMATION,
                                                   temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                   true);
                                            } // end if(complexFormationSymmetry)
                                        } // end if(nrgBoolFlag == ENERGYBASED)
                                    } // end if(allReactions.at(allCatalysis.at(idCat).getReactionID()).getType() == CONDENSATION)
                            } // end if(allCatalysis.at(idCat).getCat() == mid)

                        //\-- IF THE SPECIES IS A COMPLEX CONDENSATION TOT .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

                            if(allSpecies.at(mid).getComplexCutPnt() > 0) // If the species is a complex the second substrate could be bound
                            {

                                    // Recover catalyst and substrate ID from the complex
                                    tmpCatalyst_ID = allSpecies.at(mid).getCatalyst_ID();
                                    tmpSubstrate_ID = allSpecies.at(mid).getSubstrate_ID();

                                    // Searching for the reactions catalzed by the catalyst
                                    if(allCatalysis.at(idCat).getCat() == tmpCatalyst_ID)
                                    {
                                            // If there is searching for the reactions catalyzed containing the substrate
                                            // Check whether the temporary catalyst catalyse a condensation reaction containing the temporary substrate as a first or second molecule
                                            // WHETHER IT IS A CONDENSATION REACTION

                                        if((allReactions.at(allCatalysis.at(idCat).getReactionID()).getType() == CONDENSATION) || (reverseReactions == true))
                                            {

                                            // CONDENSATION 1 ----------------------------------------------------------------------------------------------------------------------------

                                                    // First substrate
                                                    if(allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II() == tmpSubstrate_ID)
                                                    {
                                                            // Assign species to the temp variables
                                                            temp_mol_I = allCatalysis.at(idCat).getCat(); //catalyst
                                                            temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_III(); // second substrate
                                                            temp_mol_III = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_I(); // Product
                                                            temp_mol_IV = mid; // Complex
                                                            temp_reactionID = allCatalysis.at(idCat).getReactionID(); // reaction ID
                                                            temp_catalysisID = idCat; // Catalysis ID
                                                            temp_rctType = CONDENSATION; // reaction type

                                                            if(nrgBoolFlag == ENERGYBASED)
                                                            {
                                                                    // COMPLEX CHARGED - SECOND SUBSTRATE NOT CHARGED
                                                                    if((nrgBooleanFunction[1] == TRUENRG) || (nrgBooleanFunction[3] == TRUENRG) || (nrgBooleanFunction[5] == TRUENRG))
                                                                    {
                                                                        // Compute the total amount of complexes and second substrates
                                                                        temp_cpxAmount = allSpecies.at(mid).getChargeMols();
                                                                        temp_substrateAmount = allSpecies.at(temp_mol_II).getNOTchargeMols();
                                                                        performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                           temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, COMPLEXLOAD, temp_reactionID,
                                                                                                           false);
                                                                    }

                                                                    // COMPLEX NOT CHARGED - SECOND SUBSTRATE CHARGED
                                                                    if(nrgBooleanFunction[6] == TRUENRG)
                                                                    {
                                                                        // Compute the total amount of complexes and second substrates
                                                                        temp_cpxAmount = allSpecies.at(mid).getNOTchargeMols();
                                                                        temp_substrateAmount = allSpecies.at(temp_mol_II).getChargeMols();
                                                                        performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                           temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, SUBSTRATELOAD, temp_reactionID,
                                                                                                           false);
}

                                                                    // COMPLEX CHARGED - SECOND SUBSTRATE CHARGED
                                                                    if((nrgBooleanFunction[0] == TRUENRG) || (nrgBooleanFunction[2] == TRUENRG) || (nrgBooleanFunction[4] == TRUENRG))
                                                                    {
                                                                        // Compute the total amount of complexes and second substrates
                                                                        temp_cpxAmount = allSpecies.at(mid).getChargeMols();
                                                                        temp_substrateAmount = allSpecies.at(temp_mol_II).getChargeMols();
                                                                        performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                           temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, BOTHLOAD, temp_reactionID,
                                                                                                           false);
                                                                    }

                                                                    // COMPLEX NOT CHARGED - SECOND SUBSTRATE NOT CHARGED (ONLY IF CONDENSATION ESOERGONIC)
                                                                    if(nrgBooleanFunction[7] == TRUENRG)
                                                                    {
                                                                        // Compute the total amount of complexes and second substrates
                                                                        temp_cpxAmount = allSpecies.at(mid).getNOTchargeMols();
                                                                        temp_substrateAmount = allSpecies.at(temp_mol_II).getNOTchargeMols();
                                                                        performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, CONDENSATION,
                                                                                                           temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                                                                           false);
}
                                                            }else{ // NO ENERGY
                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getAmount();
                                                                    temp_substrateAmount_TOT = allSpecies.at(temp_mol_II).getAmount();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount_TOT, mid, temp_mol_II, idCat, CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                                                                       false);
                                                            } // end if(nrgBoolFlag == ENERGYBASED)
                                                    } // if(allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II() == tmpSubstrate_ID)

    // CONDENSATION 2 -----------------------------------------------------------------------------------------------------------------------------

                                                    // Second substrate
                                                    if((allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_III() == tmpSubstrate_ID) && (complexFormationSymmetry == true))
                                                    {
                                                            // Assign species to the temp variables
                                                            temp_mol_I = allCatalysis.at(idCat).getCat(); //catalyst
                                                            temp_mol_II = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II(); // second substrate
                                                            temp_mol_III = allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_I(); // Product
                                                            temp_mol_IV = mid; // Complex
                                                            temp_reactionID = allCatalysis.at(idCat).getReactionID(); // reaction ID
                                                            temp_catalysisID = idCat; // Catalysis ID
                                                            temp_rctType = CONDENSATION; // reaction type

                                                            if(nrgBoolFlag == ENERGYBASED)
                                                            {
                                                                // COMPLEX CHARGED - SECOND SUBSTRATE NOT CHARGED
                                                                if((nrgBooleanFunction[2] == TRUENRG) || (nrgBooleanFunction[3] == TRUENRG) || (nrgBooleanFunction[6] == TRUENRG))
                                                                {
                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getChargeMols();
                                                                    temp_substrateAmount = allSpecies.at(temp_mol_II).getNOTchargeMols();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, COMPLEXLOAD, temp_reactionID,
                                                                                                       false);
                                                                }

                                                                // COMPLEX NOT CHARGED - SECOND SUBSTRATE CHARGED
                                                                if(nrgBooleanFunction[5] == TRUENRG)
                                                                {
                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getNOTchargeMols();
                                                                    temp_substrateAmount = allSpecies.at(temp_mol_II).getChargeMols();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, SUBSTRATELOAD, temp_reactionID,
                                                                                                       false);
                                                                }

                                                                // COMPLEX CHARGED - SECOND SUBSTRATE CHARGED
                                                                if((nrgBooleanFunction[0] == TRUENRG) || (nrgBooleanFunction[1] == TRUENRG) || (nrgBooleanFunction[4] == TRUENRG))
                                                                {
                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getChargeMols();
                                                                    temp_substrateAmount = allSpecies.at(temp_mol_II).getChargeMols();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, ENDO_CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, BOTHLOAD, temp_reactionID,
                                                                                                       false);
                                                                }

                                                                // COMPLEX NOT CHARGED - SECOND SUBSTRATE NOT CHARGED (ONLY IF CONDENSATION ESOERGONIC)
                                                                if(nrgBooleanFunction[7] == TRUENRG)
                                                                {
                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getNOTchargeMols();
                                                                    temp_substrateAmount = allSpecies.at(temp_mol_II).getNOTchargeMols();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount, mid, temp_mol_II, idCat, CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                                                                       false);
                                                                }
                                                            }else{

                                                                    // Compute the total amount of complexes and second substrates
                                                                    temp_cpxAmount = allSpecies.at(mid).getAmount();
                                                                    temp_substrateAmount_TOT = allSpecies.at(temp_mol_II).getAmount();
                                                                    performSingleGilleSpieIntroduction(temp_cpxAmount, temp_substrateAmount_TOT, mid, temp_mol_II, idCat, CONDENSATION,
                                                                                                       temp_mol_I, temp_mol_II, temp_mol_III, temp_mol_IV, NOTHINGLOAD, temp_reactionID,
                                                                                                       false);
                                                            } // end if(nrgBoolFlag == ENERGYBASED)
                                                    } // if(allReactions.at(allCatalysis.at(idCat).getReactionID()).getSpecies_II() == tmpSubstrate_ID)
                                            } // end if((allReactions.at(allCatalysis.at(idCat).getReactionID()).getType() == CONDENSATION) || (reverseReactions == true))
                                    } // end if(allCatalysis.at(idCat).getCat() == tmpCatalyst_ID)
                            } // end if complex
                        } // end for all catalysis
                    } // end if if((acs_longInt)allCatalysis.size() > 0)
		} //end if total amount greater than 0
	} // end for each species
	
	// Store gillespie computational time and start performReaction Times
	gillespiePartialTimes.push_back(gillespiePartialTimer.elapsed());
	performReactionPartialTimer.start();

	bool goReaction = true;
	acs_double minimalTimeForOneMols = 1 / (influx_rate * AVO);
	if((acs_longInt)allGillespieScores.size() > 0)
	{
            if(debugLevel == SMALL_DEBUG) printGillespieStructure();

            if((acs_longInt)allGillespieScores.size() == 1)
            {
                reaction_u = 0;
            }else{
                    //cout << allGillespieScores.size() << " " << gillespieCumulativeStepScoreList.size() << endl;
                reaction_u = returnSelectionIdFromAWeightProbVector(gillespieCumulativeStepScoreList,
                                                           gillespieCumulativeStepScoreList.at((acs_longInt)gillespieCumulativeStepScoreList.size()-1),
                                                           tmpRndDoubleGen);
            }
            // CREATE RANDOM NUMBER TO COMPUTE THE TIME

            tmpDeltaT = ((1 / gillespieTotalScore) * log(1 / tmpRndDoubleGen()));

            // If deltaT is lower than 10 seconds, it is fixed to 10 second in order to continue the simulation
            if((tmpDeltaT) > MINIMALRCTTIMEMULTI*minimalTimeForOneMols)
            {
                    tmpDeltaT = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    goReaction = false;
            }

            if(debugLevel == SMALL_DEBUG)
                    cout << "gillespieTotalScore: " << gillespieTotalScore << " G size: " << allGillespieScores.size() << " delta T " << tmpDeltaT << endl;

            if(goReaction)
            {
                if(reactionsTime.size() > 0)
                {
                    tempTime = reactionsTime.at(reactionsTime.size() - 1) + tmpDeltaT;
                    timeSinceTheLastInFlux += tmpDeltaT;
                }else{
                    tempTime = 0.0;
                }
                reactionsTime.push_back(tempTime);
                setActualTime(tempTime);
                gillespieReactionsSelected.push_back(reaction_u);
                allTimes.push_back(tmpTimeElapsed.elapsed());

                // =^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^
                // PERFORM REACTION SELECTED BEFORE
                // ^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=^=
                // Compute Gillespie mean
                gillespieMean = gillespieTotalScore / (acs_longInt)allGillespieScores.size();
                if(gillespieTotalScore > 0){ratioBetweenNewGillTotGill = gillespieNewSpeciesScore / gillespieTotalScore;}else{ratioBetweenNewGillTotGill=0;}
                if(gillespieTotalScore > 0){ratioBetweenReverseAndTotalScore = reverseReactionsGillScore / gillespieTotalScore;}else{ratioBetweenReverseAndTotalScore=0;}
                if(!devStd()) // compute Gillespie score vector standard deviation
                     ExitWithError("devStd", "Problems during Gillespie score standard deviation computation");
                if(!entropy()) // compute Gillespie score vector entropy
                     ExitWithError("entropy", "Problems during Gillespie score entropy computation");

                if(!performReaction(reaction_u, tmpRndDoubleGen, tmpActGEN, tmpActSIM, tmpActSTEP, tmpStoringPath))
                                ExitWithError("performReaction", "Problems during the reaction computation");

            }else{
                    gillespieMean = 0;
                    gillespieSD = 0;
                    gillespieEntropy = 0;
                    if(reactionsTime.size() > 0)
                    {
                        tempTime = reactionsTime.at(reactionsTime.size() - 1) + MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                        timeSinceTheLastInFlux += MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                        tmpDeltaT = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    }else{
                        tempTime = 0.0;
                    }
                    reactionsTime.push_back(tempTime);
                    setActualTime(tempTime);
                    gillespieReactionsSelected.push_back(0);
                    allTimes.push_back(tmpTimeElapsed.elapsed());

                    if(debugLevel >= RUNNING_VERSION)
                                    cout << "\t\t\t|- NO REACTIONS AT THIS STEP T:" << tempTime << " G: " << allGillespieScores.size() << endl;
            }

        }else{ // If there are not possible reactions
            gillespieMean = 0;
            gillespieSD = 0;
            gillespieEntropy = 0;
            ratioBetweenNewGillTotGill = 0;
            if(reactionsTime.size() > 0)
            {
                    tempTime = reactionsTime.at(reactionsTime.size() - 1) + MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    timeSinceTheLastInFlux += MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    tmpDeltaT = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
            }else{
                    tempTime = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    timeSinceTheLastInFlux = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
                    tmpDeltaT = MINIMALRCTTIMEMULTI*minimalTimeForOneMols;
            }
            reactionsTime.push_back(tempTime);
            setActualTime(tempTime);
            gillespieReactionsSelected.push_back(0);
            allTimes.push_back(tmpTimeElapsed.elapsed());

            if(debugLevel >= RUNNING_VERSION)
                    cout << "\t\t\t|- NO REACTIONS AT THIS STEP" << endl;
        } // end if((acs_longInt)allGillespieScores.size() > 0)

        // Store perform reaction time and start remaining processes timer
        performReactionPartialTimes.push_back(performReactionPartialTimer.elapsed());
        remainingProcessesPartialTimer.start();

        // If the system is open influx and efflux processes are performed
        if(influx_rate > 0)
        {
    //     acs_double minimalTimeForOneMols = 1 / (influx_rate * AVO);
                if(debugLevel >= SMALL_DEBUG)
                {
                                cout << "\t\t\t|- REFILL --------" << endl;
                                cout << "\t\t\t\t|- Minimal Time for one molecule: " << minimalTimeForOneMols <<
                                                                " - Time since the last influx: " << timeSinceTheLastInFlux <<  endl;
                }
                // If the time interval betweem two successive influx is enough to introduce at least one new mol...
                if(timeSinceTheLastInFlux > minimalTimeForOneMols)
                {
                                if(debugLevel >= SMALL_DEBUG)
                                {
                                                cout << "\t\t\t\t|- Time: " << reactionsTime.at(reactionsTime.size() - 1)
                                                                 << " - Time needed for 1 molecule incoming: " << minimalTimeForOneMols
                                                         << " - Time Since The Last InFlux: " << timeSinceTheLastInFlux << endl;
                                }
                                // PERFORM REFILL !!!
                                if(performRefill(timeSinceTheLastInFlux, minimalTimeForOneMols, tmpRndDoubleGen))
                                                timeSinceTheLastInFlux = 0;
                }
                // PERFORM EFFLUX PROCESS
                performMoleculesEfflux(tmpDeltaT, tmpRndDoubleGen);
         }

    // Perform molecule charging
    if(energy == ENERGYBASED)
            performDETMoleculesCharging(tmpDeltaT, tmpRndDoubleGen);

    // COPY and CLEAN OF GILLESPIE STRUCTURES
    COPYOFallGillespieScores = allGillespieScores;
    allGillespieScores.clear();
    gillespieCumulativeStepScoreList.clear();

    // Store remaining processes time
    remainingProcessesPartialTimes.push_back(remainingProcessesPartialTimer.elapsed());

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::performGillespieComputation end" << endl;

    return flagControl;

}

/**
 Compute a single gillespie score according to the amount and peoprieties of the species involved
 @version 1.0
 @date 20110214
 */
acs_double environment::computeSinglGilScore(acs_longInt tmpAmountI, acs_double tmpDifI, acs_int tmpSolI,
                                             acs_longInt tmpAmountII, acs_double tmpDifII, acs_int tmpSolII, acs_double tmpK, bool tmpSameMol)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::computeSinglGilScore start" << endl;
	
	acs_double tempScore;
	
	if(tmpSameMol) //IF THE SPECIES ARE THE SAME
	{
		tempScore = ((tmpAmountI * tmpDifI * tmpSolI * (tmpAmountII - 1) * tmpDifII * tmpSolII) / 2) * (tmpK / (AVO * volume));
	}else{
		tempScore = tmpAmountI * tmpDifI * tmpSolI * tmpAmountII * tmpDifII * tmpSolII * tmpK / (AVO * volume);
	}
	
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::computeSinglGilScore end" << endl;
	
	return tempScore;
}

/**
 Compute and introduct a single Gillespie entry within the Gillespie Structure
 @version 1.0
 @date 20110222
 */
void environment::performSingleGilleSpieIntroduction(acs_longInt tmpAmountI, acs_longInt tmpAmountII, acs_longInt tmpIDI, acs_longInt tmpIDII, acs_longInt tmpIDCatalysis, acs_int tmp__rctType,
                                                        acs_longInt tmpMol_I, acs_longInt tmpMol_II, acs_longInt tmpMol_III, acs_longInt tmpMol_IV, acs_int tmp_NRGDirection, acs_longInt tmpRctID,
                                                        bool tmpSameSpeciesControl)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performSingleGilleSpieIntroduction start" << endl;
    bool temp_sameSpecies = false;
    acs_double temp_score; // Gillespie score
    acs_double temp_k_reaction; // k reaction

    if((tmpAmountI > 0) && (tmpAmountII > 0))
    {
        try{
            switch(tmp__rctType)
            {
                case CONDENSATION:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getKass();
                        break;
                case ENDO_CONDENSATION:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getKass();
                        break;
                case CLEAVAGE:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getKdiss();
                        break;
                case ENDO_CLEAVAGE:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getKdiss();
                        break;
                case COMPLEXFORMATION:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getK_cpx();
                        break;
                case ENDO_COMPLEXFORMATION:
                        temp_k_reaction = allCatalysis.at(tmpIDCatalysis).getK_cpx();
                        break;
            }
            if(tmpSameSpeciesControl)
            {
                if(tmpIDI == tmpIDII)
                        temp_sameSpecies = true;
            }
        }catch(exception&e){
            cout << "switch(tmp__rctType)" << endl;
            cout << "Vectorsize "<< allCatalysis.size() << " - position " << tmpIDCatalysis << endl;
            cerr << "exceptioncaught:" << e.what() << endl;
            ExitWithError("performSimgleGilleSpieIntroduction","exceptionerrorthrown");
       }

        try{
            temp_score = computeSinglGilScore(tmpAmountI, allSpecies.at(tmpIDI).getDiffusionEnh(), allSpecies.at(tmpIDI).getSolubility(),
                                                                          tmpAmountII, allSpecies.at(tmpIDII).getDiffusionEnh(), allSpecies.at(tmpIDII).getSolubility(),
                                                                          temp_k_reaction, temp_sameSpecies);
        }catch(exception&e){
            cout << "temp_score = computeSinglGilScore" << endl;
            cout << "Vectorsize "<< allSpecies.size() << " - position " << tmpIDI << endl;
            cerr << "exceptioncaught:" << e.what() << endl;
            ExitWithError("performSimgleGilleSpieIntroduction","exceptionerrorthrown");
       }

        if(temp_score > 0) // If score is grater than 0
        {
            if(debugLevel >= SMALL_DEBUG)
                    cout << "\t\t\t|- Amount 1: " << tmpIDI << " " << tmpAmountI <<
                    " Amount 2: " << tmpIDII << " "  << tmpAmountII <<
                    " Reaction: " << tmpRctID <<
                    " tmp_NRGDirection: " << tmp_NRGDirection <<
                    " tmpIDCatalysis: " << tmpIDCatalysis << endl;

            allGillespieScores.push_back(gillespie((acs_longInt)allGillespieScores.size(),
                                            tmp__rctType, temp_score, tmpMol_I, tmpMol_II,
                                            tmpMol_III, tmpMol_IV, tmp_NRGDirection, tmpRctID,
                                            tmpIDCatalysis));
            gillespieTotalScore += temp_score;
            gillespieCumulativeStepScoreList.push_back(gillespieTotalScore);
            // If the theoretical product is not evaluated gillespieNewSpeciesScore is incremented
            if((tmp__rctType == CONDENSATION) || (tmp__rctType == ENDO_CONDENSATION))
            {
                // IN the case of condensation molIII is the product, in the reaction structure molIII is a substrate but this subroutine is the product, mol_I is che complex and mol_II is the second substrate
                if(allSpecies.at(tmpMol_III).getEvaluated() == 0)
                    gillespieNewSpeciesScore += temp_score;
            }else if((tmp__rctType == CLEAVAGE) || (tmp__rctType == ENDO_CLEAVAGE))
            {
                // In the case of cleavage molII and molIII are products
                if((allSpecies.at(tmpMol_II).getEvaluated() == 0) || (allSpecies.at(tmpMol_III).getEvaluated() == 0))
                    gillespieNewSpeciesScore += temp_score;
            }

            if( ((tmp__rctType == CLEAVAGE || tmp__rctType == ENDO_CLEAVAGE) && (allReactions.at(tmpRctID).getType() == CONDENSATION))
                 ||
                ((tmp__rctType == CONDENSATION || tmp__rctType == ENDO_CONDENSATION) && (allReactions.at(tmpRctID).getType() == CLEAVAGE)) )
            {
                reverseReactionsGillScore += temp_score;
            }
        }
    }
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performSingleGilleSpieIntroduction end" << endl;
}


/**
 This Function returns the total amount of MOLECULES in the  tmpSpeciesvector
 The file is saved in the directory indicated as a second parameter in the run command
 @param vector<species>* tmpSpeciesvector pointer to tmpSpeciesvector
 */
acs_longInt environment::getTotalNumberOfSpecies()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMolecules start" << endl;
	
	acs_longInt tmpTotNumOfMols = 0;

        for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
        {
            if((tmpAllSpeciesIter->getComplexCutPnt() == 0) &&
                (tmpAllSpeciesIter->getAmount() > 0) &&
                (tmpAllSpeciesIter->getSolubility() == SOLUBLE))
                    tmpTotNumOfMols++;
        }
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMolecules end" << endl;
	
	return tmpTotNumOfMols;
}

/**
 This Function returns the total amount of MOLECULES in the  tmpSpeciesvector
 The file is saved in the directory indicated as a second parameter in the run command
 @param vector<species>* tmpSpeciesvector pointer to tmpSpeciesvector
 */
acs_longInt environment::getTotalNumberOfMolecules()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMolecules start" << endl;

    acs_longInt tmpTotNumOfMols = 0;
    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
    {
        if((tmpAllSpeciesIter->getComplexCutPnt() == 0) &&
            (tmpAllSpeciesIter->getAmount() > 0) &&
            (tmpAllSpeciesIter->getSolubility() == SOLUBLE))
                tmpTotNumOfMols += tmpAllSpeciesIter->getAmount();
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMolecules end" << endl;

    return tmpTotNumOfMols;
}


/**
 This Function returns the total amount of COMPLEX SPECIES in the tmpSpeciesvector
 The file is saved in the directory indicated as a second parameter in the run command
 @param vector<species>* tmpSpeciesvector pointer to tmpSpeciesvector
 */
acs_longInt environment::getTotalNumberOfComplexSpecies()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfComplexSpecies start" << endl;
	
	acs_longInt tmpTotNumOfMols = 0;
        for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
        {
            if((tmpAllSpeciesIter->getComplexCutPnt() > 0) && (tmpAllSpeciesIter->getAmount() > 0))
                    tmpTotNumOfMols++;
        }
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfComplexSpecies end" << endl;
	
	return tmpTotNumOfMols;
}

/**
 This Function returns the total amount of MOLECULES in the  tmpSpeciesvector
 The file is saved in the directory indicated as a second parameter in the run command
 @param vector<species>* tmpSpeciesvector pointer to tmpSpeciesvector
 */
acs_longInt environment::getTotalNumberOfComplexes()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfComplexes start" << endl;

    acs_longInt tmpTotNumOfMols = 0;
    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
    {
        if((tmpAllSpeciesIter->getComplexCutPnt() > 0) && (tmpAllSpeciesIter->getAmount() > 0))
            tmpTotNumOfMols += tmpAllSpeciesIter->getAmount();
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfComplexes end" << endl;

    return tmpTotNumOfMols;
}

/**
 This Function returns the total amount of MONOMERS in the  tmpSpeciesvector
 The file is saved in the directory indicated as a second parameter in the run command
 @param vector<species>* tmpSpeciesvector pointer to tmpSpeciesvector
 */
acs_longInt environment::getTotalNumberOfMonomers()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMonomers start" << endl;

    acs_longInt tmpTotNumOfMols = 0;

    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
    {
        if((tmpAllSpeciesIter->getAmount() > 0) && (tmpAllSpeciesIter->getSolubility() == SOLUBLE))
            tmpTotNumOfMols += tmpAllSpeciesIter->getAmount() * tmpAllSpeciesIter->getSequenceLength();
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotalNumberOfMonomers end" << endl;

    return tmpTotNumOfMols;
}

/**
 Get the total number of charged molecules
*/
acs_int environment::getTotNumberOfChargedMols()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotNumberOfChargedMold start" << endl;
    acs_int chargedMols = 0;
    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
    {
            chargedMols += tmpAllSpeciesIter->getChargeMols();
    }
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getTotNumberOfChargedMold end" << endl;
    return chargedMols;
}

/**
 This Function populates two vectors containing all the nutrients and all the probabilities for the influx selected
 species from the firing disk according to the max length of the influx
 */
//TR void environment::getNutrientsFromTheFiringDisk()
//{
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getNutrientsFromTheFiringDisk start" << endl;
//	
//	acs_double tmpProbability;
//
//	for(acs_int singleSpecies = 0; singleSpecies < (acs_int)firingDisk.size(); singleSpecies++)
//	{
//		// IF the species (contained in the firing disk) is longer (or at least equal) to the influx 
//		if(firingDisk.at(singleSpecies).getSequenceLength() <= influx)
//		{
//			nutrientsForInflux.push_back(firingDisk.at(singleSpecies).getID());
//			tmpProbability = createInitialConcentration(alphabet.length(), firingDisk.at(singleSpecies).getSequence().length()) / overallConcentration;
//			nutrientsProb2BeSelected.push_back(tmpProbability);
//		}
//	}
//	
//	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::getNutrientsFromTheFiringDisk end" << endl;
//}

/**
 This function print to monitor the content of the vectors nutrientsForInflux and nutrientsProb2BeSelected
 @version 1.0
 @date 2010-05-17
*/
void environment::printNutrientsAndProbability()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::printNutrientsAndProbability start" << endl;

    for(vector<acs_int>::iterator tmpAllNutrientsIter = nutrientsForInflux.begin(); tmpAllNutrientsIter != nutrientsForInflux.end(); tmpAllNutrientsIter++)
    {
        cout << *tmpAllNutrientsIter << "\t";
    }

    cout << endl;
	
    for(vector<acs_double>::iterator tmpAllNutrientsIter = nutrientsProb2BeSelected.begin(); tmpAllNutrientsIter != nutrientsProb2BeSelected.end(); tmpAllNutrientsIter++)
    {
        cout << *tmpAllNutrientsIter << "\t";
    }

    cout << endl;

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::printNutrientsAndProbability end" << endl;
}

/**
 Nutrients amount fixing process. The amount of nutrients has to be fixed according to the initial theoretical distribution
 @version 1.0
 */
void environment::nutrientsAmountsFixing()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::nutrientsAmountsFixing start" << endl;
	
	// Cumulative temporary probability
	acs_double tmpTotProb = 0;
	
    for(vector<acs_double>::iterator tmpAllNutrientsIter = nutrientsProb2BeSelected.begin(); tmpAllNutrientsIter != nutrientsProb2BeSelected.end(); tmpAllNutrientsIter++)
	{
		tmpTotProb += *tmpAllNutrientsIter;
	}
	
    vector<acs_double>nutrientsProb2BeSelectedCOPY = nutrientsProb2BeSelected;
	//Clear wrong structure
	nutrientsProb2BeSelected.clear();
	
    for(vector<acs_double>::iterator tmpAllNutrientsIter = nutrientsProb2BeSelectedCOPY.begin(); tmpAllNutrientsIter != nutrientsProb2BeSelectedCOPY.end(); tmpAllNutrientsIter++)
	{
		nutrientsProb2BeSelected.push_back(*tmpAllNutrientsIter/tmpTotProb);
	}	

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::nutrientsAmountsFixing end" << endl;
}


/**
 Perform Refill according to the time interval and the total amount of refill
 @version 2.4
 @date 2010.06.10
 @param tmpTimeSinceTheLastInFlux time elapsed since the last influx of at least one molcolule
 @param tmpMinimalTimeForOneMols time necessary to feed to the system one molecule
 @param tmp__RndDoubleGen random number generator
 */
bool environment::performRefill(acs_double tmpTimeSinceTheLastInFlux, acs_double tmpMinimalTimeForOneMols, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performRefill start" << endl;
	bool refillFlag = true;
	
//TR	//IF THE MAX LENGTH TO REFILL IS GREATER THAN THE MAX LENGHT OF THE FIRING DISK
//	if(influx > initialMaxLength)
//	{
//		ExitWithError("performRefill", "ERROR: The max refill lenght is longer than the initial max length");
//		refillFlag = false;
//	}
	acs_int numberOfMolsToRefill = round(tmpTimeSinceTheLastInFlux/tmpMinimalTimeForOneMols);
	if(debugLevel >= SMALL_DEBUG ||  numberOfMolsToRefill > 1000)
	{
		cout << "\t\t\t\t|- Number of molecules to refill: " << numberOfMolsToRefill << " DT: " << tmpTimeSinceTheLastInFlux << " T: " << tmpMinimalTimeForOneMols << endl;
	}
	
	if(numberOfMolsToRefill > 0)
	{
            // SELECT NUTRIENTS FROM THE FIRING DISK
            for(acs_longInt singleRefill = 0; singleRefill < numberOfMolsToRefill; singleRefill++)
            {
                acs_longInt nutrientForInflux_ID = returnSelectionIdFromAWeightProbVectorAlreadyNormalized(nutrientsProb2BeSelected,tmp__RndDoubleGen);
                if(debugLevel >= HIGH_DEBUG)
                {
                        cout << "\t\t\t\t";
                        for(acs_int sngProb = 0; sngProb < (acs_int)nutrientsProb2BeSelected.size(); sngProb++)
                        {
                                        cout << nutrientsProb2BeSelected.at(sngProb) << " ";
                        }
                        cout << endl;
                        cout << "\t\t\t\t|- Nutrient To refill: " << allSpecies.at(nutrientsForInflux.at(nutrientForInflux_ID)).getSequence() << "#" <<  nutrientForInflux_ID << endl;
                }

                if(nutrientForInflux_ID >= (unsigned)nutrientsForInflux.size())
                        cout << nutrientsForInflux.at(nutrientForInflux_ID) << " greater than the possible nutrients selection " << nutrientsForInflux.size()-1 << endl;

                acs_longInt IDspecies;
                try{
                    IDspecies = allSpecies.at(nutrientsForInflux.at(nutrientForInflux_ID)).getID();
                  }
                catch(exception&e){
                    cout << "allSpecies.at(nutrientsForInflux.at(nutrientForInflux_ID)).getID();" << endl;
                    cout << "Vectorsize " << allSpecies.size()<<" - position " << nutrientsForInflux.at(nutrientForInflux_ID) << endl;
                    cerr << "exceptioncaught:" << e.what() << endl;

                }

                if(debugLevel >= SMALL_DEBUG)
                {
                    cout << "\t\t\t\t|- " << singleRefill << "/" << numberOfMolsToRefill << " - Tot Number of Moles before refilling: " << getTotalNumberOfMolecules();
                    cout << " - Species to Refill: (" << allSpecies.at(IDspecies).getSequence() << "#" << IDspecies << ") - Tot Amount: " <<
                                    allSpecies.at(IDspecies).getAmount() << endl;
                }

                // ACTUAL INFLUX EVENT ----------------- increment specific species and the total number of species
                if(IDspecies >= (unsigned)allSpecies.size())
                    cout << IDspecies << " maggiore del massimo consentito che è " << allSpecies.size()-1 << endl;
                try{
                allSpecies.at(IDspecies).increment(volume);
                }
                catch(exception&e){
                    cout << " allSpecies.at(IDspecies).increment(volume);" << endl;
                    cout << "Vectorsize " << allSpecies.size()<<" - position " << IDspecies<< endl;
                    cerr << "exceptioncaught:" << e.what() << endl;

                }

                incMolProcedure(IDspecies);
                incSpeciesProcedure(IDspecies);

                if(debugLevel >= SMALL_DEBUG)
                {
                        cout << " - after refilling: " << getTotalNumberOfMolecules() << " - Tot Amount: " << allSpecies.at(IDspecies).getAmount() << endl;
                }
            }
	}else{
		refillFlag = false;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performRefill end" << endl;
	return refillFlag;
}

/**
  This function perform the pseudo-deterministic molecules charging process
 @version 2.6
 @date 2011-02-24
 @param tmpTimeInterval time elapsed since the last reaction
 @param MTrand &tmp_RndDoubleGen random number generator
 */
bool environment::performDETMoleculesCharging(acs_double tmpTimeInterval, MTRand &tmp_RndDoubleGen)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performDETMoleculesCharging start" << endl;
    bool effFlug = true;
    // ENERGY -------------------------------------
    if(energy == ENERGYBASED) // If energy is turned on molecules are charged
    {
       // cout << "******************************* BEGIN" << endl;
       // cout << "-- PRE" << endl;

        setNotChargedAndChargedSpeciesIDsAndAmounts(); // create two lists containing charged and unchaged molecules

		// If there are molecules to load
        if((!unchargedIDlist.empty()) && (!cumUnchargedAmountList.empty()))
        {

            acs_int nrgIntegerPart;
						
			// DIFFERENT FUNCTIONS TO LOAD DETERMINISTICALY HAVE BEEN IMPLMENTED 
            //acs_double actualAmountOfMolToLoad = (cumUnchargedAmountList.back() * K_nrg * tmpTimeInterval) + decimalMoleculesToLoad;
            //acs_double actualAmountOfMolToLoad =  ((ECConcentration * tmpTimeInterval * AVO) * (cumUnchargedAmountList.back()) * (K_nrg / (AVO * volume))) + decimalMoleculesToLoad;
			//acs_double actualAmountOfMolToLoad =  ((ECConcentration * AVO) * tmpTimeInterval) + decimalMoleculesToLoad;
			acs_double tempInEnergyMols = ECConcentration * AVO * tmpTimeInterval;
			acs_double tempInEnergyConc = tempInEnergyMols/(AVO*volume);
            acs_double notChargeMolsConc = cumUnchargedAmountList.back()/(AVO*volume);
			int loadedEnergyResidue = 0;
			
            acs_double actualAmountOfMolToLoad = (((K_nrg * tmpTimeInterval) * tempInEnergyConc * notChargeMolsConc) * (AVO * volume)) + decimalMoleculesToLoad;
			
            //TR cout << "................." << endl;
            //cout << "notChargeMolsConc" << notChargeMolsConc << endl;
            //cout << "tempInEnergyConc" << tempInEnergyConc << endl;
            //cout << "tmpTimeInterval" << tmpTimeInterval << endl;
            //cout << "knrg" << K_nrg << endl;
            //cout << "mol to load " << actualAmountOfMolToLoad << endl;
																	
            if((isinf(actualAmountOfMolToLoad)) || (actualAmountOfMolToLoad >= cumUnchargedAmountList.back()))
            { 
                nrgIntegerPart = cumUnchargedAmountList.back();
                loadedEnergyResidue = tempInEnergyMols - cumUnchargedAmountList.back();
				if(loadedEnergyResidue < 0)
				{
					decimalMoleculesToLoad += 0;
				}else{
					decimalMoleculesToLoad += loadedEnergyResidue;
				}
            }else{
				nrgIntegerPart = (acs_int)actualAmountOfMolToLoad;
				decimalMoleculesToLoad = actualAmountOfMolToLoad - (acs_double)nrgIntegerPart;
            }

            //cout << "\t2. after: "  << nrgIntegerPart << " " << decimalMoleculesToLoad << endl;

            // Declare temporary variable indicating the species to load
            acs_int tmpSpeciesToLoad;
            if(nrgIntegerPart > 0)
            {
                acs_int j;
                for(acs_int tmpSpeciesCnt = 0; tmpSpeciesCnt < nrgIntegerPart; tmpSpeciesCnt++)
                {
                    if((!unchargedIDlist.empty()) && (!cumUnchargedAmountList.empty()))
                    {
                        if(cumUnchargedAmountList.size() > 1)
                        {
                            tmpSpeciesToLoad = returnSelectionIdFromAWeightProbVector(cumUnchargedAmountList, cumUnchargedAmountList.back(), tmp_RndDoubleGen);
                        }else{
                            tmpSpeciesToLoad = 0;
                        }

                        // Molecule Charcing

                        if(!allSpecies.at(unchargedIDlist.at(tmpSpeciesToLoad)).chargeMol())
                        {
                           ExitWithError("PerformMoleculeEfflux", "Error during the charging process");
                        }else{
                           incOverallLoadedMolsCounter();
                        }

                        // When a species goes out the cumulative list is updated;
                        if(unchargedIDlist.size() > 0)
                        {
                            if(unchargedIDlist.size() == 1)
                            {
                                cumUnchargedAmountList.at(0)--;
                                if(cumUnchargedAmountList.at(0) == 0)
                                {
                                    cumUnchargedAmountList.clear();
                                    unchargedIDlist.clear();
                                }
                            }else{
                                j = tmpSpeciesToLoad;
                                while(j < (acs_int)unchargedIDlist.size())
                                {
                                    cumUnchargedAmountList.at(j)--;
                                    if(j == 0)
                                    {
                                        if(cumUnchargedAmountList.at(j) == 0)
                                        {
                                           //unchargedIDlist.removeAt(j);
                                           unchargedIDlist.erase(unchargedIDlist.begin()+j);
                                           //cumUnchargedAmountList.removeAt(j);
                                           cumUnchargedAmountList.erase(cumUnchargedAmountList.begin()+j);
                                        }else{
                                            j++;
                                        }
                                    }else{
                                       if(cumUnchargedAmountList.at(j) == cumUnchargedAmountList.at(j-1))
                                       {
                                          //unchargedIDlist.removeAt(j);
                                          unchargedIDlist.erase(unchargedIDlist.begin()+j);
                                          //cumUnchargedAmountList.removeAt(j);
                                          cumUnchargedAmountList.erase(cumUnchargedAmountList.begin()+j);
                                       }else{
                                          j++;
                                       }
                                    } // if(j == 0)
                                } // end while(j < (acs_int)unchargedIDlist.size())
                            } // if(unchargedIDlist.size() == 1)
                        } // end if(unchargedIDlist.size() > 0)
                        //cout << "post vector unchargedIDlist sizes " << unchargedIDlist.size() << " " << cumUnchargedAmountList.size() << endl;
                    } // end if((!unchargedIDlist.empty()) && (!cumUnchargedAmountList.empty()))
                } //  for(acs_int tmpSpeciesCnt = 0; tmpSpeciesCnt < nrgIntegerPart; tmpSpeciesCnt++)
            } // end if(nrgIntegerPart > 0)
        }else{
			decimalMoleculesToLoad += ECConcentration * tmpTimeInterval; // If all the molecules are charged all the avalaible energy carries wait for the next reaction
        } // end if((!unchargedIDlist.empty()) && (!cumUnchargedAmountList.empty()))
		
		// ---------------------------------|
		// Molecules Energy DECAY Procedure |
		// ---------------------------------|
        if((!chargedIDlist.empty()) && (!cumChargedAmountList.empty()))
		{
			acs_int nrgDecayIntegerPart;
                        acs_double actualAmountOfMolToUNLOAD = (K_nrg_decay * cumChargedAmountList.back() * tmpTimeInterval) + decimalMoleculesToUNLOAD;
			if(actualAmountOfMolToUNLOAD > 0)
            { 
				nrgDecayIntegerPart = (acs_int)actualAmountOfMolToUNLOAD;
				decimalMoleculesToUNLOAD = actualAmountOfMolToUNLOAD - (acs_double)nrgDecayIntegerPart;
            }else {
				nrgDecayIntegerPart = 0;
				decimalMoleculesToUNLOAD = 0;
			}

			// Declare temporary variable indicating the species to UNload
            acs_int tmpSpeciesToUNLoad;
			if(nrgDecayIntegerPart > 0)
			{
				acs_int z;
                for(acs_int tmpSpeciesCnt = 0; tmpSpeciesCnt < nrgDecayIntegerPart; tmpSpeciesCnt++)
                {
                    if((!chargedIDlist.empty()) && (!cumChargedAmountList.empty()))
                    {
                        if(cumChargedAmountList.size() > 1)
                        {
                            tmpSpeciesToUNLoad = returnSelectionIdFromAWeightProbVector(cumChargedAmountList, cumChargedAmountList.back(), tmp_RndDoubleGen);
                        }else{
                            tmpSpeciesToUNLoad = 0;
                        }
						
                        // Molecule Charcing
                        try{
                            if(!allSpecies.at(chargedIDlist.at(tmpSpeciesToUNLoad)).unchargeMol())
                            {
                                ExitWithError("PerformMoleculeEfflux", "Error during the decay process");
                            }else{
                                decOverallLoadedMolsCounter();
                            }
                        }
                        catch(exception&e)
                        {
                            cout << "if(!allSpecies.at(chargedIDlist.at(tmpSpeciesToUNLoad)).unchargeMol())" << endl;
                            cout << "Vectorsize " << allSpecies.size()<<" - position " << chargedIDlist.at(tmpSpeciesToUNLoad) << endl;
                            cerr << "exceptioncaught:" << e.what() << endl;
                            ExitWithError(" Molecule Charcing","exceptionerrorthrown");
                        }
                        // When a species goes out the cumulative list is updated;
                        if(chargedIDlist.size() > 0)
                        {
                            if(chargedIDlist.size() == 1)
                            {
                                cumChargedAmountList.at(0)--;
                                if(cumChargedAmountList.at(0) == 0)
                                {
                                    cumChargedAmountList.clear();
                                    chargedIDlist.clear();
                                }
                            }else{
                                z = tmpSpeciesToUNLoad;
                                while(z < (acs_int)chargedIDlist.size())
                                {
                                    cumChargedAmountList.at(z)--;
                                    if(z == 0)
                                    {
                                        if(cumChargedAmountList.at(z) == 0)
                                        {
                                            //chargedIDlist.removeAt(z);
                                            chargedIDlist.erase(chargedIDlist.begin()+z);
                                            //cumChargedAmountList.removeAt(z);
                                            cumChargedAmountList.erase(cumChargedAmountList.begin()+z);
                                        }else{
                                            z++;
                                        }
                                    }else{
                                            if(cumChargedAmountList.at(z) == cumChargedAmountList.at(z-1))
                                            {
                                                    //chargedIDlist.removeAt(z);
                                                    chargedIDlist.erase(chargedIDlist.begin()+z);
                                                    //cumChargedAmountList.removeAt(z);
                                                    cumChargedAmountList.erase(cumChargedAmountList.begin()+z);
                                            }else{
                                                    z++;
                                            }
                                    } // if(z == 0)
                                } // end while(z < (acs_int)chargedIDlist.size())
                            } // if(chargedIDlist.size() == 1)
                        } // end if(chargedIDlist.size() > 0)
                        //cout << "post vector chargedIDlist sizes " << chargedIDlist.size() << " " << cumChargedAmountList.size() << endl;
                    } // end if((!chargedIDlist.empty()) && (!cumChargedAmountList.empty()))
                } //  for(acs_int tmpSpeciesCnt = 0; tmpSpeciesCnt < nrgDecayIntegerPart; tmpSpeciesCnt++)
			}
		}else{ 
			decimalMoleculesToUNLOAD = 0;
        } // end if((!chargedIDlist.empty()) && (!cumChargedAmountList.empty()))
		
		
		
    } // end if(energy == ENERGYBASED)
    // END ENERGY ------------------------------

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performDETMoleculesCharging end" << endl;
    return effFlug;
}

/**
 This function populates to lists, the first containing all the living species ID and the
 second one containing the cumulative number of living species
 @version 2.5.2
 @date 2010-11-11
 */
void environment::setLivingSpeciesIDsAndAmounts()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::setLivingSpeciesIDsAndAmounts start" << endl;

    livingSpeciesIDsList.clear(); // Clean the livingSpeciesIDs list
    cumLivingAmountsList.clear(); // Clean living Species Amount
    acs_longInt cumulativeNumberOfSpecies = 0; // Initialise the cumulative number of species
    bool toBeInserted = true;
	
	// cout << ".................." << endl;

    if(!allSpecies.empty())
    {
        for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
        {
            toBeInserted = true;
            if(maxLOut > 0){if(tmpAllSpeciesIter->getSequenceLength() <= maxLOut) toBeInserted = true; else toBeInserted = false;}
			
			if(toBeInserted)
			{
				if((tmpAllSpeciesIter->getAmount() > 0) && (tmpAllSpeciesIter->getSolubility() == SOLUBLE))
				{
					// cout << tmpAllSpeciesIter->getID() << " " << tmpAllSpeciesIter->getSequence() << " " << tmpAllSpeciesIter->getAmount() <<  endl;
					livingSpeciesIDsList.push_back(tmpAllSpeciesIter->getID());
					cumulativeNumberOfSpecies += tmpAllSpeciesIter->getAmount();
					cumLivingAmountsList.push_back((acs_double)cumulativeNumberOfSpecies);              
				}
			}
        }
    }


    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::setLivingSpeciesIDsAndAmounts end" << endl;
}

/**
 This function populates to lists, the first one contains the IDs of the uncharged mols and the second one
 contains the cumulative amount of uncharged molecules
 @version 2.5.3
 @date 2011-02-22
 */
void environment::setNotChargedAndChargedSpeciesIDsAndAmounts()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::setNotChargedAndChargedSpeciesIDsAndAmounts start" << endl;

    unchargedIDlist.clear(); // Clean Living Species Uncharged ID list
    cumUnchargedAmountList.clear(); // Clean Living specie cumulative uncharged List
    acs_longInt cumulativeNumberOfUnchargedSpecies = 0; // Initialise the cumulative number of species
	
	// Clear and declare the same variables as above, but for the charged species. 
	chargedIDlist.clear();
	cumChargedAmountList.clear();
	acs_longInt cumulativeNumberOfChargedSpecies = 0; 

    if(!allSpecies.empty())
    {
        for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
        {
            if((tmpAllSpeciesIter->getAmount() > 0) && (tmpAllSpeciesIter->getSolubility() == SOLUBLE) && (tmpAllSpeciesIter->getComplexCutPnt() == 0))
            {
                if(energy == ENERGYBASED)
                {
                    if((tmpAllSpeciesIter->getNOTchargeMols() > 0) && (tmpAllSpeciesIter->getEnergizable()))
                    {
                        unchargedIDlist.push_back(tmpAllSpeciesIter->getID());
                        cumulativeNumberOfUnchargedSpecies += tmpAllSpeciesIter->getNOTchargeMols();
                        cumUnchargedAmountList.push_back((acs_double)cumulativeNumberOfUnchargedSpecies);
                    }
					if((tmpAllSpeciesIter->getChargeMols() > 0) && (tmpAllSpeciesIter->getEnergizable()))
					{
						chargedIDlist.push_back(tmpAllSpeciesIter->getID());
						cumulativeNumberOfChargedSpecies += tmpAllSpeciesIter->getChargeMols();
						cumChargedAmountList.push_back((acs_double)cumulativeNumberOfChargedSpecies);
					}
                }
            }
        }
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::setNotChargedAndChargedSpeciesIDsAndAmounts end" << endl;
}

/**
 Perform vector unchargedIDlist update removing a new charge molecule
 vectors unchargedIDlist and cumUnchargedAmountList are involved
 @version 1.0
 @date 2010-10-10
 @param acs_int tmpSpeciesID Specie to uncharge
 */
bool environment::removeChargeMolFromList(acs_int tmpSpeciesID)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::removeChargeMolFromList start" << endl;

    bool chFlag = false;
    acs_int counter = 0;
    bool fromHere = false;
    for(vector<acs_int>::iterator tmpAllSpeciesIter = unchargedIDlist.begin(); tmpAllSpeciesIter != unchargedIDlist.end(); tmpAllSpeciesIter++)
    {
        if(*tmpAllSpeciesIter == tmpSpeciesID)
            fromHere = true;

        if(fromHere)
        {
            try{
            cumUnchargedAmountList.at(counter)++;
            }
            catch(exception&e)
            {
                cout << "cumUnchargedAmountList.at(counter)++;" << endl;
                cout << "Vectorsize " << cumUnchargedAmountList.size()<<" - position " << counter << endl;
                cerr << "exceptioncaught:" << e.what() << endl;
                ExitWithError("cumUnchargedAmountList","exceptionerrorthrown");
            }
            chFlag = true;
        }

        counter++;
    }
    // If the species is not present it is added at the end of the list with the last value of the list + 1
    if(!fromHere)
    {
        unchargedIDlist.push_back(tmpSpeciesID);
        cumUnchargedAmountList.push_back(cumUnchargedAmountList.back()+1);
        chFlag = true;
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::removeChargeMolFromList end" << endl;
    return chFlag;
}

/**
 Perform vector unchargedIDlist update adding a new charge molecule
 vector unchargedIDlist and cumUnchargedAmountList are involved
 @version 1.0
 @date 2010-10-10
 @param acs_int tmpSpeciesID Specie to charge
 */
bool environment::addChargeMolToList(acs_int tmpSpeciesID)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment:addChargeMolToList start" << endl;

    bool chFlag = false;
    acs_int counter = 0;
    bool fromHere = false;
    bool flagRemove = false;
    for(vector<acs_int>::iterator tmpAllSpeciesIter = unchargedIDlist.begin(); tmpAllSpeciesIter != unchargedIDlist.end(); tmpAllSpeciesIter++)
    {
        try{
        if(*tmpAllSpeciesIter == tmpSpeciesID)
        {
            fromHere = true;
            if(cumUnchargedAmountList.at(counter) == 1)
                flagRemove = true;
        }

        if(fromHere)
        {
            cumUnchargedAmountList.at(counter)--;
            if(!flagRemove)
                chFlag = true;
        }
        }
        catch(exception&e)
        {
        cout<<" cumUnchargedAmountList.at(counter)--" << endl;
        cout << "Vectorsize " <<cumUnchargedAmountList.size()<<" - position " <<counter<< endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("cumUnchargedAmountList","exceptionerrorthrown");
        }

        counter++;
    }
    // If the species is not present it is added at the end of the list with the last value of the list + 1
    if(flagRemove)
    {
        //unchargedIDlist.removeAt(tmpSpeciesID);
        unchargedIDlist.erase(unchargedIDlist.begin()+tmpSpeciesID);
        //cumUnchargedAmountList.removeAt(tmpSpeciesID);
        cumUnchargedAmountList.erase(cumUnchargedAmountList.begin()+tmpSpeciesID);
        chFlag = true;
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::addChargeMolToList end" << endl;
    return chFlag;
}

/**
 This function perform the deterministic molecules efflux process
 @version 2.5
 @date 2010-06-25
 @param tmpTimeInterval time elapsed since the last reaction
 @param MTrand &tmp_RndDoubleGen random number generator
 */
bool environment::performMoleculesEfflux(acs_double tmpTimeInterval, MTRand &tmp_RndDoubleGen)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performMoleculesEfflux start" << endl;
    bool effFlug = true;
    if(debugLevel == SMALL_DEBUG){cout << "\t\t\t\t|- Number of molecules: BEFORE efflux: " << getTotalNumberOfMolecules();}
	
    // Create the list of all the living species IDs and Amounts and ENERGY as well
    setLivingSpeciesIDsAndAmounts();
	
	// EFFLUX
	
	// energy efflux
	// If the system is open some energy molecules go away => moleculeDecay_KineticConstant
	if(nrgBoolFlag == ENERGYBASED)
	{
		acs_double tempNrgOut = decimalMoleculesToLoad * moleculeDecay_KineticConstant * tmpTimeInterval;
		if(tempNrgOut > 0)
		{
			if((decimalMoleculesToLoad - tempNrgOut) > 0)
			{
				decimalMoleculesToLoad = decimalMoleculesToLoad - tempNrgOut;
			}
			else{
				decimalMoleculesToLoad = 0;
			}
		}
		
		// ... and some EC molecules decay --> K_nrg_decay
		tempNrgOut = decimalMoleculesToLoad * K_nrg_decay * tmpTimeInterval;
		if(tempNrgOut > 0)
		{
			if((decimalMoleculesToLoad - tempNrgOut) > 0)
			{
				decimalMoleculesToLoad = decimalMoleculesToLoad - tempNrgOut;
			}
			else{
				decimalMoleculesToLoad = 0;
			}		
		}
	}
	
	// If there are molecules...
    if((!cumLivingAmountsList.empty()) && (!livingSpeciesIDsList.empty()))
    {
		
        // Compute the number of species to efflux according to the delta T elapsed from the last reaction
        acs_int integerPart;		
		
        acs_double actualAmountOfMoltoEfflux = (cumLivingAmountsList.back() * moleculeDecay_KineticConstant * tmpTimeInterval) + decimalMoleculesToEfflux;
		
        // cout << cumLivingAmountsList.back() << " * " << moleculeDecay_KineticConstant<< " * " << tmpTimeInterval << " + " << decimalMoleculesToEfflux << " = " << actualAmountOfMoltoEfflux << endl;
		
        if((isinf(actualAmountOfMoltoEfflux)) || (actualAmountOfMoltoEfflux > cumLivingAmountsList.back()))
        {
            integerPart = cumLivingAmountsList.back();
			decimalMoleculesToEfflux += 0;
        }else{
			integerPart = (acs_int)actualAmountOfMoltoEfflux;
			decimalMoleculesToEfflux = actualAmountOfMoltoEfflux - (acs_double)integerPart;
        }
		
        acs_longInt speciesToEfflux;
		
        // For each molecule to efflux
        if(integerPart > 0)
        {
            acs_int i;
            for(acs_longInt singleEfflux = 0; singleEfflux < integerPart; singleEfflux++)
            {
                if((!cumLivingAmountsList.empty()) && (!livingSpeciesIDsList.empty()))
                {
                    // Select species ID (ID of the livingSpeciesIDsList list) to efflux
                    if(livingSpeciesIDsList.size() > 1)
                    {
                        speciesToEfflux = returnSelectionIdFromAWeightProbVector(cumLivingAmountsList, cumLivingAmountsList.back(),
                                                                                tmp_RndDoubleGen);
                    }else{
                        speciesToEfflux = 0;
                    }
                    // Molecule efflux will be livingSpeciesIDsList at the position speciesToEfflux
                    if(debugLevel == SMALL_DEBUG)
                    {
						cout << "\t\t\tDT\t" << tmpTimeInterval << "\tSpecies to efflux\t" << livingSpeciesIDsList.at(speciesToEfflux) <<
						" \tMols <- efflux: " << allSpecies.at(livingSpeciesIDsList.at(speciesToEfflux)).getAmount() << endl;
                    }
                    try{
                    // ACTUAL EFFLUX PROCEDURE
                    if(!performMoleculeEfflux(livingSpeciesIDsList.at(speciesToEfflux), tmp_RndDoubleGen))
						ExitWithError("performMoleculeEfflux", "Problems during the EFFLUX process");
                    }
                    catch(exception&e)
                    {
                    cout<<"!performMoleculeEfflux(livingSpeciesIDsList.at(speciesToEfflux), tmp_RndDoubleGen))" << endl;
                    cout << "Vectorsize " <<livingSpeciesIDsList.size()<<" - position " <<speciesToEfflux<< endl;
                    cerr << "exceptioncaught:" << e.what() << endl;
                    ExitWithError("speciesToEfflux","exceptionerrorthrown");
                    }

                    if(livingSpeciesIDsList.size() > 0)
                    {
                        if(livingSpeciesIDsList.size() == 1)
                        {
                            cumLivingAmountsList.at(0)--;
                            if(cumLivingAmountsList.at(0) == 0)
                            {
                                cumLivingAmountsList.clear();
                                livingSpeciesIDsList.clear();
                            }
                        }else{
                            i = speciesToEfflux;
                            while(i < (acs_int)livingSpeciesIDsList.size())
                            {
                                cumLivingAmountsList.at(i)--;
                                if(i == 0)
                                {
                                    if(cumLivingAmountsList.at(i) == 0)
                                    {
                                        //livingSpeciesIDsList.removeAt(i);
                                        livingSpeciesIDsList.erase(livingSpeciesIDsList.begin()+i);
                                        //cumLivingAmountsList.removeAt(i);
                                        cumLivingAmountsList.erase(cumLivingAmountsList.begin()+i);
                                    }else{
                                        i++;
                                    }
                                }else{
                                    if(cumLivingAmountsList.at(i) == cumLivingAmountsList.at(i-1))
                                    {
                                        //livingSpeciesIDsList.removeAt(i);
                                        livingSpeciesIDsList.erase(livingSpeciesIDsList.begin()+i);
                                        //cumLivingAmountsList.removeAt(i);
                                        cumLivingAmountsList.erase(cumLivingAmountsList.begin()+i);
                                    }else{
                                        i++;
                                    }
                                } // if(i == 0)
                            } // end while(i < (acs_int)livingSpeciesIDsList.size())
                        }
                    }
					
                    if(debugLevel == SMALL_DEBUG)
                    {
						cout << "\tMols -> efflux: " << allSpecies.at(livingSpeciesIDsList.at(speciesToEfflux)).getAmount() << endl;
                    }
                }else{
                    ExitWithError("performMoleculesEfflux", "No molecules to efflux");
                } //  if((!cumLivingAmountsList.empty()) && (!livingSpeciesIDsList.empty()))
            } //  for(acs_longInt singleEfflux = 0; singleEfflux < integerPart; singleEfflux++)
        } // END if(integerPart > 0)
    } // if((!cumLivingAmountsList.empty()) && (!livingSpeciesIDsList.empty()))
	
    if(debugLevel == SMALL_DEBUG){cout << " - AFTER efflux: " << getTotalNumberOfMolecules() << endl;}
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performMoleculesEfflux end" << endl;
    return effFlug;
}


/**
 Perform MOLECULE EFFLUX reaction
 @version 2.5.1
 @date 2010-06-27
 @param acs_longInt tmpSpecies Species ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::performMoleculeEfflux(acs_longInt tmpSpecies, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performMoleculeEfflux start" << endl;
	bool reactionFlag = false;
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t\t|- Molecule to Efflux: " << allSpecies.at(tmpSpecies).getSequence() << " - Before efflux process [#" << allSpecies.at(tmpSpecies).getAmount() << "]";
	}
	
	// Complex (loaded or not loaded) to dissociate is chosen according to the total amount of loaded and not loaded complexes present in the system
    acs_double ratioLoadedSpecies;

    try{
    ratioLoadedSpecies= allSpecies.at(tmpSpecies).getChargeMols() / allSpecies.at(tmpSpecies).getAmount();
    }
    catch(exception&e)
    {
    cout<<" ratioLoadedSpecies= allSpecies.at(tmpSpecies).getChargeMols() / allSpecies.at(tmpSpecies).getAmount()" << endl;
    cout << "Vectorsize " <<allSpecies.size()<<" - tmpSpecies " << tmpSpecies << endl;
    cerr << "exceptioncaught:" << e.what() << endl;
    ExitWithError("ratioLoadedSpecies","exceptionerrorthrown");
    }

    acs_double rndNumb = tmp__RndDoubleGen();

	if(rndNumb > ratioLoadedSpecies) // rndNumb has to be stricktly greater 
	{
		// DECREMENT TOTAL AMOUNT OF THIS species or complex (not loaded)
                if(allSpecies.at(tmpSpecies).getNOTchargeMols() < 1)
		{
			ExitWithError("performMoleculeEfflux", "There are not avalaible not loaded species to efflux");
		}else{
                        allSpecies.at(tmpSpecies).decrement(volume);
			if(allSpecies.at(tmpSpecies).getComplexCutPnt() == 0) // is the species is not a complex
			{
				// Here the concentrationFixed species proprieties is not evalute since it works only with "close" systems
				decMolSpeciesProcedure(tmpSpecies); // Change overall amount of species and molecules
			}else{
				decCpxProcedure(tmpSpecies);
			}
			reactionFlag = true;
		}
	}else{
		// DECREMENT TOTAL AMOUNT OF THIS species or complex (loaded)
                if(allSpecies.at(tmpSpecies).getChargeMols() < 1)
		{
			ExitWithError("performMoleculeEfflux", "There are not avalaible loaded species to efflux");
		}else{
			//cout << "------------------------" << endl;
			//cout << allSpecies.at(tmpSpecies).getChargeMols() << " of " << allSpecies.at(tmpSpecies).getAmount() << " || ";
			unchargeMolProcess(tmpSpecies);
                        allSpecies.at(tmpSpecies).decrement(volume);
			//cout << " " << allSpecies.at(tmpSpecies).getChargeMols() << " of " << allSpecies.at(tmpSpecies).getAmount() << endl;
			if(allSpecies.at(tmpSpecies).getComplexCutPnt() == 0) // is the species is not a complex
			{
				decMolSpeciesProcedure(tmpSpecies); // Change overall amount of species and molecules
			}else{
				decCpxProcedure(tmpSpecies);
			}
			reactionFlag = true;
		}
	}
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << " - after efflux process [#" << allSpecies.at(tmpSpecies).getAmount() << "]" << endl;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performMoleculeEfflux end" << endl;
	return reactionFlag;	
}

/**
 Perform ENERGY EFFLUX reaction
 @version 2.4.1
 @date 2010-06-27
 @param MTRand& tmp__RndDoubleGen random number generator
 */

bool environment::performEnergyEfflux(MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performEnergyEfflux start" << endl;
	bool reactionFlag = false;
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t\t|- CARRIER to Efflux: " << nrgCarrier.getSequence() << " - Before efflux process [#" << nrgCarrier.getAmount() << "]";
	}
	
	// Complex (loaded or not loaded) to dissociate is chosen according to the total amount of loaded and not loaded complexes present in the system
	acs_double ratioLoadedCarriers = nrgCarrier.getChargeMols() / nrgCarrier.getAmount();
	acs_double rndNumb = tmp__RndDoubleGen();
	if(rndNumb > ratioLoadedCarriers) // If an unloaded energy carrier has to be throw away
	{
		
		// DECREMENT TOTAL AMOUNT OF THIS species (not loaded)
		if(nrgCarrier.getNOTchargeMols() < 1)
		{
			ExitWithError("performEnergyEfflux", "There are not avalaible not loaded carriers to efflux");
		}else{
			nrgCarrier.decrement(volume);
			reactionFlag = true;
		}
	}else{
		// DECREMENT TOTAL AMOUNT OF THIS species (loaded)
		if(nrgCarrier.getChargeMols() < 1)
		{
			ExitWithError("performEnergyEfflux", "There are not avalaible loaded carriers to efflux");
		}else{
			nrgCarrier.unchargeMol();
			nrgCarrier.decrement(volume);
			reactionFlag = true;
		}
	}
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << " - after carrier efflux process [#" << nrgCarrier.getAmount() << "]" << endl;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performEnergyEfflux end" << endl;
	return reactionFlag;
	
}

/**
 Perform the reaction after the Gillespie computation
 @version 1.0
 @param acs_longInt reaction_u reaction ID in Gillespie structure
 @param MTRand& tmp_RndDoubleGen random generator
 */
bool environment::performReaction(acs_longInt reaction_u, MTRand& tmp_RndDoubleGen, acs_int tmp_ActGEN, acs_int tmp_ActSIM,
                                  acs_int tmp_ActSTEP, QString tmp_StoringPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performReaction start" << endl;

	bool reactionFlag = true;
	
	// ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-
	// PERFORM OPERATIONS ACCORDING TO THE REACTION
	// ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-
    try{
        allGillespieScores.at(reaction_u);
    }
    catch(exception&e)
    {
    cout<<" allGillespieScores.at(reaction_u)" << endl;
    cout << "Vectorsize " <<allGillespieScores.size()<<" - position " << reaction_u << endl;
    cerr << "exceptioncaught:" << e.what() << endl;
    ExitWithError("","exceptionerrorthrown");
    }

	switch (allGillespieScores.at(reaction_u).getIdReactionType()) 
    {
		case CONDENSATION:
			if(!performCondensation(allGillespieScores.at(reaction_u).getMolI(), //catalyst
									allGillespieScores.at(reaction_u).getMolII(), // substrate 
									allGillespieScores.at(reaction_u).getMolIII(), // product
									allGillespieScores.at(reaction_u).getMolIV(), // complex	
									allGillespieScores.at(reaction_u).getReactionID(),
									allGillespieScores.at(reaction_u).getCatalysisID(), 
									tmp_RndDoubleGen))
			{
				if(debugLevel >= RUNNING_VERSION)
					cout << "\t\t\t|- !*!*!* There's no molecule availability to perform CONDENSATION reaction..." << endl;
			}	
                        // STORE ON FILE TIMES EVERY fileTimesSaveInterval seconds (if at least something happen)
                        if((getActualTime() > (getFileTimesSavingInterval() + internalTimesStoredCounter)) ||
                                (getActualTime() == 0) || (getFileTimesSavingInterval() == 0))
                        {
                            saveReactionsParameters(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath, allGillespieScores.at(reaction_u).getIdReactionType(),
                                                    allGillespieScores.at(reaction_u).getMolI(), allGillespieScores.at(reaction_u).getMolIII(),
                                                    allSpecies.at(allGillespieScores.at(reaction_u).getMolIV()).getSubstrate_ID(), allGillespieScores.at(reaction_u).getMolII());

                            saveLivingSpeciesID(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath);
                            saveLivingSpeciesAmount(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            saveLivingSpeciesConcentration(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            if(getActualTime() > 0)
                            {
                                internalTimesStoredCounter = internalTimesStoredCounter + getFileTimesSavingInterval();
                            }
                        }
			break;
		case ENDO_CONDENSATION:
			if(!perform_endo_Condensation(allGillespieScores.at(reaction_u).getMolI(), //catalyst
									allGillespieScores.at(reaction_u).getMolII(), // substrate
									allGillespieScores.at(reaction_u).getMolIII(), // product
									allGillespieScores.at(reaction_u).getMolIV(), // complex
									allGillespieScores.at(reaction_u).getNRGside(), // Energy species side, complex, substrate or both
									allGillespieScores.at(reaction_u).getReactionID(),
									allGillespieScores.at(reaction_u).getCatalysisID(), 
									tmp_RndDoubleGen))
			{
				if(debugLevel >= RUNNING_VERSION)
					cout << "\t\t\t|- !*!*!* There's no molecule availability to perform ENDO CONDENSATION reaction..." << endl;
                        }
                        if((getActualTime() > (getFileTimesSavingInterval() + internalTimesStoredCounter)) ||
                           (getActualTime() == 0))
                        {
                            try{
                            saveReactionsParameters(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath, allGillespieScores.at(reaction_u).getIdReactionType(),
                                                                            allGillespieScores.at(reaction_u).getMolI(), allGillespieScores.at(reaction_u).getMolIII(),

                                                                            allSpecies.at(allGillespieScores.at(reaction_u).getMolIV()).getSubstrate_ID(), allGillespieScores.at(reaction_u).getMolII());
                            }
                            catch(exception&e)
                            {
                            cout<<" saveReactionsParameters(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath, allGillespieScores.at(reaction_u).getIdReactionType(allGillespieScores.at(reaction_u).getMolI(), allGillespieScores.at(reaction_u).getMolIII(),allSpecies.at(allGillespieScores.at(reaction_u).getMolIV()).getSubstrate_ID(), allGillespieScores.at(reaction_u).getMolII());" << endl;
                            cerr << "exceptioncaught:" << e.what() << endl;
                            ExitWithError("","exceptionerrorthrown");
                            }

                            saveLivingSpeciesID(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath);
                            saveLivingSpeciesAmount(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            saveLivingSpeciesConcentration(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            if(getActualTime() > 0)
                            {
                                internalTimesStoredCounter = internalTimesStoredCounter + getFileTimesSavingInterval();
                            }
                        }
			break;
		case CLEAVAGE:
			if(!performCleavage(allGillespieScores.at(reaction_u).getMolI(), // Substrate
								allGillespieScores.at(reaction_u).getMolII(), // Product I
								allGillespieScores.at(reaction_u).getMolIII(), // product II
								allGillespieScores.at(reaction_u).getReactionID(), // reaction ID 
								allGillespieScores.at(reaction_u).getCatalysisID(), // Catalysis ID 
								tmp_RndDoubleGen))
				ExitWithError("performCleavage", "Problems during the CLEAVAGE reaction");	
			
                        if((getActualTime() > (getFileTimesSavingInterval() + internalTimesStoredCounter)) ||
                           (getActualTime() == 0))
                        {
                            saveReactionsParameters(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath, allGillespieScores.at(reaction_u).getIdReactionType(),
                                                                            allGillespieScores.at(reaction_u).getMolIV(), allGillespieScores.at(reaction_u).getMolI(), allGillespieScores.at(reaction_u).getMolII(),
                                                                            allGillespieScores.at(reaction_u).getMolIII());

                            saveLivingSpeciesID(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath);
                            saveLivingSpeciesAmount(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            saveLivingSpeciesConcentration(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            if(getActualTime() > 0)
                            {
                                internalTimesStoredCounter = internalTimesStoredCounter + getFileTimesSavingInterval();
                            }
                        }
			break;
		case ENDO_CLEAVAGE:
			if(!perform_endo_Cleavage(allGillespieScores.at(reaction_u).getMolI(), // Substrate
									  allGillespieScores.at(reaction_u).getMolII(),	// Product One
									  allGillespieScores.at(reaction_u).getMolIII(), // Product Two
									  allGillespieScores.at(reaction_u).getNRGside(), // Energy species side, complex, substrate or both
									  allGillespieScores.at(reaction_u).getReactionID(), // reaction ID
									  allGillespieScores.at(reaction_u).getCatalysisID(), // Catalysis ID
									  tmp_RndDoubleGen))
                                ExitWithError("perform_endo_Cleavage", "Problems during the ENDOCLEAVAGE reaction");
			
                        if((getActualTime() > (getFileTimesSavingInterval() + internalTimesStoredCounter)) ||
                           (getActualTime() == 0))
                        {
                            saveReactionsParameters(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath, allGillespieScores.at(reaction_u).getIdReactionType(),
                                                                            allGillespieScores.at(reaction_u).getMolIV(), allGillespieScores.at(reaction_u).getMolI(), allGillespieScores.at(reaction_u).getMolII(),
                                                                            allGillespieScores.at(reaction_u).getMolIII());

                            saveLivingSpeciesID(tmp_ActGEN, tmp_ActSIM, tmp_ActSTEP, tmp_StoringPath);
                            saveLivingSpeciesAmount(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            saveLivingSpeciesConcentration(tmp_ActGEN, tmp_ActSIM, tmp_StoringPath);
                            if(getActualTime() > 0)
                            {
                                internalTimesStoredCounter = internalTimesStoredCounter + getFileTimesSavingInterval();
                            }
                        }
			break;
		case COMPLEXFORMATION:
			if(!performComplexFormation(allGillespieScores.at(reaction_u).getMolI(), // Catalyst
                                                                                allGillespieScores.at(reaction_u).getMolII(), // Substrate
										tmp_RndDoubleGen))
			{
				if(debugLevel >= RUNNING_VERSION)
					cout << "\t\t\t|- !*!*!* There's no molecule availability to perform COMPLEX FORMATION reaction..." << endl;
				
				ExitWithError("performComplexFormation", "Problems during the COMPLEX COMPLETION process");
			}			
			break;
		case ENDO_COMPLEXFORMATION:
			if(!perform_endo_ComplexFormation(allGillespieScores.at(reaction_u).getMolI(), // Catalyst
											  allGillespieScores.at(reaction_u).getMolII(), // Substrate
                                                                                          allGillespieScores.at(reaction_u).getNRGside(), // Energy species side, complex, substrate or both
											  tmp_RndDoubleGen))
			{
				if(debugLevel >= RUNNING_VERSION)
					cout << "\t\t\t|- !*!*!* There's no molecule availability to perform ENDO COMPLEX FORMATION reaction..." << endl;
				
				ExitWithError("performComplexFormation", "Problems during the ENDO COMPLEX COMPLETION process");
			}			
			break;
		case COMPLEXDEGRADATION:
			if(!performComplexDissociation(allGillespieScores.at(reaction_u).getMolI(), 
										   allGillespieScores.at(reaction_u).getMolII(), 
										   allGillespieScores.at(reaction_u).getMolIII(),
										   tmp_RndDoubleGen))
				ExitWithError("performComplexDissociation", "Problems during the COMPLEX DISSOCIATION process");				
			break;
		case SPECIESDECAY:
			if(!performMoleculeEfflux(allGillespieScores.at(reaction_u).getMolI(), tmp_RndDoubleGen))
				ExitWithError("performMoleculeEfflux", "Problems during the EFFLUX process");			
			break;
        //TR case PHOSPHORILATION:
        //	if (!performPhosphorilation(allGillespieScores.at(reaction_u).getMolI()))
        //		ExitWithError("performPhosphorilation", "Problems during the PHOSPHORILATION process");
        //	break;
		case ENERGYEFFLUX:
			if (!performEnergyEfflux(tmp_RndDoubleGen))
				ExitWithError("performEnergyEfflux", "Problems during the ENERGY EFFLUX process");
			break;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\tenvironment::performReaction end" << endl;
	
	return reactionFlag;
}

/**
 Perform CONDENSATION reaction
 @version 1.2
 @date 2011-02-12
 @param acs_longInt tmpComplex Complex ID
 @param acs_longInt tmpSubstrate Substrate ID
 @param acs_longInt tmpProduct Product ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::performCondensation(acs_longInt tmpCatalyst, acs_longInt tmpSubstrate, acs_longInt tmpProduct, 
                                      acs_longInt tmpComplex, acs_longInt tmpIdReaction, acs_longInt tmpIdCatalysis,
                                      MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performCondensation start" << endl;

	bool reactionFlag = false;
	acs_longInt tmpSubAmount;
	acs_longInt tmpCpxAmount;

    try{
	if(nrgBoolFlag == ENERGYBASED)
	{
		tmpSubAmount = allSpecies.at(tmpSubstrate).getNOTchargeMols();
		tmpCpxAmount = allSpecies.at(tmpComplex).getNOTchargeMols();
	}else {
		tmpSubAmount = allSpecies.at(tmpSubstrate).getAmount();
		tmpCpxAmount = allSpecies.at(tmpComplex).getAmount();		
	}

	}
    catch(exception&e)
    {
    cout<<"tmpSubAmount = allSpecies.at(tmpSubstrate).getNOTchargeMols(); tmpCpxAmount = allSpecies.at(tmpComplex).getNOTchargeMols(); " << endl;
    cerr << "exceptioncaught:" << e.what() << endl;
    ExitWithError("","exceptionerrorthrown");
    }


	// check whether all the species amounts to decrement are greater than 1
	if(tmpSubAmount == 0)
		ExitWithError("performCondensation", "Substrate not Avalaible!!!");
	if(tmpCpxAmount == 0)
		ExitWithError("performCondensation", "Complex not Avalaible!!!");		

	
		
	// the catalyst come to be free
	if (debugLevel >= SMALL_DEBUG) 
	{
		cout << "CONDENSATION BEFORE complexes: " << tmpCpxAmount
			 << " - substrates: " << tmpSubAmount
                         << " - catalyst: " << allSpecies.at(tmpCatalyst).getAmount() << endl;
	}
	
    // REACTION!!!
    try{
        // concentration fixed is checked within the function
        allSpecies.at(tmpCatalyst).increment(volume);
    }
    catch(exception&e)
    {
        cout<<" allSpecies.at(tmpCatalyst).increment(volume);" << endl;
        cout << "Vectorsize " <<allSpecies.size()<<" - position " << tmpCatalyst << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("","exceptionerrorthrown");
    }

    if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
    {
        incMolProcedure(tmpCatalyst); // Increment total number of molecules and species
        incSpeciesProcedure(tmpCatalyst);
    }

	// The substrate and the complex are consumed (the first substrate has been already decremented during the complex formation reaction
	if ((tmpSubAmount > 0) && (tmpCpxAmount > 0))
	{
		// REACTION!!!
		
        allSpecies.at(tmpSubstrate).decrement(volume);
        if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
            decMolSpeciesProcedure(tmpSubstrate); // decrement total number of molecules and, if so, species
	
        allSpecies.at(tmpComplex).decrement(volume);
        if(!allSpecies.at(tmpComplex).getConcentrationFixed())
            decCpxProcedure(tmpComplex); // decrement total number of complexes token and, if so, types
		
		reactionFlag = true;
		if (debugLevel >= SMALL_DEBUG) 
		{
                        cout << "CONDENSATION AFTER complexes: " << allSpecies.at(tmpComplex).getNOTchargeMols()
                        << " - substrates: " << allSpecies.at(tmpSubstrate).getNOTchargeMols()
                        << " - catalyst: " << allSpecies.at(tmpCatalyst).getNOTchargeMols() << endl;
		}	
	}else{
		ExitWithError("performCondensation", "Complex or second substrate are not avalaible");
	}
	// Update catalysis and Reactions structure with a secure check on ID reaction
	if(allCatalysis.at(tmpIdCatalysis).getReactionID() == allReactions.at(tmpIdReaction).getID())
	{
                allCatalysis.at(tmpIdCatalysis).updateTotAmount();
                allReactions.at(tmpIdReaction).updateTotEvents();
	}else{
		ExitWithError("performCondensation", "Problem with reaction ID coherence");
	}
	// EVALUATE PRODUCT
	if(!newSpeciesEvaluation(allSpecies.at(tmpProduct).getSequence(), tmp__RndDoubleGen))
		ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performCondensation end" << endl;
	
	// Update reaction counter
	incCondensationCounter();
	return reactionFlag;
}

/**
 Perform ENDO CONDENSATION reaction
 @version 1.2
 @date 2011-02-12
 @param tmpCatalyst Catalyst (bound in the complex) ID
 @param tmpSubstrate second (or first, depend on the condensation type) substrate ID
 @param tmpProduct product ID
 @param acs_longInt tmpComplex Complex ID
 @param acs_longInt tmpSubstrate Substrate ID
 @param acs_longInt tmpProduct Product ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::perform_endo_Condensation(acs_longInt tmpCatalyst, acs_longInt tmpSubstrate, acs_longInt tmpProduct, 
											acs_longInt tmpComplex, acs_int tmpNRGside, acs_longInt tmpIdReaction, 
											acs_longInt tmpIdCatalysis, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_Condensation start" << endl;
	
	bool reactionFlag = false;
	acs_longInt tmpSubAmount;
	acs_longInt tmpCpxAmount;


	
	// According to the NRG side position the right amount of molecules belonging to the complexes and substrates is selected
	switch (tmpNRGside) {
		case COMPLEXLOAD:
			tmpSubAmount = allSpecies.at(tmpSubstrate).getNOTchargeMols();
			tmpCpxAmount = allSpecies.at(tmpComplex).getChargeMols();
			break;
		case SUBSTRATELOAD:
			tmpSubAmount = allSpecies.at(tmpSubstrate).getChargeMols();
			tmpCpxAmount = allSpecies.at(tmpComplex).getNOTchargeMols();
			break;			
		default:
			tmpSubAmount = allSpecies.at(tmpSubstrate).getChargeMols(); 
			tmpCpxAmount = 	allSpecies.at(tmpComplex).getChargeMols();		
			break;
	}
	
	// check whether all the species amount of not loaded molecules to decrement are greater than 1
	if(tmpSubAmount == 0)
		ExitWithError("performCondensation", "Not loaded Substrate not Avalaible!!!");
	if(tmpCpxAmount == 0)
		ExitWithError("performCondensation", "Loaded Complex not Avalaible!!!");
	
	if (debugLevel >= SMALL_DEBUG) 
	{
		cout << "ENDOCONDENSATION BEFORE complexes: " << tmpCpxAmount
		<< " - substrates: " << tmpSubAmount
                << " - catalyst: " << allSpecies.at(tmpCatalyst).getAmount() << endl;
	}
	
	// REACTION! the catalyst come to be free
        allSpecies.at(tmpCatalyst).increment(volume);
    if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
    {
        incMolProcedure(tmpCatalyst); // Increment total number of molecules and species
        incSpeciesProcedure(tmpCatalyst);
    }
			
	// The substrate and the complex are consumed (the first substrate has been already decremented during the complex formation reaction
	if((tmpSubAmount > 0) && (tmpCpxAmount > 0))
	{		
            // REACTION!!!
		// According to the NRG side position complexes and/or substrates are uncharged 
		switch (tmpNRGside) {
			case COMPLEXLOAD:
				unchargeMolProcess(tmpComplex);
				break;
			case SUBSTRATELOAD:
				unchargeMolProcess(tmpSubstrate);
				break;			
			default:
				unchargeMolProcess(tmpComplex); 
				unchargeMolProcess(tmpSubstrate);		
				break;
		}		
		
                try{
                    allSpecies.at(tmpSubstrate).decrement(volume);
                    if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                        decMolSpeciesProcedure(tmpSubstrate); // decrement total number of molecules and, if so, species
                }catch(exception& e){
                    cout << "Error in perform_endo_condensation allSpecies.at(tmpSubstrate).decrement(volume)..." << endl;
                    cerr << "exception caught: " << e.what() << endl;
                    ExitWithError("perform_endo_condensation","exception error thrown");
                }

                try{
                    allSpecies.at(tmpComplex).decrement(volume);
                    if(!allSpecies.at(tmpComplex).getConcentrationFixed())
                        decCpxProcedure(tmpComplex); // decrement total number of complexes token and, if so, types
                }catch(exception& e){
                    cout << "Error in perform_endo_condensation allSpecies.at(tmpComplex).decrement(volume)..." << endl;
                    cerr << "exception caught: " << e.what() << endl;
                    ExitWithError("perform_endo_condensation","exception error thrown");
                }

		reactionFlag = true;
		if (debugLevel >= SMALL_DEBUG)
		{
                        cout << "ENDOCONDENSATION AFTER complexes: " << allSpecies.at(tmpComplex).getAmount()
                        << " - substrates: " << allSpecies.at(tmpSubstrate).getAmount()
                        << " - catalyst: " << allSpecies.at(tmpCatalyst).getAmount() << endl;
		}
	}else{
            ExitWithError("perform_endo_Condensation", "Complex or second substrate are not avalaible");
	}
	// Update catalysis and Reactions structure with a secure check on ID reaction
    if(allCatalysis.at(tmpIdCatalysis).getReactionID() == allReactions.at(tmpIdReaction).getID())
    {       try{
            allCatalysis.at(tmpIdCatalysis).updateTotAmount();
            allReactions.at(tmpIdReaction).updateTotEvents();
        }
        catch(exception&e)
        {
            cout<<" allCatalysis.at(tmpIdCatalysis).updateTotAmount(); and  allReactions.at(tmpIdReaction).updateTotEvents();" << endl;
            cout << "Vectorsize allCatalysis " <<allCatalysis.size()<<" - position " << tmpIdCatalysis << endl;
            cout << "Vectorsize allReactions " <<allReactions.size()<<" - position " << tmpIdReaction << endl;
            cerr << "exceptioncaught:" << e.what() << endl;
            ExitWithError("Update catalysis and Reactions structure with a secure check on ID reaction","exceptionerrorthrown");
        }
    }else{
            ExitWithError("performCondensation", "Problem with reaction ID coherence");
	}
	// EVALUATE PRODUCT
	if(!newSpeciesEvaluation(allSpecies.at(tmpProduct).getSequence(), tmp__RndDoubleGen))
            ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_Condensation end" << endl;
	
	// Update reaction counter
	incEndoCondensationCounter();
	return reactionFlag;
}

/**
 Perform CLEAVAGE reaction
 @version 1.2
 @date 2011.02.12
 @param acs_longInt tmpSubstrate Substrate ID
 @param acs_longInt tmpProduct_I Product 1 ID
 @param acs_longInt tmpProduct_II Product 2 ID
 @param tmpIdReaction Rections ID
 @param tmpIdCatalysis Catalysis ID
 @param MTRand& tmp__RndDoubleGen random number generator
 */
bool environment::performCleavage(acs_longInt tmpSubstrate, acs_longInt tmpProduct_I, acs_longInt tmpProduct_II, acs_longInt tmpIdReaction, acs_longInt tmpIdCatalysis, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performCleavage start" << endl;

	bool reactionFlag = false;
	bool avalability = true;
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "\t\t\t|- Species " <<  tmpSubstrate << " will be cleaved" << endl;

    try{
	
	// substrate decrement
	if((!allSpecies.at(tmpSubstrate).getAmount() > 0) || (!allSpecies.at(allCatalysis.at(tmpIdCatalysis).getCat()).getAmount() > 0))
	{
		ExitWithError("performCleavage", "Substrate or catalyst not Avalaible!!!");
	}else{
		if(allCatalysis.at(tmpIdCatalysis).getCat() == tmpSubstrate)
		{
			if(allSpecies.at(tmpSubstrate).getAmount() < 2)
				avalability = false;
		}
		if(avalability)
		{
                        allSpecies.at(tmpSubstrate).decrement(volume);
            if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
			reactionFlag = true;
		}else{
			ExitWithError("performCleavage", "Substrate not Avalaible, when catalyst and substrate are the same, at least of that should be avalable");
		}
	}

    }
    catch(exception&e)
    {
    cout<<"" << endl;
    cerr << "exceptioncaught:" << e.what() << endl;
    ExitWithError("something wrong in substrate decrement within performCleavag method","exceptionerrorthrown");
    }

    try{

        // Update catalysis and Reactions structure with a secure check on ID reaction
        if(allCatalysis.at(tmpIdCatalysis).getReactionID() == allReactions.at(tmpIdReaction).getID())
        {
            allCatalysis.at(tmpIdCatalysis).updateTotAmount();
            allReactions.at(tmpIdReaction).updateTotEvents();
        }else{
            ExitWithError("performCleavage", "Problem with reaction ID coherence");
        }

    }
    catch(exception&e)
    {
        cout<<"Update catalysis and Reactions structure with a secure check on ID reaction" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in within performCleavag method","exceptionerrorthrown");
    }

    try{
        // EVALUATE PRODUCT 1
        if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_I).getSequence(), tmp__RndDoubleGen))
            ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
    }
    catch(exception&e)
    {
        cout<<" if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_I).getSequence(), tmp__RndDoubleGen))" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in evaluating product 1 in performCleavage method","exceptionerrorthrown");
    }

    try{
        // EVALUATE PRODUCT 2
        if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_II).getSequence(), tmp__RndDoubleGen))
            ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
    }
    catch(exception&e)
    {
        cout<<" if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_II).getSequence(), tmp__RndDoubleGen))" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in evaluating product 2 in performCleavage method","exceptionerrorthrown");
    }

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performCleavage end" << endl;

        // Update reaction counter
        incCleavageCounter();
	return reactionFlag;
}

/**
 Perform ENDO_CLEAVAGE reaction
 @version 1.2
 @date 2010.11.08
 @param acs_longInt tmpSubstrate Substrate ID
 @param acs_longInt tmpProduct_I Product 1 ID
 @param acs_longInt tmpProduct_II Product 2 ID
 @param acs_int tmpNrgTarget Energy Target --> catalyst loaded, substrate loaded or both
 @param tmpIdReaction Rections ID
 @param tmpIdCatalysis Catalysis ID
 @param MTRand& tmp__RndDoubleGen random number generator
 */
bool environment::perform_endo_Cleavage(acs_longInt tmpSubstrate, acs_longInt tmpProduct_I, acs_longInt tmpProduct_II,
										acs_int tmpNRGside, acs_longInt tmpIdReaction, acs_longInt tmpIdCatalysis, MTRand& tmp__RndDoubleGen)
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_Cleavage start" << endl;

    bool reactionFlag = false;

    if(debugLevel >= SMALL_DEBUG)
            cout << "\t\t\t|- Species " <<  tmpSubstrate << " will be cleaved" << endl;

    try{

        switch (tmpNRGside) {
        case CATALYSTLOAD:
            if((!allSpecies.at(allCatalysis.at(tmpIdCatalysis).getCat()).getChargeMols() > 0) || (!allSpecies.at(tmpSubstrate).getNOTchargeMols() > 0))
            {
                ExitWithError("perform_endo_Cleavage", "Loaded substrate not Avalaible!!!");
            }else{
                unchargeMolProcess(allCatalysis.at(tmpIdCatalysis).getCat());
                allSpecies.at(tmpSubstrate).decrement(volume);
                if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                    decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                reactionFlag = true;
            }
            break;
        case SUBSTRATELOAD:
            if((!allSpecies.at(allCatalysis.at(tmpIdCatalysis).getCat()).getNOTchargeMols() > 0) || (!allSpecies.at(tmpSubstrate).getChargeMols() > 0))
            {
                ExitWithError("perform_endo_Cleavage", "Loaded substrate not Avalaible!!!");
            }else{
                unchargeMolProcess(tmpSubstrate);
                allSpecies.at(tmpSubstrate).decrement(volume);
                if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                    decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                reactionFlag = true;
            }
            break;
        default:
            if((!allSpecies.at(allCatalysis.at(tmpIdCatalysis).getCat()).getChargeMols() > 0) || (!allSpecies.at(tmpSubstrate).getChargeMols() > 0))
            {
                ExitWithError("perform_endo_Cleavage", "Loaded substrate not Avalaible!!!");
            }else{
                unchargeMolProcess(allCatalysis.at(tmpIdCatalysis).getCat());
                unchargeMolProcess(tmpSubstrate);
                allSpecies.at(tmpSubstrate).decrement(volume);
                if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                    decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                reactionFlag = true;
            }
            break;
        }

    }
    catch(exception&e)
    {
        cout<<"switch (tmpNRGside)" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in switch block of method perform_endo_Cleavage","exceptionerrorthrown");
    }

    try{

        // Update catalysis and Reactions structure with a secure check on ID reaction
        if(allCatalysis.at(tmpIdCatalysis).getReactionID() == allReactions.at(tmpIdReaction).getID())
        {
            allCatalysis.at(tmpIdCatalysis).updateTotAmount();
            allReactions.at(tmpIdReaction).updateTotEvents();
        }else{
            ExitWithError("perform_endo_Cleavage", "Problem with reaction ID coherence");
        }

    }
    catch(exception&e)
    {
        cout<<"Update catalysis and Reactions structure with a secure check on ID reaction" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in if block in perform_endo_Cleavage method","exceptionerrorthrown");
    }

    try{
        // EVALUATE PRODUCT 1
        if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_I).getSequence(), tmp__RndDoubleGen))
            ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
    }
    catch(exception&e)
    {
        cout<<"if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_I).getSequence(), tmp__RndDoubleGen))" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in evaluating product 1 in  form_endo_Cleavage method","exceptionerrorthrown");
    }


    try{
        // EVALUATE PRODUCT 2
        if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_II).getSequence(), tmp__RndDoubleGen))
            ExitWithError("newSpeciesEvaluation", "Problems during the new species evalutation");
    }
    catch(exception&e)
    {
        cout<<"if(!newSpeciesEvaluation(allSpecies.at(tmpProduct_II).getSequence(), tmp__RndDoubleGen))" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in evaluating product 2 in  form_endo_Cleavage method","exceptionerrorthrown");
    }


    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_Cleavage end" << endl;

    // Update reaction counter
    incEndoCleavageCounter();
    return reactionFlag;
}

/**
 Perform COMPLEX FORMATION reaction
 @version 1.2
 @date 2011.02.13
 @param acs_longInt tmpCatalyst Catalyst ID
 @param acs_longInt tmpSubstrate Substrate ID
 @tmpCatalysisID Catalysis ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::performComplexFormation(acs_longInt tmpCatalyst, acs_longInt tmpSubstrate, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performComplexFormation start" << endl;
	
	bool reactionFlag = false;
	bool avalability = true;
        string strErr = "";
	
	if(debugLevel >= SMALL_DEBUG)
            cout << "\t\t\t|- Complex between " <<  tmpCatalyst << "(" << allSpecies.at(tmpCatalyst).getSequence()  << "#" << allSpecies.at(tmpCatalyst).getNOTchargeMols() << ") and "
             << tmpSubstrate << "(" << allSpecies.at(tmpSubstrate).getSequence()  << "#" << allSpecies.at(tmpSubstrate).getNOTchargeMols() << ") will be formed -> CP: "
             << allSpecies.at(tmpCatalyst).getSequence().length() << endl;

    try{
        // IF CATALYST AND SUBSTRATE ARE EQUAL AT LEAST 2 MOLECULES HAVE TO BE PRESENT
        if(tmpCatalyst == tmpSubstrate)
        {
            if(allSpecies.at(tmpSubstrate).getNOTchargeMols() < 2)
            {
                avalability = false;
            }
        }
    }
    catch(exception&e)
    {
        cout<<"IF CATALYST AND SUBSTRATE ARE EQUAL AT LEAST 2 MOLECULES HAVE TO BE PRESENT" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in if(tmpCatalyst == tmpSubstrate) block in performComplexFormation ","exceptionerrorthrown");
    }

	if(avalability)
	{
        string tmpComplex;

        try{
            // CREATE COMPLEX
            tmpComplex = allSpecies.at(tmpCatalyst).getSequence() + allSpecies.at(tmpSubstrate).getSequence();
        }
        catch(exception&e)
        {
            cout<<"tmpComplex = allSpecies.at(tmpCatalyst).getSequence() + allSpecies.at(tmpSubstrate).getSequence();" << endl;
            cerr << "exceptioncaught:" << e.what() << endl;
            ExitWithError("something wrong in creating complex in performComplexFormation","exceptionerrorthrown");
        }

        if(allSpecies.at(tmpCatalyst).getNOTchargeMols() < 1 || allSpecies.at(tmpSubstrate).getNOTchargeMols() < 1)
		{
				avalability = false;
		}

		bool tempNrgType = ENDOERGONIC;
		
		if(avalability)
		{
                        allSpecies.at(tmpCatalyst).decrement(volume);
            if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
                decMolSpeciesProcedure(tmpCatalyst); // Update overall number of species and molecules

                        allSpecies.at(tmpSubstrate).decrement(volume);
            if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
			reactionFlag = true;
		}else{
			ExitWithError("performComplexFormation", strErr);
		}
		// EVALUATE COMPLEX (allSpecies.at(tmpCatalyst).getSequence().length() is definitly the cutting point)
		if(!complexEvaluation(tmpComplex, tmp__RndDoubleGen, allSpecies.at(tmpCatalyst).getSequence().length(),
                                                          tmpCatalyst, tmpSubstrate, tempNrgType))
				ExitWithError("complexEvaluation", "Problems during the complex evalutation");
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performComplexFormation end" << endl;
		
	return reactionFlag;	
}
/**
 Perform ENDO COMPLEX FORMATION reaction
 @version 1.2
 @date 2011.04.13
 @param acs_longInt tmpCatalyst Catalyst ID
 @param acs_longInt tmpSubstrate Substrate ID
 @tmpCatalysisID Catalysis ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::perform_endo_ComplexFormation(acs_longInt tmpCatalyst, acs_longInt tmpSubstrate, acs_int tmpNRGSide, MTRand& tmp__RndDoubleGen)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_ComplexFormation start" << endl;
	
	bool reactionFlag = false; //This flag has to becames true to validate the reaction
        //string strErr = "";
	string tmpComplex;
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "\t\t\t|- Complex between " <<  tmpCatalyst << "(" << allSpecies.at(tmpCatalyst).getSequence()  << "#" << allSpecies.at(tmpCatalyst).getNOTchargeMols() << ") and "
		<< tmpSubstrate << "(" << allSpecies.at(tmpSubstrate).getSequence()  << "#" << allSpecies.at(tmpSubstrate).getChargeMols() << ") will be formed -> CP: "
		<< allSpecies.at(tmpCatalyst).getSequence().length() << endl;

    try{
        // CREATE COMPLEX
        tmpComplex = allSpecies.at(tmpCatalyst).getSequence() + allSpecies.at(tmpSubstrate).getSequence();
    }
    catch(exception&e)
    {
        cout<<"tmpComplex = allSpecies.at(tmpCatalyst).getSequence() + allSpecies.at(tmpSubstrate).getSequence();" << endl;
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in creating complex in perform_endo_ComplexFormation","exceptionerrorthrown");
    }

        if(tmpNRGSide == SUBSTRATELOAD)
        {
            if((allSpecies.at(tmpCatalyst).getNOTchargeMols() > 0) && (allSpecies.at(tmpSubstrate).getChargeMols() > 0))
            {
                            allSpecies.at(tmpCatalyst).decrement(volume);
                            if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpCatalyst); // Update overall number of species and molecules

                            unchargeMolProcess(tmpSubstrate);
                            allSpecies.at(tmpSubstrate).decrement(volume);
                            if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                            reactionFlag = true;
            }else{
                            ExitWithError("perform_endo_ComplexFormation", "Catalyst or Substrate are not avalaible");
            }
        }
        if(tmpNRGSide == CATALYSTLOAD)
        {
            if((allSpecies.at(tmpCatalyst).getChargeMols() > 0) && (allSpecies.at(tmpSubstrate).getNOTchargeMols() > 0))
            {
                            unchargeMolProcess(tmpCatalyst);
                            allSpecies.at(tmpCatalyst).decrement(volume);
                            if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpCatalyst); // Update overall number of species and molecules

                            allSpecies.at(tmpSubstrate).decrement(volume);
                            if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                            reactionFlag = true;
            }else{
                            ExitWithError("perform_endo_ComplexFormation", "Catalyst or Substrate are not avalaible");
            }
        }
        if(tmpNRGSide == BOTHLOAD)
            {
            if((allSpecies.at(tmpCatalyst).getChargeMols() > 0) && (allSpecies.at(tmpSubstrate).getChargeMols() > 0))
            {
                            unchargeMolProcess(tmpCatalyst);
                            allSpecies.at(tmpCatalyst).decrement(volume);
                            if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpCatalyst); // Update overall number of species and molecules

                            unchargeMolProcess(tmpSubstrate);
                            allSpecies.at(tmpSubstrate).decrement(volume);
                            if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
                                decMolSpeciesProcedure(tmpSubstrate); // Update overall number of species and molecules
                            reactionFlag = true;
            }else{
                            ExitWithError("perform_endo_ComplexFormation", "Catalyst or Substrate are not avalaible");
            }
        }
	// EVALUATE COMPLEX (allSpecies.at(tmpCatalyst).getSequence().length() is definitly the cutting point)
	if(!complexEvaluation(tmpComplex, tmp__RndDoubleGen, allSpecies.at(tmpCatalyst).getSequence().length(),
                                                  tmpCatalyst, tmpSubstrate, ESOERGONIC))
			ExitWithError("complexEvaluation", "Problems during the complex evalutation");
		
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::perform_endo_ComplexFormation end" << endl;
	return reactionFlag;	
}


/**
 Perform COMPLEX DISASSOCIATION reaction
 @version 1.1
 @date 2010.06.08
 @param acs_longInt tmpComplex Complex ID
 @param MTRand& tmp__RndDoubleGen random generator
 */
bool environment::performComplexDissociation(acs_longInt tmpComplex, acs_longInt tmpCatalyst, acs_longInt tmpSubstrate, MTRand& tmp__RndDoubleGen)
{
        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performComplexDissociation start" << endl;

        if(debugLevel >= SMALL_DEBUG)
            cout << "\t\t\t|-COMPLEX " <<  tmpComplex << " will be degradated" << endl;
        bool reactionFlag = false;

    try{

        // Complex (loaded or not loaded) to dissociate is chosen according to the total amount of loaded and not loaded complexes present in the system
        acs_double ratioLoadedCpx = allSpecies.at(tmpComplex).getChargeMols() / allSpecies.at(tmpComplex).getAmount();
        acs_double rndNumb = tmp__RndDoubleGen();

        if(debugLevel >= SMALL_DEBUG)
        {
            cout << "\t\t\t\t|- BEFORE: Complexes[" << allSpecies.at(tmpComplex).getSequence() << "]- Loaded:" << allSpecies.at(tmpComplex).getChargeMols()
                 << "- Not Loaded:" << allSpecies.at(tmpComplex).getNOTchargeMols()
                 << " - Catalysts[" << allSpecies.at(tmpCatalyst).getSequence() << "]: " << allSpecies.at(tmpCatalyst).getAmount()
                 << " - Substrates[" << allSpecies.at(tmpSubstrate).getSequence() << "]: " << allSpecies.at(tmpSubstrate).getAmount() << endl;
        }

        if(rndNumb > ratioLoadedCpx)
        {
            // DECREMENT TOTAL AMOUNT OF THIS COMPLEX (not loaded)
            if(allSpecies.at(tmpComplex).getNOTchargeMols() < 1)
            {
                ExitWithError("performComplexDissociation", "There are not avalaible not loaded complexes to dissociate");
            }else{
                allSpecies.at(tmpComplex).decrement(volume);
                if(!allSpecies.at(tmpComplex).getConcentrationFixed())
                    decCpxProcedure(tmpComplex);
                reactionFlag = true;
            }
        }else{
            // DECREMENT TOTAL AMOUNT OF THIS COMPLEX (loaded)
            if(allSpecies.at(tmpComplex).getChargeMols() < 1)
            {
                ExitWithError("performComplexDissociation", "There are not avalaible loaded complexes to dissociate");
            }else{
                unchargeMolProcess(tmpComplex);
                allSpecies.at(tmpComplex).decrement(volume);
                if(!allSpecies.at(tmpComplex).getConcentrationFixed())
                    decCpxProcedure(tmpComplex);
                reactionFlag = true;
            }
        }

        // UPDATE CATALYST AND SUBSTRATE
        allSpecies.at(tmpCatalyst).increment(volume);
        if(!allSpecies.at(tmpCatalyst).getConcentrationFixed())
        {
            incMolProcedure(tmpCatalyst); // Increment total number of catalyst
            incSpeciesProcedure(tmpCatalyst);
        }

        allSpecies.at(tmpSubstrate).increment(volume);
        if(!allSpecies.at(tmpSubstrate).getConcentrationFixed())
        {
            incMolProcedure(tmpSubstrate); // Increment total number of substrate
            incSpeciesProcedure(tmpSubstrate);
        }

        if(debugLevel >= SMALL_DEBUG)
        {
            cout << "\t\t\t\t|- AFTER: Complexes[" << allSpecies.at(tmpComplex).getSequence() << "]- Loaded:" << allSpecies.at(tmpComplex).getChargeMols()
                 << "- Not Loaded:" << allSpecies.at(tmpComplex).getNOTchargeMols()
                 << " - Catalysts: " << allSpecies.at(tmpCatalyst).getAmount()
                 << " - Substrates: " << allSpecies.at(tmpSubstrate).getAmount() << endl;
        }

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in performComplexDissociation","exceptionerrorthrown");
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performComplexDissociation end" << endl;

    return reactionFlag;
}

//TR
/*
 Perform PHOSPHORILATION reaction
 @version 1.0
 @param acs_longInt tmpSpecies Species ID
 @date 2010-05-25

bool environment::performPhosphorilation(acs_longInt tmpSpecies)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performPhosphorilation start" << endl;
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "\t\t\t|-Species " << tmpSpecies << " will be Phosphorilated" << endl;
	bool reactionFlag = false;
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t\t\t|- BEFORE: loaded molecules[" << allSpecies[tmpSpecies].getSequence() << "]: " << allSpecies[tmpSpecies].getChargeMols() << endl;
		cout << "\t\t\t\t|- BEFORE: loaded carriers[" << nrgCarrier.getSequence() << "]: " << nrgCarrier.getChargeMols() << endl;
	}
	
	// Molecule phosphorilation
	if(!allSpecies.at(tmpSpecies).getNOTchargeMols() > 0)
	{
		ExitWithError("chargeMol", "Problems during the PHOSPHORILATION process, no molecules to load");
	}else{
		if(!allSpecies[tmpSpecies].chargeMol())
			ExitWithError("chargeMol", "Problems during the PHOSPHORILATION process, in particular loaded molecules are more than the unloaded molecules");
		else
			reactionFlag = true;
	}

        // Increase the counter of loaded molecules
        incOverallLoadedMolsCounter();

	
	// Decrease the number of loaded energy carriers
	if(!nrgCarrier.unchargeMol())
		ExitWithError("unchargeMol", "Problems during the PHOSPHORILATION process, in particular loaded carriers are more than the unloaded molecules");	
	else
		reactionFlag = true;
	
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t\t\t|- AFTER: loaded molecules[" << allSpecies[tmpSpecies].getSequence() << "]: " << allSpecies[tmpSpecies].getChargeMols() << endl;
		cout << "\t\t\t\t|- AFTER: loaded carriers[" << nrgCarrier.getSequence() << "]: " << nrgCarrier.getChargeMols() << endl;
	}
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\tenvironment::performPhosphorilation end" << endl;
	
	return reactionFlag;
}*/

/**
 Evaluate new species
 @version 1.0
 @param string tmpNewSpecies New species sequence to evaluate 
 @param MTRand& tmp___RndDoubleGen random number generator
 */
bool environment::newSpeciesEvaluation(string tmpNewSpecies, MTRand& tmp___RndDoubleGen)
{
        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::newSpeciesEvaluation start" << endl;

        bool newSpeciesFlag = true; // Function Flag Control
        bool tmpNotEqualSeqBetweenTwoSpecies = true; // True whether there is not equal species
        bool tmpAlreadyEvaluated = false; // True if the species has been already evaluated
        bool toEvaluate = true; // another control to check whether the evaluation is to do
        acs_longInt tmpIdSpeciesToEvaluate = 0;
        acs_int tmpEnergizable = NOTENERGIZABLE;

        if(debugLevel >= SMALL_DEBUG)
            cout << "\t\t\t|- New Species: " << tmpNewSpecies << endl;

    try{

        //CHECK WHETHER THE SPECIES (OR COMPLEX) IS ALREADY PRESENT
        for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
        {
            if((allSpecies.at(i).getSequence() == tmpNewSpecies) && (allSpecies.at(i).getComplexCutPnt() == 0)) // IF THE SPECIES IS ALREADY PRESENT
            {
                if(allSpecies.at(i).getAmount() == 0)
                    allSpecies.at(i).rebornsIncrement(); // IF THE SPECIES REAPPEAR THE REBORN COUNTER IS UPDATED
                allSpecies.at(i).increment(volume); // INCREMENT THE NUMBER OF ELEMENTS OF THIS SPECIES
                if(!allSpecies.at(i).getConcentrationFixed())
                {
                    incMolProcedure(i); // Increment overall amount of species
                    incSpeciesProcedure(i);
                }

                tmpNotEqualSeqBetweenTwoSpecies = false; // IF THE SPECIES IS ALREADY PRESENT
                tmpIdSpeciesToEvaluate = i; // SET THE ALREADY PRESENT ID OF THE SPECIES
                if(allSpecies.at(i).getEvaluated() == 1) // IF THE SPECIES HAS BEEN ALSO EVALUATED
                {
                    tmpAlreadyEvaluated = true;
                }else{
                    if(allSpecies.at(i).getComplexCutPnt() == 0) // IF THE SPECIES IS NOT A COMPLEX
                    {
                        // IF THE SPECIES IS ALREADY PRESENT BUT NOT EVALUATED
                        // PRECIPITATION AND DIFFUSIO0N CONTRIBUTE COMPUTATION
                        acs_double tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, 1);
                        allSpecies.at(i).setDiffusion(tmpDiffusionContribute);
                        bool tmpSolubilityState = setSolubility(allSpecies.at(i).getSequenceLength(), tmp___RndDoubleGen);

                        // IN THIS CASE SET SOLUBILITY REFERES TO THE SPECIES OBJECT
                        allSpecies.at(i).setSolubility(tmpSolubilityState);
                        allSpecies.at(i).setKphospho(K_nrg);
                        allSpecies.at(i).setEvaluated(); // IF the reactions have not been yet created the molecules evalutation is setting on 1 and the
                        // reactions will be created below
                    }
                }
                break;
            }
        }

        //IF THE MOLECULES IS NOT YET EVALUATED
        if(tmpAlreadyEvaluated == false)
        {
            acs_longInt totalNumberOfConceivableReactions = 0;
            // IF THE SPECIES IS ACTUALLY NEW
            if(tmpNotEqualSeqBetweenTwoSpecies == true)
            {
                // PRECIPITATION AND DIFFUSION CONTRIBUTE COMPUTATION
                acs_double tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, tmpNewSpecies.length());

                bool tmpSolubilityState = setSolubility(tmpNewSpecies.length(), tmp___RndDoubleGen);

                // CREATE NEW SPECIES OBJECT AND STORE IT INTO THE ENVIRONMENT SPECIES VECTOR
                tmpIdSpeciesToEvaluate = (acs_longInt)allSpecies.size();
                if(tmp___RndDoubleGen() < ratioSpeciesEnergizable){tmpEnergizable=ENERGIZABLE;}else{tmpEnergizable=NOTENERGIZABLE;}
                allSpecies.push_back(species(tmpIdSpeciesToEvaluate, tmpNewSpecies, (acs_longInt)1, tmpDiffusionContribute,
                                             tmpSolubilityState, 0, 0, 1, volume, K_nrg,tmpEnergizable, influx_rate, maxLOut));

                if(!allSpecies.at(tmpIdSpeciesToEvaluate).getConcentrationFixed())
                {
                    incSpeciesProcedure(tmpIdSpeciesToEvaluate);
                    incMolProcedure(tmpIdSpeciesToEvaluate);
                }

                toEvaluate = false;
                if(debugLevel >= SMALL_DEBUG)
                    cout << "\t\t\t\t|- New Species " <<  tmpNewSpecies << " has been created" << endl;

            }

            if(toEvaluate)
            {
                // SET REACTIONS FOR THIS NEW SPECIES
                // COPY ALL THE ALREADY EVALUATED SPECIES ID IN A TEMPORARY VECTOR
                vector<acs_longInt> tmpAlreadyEvaluatedSpeciesVector;
                for(acs_longInt tmpS = 0; tmpS < (acs_longInt)allSpecies.size(); tmpS++)
                {
                    if(allSpecies.at(tmpS).getEvaluated() == 1)
                    {
                        // DEEP AND SECURE CHECK
                        if(allSpecies.at(tmpS).getComplexCutPnt() > 0)
                        {
                            ExitWithError("newSpeciesEvaluation", "A complex cannot be evaluated and involved in reactions!!!");
                        }else{
                            tmpAlreadyEvaluatedSpeciesVector.push_back(tmpS);
                        }
                    }
                }

                // COMPUTE TOTAL NUMBER OF CONCEIVABLE REACTIONS CONSIDERING ALREADY EVALUATED MOLECULES
                for(acs_int presSpeciID = 0; presSpeciID < (acs_longInt)tmpAlreadyEvaluatedSpeciesVector.size(); presSpeciID++)
                {
                    totalNumberOfConceivableReactions += allSpecies.at(tmpAlreadyEvaluatedSpeciesVector.at(presSpeciID)).getSequenceLength() - 1;
                }
                totalNumberOfConceivableReactions += pow((double)tmpAlreadyEvaluatedSpeciesVector.size(), 2.0);

                if(debugLevel >= HIGH_DEBUG){printAllSpeciesIdAndSequence();}
                if(debugLevel >= RUNNING_VERSION)
                {
                    cout << "\t\t|-------------------------------------------------------|" << endl;
                    cout << "\t\t|- !! EVENT !! New species has been evaluated           |" << endl;
                    cout << "\t\t|- ID: " << allSpecies.at(tmpIdSpeciesToEvaluate).getID() << " - Sequence: " << allSpecies.at(tmpIdSpeciesToEvaluate).getSequence() << endl;
                    cout << "\t\t|- Total new number of conceivable reactions:" << totalNumberOfConceivableReactions << endl;
                }

                // COMPUTE THE REAL NUMBER OF REACTIONS FOR THIS SPECIES
                acs_int reactionsForThisSpecies;
                reactionsForThisSpecies = computeSngSpeciesRctsNumber(totalNumberOfConceivableReactions, tmp___RndDoubleGen);

                if(debugLevel >= RUNNING_VERSION)
                {
                    cout << "\t\t|- Number of reaction to catalyze: " << reactionsForThisSpecies << endl;
                    cout << "\t\t|-------------------------------------------------------|" << endl;
                }

                // CREATE REACTIONS FOR THIS SPECIFIC SPECIES
                if((reactionsForThisSpecies > 0) && (allSpecies.at(tmpIdSpeciesToEvaluate).getSolubility() == SOLUBLE))
                {
                    if(!createReactionsForThisSpecies(tmpIdSpeciesToEvaluate, reactionsForThisSpecies, tmp___RndDoubleGen, tmpAlreadyEvaluatedSpeciesVector, NEWREACTIONS))
                        ExitWithError("createReactionsForThisSpecies", "	|- !*!*!*! Problem with the reactions creation");
                }

                if(debugLevel >= SMALL_DEBUG){cout << "\t\t|- DONE!!! " << endl;}

                // IF the new species is soluble
                if(allSpecies.at(tmpIdSpeciesToEvaluate).getSolubility() == SOLUBLE)
                {
                    // ------------------------------------------
                    // NOW I HAVE TO UPDATE OLD SPECIES REACTIONS
                    // ------------------------------------------
                    // For each evaluated species
                    acs_longInt tmpIDcatalysis = 0;
                    acs_longInt tmpReactionsAlreadyCatbyThisSpecies = 0;
                    acs_longInt tmpNEWReactionsForThisOldSpecies = 0;
                    for(acs_longInt alreadyEvaID = 0; alreadyEvaID < (acs_longInt)tmpAlreadyEvaluatedSpeciesVector.size(); alreadyEvaID++)
                    {
                        // IF THE SPECIES IS NOT THE SAME OF THE SPECIES EVALUATED ABOVE
                        if(tmpAlreadyEvaluatedSpeciesVector.at(alreadyEvaID) != tmpIdSpeciesToEvaluate)
                        {
                            // UNTIL THE SPECIES ID WILL BE GREATER THAN THE EVALUATING SPECIES (in this way I don't have to go through all
                            // the vector but only until the species
                            // (acs_longInt)allCatalysis.size() > tmpIDcatalysis is necessary to avoid an "out of range" error
                            while((acs_longInt)allCatalysis.size() > tmpIDcatalysis && allCatalysis.at(tmpIDcatalysis).getCat() <= tmpAlreadyEvaluatedSpeciesVector.at(alreadyEvaID))
                            {
                                // IF THE SPECIES IS WHICH WE WANT WE COUNT ALL THE REACTIONS CATALYZED BY THIS SPECIES
                                if(allCatalysis.at(tmpIDcatalysis).getCat() == tmpAlreadyEvaluatedSpeciesVector.at(alreadyEvaID))
                                {
                                    tmpReactionsAlreadyCatbyThisSpecies++;
                                }
                                tmpIDcatalysis++;
                            }
                            // NOW THE GAP BETWEEN THE NEW REAL NUMBER OF POSSIBLE REACTIONS AND THE NUMBER OF ALREADY PRESENT REACTIONS WILL BE FILLED UP
                            // Only species longer than nonCatalyticMaxLength can catalyse reactions!!!
                            if(allSpecies.at(tmpAlreadyEvaluatedSpeciesVector.at(alreadyEvaID)).getSequenceLength() > nonCatalyticMaxLength)
                            {
                                reactionsForThisSpecies = computeSngSpeciesRctsNumber(totalNumberOfConceivableReactions, tmp___RndDoubleGen);
                            }else{
                                reactionsForThisSpecies = 0;
                            }

                            if(reactionsForThisSpecies > 0)
                            {
                                // COMPUTE GAP BETWEEN THE NEW NUMBER OF POSSIBLE REACTIONS AND THE REACTIONS ALREADY CATALYZED
                                if(reactionsForThisSpecies > tmpReactionsAlreadyCatbyThisSpecies)
                                {
                                    //tmpNEWReactionsForThisOldSpecies = reactionsForThisSpecies - tmpReactionsAlreadyCatbyThisSpecies;
                                    tmpNEWReactionsForThisOldSpecies = computeSngSpeciesRctsNumber(reactionsForThisSpecies - tmpReactionsAlreadyCatbyThisSpecies, tmp___RndDoubleGen);
                                }else{
                                    tmpNEWReactionsForThisOldSpecies = 0;
                                }
                                if(debugLevel >= MEDIUM_DEBUG)
                                {
                                    cout << "\t\t|- TotRcts: " << reactionsForThisSpecies << " - ";
                                    cout << "AlreadyCatRcts: " << tmpReactionsAlreadyCatbyThisSpecies << " - ";
                                    cout << "NewRcts: " << tmpNEWReactionsForThisOldSpecies << endl;
                                }

                                // IF THERE IS SOME NEW REACTION TO CREATE
                                if(tmpNEWReactionsForThisOldSpecies > 0)
                                {
                                    if(!createReactionsForThisSpecies(tmpAlreadyEvaluatedSpeciesVector.at(alreadyEvaID),
                                                                      tmpNEWReactionsForThisOldSpecies, tmp___RndDoubleGen,
                                                                      tmpAlreadyEvaluatedSpeciesVector, UPGRADEREACTIONS))
                                    {
                                        ExitWithError("createReactionsForThisSpecies", "	|- !*!*!*! Problem with the reactions creation");
                                    }
                                }
                            }
                            tmpReactionsAlreadyCatbyThisSpecies = 0;
                        }// end not just evaluated
                    } // end for all species to upgrade the reactions network
                } // if(allSpecies.at(tmpIdSpeciesToEvaluate).getSolubility() == SOLUBLE)
            } // end if to evaluate
        }

        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::newSpeciesEvaluation end" << endl;    

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("something wrong in newSpeciesEvaluation method","exceptionerrorthrown");
    }

    return newSpeciesFlag;
}

/**
 Evaluate new species
 @version 1.1
 @date 2010-06-04
 @param string tmpNewSpecies New species sequence to evaluate 
 @param MTRand& tmp___RndDoubleGen random number generator
 @param tmpCuttingPnt Complex cutting point
 @param tmpCatalyst_ID catalyst ID
 @param tmpSubstrate_ID substrate ID
 @param tmp_catalysisID catalysis ID
 @param tmpCpxType ENDOERGONIC or ESOERGONIC
 */
bool environment::complexEvaluation(string tmpComplex, MTRand& tmp___RndDoubleGen, acs_int tmpCuttingPnt, 
                                    acs_int tmpCatalyst_ID, acs_int tmpSubstrate_ID, bool tmpCpxType)
{
        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::ComplexEvaluation start" << endl;

        bool newComplexFlag = true; // Function Flag Control
        bool tmpNotEqualSeqBetweenTwoSpecies = true; // True whether there is not equal species
        acs_longInt tmpIdSpeciesToEvaluate = 0;

        if(debugLevel >= SMALL_DEBUG)
            cout << "\t\t\t|- New Species: " << tmpComplex << " CP: " << tmpCuttingPnt << endl;

    try{

        //CHECK WHETHER THE SPECIES (OR COMPLEX) IS ALREADY PRESENT
        for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
        {
            if((allSpecies.at(i).getSequence() == tmpComplex) & (allSpecies.at(i).getComplexCutPnt() > 0)) // IF THE COMPLEX IS ALREADY PRESENT
            {
                if(allSpecies.at(i).getComplexCutPnt() == tmpCuttingPnt) // IF THE CUTTING POINT IS THE SAME
                {
                    allSpecies.at(i).increment(volume); // INCREMENT CHE NUMBER OF ELEMENTS OF THIS SPECIES THAT COULD BE ALSO A COMPLEX
                    if(allSpecies.at(i).getAmount() == 1){incNumberOfCpx();} // If the number of complex was 0 the total number of complex is increased
                    incNumberOfCpxMols(); // Increase the total number of complex copies

                    if(tmpCpxType == ESOERGONIC)
                    {
                        allSpecies.at(i).chargeMol();
                        incOverallLoadedMolsCounter();
                    } // If the complex is formed of loaded molecules it is considered loaded as well

                    tmpNotEqualSeqBetweenTwoSpecies = false; // IF THE SPECIES IS ALREADY PRESENT
                    tmpIdSpeciesToEvaluate = i; // SET THE ALREADY PRESENT ID OF THE SPECIES
                    //IF THE SPECIES IS A COMPLEX
                    // THE SPECIE IS A COMPLEX, ONLY DIFFUSION CONSTANT HAS TO BE CREATED, WE ASSUEME THAT DEGRADATION IS MORE FASTER THAN
                    // PRECIPITATION, HENCE PRECIPITATION IS SET TO 0 (NOT COMPUTED)
                    if(allSpecies.at(i).getDiffusionEnh() == 0)
                    {
                        acs_double tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, 1);
                        allSpecies.at(i).setDiffusion(tmpDiffusionContribute);
                    }
                    break;
                }
            }
        }

        // IF THE SPECIES IS COMPLETALY NEW
        if(tmpNotEqualSeqBetweenTwoSpecies == true)
        {
            // PRECIPITATION AND DIFFUSION CONTRIBUTE COMPUTATION
            acs_double tmpDiffusionContribute = createDiffusionRenforcement(diffusion_contribute, tmpComplex.length());
            // CREATE NEW SPECIES OBJECT AND STORE IT INTO THE ENVIRONMENT SPECIES VECTOR
            tmpIdSpeciesToEvaluate = (acs_longInt)allSpecies.size();

            // COMPLEX FORCED CREATIONS
            // ALSO tmp_catalysisID of this function IS TO REMOVE
            allSpecies.push_back(species(tmpIdSpeciesToEvaluate, tmpComplex, tmpDiffusionContribute,
                                         SOLUBLE, K_cpxDiss, tmpCuttingPnt,
                                         tmp___RndDoubleGen, tmpCatalyst_ID, tmpSubstrate_ID, volume, 0, NOTENERGIZABLE));
            incNumberOfCpx();	// Increment number of complex types
            incNumberOfCpxMols();	// Increment number of complex tokens

            if(tmpCpxType == ESOERGONIC)
            {
                allSpecies.at(tmpIdSpeciesToEvaluate).chargeMol();
                incOverallLoadedMolsCounter();
            } // If the complex is formed by a loaded molecules, it is loaded as well

            if(debugLevel >= SMALL_DEBUG)
                cout << "\t\t\t\t|- New Complex " <<  tmpComplex << " has been created" << endl;
        }

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in complexEvaluation method","exceptionerrorthrown");
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "\t\t\tenvironment::ComplexEvaluation end" << endl;

    return newComplexFlag;
}

/**
 Update the species age
 @version 1.0
 */
void environment::updateSpeciesAges()
{
    try{


        if((acs_longInt)allSpecies.size() > 0)
        {
            for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
            {
                // UPDATE SPECIES AGE ----------------
                if((tmpAllSpeciesIter->getAmount() > 0) & (tmpAllSpeciesIter->getComplexCutPnt() == 0))
                {
                    tmpAllSpeciesIter->setNewAge(reactionsTime.at((reactionsTime.size() - 1)) - reactionsTime.at((reactionsTime.size() - 2)));
                }else{
                    tmpAllSpeciesIter->setNewAge(0); // IF THE SPECIES IS DEAD THE AGE OF LAST DEATH REMAINS
                }

            }
        }

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in updateSpeciesAges method","exceptionerrorthrown");
    }
}


/* ************************
 |
 |	PROMPT FUNCTIONS
 |
 *************************/

/**
 Shows all parameters uploaded from the configuration file
 @version 1.0
 */
void environment::showGlobalParameter()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::showGlobalParameter start" << endl;

	QTextStream out(stdout);
	if(debugLevel >= RUNNING_VERSION)
	{ 
		out << endl << endl;
        out << "|---------------------------------------------------------------------------------|" << endl;
        out << "|   ****         ***   *     *          *****   *****                             |" << endl;
        out << "|  *            *   *  **    *         *       *                                  |" << endl;
        out << "| *        ***  *   *  * *   *  ****   *       *                                  |" << endl;
        out << "| *          *  ****   *  *  *  *  *    ****    ****    VERSION 3.2b20130403.51   |" << endl;
        out << "| *       ****  **     *   * *  ****        *       *                             |" << endl;
        out << "|  *      *  *  * *    *    **  *           *       *                             |"  << endl;
        out << "|   ****  ****  *  *   *     *   ***   *****   *****                              |" << endl;
        out << "|---------------------------------------------------------------------------------|" << endl;
		out << endl << endl;

		//TR if(onlyEnvironmentCreation)
		//TR 	out << "\t|-ONLY THE ENVIRONMENT WILL BE CREATED..." << endl; 
		out << "|- GLOBAL PARAMETERS" << endl;
		out << "\t|- Number of Generations: " << nGEN << endl;
		out << "\t|- Number of Simulations: " << nSIM << endl;
		out << "\t|- Number of Seconds: " << (double)nSeconds << endl;
		out << "\t|- Number of Reactions Permitted: " << nReactions << endl;
                out << "\t|- Max number of temptative in simulating the same network with different random seeds" << nAttempts << endl;
                out << "\t|- Max number of hours of the simulation (computational time)" << nHours << endl;
		out << "\t|- Last Firing disk species ID (in structure files upload configuration): " << lastFiringDiskSpeciesID << endl;
		out << "\t|- time Structures Saving Interval: " << (double)timeStructuresSavingInterval << endl;
                out << "\t|- file times Saving Interval: " << (double)fileTimesSaveInterval << endl;
                out << "\t|- Complex Formation Simmetry: " << complexFormationSymmetry << endl;
		out << "\t|- Max lenght of non catalytic species: " << nonCatalyticMaxLength << endl;
		cout << "\t|- Overall initial concentration: " << overallConcentration << endl;
		cout << "\t|- Energy Carriers concentration: " << ECConcentration << endl;
		cout << "\t|- Reaction Probability: " << reactionProbability << endl;
		cout << "\t|- cleavage Probability: " << cleavageProbability << endl;
		cout << "\t|- Reverse Reactions: " << reverseReactions << endl;
                cout << "\t|- Ratio between forward and backward reactions: " << revRctRatio << endl;
		cout << "\t|- ASSOCIATION kinetic constant: " << K_ass << endl;
		cout << "\t|- DISSOCIATION kinetic constant: " << K_diss << endl;
		cout << "\t|- COMPLEX FORMATION kinetic constant: " << K_cpx << endl;
		cout << "\t|- COMPLEX dissociation : " << K_cpxDiss << endl;
		cout << "\t|- ENERGY PHOSFORILATION constant: " << K_nrg << endl;
                cout << "\t|- ENERGY DECAY CONSTANT: " << K_nrg_decay << endl;
		cout << "\t|- SOLUBILITY THRESHOLD: " << solubility_threshold << endl;
        if(influx_rate > 0)
		{
			out << "\t|- The system is OPEN" << endl;
			cout << "\t|- Max out length: " << maxLOut << endl;
			cout << "\t|- MOLECULE DECAY kinetic constant: " << moleculeDecay_KineticConstant << endl;
			cout << "\t|- Refill rate: " << influx_rate << " conc/sec" << endl;
		}else{
			cout << "\t|- The system is CLOSED" << endl;
		}
		cout << "\t|- Alphabet: " << alphabet << endl;
		cout << "\t|- Volume: "<< volume << endl;
		cout << "\t|- Random Seed: " << randomSeed << endl;	
		cout << "\t|- NEPERO: " << NEP << endl;
		cout << "\t|- AVOGADRO: " << AVO << endl;
		cout << "\t|- ENERGY: " << energy << endl;
		cout << "\t|- ratioSpeciesEnergizable: " << ratioSpeciesEnergizable << endl;
		//TR cout << "\t|- Percentage of laoded carriers in the influx: " << percLoadedECInflux << endl;
		//TR switch (energyTarget) {
		//	case SUBSTRATELOAD:
		//		cout << "\t|- energyTarget: SUBSTRATES have to be loaded in endoergonic reactions" << endl;
		//		break;
		//	case CATALYSTLOAD:
		//		cout << "\t|- energyTarget: CATALYSTS have to be loaded in endoergonic reactions" << endl;
		//		break;
		//	default:
		//		cout << "\t|- energyTarget: BOTH SUBSTRATES AND CATALYSTS have to be loaded in endoergonic reactions" << endl;
		//	break;
		//}
	}	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::showGlobalParameter end" << endl;

}

/**
 Show all initial species in table format
 @version 1.0
*/
void environment::printInitialCondition()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printInitialCondition start" << endl;

		cout << "\tNumber of theoretical species after the creation process -> " << this->getNumberOfTheoreticalSpecies() << endl;
		
		cout << "" << endl;
		cout << "ID" << "\t" << "SEQ" << "\t" << "N" << "\t" << "DIFF" << "\t" << "PREC" << "\t" << "DEG" << "\t" << "CUT" <<endl;
		
		for(acs_longInt i = 0; i < getNumberOfTheoreticalSpecies(); i++)
		{
			cout << allSpecies.at(i).getID() << "\t" << allSpecies.at(i).getSequence() << "\t" << 
				allSpecies.at(i).getAmount() << "\t" << allSpecies.at(i).getDiffusionEnh() << "\t" << 
				allSpecies.at(i).getSolubility() << "\t" << allSpecies.at(i).getComplexDegEnh() << "\t" <<
				allSpecies.at(i).getComplexCutPnt() << endl;
		}
		
		cout << "" << endl;	
		cout << " |-----------|" << endl;
		cout << " | REACTIONS |" << endl;
		cout << " |-----------|" << endl;	
		cout << "" << endl;
		if(getNumberOfReactions() > 0)
		{
			for(acs_longInt i = 0; i < getNumberOfReactions(); i++)
			{
				cout << allReactions.at(i).getID() << "\t" << allReactions.at(i).getType() << "\t" << 
						allReactions.at(i).getSpecies_I() << "\t" << allReactions.at(i).getSpecies_II() << "\t" << 
						allReactions.at(i).getSpecies_III() << endl;
			}
		}else{
			ExitWithError("printInitialCondition", "!!! THERE ARE NO REACTIONS IN THIS ENVIRONMENT");
		}
	
	cout << "" << endl;	
	cout << " |-----------|" << endl;
	cout << " | CATALYSIS |" << endl;
	cout << " |-----------|" << endl;	
	cout << "" << endl;
	if(getNumberOfCatalysis() > 0)
	{
		for(acs_longInt i = 0; i < getNumberOfCatalysis(); i++)
		{
			cout << allCatalysis.at(i).getCatId() << "\t" << allCatalysis.at(i).getCat() << "\t" << 
					allCatalysis.at(i).getReactionID() << "\t" << allCatalysis.at(i).getTotAmount() << endl;
		}
	}else{
		ExitWithError("printInitialCondition", "!!! THERE ARE NO CATALYSED REACTIONS!!!");
	}
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printInitialCondition end" << endl;

}

/**
 Show all the species with their ID
 @version 1.0
 */
void environment::printAllSpeciesIdAndSequence()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printAllSpeciesIdAndSequence start" << endl;

	cout << "ID\tS" << endl;
	for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
	{
		cout << allSpecies.at(i).getID() << "\t" << allSpecies.at(i).getSequence() << "\t" << allSpecies.at(i).getConcentration() 
			 << "\t" << allSpecies.at(i).getAmount() 
			 << "\t" << allSpecies.at(i).getNOTchargeMols()
			 << "\t" << allSpecies.at(i).getChargeMols() << endl;
	}
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printAllSpeciesIdAndSequence end" << endl;

}

/**
 Show all the Gillespie Structure
 @version 1.0
 */
void environment::printGillespieStructure()
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printGillespieStructure start" << endl;

	cout << "---- GILLESPIE STRUCTURE ---- (SIZE " << allGillespieScores.size() << ")"<< endl << endl;
	cout << "ID\tSCORE\tRCT\tM1\tM2\tM3\tM4" << endl;
	for(acs_longInt i = 0; i < (acs_longInt)allGillespieScores.size(); i++)
	{
		cout << allGillespieScores.at(i).getID() << "\t" <<
			    allGillespieScores.at(i).getScore() << "\t" <<
				allGillespieScores.at(i).getIdReactionType() << "\t" <<
				allGillespieScores.at(i).getMolI() << "\t" <<
				allGillespieScores.at(i).getMolII() << "\t" <<
				allGillespieScores.at(i).getMolIII() << "\t" <<
				allGillespieScores.at(i).getMolIV() << endl;
	}
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::printGillespieStructure end" << endl;

}

/**
 Print all the energized molecules
 @versione 1.0
 @date 2010-11-14
 */

void environment::printAllChargeMols()
{
	acs_int counter = 0;
	cout << "-------------" << endl;
        cout << "ID" << "\t" << "TOT" << "\t" << "-" << "\t" << "cum" << endl;
    for(vector<acs_double>::iterator tmpAllUnchargedIter = cumUnchargedAmountList.begin(); tmpAllUnchargedIter != cumUnchargedAmountList.end(); tmpAllUnchargedIter++)
	{
		cout << unchargedIDlist.at(counter) << "\t" << allSpecies.at(unchargedIDlist.at(counter)).getAmount() << "\t" 
			 << allSpecies.at(unchargedIDlist.at(counter)).getNOTchargeMols() << "\t" << *tmpAllUnchargedIter << endl;

                if(counter > 0)
                {
                    if((allSpecies.at(unchargedIDlist.at(counter)).getNOTchargeMols()) !=
                        (cumUnchargedAmountList.at(counter) - cumUnchargedAmountList.at(counter-1)))
                             ExitWithError("printAllChargeMols", "	|- !*!*!*! Cumulative sum is not right");
                }

		counter++;
	}
}
/**
 Clear all structures after each simulation
 @version 1.0
 */
void environment::clearAllStructures()
{
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t|- Number of Species: " << allSpecies.size() << endl;
		cout << "\t\t|- Number of Reactions: " << allReactions.size() << endl;
		cout << "\t\t|- Number of Catalysis: " << allCatalysis.size() << endl;
		cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
		cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
		cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;		
	}
       // printAllSpeciesIdAndSequence();
	allSpecies.clear();
	allReactions.clear();
	allCatalysis.clear();
	allTimes.clear();
	reactionsTime.clear();
	gillespieReactionsSelected.clear();
	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t|- Number of Species: " << allSpecies.size() << endl;
		cout << "\t\t|- Number of Reactions: " << allReactions.size() << endl;
		cout << "\t\t|- Number of Catalysis: " << allCatalysis.size() << endl;
		cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
		cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
		cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;		
	}
	allSpecies = initialAllSpecies;
        //printAllSpeciesIdAndSequence();
	allReactions = initiaAllReactions;
	allCatalysis = initialAllCatalysis;
	

	if(debugLevel >= SMALL_DEBUG)
	{
		cout << "\t\t|- Number of Species: " << allSpecies.size() << endl;
		cout << "\t\t|- Number of Reactions: " << allReactions.size() << endl;
		cout << "\t\t|- Number of Catalysis: " << allCatalysis.size() << endl;
		cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
		cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
		cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;		
	}
	
	// Reset total amount of species, complexes and energy carriers for the next simulation

	numberOfSpecies = getTotalNumberOfSpecies(); // Set the initial number of species equal to the firing disk size
	numberOfNewSpecies = 0;
	numberOfMolecules = getTotalNumberOfMolecules();
	numberOfNewMolecules = 0;
	numberOfCpx = getTotalNumberOfComplexSpecies();
	numberOfCpxMols = getTotalNumberOfComplexes();
	timeSinceTheLastInFlux = 0;
	decimalMoleculesToEfflux = 0;
	decimalMoleculesToLoad = 0;
	decimalMoleculesToUNLOAD = 0;
        internalTimesStoredCounter = 0;
	setActualTime(0);
	resetReactionsCounter();
	
}

/**
 set the concentrations to the initial values and reset internal statistics and counter
 @version 1.0
 */
//void environment::resetConcentrationToInitialConditions(QString tmpSpeciesFilePath, acs_int tmpActGEN, acs_int tmpActSIM)
void environment::resetConcentrationToInitialConditions()
{
    if(debugLevel >= RUNNING_VERSION)
    {
            cout << endl << "\t\t|- OLD STRUCTURES" << endl;
            cout << "\t\t|- Number of Species: " << allSpecies.size() << endl;
            cout << "\t\t|- Number of Reactions: " << allReactions.size() << endl;
            cout << "\t\t|- Number of Catalysis: " << allCatalysis.size() << endl;
            cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
            cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
            cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;
    }

    // RESET REACTIONS COUNTER
    for(vector<reactions>::iterator tmpAllReactionsIter = allReactions.begin(); tmpAllReactionsIter != allReactions.end(); tmpAllReactionsIter++)
    {
        tmpAllReactionsIter->resetEventsCounter();
    }
    // RESET CATALYSIS COUNTER
    for(vector<catalysis>::iterator tmpAllCatalysisIter = allCatalysis.begin(); tmpAllCatalysisIter != allCatalysis.end(); tmpAllCatalysisIter++)
    {
        tmpAllCatalysisIter->resetEventsCounter();
    }
    // RESET SPECIES PROPRIETIES
    for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
    {
        tmpAllSpeciesIter->resetAge();
        tmpAllSpeciesIter->resetReborns();
        tmpAllSpeciesIter->resetToInitConc(volume);
    }

    //allSpecies.clear();
    //allReactions.clear();
    //allCatalysis.clear();
	allTimes.clear();
	reactionsTime.clear();
	gillespieReactionsSelected.clear();

	if(debugLevel >= RUNNING_VERSION)
        {
            cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
            cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
            cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;
	}

	//LOADING SPECIES FROM FILE
//	if(!createInitialMoleculesPopulationFromSpecificFile(tmpSpeciesFilePath, tmpActGEN, tmpActSIM))
//		ExitWithError("createInitialMoleculesPopulationFromSpecificFile", "Problem with the species loading process");
//	//LOADING REACTIONS AND CATALYSIS FROM FILE
//	if(!createInitialReactionsLayerFromSpecificFile(tmpSpeciesFilePath, tmpActGEN, tmpActSIM))
//		ExitWithError("createInitialReactionsLayerFromSpecificFile", "Problem with the reactions loading process");
//	if(!createInitialCatalysisLayerFromSpecificFile(tmpSpeciesFilePath, tmpActGEN, tmpActSIM))
//		ExitWithError("createInitialCatalysisLayerFromSpecificFile", "Problem with the catalysis loading process");
	//CHECK STRUCTURES
	if(!structureCoherenceCheckUp())
	{
		cout << endl;
		ExitWithError("structureCoherenceCheckUp", "PROBLEM WITH STRUCTURE COHERENCE... BE CARE TO THE SIMULATION OUTCOMES!!!");
	}
	//STORE INITIAL STRUCTURES DATA IN ORDER TO REINITIALIZE THE STRUCTURE AFTER EACH SIMULATION
	storeInitialStructures();
	
	if(debugLevel >= RUNNING_VERSION)
	{
		cout << endl << "\t\t|- NEW STRUCTURES" << endl;
		cout << "\t\t|- Number of Species: " << allSpecies.size() << endl;
		cout << "\t\t|- Number of Reactions: " << allReactions.size() << endl;
		cout << "\t\t|- Number of Catalysis: " << allCatalysis.size() << endl;
		cout << "\t\t|- Number of Times: " << allTimes.size() << endl;
		cout << "\t\t|- Number of Reactions Time: " << reactionsTime.size() << endl;
		cout << "\t\t|- Number of Reactions Selected: " << gillespieReactionsSelected.size() << endl;		
	}

        // Reset total amount of species, complexes and energy carriers for the next simulation

	numberOfSpecies = getTotalNumberOfSpecies(); // Set the initial number of species equal to the firing disk size
	numberOfNewSpecies = 0;
	numberOfMolecules = getTotalNumberOfMolecules();
	numberOfNewMolecules = 0;
	numberOfCpx = getTotalNumberOfComplexSpecies();
	numberOfCpxMols = getTotalNumberOfComplexes();
	timeSinceTheLastInFlux = 0;
	decimalMoleculesToEfflux = 0;
	decimalMoleculesToLoad = 0;
	decimalMoleculesToUNLOAD = 0;
	setActualTime(0);
	resetReactionsCounter();
	
}

/**
 Store initial structures into storing variables
 @version 1.0
 */
void environment::storeInitialStructures()
{
	initialAllSpecies.clear();
	initiaAllReactions.clear();
	initialAllCatalysis.clear();
	initialAllSpecies = allSpecies;
	initiaAllReactions = allReactions;
	initialAllCatalysis = allCatalysis;
}

/* ************************
 |
 |	SAVE TO FILE FUNCTIONS
 |
 *************************/

/**
 This function creates a chain of zero as QString according to tmpTotN and tmpCurrent N in order to make possible a sorting
 (e.g. tmpTotN = 1000, tmpCurrentN = 3, return 0003
 @version 1.0
 @param acs_int tmpTotN Total N
 @param acs_int tmpCurrentN current N
 */
QString environment::zeroBeforeStringNumber(acs_int tmpTotN, acs_int tmpCurrentN)
{
	QString strZeroReturned = "";
	QString tempQStrTmpTotN;
	QString tempQStrtmpCurrentN;	
	QString QStrTmpTotN = tempQStrTmpTotN.setNum(tmpTotN);
	QString QStrtmpCurrentN = tempQStrtmpCurrentN.setNum(tmpCurrentN);
	
	for(int i = 0; i < QStrTmpTotN.length() - QStrtmpCurrentN.length(); i++)
	{
		strZeroReturned += "0";
	}
	
	return strZeroReturned;
}

/**
 Save a file with the configuration parameters
 @version 1.0
 */
bool environment::saveConfigurationFile(QString tmpStoringPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveConfigurationFile start" << endl;

	cout << "Saving configuration file... ";
	QString strConfigurationFile = tmpStoringPath + "/acsm2s.conf";
	QFile fid(strConfigurationFile);
	if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);

	out << "# =================" << endl;
	out << "# ACSM2S PARAMETERS" << endl;
	out << "# =================" << endl << endl;

	out << "# -----------------" << endl;
	out << "# SYSTEM PARAMETERS" << endl;
	out << "# -----------------" << endl << endl;
	
	//TR out << "# Limit the work of the software to the environment creation" << endl;
	//TR out << "onlyEnvironmentCreation=" << onlyEnvironmentCreation << endl << endl;
	
	out << "# Number of Generations" << endl;
	out << "nGEN=" << nGEN << endl << endl;
	
	out << "# Number of Simulations per generation (after noMultipleSimsGens generations)" << endl;
	out << "nSIM=" << nSIM << endl << endl;
	
	out << "# Number of seconds" << endl;
	out << "nSeconds=" << (double)nSeconds << endl << endl;
	
	out << "# Number of max reactions permitted (step)" << endl;
	out << "nReactions=" << nReactions << endl << endl;

        out << "# Max number of hours (computational time) of the simulation (if 0 no limits are set)" << endl;
        out << "nHours=" << nHours << endl << endl;

        out << "# Number of attempts in same network / different random seed (if 0 no limits are set) " << endl;
        out << "nAttempts=" << nAttempts << endl << endl;
	
	out << "# random seed (random if 0)" << endl;
	out << "randomSeed=" << (int)randomSeed << endl << endl;
	
	out << "# Debug Level: Runtime number of prompted messages level" << endl; 
	out << "debugLevel=" << debugLevel << endl << endl;
	
	out << "# Save structures to file every..." << endl; 
	out << "timeStructuresSavingInterval=" << (double)timeStructuresSavingInterval << endl << endl;

        out << "# Save file times avery..." << endl;
        out << "fileTimesSaveInterval=" << (double)fileTimesSaveInterval << endl << endl;
	
	out << "# ------------------------" << endl;
	out << "# ENVIRONMENTAL PARAMETERS" << endl;
	out << "# ------------------------" << endl << endl;
	
	out << "# Total number of species in the initial population" << endl;
	out << "# 	If The number is greater than the theoretical number" << endl; 
	out << "#	according to initial max length and the alphabet all species" << endl;
	out << "#	will be created, otherwise if it is equal to 0 the system will be" << endl;
	out << "#	upload from file." << endl << endl;
	//TR out << "initialPopulationNumber=" << initialPopulationNumber << endl;
	
	out << "# Identificator of the last firing disk species" << endl;
	out << "lastFiringDiskSpeciesID=" << lastFiringDiskSpeciesID << endl << endl;
	
	out << "# Initial distribution" << endl;
	out << "# 1- Proportional: Same number of molecules for each species" << endl;
	out << "# 2- Uniform: Same number of molecules for each length" << endl;
	out << "# 3- inversely proportional: more morecules for the short species" << endl << endl;
	//TR out << "initialAmountDistribution=" << initialAmountDistribution << endl << endl;
	
	//TR out << "# Initial maximum length" << endl;
	//TR out << "initialMaxLength=" << initialMaxLength << endl << endl;
	
	out << "# Overall initial concentration" << endl;
	out << "overallConcentration=" << (double)overallConcentration << endl << endl;
	
	out << "# Overall energy carriers concentration" << endl;
	out << "ECConcentration=" << (double)ECConcentration << endl << endl;
	
	out << "# Alphabet (e.g. AGCT for DNA)" << endl;
	out << "alphabet=" << alphabet.c_str() << endl << endl;
	
	out << "# Volume (dm^3)" << endl;
	out << "volume=" << (double)volume << endl << endl;
	
	out << "# ------------------" << endl;
	out << "# DYNAMIC PARAMETERS" << endl;
	out << "# ------------------" << endl << endl;	
	
	out << "# Energy introduction" << endl; 
	out << "#	0: Not energy in the system" << endl;
	out << "#	1: Energy is present" << endl;
	out << "energy=" << (double)energy << endl << endl;

	out << "# Ratio of energizable species" << endl;
	out << "ratioSpeciesEnergizable=" << (double)ratioSpeciesEnergizable << endl << endl;

	//TR out << "# Energy target (0=substrate, 1=catalsyt, 2=both)" << endl << endl;
	//TR out << "energyTarget=" <<  energyTarget << endl << endl;

	//TR out << "# Percentage of loaded energy carriers in the incoming flux" << endl;
	//TR out << "percLoadedECInflux=" <<  (double)percLoadedECInflux << endl << endl;
	
	out << "# Complex Formation Symmetry (GILLESPIE computation: if equal to 1, one complex" << endl;
	out << "#	formation reaction for each substrate will be created, otherwise only" << endl;
	out << "#	complex formation reaction with the first substrate will be considered" << endl;
	out << "complexFormationSymmetry=" << complexFormationSymmetry << endl << endl;

	out << "# IF 1 also monomers can catalyze reactions, otherwise reactions are catalyzed" << endl;
	out << "# starting from dimers" << endl;
	out << "nonCatalyticMaxLength=" << nonCatalyticMaxLength << endl << endl;
	
	out << "# Catalysis probability" << endl;
	out << "reactionProbability=" << (double)reactionProbability << endl << endl;
	
	out << "# Cleavage probability (Condensation Probability is 1 - cleavage probability)" << endl;
	out << "cleavageProbability=" << (double)cleavageProbability << endl << endl;
	
	out << "# Enable reverse reactions" << endl;
	out << "reverseReactions=" << reverseReactions << endl << endl;

        out << "# Ratio between forward and backward reactions (if reverseReactions = TRUE)" << endl;
        out << "revRctRatio=" << (double)revRctRatio << endl << endl;
	
	out << "# kinetic constants" << endl;
	out << "K_ass=" << (double)K_ass << endl;
	out << "K_diss=" << (double)K_diss << endl;
	out << "K_cpx=" << (double)K_cpx << endl;
	out << "K_cpxDiss=" << (double)K_cpxDiss << endl;
	out << "K_nrg=" << (double)K_nrg << endl;
	out << "K_nrg_decay=" << (double)K_nrg_decay << endl;
	out << "moleculeDecay_KineticConstant=" << (double)moleculeDecay_KineticConstant << endl << endl;
	
	out << "# (0 or 0.5) if set to 0.5 the speed of molecules goes with the inverse of the square of the length" << endl;
	out << "diffusion_contribute=" << (double)diffusion_contribute << endl << endl;
	
	out << "# Solubility Threshold (The threshold set the centre of the logistic curve, 0 to exclude precipitation)" << endl;
	out << "solubility_threshold=" << solubility_threshold << endl << endl;
	
        //TR out << "# 0 (Close System) - Max length of the influx" << endl;
        //TR out << "influx=" << influx << endl << endl;
	
	out << "# Overall influx (moles per second) and maximum length of the species passing the filter in the outflow process" << endl;
	out << "influx_rate=" << (double)influx_rate << endl;
	out << "maxLOut=" << maxLOut << endl << endl;

	
	fid.close();
	cout << "done." << endl;
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveConfigurationFile end" << endl;
	
	return true;
}

/**
 Save influx structures in a file named
 @param bool saveInfluxStructure(QString tmpStoringPath);
 @version 1.0
 @date 2010-04-04
*/
bool environment::saveInfluxStructure(QString tmpStoringPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveInfluxStructure start" << endl;
	cout << "Saving Influx file...";
	
	QString strConfigurationFile = tmpStoringPath + "/_acsinflux.csv";
	QFile fid(strConfigurationFile);
	if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);	
	acs_int influxSpeciesID = 0;
        for(vector<acs_int>::iterator tmpAllInfluxIter = nutrientsForInflux.begin(); tmpAllInfluxIter != nutrientsForInflux.end(); tmpAllInfluxIter++)
	{
		out << *tmpAllInfluxIter << "\t" << (double)nutrientsProb2BeSelected.at(influxSpeciesID) << endl;
		influxSpeciesID++;
	}
	fid.close();
	cout << "done." << endl;

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveInfluxStructure end" << endl;	
	return true;

}

/**
 Save Energetic Boolean Function on a file named _acsnrgbooleanfunctions.csv
 @version 1.0
 @date 2011-04-15
 @param QString tmpStoringPath Path of the saving folder
*/
bool environment::saveNrgBoolFncStructure(QString tmpStoringPath)
{
        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveNrgBoolFncStructure start" << endl;
        cout << "Saving Influx file...";

        QString strConfigurationFile = tmpStoringPath + "/_acsnrgbooleanfunctions.csv";
        QFile fid(strConfigurationFile);
        if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
                exit(EXIT_FAILURE);

        QTextStream out(&fid);
        acs_int influxNrgBoolID = 0;
        for(vector<acs_int>::iterator tmpAllNrgBoolIter = nrgBooleanFunctions.begin(); tmpAllNrgBoolIter != nrgBooleanFunctions.end(); tmpAllNrgBoolIter++)
        {
                out << *tmpAllNrgBoolIter << "\t" << (double)nrgBoolFncsProb2BeSelected.at(influxNrgBoolID) << endl;
                influxNrgBoolID++;
        }
        fid.close();
        cout << "done." << endl;

        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveNrgBoolFncStructure end" << endl;
        return true;

}


/**
 Save the species structures in a file named species_[currentSims]_[currentStep].csv. This is file is equal to the acs_species.csv input file. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveSpeciesStructure(acs_int tmpCurrentGen, acs_int tmpCurrentSim, acs_int tmpCurrentStep, QString tmpStoringPath) 
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveSpeciesStructure start" << endl;

	if(debugLevel >= SMALL_DEBUG)
            cout << "Saving species structure...";
	QString strCurrenGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpCurrentGen);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpCurrentGen)), tmpCurrentSim);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, tmpCurrentStep);
	QString strFileSpeciesStructure = tmpStoringPath + "/species_" + strZeroGenBefore + strCurrenGen.setNum(tmpCurrentGen) + "_" +
									strZeroSimBefore + strCurrentSim.setNum(tmpCurrentSim) + "_" + 
									strZeroStepBefore + strCurrentStep.setNum(tmpCurrentStep) + ".csv";
	QFile fid(strFileSpeciesStructure);
	if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);
        for(vector<species>::iterator tmpAllSpeciesIter = allSpecies.begin(); tmpAllSpeciesIter != allSpecies.end(); tmpAllSpeciesIter++)
	{
		out << (acs_longInt)tmpAllSpeciesIter->getID() << "\t"
		<< tmpAllSpeciesIter->getSequence().c_str() << "\t"
		//<< (acs_longInt)tmpAllSpeciesIter->getAmount() << "\t"
		<< (double)tmpAllSpeciesIter->getConcentration() << "\t"
		<< (double)tmpAllSpeciesIter->getDiffusionEnh() << "\t"
		<< (acs_int)tmpAllSpeciesIter->getSolubility() << "\t"
		<< (double)tmpAllSpeciesIter->getComplexDegEnh() << "\t"
		<< tmpAllSpeciesIter->getComplexCutPnt() << "\t"
		<< tmpAllSpeciesIter->getEvaluated() << "\t"
		<< (double)tmpAllSpeciesIter->getAge() << "\t"
		<< tmpAllSpeciesIter->getReborns() << "\t" 
		<< tmpAllSpeciesIter->getCatalyst_ID()  << "\t"
		<< tmpAllSpeciesIter->getSubstrate_ID() <<	"\t"
		<< (double)tmpAllSpeciesIter->getK_phospho() << "\t"
        << (double)tmpAllSpeciesIter->getLoadedConcentration(volume) << "\t"
        << tmpAllSpeciesIter->getConcentrationFixed() << endl;
	}
	fid.close();
	
	if(debugLevel >= SMALL_DEBUG)
		cout << "done." << endl;
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveSpeciesStructure end" << endl;
	
	return true;
}

/**
 Save the reactions structures in a file named reactions_[currentSims]_[currentStep].csv. This is file is equal to the acs_reactions.csv input file. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveReactionsStructure(acs_int tmpCurrentGen, acs_int tmpCurrentSim, acs_int tmpCurrentStep, QString tmpStoringPath) 
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsStructure start" << endl;

	if(debugLevel >= SMALL_DEBUG)
		cout << "Saving reactions structure...";
	QString strCurrenGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpCurrentGen);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpCurrentGen)), tmpCurrentSim);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, tmpCurrentStep);
	QString strFileReactionsStructure = tmpStoringPath + "/reactions_" + strZeroGenBefore + strCurrenGen.setNum(tmpCurrentGen) + "_" +
										strZeroSimBefore + strCurrentSim.setNum(tmpCurrentSim) + "_" + 
										strZeroStepBefore + strCurrentStep.setNum(tmpCurrentStep) + ".csv";
	QFile fid(strFileReactionsStructure);
	if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);
        for(vector<reactions>::iterator tmpAllReactionsIter = allReactions.begin(); tmpAllReactionsIter != allReactions.end(); tmpAllReactionsIter++)
	{
		out << tmpAllReactionsIter->getID() << "\t"
		<< tmpAllReactionsIter->getType() << "\t"
		<< tmpAllReactionsIter->getSpecies_I() << "\t"
		<< tmpAllReactionsIter->getSpecies_II() << "\t"
		<< tmpAllReactionsIter->getSpecies_III() << "\t"
        << tmpAllReactionsIter->getEvents() << "\t"
		<< tmpAllReactionsIter->getEnergyType() << endl;
	}
	fid.close();
	if(debugLevel >= SMALL_DEBUG)
		cout << "done." << endl;

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsStructure end" << endl;

	return true;
}

/**
 Save the catalysis structures in a file named catalysis_[currentSims]_[currentStep].csv. This is file is equal to the acs_catalysis.csv input file. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveCatalysisStructure(acs_int tmpCurrentGen, acs_int tmpCurrentSim, acs_int tmpCurrentStep, QString tmpStoringPath)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveCatalysisStructure start" << endl;

	if(debugLevel >= SMALL_DEBUG)
		cout << "Saving catalysis structure...";
	QString strCurrenGen;
	QString strCurrentSim;
	QString strCurrentStep;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpCurrentGen);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpCurrentGen)), tmpCurrentSim);
	QString strZeroStepBefore = zeroBeforeStringNumber(nReactions, tmpCurrentStep);
	QString strFileCatalysisStructure = tmpStoringPath + "/catalysis_" + strZeroGenBefore + strCurrenGen.setNum(tmpCurrentGen) + "_" +
										strZeroSimBefore + strCurrentSim.setNum(tmpCurrentSim) + "_" + 
										strZeroStepBefore + strCurrentStep.setNum(tmpCurrentStep) + ".csv";
	QFile fid(strFileCatalysisStructure);
	if(!fid.open(QIODevice::WriteOnly | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);
        for(vector<catalysis>::iterator tmpAllCatalysisIter = allCatalysis.begin(); tmpAllCatalysisIter != allCatalysis.end(); tmpAllCatalysisIter++)
	{
		out << tmpAllCatalysisIter->getCatId() << "\t"
		<< tmpAllCatalysisIter->getCat() << "\t"
		<< tmpAllCatalysisIter->getReactionID() << "\t"
		<< tmpAllCatalysisIter->getTotAmount() << "\t"
		<< (double)tmpAllCatalysisIter->getKass() << "\t"
		<< (double)tmpAllCatalysisIter->getKdiss() << "\t"
		<< (double)tmpAllCatalysisIter->getK_cpx() << endl;
		//TR << (double)tmpAllCatalysisIter->getK_cpxDiss() << endl;
	}
	fid.close();
	if(debugLevel >= SMALL_DEBUG)
		cout << "done." << endl;

	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveCatalysisStructure end" << endl;

	return true;
}

/**
 Save the reactions times in a file named times_[currentSim].csv. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveTimes(acs_int tmpCurrentGen, acs_int tmpCurrentSim, acs_int tmpCurrentStep, QString tmpStoringPath)
{
        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveTimes start" << endl;
        if(debugLevel >= SMALL_DEBUG)
            cout << "\t|- Saving Times to file...";

    try{

        QString strCurrentGen;
        QString strCurrentSim;
        QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmpCurrentGen);
        QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmpCurrentGen)), tmpCurrentSim);
        QString strFileCatalysisStructure = tmpStoringPath + "/times_" + strZeroGenBefore + strCurrentGen.setNum(tmpCurrentGen) + "_" +
                strZeroSimBefore + strCurrentSim.setNum(tmpCurrentSim) + ".csv";
        QFile fid(strFileCatalysisStructure);
        if(!fid.open(QIODevice::Append | QIODevice::Text))
            exit(EXIT_FAILURE);

        QTextStream out(&fid);
        if(COPYOFallGillespieScores.size() > 0)
        {
            out << tmpCurrentStep << "\t"
                << (double)reactionsTime.at(tmpCurrentStep-1) << "\t"
                << gillespieReactionsSelected.at(tmpCurrentStep-1) << "\t"
                << COPYOFallGillespieScores.at(gillespieReactionsSelected.at(tmpCurrentStep-1)).getIdReactionType() << "\t"
                << COPYOFallGillespieScores.size() << "\t"
                << allTimes.at(tmpCurrentStep-1) << "\t"
                << getTotalNumberOfSpecies() << "\t"
                << getTotalNumberOfMolecules() << "\t"
                << getTotalNumberOfComplexSpecies() << "\t"
                << getTotalNumberOfComplexes() << "\t"
                << getTotalNumberOfMonomers() << "\t"
                << gillespiePartialTimes.at(tmpCurrentStep-1) << "\t"
                << performReactionPartialTimes.at(tmpCurrentStep-1) << "\t"
                << remainingProcessesPartialTimes.at(tmpCurrentStep-1) << "\t"
                << (double)getRatioBetweenNewGillTotGill() << endl;
        }else{
            out << tmpCurrentStep << "\t"
                << (double)reactionsTime.at(tmpCurrentStep-1) << "\t"
                << gillespieReactionsSelected.at(tmpCurrentStep-1) << "\t"
                << 0 << "\t"
                << 0 << "\t"
                << 0 << "\t"
                << getTotalNumberOfSpecies() << "\t"
                << getTotalNumberOfMolecules() << "\t"
                << getTotalNumberOfComplexSpecies() << "\t"
                << getTotalNumberOfComplexes() << "\t"
                << getTotalNumberOfMonomers() << "\t"
                << 0 << "\t"
                << 0 << "\t"
                << 0 << "\t"
                << 0 << endl;
        }
        fid.close();
        if(debugLevel >= SMALL_DEBUG)
            cout << "OK" << endl;

        COPYOFallGillespieScores.clear();

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in method saveTimes","exceptionerrorthrown");
    }

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveTimes end" << endl;

    return true;
}

/**
 Save the reactions parameters in a file named reactions_parameters_[currentSim].csv. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveReactionsParameters(acs_int tmp__CurrentGen, acs_int tmp__CurrentSim, acs_int tmp__CurrentStep, QString tmp__StoringPath, 
                                          acs_int tmpRctType, acs_longInt tmpCat, acs_longInt tmpMol_I, acs_longInt tmpMol_II, acs_longInt tmpMol_III)
{
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParameters start" << endl;
	if(debugLevel >= HIGH_DEBUG)
            cout << "\t|- Saving reaction parameters to file...";
	
	QString strCurrentGen;
	QString strCurrentSim;
	QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmp__CurrentGen);
	QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmp__CurrentGen)), tmp__CurrentSim);
	QString strFileReactionsParameters = tmp__StoringPath + "/reactions_parameters_" + strZeroGenBefore + strCurrentGen.setNum(tmp__CurrentGen) + "_" +
											strZeroSimBefore + strCurrentSim.setNum(tmp__CurrentSim) + ".csv";
	QFile fid(strFileReactionsParameters);
	if(!fid.open(QIODevice::Append | QIODevice::Text))
		exit(EXIT_FAILURE);
	
	QTextStream out(&fid);
	out << tmp__CurrentStep << "\t"
	<< (double)reactionsTime.at(tmp__CurrentStep-1) << "\t" 
	<< tmpRctType << "\t"
	<< tmpCat << "\t"
	<< tmpMol_I << "\t"
	<< tmpMol_II << "\t"
	<< tmpMol_III << "\t"
	<< overallLoadedMolsCounter << "\t"
    << (double)(overallLoadedMolsCounter / (AVO * volume)) << "\t"
	<< (double)gillespieMean << "\t"
	<< (double)gillespieSD << "\t"
    << (double)gillespieEntropy << "\t"
    << (double)ratioBetweenNewGillTotGill << "\t"
    << (double)ratioBetweenReverseAndTotalScore << endl;
	fid.close();
	if(debugLevel >= HIGH_DEBUG)
		cout << "OK" << endl;
	
	COPYOFallGillespieScores.clear();
	
	if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParameters end" << endl;
	
	return true;
}

/**
 Save living species in a file named living_species_[currentSim].csv. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveLivingSpeciesID(acs_int tmp__CurrentGen, acs_int tmp__CurrentSim, acs_int tmp__CurrentStep, QString tmp__StoringPath)
{
    try{


        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters start" << endl;
        if(debugLevel >= SMALL_DEBUG)
            cout << "\t|- Saving reaction parameters to file...";

        QString strCurrentGen;
        QString strCurrentSim;
        QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmp__CurrentGen);
        QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmp__CurrentGen)), tmp__CurrentSim);
        QString strFilelivingSpecies = tmp__StoringPath + "/livingSpecies_" + strZeroGenBefore + strCurrentGen.setNum(tmp__CurrentGen) + "_" +
                strZeroSimBefore + strCurrentSim.setNum(tmp__CurrentSim) + ".csv";

        QFile fid(strFilelivingSpecies);
        if(!fid.open(QIODevice::Append | QIODevice::Text))
            exit(EXIT_FAILURE);

        QTextStream out(&fid);
        out << tmp__CurrentStep << "\t"
            << (double)reactionsTime.at(tmp__CurrentStep-1);
        for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
        {
            if((allSpecies.at(i).getAmount() > 0) & (allSpecies.at(i).getComplexCutPnt() == 0))
                out << "\t" << allSpecies.at(i).getID();
        }
        out << endl;
        fid.close();
        if(debugLevel >= SMALL_DEBUG)
            cout << "OK" << endl;

        COPYOFallGillespieScores.clear();

        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters end" << endl;

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in saveLivingSpeciesID method","exceptionerrorthrown");
    }

    return true;
}

/**
 Save living species total AMOUNT in a file named livingAmount_[CurrentGen]_[currentSim].csv. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveLivingSpeciesAmount(acs_int tmp__CurrentGen, acs_int tmp__CurrentSim, QString tmp__StoringPath)
{
    try{


        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters start" << endl;
        if(debugLevel >= SMALL_DEBUG)
            cout << "\t|- Saving reaction parameters to file...";

        QString strCurrentGen;
        QString strCurrentSim;
        QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmp__CurrentGen);
        QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmp__CurrentGen)), tmp__CurrentSim);
        QString strFilelivingSpecies = tmp__StoringPath + "/livingAmount_" + strZeroGenBefore + strCurrentGen.setNum(tmp__CurrentGen) + "_" +
                strZeroSimBefore + strCurrentSim.setNum(tmp__CurrentSim) + ".csv";

        QFile fid(strFilelivingSpecies);
        if(!fid.open(QIODevice::Append | QIODevice::Text))
            exit(EXIT_FAILURE);

        QTextStream out(&fid);
        acs_int firstSpeciesControl = 0;
        for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
        {
            if((allSpecies.at(i).getAmount() > 0) & (allSpecies.at(i).getComplexCutPnt() == 0))
            {
                if(firstSpeciesControl != 0)
                {
                    out << "\t" << allSpecies.at(i).getAmount();
                }else{
                    out << allSpecies.at(i).getAmount();
                    firstSpeciesControl++;
                }
            }
        }
        out << endl;
        fid.close();
        if(debugLevel >= SMALL_DEBUG)
            cout << "OK" << endl;

        COPYOFallGillespieScores.clear();

        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters end" << endl;

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in saveLivingSpeciesAmount method","exceptionerrorthrown");
    }

	return true;
}

/**
 Save living species total CONCENTRATION in a file named livingAmount_[CurrentGen]_[currentSim].csv. 
 The file is saved in the directory indicated as a second parameter in the run command
 @version 1.0
 */
bool environment::saveLivingSpeciesConcentration(acs_int tmp__CurrentGen, acs_int tmp__CurrentSim, QString tmp__StoringPath)
{
    try{


        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters start" << endl;
        if(debugLevel >= SMALL_DEBUG)
            cout << "\t|- Saving reaction parameters to file...";

        QString strCurrentGen;
        QString strCurrentSim;
        QString strZeroGenBefore = zeroBeforeStringNumber(nGEN, tmp__CurrentGen);
        QString strZeroSimBefore = zeroBeforeStringNumber(pow(double(nSIM), double(tmp__CurrentGen)), tmp__CurrentSim);
        QString strFilelivingSpecies = tmp__StoringPath + "/livingConcentration_" + strZeroGenBefore + strCurrentGen.setNum(tmp__CurrentGen) + "_" +
                strZeroSimBefore + strCurrentSim.setNum(tmp__CurrentSim) + ".csv";

        QFile fid(strFilelivingSpecies);
        if(!fid.open(QIODevice::Append | QIODevice::Text))
            exit(EXIT_FAILURE);

        QTextStream out(&fid);
        acs_int firstSpeciesControl = 0;
        for(acs_longInt i = 0; i < (acs_longInt)allSpecies.size(); i++)
        {
            if((allSpecies.at(i).getAmount() > 0) & (allSpecies.at(i).getComplexCutPnt() == 0))
            {
                if(firstSpeciesControl != 0)
                {
                    out << "\t" << (double)allSpecies.at(i).getConcentration();
                }else{
                    out << (double)allSpecies.at(i).getConcentration();
                    firstSpeciesControl++;
                }
            }
        }
        out << endl;
        fid.close();
        if(debugLevel >= SMALL_DEBUG)
            cout << "OK" << endl;

        COPYOFallGillespieScores.clear();

        if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::saveReactionsParamters end" << endl;

    }
    catch(exception&e)
    {
        cerr << "exceptioncaught:" << e.what() << endl;
        ExitWithError("error in saveLivingSpeciesConcentration method","exceptionerrorthrown");
    }

	return true;
}

///////////////////////////////////
// STATISTIC FUNTIONS
///////////////////////////////////

bool environment::devStd()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::devStd start" << endl;
    bool devStdFlag = true;
    acs_double tempDevStd = 0;

    for(vector<gillespie>::iterator tmpScoreValue = allGillespieScores.begin(); tmpScoreValue != allGillespieScores.end(); tmpScoreValue++)
    {
        tempDevStd += pow((double)tmpScoreValue->getScore() - gillespieMean,2);
    }

    gillespieSD = sqrt((double)tempDevStd / (double)allGillespieScores.size());

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::devStd end" << endl;

    return devStdFlag;
}

bool environment::entropy()
{
    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::entropy start" << endl;
    bool entropyFlag = true;
    acs_double tempEntropy = 0;
    acs_double normValue;

    for(vector<gillespie>::iterator tmpScoreValue = allGillespieScores.begin(); tmpScoreValue != allGillespieScores.end(); tmpScoreValue++)
    {
        normValue = tmpScoreValue->getScore() / gillespieCumulativeStepScoreList.back();
        tempEntropy += -normValue * log(normValue);
    }

    gillespieEntropy = tempEntropy;

    if(debugLevel == FINDERRORDURINGRUNTIME) cout << "environment::entropy end" << endl;

    return entropyFlag;
}

