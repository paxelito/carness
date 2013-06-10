%lancia_acs.m

clear all
close all

%parametri
kdiss = 0 ; 
kcomplex = 1e6; 
kcond = 6e8;
k_complex = 1e-4;

AB = 0;
C = 2e-7;
CA = 0;

k = 0;
for A = 10e-7:10e-7:10e-6
    
    k=k+1
    j=0;
    for B = 10e-7:10e-7:10e-6
        
        j=j+1
        
        
        [t y] = ACS_reverse_reaction_con_input(A,B,AB,C,CA,kdiss,kcomplex,kcond,k_complex);
        
        
        Keq(k,j)=(y(length(y(:,1)),3))/(y(length(y(:,1)),1)*y(length(y(:,1)),2));
        
    
        
    end
end

imagesc(Keq)