function [firing_disk concentrazioni_iniziali specie_def influx catalizzatore reazione specie_non_esistenti matrice_adiacenza_sub_prod matrice_adiacenza_cat_prod] = inizializzatore_ACS(nGEN, nSIM, nSeconds, nReactions, initialMaxLength, massima_lunghezza_su_cui_calcolare_le_reazioni, overallConcentration, alphabet, complexFormationSymmetry, fino_a_che_lunghezza_i_polimeri_non_catalizzano, reactionProbability, cleavageProbability, diffusion_contribute, solubility_threshold, influx_rate, reverseReactions,K_nrg, moleculeDecay_KineticConstant, ratio_firing_disk, lunghezza_max_fd, scelta_concentrazioni, gamma_powerlaw_concentrazioni,decisione_catalizzatori, lastFiringDiskSpeciesID, ECConcentration, volume, energy, controllo_ACS_nel_ciclo, K_nrg_decay, nome_cartella, funzioni_booleane_in_dec,ratioSpeciesEnergizable,Kass,Kdiss,Kcpx,K_cpx, randomSeed, debugLevel, timeStructuresSavingInterval,maxLOut,simFolder,lMaxInflux,fileTimesSaveInterval,nHours,nAttempts,revRctRatio)
%function [firing_disk concentrazioni_iniziali specie_def influx catalizzatore reazione specie_non_esistenti matrice_adiacenza_sub_prod matrice_adiacenza_cat_prod] = inizializzatore_ACS(nGEN, nSIM, nSeconds, nReactions, initialMaxLength, massima_lunghezza_su_cui_calcolare_le_reazioni, overallConcentration, alphabet, complexFormationSymmetry, fino_a_che_lunghezza_i_polimeri_non_catalizzano, reactionProbability, cleavageProbability, diffusion_contribute, solubility_threshold, influx_rate, reverseReactions,K_nrg, moleculeDecay_KineticConstant, ratio_firing_disk, lunghezza_max_fd, scelta_concentrazioni, gamma_powerlaw_concentrazioni,decisione_catalizzatori, lastFiringDiskSpeciesID, ECConcentration, volume, energy, controllo_ACS_nel_ciclo, K_nrg_decay, nome_cartella, funzioni_booleane_in_dec,ratioSpeciesEnergizable,Kass,Kdiss,Kcpx,K_cpx,onlyEnvironmentCreation, randomSeed, debugLevel, timeStructuresSavingInterval,maxLOut)

 rand('state',sum(100*clock))
 rand
 
%--------------------------------------------------------------------------
%apertura file
%--------------------------------------------------------------------------
thisFolder = pwd;

cd(simFolder.path)

cd(simFolder.name)

mkdir(nome_cartella);
cd(nome_cartella)

fid1 = fopen('acsm2s.conf','w');
fid2 = fopen('_acsspecies.csv','a');
fid3 = fopen('_acsreactions.csv','a');
fid4 = fopen('_acscatalysis.csv','a');
fid5 = fopen('_acsinflux.csv','a');
fid10 = fopen('_acsnrgbooleanfunctions.csv','a');
mkdir('res');

cd(thisFolder);


%--------------------------------------------------------------------------
%inizializzazione del file di configurazione "acsm2s.conf"
%--------------------------------------------------------------------------

count = fprintf(fid1,'nGEN=');
count = fprintf(fid1,'%d\n',nGEN);
count = fprintf(fid1,'nSIM=');
count = fprintf(fid1,'%d\n',nSIM);
count = fprintf(fid1,'nSeconds=');
count = fprintf(fid1,'%d\n',nSeconds);
count = fprintf(fid1,'nReactions=');
count = fprintf(fid1,'%d\n',nReactions);
count = fprintf(fid1,'randomSeed=');
count = fprintf(fid1,'%d\n',randomSeed);
count = fprintf(fid1,'debugLevel=');
count = fprintf(fid1,'%d\n',debugLevel);
count = fprintf(fid1,'timeStructuresSavingInterval=');
count = fprintf(fid1,'%d\n',timeStructuresSavingInterval);
count = fprintf(fid1,'fileTimesSaveInterval=');
count = fprintf(fid1,'%d\n',fileTimesSaveInterval);
count = fprintf(fid1,'nHours=');
count = fprintf(fid1,'%d\n',nHours);
count = fprintf(fid1,'nAttempts=');
count = fprintf(fid1,'%d\n',nAttempts);
count = fprintf(fid1,'lastFiringDiskSpeciesID=');
count = fprintf(fid1,'%d\n',lastFiringDiskSpeciesID);
count = fprintf(fid1,'maxLOut=');
count = fprintf(fid1,'%d\n', maxLOut);
count = fprintf(fid1,'overallConcentration=');
count = fprintf(fid1,'%d\n',overallConcentration);
count = fprintf(fid1,'ECConcentration=');
count = fprintf(fid1,'%d\n',ECConcentration);
count = fprintf(fid1,'alphabet=');
count = fprintf(fid1,'%s\n',alphabet);
count = fprintf(fid1,'volume=');
count = fprintf(fid1,'%d\n',volume);
count = fprintf(fid1,'energy=');
count = fprintf(fid1,'%d\n',energy);
count = fprintf(fid1,'ratioSpeciesEnergizable=');
count = fprintf(fid1,'%d\n',ratioSpeciesEnergizable);
count = fprintf(fid1,'complexFormationSymmetry=');
count = fprintf(fid1,'%d\n',complexFormationSymmetry);
count = fprintf(fid1,'nonCatalyticMaxLength=');
count = fprintf(fid1,'%d\n',fino_a_che_lunghezza_i_polimeri_non_catalizzano);
count = fprintf(fid1,'reactionProbability=');
count = fprintf(fid1,'%d\n',reactionProbability);
count = fprintf(fid1,'cleavageProbability=');
count = fprintf(fid1,'%d\n',cleavageProbability);
count = fprintf(fid1,'reverseReactions=');
count = fprintf(fid1,'%d\n',reverseReactions);
count = fprintf(fid1,'revRctRatio=');
count = fprintf(fid1,'%d\n',revRctRatio);
count = fprintf(fid1,'K_ass=');
count = fprintf(fid1,'%d\n',Kass); %perch� sono input da file (i prossimi 4)
count = fprintf(fid1,'K_diss=');
count = fprintf(fid1,'%d\n',Kdiss);
count = fprintf(fid1,'K_cpx=');
count = fprintf(fid1,'%d\n',Kcpx);
count = fprintf(fid1,'K_cpxDiss=');
count = fprintf(fid1,'%d\n',K_cpx);
count = fprintf(fid1,'K_nrg=');
count = fprintf(fid1,'%d\n',K_nrg);
count = fprintf(fid1,'K_nrg_decay=');
count = fprintf(fid1,'%d\n',K_nrg_decay);
count = fprintf(fid1,'moleculeDecay_KineticConstant=');
count = fprintf(fid1,'%d\n',moleculeDecay_KineticConstant);
count = fprintf(fid1,'diffusion_contribute=');
count = fprintf(fid1,'%d\n',diffusion_contribute);
count = fprintf(fid1,'solubility_threshold=');
count = fprintf(fid1,'%d\n',solubility_threshold);
count = fprintf(fid1,'influx_rate=');
count = fprintf(fid1,'%d\n\n',influx_rate);
count = fprintf(fid1,'ratio_firing_disk=');
count = fprintf(fid1,'%d\n',ratio_firing_disk);
count = fprintf(fid1,'lunghezza_max_fd=');
count = fprintf(fid1,'%d\n',lunghezza_max_fd);
count = fprintf(fid1,'scelta_concentrazioni=');
count = fprintf(fid1,'%d\n',scelta_concentrazioni);
count = fprintf(fid1,'gamma_powerlaw_concentrazioni=');
count = fprintf(fid1,'%d\n',gamma_powerlaw_concentrazioni);
count = fprintf(fid1,'decisione_catalizzatori=');
count = fprintf(fid1,'%d\n',decisione_catalizzatori);
count = fprintf(fid1,'massima_lunghezza_su_cui_calcolare_le_reazioni=');
count = fprintf(fid1,'%d\n',massima_lunghezza_su_cui_calcolare_le_reazioni);
count = fprintf(fid1,'controllo_ACS_nel_ciclo=');
count = fprintf(fid1,'%d\n',controllo_ACS_nel_ciclo);
count = fprintf(fid1,'lMaxInflux=');
count = fprintf(fid1,'%d\n',lMaxInflux);

st = fclose(fid1); 


%--------------------------------------------------------------------------
%inizializzazione del file _acs_nrg_booleanfunctions.csv
%--------------------------------------------------------------------------
% 

for i = 1:length(funzioni_booleane_in_dec(:,1))
    count = fprintf(fid10,'%d\t',funzioni_booleane_in_dec(i,1));
    count = fprintf(fid10,'%d\n',funzioni_booleane_in_dec(i,2));
end
st = fclose(fid10); 


%--------------------------------------------------------------------------
%inizializzazione del firing disk 
%--------------------------------------------------------------------------
%so che il numero di combinazioni possibili per x monomenri � x^1 + x ^2 +
%... + x^initialMaxLength

[firing_disk] = crea_firing_disk(alphabet,massima_lunghezza_su_cui_calcolare_le_reazioni);


%--------------------------------------------------------------------------
%inizializzazione delle concentrazioni iniziali
%--------------------------------------------------------------------------

[concentrazioni_iniziali] = crea_concentrazioni_iniziali(alphabet,firing_disk,initialMaxLength,lunghezza_max_fd,ratio_firing_disk,  scelta_concentrazioni, overallConcentration, gamma_powerlaw_concentrazioni);


%--------------------------------------------------------------------------
%inizializzazione dell'influx 
%--------------------------------------------------------------------------

%[influx] = crea_influx(concentrazioni_iniziali);
[influx] = crea_influx_semplice(lMaxInflux,alphabet);


%--------------------------------------------------------------------------
%inizializzazione del file delle specie "_acsspecies.csv"
%--------------------------------------------------------------------------

%----------------------
%combinazioni possibili
%----------------------
k = 0;%counter id specie
for i = massima_lunghezza_su_cui_calcolare_le_reazioni:-1:1
    specie_temp=crea_tutte_le_combinazioni_di_elementi(alphabet,i);

    for j = length(specie_temp(:,1)):-1:1
        k = k+1;    
        for z = 1:length(specie_temp(1,:))
           specie_def(k,z)=specie_temp(j,z);
        end
    end
    clear specie_temp
end



k = 0;
for i=length(specie_def(:,1)):-1:1
    k = k+1;
    specie_def_2(k,:)=specie_def(i,:);
end
specie_def =specie_def_2;
    

%--------------------------------------------------------------------------
% creazione reazioni e catalizzatori
%--------------------------------------------------------------------------

[catalizzatore reazione specie_non_esistenti matrice_adiacenza_sub_prod matrice_adiacenza_cat_prod] = crea_e_controlla_i_catalizzatori (controllo_ACS_nel_ciclo, firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def, influx);


%-------------------------------------------------
%scrittura a file
%-------------------------------------------------

kk = -1;
for i=1:length(specie_def(:,1))
        kk = kk+1;
        count = fprintf(fid2,'%d\t',kk);
        tmpStr = specie_def(i,:);
        %tmpStr = tmpStr(1:sum(not(isspace(tmpstr))));
        tmpStr = strtrim(tmpStr);
        count = fprintf(fid2,'%s',tmpStr);
        count = fprintf(fid2,'\t');
        count = fprintf(fid2,'%d\t',concentrazioni_iniziali(i)); %Concentrazioni
        count = fprintf(fid2,'%d\t',1); %Coefficiente di diffusione						
        count = fprintf(fid2,'%d\t',1); %Coefficiente di precipitazione o solubilit�
        count = fprintf(fid2,'%d\t',0); %Coefficiente di degradazione del complesso, ex k -complex ***** !!!!!!!*****
        count = fprintf(fid2,'%d\t',0); %Punto di tagli del complesso (1 -- L-1)
        if concentrazioni_iniziali(i) > 0 || sum(i==catalizzatore(:,2))>0
            count = fprintf(fid2,'%d\t',1);%Se esiste. esiste se la concentraizone � maggiore di 0 oppure se � catalizzatore di qualche reazione
        else
            count = fprintf(fid2,'%d\t',1);
        end
        count = fprintf(fid2,'%d\t',0); %Et� in secondi
        count = fprintf(fid2,'%d\t',0); %Reborn
        count = fprintf(fid2,'%d\t',0); %Catalyst id
        count = fprintf(fid2,'%d\t',0); %substrate id
        count = fprintf(fid2,'%d\t',K_nrg); %k_fosforilazione velocit� con cui l'atp 
        count = fprintf(fid2,'%d\t',0); % concentrazione molecole cariche
%         if rand < ratioSpeciesEnergizable
%         	count = fprintf(fid2,'%d\n',1); % specie energizzabile
%         else
%  	        count = fprintf(fid2,'%d\n',0); % specie NON energizzabile
%         end
        if influx_rate == 0
            if maxLOut > 0
                if i <= (2^(maxLOut+1)-2)
                    count = fprintf(fid2,'%d\n',1);
                else
                    count = fprintf(fid2,'%d\n',0);
                end
            else
                count = fprintf(fid2,'%d\n',0);
            end
        else
            count = fprintf(fid2,'%d\n',0);
        end
end


%--------------------------------------------------------------------------
%inizializzazione del file dell'influx "_influx.csv"
%--------------------------------------------------------------------------

for i = 1:length(influx(:,1))
    count = fprintf(fid5,'%d \t', influx(i,1)-1);
    count = fprintf(fid5,'%d \n', influx(i,2));
end
st = fclose(fid5);


%--------------------------------------------------------------------------
%inizializzazione del file delle reazioni e dei catalizzatori
%--------------------------------------------------------------------------

if  catalizzatore(1,1) == -9999;
else
            for i=1:length(catalizzatore(:,1))
                    count = fprintf(fid4,'%d\t',catalizzatore(i,1)-1);
                    count = fprintf(fid4,'%d\t',catalizzatore(i,2)-1);
                    count = fprintf(fid4,'%d\t',catalizzatore(i,3)-1);
                    count = fprintf(fid4,'%d\t',0); %quante volte
                    
                    if catalizzatore(i,4)==0
                        tmpKdiss = Kdiss / revRctRatio;
                        count = fprintf(fid4,'%g\t',Kass); %kass
                        count = fprintf(fid4,'%g\t',tmpKdiss); %kdiss
                        count = fprintf(fid4,'%g\n',Kcpx); %k complex
                    else
                        tmpKass = Kass / revRctRatio;
                        tmpKcpx = Kcpx / revRctRatio;
                        count = fprintf(fid4,'%g\t',tmpKass); %kass
                        count = fprintf(fid4,'%g\t',Kdiss); %kdiss
                        count = fprintf(fid4,'%g\n',tmpKcpx); %k complex
                    end


            end
            [righe_xx colonne_xx]=size(funzioni_booleane_in_dec);
            

            for i=1:length(reazione(:,1))
                
                    indexx = ceil(rand*righe_xx);
                    funzione_giusta = funzioni_booleane_in_dec(indexx);
                    count = fprintf(fid3,'%d\t',reazione(i,1)-1);
                    count = fprintf(fid3,'%d\t',reazione(i,2));
                    count = fprintf(fid3,'%d\t',reazione(i,3)-1);
                    count = fprintf(fid3,'%d\t',reazione(i,4)-1);
                    count = fprintf(fid3,'%d\t',reazione(i,5)-1);
                    count = fprintf(fid3,'%d\t',0);

                    if energy == 2
                        eso_endo = 1; %perch� se non c'� l'energia sono tutte eso
                    else            
                        if rand > energy
                            if reazione(i,2)==1
                                eso_endo =1;
                            else
                                eso_endo =0;
                            end
                        else
                            if reazione(i,2)==1
                                eso_endo =0;
                            else
                                eso_endo =1;
                            end
                        end
                    end
                    count = fprintf(fid3,'%d\n',funzione_giusta); %inserisco il numero decimale relativo alla funzione booleana della reazione

            end
end

st = fclose(fid3);
st = fclose(fid4);

%--------------------------------------------------------------------------
% aggiunta delle specie nuove al file delle specie
%--------------------------------------------------------------------------

if specie_non_esistenti{1,1}==-9999
else
    
    for i=1:length(specie_non_esistenti(:,1))
            kk = kk+1;
            count = fprintf(fid2,'%d\t',kk);
            temporal = specie_non_esistenti{i};
            count = fprintf(fid2,'%s',temporal);
            clear temporal
            count = fprintf(fid2,'\t');
            count = fprintf(fid2,'%d\t',0); %Concentrazioni
            count = fprintf(fid2,'%d\t',0); %Coefficiente di diffusione						
            count = fprintf(fid2,'%d\t',0); %Coefficiente di precipitazione o solubilit�
            count = fprintf(fid2,'%d\t',0); %Coefficiente di degradazione (per complessi)
            count = fprintf(fid2,'%d\t',0); %Punto di tagli del complesso (1 -- L-1)	
            count = fprintf(fid2,'%d\t',0); %Se esiste
            count = fprintf(fid2,'%d\t',0); %Et� in secondi
            count = fprintf(fid2,'%d\t',0); %Reborn
            count = fprintf(fid2,'%d\t',0); %Catalyst id
            count = fprintf(fid2,'%d\t',0); %substrate id
            count = fprintf(fid2,'%d\t',K_nrg); %k_fosforilazione velocit� con cui l'atp 
            count = fprintf(fid2,'%d\t',0); % concentrazione molecole cariche
           
            if rand < ratioSpeciesEnergizable
                 count = fprintf(fid2,'%d\n',1); % specie energizzabile
            else
                 count = fprintf(fid2,'%d\n',0); % specie NON energizzabile
            end
    end
end
st = fclose(fid2);
 
clear all
close all
