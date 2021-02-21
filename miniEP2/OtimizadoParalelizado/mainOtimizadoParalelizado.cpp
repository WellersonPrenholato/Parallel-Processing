// Para compilar use o seguinte comando:
// g++ -O3 -fopenmp main.cpp -o removeRuido
// Para executar no cluster: qsub -l nodes=1:gpu:ppn=2 -d . miniEP2.sh
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <omp.h>

using namespace std;

typedef struct {
	int altura, largura, threshold;
	unsigned char ***pixel;
} Imagem;

unsigned char*** aloca(int n, int m);

Imagem *readPNM(const char *nomeArquivo);

void salvaPNM(Imagem *img, const char *nomeArquivo);

void removeRuidoMediana( Imagem *img);

int mediana(int a[], int n);

int main(int argc, char *argv[]) {

	if (argc != 4) {
        fprintf(stderr, "usage: prog <in.ppm> <out.ppm> <n>\n");
        exit(1);
    }

    int n = atoi(argv[3]);

    double start_time = omp_get_wtime();

	//Realiza a leitura da imagem
    Imagem *img = readPNM(argv[1]);

	removeRuidoMediana(img);
	for(int i=2; i<=n; i++)
		removeRuidoMediana(img);

	//Salva imagem no arquivo destino
	salvaPNM(img, argv[2]);

	double end_time = omp_get_wtime();
	printf("%s\t%.5lf\n", argv[1], end_time - start_time);

	return 0;
}

// Aloca memoria para uma matriz de dimencoes (N x M x 3)
unsigned char*** aloca(int n, int m) {
    int i, j;
    unsigned char ***M;
    M = (unsigned char***) malloc(n * sizeof(unsigned char**));
    for(i = 0; i < n; i++){
        M[i] = (unsigned char**) malloc(m * sizeof(unsigned char*));
        for(j = 0; j < m; j++){
        	M[i][j] = (unsigned char*) malloc(3 * sizeof(unsigned char)); 
        	M[i][j][0] = 0; //Vermelho
        	M[i][j][1] = 0; //Verde
        	M[i][j][2] = 0; //Azul
        }
    }
    if (!M) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}

    return M;
}

Imagem *readPNM(const char *nomeArquivo) {
	char buff[16];
	Imagem *img;
	FILE *fp;
	int c;
    fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }
    if (!fgets(buff, sizeof(buff), fp)) {
		perror("stdin");
		exit(1);
	}

	if (buff[0] != 'P' || buff[1] != '3') {
		fprintf(stderr, "Formato da imagem invalido (deve ser 'P3')\n");
		exit(1);
	}

	img = (Imagem *) malloc(sizeof(Imagem));
	if (!img) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}

	c = getc(fp);
	while (c == '#') {
		while (getc(fp) != '\n')
			;
		c = getc(fp);
	}

	ungetc(c, fp);
	if (fscanf(fp, "%d %d", &img->largura, &img->altura) != 2) {
		fprintf(stderr, "Tamanho da imagem invalido\n");
		exit(1);
	}

	if (fscanf(fp, "%d", &img->threshold) != 1) {
		fprintf(stderr, "Componente rgb invalido\n");
		exit(1);
	}

	while (fgetc(fp) != '\n')
		;

	img->pixel = aloca(img->altura+2, img->largura+2);

	if (!img) {
		fprintf(stderr, "Erro na alocacao da memoria\n");
		exit(1);
	}
	int r, g, b;
	for(int i = 1; i <= img->altura; i++){
        for(int j = 1; j <= img->largura; j++){
            c = fscanf(fp, "%d %d %d", &r, &g, &b);
            img->pixel[i][j][0] = (unsigned char)r;
            img->pixel[i][j][1] = (unsigned char)g;
            img->pixel[i][j][2] = (unsigned char)b;
        }
    }
    fclose(fp);

	return img;
}

void salvaPNM(Imagem *img, const char *nomeArquivo){
	FILE *arquivo;
	int c, rgb_comp_color;
    arquivo = fopen(nomeArquivo, "w");
    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "#Processamento Paralelo\n");
    fprintf(arquivo, "%d %d %d\n", img->largura, img->altura, img->threshold);
    
	for(int i = 1; i <= img->altura; i++)
      for(int j = 1; j <= img->largura; j++) 
      	for(int k = 0; k < 3; k++)
      		fprintf(arquivo, "%d\n", (int)img->pixel[i][j][k]);
    fclose(arquivo);
}

void removeRuidoMediana( Imagem *img ){

	int i, j, k;
	double r;
	int m[9];

	unsigned char ***copia = aloca(img->altura+2, img->largura+2);
    
	//int copia[img->altura+2][img->largura+2][3];
	for(i=0;i<=img->altura;i++)
        for (k=0; k<3; k++)
            for(j=0;j<=img->largura;j++)
		    	copia[i][j][k] = (int)img->pixel[i][j][k];


	/* Parte principal da imagem */
	#pragma omp parallel shared(copia, img) private(m,i,j,k)
	{
		#pragma omp for
		for(i=2;i<=img->altura-1;i++){
			for (k=0; k<3; k++){
				for(j=2;j<=img->largura-1;j++){
				
					m[0] = copia[i-1][j-1][k];
					m[1] = copia[i-1][j  ][k];
					m[2] = copia[i-1][j+1][k];
					m[3] = copia[i  ][j-1][k];
					m[4] = copia[i  ][j  ][k];
					m[5] = copia[i  ][j+1][k];
					m[6] = copia[i+1][j-1][k];
					m[7] = copia[i+1][j  ][k];
					m[8] = copia[i+1][j+1][k];
					img->pixel[i][j][k] = (unsigned char)mediana(m, 9);
				}
			}
		}

		/* Processa as quatro bordas */
		#pragma omp for
		for(i=2;i<=img->altura-1;i++){
			j = 1;
			for (k=0; k<3; k++){
				m[0] = copia[i-1][j  ][k];
				m[1] = copia[i-1][j+1][k];
				m[2] = copia[i  ][j  ][k];
				m[3] = copia[i  ][j+1][k];
				m[4] = copia[i+1][j  ][k];
				m[5] = copia[i+1][j+1][k];
				img->pixel[i][j][k] = (unsigned char)mediana(m, 6);
			}

			j = img->largura;
			for (k=0; k<3; k++){
				m[0] = copia[i-1][j-1][k];
				m[1] = copia[i-1][j  ][k];
				m[2] = copia[i  ][j-1][k];
				m[3] = copia[i  ][j  ][k];
				m[4] = copia[i+1][j-1][k];
				m[5] = copia[i+1][j  ][k];
				img->pixel[i][j][k] = (unsigned char)mediana(m, 6);
			}
		}

		#pragma omp for
		for(j=2;j<=img->largura-1;j++){
			i = 1;
			for (k=0; k<3; k++){
				m[0] = copia[i  ][j-1][k];
				m[1] = copia[i  ][j  ][k];
				m[2] = copia[i  ][j+1][k];
				m[3] = copia[i+1][j-1][k];
				m[4] = copia[i+1][j  ][k];
				m[5] = copia[i+1][j+1][k];
				img->pixel[i][j][k] = (unsigned char)mediana(m, 6);
			}

			i = img->altura;
			for (k=0; k<3; k++){
				m[0] = copia[i-1][j-1][k];
				m[1] = copia[i-1][j  ][k];
				m[2] = copia[i-1][j+1][k];
				m[3] = copia[i  ][j-1][k];
				m[4] = copia[i  ][j  ][k];
				m[5] = copia[i  ][j+1][k];
				img->pixel[i][j][k] = (unsigned char)mediana(m, 6);
			}
		}
	}

	/* Processa os quatro cantos */
	for (k=0; k<3; k++){
		i = 0; j = 0;
		m[0] = copia[i  ][j][k];
		m[1] = copia[i  ][j+1][k];
		m[2] = copia[i+1][j  ][k];
		m[3] = copia[i+1][j+1][k];
		img->pixel[i][j][k] = (unsigned char)mediana(m, 4);

		i = 0; j = img->largura;
		m[0] = copia[i  ][j][k];
		m[1] = copia[i  ][j-1][k];
		m[2] = copia[i+1][j-1][k];
		m[3] = copia[i+1][j  ][k];
		img->pixel[i][j][k] = (unsigned char)mediana(m, 4);

		i = img->altura; j = 0;
		m[0] = copia[i  ][j][k];
		m[1] = copia[i-1][j  ][k];
		m[2] = copia[i-1][j+1][k];
		m[3] = copia[i  ][j+1][k];
		img->pixel[i][j][k] = (unsigned char)mediana(m, 4);

		i = img->altura; j = img->largura;
		m[0] = copia[i  ][j][k];
		m[1] = copia[i-1][j-1][k];
		m[2] = copia[i-1][j  ][k];
		m[3] = copia[i  ][j-1][k];
		img->pixel[i][j][k] = (unsigned char)mediana(m, 4);
	}
}

int mediana(int a[], int n){
	sort(a, a+n);
	return a[n/2];
}
