
# Números primos da forma 2n² − 1

Departamento de Computação e Eletrônica - CEUNES
PRocessamento PaRalelo
Prof. Oberlan Romão

Como sabemos, um número é classificado como primo se ele é maior do que um e é divisível apenas por
um e por ele mesmo. Apenas números naturais são classificados como primos. O dez primeiros números
primos são: 2, 3, 5, 7, 11, 13, 17, 19, 23 e 29.

Existem várias estratégias/algoritmos para verificar se um número é primo ou não. A mais simples
e trivial é verificar se um dado número n possui dois divisores (veja o código abaixo). Claro que essa
estratégia não é a única e nem a mais eficiente.

```c
1   bool ehPrimo(int n) {
2       int numDiv = 0;
3       for (int d = 1; d <= n; d++) {
4           if (n % d == 0)
5               numDiv++;
6       }
7       return numDiv == 2;
8   }
```


Considere os números da forma *t(n) = 2n² − 1* com *n > 1*. Os primeiros números dessa sequencia
são 7, 17, 31, 49, 71, 97, 127 e 161 (veja a tabela abaixo). Desses, apenas 49 = 7 × 7 e 161 = 7 × 23 não são
primos. Para *n ≤ 10.000*, existem 2202 números da sequencia *t(n)* que são primos.


| **n** | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9                       |
| :-- | :-- | :-- | :-- | :-- | :-- | :-- | :-- | :-- |
| *t(n)*      | 7 | 17 | 31 | 49 | 71 | 97 | 127 | 161 |
| *Primo?*      | Sim | Sim | Sim | Não | Sim | Sim | Sim | Não |

***

## Tarefa
Você deve implementar um código paralelo, usando Pthread ou std::thread, que encontre quantos nú-
mero de *t(n)* são primos para *n ≤ N*. Você pode usar qualquer estratégia para verificar se um número
é primo ou não, mas você deve explicar o que fez (use comentários para isso). Caso parte do código seja
baseado de algum artigo/livro/site, deixe isso claro. Seu código deve imprimir apenas a quantidade de
números primos de *t(n)*, para *n ≤ N*, e o tempo gasto em segundos.

Após a implementação (tenha certeza que seu código paralelo está gerando a resposta correta), você
deve fazer alguns experimentos do seu programa no DevCloud da Intel. Nos experimentos, você deve
contabilizar o tempo total (em segundos) do programa considerando os valores de N e número de threads 
mostrados na tabela abaixo. Nesse miniEP, você pode executar apenas uma vez o seu código. Essa tabela
deve ser entregue preenchida.

**Obs.:** Caso o seu programa demore mais que 6h (tempo limite padrão de execução de um job no DevCloud)
para algum valor N e número de threads, o mesmo será encerrado e você não saberá a resposta. Nesse
caso, coloque na célula da tabela o valor >6h.