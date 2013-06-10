function [concentrazioni_iniziali] = crea_concentrazioni_iniziali(alphabet,firing_disk,initialMaxLength,lunghezza_max_fd,ratio_firing_disk,  scelta_concentrazioni, overallConcentration, gamma);
%function [concentrazioni_iniziali] = crea_concentrazioni_iniziali(alphabet,firing_disk,initialMaxLength,lunghezza_max_fd,ratio_firing_disk,  scelta_concentrazioni, overallConcentration, gamma);

%le specie "fittizie" create fino alla
%lunghezza_massima_per_calcolare_le_reazioni vengono poste uguali a 0 in
%concentrazione 

tot_species = 0;
for i = 1:initialMaxLength
    tot_species = tot_species+length(alphabet)^i;
end

lunghezza_totale = length(firing_disk(:,1));
firing_disk_bck=firing_disk;

firing_disk_2=firing_disk(1:tot_species,:);
firing_disk=[];
firing_disk=firing_disk_2;
firing_disk(:,3)=1;%check di esistenza nel firing disk


%numero_molecole = overallConcentration*volume
numero_specie = length(firing_disk(:,1));

%a seconda dei casi seleziono le specie esistenti del firing disk, quelle
%non esistenti andranno semplicemente a concentrazione 0

%%%^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

        remaining_species = tot_species;
        l_max=0;
        for i = 1:lunghezza_max_fd
            l_max=l_max+length(alphabet)^i;
        end

        remaining_species = tot_species-l_max;
        
        species_to_delete = round(ratio_firing_disk*remaining_species); %la percentuale è di reazioni fra quelle che restano
        species_to_keep = remaining_species - species_to_delete + l_max;
        
        
        for i =1:species_to_delete
            trovato = 0;
            while  trovato ==0
                index = l_max+ceil(rand*remaining_species);
                if firing_disk(index,3)==1
                    firing_disk(index,3)=0;
                    trovato = 1;
                end
            end
        end
        
    


            switch scelta_concentrazioni 

                case 1
                    %distribuzione uniforme su tutte le specie esistenti del firing disk
                    probabilita_uniforme = 1/species_to_keep;
                    for i =1:length(firing_disk(:,1))
                        if firing_disk(i,3)==1
                            concentrazioni_iniziali(i)=(probabilita_uniforme*overallConcentration);
                        else
                            concentrazioni_iniziali(i)=0;
                        end
                    end
                    

                case 2
                    %uniforme sulle lunghezza
                    
                    k=0;
                    for i =1:length(firing_disk(:,1))
                        if firing_disk(i,3)==1
                            k = k+1;
                            firing_disk_reale(k,:)=firing_disk(i,:);
                        end
                    end
                        
                    vettore_ordinato_lunghezze = unique(firing_disk_reale(:,2));
                    probabilita_per_lunghezza = 1/length(vettore_ordinato_lunghezze);

                    for i =1:length(vettore_ordinato_lunghezze)
                        probabilita_per_specie(vettore_ordinato_lunghezze(i))=probabilita_per_lunghezza/sum(firing_disk_reale(:,2)==vettore_ordinato_lunghezze(i));
                    end

                    for i = 1:length(firing_disk(:,1))
                        if firing_disk(i,3)==1
                            concentrazioni_iniziali(i)= (probabilita_per_specie(firing_disk(i,2))*overallConcentration);
                        else
                            concentrazioni_iniziali(i)=0;
                        end
                    end
                    


                case 3
                    %favorire quelle corte con una scale free di esponente gamma
                    k=0;
                    for i =1:length(firing_disk(:,1))
                        if firing_disk(i,3)==1
                            k = k+1;
                            firing_disk_reale(k,:)=firing_disk(i,:);
                        end
                    end

                    %creo la scale-free con la di Riemann
                    Z=0;
                    for i = 1:max(firing_disk_reale(:,2))
                        Z=Z+i^-gamma;
                    end

                    for i = 1:max(firing_disk_reale(:,2))
                        p(i)=(1/Z)*i^-gamma;
                    end


                     for i = 1:length(firing_disk(:,1))
                        if firing_disk(i,3)==1
                                                       
                            concentrazioni_iniziali(i)=(overallConcentration*p(firing_disk(i,2)))/(sum(firing_disk_reale(:,2)==firing_disk(i,2)));
                        else
                            concentrazioni_iniziali(i)=0;
                        end
                    end
                    
                    %normalizzazione per avere la concentrazione
                    concentrazioni_iniziali=concentrazioni_iniziali/sum(concentrazioni_iniziali)*overallConcentration;
                    %sum(concentrazioni_iniziali)


            end

            concentrazioni_iniziali(tot_species+1:lunghezza_totale)=0;
            concentrazioni_iniziali=concentrazioni_iniziali';
 
            valore(1:max(firing_disk_bck(:,2)))=0;
            for i = 1:max(firing_disk_bck(:,2))

                for j = 1:numero_specie

                    if firing_disk_bck(j,2)==i;
                        valore(i)=valore(i)+concentrazioni_iniziali(j);
                    end
                end
            end

            %STAMPA DISTRIBUZIONI DELLE CONCENTRAZIONI
%             figure(123)
%             plot(valore,'+')
%             hold on
%             plot(valore,'k')
%             grid on
% 
% 
%             figure (321)
%             plot(log(valore),log(1:length(valore)),'+')
%             hold on
%             grid on
%             plot(log(valore),log(1:length(valore)),'k')
%     
%     







