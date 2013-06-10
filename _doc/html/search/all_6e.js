var searchData=
[
  ['name',['name',['../garbage_search_8m.html#abbf559a76fab59203496b0847ab9502a',1,'garbageSearch.m']]],
  ['names',['names',['../general_concentration_over_threshold_8m.html#a3af72bbca23cfcc45a9043b1036a3c2f',1,'generalConcentrationOverThreshold.m']]],
  ['nargin_3c_201params_2epath_3dcurrentdir_28_29_3bparams_2efigurevisible_3d0_3bendcd_28params_2etmppath_29_3bdisp_28_27_7c_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_7c_27_29_3bdisp_28_27_7c_2dconcentration_20analysis_2e_2e_2e_7c_27_29_3bdisp_28_27_7c_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_2d_7c_27_29_3bif_7eisdir_28_270_5fstatistics_27_29_20mkdir_28_270_5fstatistics_27_29_3bend_25read_20all_20the_20directory_20containing_20simulationssearch_3dstrcat_28_27_2a_27_2c_20params_2esimfolder_2c_27_2a_27_29_3bsimdirs_3ddir_28search_29_3b_25for_20each_20folder_20the_20necessary_20computations_20are_20performedfor_20i_3d1_3alength_28simdirs_29_25go_20into_20the_20results_20folderif_20isdir_28strcat_28simdirs_28i_29_2ename_29_29_20cd_28strcat_28simdirs_28i_29_2ename_2c_27_2fres_27_29_29_3bthissimfolder_3dstrcat_28simdirs_28i_29_2ename_2c_27_2fres_27_29_3b_25read_20configuration_20fileconfparams_3dreadparameters_28_29_3b_25file_20containing_20all_20timestimes_3d0_3aconfparams_2etimestructuressavinginterval_3aconfparams_2enseconds_3bspeciesfiles_3ddir_28_27species_5f_20_2a_27_29_3b_25speciesfiles_3dspeciesfiles_281_3aend_2d1_29_3bto_20comment_20if_20species_5f2_25does_20not_20exist_25speciesfiles_3dspeciesfiles_281_3alength_28speciesfiles_29_2d1_29_3b_25for_20each_20species_20file_2c_20from_20the_20last_20to_20the_20firstnfile_3d1_3b_5bnspeciesfile_2c_20r_5d_3dsize_28speciesfiles_29_3bfor_20j_3dnspeciesfile_3a_2d1_3a1_25from_20villani_20marcofid_3dfopen_28speciesfiles_28j_29_2ename_2c_27r_27_29_3b_25apro_20il_20primo_20filedisp_28sprintf_28_27processing_20dir_25s_2c_20file_25s_2c_25d_2f_25d_27_2c_20simdirs_28i_29_2ename_2c_20speciesfiles_28j_29_2ename_2c_20nspeciesfile_2dj_2c_20nspeciesfile_29_29_3b_25leggo_20gli_20oggetti_20che_20ci_20sono_20in_20ogni_20riga_2dalcuni_20li_20memorizzoindice_3d1_3b_25definisco_20il_20parametro_20di_20controlo_22continua_22while_20indice_20_3e',['nargin&lt; 1params.path=currentDir();params.figureVisible=0;endcd(params.tmpPath);disp(&apos;|--------------------------------|&apos;);disp(&apos;|-Concentration Analysis...|&apos;);disp(&apos;|--------------------------------|&apos;);if~isdir(&apos;0_statistics&apos;) mkdir(&apos;0_statistics&apos;);end%READ ALL THE DIRECTORY CONTAINING SIMULATIONSsearch=strcat(&apos;*&apos;, params.simFolder,&apos;*&apos;);simDirs=dir(search);%For each folder the necessary computations are performedfor i=1:length(simDirs)%Go into the results folderif isdir(strcat(simDirs(i).name)) cd(strcat(simDirs(i).name,&apos;/res&apos;));thisSimFolder=strcat(simDirs(i).name,&apos;/res&apos;);%Read configuration fileconfParams=readParameters();%File Containing all Timestimes=0:confParams.timeStructuresSavingInterval:confParams.nSeconds;speciesFiles=dir(&apos;species_ *&apos;);%speciesFiles=speciesFiles(1:end-1);to comment if species_2%does not exist%speciesFiles=speciesFiles(1:length(speciesFiles)-1);%For each species file, from the last to the firstnFile=1;[nSpeciesFile, r]=size(speciesFiles);for j=nSpeciesFile:-1:1%FROM VILLANI MARCOfid=fopen(speciesFiles(j).name,&apos;r&apos;);%apro il primo filedisp(sprintf(&apos;Processing dir%s, file%s,%d/%d&apos;, simDirs(i).name, speciesFiles(j).name, nSpeciesFile-j, nSpeciesFile));%leggo gli oggetti che ci sono in ogni riga-alcuni li memorizzoindice=1;%definisco il parametro di controlo&quot;continua&quot;while indice &gt;',['../conc_analysis_8m.html#a389644115bfaaa246f363dc22d48bf07',1,'concAnalysis.m']]],
  ['nep',['NEP',['../acs__headers_8h.html#a029d801cdb598a397cb99ea968a64dc2',1,'acs_headers.h']]],
  ['newdir',['newdir',['../namespacebuffered_flux_analysis.html#a90d7a1a691a7ba3f095a06b940e152c9',1,'bufferedFluxAnalysis']]],
  ['newreactions',['NEWREACTIONS',['../acs__headers_8h.html#afb2a947dfb1847f71649f82bc1bf0292',1,'acs_headers.h']]],
  ['newspeciesevaluation',['newSpeciesEvaluation',['../classenvironment.html#aa4b3e51bd7bbb2a287f0963e261cb79b',1,'environment']]],
  ['newspeciesprob',['newSpeciesProb',['../general_concentration_over_threshold_8m.html#aa66147edba72bc0b9cf591cd7475396f',1,'generalConcentrationOverThreshold.m']]],
  ['nfile',['nFile',['../conc_analysis_8m.html#a0df074de7bfa18238647c0c8b555316e',1,'concAnalysis.m']]],
  ['ngen',['nGEN',['../start_8m.html#a4af22ee598eb5fcc4d0ff8439823e600',1,'start.m']]],
  ['noinacs',['noInAcs',['../general_concentration_over_threshold_8m.html#ac45b9c97670e4b4e103ce174dc2db6b3',1,'generalConcentrationOverThreshold.m']]],
  ['nome_5ffolder',['nome_folder',['../start_8m.html#a277bc625a7a558f74ccc1eb2963d70d0',1,'start.m']]],
  ['nome_5fprob',['nome_prob',['../start_8m.html#ab05ea37ca64abe64c55c1f166e3a818b',1,'start.m']]],
  ['notenergizable',['NOTENERGIZABLE',['../acs__headers_8h.html#a04e076b71093a6dc76f99298d9cfeb9e',1,'acs_headers.h']]],
  ['nothingload',['NOTHINGLOAD',['../acs__headers_8h.html#a15e77522039bb4bb52000b65773c83cf',1,'acs_headers.h']]],
  ['notinversereactionalreadycatalyzed',['notInverseReactionAlreadyCatalyzed',['../classenvironment.html#a5160dec152ed0369fe8af9aff3253a9e',1,'environment']]],
  ['nreactions',['nReactions',['../lancia__inizializzatore__acs_8m.html#a7ab8b9fa18f22ee71429cf8ae50d754b',1,'nReactions():&#160;lancia_inizializzatore_acs.m'],['../start_8m.html#a8d704532b4b419f1428cb078bb5c7ffe',1,'nReactions():&#160;start.m']]],
  ['nrg',['nrg',['../general_concentration_over_threshold_8m.html#af837f695e5b67c86016c1a82608c38b4',1,'generalConcentrationOverThreshold.m']]],
  ['nrgtimeseries',['nrgTimeSeries',['../general_concentration_over_threshold_8m.html#ad5f4092827ae220bd7c53532aaaa0590',1,'generalConcentrationOverThreshold.m']]],
  ['nseconds',['nSeconds',['../lancia__inizializzatore__acs_8m.html#aaded2f2d61413dc4bddf805e9be03ded',1,'lancia_inizializzatore_acs.m']]],
  ['nsim',['nSIM',['../lancia__inizializzatore__acs_8m.html#a68c8b36ce2387749248f566faa108e45',1,'nSIM():&#160;lancia_inizializzatore_acs.m'],['../start_8m.html#a2b9b3728c03157895f28160b24f4c572',1,'nSIM():&#160;start.m'],['../start_8m.html#af882a6050e97fe1c6cc2bb391ea57479',1,'Nsim():&#160;start.m']]],
  ['num2str',['num2str',['../start_8m.html#a98a8912cc0fff468250472cd41281c51',1,'start.m']]],
  ['numero_5felementi',['numero_elementi',['../crea__tutte__le__combinazioni__di__elementi_8m.html#a071e4a20ed3694e1603406261e60409a',1,'crea_tutte_le_combinazioni_di_elementi.m']]],
  ['numero_5fmolecole',['numero_molecole',['../crea__concentrazioni__iniziali_8m.html#a88a0f7d52768638928258ed8900a4a30',1,'crea_concentrazioni_iniziali.m']]],
  ['numero_5fspecie',['numero_specie',['../crea__catalizzatori_8m.html#ab5807df6e5701d7529696a19c65fab49',1,'crea_catalizzatori.m']]],
  ['numero_5fspecie_5fda_5ftogliere',['numero_specie_da_togliere',['../crea__catalizzatori_8m.html#ab149f236ebc8e97056dd65cc2eacb67f',1,'crea_catalizzatori.m']]],
  ['numscc',['numScc',['../general_concentration_over_threshold_8m.html#a0d0db21d4520f7561ff56e2c80e4fb69',1,'generalConcentrationOverThreshold.m']]],
  ['numtoconc',['numToConc',['../classspecies.html#a23c19a53390142ba690d0f3db0520d05',1,'species']]],
  ['nutrientsamountsfixing',['nutrientsAmountsFixing',['../classenvironment.html#a9ceec5e00b0f5a51dd125c583b8ac5ec',1,'environment']]],
  ['nzeros',['nZeros',['../general_concentration_over_threshold_8m.html#ac4353d99277795cadf898255e2c73c71',1,'generalConcentrationOverThreshold.m']]]
];
