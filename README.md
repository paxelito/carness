Introdurre nel costruttore di ENV il tipo di sistema e utilizzare per creare flusso!!!

La concentrazione fissa non viene assolutamente presa dal file, viene sempre calcolata sulle base degli altri parametri

FARE IN MODO CHE LA CONCENTRAZIONE FISSA VENGA DEFINITA DAL FILE SPECIES... AL momento passiamo il parametro conclock ma la fuznioen lo usa come legato all'energia
e calcola da sola se la specie ha concentrazione o meno 


RELEASE NOTES
=============

Build8.0b20150427.76
--------------------
	
	* A new class influxspecies has been introduced to deal with membrane finite diffusion of external food
	* New surface is computed too
	* Runtime interface has been enxhanced, information have been riorganized and surface has been added

Build7.1b20140721.75
--------------------
	
	* Volume now growths as a function of the lipids. Relation between volume and lipids is computed during the initialization and it is equal to 
 	V = omega*C^{3/2}.  

Build7.0b20140623.74
--------------------
	
	* Volume growth has been introduced with adiabatic assumption
	* Protocell division has been added 

Build6.1b20140529.73
--------------------
	
	* A bug in the gillespie introduction has been fixed

Build6.1b20140529.72
--------------------
	
	* A bug in the reaction parameter saving procedure has been fixed
	* New the user can choose if save reaction parameters
	* Simulation prompt results every XXX seconds
	* At each generation now concentration can be randomly reassigned or first concentration are assigned
	* Minor bugs fixed

Build6.0b20140523.71
--------------------
	
	* File buffering writing procedures have been completed
	* Minor bugs fixed

Build5.0b20140512.70
--------------------
	
	* Added buffering for writing to files
	* Changed some file writing function to improve software performance
	* Minor bugs fixed 

Build5.0b20140512.69
--------------------
	
	* Parameter fileAmountSaveInterval has been added 
	* Minor bugs fixed 

Build5.0b20140402.68
--------------------
	
	* New optimized Gillespie SSA algorithm has been implemented. 
	* Minor bugs fixed 

Build4.82b20140327.67
--------------------
	
	* Documentation updated 

Build4.8b20140120.66
--------------------
	
	* Trush code has been removed from the Gillespie function.
	* Documentation has been updated.  

Build4.8b20140120.65
--------------------
	
	* A possible bug in complex dissociation procedure has been fixed. 

Build4.8b20131212.64
--------------------
	
	* All the computational time stat procedures now work with normal variables insteaf of vectors. 
	* Documentation Updated

Build4.8b20131210.63
--------------------
	
	* A possible bad_allock in complex second substrate association procedure has been fixed
	* Documentation has been re-create according to the new version 
	* Graphs have been added to the documentation  

Build4.8b20131209.62
--------------------
	
	* New try and catch have been added to monitor bugs and crashes. 

Build4.8b20131125.61
--------------------
	
	* A bug in the second step of the condensation has been fixed. 

Build4.8b20131026.60
--------------------
	
	* Spontaneous reactions have been added. 
	* Several bugs Fixed

Build4.7b20131001.59
--------------------
	
	* Run time complex species dynamics information
