var a00025 =
[
    [ "Age", "a00025.html#aefba28007767b12696670c7309808dd1", null ],
    [ "angles", "a00025.html#ab0f774a1c2475b84dc2f125473693bc2", null ],
    [ "bindpnt", "a00025.html#abe7c50c8b184b4269ba5aaecedcd5457", null ],
    [ "cd", "a00025.html#a4745c86f44382225b251e3640cb2fe63", null ],
    [ "cd", "a00025.html#a31bfd2803e4b18891d268c6a018db432", null ],
    [ "concentrazione", "a00025.html#a816e2260bf1c36cbca7ade7517c19b07", null ],
    [ "coseno", "a00025.html#a52f1bbbf72ac97a5d451adc330decd0b", null ],
    [ "coss", "a00025.html#aef980037b6271b6ab8be33ae415ef453", null ],
    [ "disp", "a00025.html#a2985ef58c816724bba3cccbf43c4f936", null ],
    [ "evaluated", "a00025.html#a5e1fe2a8074aede6ad4a7a0613f0f91c", null ],
    [ "exist", "a00025.html#ab05bb9470ea34cab3ab1c2c9e748840b", null ],
    [ "fclose", "a00025.html#a210fb0ae3c985ed0d3c1d439a131b48c", null ],
    [ "fclose", "a00025.html#a5e769bbbabcaddc548203741c7100228", null ],
    [ "file", "a00025.html#a10e64101d80ef71182bd7b1250e59135", null ],
    [ "fscanf", "a00025.html#a028ac102a731e62fb0a7439381f566c1", null ],
    [ "if", "a00025.html#adf3394dfd4755fd0ef2854fe558ff8aa", null ],
    [ "if", "a00025.html#ab824f8578204315feac8f0d0c6f25b2c", null ],
    [ "isempty", "a00025.html#ac10445404f4b83302522defb59e25ef7", null ],
    [ "lenghtAnalysis", "a00025.html#a7a3c9de2d82a97c217e41d93905be493", null ],
    [ "lenghtAnalysis", "a00025.html#a3b1ab2e105a6a3b8ed1ee6b0b0f11792", null ],
    [ "overallConcMatrix", "a00025.html#aafaf668a3a1fbcc622062635e470ba72", null ],
    [ "overallConcMatrix", "a00025.html#a91ebfde92d1bf0522290062b808c9e9e", null ],
    [ "overallConcMatrix", "a00025.html#a576dd8edd1b0fd4cc65709a59b308518", null ],
    [ "speciesLENvec", "a00025.html#a63d65c48296edd79c9a2419e091206d0", null ],
    [ "tmpbindpnt", "a00025.html#a00f81a9dbc71b6c82583a1be559f70e2", null ],
    [ "tmpevaluated", "a00025.html#a578805b808d01076403bf6fb9f7f0dab", null ],
    [ "__pad0__", "a00025.html#a1bd174db58293f9130ed98bb375ccc03", null ],
    [ "a", "a00025.html#a230414213a9710ed03b6cf8d2695ee94", null ],
    [ "angles", "a00025.html#aee6c8457aab4cc643bbdaea8794ca74e", null ],
    [ "anglesFromInit", "a00025.html#a860d662b73220f44f28099dfa9d3de76", null ],
    [ "concentrazione", "a00025.html#a5acf1fa9f8d0cb2ab8b1505ffd4dce5b", null ],
    [ "constant", "a00025.html#a163bb0e728c363ddfbd84725ee4bcbf1", null ],
    [ "cossFromInit", "a00025.html#a547b10724f74451f717078739944cc74", null ],
    [ "currentDir", "a00025.html#afb60cd67e28ca8c9fa44e4f5452589b9", null ],
    [ "end", "a00025.html#afb358f48b1646c750fb9da6c6585be2b", null ],
    [ "f", "a00025.html#a9c5a71c46b1abb8b7df5ebeac6c81535", null ],
    [ "fidC", "a00025.html#a5650dbe23ad9065391c1ea56f8acd34c", null ],
    [ "fileConcAllName", "a00025.html#a45b397c4e1bd8e68da97ba6d26fbb41f", null ],
    [ "ftmp", "a00025.html#ad82fa813707dc406b75a0b6e38d45a3e", null ],
    [ "function", "a00025.html#a370f3dd25136a73d619eba0aa2e3bb4b", null ],
    [ "indice", "a00025.html#a776b2bbd08be028d44f6d4260f27633a", null ],
    [ "itmp", "a00025.html#af17812863fb385a507b5b07ed6166569", null ],
    [ "k", "a00025.html#ab7005e24e9bb6ea9b6e14c4ac2614a31", null ],
    [ "nargin< 1params.path=currentDir();params.figureVisible=0;endcd(params.tmpPath);disp('|--------------------------------|');disp('|-Concentration Analysis...|');disp('|--------------------------------|');if~isdir('0_statistics') mkdir('0_statistics');end%READ ALL THE DIRECTORY CONTAINING SIMULATIONSsearch=strcat('*', params.simFolder,'*');simDirs=dir(search);%For each folder the necessary computations are performedfor i=1:length(simDirs)%Go into the results folderif isdir(strcat(simDirs(i).name)) cd(strcat(simDirs(i).name,'/res'));thisSimFolder=strcat(simDirs(i).name,'/res');%Read configuration fileconfParams=readParameters();%File Containing all Timestimes=0:confParams.timeStructuresSavingInterval:confParams.nSeconds;speciesFiles=dir('species_ *');%speciesFiles=speciesFiles(1:end-1);to comment if species_2%does not exist%speciesFiles=speciesFiles(1:length(speciesFiles)-1);%For each species file, from the last to the firstnFile=1;[nSpeciesFile, r]=size(speciesFiles);for j=nSpeciesFile:-1:1%FROM VILLANI MARCOfid=fopen(speciesFiles(j).name,'r');%apro il primo filedisp(sprintf('Processing dir%s, file%s,%d/%d', simDirs(i).name, speciesFiles(j).name, nSpeciesFile-j, nSpeciesFile));%leggo gli oggetti che ci sono in ogni riga-alcuni li memorizzoindice=1;%definisco il parametro di controlo\"continua\"while indice >", "a00025.html#a389644115bfaaa246f363dc22d48bf07", null ],
    [ "nFile", "a00025.html#a0df074de7bfa18238647c0c8b555316e", null ],
    [ "overallConcMatrixEval", "a00025.html#ad9fb43d1f2f660ac0e99cc638e5ac774", null ],
    [ "pause", "a00025.html#afd7d49e17b69bd6bf3d7a649856c1067", null ],
    [ "species", "a00025.html#a0e465545a27eaf9ca2c9710f744963c4", null ],
    [ "speciesLENvec", "a00025.html#a728fdfd72d1bd5110134afd6e09e99da", null ],
    [ "strZero", "a00025.html#ab253e75f6224bf843e7a5ff2fb472e7d", null ],
    [ "tmpbindpnt", "a00025.html#a5767512ebb74a4931fc7193b57426f9f", null ],
    [ "tmpcos", "a00025.html#ab6beb59ba238329bfb9d4ed5a5486c5e", null ],
    [ "tmpevaluated", "a00025.html#a4e591f841c52d48a504874598be0542a", null ],
    [ "tmpspecie", "a00025.html#a045ecd9b02a87529b837dde223b08719", null ]
];