## 🎈 Descrição 
### 📌 Aula Prática 5
Nessa aula prática o intuito foi paralelizar a função preencheVetor do arquivo pratica5.cpp.
Podendo utilizar a biblioteca pthread ou std::thread.

#### 📚 Lembrando que:
<br> pthread é o padrão C
<br> std::thread é o padrão C++

#### 👨🏻‍💻 Para compilar o código:
<br>g++ -o pratica5 -O3 -std=c++11 pratica5.cpp -pthread -lm
ou
<br>icpc -o pratica5 -O3 -std=c++11pratica5.cpp -pthread -lm <em>(Compilador de C++ desenvolvido pela Intel).</em>

Apesar do arquivo ter a extensão cpp e estarmos usando o compilador de C++, o código não contém nada específico de C++. 

#### 💻 Para executar/testar:
./pratica5 <numThreads> <N>

onde, <numThreads> representa o número de threads utilizadas e <N> o tamanho do vetor. 

O arquivo job.sh executa os experimentos com o <b>numThreads = {1, 6, 12, 18, 24}</b> e para <b>N =  {100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}</b>. Para cada par (<N>, <NumThreads>), o programa é executado 30 vezes. 
