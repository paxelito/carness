
%lancia_serie_di_inizializzatore.m

clear all
close all

%**************************************************************************
%Inserimento dei PARAMETRI VARIABILI sui quali fare lo SCREENING, sottoforma di matrici
%o vettori

%reactionProbability = [0.000516529; 0.000258264; 0.000129132; 0.001033058; 0.002066116; 0.004132231; 0.008264463];
%nome_prob = [0.125; 0.25; 0.5; 1; 2; 4; 8];
lMaxInflux = [2];
parametro_screening = lMaxInflux;
nome_folder = [2];
%**************************************************************************


%**************************************************************************
%Inserimento dei PARAMETRI FISSI, quelli che restano cio? costanti in
%tutti gli esperimenti della serie

nSIM=1;                             %Numero di simulazioni (diversi semi random)
nSeconds=1000;                      %Numero di secondi
randomSeed=0;                       %lasciare a 0
debugLevel=0;                       %livello di dettaglio messaggi durante simulazione, lasciare a 0, >0 per debug software
timeStructuresSavingInterval=nSeconds/100;%definisce il tempo in cui vengono salvati i file durante la simulazione
fileTimesSaveInterval=0;            %Definisce il tempo in cui vengono salvati i dati sui file times, reaction_parameter e i vari living...
nReactions=200000000;               %Numero massimo di reazioni (secondo parametro di stop oltre al numero di secondi)
nHours=0;                            %Numero massimo di ore per la simulazione (=0 no vincolo)
nAttempts=0;                         %Numero di volte in cui sistema ritenta la stessa rete (=0 no vincolo)
initialMaxLength=6;                 %Lunghezza massima delle specie da creare
massima_lunghezza_su_cui_calcolare_le_reazioni = 6;          %Lunghezza massima fino alla quale creare le reazioni
maxLOut = 2;						%se=0 non viene considerato, altrimenti... Quando influx_rate > 0 indica la lunghezza massima delle molecole che possono uscire dal contenitore, quando influx_rate = 0 indica fino a quale lunghezza le molecole non variano in quantita' (simulazione membrana permeabile)
ECConcentration=0;
alphabet = ['AB'];
overallConcentration=0.0333; 
volume=1e-18;
energy=0;                            %energia 1 considerata, 0 non considerata
complexFormationSymmetry=0;
fino_a_che_lunghezza_i_polimeri_non_catalizzano = 2;
cleavageProbability=0.5;
reverseReactions=0;
reactionProbability=(1/126)/2;
Kass = 50;
Kdiss = 25;
Kcpx = 50;
K_cpx = 1;
K_nrg = 0;
K_nrg_decay =0;                      %coefficiente di decadimento delle molecole o dei carrier dalla propria componente energetica
revRctRatio = 10;
ratioSpeciesEnergizable = 0;         %percentuale di specie presenti nel sistema che possono essere energizzate  per ogni specie create c'? una certa probabilit? di essere energizzabile o meno
moleculeDecay_KineticConstant=0.02;
diffusion_contribute=0;
solubility_threshold=0;
influx_rate=0;                       %se ? 0 il sistema ? chiuso
%lMaxInflux=4;                        %lunghezza massima delle molecole presenti nell'influx
ratio_firing_disk=0;                 %percentuale di specie da cancellare rispetto a tutte quelle che restano dopo aver conservato i polimeri fino a lunghezzamaxfd
lunghezza_max_fd = 7;                %lunghezza dei monomeri/polimeri da conservare
scelta_concentrazioni =1 ;           % parametro switch: 1 uniforme su tutte le specie esistenti del firing disk, 2 uniforme sulle lunghezze, 3 powerlaw con esponente gamma
gamma_powerlaw_concentrazioni = 2.1; %esponente della powerlaw in caso 3
decisione_catalizzatori=1;           %parametri per la distribuzione dei catalizzatori: distribuzione dei catalizzatori 1 random 2 con distribuzione
controllo_ACS_nel_ciclo = 1;         %controllo che non ci siano cicli nell'influx %1: nessun controllo %2: no cicli nel grafo substrato-prodotto %3: no cicli nel grafo catalizzatore-prodotto 4: no cicli nel grafo catalizzatore-prodotto n? nel grafo substrato-prodotto
                                     % NOVITA': se metto
                                     % controllo_ACS_nel_ciclo = 5 accetto
                                     % solo quelle reti che hanno
                                     % necessariamnete un ciclo nel flusso.
newSpeciesProbMinThreshold = 1;       % NUOVO PARAMETRO
volumeGrowth = 0;                    %NUOVO PARAMETRO
stochDivision = 0;                   %NUOVO PARAMETRO
                                     
simFolder.nets = 10;					% Number of different networks ensambles, for every network will be performed nSim different simulation (differnt random seeds)
simFolder.name = 'Sistema_fino_a_6';       %Nome della cartella dove verr? salvata la simulazione
simFolder.path = 'SIMS';   %Percorso dove verr? creata la cartella simFolder dove verranno salvati tutti i file

%**********************************************************************

nGEN=10;                             %Numero di generazioni, al momento significa che alla fine di ogni generazione da ogni file di fine sim partono altre Nsim, lasciare ad 1!!!
lastFiringDiskSpeciesID = 0;         %calcolata in automatico
for i = 1:massima_lunghezza_su_cui_calcolare_le_reazioni
    lastFiringDiskSpeciesID = lastFiringDiskSpeciesID + length(alphabet)^i;
end
lastFiringDiskSpeciesID = lastFiringDiskSpeciesID -1;


thisFolder = pwd;
cd(simFolder.path)
if exist(simFolder.name, 'dir') == 0
    mkdir(simFolder.name);
end
cd(simFolder.name)
fid20 = fopen('lanciatore.sh','w');
cd(thisFolder)

%introduzione delle FUNZIONI BOOLEANE nell'energia:
%la combinazione di input riguarda quali elementi possano/debbano essere
%carichi per rendere possibile la reazione. Nello specifico la tabella ?
%questa:
%C	S1	S2
%+	+	+
%+	+	-
%+	-	+
%+	-	-
%-	+	+
%-	+	-
%-	-	+
%-	-	-

%un esempio di funzione  booleana sar? pertanto 01100101
%in questo caso si chiede di indicare nella  matrice 'funzioni_booleane' le
%funzioni che si vogliono rendere possibili, che verranno successivamente
%assegnate con probabilit? uniforme alle reazioni 
%la funzione ? divisa a met?, la prima met? corrisponde alla condensazione
%(8 bit), la seconda parte al cleavage (4 bit).
%esempio: funzione 00001110 sulla condensazione e funzione 1111 sul
%cleavage, la funzione booleana viene codificata come 000011101111

funzioni_booleane = ('0 0 0 0 1 1 1 0 1 1 1 1');
%funzioni_booleane_in_dec = bi2de(funzioni_booleane,'left-msb'); %converto in decimale
funzioni_booleane_in_dec = bin2dec(funzioni_booleane); %converto in decimale
for i=1:length(funzioni_booleane_in_dec) %assegno la probabilit? di scelta della funzione booleana, per default ? uniforme

    funzioni_booleane_in_dec(i,2)=1/length(funzioni_booleane_in_dec);
end

%**************************************************************************



%*********************
%***** S T A R T *****
%*********************

[rows,b]=size(parametro_screening);

for i = 1:b %numero di valori delle variabili (e.g. numero di valori della probabilit?)
    
        for z = 1:simFolder.nets %numero di reti per ogni combinazione di variabili
    
            %scrivo il nome delle cartelle
            parte1_nome_cartella = ('Proto_fino_a_6_');
            parte2_nome_cartella = num2str(nome_folder(i));
            parte3_nome_cartella = ('_rete_n_');      
            
            if z <10
                parte_a=num2str(0);
                parte_b=num2str(z);
                parte4_nome_cartella = strcat(parte_a,parte_b);
            else
                parte4_nome_cartella = num2str(z);
            end          
            nome_cartella= strcat(parte1_nome_cartella,parte2_nome_cartella,parte3_nome_cartella,parte4_nome_cartella);
            
            %scrivo il lanciatore.sh
            riga_lanciatore = strcat(' nice ./acsm2s ./',nome_cartella,'/ ./',nome_cartella,'/res/ ./', nome_cartella,'/ >sims','_',parte2_nome_cartella,'_',num2str(z),'.log');
            riga_lanciatore_2 = strcat('echo "Buh/',nome_cartella,'" ;',riga_lanciatore);
            count = fprintf(fid20,'%s\n ',riga_lanciatore_2);
            clear riga_lanciatore
                                          
            %lancio il vero e proprio inizializzatore            
            inizializzatore_ACS(nGEN, nSIM, nSeconds, nReactions, initialMaxLength, massima_lunghezza_su_cui_calcolare_le_reazioni, overallConcentration, ...
                alphabet, complexFormationSymmetry, fino_a_che_lunghezza_i_polimeri_non_catalizzano, reactionProbability, cleavageProbability, ...
                diffusion_contribute, solubility_threshold, influx_rate, reverseReactions,K_nrg, moleculeDecay_KineticConstant, ratio_firing_disk, ...
                lunghezza_max_fd, scelta_concentrazioni, gamma_powerlaw_concentrazioni,decisione_catalizzatori, lastFiringDiskSpeciesID, ECConcentration, ...
                volume, energy, controllo_ACS_nel_ciclo, K_nrg_decay, nome_cartella, funzioni_booleane_in_dec,ratioSpeciesEnergizable,Kass,Kdiss,Kcpx,K_cpx,...
                randomSeed, debugLevel, timeStructuresSavingInterval,maxLOut,simFolder,lMaxInflux(i),fileTimesSaveInterval,nHours,nAttempts,revRctRatio,newSpeciesProbMinThreshold,volumeGrowth,stochDivision);
           
        end
end

st = fclose(fid20);
            
            
            
