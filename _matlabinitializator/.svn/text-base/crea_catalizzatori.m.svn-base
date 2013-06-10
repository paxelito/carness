function [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def)
%function [catalizzatore reazione specie_non_esistenti]=crea_catalizzatori (firing_disk, reactionProbability, decisione_catalizzatori, fino_a_che_lunghezza_i_polimeri_non_catalizzano, alphabet, cleavageProbability, specie_def)

tot_cleav = 0;
numero_specie = length(firing_disk(:,1));

for i=1:numero_specie
    tot_cleav = tot_cleav + firing_disk(i,2)-1;
end
tot_cond = numero_specie^2;

tot_reaz=tot_cond+tot_cleav;

%controllo
while tot_reaz*reactionProbability*cleavageProbability > tot_cleav   
    fprintf('la combinazione di reactionProbability e cleavageProbability \n è sbagliata, non ci sono cleavage possibili sufficienti \n')
    reactionProbability = input('introduci la nuova reactionProbability \n');
    cleavageProbability = input('introduci la nuova cleavageProbability \n');
end

catalisi_reali = round(tot_reaz*reactionProbability*numero_specie);

if catalisi_reali == 0
    catalizzatore = -9999;
    reazione = -9999;
    specie_non_esistenti{1,1} =-9999;
else
    
                h = 0;

                %distribuendo le catalisi a caso viene una distribuzione uniforme. 

                switch (decisione_catalizzatori) %distribuzione dei catalizzatori 1 random 2 con distribuzione
                    case 1
                        k=0; %indice reazione
                        kk = 0; %indice catalizzatore

                        while catalisi_reali > 0

                            k = k+1;
                            kk = kk + 1;

                            numero_specie_da_togliere=0;
                            for i = 1:fino_a_che_lunghezza_i_polimeri_non_catalizzano
                                numero_specie_da_togliere=numero_specie_da_togliere+length(alphabet)^i;
                            end

                            %numero_specie_da_togliere
                            index = ceil(rand*(numero_specie-numero_specie_da_togliere))+numero_specie_da_togliere;




                %             if fino_a_che_lunghezza_i_polimeri_non_catalizzano == 0 %i monomeri non catalizzano 0, sennò 1
                %                 index = ceil(rand*numero_specie-length(alphabet))+length(alphabet);
                %             else
                %                 index = ceil(rand*numero_specie);
                %             end
                %             
                            catalizzatore(kk,1)=kk; %id catalizzatore
                            catalizzatore(kk,2)=index; %id specie
                            catalizzatore(kk,3)= k; %id reazione




                            if rand < cleavageProbability %cleveage o condensazione??

                                catalizzatore(kk,4)=1;

                                %caso cleveage 

                                trovato = 0;
                                while trovato == 0


                                    index_reaz = ceil(rand*(numero_specie-length(alphabet)))+length(alphabet);

                                    punto_di_taglio=ceil(rand*(firing_disk(index_reaz,2)-1));


                                    reazione(k,1)=k;
                                    reazione(k,2)=1;    %id del cleavage: 1 cleavage 0 condensazione 

                                    reazione(k,3)=firing_disk(index_reaz,1);

                                    sp = char(specie_def(:,:));
                                    sp1=char(sp(index_reaz,1:punto_di_taglio));
                                    sp2=char(sp(index_reaz,punto_di_taglio+1:firing_disk(index_reaz,2)));

                                    for i =1:length(specie_def(:,1))
                                        if strcmp(deblank(sp(i,:)),sp1)==1
                                            reazione(k,4)=i;
                                        end
                                        if strcmp(deblank(sp(i,:)),sp2)==1
                                            reazione(k,5)=i;
                                        end
                                    end



                                    for i = length(reazione(:,1)):-1:1
                                        if ((sum(reazione(k,2:5)==reazione(i,2:5)))==4 && i~=k ) 
                                            reazione(k,:)=[];
                                            k = k-1;
                                            catalizzatore(kk,3)= i;
                                            trovato =1;
                                            break
                                        else
                                            %CONTROLLARE IL CONTROLLO!!!!! DOPO IL ||
                                            %TOGLIERE IL CONTROLLO DA QUI E DA SOTTO!!!
                                            if (sum(reazione(k,3:5)==reazione(i,3:5))==3 && reazione(k,2) ~= reazione(i,2)) || ((reazione(k,3)==reazione(i,3)&&reazione(k,4)==reazione(i,5)&&reazione(k,5)==reazione(i,4)))
                                                trovato =0;
                                                break
                                            else
                                                trovato = 1;
                                            end

                                        end


                                    end



                                end



                            else %  caso condensazione

                                catalizzatore(kk,4)=0;

                                trovato = 0;

                                while trovato == 0

                                        reazione(k,1)=k;
                                        reazione(k,2)=0;    %id della condensazione: 1 cleavage 0 condensazione 

                                        index_specie_1 = ceil(rand*(numero_specie));
                                        index_specie_2 = ceil(rand*(numero_specie));

                                        nuova_specie = [deblank(specie_def(index_specie_1,:)), deblank(specie_def(index_specie_2,:))];
                                        nuova_specie=char(nuova_specie);

                                        sp = char(specie_def(:,:));

                                        found = 0; % controllo per vedere se trovo  una specie che  esiste già

                                        for i = 1:length(specie_def(:,1))

                                            if strcmp(deblank(sp(i,:)),deblank(nuova_specie))==1

                                                reazione(k,3)=i;
                                                found = 1;

                                            end

                                            if strcmp(deblank(sp(i,:)),deblank(sp(index_specie_1,:)))==1
                                                reazione(k,4)=i;
                                            end

                                            if strcmp(deblank(sp(i,:)),deblank(sp(index_specie_2,:)))==1
                                                reazione(k,5)=i;
                                            end

                                        end






                                        if found == 0   % se ho trovato una specie che NON esiste

                                                h = h +1;
                                                reazione(k,3)=length(specie_def(:,1))+h;
                                                specie_non_esistenti(h)={nuova_specie};

                                                for iii = h:-1:1
                                                    if strcmp(specie_non_esistenti(h),specie_non_esistenti(iii))==1 && h ~= iii
                                                        specie_non_esistenti(h)=[];
                                                        h = h-1;
                                                        reazione(k,3)=length(specie_def(:,1))+iii;
                                                   end
                                                end
                                        end


                                        %controllo che la reazione non esista già


                                        for i = length(reazione(:,1)):-1:1
                                            if (sum(reazione(k,2:5)==reazione(i,2:5)))==4 && i~=k 

                                                reazione(k,:)=[];
                                                k = k-1;
                                                catalizzatore(kk,3)= i;
                                                trovato =1;
                                                break

                                            else


                                                if (sum(reazione(k,3:5)==reazione(i,3:5))==3 && reazione(k,2) ~= reazione(i,2)) || ((reazione(k,3)==reazione(i,3)&&reazione(k,4)==reazione(i,5)&&reazione(k,5)==reazione(i,4)))
                                                    trovato =0;
                                                    break
                                                else
                                                    trovato = 1;
                                                end

                                            end
                                        end



                                end


                            end

                            %controllo per evitare che lo stesso catalizzatore catalizzi la
                            %stessa reazione
                            trovato_uguale = 1;
                            for iiii = length(catalizzatore(:,1)):-1:1
                                if sum(catalizzatore(kk,2:3)==catalizzatore(iiii,2:3))==2 && kk ~= iiii
                                    catalizzatore(kk,:)=[];
                                    kk = kk-1;
                                    trovato_uguale = 0;
                                    break
                                end
                            end

                            if trovato_uguale == 1
                                catalisi_reali = catalisi_reali-1;
                            end



                        end

                        if exist('specie_non_esistenti')>0
                            specie_non_esistenti=specie_non_esistenti'; %CONTROLLARE LA QUESTIONE DI COME VENGONO SCELTI I SUBSTRTI NEL CASO AABB è A + ABB oppue AA + BB?
                        else
                            specie_non_esistenti{1,1} =-9999;
                        end


                    case 2
                        %da implementare

                end
                
end
    