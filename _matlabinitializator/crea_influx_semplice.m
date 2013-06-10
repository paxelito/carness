

function [influx] = crea_influx_semplice(lMaxInflux,alphabet)

% total Number of species
sn = 0;
for i = 1:lMaxInflux
   sn = sn + length(alphabet)^i;  
end

influx = zeros(sn,2);
for j = 1:sn
   influx(j,1)=j;
   influx(j,2)=1./sn; 
end

