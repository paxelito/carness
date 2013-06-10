function somma(N)

close all


a = zeros(1,N);
b = zeros(1,N);
c = zeros(1,N);

for i = 1 : N
    r = rand();
    a(i) = r;
    if r > 0.5
       b(i) = 1;
    else
       b(i) = -1; 
    end
    
    c(i) = sum(b);
    
end

figure(1)
hist(a)
figure(2)
plot(c)
a
c

disp('cuai')

end

