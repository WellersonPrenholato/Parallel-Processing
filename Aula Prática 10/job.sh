#!/bin/bash
source /opt/intel/inteloneapi/setvars.sh > /dev/null 2>&1

#*********************************************************************#
# Antes de executar ./job.sh você deve dar perminsão para o arquivo   #
# possa ser executado. Para isso, execute o seginte comando:          #
#              chmod +x job.sh                                        #
#*********************************************************************#
#Submeter job: 
#qsub -l nodes=1:gpu:ppn=2 -d . job.sh
#qsub -l nodes=2:gpu:ppn=2 -d . job.sh
#qsub -l nodes=3:gpu:ppn=2 -d . job.sh
#qsub -l nodes=4:gpu:ppn=2 -d . job.sh

echo
echo start: $(date "+%d/%m/%y %H:%M:%S.%3N")
echo

mpirun -np 10 ./programa

echo
echo stop:  $(date "+%d/%m/%y %H:%M:%S.%3N")
echo