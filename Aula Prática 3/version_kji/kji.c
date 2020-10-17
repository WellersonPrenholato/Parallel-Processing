#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000) + tv.tv_usec;
}

// Considerando uma matriz NxN
void produto( int N, int **v1 ,int **v2, int **v3){
	int i, j, soma=0, k, r=0;
	// v3 = (int**)malloc(N*sizeof(int*));
	for(k=0; k<N;k++){
		// v3[k]= (int*)malloc(N*sizeof(int));
		for(j=0; j<N; j++){
            r = v2[k][j];
			for(i=0; i< N; i++){
				v3[i][j] += v1[i][k] * r;
			}
		}
	}
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

    mat3 = (int**)malloc(dimensao*sizeof(int*));
	for(i=0; i<dimensao;i++){
		mat3[i]= (int*)malloc(dimensao*sizeof(int));
        // printf("\n");
		for(j=0; j<dimensao; j++){
            mat3[i][j] = 0;
            // printf("Matriz %d %d: ", i,j);
			// scanf("%d", &mat3[i][j]);
		}
	}

    double inicio = MyClock();

    /* Calcula o valor de C = AxB                              */
    /* Implemente a multiplicação das matrizes A e B abaixo    */
    /* se prefirir, pode fazer uma função para fazer o calculo */
    
    /* Parâmetros:
    - Dimensão da matriz (supondo que ela é NxN)
    - Matriz 1
    - Matriz 2
    */
    produto(dimensao, mat1, mat2, mat3);

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