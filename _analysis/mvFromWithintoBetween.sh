# Compress results in a tar.gz back up folders 
# Comment this line to present backup archive creation
# tar -cvzf res.tar.gz res
# This file has to be copied into the result folder to re-arrange

# Create Folders
 mkdir sim_01 sim_02 sim_03 sim_04 sim_05 sim_06 sim_07 sim_08 sim_09 sim_10 sim_11 sim_12 sim_13 sim_14 sim_15 sim_16 sim_17 sim_18 sim_19 sim_20

# Create Res Folders 
 mkdir sim_01/res
 mkdir sim_02/res
 mkdir sim_03/res
 mkdir sim_04/res
 mkdir sim_05/res
 mkdir sim_06/res
 mkdir sim_07/res
 mkdir sim_08/res
 mkdir sim_09/res
 mkdir sim_10/res
 mkdir sim_11/res
 mkdir sim_12/res
 mkdir sim_13/res
 mkdir sim_14/res
 mkdir sim_15/res
 mkdir sim_16/res
 mkdir sim_17/res
 mkdir sim_18/res
 mkdir sim_19/res
 mkdir sim_20/res

# Move results
 mv res/*_01_1* sim_01/res/
 mv res/*_02_1* sim_02/res/
 mv res/*_03_1* sim_03/res/
 mv res/*_04_1* sim_04/res/
 mv res/*_05_1* sim_05/res/
 mv res/*_06_1* sim_06/res/
 mv res/*_07_1* sim_07/res/
 mv res/*_08_1* sim_08/res/
 mv res/*_09_1* sim_09/res/
 mv res/*_10_1* sim_10/res/
 mv res/*_11_1* sim_11/res/
 mv res/*_12_1* sim_12/res/
 mv res/*_13_1* sim_13/res/
 mv res/*_14_1* sim_14/res/
 mv res/*_15_1* sim_15/res/
 mv res/*_16_1* sim_16/res/
 mv res/*_17_1* sim_17/res/
 mv res/*_18_1* sim_18/res/
 mv res/*_19_1* sim_19/res/
 mv res/*_20_1* sim_20/res/

# Move remaining files
 cp res/* sim_01/res/ 
 cp res/* sim_02/res/ 
 cp res/* sim_03/res/ 
 cp res/* sim_04/res/ 
 cp res/* sim_05/res/
 cp res/* sim_06/res/
 cp res/* sim_07/res/
 cp res/* sim_08/res/
 cp res/* sim_09/res/
 cp res/* sim_10/res/
 cp res/* sim_11/res/ 
 cp res/* sim_12/res/ 
 cp res/* sim_13/res/ 
 cp res/* sim_14/res/ 
 cp res/* sim_15/res/
 cp res/* sim_16/res/
 cp res/* sim_17/res/
 cp res/* sim_18/res/
 cp res/* sim_19/res/
 cp res/* sim_20/res/

# Copy initial files within the folders
cp ./sim_01/res/acsm2s.conf ./sim_01/
cp ./sim_01/res/_acsinflux.csv ./sim_01/
cp ./sim_01/res/_acsnrgbooleanfunctions.csv ./sim_01/
cp ./sim_01/res/catalysis_00_0_000000000.csv ./sim_01/_acscatalysis.csv
cp ./sim_01/res/species_00_0_000000000.csv ./sim_01/_acsspecies.csv
cp ./sim_01/res/reactions_00_0_000000000.csv ./sim_01/_acsreactions.csv

cp ./sim_02/res/acsm2s.conf ./sim_02/
cp ./sim_02/res/_acsinflux.csv ./sim_02/
cp ./sim_02/res/_acsnrgbooleanfunctions.csv ./sim_02/
cp ./sim_02/res/catalysis_02_1_000000000.csv ./sim_02/_acscatalysis.csv
cp ./sim_02/res/species_02_1_000000000.csv ./sim_02/_acsspecies.csv
cp ./sim_02/res/reactions_02_1_000000000.csv ./sim_02/_acsreactions.csv

cp ./sim_03/res/acsm2s.conf ./sim_03/
cp ./sim_03/res/_acsinflux.csv ./sim_03/
cp ./sim_03/res/_acsnrgbooleanfunctions.csv ./sim_03/
cp ./sim_03/res/catalysis_03_1_000000000.csv ./sim_03/_acscatalysis.csv
cp ./sim_03/res/species_03_1_000000000.csv ./sim_03/_acsspecies.csv
cp ./sim_03/res/reactions_03_1_000000000.csv ./sim_03/_acsreactions.csv

cp ./sim_04/res/acsm2s.conf ./sim_04/
cp ./sim_04/res/_acsinflux.csv ./sim_04/
cp ./sim_04/res/_acsnrgbooleanfunctions.csv ./sim_04/
cp ./sim_04/res/catalysis_04_1_000000000.csv ./sim_04/_acscatalysis.csv
cp ./sim_04/res/species_04_1_000000000.csv ./sim_04/_acsspecies.csv
cp ./sim_04/res/reactions_04_1_000000000.csv ./sim_04/_acsreactions.csv

cp ./sim_05/res/acsm2s.conf ./sim_05/
cp ./sim_05/res/_acsinflux.csv ./sim_05/
cp ./sim_05/res/_acsnrgbooleanfunctions.csv ./sim_05/
cp ./sim_05/res/catalysis_05_1_000000000.csv ./sim_05/_acscatalysis.csv
cp ./sim_05/res/species_05_1_000000000.csv ./sim_05/_acsspecies.csv
cp ./sim_05/res/reactions_05_1_000000000.csv ./sim_05/_acsreactions.csv

cp ./sim_06/res/acsm2s.conf ./sim_06/
cp ./sim_06/res/_acsinflux.csv ./sim_06/
cp ./sim_06/res/_acsnrgbooleanfunctions.csv ./sim_06/
cp ./sim_06/res/catalysis_06_1_000000000.csv ./sim_06/_acscatalysis.csv
cp ./sim_06/res/species_06_1_000000000.csv ./sim_06/_acsspecies.csv
cp ./sim_06/res/reactions_06_1_000000000.csv ./sim_06/_acsreactions.csv

cp ./sim_07/res/acsm2s.conf ./sim_07/
cp ./sim_07/res/_acsinflux.csv ./sim_07/
cp ./sim_07/res/_acsnrgbooleanfunctions.csv ./sim_07/
cp ./sim_07/res/catalysis_07_1_000000000.csv ./sim_07/_acscatalysis.csv
cp ./sim_07/res/species_07_1_000000000.csv ./sim_07/_acsspecies.csv
cp ./sim_07/res/reactions_07_1_000000000.csv ./sim_07/_acsreactions.csv

cp ./sim_08/res/acsm2s.conf ./sim_08/
cp ./sim_08/res/_acsinflux.csv ./sim_08/
cp ./sim_08/res/_acsnrgbooleanfunctions.csv ./sim_08/
cp ./sim_08/res/catalysis_08_1_000000000.csv ./sim_08/_acscatalysis.csv
cp ./sim_08/res/species_08_1_000000000.csv ./sim_08/_acsspecies.csv
cp ./sim_08/res/reactions_08_1_000000000.csv ./sim_08/_acsreactions.csv

cp ./sim_09/res/acsm2s.conf ./sim_09/
cp ./sim_09/res/_acsinflux.csv ./sim_09/
cp ./sim_09/res/_acsnrgbooleanfunctions.csv ./sim_09/
cp ./sim_09/res/catalysis_09_1_000000000.csv ./sim_09/_acscatalysis.csv
cp ./sim_09/res/species_09_1_000000000.csv ./sim_09/_acsspecies.csv
cp ./sim_09/res/reactions_09_1_000000000.csv ./sim_09/_acsreactions.csv

cp ./sim_10/res/acsm2s.conf ./sim_10/
cp ./sim_10/res/_acsinflux.csv ./sim_10/
cp ./sim_10/res/_acsnrgbooleanfunctions.csv ./sim_10/
cp ./sim_10/res/catalysis_10_1_000000000.csv ./sim_10/_acscatalysis.csv
cp ./sim_10/res/species_10_1_000000000.csv ./sim_10/_acsspecies.csv
cp ./sim_10/res/reactions_10_1_000000000.csv ./sim_10/_acsreactions.csv

cp ./sim_11/res/acsm2s.conf ./sim_11/
cp ./sim_11/res/_acsinflux.csv ./sim_11/
cp ./sim_11/res/_acsnrgbooleanfunctions.csv ./sim_11/
cp ./sim_11/res/catalysis_11_1_000000000.csv ./sim_11/_acscatalysis.csv
cp ./sim_11/res/species_11_1_000000000.csv ./sim_11/_acsspecies.csv
cp ./sim_11/res/reactions_11_1_000000000.csv ./sim_11/_acsreactions.csv

cp ./sim_12/res/acsm2s.conf ./sim_12/
cp ./sim_12/res/_acsinflux.csv ./sim_12/
cp ./sim_12/res/_acsnrgbooleanfunctions.csv ./sim_12/
cp ./sim_12/res/catalysis_12_1_000000000.csv ./sim_12/_acscatalysis.csv
cp ./sim_12/res/species_12_1_000000000.csv ./sim_12/_acsspecies.csv
cp ./sim_12/res/reactions_12_1_000000000.csv ./sim_12/_acsreactions.csv

cp ./sim_13/res/acsm2s.conf ./sim_13/
cp ./sim_13/res/_acsinflux.csv ./sim_13/
cp ./sim_13/res/_acsnrgbooleanfunctions.csv ./sim_13/
cp ./sim_13/res/catalysis_12_1_000000000.csv ./sim_13/_acscatalysis.csv
cp ./sim_13/res/species_13_1_000000000.csv ./sim_13/_acsspecies.csv
cp ./sim_13/res/reactions_13_1_000000000.csv ./sim_13/_acsreactions.csv

cp ./sim_14/res/acsm2s.conf ./sim_14/
cp ./sim_14/res/_acsinflux.csv ./sim_14/
cp ./sim_14/res/_acsnrgbooleanfunctions.csv ./sim_14/
cp ./sim_14/res/catalysis_14_1_000000000.csv ./sim_14/_acscatalysis.csv
cp ./sim_14/res/species_14_1_000000000.csv ./sim_14/_acsspecies.csv
cp ./sim_14/res/reactions_14_1_000000000.csv ./sim_14/_acsreactions.csv

cp ./sim_15/res/acsm2s.conf ./sim_15/
cp ./sim_15/res/_acsinflux.csv ./sim_15/
cp ./sim_15/res/_acsnrgbooleanfunctions.csv ./sim_15/
cp ./sim_15/res/catalysis_15_1_000000000.csv ./sim_15/_acscatalysis.csv
cp ./sim_15/res/species_15_1_000000000.csv ./sim_15/_acsspecies.csv
cp ./sim_15/res/reactions_15_1_000000000.csv ./sim_15/_acsreactions.csv

cp ./sim_16/res/acsm2s.conf ./sim_16/
cp ./sim_16/res/_acsinflux.csv ./sim_16/
cp ./sim_16/res/_acsnrgbooleanfunctions.csv ./sim_16/
cp ./sim_16/res/catalysis_16_1_000000000.csv ./sim_16/_acscatalysis.csv
cp ./sim_16/res/species_16_1_000000000.csv ./sim_16/_acsspecies.csv
cp ./sim_16/res/reactions_16_1_000000000.csv ./sim_16/_acsreactions.csv

cp ./sim_17/res/acsm2s.conf ./sim_17/
cp ./sim_17/res/_acsinflux.csv ./sim_17/
cp ./sim_17/res/_acsnrgbooleanfunctions.csv ./sim_17/
cp ./sim_17/res/catalysis_17_1_000000000.csv ./sim_17/_acscatalysis.csv
cp ./sim_17/res/species_17_1_000000000.csv ./sim_17/_acsspecies.csv
cp ./sim_17/res/reactions_17_1_000000000.csv ./sim_17/_acsreactions.csv

cp ./sim_18/res/acsm2s.conf ./sim_18/
cp ./sim_18/res/_acsinflux.csv ./sim_18/
cp ./sim_18/res/_acsnrgbooleanfunctions.csv ./sim_18/
cp ./sim_18/res/catalysis_18_1_000000000.csv ./sim_18/_acscatalysis.csv
cp ./sim_18/res/species_18_1_000000000.csv ./sim_18/_acsspecies.csv
cp ./sim_18/res/reactions_18_1_000000000.csv ./sim_18/_acsreactions.csv

cp ./sim_19/res/acsm2s.conf ./sim_19/
cp ./sim_19/res/_acsinflux.csv ./sim_19/
cp ./sim_19/res/_acsnrgbooleanfunctions.csv ./sim_19/
cp ./sim_19/res/catalysis_19_1_000000000.csv ./sim_19/_acscatalysis.csv
cp ./sim_19/res/species_19_1_000000000.csv ./sim_19/_acsspecies.csv
cp ./sim_19/res/reactions_19_1_000000000.csv ./sim_19/_acsreactions.csv

cp ./sim_20/res/acsm2s.conf ./sim_20/
cp ./sim_20/res/_acsinflux.csv ./sim_20/
cp ./sim_20/res/_acsnrgbooleanfunctions.csv ./sim_20/
cp ./sim_20/res/catalysis_20_1_000000000.csv ./sim_20/_acscatalysis.csv
cp ./sim_20/res/species_20_1_000000000.csv ./sim_20/_acsspecies.csv
cp ./sim_20/res/reactions_20_1_000000000.csv ./sim_20/_acsreactions.csv

#rm ./sim_01/res/species_00_0_000000000.csv
rm ./sim_02/res/species_00_0_000000000.csv
rm ./sim_03/res/species_00_0_000000000.csv
rm ./sim_04/res/species_00_0_000000000.csv
rm ./sim_05/res/species_00_0_000000000.csv
rm ./sim_06/res/species_00_0_000000000.csv
rm ./sim_07/res/species_00_0_000000000.csv
rm ./sim_08/res/species_00_0_000000000.csv
rm ./sim_09/res/species_00_0_000000000.csv
rm ./sim_10/res/species_00_0_000000000.csv
rm ./sim_11/res/species_00_0_000000000.csv
rm ./sim_12/res/species_00_0_000000000.csv
rm ./sim_13/res/species_00_0_000000000.csv
rm ./sim_14/res/species_00_0_000000000.csv
rm ./sim_15/res/species_00_0_000000000.csv
rm ./sim_16/res/species_00_0_000000000.csv
rm ./sim_17/res/species_00_0_000000000.csv
rm ./sim_18/res/species_00_0_000000000.csv
rm ./sim_19/res/species_00_0_000000000.csv
rm ./sim_20/res/species_00_0_000000000.csv

#rm ./sim_01/res/catalysis_00_0_000000000.csv
rm ./sim_02/res/catalysis_00_0_000000000.csv
rm ./sim_03/res/catalysis_00_0_000000000.csv
rm ./sim_04/res/catalysis_00_0_000000000.csv
rm ./sim_05/res/catalysis_00_0_000000000.csv
rm ./sim_06/res/catalysis_00_0_000000000.csv
rm ./sim_07/res/catalysis_00_0_000000000.csv
rm ./sim_08/res/catalysis_00_0_000000000.csv
rm ./sim_09/res/catalysis_00_0_000000000.csv
rm ./sim_10/res/catalysis_00_0_000000000.csv
rm ./sim_11/res/catalysis_00_0_000000000.csv
rm ./sim_12/res/catalysis_00_0_000000000.csv
rm ./sim_13/res/catalysis_00_0_000000000.csv
rm ./sim_14/res/catalysis_00_0_000000000.csv
rm ./sim_15/res/catalysis_00_0_000000000.csv
rm ./sim_16/res/catalysis_00_0_000000000.csv
rm ./sim_17/res/catalysis_00_0_000000000.csv
rm ./sim_18/res/catalysis_00_0_000000000.csv
rm ./sim_19/res/catalysis_00_0_000000000.csv
rm ./sim_20/res/catalysis_00_0_000000000.csv

#rm ./sim_01/res/reactions_00_0_000000000.csv
rm ./sim_01/res/reactions_00_0_000000000.csv
rm ./sim_02/res/reactions_00_0_000000000.csv
rm ./sim_03/res/reactions_00_0_000000000.csv
rm ./sim_04/res/reactions_00_0_000000000.csv
rm ./sim_05/res/reactions_00_0_000000000.csv
rm ./sim_06/res/reactions_00_0_000000000.csv
rm ./sim_07/res/reactions_00_0_000000000.csv
rm ./sim_08/res/reactions_00_0_000000000.csv
rm ./sim_09/res/reactions_00_0_000000000.csv
rm ./sim_10/res/reactions_00_0_000000000.csv
rm ./sim_11/res/reactions_00_0_000000000.csv
rm ./sim_12/res/reactions_00_0_000000000.csv
rm ./sim_13/res/reactions_00_0_000000000.csv
rm ./sim_14/res/reactions_00_0_000000000.csv
rm ./sim_15/res/reactions_00_0_000000000.csv
rm ./sim_16/res/reactions_00_0_000000000.csv
rm ./sim_17/res/reactions_00_0_000000000.csv
rm ./sim_18/res/reactions_00_0_000000000.csv
rm ./sim_19/res/reactions_00_0_000000000.csv
rm ./sim_20/res/reactions_00_0_000000000.csv