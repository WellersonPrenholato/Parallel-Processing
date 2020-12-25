/*
# Resources: neednodes=1:gpu:ppn=2,nodes=1:gpu:ppn=2,walltime=06:00:00

start: 09/10/20 17:00:29.842

f(1000000): 224427

stop: 09/10/20 17:03:37.270

time ./programa 1000000
real	3m7.406s
user	3m7.367s
*/

#include <bits/stdc++.h>
 
using namespace std;

#define tamCrivo 1000001

// vector <char> crivo;
char crivo[tamCrivo + 1];

int oitoDivisores(int n) 
{ 
    int total = 1; 
    for (int p = 2; p <= n; p++) { 
        if (crivo[p]) { 
            int count = 0; 
            if (n % p == 0) { 
                while (n % p == 0) { 
                    n = n / p; 
                    count++;
                } 
                total = total * (count + 1);
                if (total > 8){
                    break;
                }
            } 
        } 
    } 

    if (total == 8){
        return n;
    }else{
        return 0;
    }
}
 
int main(int argc, char *argv[]){                    
    if (argc != 2) {
		fprintf(stderr, "usage: prog <N>\n");
		exit(1);
    }

    int N = atoi(argv[1]);

    vector<int> divisores;

    int divisor;

    for (int k=0; k<=tamCrivo; ++k){
        if (k == 0 || k == 1){
            // crivo.push_back(0);
            crivo[k] = 0;
        }else{
            // crivo.push_back(1);
            crivo[k] = 1;
        }
    }

    for (int p = 2; p * p < tamCrivo; p++) 
        if (crivo[p] == 1) 
            for (int i = p * 2; i < tamCrivo; i += p) 
                crivo[i] = 0; 

    for (int i=1; i<=N; ++i){
        divisor = oitoDivisores(i);

        if ( divisor != 0){           
            divisores.push_back(divisor);
            // printf("%d ", divisor);
        }
    }
        printf("\nTamanho: %ld\n", divisores.size());

  return 0;
}