function overallStats()

close all
clear all

p.tmpAnalysis = [0 0 0 1 0 1 0];
p.tmpPath = '/Users/alessandrofilisetti/Documents/results/VILLANI/';
p.figureVisible = 0;
p.simFolder = 'ACS2';
p.lastSpecies = 2; % Used in KillSpan analysis, it represents the last influx species

% LATEST FILES ANALYSIS
if p.tmpAnalysis(1) == 1
    timesAnalysis(p);
end

if p.tmpAnalysis(2) == 1
    garbageSearch(p);
end

if p.tmpAnalysis(3) == 1
    KillSpam(p);
end

if p.tmpAnalysis(4) == 1
    concAnalysis(p)
end

if p.tmpAnalysis(5) == 1
    allTimesAnalysis(p)
end

p.decayTime = 10; 
if p.tmpAnalysis(6) == 1
    p.interval = 10;
    p.threshold = 0;       
    p.tmpRctFileToLoad = '';      
    p.tmpRctSUBFileToLoad = '';
    generalConcentrationOverThreshold(p)
end

% Need p.tmpAnalysis(6) in order to be performed
if p.tmpAnalysis(7) == 1
    % Using an R-Cran script this part is a little bit different
    crtDir = cd();
    if exist('MATLAB2R.Rout','file')
       delete('MATLAB2R.Rout');
    end 
    scriptAnalDir = cd();
    gfs = strcat('_',num2str(p.decayTime));
    eval(['! R CMD BATCH --no-save --no-restore --slave "--args sf=''',scriptAnalDir,''' ls=',num2str(p.lastSpecies),...
        ' sss=''',p.simFolder,''' gfs=''',gfs,''' sd=''',p.tmpPath,'''" MATLAB2R.R']);
    cd(crtDir);
end

close all
clear all


end