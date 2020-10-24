#!/bin/bash

#*********************************************************************#
# Antes de executar ./job.sh você deve dar perminsão para o arquivo   #
# possa ser executado. Para isso, execute o seginte comando:          #
#              chmod +x job.sh                                        #
#*********************************************************************#

echo
echo start: $(date "+%d/%m/%y %H:%M:%S.%3N")
echo

numeroExecucoes=30

tamanhoVetor="100 1000"
# tamanhoVetor="100 1000 10000"

numThreads="1 6 12 18 24"

for N in $tamanhoVetor
do
	echo "------------------------------------------------"
	echo "N = "$N
	echo "------------------------------------------------"
	for T in $numThreads
	do
		echo "Threads = "$T
		printf "Threads = "$T >>saida$N.txt
		printf "\n["  >>saida$N.txt
		for (( i=1; i<numeroExecucoes; i++ ))
		do
			./pratica5 $T $N >>saida$N.txt
			printf ", "  >>saida$N.txt
		done
		./pratica5 $T $N >>saida$N.txt
		printf "]\n\n" >>saida$N.txt
		echo
	done
	echo
done

echo
echo stop:  $(date "+%d/%m/%y %H:%M:%S.%3N")
echo