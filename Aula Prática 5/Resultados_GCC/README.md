## 👨🏻‍💻 Esses resultados foram compilados com:
`g++ -o pratica5 -O3 -std=c++11 pratica5.cpp -pthread -lm`

### 💻 Resultados:
O arquivo job.sh executa os experimentos com o `numThreads = {1, 6, 12, 18, 24}` e para `N = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}`. 
Para cada par `(<N>, <NumThreads>)`, o programa é executado 30 vezes, consequentemente são gerados os arquivos `Saida<N>.txt` que são referentes ao tempo de execução de cada variação.

### 📌 Ambiente de desenvolvimento:
Os algoritmos foram compilados e executados no  Intel ® DevCloud para OneAPI (beta), onde é possível desenvolver, testar e executar suas cargas de trabalho através de uma gama de Intel ® CPUs, GPUs e FPGAs usando software OneAPI.

## 🎈 Description
Intel oneAPI provides a cross-architecture language called Data Parallel C++, with best-in-class compilers, performance libraries, and analysis tools for high-performance heterogeneous code. Learn the essentials of DPC++ here (https://software.seek.intel.com/learn-parallel-programming-dpc-essentials).
We want you to get as much value as possible out of your DevCloud experience, so if you have any technical questions please visit our interactive DevCloud forums (https://software.intel.com/en-us/forums/intel-devcloud)!

It's all about you and your code. We look forward to the innovations you'll create.!

- Your friendly Intel DevCloud Team

Get Started with oneAPI
Below are ways to get started immediately.
1. CONNECT to Intel® DevCloud using a Secure Shell (SSH) client terminal or a Jupyter Lab in your web browser: https://devcloud.intel.com/oneapi/connect
2. RUN your first DPC++ program by executing welcome_dpcpp.sh by typing /data/oneapi/welcome_dpcpp.sh at the command prompt.

Learn More
- Get familiar with Intel® DevCloud commands:  https://devcloud.intel.com/oneapi/learn/
- Watch "What is the Intel® DevCloud for oneAPI?":  https://techdecoded.intel.io/quickhits/what-is-the-intel-devcloud/
- Access oneAPI toolkit Getting Started Guides: https://devcloud.intel.com/oneapi/get-started
- For questions about oneAPI, visit:  https://software.intel.com/en-us/forums/oneAPI
