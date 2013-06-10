

function [firing_disk] = crea_firing_disk(alphabet,massima_lunghezza_su_cui_calcolare_le_reazioni)
%function [firing_disk] = crea_firing_disk(alphabet,massima_lunghezza_su_cui_calcolare_le_reazioni)

tot_species = 0;

for i = 1:massima_lunghezza_su_cui_calcolare_le_reazioni
    tot_species = tot_species+length(alphabet)^i;
    step(i)=length(alphabet)^i;
end


for i=1:tot_species
    id_species(i,1)=i;
end

k = 1;
for i =1:length(step)
    id_species(k:step(i)+k-1,2)=i;
    k = k+step(i);
end

firing_disk=id_species;