function [out] = concAnalysis(params)
% function [out] = concAnalysis(params)
%
% INPUT
% params.tmpPath = tmpPath of the simulations root 
%
% This function performs statistics on each single simulation, on each
% single species file. 

currentDir = cd();

if nargin < 1
   params.path = currentDir();
   params.figureVisible = 0;
end

cd(params.tmpPath);

disp('|--------------------------------|');
disp('|- Concentration Analysis...     |');
disp('|--------------------------------|');


if ~isdir('0_statistics')
    mkdir('0_statistics');
end

% READ ALL THE DIRECTORY CONTAINING SIMULATIONS
search = strcat('*',params.simFolder,'*');
simDirs = dir(search);

% For each folder the necessary computations are performed
for i=1:length(simDirs)
    
    % Go into the results folder
    if isdir(strcat(simDirs(i).name))
        cd(strcat(simDirs(i).name,'/res'));
        
        thisSimFolder = strcat(simDirs(i).name,'/res');
        
        % Read configuration file
        confParams = readParameters();
        
        % File Containing all Times
        times = 0:confParams.timeStructuresSavingInterval:confParams.nSeconds;
        
        speciesFiles = dir('species_*');
        % speciesFiles = speciesFiles(1:end-1); to comment if species_2
        % does not exist
        %speciesFiles = speciesFiles(1:length(speciesFiles)-1);
        
        % For each species file, from the last to the first
        nFile = 1;
        [nSpeciesFile,r] = size(speciesFiles);
        
        for j=nSpeciesFile:-1:1
            
            %FROM VILLANI MARCO
            fid=fopen(speciesFiles(j).name,'r');            %apro il primo file
            disp(sprintf('Processing dir %s, file %s, %d/%d',simDirs(i).name,speciesFiles(j).name,nSpeciesFile-j,nSpeciesFile));
            
            %leggo gli oggetti che ci sono in ogni riga - alcuni li memorizzo
            indice=1; %definisco il parametro di controlo "continua"
            
            while indice>=1 % For each species
                
                itmp=fscanf(fid,'%d',1); %ID: Species Index
                
                %ora controllo di avere letto qualche cosa - se non ho letto nulla,
                %ho raggiunto la fine del file
                if isempty(itmp)==1
                    break;
                end;
                
                if nFile == 1
                    % per ora ho memorizzato solo nome specie e concentrazione, come
                    % esempio - tu poi dovresti fare le cohe che ti occorrono veramente
                    specie(indice).nome=fscanf(fid,'%s',1); %Species sequence
                    concentrazione(indice)=fscanf(fid,'%f',1); %Total concentration of the species
                    itmp=fscanf(fid,'%d',1); %Diffusion enhancement
                    itmp=fscanf(fid,'%d',1); %Precipitation flag
                    ftmp=fscanf(fid,'%f',1); %Dissociation Kinetic Constant
                    bindpnt(indice)=fscanf(fid,'%d',1); %Binding point
                    evaluated(indice)=fscanf(fid,'%d',1); %Evaluated
                    ftmp=fscanf(fid,'%f',1); %Species Age (in seconds)
                    itmp=fscanf(fid,'%d',1); %Number of reborns
                    itmp=fscanf(fid,'%d',1); %Catalyst ID
                    itmp=fscanf(fid,'%d',1); %Substrate ID
                    ftmp=fscanf(fid,'%f',1); %Phosphorilation Kinetic constant: NOT USED NOW!!!
                    ftmp=fscanf(fid,'%f',1); %Charged Molecules Concentration
                    ftmp=fscanf(fid,'%d',1); %fixed Concentration
                    
                    if (evaluated(indice) == 1) && (bindpnt(indice)==0) && (concentrazione(indice) > 0)
                        speciesLENvec(indice) = length(specie(indice).nome);
                    else
                        speciesLENvec(indice) = 0;
                    end
                    
                    indice=indice+1;
                else
                    % per ora ho memorizzato solo nome specie e concentrazione, come
                    % esempio - tu poi dovresti fare le cohe che ti occorrono veramente
                    tmpspecie(indice).nome=fscanf(fid,'%s',1); %Species sequence
                    overallConcMatrix(j,indice)=fscanf(fid,'%f',1); %Total concentration of the species
                    itmp=fscanf(fid,'%d',1); %Diffusion enhancement
                    itmp=fscanf(fid,'%d',1); %Precipitation flag
                    ftmp=fscanf(fid,'%f',1); %Dissociation Kinetic Constant
                    tmpbindpnt(indice)=fscanf(fid,'%d',1); %Binding point
                    tmpevaluated(indice)=fscanf(fid,'%d',1); %Evaluated
                    ftmp=fscanf(fid,'%f',1); %Species Age (in seconds)
                    itmp=fscanf(fid,'%d',1); %Number of reborns
                    itmp=fscanf(fid,'%d',1); %Catalyst ID
                    itmp=fscanf(fid,'%d',1); %Substrate ID
                    ftmp=fscanf(fid,'%f',1); %Phosphorilation Kinetic constant: NOT USED NOW!!!
                    ftmp=fscanf(fid,'%f',1); %Charged Molecules Concentration
                    ftmp=fscanf(fid,'%d',1); %fixed Concentration
                    
                    if (tmpevaluated(indice) == 1) && (tmpbindpnt(indice)==0) && (overallConcMatrix(j,indice) > 0)
                        speciesLENvec(indice) = length(tmpspecie(indice).nome);
                    else
                        speciesLENvec(indice) = 0;
                    end
                    
                    indice=indice+1;
                end;
                
            end;
            
                        
            if nFile > 1
                % Compute matrix indicators
                tmpcos = (overallConcMatrix(j,:)*overallConcMatrix(j+1,:)')/(norm(overallConcMatrix(j,:))*norm(overallConcMatrix(j+1,:)));
                coss(j+1) = tmpcos;
                angles(j+1) = acos(tmpcos);
            end
            
            if nFile == 1
                % INIT overall concentration matrix
                overallConcMatrix = zeros(nSpeciesFile,indice-1);
                overallConcMatrix(end,:) = concentrazione;
                
                cd(strcat(params.tmpPath,'/0_statistics'));
                strZero = zeroBeforeStrNum(i,length(simDirs));
                fileConcAllName = strcat('0_concentrations_ALL_',strZero,int2str(i),'.csv');
                if exist(fileConcAllName,'file')
                    delete(fileConcAllName);
                end
                fidC=fopen(fileConcAllName,'a');
                for a=1:indice-1
                    fprintf(fidC,'%s \t',specie(a).nome);
                end;
                fclose(fidC);
                cd(strcat('../',thisSimFolder));
                
                % INIT lengths analysis file (maxL,meanL,medianL)
                lenghtAnalysis = zeros(nSpeciesFile,3);
                speciesLENvec = speciesLENvec(speciesLENvec > 0);
                lenghtAnalysis(end,:) = [max(speciesLENvec),mean(speciesLENvec),median(speciesLENvec)];
                % Create vector containing all the angles, coseno (nSpecies files
                % -1) from both the previous file and the first file
                coss = zeros(1,nSpeciesFile);
                angles = zeros(1,nSpeciesFile);
                cossFromInit = zeros(1,nSpeciesFile);
                anglesFromInit = zeros(1,nSpeciesFile);
            else
                speciesLENvec = speciesLENvec(speciesLENvec > 0);
                lenghtAnalysis(j,:) = [max(speciesLENvec),mean(speciesLENvec),median(speciesLENvec)];
            end;
            %pause;
            fclose(fid);
            
            % Clear temp variable used to store species, binding points and
            % evaluation flags for each file
            clear tmpspecie; clear tmpbindpnt; clear tmpevaluated; clear speciesLENvec;

            nFile = nFile + 1;
        end
       
        disp('Save concentrations...');
        [ss,nSpecies] = size(overallConcMatrix);

        % MOVING INTO THE STATISTIC FOLDER
        cd(strcat(params.tmpPath,'/0_statistics'));
        
        fidC=fopen(fileConcAllName,'a'); 
        for k = 1 : ss    
            fprintf(fidC,' \n');                    
            for a=1:indice-1
                fprintf(fidC,'%f \t',overallConcMatrix(k,a));
            end;
        end
        fclose(fidC);


        overallConcMatrixEval = overallConcMatrix(:,evaluated>0);

        % IMPORTANT FILE ----
        overallConcMatrixEvalNoComplex = overallConcMatrix(:,(and(evaluated>0,bindpnt==0)));
        
        % Number of 0s to put in front of the sim number in file names
        % (e.g. sim 1 of 10 sims, strZero will be '0' in order to create a
        % file named XXX_01_XXX
        strZero = zeroBeforeStrNum(i,length(simDirs));

        disp('Concentration graph creation...');
        if params.figureVisible == 0
            figure('Visible','off')
        else
            figure(1)
        end 
        
        plot(times', overallConcMatrixEvalNoComplex, '-');
        grid on
        set(gca,'fontsize',15,'fontname','times');
        xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
        ylabel('Concentration', 'Interpreter', 'latex', 'fontsize',15);
        fileConcAllName = strcat('21_conc_',strZero,int2str(i),'.eps');
        legend('AA','BA','BB','AAB','ABB','AABA','AABABB','BBBB');
        eval(['print -depsc ', fileConcAllName]);
        figure1= gcf;
        fileConcAllName = strcat('31_conc_',strZero,int2str(i),'.fig');
        saveas(figure1, fileConcAllName); 
        
        disp('Trigonometric computation...');
        % Computing coseno and angle with respect to the first reaction and
        % in relation with the matrix of the actual species only
        cosFiltered = zeros(1,nSpeciesFile);
        angleFiltered = zeros(1,nSpeciesFile);
        cosFilteredINIT = zeros(1,nSpeciesFile);
        angleFilteredINIT = zeros(1,nSpeciesFile);
        
        for h = 2:length(coss)
        	tmpcosfrominit = (overallConcMatrix(1,:)*overallConcMatrix(h,:)')/(norm(overallConcMatrix(1,:))*norm(overallConcMatrix(h,:)));
            cossFromInit(h) = tmpcosfrominit;
            anglesFromInit(h) = acos(tmpcosfrominit);
            
            tmpcosFiltered = (overallConcMatrixEvalNoComplex(h-1,:)*overallConcMatrixEvalNoComplex(h,:)')/...
                (norm(overallConcMatrixEvalNoComplex(h-1,:))*norm(overallConcMatrixEvalNoComplex(h,:)));
            cosFiltered(h) = tmpcosFiltered;
            angleFiltered(h) = acos(tmpcosFiltered);
            
            tmpcosFilteredINIT = (overallConcMatrixEvalNoComplex(1,:)*overallConcMatrixEvalNoComplex(h,:)')/...
                (norm(overallConcMatrixEvalNoComplex(1,:))*norm(overallConcMatrixEvalNoComplex(h,:)));
            cosFilteredINIT(h) = tmpcosFilteredINIT;
            angleFilteredINIT(h) = acos(tmpcosFilteredINIT);
        end
        
        % -----------------------------------------------------------------
        
        disp('Save trigonometric graph 1...');
        if params.figureVisible == 0
            figure('Visible','off')
        else
            figure(2)
        end 
        plot(times', coss, 'ko-');
        hold on
        plot(times', angles, 'ro:');
        plot(times', cossFromInit, 'bo-');
        plot(times', anglesFromInit, 'go:');
        grid on
        set(gca,'fontsize',15,'fontname','times');
        xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
        ylabel('Coseno and Arcocoseno', 'Interpreter', 'latex', 'fontsize',15);
        legend('Coseno','Angle','Coseno (init)','Angle (init)');
        hold off
        fileConcAllName = strcat('22_coseno_',strZero,int2str(i),'.eps');
        eval(['print -depsc ', fileConcAllName]);
        figure2= gcf;
        fileConcAllName = strcat('32_coseno_',strZero,int2str(i),'.fig');
        saveas(figure2, fileConcAllName); 
        
        disp('Save trigonometric graph 2...');
        if params.figureVisible == 0
            figure('Visible','off')
        else
            figure(3)
        end 
        plot(times', cosFiltered, 'ko-');
        hold on
        plot(times', angleFiltered, 'ro:');
        plot(times', cosFilteredINIT, 'bo-');
        plot(times', angleFilteredINIT, 'go:');
        grid on
        set(gca,'fontsize',15,'fontname','times');
        xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
        ylabel('Coseno and Arcocoseno', 'Interpreter', 'latex', 'fontsize',15);
        legend('Coseno','Angle','Coseno (init)','Angle (init)');
        hold off
        fileConcAllName = strcat('23_cosenoFILTERED_',strZero,int2str(i),'.eps');
        eval(['print -depsc ', fileConcAllName]);
        figure3= gcf;
        fileConcAllName = strcat('33_cosenoFILTERED_',strZero,int2str(i),'.fig');
        saveas(figure3, fileConcAllName);
 
        disp('Save length analysis graph...');
        if params.figureVisible == 0
            figure('Visible','off')
        else
            figure(4)
        end 
        plot(times', lenghtAnalysis);
        grid on
        set(gca,'fontsize',15,'fontname','times');
        xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
        ylabel('Length', 'Interpreter', 'latex', 'fontsize',15);
        legend('Max L','Mean L','Median L');
        fileConcAllName = strcat('24_lengthAnalysis_',strZero,int2str(i),'.eps');
        eval(['print -depsc ', fileConcAllName]);
        figure4= gcf;
        fileConcAllName = strcat('34_lengthAnalysis_',strZero,int2str(i),'.fig');
        saveas(figure4, fileConcAllName);

        %compute corrcoef of species file (NO complexes NO notEvaluated)
        cct = corrcoef(overallConcMatrixEvalNoComplex);
        filename = strcat('0_cct_',strZero,int2str(i),'.txt');
        eval(['save ', filename,' cct -ASCII -DOUBLE -TABS']);
         
        filename = strcat('0_lengthAnalysis_',strZero,int2str(i),'.txt');
        eval(['save ', filename,' lenghtAnalysis -ASCII -DOUBLE -TABS']);
            
        % SAVING TRIGONOMETRIC ANALYSIS
        filename = strcat('0_coss_',strZero,int2str(i),'.txt');  
        scoss = coss'; eval(['save ', filename,' scoss -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_angle_',strZero,int2str(i),'.txt');  
        sangles = angles'; eval(['save ', filename,' sangles -ASCII -DOUBLE -TABS']);
      
        filename = strcat('0_scossFromInit_',strZero,int2str(i),'.txt');  
        scossFromInit = cossFromInit'; eval(['save ', filename,' scossFromInit -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_sanglesFromInit_',strZero,int2str(i),'.txt');  
        sanglesFromInit = anglesFromInit'; eval(['save ', filename,' sanglesFromInit -ASCII -DOUBLE -TABS']);
        
        % SAVING FILTERED TRIGONOMETRIC ANALYSIS
        filename = strcat('0_Filteredscoss_',strZero,int2str(i),'.txt');
        Filteredscoss = cosFiltered'; eval(['save ', filename,' Filteredscoss -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_Filteredsangles_',strZero,int2str(i),'.txt');
        Filteredsangles = angleFiltered'; eval(['save ', filename,' Filteredsangles -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_FilteredscossFromInit_',strZero,int2str(i),'.txt');
        FilteredscossFromInit = cosFilteredINIT'; eval(['save ', filename,' FilteredscossFromInit -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_FilteredsanglesFromInit_',strZero,int2str(i),'.txt');
        FilteredsanglesFromInit = angleFilteredINIT'; eval(['save ', filename,' FilteredsanglesFromInit -ASCII -DOUBLE -TABS']);
        
        filename = strcat('0_concentrations_EVAL_',strZero,int2str(i),'.csv');
        if exist(filename,'file')
            delete(filename); 
        end
        fidC=fopen(filename,'a'); 
        for a=1:indice-1
            if evaluated(a) > 0
                fprintf(fidC,'%s \t',specie(a).nome);
            end
        end;
        [ss,nSpecies] = size(overallConcMatrixEval);
        for k = 1 : ss    
            fprintf(fidC,' \n');                    
            for a=1:nSpecies
                fprintf(fidC,'%f \t',overallConcMatrixEval(k,a));
            end;
        end
        fclose(fidC);

        filename = strcat('0_concentrations_EVALNOCPX_',strZero,int2str(i),'.csv');
        if exist(filename,'file')
            delete(filename); 
        end    
        fidC=fopen(filename,'a'); 
        for a=1:indice-1
            if (evaluated(a) > 0) && (bindpnt(a) == 0)
                fprintf(fidC,'%s \t',specie(a).nome);
            end
        end;
        [ss,nSpecies] = size(overallConcMatrixEvalNoComplex);
        for k = 1 : ss    
            fprintf(fidC,' \n');                    
            for a=1:nSpecies
                fprintf(fidC,'%f \t',overallConcMatrixEvalNoComplex(k,a));
            end;
        end
        fclose(fidC);

        cd('./..');  
        
        clear overallConcMatrix;
        clear overallConcMatrixEval; 
        clear overallConcMatrixEvalNoComplex;
        clear specie;
        clear concentrazione;
        clear bindpnt;
        clear evaluated;

    end
    
end

    

cd(currentDir);

out = 0;

end

function strZero = zeroBeforeStrNum(tmpl, tmpL)
    strZero = '';
    nZeros = length(num2str(tmpL)) - length(num2str(tmpl));
    if nZeros > 0
        for p=1:nZeros
            strZero = strcat(strZero,'0');
        end
    end
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


