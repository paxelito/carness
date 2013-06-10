%prova.m


function [specie]=crea_tutte_le_combinazioni_di_elementi(vettore_elementi,K)
%function [specie]=crea_tutte_le_combinazioni_di_elementi(vettore_elementi)

%dato un vettore di elementi e una lunghezza massima K restituisce tutte le
%possibili combinazioni di elementi ordinati

lunghezza_stringa = K;
numero_elementi = length(vettore_elementi);
righe = numero_elementi^lunghezza_stringa;

for i =1:lunghezza_stringa %colonne
   for j = 1:numero_elementi
       for z = (numero_elementi^(i-1))*(j-1)+1:numero_elementi^(i):righe
           specie(z:z+numero_elementi^(i-1)-1,i)=(vettore_elementi(j));
       end
   end
end

    