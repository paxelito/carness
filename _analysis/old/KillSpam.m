function KillSpam(param)

currentDir = cd();
cd(param.tmpPath);

disp('|-----------------------------------------|');
disp('|- Killer and Spammer analysis is started |');
disp('|-----------------------------------------|');

% READ ALL THE DIRECTORY CONTAINING SIMULATIONS

if ~isdir('0_statistics')
    mkdir('0_statistics');
end

tmpFolder = strcat('*',param.simFolder,'*');
simDirs = dir(tmpFolder);

cd('0_statistics');
fid = fopen('ALL_results_TS1.txt','w');
fclose(fid);
cd('../');

for x = 1:length(simDirs)
    cd(strcat(simDirs(x).name,'/res'));
    disp(strcat('  |- Folder: ',simDirs(x).name,'/res...'));
    blocked = 0:param.lastSpecies;
    % creating reactions matrix
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
    
    % creating catalysis matrix
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
    [rcm ccm] = size(catalysisMatrix);
    
    % identifying "outliers"
    reactionsCounters = reactionsMatrix(:,6);
    for i = length(reactionsCounters):-1:1
        if reactionsCounters(i) < 1
            reactionsCounters(i) = [];
        end
    end
    clear i;
    outRows = 0;
    outliersMatrix = 0;
    for i = 1:rrm
        possible = ismember(reactionsMatrix(i,6),reactionsCounters);
        if possible == 1
            outRows = outRows+1;
            outliersMatrix(outRows,1:6) = reactionsMatrix(i,1:6);
        end
    end
    clear i;
    
    % identifying "killers"
    killRows = 0;
    killersMatrix = 0;
    for i = 1:outRows
        check1 = ismember(outliersMatrix(i,3),blocked);
        check2 = ismember(outliersMatrix(i,4),blocked);
        check3 = ismember(outliersMatrix(i,5),blocked);
        if ((outliersMatrix(i,2) == 1) && (check2 == 1 && check3 == 1)) || (outliersMatrix(i,2) == 0 && check1 == 1)
            killRows = killRows+1;
            killersMatrix(killRows,1:6) = outliersMatrix(i,1:6);
        end
    end
    clear i;
    if killRows > 0
        [rkm ckm] = size(killersMatrix);
        killerCatalysts = 0;
        KCRows = 0;
        for i = 1:rkm
            killerReaction = killersMatrix(i,1);
            for j = 1:rcm
                if killerReaction == catalysisMatrix(j,3) && catalysisMatrix(j,4) > 0
                    KCRows = KCRows+1;
                    killerCatalysts(KCRows,1) = killerReaction;
                    killerCatalysts(KCRows,2) = catalysisMatrix(j,2);
                    killerCatalysts(KCRows,3) = catalysisMatrix(j,4);
                end
            end
        end
        clear i;
        clear j;
    end
    
    % identifying "killer-spammers"
    KSRows = 0;
    KSMatrix = 0;
    for i = 1:outRows
        check2 = ismember(outliersMatrix(i,4),blocked);
        check3 = ismember(outliersMatrix(i,5),blocked);
        check4 = xor(check2,check3);
        if outliersMatrix(i,2) == 1 && check4 == 1
            KSRows = KSRows+1;
            KSMatrix(KSRows,1:6) = outliersMatrix(i,1:6);
        end
    end
    clear i;
    if KSRows > 0
        for i = KSRows:-1:1
            if KSMatrix(i,4) < 6
                check5 = ismember(KSMatrix(i,5),condensationsMatrix(:,4:5));
                check6 = ismember(KSMatrix(i,5),cleavagesMatrix(:,3));
                check7 = ismember(KSMatrix(i,5),catalysisMatrix(:,2));
                if check5 == 1 || check6 == 1 || check7 == 1
                    KSRows = KSRows-1;
                    KSMatrix(i,:) = [];
                end
            else
                check5 = ismember(KSMatrix(i,4),condensationsMatrix(:,4:5));
                check6 = ismember(KSMatrix(i,4),cleavagesMatrix(:,3));
                check7 = ismember(KSMatrix(i,4),catalysisMatrix(:,2));
                if check5 == 1 || check6 == 1 || check7 == 1
                    KSRows = KSRows-1;
                    KSMatrix(i,:) = [];
                end
            end
        end
    end
    clear i;
    checkKSM = isempty(KSMatrix);
    if checkKSM == 0
        [rksm cksm] = size(KSMatrix);
        KSCatalysts = 0;
        KSCRows = 0;
        for i = 1:rksm
            KSReaction = KSMatrix(i,1);
            for j = 1:rcm
                if KSReaction == catalysisMatrix(j,3) && catalysisMatrix(j,4) > 0
                    KSCRows = KSCRows+1;
                    KSCatalysts(KSCRows,1) = KSReaction;
                    KSCatalysts(KSCRows,2) = catalysisMatrix(j,2);
                    KSCatalysts(KSCRows,3) = catalysisMatrix(j,4);
                end
            end
        end
        clear i;
        clear j;
    end
    
    % identifying "spammers"
    SpamRows = 0;
    SpammersMatrix = 0;
    for i = 1:outRows
        check1 = ismember(outliersMatrix(i,3),blocked);
        check2 = ismember(outliersMatrix(i,4),blocked);
        check3 = ismember(outliersMatrix(i,5),blocked);
        if ((outliersMatrix(i,2) == 1) && (check2 == 0 && check3 == 0)) || (outliersMatrix(i,2) == 0 && check1 == 0)
            SpamRows = SpamRows+1;
            SpammersMatrix(SpamRows,1:6) = outliersMatrix(i,1:6);
        end
    end
    clear i;
    if SpamRows > 0
        SpammersMatrix(:,7) = zeros(SpamRows,1);
        for i = SpamRows:-1:1
            if SpammersMatrix(i,2) == 1
                check5 = ismember(SpammersMatrix(i,4),condensationsMatrix(:,4:5));
                check6 = ismember(SpammersMatrix(i,4),cleavagesMatrix(:,3));
                check7 = ismember(SpammersMatrix(i,4),catalysisMatrix(:,2));
                if check5 == 1 || check6 == 1 || check7 == 1
                    SpammersMatrix(i,7) = SpammersMatrix(i,5);
                end
                check5 = ismember(SpammersMatrix(i,5),condensationsMatrix(:,4:5));
                check6 = ismember(SpammersMatrix(i,5),cleavagesMatrix(:,3));
                check7 = ismember(SpammersMatrix(i,5),catalysisMatrix(:,2));
                if check5 == 1 || check6 == 1 || check7 == 1
                    if SpammersMatrix(i,7) > 0
                        SpamRows = SpamRows-1;
                        SpammersMatrix(i,:) = [];
                    else
                        SpammersMatrix(i,7) = SpammersMatrix(i,4);
                    end
                end
            else
                check5 = ismember(SpammersMatrix(i,3),condensationsMatrix(:,4:5));
                check6 = ismember(SpammersMatrix(i,3),cleavagesMatrix(:,3));
                check7 = ismember(SpammersMatrix(i,3),catalysisMatrix(:,2));
                if check5 == 1 || check6 == 1 || check7 == 1
                    SpamRows = SpamRows-1;
                    SpammersMatrix(i,:) = [];
                end
            end
        end
        clear i;
    end
    checkSM = isempty(SpammersMatrix);
    if checkSM == 0
        [rsm csm] = size(SpammersMatrix);
        spammersCatalysts = 0;
        SCRows = 0;
        for i = 1:rsm
            spammerReaction = SpammersMatrix(i,1);
            for j = 1:rcm
                if spammerReaction == catalysisMatrix(j,3) && catalysisMatrix(j,4) > 0
                    SCRows = SCRows+1;
                    spammerCatalysts(KSCRows,1) = spammerReaction;
                    spammerCatalysts(KSCRows,2) = catalysisMatrix(j,2);
                    spammerCatalysts(KSCRows,3) = catalysisMatrix(j,4);
                end
            end
        end
        clear i;
        clear j;
    end
    
    cd(param.tmpPath);
    cd('0_statistics');
    fid=fopen('ALL_results_TS1.txt','a');
    fprintf(fid,'NET %d\n\n',x);
    fprintf(fid,'KILLERS\n\n');
    checkKM = isempty(killersMatrix);
    if checkKM == 1
        fprintf(fid,'No killers were found in this net\n');
    else
        [r c] = size(killersMatrix);
        for i = 1:r
            for j = 1:c
                fprintf(fid,'%d\t',killersMatrix(i,j));
            end
            fprintf(fid,'\n\n');
        end
        clear i;
        clear j;
        clear r;
        clear c;
        fprintf(fid,'Catalysts\n\n');
        for i = 1:KCRows
            fprintf(fid,'%d\t',killerCatalysts(i,1));
            fprintf(fid,'%d\t',killerCatalysts(i,2));
            fprintf(fid,'%d\n\n',killerCatalysts(i,3));
        end
        clear i;
    end
    fprintf(fid,'KILLERS - SPAMMERS\n\n');
    checkKSM = isempty(KSMatrix);
    if checkKSM == 1
        fprintf(fid,'No killers-spammers were found in this net\n\n');
    else
        [r c] = size(KSMatrix);
        for i = 1:r
            for j = 1:c
                fprintf(fid,'%d\t',KSMatrix(i,j));
            end
            fprintf(fid,'\n\n');
        end
        clear i;
        clear j;
        clear r;
        clear c;
        fprintf(fid,'Catalysts\n\n');
        for i = 1:KSCRows
            fprintf(fid,'%d\t',KSCatalysts(KSCRows,1));
            fprintf(fid,'%d\t',KSCatalysts(KSCRows,2));
            fprintf(fid,'%d\n\n',KSCatalysts(KSCRows,3));
        end
        clear i;
    end
    fprintf(fid,'SPAMMERS\n\n');
    checkSM = isempty(SpammersMatrix);
    if checkSM == 1
        fprintf(fid,'No spammers were found in this net\n\n');
    else
        [r c] = size(SpammersMatrix);
        for i = 1:r
            for j = 1:c
                fprintf(fid,'%d\t',SpammersMatrix(i,j));
            end
            fprintf(fid,'\n\n');
        end
        clear i;
        clear j;
        clear r;
        clear c;
        fprintf(fid,'Catalysts\n\n');
        for i = 1:SCRows
            fprintf(fid,'%d\t',spammerCatalysts(SCRows,1));
            fprintf(fid,'%d\t',spammerCatalysts(SCRows,2));
            fprintf(fid,'%d\n\n',spammerCatalysts(SCRows,3));
        end
        clear i;
    end
    fclose(fid);
    cd('../');
end
cd(currentDir);
end