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