function out = generalConcentrationOverThreshold(params)

% param.threshold               # Theshold above which the concentration has to be 
% param.decayTime               # Reaction decay time
% param.simFolder               # Subtring identifycating the folders containing sims
% param.tmpRctFileToLoad        # Reaction file to load
% param.tmpRctSUBFileToLoad     # Reaction SUB file to load

if nargin < 1
    params.tmpPath = '~/Documents/simChiara/variaK_cpx/K_cpx_05';
    params.threshold = 0;     
    params.decayTime = 100;  
    params.simFolder = 'K_cpx5_rete_n_'; 
    params.tmpRctFileToLoad = '';      
    params.tmpRctSUBFileToLoad = '';
    params.figureVisible = 0;
    params.interval = 10;
end

% Set current date and current directory
currentDate = date();
currentDir = cd();

cd(params.tmpPath);

disp('start analysis...')


if ~isdir('0_statistics')
    mkdir('0_statistics');
end
cd('0_statistics')
% CREATE HEADER ROW IN THE FINAL OUTCOMES FILES
outFilenName = strcat(currentDate, '_' , int2str(params.threshold), '_convOverThreshold_', int2str(params.decayTime), '.csv');
if exist(outFilenName,'file')
    delete(outFilenName);
end
fidFINAL = fopen(outFilenName,'w');
fprintf(fidFINAL,'\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n',...
    'Reaction Probability','Energy Concentration','Tot over Threshold','Real ACSs','in ACSs',...
    'Leaves','by Chain','Overlap','Autocatalysis','in ACSs (W)','Leaves (W)','by Chain (W)','Overlap (W)','Autocatalysis (W)',...
    '[ACS]','[Leaves]','[Chains]','[Self]','Endo Cond','Cond','Endo Cleavage','Cleavage','Wasted species');
fclose(fidFINAL);
cd(params.tmpPath); % Come back to the original folder


% READ ALL THE DIRECTORY CONTAINING SIMULATIONS
search = strcat('*',params.simFolder,'*');
simDirs = dir(search);

% File Containing all Times
%times = 0:params.deltaT:params.totT;


% For each folder the necessary computations are performed
disp('*********************************************************************************');
disp('* NEW SIMULATION ANALYSIS PROCESS');

IDsimFOLDER = 1;

for IDF=1:length(simDirs)
    
    if isdir(strcat(simDirs(IDF).name))
        
        disp(sprintf('|- Processing dir %s',simDirs(IDF).name));
        
        % Go into the results folder
        cd(strcat(simDirs(IDF).name,'/res'));
        
        % Read file conf
        confparams = readParameters();
        
        % Select Times and reactions files       
        speciesFiles = dir('species_1*');
        
        if confparams.energy < 2
            nrg = 1;
        else
            nrg = 0;
        end
     
        % analysisTimeInterval is 1/10 of the total decay time
        analysisTimeInterval = params.interval;
        analysisTimeIntervalNoSave = confparams.nSeconds ./ params.decayTime;
        
        % load incoming flux
        if confparams.influx_rate > 0
            influx = loadInflux()';
        else
            influx = 0:(2^(confparams.maxLOut+1)-3);
        end
        
        % If there are species over theshold network analysis is performed  
        disp('  |- Graph Creation');
        folderCat = strcat('__0_iGraph_CAT_', int2str(params.decayTime));
        folderSub = strcat('__0_iGraph_SUB_', int2str(params.decayTime));
        
        if ~isdir(strcat('../../',folderCat))
            mkdir(strcat('../../',folderCat));
        end
        if ~isdir(strcat('../../',folderSub))
            mkdir(strcat('../../',folderSub));
        end
        
        
        % ID file species counter
        fileSpeciesID = 1;

        % LOAD FIRST SPECIES FILE
        %speciesFiles
        [tmpID, tmpSeq, tmpConc, tmpDiff, tmpSol, tmpCpxDiss, tmpCpxCut, tmpEval, tmpAge, tmpReb, tmpCatID, tmpSubID, tmpKpho, tmpLoadConc, tmpConcFixed]...
            = textread(speciesFiles(length(speciesFiles)).name,'%d %s %f %f %f %f %d %d %f %d %d %d %f %f %d','headerlines',0);
        fileSpeciesID = fileSpeciesID + 1;   
        
        % Compute species over threshold
        IDsOverThreshold = tmpID(and(tmpConc>params.threshold,tmpCpxCut==0));
        concVec = tmpConc;        
        
        % reaction parameters files
        rcsFiles = dir('*reactions_parameters*');   
        
        filextPre = strcat('_',zeroBeforeStrNum(IDsimFOLDER, length(simDirs)),int2str(IDsimFOLDER));
   
        for rfileID=1:length(rcsFiles)
            % read species file
            
            %Initialize reaction type counter
            endo_condensation_counter = 0;
            condensation_counter = 0;
            endo_cleavage_counter = 0;
            cleavage_counter = 0;
            
            disp(strcat('  |- File ', rcsFiles(rfileID).name, ' processing...'));
            
            fid=fopen(rcsFiles(rfileID).name,'r');            %apro il primo file
            
            % initialize useful variables
            previousTime = 0;
            rctIDshow = 1;
            rctIDshowNoSave = 1;
            rctID = 1;
            
            rline = fgetl(fid);
            rlineb = rline;
            rlineID = 1;
            
            % FOR EACH REACTION
            fluxEconomy = 0;
            fluxPlus = 0;
            fluxMinus = 0;
            fluxEconomyArray = [];
            
            while ischar(rlineb)
                if ischar(rlineb)
                    % Format lines
                    if isstrprop(rline(end), 'cntrl'), rline(end) = []; end
                    rline = strread(rline);
                    % Craete different variables
                    reaction = rline(1);
                    rtime = rline(2);
                    cc = rline(3);
                    cat = rline(4);
                    mol_I = rline(5);
                    mol_II = rline(6);
                    mol_III = rline(7);
                    loadedMolsConc = rline(8);
                    loadedMols = rline(9);
                    gillMean = rline(10);
                    gillSD = rline(11);
                    gillEntropy = rline(12);
                    newSpeciesProb = rline(13);
                    ratioBackForward = rline(14);
                end
                
                if nrg == 1
                    nrgTimeSeries(rlineID,:) = [rtime,loadedMolsConc,loadedMols];
                end
                
                gillTimeSeries(rlineID,:) = [rtime,gillMean,gillSD,gillEntropy,newSpeciesProb,ratioBackForward];
                %gillTimeSeries(rlineID,:) = [rtime,gillMean,gillSD,gillEntropy,newSpeciesProb];
                
                printTemporalMessage = 1;
                % If the time is righe save iGraph structures to file
                if (rtime > rctIDshow * analysisTimeInterval)
                    disp(sprintf('     |- %s | Reaction %d - time: %6.4f - Save structures', simDirs(IDF).name, reaction, rtime));
                    saveGraphToFile(folderCat,reaction,rtime,confparams.nReactions,graph,filextPre);
                    saveGraphSUBToFile(folderSub,reaction,rtime,confparams.nReactions,graphSUB,filextPre);
                    rctIDshow = rctIDshow + 1;
                    printTemporalMessage = 0;
                    rctIDshowNoSave = rctIDshowNoSave + 1;
                end
              
                
                % If the prompt time is righe a message on the screen indicating the reaction number and the time is shown
                if and((rtime > rctIDshowNoSave * analysisTimeIntervalNoSave),(printTemporalMessage == 1))
                    msg=sprintf('     |- %s | Reaction %d - time: %6.4f', simDirs(IDF).name, reaction, rtime);disp(msg);
                    rctIDshowNoSave = rctIDshowNoSave + 1;
                end
                
                % update time intervals
                timeInterval = rtime - previousTime;
                previousTime = rtime;
                
                % Increment the time of each reaction present in the system
                % If the time of some reactions overcome the decay time the reaction is removed from the igraph structure
                if rlineID > 1
                    [nRCg,nCCg] = size(graph);
                    [nRSg,nCSg] = size(graphSUB);
                    
                    % CATALYST -> PRODUCT
                    if nRCg > 1
                        graph(:,4) = graph(:,4) + timeInterval;
                        graph(:,5) = graph(:,3) - graph(:,4);
                        graph = graph(graph(:,5)>0,:);
                    end
                    % SUBSTRATE -> PRODUCT
                    if nRSg > 1
                        graphSUB(:,4) = graphSUB(:,4) + timeInterval;
                        graphSUB(:,5) = graphSUB(:,3) - graphSUB(:,4);
                        graphSUB = graphSUB(graphSUB(:,5)>0,:);
                    end
                end
                if (cc == 0) || (cc == 7) % CONDENSATION and ENDO CONDENSATION
                    if cc == 0
                        condensation_counter = condensation_counter + 1;
                    else
                        endo_condensation_counter = endo_condensation_counter + 1;
                    end
                    
                    % INFLUX ECONOMY ANALYSIS
                    if sum(influx == mol_I) >= 1
                        fluxEconomy = fluxEconomy - 1;
                        fluxMinus = fluxMinus + 1;
                    end
                    if sum(influx == mol_II) >= 1
                        fluxEconomy = fluxEconomy + 1;
                        fluxPlus = fluxPlus + 1;
                    end
                    if sum(influx == mol_III) >= 1
                        fluxEconomy = fluxEconomy + 1;
                        fluxPlus = fluxPlus + 1;
                    end
                    
                    if rlineID == 1 % If it is the first reaction nparray (matrix) is created
                        graph       = [cat, mol_I, params.decayTime, 0, params.decayTime, 1];
                        graphSUB    = [mol_II, mol_I, params.decayTime, 0, params.decayTime, 1];
                        if mol_II ~= mol_III
                            graphSUB = [graphSUB;mol_III, mol_I, params.decayTime, 0, params.decayTime, 1]; % Substrate 2 (If different from 1)
                        end
                    else
                        % CAT -> PRO, Otherwise if the reaction is already present its parameters are updated
                        if sum(and((graph(:,1) == cat),graph(:,2) == mol_I)) == 1
                            position = and((graph(:,1) == cat),graph(:,2) == mol_I);
                            graph(position,:) = [cat, mol_I, params.decayTime, 0, params.decayTime, graph(position,6)+1];
                        else
                            % Otherwise a new reaction is added at the end of the matrix
                            graph = [graph;cat, mol_I, params.decayTime, 0, params.decayTime, 1];
                        end
                        
                        % SUB -> PRO, Otherwise if the reaction is already present its parameters are updated
                        if sum(and((graphSUB(:,1) == mol_II),graphSUB(:,2) == mol_I)) == 1
                            position = and((graphSUB(:,1) == mol_II),graphSUB(:,2) == mol_I);
                            graphSUB(position,:) = [mol_II, mol_I, params.decayTime, 0, params.decayTime, graphSUB(position,6)+1];
                        else
                            % Otherwise a new reaction is added at the end of the matrix
                            graphSUB = [graphSUB;mol_II, mol_I, params.decayTime, 0, params.decayTime, 1];
                        end
                        if mol_II ~= mol_III
                            if sum(and((graphSUB(:,1) == mol_III),graphSUB(:,2) == mol_I)) == 1
                                position = and((graphSUB(:,1) == mol_III),graphSUB(:,2) == mol_I);
                                graphSUB(position,:) = [mol_III, mol_I, params.decayTime, 0, params.decayTime, graphSUB(position,6)+1];
                            else
                                graphSUB = [graphSUB;mol_III, mol_I, params.decayTime, 0, params.decayTime, 1];
                            end
                        end
                    end
                else
                    if cc == 6
                        endo_cleavage_counter = endo_cleavage_counter + 1;
                    else
                        cleavage_counter = cleavage_counter + 1;
                    end
                    
                    % INFLUX ECONOMY ANALYSIS
                    if sum(influx == mol_I) >= 1
                        fluxEconomy = fluxEconomy + 1;
                        fluxPlus = fluxPlus + 1;
                    end
                    if sum(influx == mol_II) >= 1
                        fluxEconomy = fluxEconomy - 1;
                        fluxMinus = fluxMinus + 1;
                    end
                    if sum(influx == mol_III) >= 1
                        fluxEconomy = fluxEconomy - 1;
                        fluxMinus = fluxMinus + 1;
                    end
                    
                    if rlineID == 1 % If it is the first reaction nparray (matrix) is created
                        graph       = [cat, mol_II, params.decayTime, 0, params.decayTime, 1];
                        if mol_II ~= mol_III
                            graph = [graph;cat, mol_III, params.decayTime, 0, params.decayTime, 1];
                        end
                        graphSUB = [mol_I, mol_II, params.decayTime, 0, params.decayTime, 1];
                        if mol_II ~= mol_III
                            graphSUB = [graphSUB;mol_I, mol_III, params.decayTime, 0, params.decayTime, 1]; % Substrate 2 (If different from 1)
                        end
                    else
                        % CAT -> PRO, Otherwise if the reaction is already present its parameters are updated
                        if sum(and((graph(:,1) == cat),graph(:,2) == mol_II)) == 1
                            position = and((graph(:,1) == cat),graph(:,2) == mol_II);
                            graph(position,:) = [cat, mol_II, params.decayTime, 0, params.decayTime, graph(position,6)+1];
                        else
                            % Otherwise a new reaction is added at the end of the matrix
                            graph = [graph;cat, mol_II, params.decayTime, 0, params.decayTime, 1];
                        end
                        if mol_II ~= mol_III
                            if sum(and((graph(:,1) == cat),graph(:,2) == mol_III)) == 1
                                position = and((graph(:,1) == cat),graph(:,2) == mol_III);
                                graph(position,:) = [cat, mol_III, params.decayTime, 0, params.decayTime, graph(position,6)+1];
                            else
                                graph = [graph;cat, mol_III, params.decayTime, 0, params.decayTime, 1];
                            end
                        end
                        
                        % SUB -> PRO, Otherwise if the reaction is already present its parameters are updated
                        if sum(and((graphSUB(:,1) == mol_I),graphSUB(:,2) == mol_II)) == 1
                            position = and((graphSUB(:,1) == mol_I),graphSUB(:,2) == mol_II);
                            graphSUB(position,:) = [mol_I, mol_II, params.decayTime, 0, params.decayTime, graphSUB(position,6)+1];
                        else
                            % Otherwise a new reaction is added at the end of the matrix
                            graphSUB = [graphSUB;mol_I, mol_II, params.decayTime, 0, params.decayTime, 1];
                        end
                        if mol_II ~= mol_III
                            if sum(and((graphSUB(:,1) == mol_I),graphSUB(:,2) == mol_III)) == 1
                                position = and((graphSUB(:,1) == mol_I),graphSUB(:,2) == mol_III);
                                graphSUB(position,:) = [mol_I, mol_III, params.decayTime, 0, params.decayTime, graphSUB(position,6)+1];
                            else
                                graphSUB = [graphSUB;mol_I, mol_III, params.decayTime, 0, params.decayTime, 1];
                            end
                        end
                    end
                end
                fluxEconomyArray = [fluxEconomyArray; fluxEconomy, fluxPlus, fluxMinus];
                % Update rlineID
                rlineID = rlineID + 1;
                rline = fgetl(fid);
                rlineb = rline;
                
            end
            fclose(fid);
            
            currentFolder = cd();
            cd('../../0_statistics');
            
            % -----------------------|
            % SAVE GILLESPIE FIGURES |
            % -----------------------|
            
            % Number of 0s to put in front of the sim number in file names
            % (e.g. sim 1 of 10 sims, strZero will be '0' in order to create a
            % file named XXX_01_XXX
            strZero = zeroBeforeStrNum(IDF,length(simDirs));
                        
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(1)
%             end 
%             plot(gillTimeSeries(:,1), gillTimeSeries(:,2), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Gillespie Mean', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('25_gilleMean_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure1= gcf;
%             fileName = strcat('35_gilleMean_',strZero,int2str(IDF),'.fig');
%             saveas(figure1, fileName);
%             
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(2)
%             end 
%             plot(gillTimeSeries(:,1), gillTimeSeries(:,3), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Gillespie SD', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('26_gilleSD_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure2= gcf;
%             fileName = strcat('36_gilleSD_',strZero,int2str(IDF),'.fig');
%             saveas(figure2, fileName);
%             
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(3)
%             end 
%             plot(gillTimeSeries(:,1), gillTimeSeries(:,4), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Entropy', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('27_entropy_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure3= gcf;
%             fileName = strcat('37_entropy_',strZero,int2str(IDF),'.fig');
%             saveas(figure3, fileName);
%             
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(4)
%             end 
%             plot(gillTimeSeries(:,1), gillTimeSeries(:,5), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('New species Probability', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('28_nsp_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure4= gcf;
%             fileName = strcat('38_nsp_',strZero,int2str(IDF),'.fig');
%             saveas(figure4, fileName);
%             
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(5)
%             end 
%             plot(gillTimeSeries(:,1), fluxEconomyArray(:,1), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Flux Molecules Balance', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('29_fluxEconomy_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure5= gcf;
%             fileName = strcat('39_fluxEconomy_',strZero,int2str(IDF),'.fig');
%             saveas(figure5, fileName);
%             
%            if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(6)
%             end 
%             plot(gillTimeSeries(:,1), gillTimeSeries(:,6), 'k-');
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Ratio of backward reactions', 'Interpreter', 'latex', 'fontsize',15);
%             fileName = strcat('30_ratioBackward_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure6= gcf;
%             fileName = strcat('40_ratioBackward_',strZero,int2str(IDF),'.fig');
%             saveas(figure6, fileName);   
%             
%             if params.figureVisible == 0
%                 figure('Visible','off')
%             else
%                 figure(7)
%             end 
%             plot(gillTimeSeries(:,1), fluxEconomyArray(:,2:3));
%             grid on
%             set(gca,'fontsize',15,'fontname','times');
%             xlabel('Time', 'Interpreter', 'latex', 'fontsize',15);
%             ylabel('Flux Molecules', 'Interpreter', 'latex', 'fontsize',15);
%             legend('Added','Removed');
%             fileName = strcat('29_fluxesOverall_',strZero,int2str(IDF),'.eps');
%             eval(['print -depsc ', fileName]);
%             figure7= gcf;
%             fileName = strcat('39_fluxesOverall',strZero,int2str(IDF),'.fig');
%             saveas(figure7, fileName);
%             
%             % SAVE THE GILLESPIE MATRXI ON FILE
%             filename = strcat('0_gillespie_',strZero,int2str(IDF),'.txt');
%             eval(['save ', filename,' gillTimeSeries -ASCII -DOUBLE -TABS']);
%             
%             fluxEconomyMatrix = [gillTimeSeries(:,1), fluxEconomyArray];
%             
%             % SAVE THE GILLESPIE MATRXI ON FILE
%             filename = strcat('0_fluxNet_',strZero,int2str(IDF),'.txt');
%             eval(['save ', filename,' fluxEconomyMatrix -ASCII -DOUBLE -TABS']);
            
            %%%%%%%%%%%%%%%%%%
            % NET ANALYSIS
            %%%%%%%%%%%%%%%%%%
            
            disp('     |- ******* NETWORK ANALYSIS *******');
            disp('      |- Strongly connected components analysis... ');
            
            % Computing actual number od strongly connected components
            from = graph(:,1)+1;
            to = graph(:,2)+1;
            
            prod_inSCC = 0;
            prod_chain = 0;
            prod_bySCC = 0;
            prod_overlap = 0;
            sccID = 0;
            autocatalysis = 0;
            prod_inSCC_weight = 0;
            prod_chain_weight = 0;
            prod_bySCC_weight = 0;
            prod_overlap_weight = 0;
            self_loop_weight = 0;
            conc_inSCC = 0;
            conc_chain = 0;
            conc_bySCC = 0;
            conc_selfCat = 0;
            wasteSpecies = 0;
            
            catSparse = sparse(from,to,true,max(max(from,to)),max(max(from,to)));
            [Nscc,scc] = graphconncomp(catSparse);
            numScc = histc(scc,1:max(scc));
            [self,selfID] = self_loops(graph);
            realSccs = 0;
            for c = 1 : length(numScc)
                if numScc(c) > 1
                    sccID = sccID + 1;
                    disp(sprintf('<> SCC n.%d', c));
                    realSccs = realSccs + 1;
                end
            end
            
            disp(sprintf('          | - Number of ACS: %d', realSccs));
            disp(sprintf('          | - Number of ACS(length 1): %d', self));
            disp(sprintf('          | - Species over threshold: %d', length(IDsOverThreshold)));
            if ~isempty(IDsOverThreshold)
                for idot = 1 : length(IDsOverThreshold)
                    alreadyAdded_ACS = 0;
                    alreadyAdded_leaves = 0;
                    alreadyAdded_chain = 0;
                    tmpProd_chain = 0;
                    incomingNodes = graph(graph(:,2)==IDsOverThreshold(idot),1);
                    tmpProd_chain = tmpProd_chain + length(incomingNodes);
                    tempProd_chain_weight = 0;
                    wasteSpeciesFLAG = 0;
                    if ~isempty(incomingNodes)
                        wasteSpeciesFLAG = 1;
                        for innode = 1 : length(incomingNodes)
                            alreadyAdded_ACS = 0;
                            alreadyAdded_leaves = 0;
                            noInAcs = 1;
                            if realSccs > 0 % If there are ACS
                                for c = 1 : length(numScc) % for each ACS (if present)
                                    if numScc(c) > 1 % IF the ACS contains more than one species
                                        inSCCFlag = 0;
                                        if sum(find(scc==c)==IDsOverThreshold(idot)) % If the species belong to the ACS
                                            inSCCFlag = 1;
                                            if alreadyAdded_ACS == 0 % Add concentration to conc of ACSs
                                                conc_inSCC = conc_inSCC + concVec(idot);
                                                alreadyAdded_ACS = 1;
                                            end
                                        end
                                        % Reactions to distribuite in the
                                        % different nature of the reactions
                                        weightToDistribute = graph(and((graph(:,1) == incomingNodes(innode)),(graph(:,2) == IDsOverThreshold(idot))),6);
                                        if sum(find(scc==c)==incomingNodes(innode)) % If the incoming node is in the ACS
                                            noInAcs = 0;
                                            if inSCCFlag == 1 % If the node is in an ACS, then it has been produced within an ACS
                                                prod_inSCC = prod_inSCC + 1;
                                                tmpProd_chain = tmpProd_chain - 1;
                                                disp(fprintf('\t Within Acs %d -> %d #%d-[%d]%d %6.4f',incomingNodes(innode),IDsOverThreshold(idot),weightToDistribute,...
                                                    IDsOverThreshold(idot),IDsOverThreshold(idot),concVec(idot)));
                                                prod_inSCC_weight = prod_inSCC_weight + weightToDistribute;
                                            else % Otherwise it has been produced by an ACS, so it is a first layer leaf
                                                if alreadyAdded_leaves == 0
                                                    conc_bySCC = conc_bySCC + concVec(idot);
                                                    alreadyAdded_leaves = 1;
                                                end
                                                prod_bySCC = prod_bySCC + 1;
                                                tmpProd_chain = tmpProd_chain - 1;
                                                disp(fprintf('\t From Acs %d -> %d #%d-[%d]%d %6.4f',incomingNodes(innode),IDsOverThreshold(idot),weightToDistribute,...
                                                    IDsOverThreshold(idot),IDsOverThreshold(idot),concVec(idot)));
                                                prod_bySCC_weight = prod_bySCC_weight + weightToDistribute;
                                            end
                                        end
                                    end
                                end
                            end
                            % If both the species over threshold and the
                            % incoming node are not belonging to an ACS
                            if noInAcs == 1
                                prod_chain_weight = prod_chain_weight + graph(and((graph(:,1) == incomingNodes(innode)),(graph(:,2) == IDsOverThreshold(idot))),6);
                                if alreadyAdded_chain == 0
                                    conc_chain = conc_chain + concVec(idot);
                                    alreadyAdded_chain = 1;
                                end
                            end
                        end
                    end
                    if self > 0
                        if sum(selfID==idot) > 0
                            wasteSpeciesFLAG = 1;
                            self_loop_weight =  self_loop_weight + graph(and((graph(:,1) == IDsOverThreshold(idot)),(graph(:,2) == IDsOverThreshold(idot))),6);
                            conc_selfCat = conc_selfCat + concVec(idot);
                            autocatalysis = autocatalysis + 1;
                        end
                    end
                    % If the species concentration > 0 but the species is
                    % not produced by other species, so it is waste
                    if wasteSpeciesFLAG == 0
                        wasteSpecies = wasteSpecies + 1;
                    end
                    
                    % Compute the overlap between the different counter
                    prod_overlap = prod_overlap + min(min([prod_bySCC, prod_inSCC, tmpProd_chain]));
                    prod_chain = prod_chain + tmpProd_chain;
                    prod_overlap_weight = prod_overlap_weight + min(min([prod_inSCC_weight, prod_bySCC_weight, prod_chain_weight]));
                end
            end
            disp(fprintf('\t\t<> Number of Structural Autocatalytic set of molecules: %d', realSccs));
            disp(fprintf('\t\t<> -----------------------------------------------'));
            disp(fprintf('\t\t<> Species over threshold produced by a CHAIN: %d', prod_chain));
            if realSccs > 0
                disp(fprintf('\t\t<> Species over threshold produced INTO an ACS: %d', prod_inSCC));
                disp(fprintf('\t\t<> Species over threshold produced INTO an ACS (weigthed): %d', prod_inSCC_weight));
                disp(fprintf('\t\t<> Species over threshold produced BY an ACS: %d', prod_bySCC));
                disp(fprintf('\t\t<> Species over threshold produced BY an ACS (weigthed): %d', prod_bySCC_weight));
                disp(fprintf('\t\t<> Species over threshold produced by an overlap: %d', prod_overlap));
                disp(fprintf('\t\t<> Species over threshold produced by an overlap (weigthed): %d', prod_overlap_weight));
                disp(fprintf('\t\t<> Species over threshold produced by itself: %d', autocatalysis));
                disp(fprintf('\t\t<> Species over threshold produced by itself (weigthed): %d', self_loop_weight));
                disp(fprintf('\t\t<> Concentration in ACSs: %6.4f', conc_inSCC));
                disp(fprintf('\t\t<> Concentration in ACSs leaves: %6.4f', conc_bySCC));
                disp(fprintf('\t\t<> Concentration in chains: %6.4f', conc_chain));
                disp(fprintf('\t\t<> Concentration of autocatalyst: %6.4f', conc_selfCat));
                disp(fprintf('\t\t<> Number of endo condensations: %6.4f', endo_condensation_counter));
                disp(fprintf('\t\t<> Number of condensations: %6.4f', condensation_counter));
                disp(fprintf('\t\t<> Number of endo cleavages: %6.4f', endo_cleavage_counter));
                disp(fprintf('\t\t<> Number of cleavages: %6.4f', cleavage_counter));
            end
            disp(fprintf('\t\t<> -----------------------------------------------'));
        end
        
        
        fidFINAL = fopen(outFilenName,'a');
        rct = confparams.reactionProbability;
        ecc = confparams.ECConcentration;
        idOt = length(IDsOverThreshold);
        fprintf(fidFINAL,'\n%s\t%6.4f\t%6.4f\t%6.4f\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%6.4f\t%6.4f\t%6.4f\t%6.4f\t%d\t%d\t%d\t%d\t%d',...
            simDirs(IDF).name,rct,ecc,idOt,realSccs,prod_inSCC,prod_bySCC,prod_chain,prod_overlap,autocatalysis,prod_inSCC_weight,...
            prod_bySCC_weight,prod_chain_weight,prod_overlap_weight,self_loop_weight,conc_inSCC,conc_bySCC,conc_chain,conc_selfCat,endo_condensation_counter,...
            condensation_counter,endo_cleavage_counter,cleavage_counter,wasteSpecies);
        fclose(fidFINAL);
        
        clear nrgTimeSeries;
        clear gillTimeSeries;
        
        disp(fprintf('\n ANALYSIS of the SIMULATION %s IS FINISHED\n', simDirs(IDF).name));
        IDsimFOLDER = IDsimFOLDER + 1;
        
        cd(params.tmpPath); % Come back to the original folder
        
    end
end
out = 1;

cd(currentDir);
end




%--------------------------------------------------------------------------------------
% Function to create string zero string vector before graph filename. 
% According to the total number of reactions N zeros will be add before the instant reaction number 
% (e.g. reaction 130 of 10000 the string became '00130')

function strZero = zeroBeforeStrNum(tmpl, tmpL)
    strZero = '';
    nZeros = length(num2str(tmpL)) - length(num2str(tmpl));
    if nZeros > 0
        for p=1:nZeros
            strZero = strcat(strZero,'0');
        end
    end
end


function influx = loadInflux()
    cd('../');     
    [influx,prob] = textread('_acsinflux.csv','%d %f','headerlines',0);  
    cd('./res');
end

function saveGraphToFile(tmpDir,tmpRct,tmprTime,tmpRcts,tmpGraph,tmpFilextPre)
    currentDir = cd();
	cd(strcat('../../',tmpDir));
	tmpStrZeros = zeroBeforeStrNum(tmpRct, tmpRcts);
	outFname = strcat('_iGraph_CAT',tmpFilextPre,'_',tmpStrZeros,num2str(tmpRct),'_',num2str(tmprTime),'.csv');
    if exist(outFname,'file')
        delete(outFname);
    end
    fid1 = fopen(outFname,'a');
    [r,c] = size(tmpGraph);
    for j = 1 : r
        fprintf(fid1,'%d\t%d\t%d\t%6.4f\t%6.4f\t%d\n',tmpGraph(j,1),tmpGraph(j,2),tmpGraph(j,3),tmpGraph(j,4),tmpGraph(j,5),tmpGraph(j,6));
    end
    fclose(fid1);
   cd(currentDir);
end

function saveGraphSUBToFile(tmpDir,tmpRct,tmprTime,tmpRcts,tmpGraph,tmpFilextPre)
    currentDir = cd();
	cd(strcat('../../',tmpDir));
	tmpStrZeros = zeroBeforeStrNum(tmpRct, tmpRcts);
	outFname = strcat('_iGraph_SUB',tmpFilextPre,'_',tmpStrZeros,num2str(tmpRct),'_',num2str(tmprTime),'.csv');
    if exist(outFname,'file')
        delete(outFname);
    end
    fid1 = fopen(outFname,'a');
    [r,c] = size(tmpGraph);
    for j = 1 : r
        fprintf(fid1,'%d\t%d\t%d\t%6.4f\t%6.4f\t%d\n',tmpGraph(j,1),tmpGraph(j,2),tmpGraph(j,3),tmpGraph(j,4),tmpGraph(j,5),tmpGraph(j,6));     
    end
    fclose(fid1);
   cd(currentDir);
end

function [N,ids] = self_loops(graph)
    %Compute self-loop
    N = sum(graph(:,1)==graph(:,2));
    ids = graph(graph(:,1)==graph(:,2),1);
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