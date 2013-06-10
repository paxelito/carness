function [catalizzatore reazione specie_non_esistenti matrice_adiacenza_sub_prod matrice_adiacenza_cat_prod] = crea_e_controlla_i_catalizzatori (controllo_ACS_nel_ciclo, firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def, influx);
%function [catalizzatore reazione specie_non_esistenti] = crea_e_controlla_i_catalizzatori (controllo_ACS_nel_ciclo, firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def, influx);


%controllo no ACS nell'influx
switch controllo_ACS_nel_ciclo 
    
    case 1  % nessun controllo
        
        matrice_adiacenza_sub_prod =0;
        matrice_adiacenza_cat_prod = 0;
        [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def);

    case 2  %no cicli nel grafo substrato-prodotto
        
        matrice_adiacenza_sub_prod(1:length(influx(:,1)),1:length(influx(:,1)))=0;
        
        check_ACS = 0;
        while check_ACS == 0
            
            check_ACS = 1;
            matrice_adiacenza_sub_prod(1:max(influx(:,1)),1:max(influx(:,1)))=0;
            
            [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def);
            
            for i = 1:length(reazione(:,1))
                if sum(reazione(i,3)==influx(:,1))==1 && sum(reazione(i,4)==influx(:,1))==1 && sum(reazione(i,5)==influx(:,1))==1
                    if reazione(i,2)==0                        
                        matrice_adiacenza_sub_prod(reazione(i,4),reazione(i,3))=1;
                        matrice_adiacenza_sub_prod(reazione(i,5),reazione(i,3))=1;
                    else
                        matrice_adiacenza_sub_prod(reazione(i,3),reazione(i,4))=1;
                        matrice_adiacenza_sub_prod(reazione(i,3),reazione(i,5))=1;
                    end
                end
            end
            
            if max(real(eig(matrice_adiacenza_sub_prod))) > 0
                clear catalizzatore
                clear reazione
                clear specie_non_esistenti
                clear matrice_adiacenza_sub_prod
                check_ACS = 0;
                %inpudda = input('');
            end
        end
        
    case 3  %no cicli nel grafo catalizzatore-prodotto
        
        check_ACS = 0;
        while check_ACS == 0
            check_ACS = 1;
            
            matrice_adiacenza_cat_prod(1:max(influx(:,1)),1:max(influx(:,1)))=0;
            
            [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def);
            
            for i = 1:length(catalizzatore(:,1))
                if sum(catalizzatore(i,2)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),3)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),4)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),5)==influx(:,1))==1
                    if reazione(catalizzatore(i,3),2)==0
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),3))=1;
                    else
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),4))=1;
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),5))=1;
                    end
                end
            end           
            
            if max(real(eig(matrice_adiacenza_cat_prod))) > 0
                clear catalizzatore
                clear reazione
                clear specie_non_esistenti
                clear matrice_adiacenza_cat_prod
                check_ACS = 0;
            end
        end
        
        
    case 4  %no cicli nel grafo catalizzatore-prodotto nè nel grafo substrato-prodotto
        
        check_ACS = 0;
        counter_cicli = 0;
        while check_ACS == 0
            check_ACS = 1;
            counter_cicli = counter_cicli +1
            
            matrice_adiacenza_sub_prod(1:max(influx(:,1)),1:max(influx(:,1)))=0;
            matrice_adiacenza_cat_prod(1:max(influx(:,1)),1:max(influx(:,1)))=0;
            
            [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def);
            
            for i = 1:length(reazione(:,1))
                if sum(reazione(i,3)==influx(:,1))==1 && sum(reazione(i,4)==influx(:,1))==1 && sum(reazione(i,5)==influx(:,1))==1
                    if reazione(i,2)==0                        
                        matrice_adiacenza_sub_prod(reazione(i,4),reazione(i,3))=1;
                        matrice_adiacenza_sub_prod(reazione(i,5),reazione(i,3))=1;
                    else
                        matrice_adiacenza_sub_prod(reazione(i,3),reazione(i,4))=1;
                        matrice_adiacenza_sub_prod(reazione(i,3),reazione(i,5))=1;
                    end
                end
            end
            
            for i = 1:length(catalizzatore(:,1))
                if sum(catalizzatore(i,2)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),3)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),4)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),5)==influx(:,1))==1
                    if reazione(catalizzatore(i,3),2)==0
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),3))=1;
                    else
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),4))=1;
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),5))=1;
                    end
                end
            end           
            
            %size(matrice_adiacenza_sub_prod)
            %size(matrice_adiacenza_cat_prod)
            
            if max(real(eig(matrice_adiacenza_sub_prod))) > 0 || max(real(eig(matrice_adiacenza_cat_prod))) > 0
                clear catalizzatore
                clear reazione
                clear specie_non_esistenti
                clear matrice_adiacenza_cat_prod
                clear matrice_adiacenza_sub_prod
                check_ACS = 0;
   
            end
        end
        
        
              
    case 5  %controllo che CI SIANO NECESSARIAMENTE CICLI CATALIZZATORE - PRODOTTO NEL GRAFO
        
        
        check_ACS = 0;
        matrice_adiacenza_sub_prod = 0;
        while check_ACS == 0
            %check_ACS = 1;
            
            matrice_adiacenza_cat_prod(1:max(influx(:,1)),1:max(influx(:,1)))=0;
            
            [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def);
            
            for i = 1:length(catalizzatore(:,1))
                if sum(catalizzatore(i,2)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),3)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),4)==influx(:,1))==1 && sum(reazione(catalizzatore(i,3),5)==influx(:,1))==1
                    if reazione(catalizzatore(i,3),2)==0
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),3))=1;
                    else
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),4))=1;
                        matrice_adiacenza_cat_prod(catalizzatore(i,2),reazione(catalizzatore(i,3),5))=1;
                    end
                end
            end           
            
            if max(real(eig(matrice_adiacenza_cat_prod))) > 0
             
                check_ACS = 1;
            else
                clear catalizzatore
                clear reazione
                clear specie_non_esistenti
                clear matrice_adiacenza_cat_prod
            end
        end
        
        
        
        
        
        
        
        
        
        
        
end





