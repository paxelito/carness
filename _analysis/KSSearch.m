blocked = 0:5;

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
    if reactionsMatrix(i,2) == 0
        cleavages = cleavages+1;
        cleavagesMatrix(i,1:6) = reactionsMatrix(i,1:6);
    else
        condensations = condensations+1;
        condensationsMatrix(i,1:6) = reactionsMatrix(i,1:6);
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
        break
    end
    catalysisMatrix(continua,1:7) = cValues(1:7);
    continua = continua+1;
end
fclose(fid);

% identifying "outliers"
reactionsCounters = sort(reactionsMatrix(:,6))';
fpc = ceil(rrm/20*19);
outliersCounter = reactionsCounters(fpc:rrm);
for i = length(outliersCounter):-1:1
    if outliersCounter(i) < 1000
        outliersCounter(i) = [];
    end
end
clear i;
outRows = 0;
outliersMatrix = 0;
for i = 1:rrm
    possible = ismember(reactionsMatrix(i,6),outliersCounter);
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
   if ((outliersMatrix(i,2) == 0) && (check2 == 1 && check3 == 1)) || (outliersMatrix(i,2) == 1 && check1 == 1)
       killRows = killRows+1;
       killersMatrix(killRows,1:6) = outliersMatrix(i,1:6);
   end
end
clear i;

% identifying "killer-spammers"
KSRows = 0;
KSMatrix = 0;
for i = 1:outRows
   check2 = ismember(outliersMatrix(i,4),blocked);
   check3 = ismember(outliersMatrix(i,5),blocked);
   check4 = xor(check2,check3);
   if outliersMatrix(i,2) == 0 && check4 == 1
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

% identifying "spammers"
SpamRows = 0;
SpammersMatrix = 0;
for i = 1:outRows
   check1 = ismember(outliersMatrix(i,3),blocked);
   check2 = ismember(outliersMatrix(i,4),blocked);
   check3 = ismember(outliersMatrix(i,5),blocked);
   if ((outliersMatrix(i,2) == 0) && (check2 == 0 && check3 == 0)) || (outliersMatrix(i,2) == 1 && check1 == 0)
       SpamRows = SpamRows+1;
       SpammersMatrix(SpamRows,1:6) = outliersMatrix(i,1:6);
   end
end
clear i;
if SpamRows > 0
    SpammersMatrix(:,7) = zeros(SpamRows,1);
    for i = SpamRows:-1:1
        if SpammersMatrix(i,2) == 0
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