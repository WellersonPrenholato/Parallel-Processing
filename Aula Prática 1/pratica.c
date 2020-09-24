#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

double MyClock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000) + tv.tv_usec;
}

int somaElementos(int **mat, int n){
    int i,j;
    int soma =0;

    for (i=0; i<n; i++){
        for(j=0; j<n; j++){
            soma += mat[i][j];
        }
    }

    return soma;
}

int main(int argc, char *argv[]){                    
    if (argc != 2) {
		fprintf(stderr, "Uso: nomePrograma <N>\n");
		exit(1);
    }
    int N = atoi(argv[1]);

    int i,j;

    int **mat;

    mat = (int**)malloc(N*sizeof(int*));
	for(i=0; i<N;i++){
		mat[i]= (int*)malloc(N*sizeof(int));
		// printf("\n");
		for(j=0; j<N; j++){
            mat[i][j] = 1;
		}
	}

    double inicio = MyClock();

	int soma = somaElementos(mat, N);

	printf("%.10lf\n", (MyClock()-inicio)/CLOCKS_PER_SEC);

    return 0;
}
