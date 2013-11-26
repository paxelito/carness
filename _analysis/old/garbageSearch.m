function garbageSearch(param)

currentDir = cd();
cd(param.tmpPath);

disp('|------------------------------|');
disp('|- Garbage analysis is started |');
disp('|------------------------------|');

% READ ALL THE DIRECTORY CONTAINING SIMULATIONS

if ~isdir('0_statistics')
    mkdir('0_statistics');
end

tmpFolder = strcat('*',param.simFolder,'*');
simDirs = dir(tmpFolder);

cd('0_statistics');
fid = fopen('ALL_garbage.txt','w');
fclose(fid);
cd('../');

for x = 1:length(simDirs)
    cd(strcat(simDirs(x).name,'/res'));
    disp(strcat('  |- Folder: ',simDirs(x).name,'/res...'));
    
    %creating species matrix
    sFiles = dir('species*');
    speciesFile = sFiles(length(sFiles)).name;
    fid = fopen(speciesFile);
    continua = 1;
    speciesMatrix = 0;
    while continua > 0
        index = fscanf(fid,'%d',1);
        stop = isempty(index);
        if stop == 1
            continua = 0;
            break
        end
        name = fscanf(fid,'%s',1);
        conc = fscanf(fid,'%f',1);
        sValues = fscanf(fid,'%f',12);
        if conc > 0 && sValues(5) == 1
            speciesMatrix(continua,1) = index;
            speciesMatrix(continua,2) = conc;
            continua = continua+1;
        end
    end
    fclose(fid);
    
    %creating reactions matrix
    rFiles = dir('reactions*');
    reactionsFile = rFiles(length(rFiles)-1).name;
    fid = fopen(reactionsFile);
    continua = 1;
    reactionsMatrix = 0;
    while continua > 0
        rValues = fscanf(fid,'%d',7);
        stop = isempty(rValues);
        if stop == 1
            continua = 0;
            break
        end
        reactionsMatrix(continua,1:6) = rValues(1:6);
        continua = continua+1;
    end
    fclose(fid);
    
    %dividing into condensations and cleavages
    condensations = 0;
    cleavages = 0;
    [rrm crm] = size(reactionsMatrix);
    cleavagesMatrix = 0;
    condensationsMatrix = 0;
    for i = 1:rrm
        if reactionsMatrix(i,2) == 1
            cleavages = cleavages+1;
            cleavagesMatrix(cleavages,1:6) = reactionsMatrix(i,1:6);
        else
            condensations = condensations+1;
            condensationsMatrix(condensations,1:6) = reactionsMatrix(i,1:6);
        end
    end
    clear i;
    
    %creating catalysis matrix
    cFiles = dir('catalysis*');
    catalysisFile = cFiles(length(cFiles)).name;
    fid = fopen(catalysisFile);
    continua = 1;
    catalysisMatrix = 0;
    while continua > 0
        cValues = fscanf(fid,'%f',7);
        stop = isempty(cValues);
        if stop == 1
            continua = 0;
            break;
        end
        catalysisMatrix(continua,1:4) = cValues(1:4);
        continua = continua+1;
    end
    fclose(fid);
    
    %identifying garbage
    [rsm csm] = size(speciesMatrix);
    gRows = 0;
    garbageMatrix = 0;
    for i = 1:rsm
        check1 = ismember(speciesMatrix(i,1),cleavagesMatrix(:,3));
        check2 = ismember(speciesMatrix(i,1),condensationsMatrix(:,4:5));
        check3 = ismember(speciesMatrix(i,1),catalysisMatrix(:,2));
        if check1 == 0 && check2 == 0 && check3 == 0
            gRows = gRows+1;
            garbageMatrix(gRows,1:2) = speciesMatrix(i,1:2);
        end
    end
    clear i;
    
    %printing results
    cd(param.tmpPath);
    cd('0_statistics');
    fid = fopen('ALL_garbage.txt','a');
    fprintf(fid,'NET %d\n\n',x);
    if garbageMatrix == 0
        fprintf(fid,'This net is garbage-free!\n\n');
    else
        [r c] = size(garbageMatrix);
        for i = 1:r
            fprintf(fid,'%d\t',garbageMatrix(i,1));
            fprintf(fid,'%f\n\n',garbageMatrix(i,2));
        end
    end
    fclose(fid);
    cd('../');
    clear i;
    clear r;
    clear c;
end

cd(currentDir);

end