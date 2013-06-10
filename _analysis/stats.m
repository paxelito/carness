function stats()

% clear all 
% close all
% 
% params.path = '~/Documents/lavoro/panini/reactionIN2';
% params.deltaT = 10;
% params.totT = 1000;
% params.showFig = 0;
% params.totT = 1000;
% params.deltaT = 10;   
% 
% concAnalysis(params)
% clear all 
% close all
% 
% params.path = '~/Documents/lavoro/panini/reactionIN3';
% params.deltaT = 10;
% params.totT = 1000;
% params.showFig = 0;
% params.totT = 1000;
% params.deltaT = 10;   
% 
% concAnalysis(params)
% 
% clear all 
% close all
% 
% params.path = '~/Documents/lavoro/panini/reactionIN4';
% params.deltaT = 10;
% params.totT = 1000;
% params.showFig = 0;
% params.totT = 1000;
% params.deltaT = 10;
% 
% 
% concAnalysis(params)

% clear all
% close all
% tmpPath = '~/Documents/lavoro/panini/reactionIN2';
% [out] = timesAnalysis(tmpPath)
% 
% clear all
% close all
% tmpPath = '~/Documents/lavoro/panini/reactionIN3';
% [out] = timesAnalysis(tmpPath)
% 
% clear all
% close all
% tmpPath = '~/Documents/lavoro/panini/reactionIN4';
% [out] = timesAnalysis(tmpPath)

% clear all
% close all
% params.tmpPath = '~/Documents/lavoro/panini/reactionIN2';
% params.figureVisible = 0;
% params.deltaT =10;
% params.totT = 1000;
% %[outa] = allTimesAnalysis(params)
% 
% clear all
% close all
% params.tmpPath = '~/Documents/lavoro/panini/reactionIN3';
% params.figureVisible = 0;
% params.deltaT =10;
% params.totT = 1000;
% [outb] = allTimesAnalysis(params)
% 
% clear all
% close all
% params.tmpPath = '~/Documents/lavoro/panini/reactionIN4';
% params.figureVisible = 0;
% params.deltaT =10;
% params.totT = 1000;
% [outc] = allTimesAnalysis(params)

close all
clear all

params.tmpPath = '~/Documents/simPanini/oldSimsReactor/panini/reactionIN4/';
params.showFig = 0;
params.threshold = 0;     
params.decayTime = 10;  
params.tmpResFold = 'res';     
params.distinctiveSubStr = 'sim'; 
params.tmpIDsim = '5';
params.tmpRctFileToLoad = '';      
params.tmpRctSUBFileToLoad = '';
out = generalConcentrationOverThreshold(params)

end