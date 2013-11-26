function [out] = allTimesAnalysis(params)
% function [out] = allTimesAnalysis(params)
%

%
% INPUT
%    params.tmpPath = simulations path; 
%    params.figureVisible = prompt figures (1), do not prompt figures (0);
%    params.deltaT = Delta T;
%    params.totT = total time of the simulation;
% OUT

disp('|--------------------------------|');
disp('|- All times analysis...         |');
disp('|--------------------------------|');

currentDir = cd();

if nargin < 1
   params.tmpPath = currentDir(); 
   params.figureVisible = 0;
end

cd(params.tmpPath);

disp('start analysis')


% READ ALL THE DIRECTORY CONTAINING SIMULATIONS
search = strcat('*',params.simFolder,'*');
simDirs = dir(search);

cd(strcat(simDirs(1).name,'/res'));
% Read configuration file
confParams = readParameters();
% File Containing all Times
times = 0:confParams.timeStructuresSavingInterval:confParams.nSeconds;
cd('./../..');

% Init aggregate matrices 
allSpecies = zeros(length(times),length(simDirs));
allMolecules = zeros(length(times),length(simDirs));
allCpx = zeros(length(times),length(simDirs));
allCpxMols = zeros(length(times),length(simDirs));
allBricks = zeros(length(times),length(simDirs));

% For each folder the necessary computations are performed
for i=1:length(simDirs)
   
    if isdir(strcat(simDirs(i).name))
        % Go into the results folder
        cd(strcat(simDirs(i).name,'/res'));

        % Select Times and reactions files
        timeFiles = dir('*times*');

        % For each time file
        for j=1:length(timeFiles)

            msg = sprintf('Processing dir %s, file %s',simDirs(i).name,timeFiles(j).name);
            disp(msg);

            timesSel = 1;

            fid=fopen(timeFiles(j).name,'r');
            tline = fgetl(fid);
            tlineb = tline;

            % Read first line of the times file
            if isstrprop(tline(end), 'cntrl'), tline(end) = []; end
            tline = strread(tline);

            allSpecies(timesSel,i) = tline(7);
            allMolecules(timesSel,i) = tline(8);
            allCpx(timesSel,i) = tline(9);
            allCpxMols(timesSel,i) = tline(10);
            allBricks(timesSel,i) = tline(11);

            timesSel = timesSel + 1;

            % The the other rows
            while ischar(tlineb)
                tline = fgetl(fid);
                tlineb = tline;
                if ischar(tlineb)
                    if isstrprop(tline(end), 'cntrl'), tline(end) = []; end
                    tline = strread(tline);
                    if and(times(timesSel) <= tline(2),tline(2)~=confParams.nSeconds)
                       allSpecies(timesSel,i) = tline(7);
                       allMolecules(timesSel,i) = tline(8);
                       allCpx(timesSel,i) = tline(9);
                       allCpxMols(timesSel,i) = tline(10);
                       allBricks(timesSel,i) = tline(11);
                       timesSel = timesSel + 1;
                    end
                end
            end
            
            fclose(fid);


        end

        cd('./../..');  
    
    end
    
end


out.allSpecies = allSpecies;
out.allMolecules = allMolecules;
out.allCpx = allCpx;
out.allCpxMols = allCpxMols;
out.allBricks = allBricks;
out.times = times;

if ~isdir('0_statistics')
    mkdir('0_statistics');
end
cd('0_statistics')

save 'ALL_0_allSpecies.csv' allSpecies -ASCII -TABS
save 'ALL_0_allMolecules.csv' allMolecules -ASCII -TABS
save 'ALL_0_allCpx.csv' allCpx -ASCII -TABS
save 'ALL_0_allCpxMols.csv' allCpxMols -ASCII -TABS
save 'ALL_0_allBricks.csv' allBricks -ASCII -TABS

% FIGURE 1
if params.figureVisible == 0
    figure('Visible','off')
else
    figure(1)
end  
plot(times,allSpecies, '-')
grid on
set(gca,'fontsize',15,'fontname','times');
xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
ylabel('Species', 'Interpreter', 'latex', 'fontsize',15);
print -depsc ALL_11_species.eps
figure1 = gcf;
saveas(figure1, 'ALL_21_species.fig');

% FIGURE 2
if params.figureVisible == 0
    figure('Visible','off')
else
    figure(2)
end  
plot(times,allMolecules, '-')
grid on
set(gca,'fontsize',15,'fontname','times');
xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
ylabel('Molecules', 'Interpreter', 'latex', 'fontsize',15);
print -depsc ALL_12_allMolecules.eps
figure1 = gcf;
saveas(figure1, 'ALL_22_allMolecules.fig');

% FIGURE 3
if params.figureVisible == 0
    figure('Visible','off')
else
    figure(3)
end  
plot(times,allCpx, '-')
grid on
set(gca,'fontsize',15,'fontname','times');
xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
ylabel('Complexes', 'Interpreter', 'latex', 'fontsize',15);
print -depsc ALL_13_allComplexes.eps
figure1 = gcf;
saveas(figure1, 'ALL_23_allComplexes.fig');

% FIGURE 4
if params.figureVisible == 0
    figure('Visible','off')
else
    figure(4)
end  
plot(times,allCpxMols, '-')
grid on
set(gca,'fontsize',15,'fontname','times');
xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
ylabel('Complex Molecules', 'Interpreter', 'latex', 'fontsize',15);
print -depsc ALL_14_allCpxMols.eps
figure1 = gcf;
saveas(figure1, 'ALL_24_allCpxMols.fig');

% FIGURE 5
if params.figureVisible == 0
    figure('Visible','off')
else
    figure(5)
end  
plot(times,allBricks, '-')
grid on
set(gca,'fontsize',15,'fontname','times');
xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
ylabel('Bricks', 'Interpreter', 'latex', 'fontsize',15);
print -depsc ALL_15_allBricks.eps
figure1 = gcf;
saveas(figure1, 'ALL_25_allBricks.fig');



cd('../');

cd(currentDir);

end


function confparams = readParameters()

    fidConf=fopen('acsm2s.conf','r');
        
    tline = fgets(fidConf);
    
    while ischar(tline)
        tline = fgets(fidConf);
        param = findstr(tline,'=');
        if isequal(tline(1:param-1),'nSeconds')
            confparams.nSeconds = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'nGEN')
            confparams.nGEN = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'nSIM')
            confparams.nSIM = str2num(tline(param+1:length(tline))); 
        elseif isequal(tline(1:param-1),'nReactions')
            confparams.nReactions = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'timeStructuresSavingInterval')
            confparams.timeStructuresSavingInterval = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'fileTimesSaveInterval')
            confparams.fileTimesSaveInterval = str2num(tline(param+1:length(tline)));            
        elseif isequal(tline(1:param-1),'reactionProbability')
            confparams.reactionProbability = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'energy')
            confparams.energy = str2num(tline(param+1:length(tline)));      
        elseif isequal(tline(1:param-1),'ECConcentration')
            confparams.ECConcentration = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'influx_rate')
            confparams.influx_rate = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'maxLOut')
            confparams.maxLOut = str2num(tline(param+1:length(tline))); 
        elseif isequal(tline(1:param-1),'ECConcentration')
            confparams.ECConcentration = str2num(tline(param+1:length(tline)));
        elseif isequal(tline(1:param-1),'volume')
            confparams.volume = str2num(tline(param+1:length(tline)));
        end
    end
    
    fclose(fidConf);
    
end



