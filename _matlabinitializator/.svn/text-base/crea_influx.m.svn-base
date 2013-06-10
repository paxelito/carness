

function [influx] = crea_influx(concentrazioni_iniziali)
%function [influx] = crea_influx(concentrazioni_iniziali)


for i =1:length(concentrazioni_iniziali)
    
    influx(i,1)=i;
    influx(i,2)=concentrazioni_iniziali(i)/sum(concentrazioni_iniziali);
end

for j = length(concentrazioni_iniziali):-1:1
    if influx (j,2)==0
        influx(j,:)=[];
    end
end




















% 
% 
% 
% 
% 
% 
% tot_species = length(firing_disk(:,1));
% 
% 
% 
% switch scelta_influx
%     
%     %casuale
%     case 1
%         
%         species_to_delete = round(ratio_influx*tot_species);
%         species_to_keep = tot_species - species_to_delete;
% 
%         for i = 1:species_to_keep
%             trovato = 0;
%             while trovato == 0;
%                 influx(i,:)=firing_disk(ceil(rand*tot_species),:);
%                 if sum(influx(i,1)==influx(:,1))==1
%                     trovato = 1;
%                 end
%             end
%         end
%         influx=sort(influx);
%         
%     %casuale tenendo i polimeri fino a lunghezza x e poi ne toglie l'x%
%     case 2
%         
%  
%         remaining_species = tot_species;
%        
%         influx(1,1:2)=0;
%         
%        for i =1:tot_species
%            
%            if firing_disk(i,2)<=lunghezza_max_influx
%                influx(i,:)=firing_disk(i,:);
%                remaining_species = remaining_species-1;
%            end
%            
%        end
%        
%        species_to_delete = round(ratio_influx*remaining_species);
%        species_to_keep = remaining_species - species_to_delete;
%     
%     
%        if influx(1,1)>0
%            
% 
%             for i = length(influx(:,1))+1:length(influx(:,1))+species_to_keep
%                 trovato = 0;
%                 while trovato == 0;
%                     influx(i,:)=firing_disk(ceil(rand*tot_species),:);
% 
%                     if sum(influx(i,1)==influx(:,1))==1
%                         trovato = 1;
%                     end
%                 end
%             end
%             influx=sort(influx);
%             
%        else
%            clear influx 
%            influx = 0;
%        end
%         
%     %proporzionale alla lunghezza, conservando i monomeri
%     case 3
% 
% end
                    

       
