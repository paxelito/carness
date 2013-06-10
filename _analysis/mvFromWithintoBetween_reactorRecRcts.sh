# Compress results in a tar.gz back up folders 
tar -cvzf res.tar.gz res

# Create Folders
 mkdir s_01_01 s_01_02 s_01_03 s_01_04 s_01_05 s_01_06 s_01_07 s_01_08 s_01_09 s_01_10

# Create Res Folders 
 mkdir s_01_01/res
 mkdir s_01_02/res
 mkdir s_01_03/res
 mkdir s_01_04/res
 mkdir s_01_05/res
 mkdir s_01_06/res
 mkdir s_01_07/res
 mkdir s_01_08/res
 mkdir s_01_09/res
 mkdir s_01_10/res

# Move results
 mv res/*_1_01_* s_01_01/res/
 mv res/*_1_02_* s_01_02/res/
 mv res/*_1_03_* s_01_03/res/
 mv res/*_1_04_* s_01_04/res/
 mv res/*_1_05_* s_01_05/res/
 mv res/*_1_06_* s_01_06/res/
 mv res/*_1_07_* s_01_07/res/
 mv res/*_1_08_* s_01_08/res/
 mv res/*_1_09_* s_01_09/res/
 mv res/*_1_10_* s_01_10/res/

# Move overall Results
 mv res/*_1_01.csv s_01_01/res/
 mv res/*_1_02.csv s_01_02/res/
 mv res/*_1_03.csv s_01_03/res/
 mv res/*_1_04.csv s_01_04/res/
 mv res/*_1_05.csv s_01_05/res/
 mv res/*_1_06.csv s_01_06/res/
 mv res/*_1_07.csv s_01_07/res/
 mv res/*_1_08.csv s_01_08/res/
 mv res/*_1_09.csv s_01_09/res/
 mv res/*_1_10.csv s_01_10/res/

# Move Final files
 mv res/*_2_001_* s_01_01/res/
 mv res/*_2_002_* s_01_02/res/
 mv res/*_2_003_* s_01_03/res/
 mv res/*_2_004_* s_01_04/res/
 mv res/*_2_005_* s_01_05/res/
 mv res/*_2_006_* s_01_06/res/
 mv res/*_2_007_* s_01_07/res/
 mv res/*_2_008_* s_01_08/res/
 mv res/*_2_009_* s_01_09/res/
 mv res/*_2_010_* s_01_10/res/

# Move remaining files
 cp res/* s_01_01/res/ 
 cp res/* s_01_02/res/ 
 cp res/* s_01_03/res/ 
 cp res/* s_01_04/res/ 
 cp res/* s_01_05/res/
 cp res/* s_01_06/res/
 cp res/* s_01_07/res/
 cp res/* s_01_08/res/
 cp res/* s_01_09/res/
 cp res/* s_01_10/res/

# Copy initial files within the folders
cp ./s_01_01/res/acsm2s.conf ./s_01_01/
cp ./s_01_01/res/_acsinflux.csv ./s_01_01/
cp ./s_01_01/res/catalysis_0_0_000000000.csv ./s_01_01/_acscatalysis.csv
cp ./s_01_01/res/species_0_0_000000000.csv ./s_01_01/_acsspecies.csv
cp ./s_01_01/res/reactions_0_0_000000000.csv ./s_01_01/_acsreactions.csv

cp ./s_01_02/res/acsm2s.conf ./s_01_02/
cp ./s_01_02/res/_acsinflux.csv ./s_01_02/
cp ./s_01_02/res/catalysis_0_0_000000000.csv ./s_01_02/_acscatalysis.csv
cp ./s_01_02/res/species_0_0_000000000.csv ./s_01_02/_acsspecies.csv
cp ./s_01_02/res/reactions_0_0_000000000.csv ./s_01_02/_acsreactions.csv

cp ./s_01_03/res/acsm2s.conf ./s_01_03/
cp ./s_01_03/res/_acsinflux.csv ./s_01_03/
cp ./s_01_03/res/catalysis_0_0_000000000.csv ./s_01_03/_acscatalysis.csv
cp ./s_01_03/res/species_0_0_000000000.csv ./s_01_03/_acsspecies.csv
cp ./s_01_03/res/reactions_0_0_000000000.csv ./s_01_03/_acsreactions.csv

cp ./s_01_04/res/acsm2s.conf ./s_01_04/
cp ./s_01_04/res/_acsinflux.csv ./s_01_04/
cp ./s_01_04/res/catalysis_0_0_000000000.csv ./s_01_04/_acscatalysis.csv
cp ./s_01_04/res/species_0_0_000000000.csv ./s_01_04/_acsspecies.csv
cp ./s_01_04/res/reactions_0_0_000000000.csv ./s_01_04/_acsreactions.csv

cp ./s_01_05/res/acsm2s.conf ./s_01_05/
cp ./s_01_05/res/_acsinflux.csv ./s_01_05/
cp ./s_01_05/res/catalysis_0_0_000000000.csv ./s_01_05/_acscatalysis.csv
cp ./s_01_05/res/species_0_0_000000000.csv ./s_01_05/_acsspecies.csv
cp ./s_01_05/res/reactions_0_0_000000000.csv ./s_01_05/_acsreactions.csv

cp ./s_01_06/res/acsm2s.conf ./s_01_06/
cp ./s_01_06/res/_acsinflux.csv ./s_01_06/
cp ./s_01_06/res/catalysis_0_0_000000000.csv ./s_01_06/_acscatalysis.csv
cp ./s_01_06/res/species_0_0_000000000.csv ./s_01_06/_acsspecies.csv
cp ./s_01_06/res/reactions_0_0_000000000.csv ./s_01_06/_acsreactions.csv

cp ./s_01_07/res/acsm2s.conf ./s_01_07/
cp ./s_01_07/res/_acsinflux.csv ./s_01_07/
cp ./s_01_07/res/catalysis_0_0_000000000.csv ./s_01_07/_acscatalysis.csv
cp ./s_01_07/res/species_0_0_000000000.csv ./s_01_07/_acsspecies.csv
cp ./s_01_07/res/reactions_0_0_000000000.csv ./s_01_07/_acsreactions.csv

cp ./s_01_08/res/acsm2s.conf ./s_01_08/
cp ./s_01_08/res/_acsinflux.csv ./s_01_08/
cp ./s_01_08/res/catalysis_0_0_000000000.csv ./s_01_08/_acscatalysis.csv
cp ./s_01_08/res/species_0_0_000000000.csv ./s_01_08/_acsspecies.csv
cp ./s_01_08/res/reactions_0_0_000000000.csv ./s_01_08/_acsreactions.csv

cp ./s_01_09/res/acsm2s.conf ./s_01_09/
cp ./s_01_09/res/_acsinflux.csv ./s_01_09/
cp ./s_01_09/res/catalysis_0_0_000000000.csv ./s_01_09/_acscatalysis.csv
cp ./s_01_09/res/species_0_0_000000000.csv ./s_01_09/_acsspecies.csv
cp ./s_01_09/res/reactions_0_0_000000000.csv ./s_01_09/_acsreactions.csv

cp ./s_01_10/res/acsm2s.conf ./s_01_10/
cp ./s_01_10/res/_acsinflux.csv ./s_01_10/
cp ./s_01_10/res/catalysis_0_0_000000000.csv ./s_01_10/_acscatalysis.csv
cp ./s_01_10/res/species_0_0_000000000.csv ./s_01_10/_acsspecies.csv
cp ./s_01_10/res/reactions_0_0_000000000.csv ./s_01_10/_acsreactions.csv