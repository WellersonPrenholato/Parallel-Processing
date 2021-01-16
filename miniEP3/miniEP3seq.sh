#!/bin/bash

#**************************************************************************#
# Antes de executar ./miniEP3seq.sh você deve dar perminsão para o arquivo #
# possa ser executado. Para isso, execute o seginte comando:               #
#              chmod +x miniEP3seq.sh                                      #
#**************************************************************************#
#qsub -l nodes=1:gpu:ppn=2 -d . miniEP3seq.sh

echo
echo start: $(date "+%d/%m/%y %H:%M:%S.%3N")
echo

numeroExecucoes=10

echo "Versão sequencial"
for (( i=1; i<=numeroExecucoes; i++ ))
do
    ./piSeq <in.txt
done

echo
echo stop:  $(date "+%d/%m/%y %H:%M:%S.%3N")
echo