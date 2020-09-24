#!/bin/bash

#*********************************************************************#
# Antes de executar ./run.sh você deve dar perminsão para o arquivo   #
# possa ser executado. Para isso, execute o seginte comando:          #
#              chmod +x run.sh                                        #
#*********************************************************************#

numeroExecucoes=30

tamanhoMatriz="500 1000 5000 10000 15000"


for N in $tamanhoMatriz
do
	echo "N = " $N
	for (( i=1; i<=numeroExecucoes; i++ ))
	do
		./pratica $N >>saida$N.txt
	done
	echo ""
	echo ""
done