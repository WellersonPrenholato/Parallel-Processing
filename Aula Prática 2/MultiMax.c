#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

int **produto( int linha1, int p, int coluna2, int **v1 ,int **v2){
	int i, j, soma=0, k;
	int **v3;
	v3 = (int**)malloc(linha1*sizeof(int*));
	for(i=0; i<linha1;i++){
		v3[i]= (int*)malloc(coluna2*sizeof(int));
		for(j=0; j<coluna2; j++){
			soma =0;
			for(k=0; k< p; k++){
				soma = soma + v1[i][k] * v2[k][j];
				v3[i][j] = soma;
			}
		}
	}
	return v3;
}

int main(int argc, char *argv[]){                    
    if (argc != 2) {
		fprintf(stderr, "usage: prog <N>\n");
		exit(1);
    }
    int dimensao = atoi(argv[1]);

    /* Cria a matriz */
    // Se tiverem problemas com a declaração estática, mude para a dinâmica 
    int **mat1, **mat2, **mat3;
    int i, j;

    /* Cria e Inicializa a matriz */
    //Chamada da matriz 1
    mat1 = (int**)malloc(dimensao*sizeof(int*));
    for(i=0; i<dimensao;i++){
        mat1[i]= (int*)malloc(dimensao*sizeof(int));
        // printf("\n");
        for(j=0; j<dimensao; j++){
            mat1[i][j] = 1;
            // printf("Matriz %d %d: ", i,j);
			// scanf("%d", &mat1[i][j]);
        }
    }
	
	//Chamada da matriz 2
	mat2 = (int**)malloc(dimensao*sizeof(int*));
	for(i=0; i<dimensao;i++){
		mat2[i]= (int*)malloc(dimensao*sizeof(int));
        // printf("\n");
		for(j=0; j<dimensao; j++){
            mat2[i][j] = 1;
            // printf("Matriz %d %d: ", i,j);
			// scanf("%d", &mat2[i][j]);
		}
	}
    // printf("\n");

    double inicio = MyClock();

    /* Calcula o valor de C = AxB                              */
    /* Implemente a multiplicação das matrizes A e B abaixo    */
    /* se prefirir, pode fazer uma função para fazer o calculo */
    
    /* Parâmetros:
    - Linha da 1º Matriz
    - Coluna da 1º Matriz e Linha da 2º Matriz
    - Coluna da 2º Matriz
    - Matriz 1
    - Matriz 2
    */
    mat3 = produto(dimensao, dimensao, dimensao, mat1, mat2);

    //Impressao Matriz resultado
	// printf("MATRIZ RESULTADO:\n");
	// printf("*** Matriz 3 ***\n");
	// for(i=0; i<dimensao;i++){
	// 	printf("\n");
	// 	for(j=0; j<dimensao; j++){
	// 		printf("%d ", mat3[i][j]);
	// 	}
	// }

    printf("%.15lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC);

    return 0;
}