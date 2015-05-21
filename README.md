Aggiungere al file di inizializzazione il tipo di ambiente da inizializzare. 
Aggiungere al file di inizializzazione la creazione del file flusso corretta. 
Aggiunere all'analisi l'andamento anche intragenerazioni 
Spostare tutte l'analisi dentro questo GIT ed eliminare quell'altro. 
Meetere il nome giusto




RELEASE NOTES
=============

Build8.0b20150522.76
--------------------
	
	* A new class influxspecies has been introduced to deal with membrane finite diffusion of external molecules (look at the documentation for details)
	* A new parameter systemArchitecture in acsm2m.conf has been added to select the system architecture in a easiest way
	* Now surface is computed too
	* Runtime interface has been enxhanced, information have been riorganized and surface has been added
	* Files can be now saved only at the beginning and at the end of the simulation using "-1" value for the specific parameters timeStructuresSavingInterval, fileTimesSaveInterval and fileAmountSaveInterval
	* Various little improvements
	* Documentation has been updated. 
	* Demo folders CSTR, protocell_buffered_flow and protocell_finite_membrane_passage have been added to test the simulation for the specific environmental system architecture

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
