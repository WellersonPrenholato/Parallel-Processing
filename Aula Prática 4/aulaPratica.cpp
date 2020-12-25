/*
# Resources: neednodes=1:gpu:ppn=2,nodes=1:gpu:ppn=2,walltime=06:00:00
start: 08/10/20 16:57:50.885
f(1000000): 224427
stop: 08/10/20 17:09:02.784

time ./programa 1000000
real	11m11.875s
user	11m11.840s
sys	0m0.012s

*/

#include <bits/stdc++.h>
 
using namespace std;


int oitoDivisores (int n){
    int count =0;
    int aux =0;

    for (int i=1; i<=n; ++i){
        if (n % i == 0){
            count++;
            if (count > 8){
                break;
            }
        }
    }

    if (count == 8){
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

    for (int i=1; i<=N; ++i){
        divisor = oitoDivisores(i);

        if ( divisor != 0){           
            divisores.push_back(divisor);
            printf("%d ", divisor);
        }
    }
        printf("\nTamanho: %ld\n", divisores.size());

  return 0;
}