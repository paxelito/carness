function [out] = timesAnalysis(param)
% function [out] = timesAnalysis(tmpPath)
%
% This function collects all the last reactions contained in both the times and
% reactions_parameter files, hence different scatterplot between different dimensions are performed.
% Output out is a structure containing two variables:
% out.timesMatrix = all the last row of the times files
% out.cct = the correlation coefficients of the out.timesMatrix matrix
%
% INPUT
% tmpPath = path of the simulations root 

currentDir = cd();

if nargin < 1
   param.tmpPath = currentDir(); 
   param.figureVisible = 0;
   param.simFolder = 'sim';
end

cd(param.tmpPath);

disp('|--------------------------------------------------------|');
disp('|- Last times and Reaction_parameter analysis started... |');
disp('|--------------------------------------------------------|');

% READ ALL THE DIRECTORY CONTAINING SIMULATIONS
tmpFolder = strcat('*',param.simFolder,'*');
simDirs = dir(tmpFolder);

timesMatrix = zeros(size(simDirs),12);

% For each folder the necessary computations are performed
for i=1:size(simDirs)
    
   if isdir(strcat(simDirs(i).name))
   
        % Go into the results folder
        cd(strcat(simDirs(i).name,'/res'));
        
        disp(strcat('  |- Folder: ',simDirs(i).name,'/res...'));

        % Select Times and reactions files
        timeFiles = dir('*times*');
        rctFiles = dir('*reactions_parameters*');

        % For each time file
        for j=1:size(timeFiles)

            % timeFiles(j).name is the current file times. 

            os = computer('arch');
            if strcmp(os,'maci64') || strcmp(os,'maci') || strcmp(os,'GLNX86') || strcmp(os,'GLNXA64')
                % File times - last row
                eval(['[s,timeLastLine]=system(''tail -n 1 ',timeFiles(j).name,''');']);
                if isstrprop(timeLastLine(end), 'cntrl'), timeLastLine(end) = []; end
                timeLastLine = strread(timeLastLine);
                timesMatrix(i,1) = timeLastLine(1:1);
                timesMatrix(i,2:8) = timeLastLine(5:11);
                % File reations_parameters - last row
                eval(['[t,rctLastLine]=system(''tail -n 1 ',rctFiles(j).name,''');']);
                if isstrprop(rctLastLine(end), 'cntrl'), rctLastLine(end) = []; end
                rctLastLine = strread(rctLastLine);
                timesMatrix(i,9) = rctLastLine(10);
                timesMatrix(i,10) = rctLastLine(12);
                timesMatrix(i,11) = timeLastLine(13);               

            else
                % Windows procedure
                % Windows procedure - File times - last row
                fid = fopen(timeFiles(j).name,'r');
                Tvalues = fscanf(fid,'%f',15);
                % Stop parameter
                stop = 0;
                while stop == 0
                    % Keep going until you reach the end of the file
                    Tvalues2 = fscanf(fid,'%f',15);
                    checkTvalues2 = isempty(Tvalues2);
                    if checkTvalues == 1
                        stop = 1;
                        break
                    end
                    Tvalues = Tvalues2;
                end
                fclose(fid);
                timesMatrix(i,1) = Tvalues(1);
                timesMatrix(i,2:8) = Tvalues(5:11);
                clear stop;
                % File reactions_parameters - last row
                fid = fopen(rctFiles(j).name,'r');
                Rvalues = fscanf(fid,'%f',12);
                stop = 0;
                while stop == 0
                    Rvalues2 = fscanf(fid,'%f',12);
                    checkRvalues2 = isempty(Rvalues2);
                    if checkRvalues2 == 1
                        stop = 1;
                        break
                    end
                    Rvalues = Rvalues2;
                end
                fclose(fid);
                timesMatrix(i,9) = Rvalues(10);
                timesMatrix(i,10) = Rvalues(12);
                timesMatrix(i,11) = Rvalues(13);
                clear stop;
            end


        end

        cd('./../..');  
    
   end
    
end



%compute corrcoef of timeFile
cct = corrcoef(timesMatrix);

% output object variable
out.cct = cct;
out.timesMatrix = timesMatrix;

%CREATE FIGURE PARAMS
%COLS
% 1.RCTS - 2.PossibleReactions - 3.Computational time - 4.species - 5.molecules -
% 6.cpx - 7.cpx mols - 8.bricks - 9.gill mean - 10.entropy - 11.prob new species

xlv = {'Reactions','Reactions','Species','Complexes','Species','Molecules','Reactions','Bricks','Molecules','Species'};
ylv = {'Species','Molecules','Molecules','Complexes Molecules','Bricks','Bricks','Bricks','Entropy','Entropy','Entropy'};
nf = {'rctVSspecies','rctVsMols','speciesVSmols','cpxVScpxMols','speciesVSbricks','molsVSbricks','rctVSbricks','bricksVSentropy','molsVSentropy','speciesVSentropy'};
xtp = [1,1,4,6,4,5,1,8,5,4];
ytp = [4,5,5,7,8,8,8,10,10,10];

if ~isdir('0_statistics')
    mkdir('0_statistics');
end
cd('0_statistics')

for k=1:length(xtp)
    if param.figureVisible == 0
        figure('Visible','off')
    else
        figure(k)
    end  
    plot(timesMatrix(:,xtp(k)),timesMatrix(:,ytp(k)), 'ko')
    grid on
    set(gca,'fontsize',15,'fontname','times');
    xlabel(xlv(k), 'Interpreter', 'latex', 'fontsize',15);
    ylabel(ylv(k), 'Interpreter', 'latex', 'fontsize',15);
    eval(['print -depsc ALL_', int2str(k), '_', char(nf(k)),'_corr.eps;']);
    eval(['figure',int2str(k), '= gcf;']);
    %eval(['saveas(figure', int2str(k), ',', '''',int2str(k), '_', char(nf(k)),'_corr.fig''',');']);
    eval(['saveas(figure', int2str(k), ',', '''',int2str(k), '_', char(nf(k)),'_corr.fig''',');']);
end

save 'ALL_timeLastRct.csv' timesMatrix -ASCII -TABS
cd('../');

cd(currentDir);

end


