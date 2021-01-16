#!/bin/bash

#**************************************************************************#
# Antes de executar ./miniEP3par.sh você deve dar perminsão para o arquivo #
# possa ser executado. Para isso, execute o seginte comando:               #
#              chmod +x miniEP3par.sh                                      #
#**************************************************************************#
#qsub -l nodes=1:gpu:ppn=2 -d . miniEP3par.sh
#qsub -l nodes=2:gpu:ppn=2 -d . miniEP3par.sh

echo
echo start: $(date "+%d/%m/%y %H:%M:%S.%3N")
echo

numeroExecucoes=10

echo "np = 12"
for (( i=1; i<=numeroExecucoes; i++ ))
do
    mpirun -np 12 ./pi <in.txt
done
echo

echo "np = 24"
for (( i=1; i<=numeroExecucoes; i++ ))
do
    mpirun -np 24 ./pi <in.txt
done
echo

echo "np = 48"
for (( i=1; i<=numeroExecucoes; i++ ))
do
    mpirun -np 48 ./pi <in.txt
done


echo
echo stop:  $(date "+%d/%m/%y %H:%M:%S.%3N")
echo