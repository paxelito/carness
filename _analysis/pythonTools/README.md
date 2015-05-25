CARNESS APP :: Analysis Python Package
======================================

CARNESS APP is a python scripts package containing useful scripts to study and analyse the simulations carried out by means of the `CARNESS <https://github.com/paxelito/carness>`_ simulator. 

System requirements
-------------------

Python Libraries: python-numpy python-scipy python-matplotlib python-setuptools python-networkx python-deap graphviz libgraphviz-dev pkg-config python-pygraphviz

All Scripts
-----------

* initializator.py 				-> system initializator
* graph_chemistry_analysis		-> artificial chemistry graph analysis
* acsDuplicationAnalysis		-> protcell duplication analysis
* acsAttractorAnalysis.py 		-> Comparison between final states 
* acsAttractorAnalysisInTime.py -> Comparison between distinct states in time
* acsSCCanalysis.py 			-> Strongly connected components analysis
* acsSpeciesActivity.py 		-> Count how many times a species is a substrate, a catalyst or a product
* acsStateAnalysis.py 			-> Comparison between different times in the same run. Agglomerative statistics are computed as well
* acsDynStatInTime 				-> Trajectory in concentrations of each species are detected
* prepareNewSim.py 				-> prepare the initial conditions of a new simulation starting from the final conditions of an other sim. 

Currently Documented
--------------------

* initializator.py 				-> system initializator
* graph_chemistry_analysis		-> artificial chemistry graph analysis
* acsDuplicationAnalysis		-> protcell duplication analysis

Release Notes
-------------

Version 002 - 20150526
**********************

* Parameters are now stored in a dictionary for a more simple management
* Initializator.py
	* the system architecture is now set in the acsm2m.conf file, hence the parameter sysType has been removed
	* The influx file related to the systemArchitecture 3 (PROTOCELLFLUXFINITE) is now created. 
* acsDuplicationAnalysis.py
	* The amount of the species in now extracted also within two successive generation and not only at the end of each generation. 
* Documentation updated

Version 001 - 20150424
**********************

* Documentation update 
* initializator.py
	* the permission of the lunghers is not automatically set to 0755 
	* the __resetsimulations.sh file has been created (CAUTION in using it!!! All the simulation results folders will be erased) 


controllare creazione di reazioni spontanee, 