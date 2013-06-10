%lancia_inizializzatore_acs.m
%script che lancia l'inizializzatore per il simulatore ACSM2M e in cui sono
%contenuti tutti i parametri dell'inizializzazione

%comandi di sistema
clear all
close all

%seme random
rand('state',sum(100*clock))
rand

%--------------------------------------------------------------------------
%PARAMETRI
%--------------------------------------------------------------------------

nGEN=1;  
nSIM=1; 
nSeconds=400;
nReactions=200000000;
initialPopulationNumber=0;

initialMaxLength=3;
massima_lunghezza_su_cui_calcolare_le_reazioni = 3; % experiment: da 2 a 8


ECConcentration = 0;

alphabet = ['AB'];


lastFiringDiskSpeciesID = 0;
for i = 1:massima_lunghezza_su_cui_calcolare_le_reazioni
    lastFiringDiskSpeciesID = lastFiringDiskSpeciesID + length(alphabet)^i;
end
lastFiringDiskSpeciesID = lastFiringDiskSpeciesID -1;

overallConcentration=1e-4; 

volume=1e-15; %experiment: così basso è irrealistico

% # Energy introduction
% #	2: energy is not considered
% #	0-1: ratio between cleavage and condensation esoergonic and ergononic reactions
% #	(0 all cleavage are eso (and condensation end), 1 all condensation are eso (and cleavage endo))
energy=2;

% # Energy target (0=substrate, 1=catalsyt, 2=both)
energyTarget=0;

complexFormationSymmetry=0;

%**NEW**
fino_a_che_lunghezza_i_polimeri_non_catalizzano = 2;

reactionProbability=0.004; % experiment: 1
cleavageProbability=0.5;
reverseReactions=0;

%costanti CINETICHE
%K_eq=1000;
%parte da rivedere e correggere
Kass_o_Kdiss = 0; % se è un cleavage kdiss = 100, se è una condensazione kass =100;
rapporto_Kfor_Kback = 0; %e.g. Kass = 100 --> Kdiss = 100/100 = 1
rapporto_Kcpx_K_ass = 0;    %e.g. Kass = 100 --> Kcpx = 100*2 = 200;
K_cpxDiss=0;

%coefficiente di fosforilazione; 
K_nrg = 0;

K_irrad = 0;

%altri parametri
moleculeDecay_KineticConstant=0.02;
diffusion_contribute=0;
solubility_threshold=0; %experimentveri
influx=2;
influx_rate=1e-6;

%parametri per l'inizializzazione del firing disk
%------------------------------------------------
ratio_firing_disk=0;    %percentuale di specie da cancellare rispetto a tutte quelle che restano dopo aver conservato i polimeri fino a lunghezzamaxfd
lunghezza_max_fd = 1;     %lunghezza dei monomeri/polimeri da conservare
scelta_concentrazioni =1 ; % parametro switch: 1 uniforme su tutte le specie esistenti del firing disk, 2 uniforme sulle lunghezze, 3 powerlaw con esponente gamma
gamma_powerlaw_concentrazioni = 2.1; %esponente della powerlaw in caso 3

%parametri per la distribuzione dei catalizzatori: distribuzione dei
%catalizzatori 1 random 2 con distribuzione
decisione_catalizzatori=1;

%controllo che non ci siano cicli nell'influx
%1: nessun controllo
%2: no cicli nel grafo substrato-prodotto
%3: no cicli nel grafo catalizzatore-prodotto
%4: no cicli nel grafo catalizzatore-prodotto nè nel grafo substrato-prodotto
controllo_ACS_nel_ciclo = 4;


%richiamo la funzione inizializzatore_ACS
[fd concentrazioni specie_def influx catalizzatore reazione specie_non_esistenti matrice_adiacenza_sub_prod matrice_adiacenza_cat_prod] = inizializzatore_ACS(nGEN, nSIM, nSeconds, nReactions, initialPopulationNumber, initialMaxLength, massima_lunghezza_su_cui_calcolare_le_reazioni, overallConcentration, alphabet, complexFormationSymmetry, fino_a_che_lunghezza_i_polimeri_non_catalizzano, reactionProbability, cleavageProbability, diffusion_contribute, solubility_threshold, influx, influx_rate, reverseReactions,  Kass_o_Kdiss,rapporto_Kfor_Kback,rapporto_Kcpx_K_ass,K_cpxDiss, K_nrg, moleculeDecay_KineticConstant, ratio_firing_disk, lunghezza_max_fd, scelta_concentrazioni, gamma_powerlaw_concentrazioni,decisione_catalizzatori, lastFiringDiskSpeciesID, ECConcentration, volume, energy, energyTarget, controllo_ACS_nel_ciclo, K_irrad);


