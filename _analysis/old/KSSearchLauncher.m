currentDir = cd();
simDirs = dir('sim_*');
fid = fopen('results.txt','w');
fclose(fid);
for x = 1:length(simDirs)
    cd(strcat(simDirs(x).name,'/res'));
    KSSearch;
    cd(currentDir);
    fid=fopen('results.txt','a');
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
    end
    clear i;
    clear j;
    clear r;
    clear c;
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
    end
    clear i;
    clear j;
    clear r;
    clear c;
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
    end
    clear i;
    clear j;
    clear r;
    clear c;
    fclose(fid);
end