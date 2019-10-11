#include <iostream>
#include <list>
#include <fstream>
#include <cstring>
#include <ctime>

#include "graph/graph.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Utilização: " << argv[0] << " INPUT TYPE" << endl;
        cerr << "\t- INPUT: arquivo de mapeamento dos vértices" << endl;
        cerr << "\t- TYPE: tipo de execução a ser realizada. Valores: fila ou bag" << endl;

        exit(EXIT_FAILURE);
    }
    string caminho = argv[1];

    // cout << "Informe o arquivo de entrada: ";
    // cin >> caminho;
    
    ifstream arquivo(caminho);

    if (not arquivo) {
        cerr << "Não foi possível abrir o arquivo!" << endl;
        exit(EXIT_FAILURE);
    }

    unsigned quantidade;
    arquivo >> quantidade;
    string leitura;

    Graph<string> grafo;

    for (unsigned i = 0; i < quantidade; i++) {
        arquivo >> leitura;
        grafo.add(leitura);
    }

    arquivo >> quantidade;

    string leitura2;
    for (unsigned i = 0; i < quantidade; i++) {
        arquivo >> leitura >> leitura2;
        grafo.buildEdge(leitura, leitura2, 1);
    }

    // primeiro elemento
    arquivo >> leitura;

    const clock_t begin_time = clock();

    if (strcmp(argv[2], "fila")) {
        grafo.applySerialBFS(leitura);
    } else if (strcmp(argv[2], "bag")) {
        grafo.applyBFS(leitura);
    }
    cout << fixed;
    cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC;
    // grafo.print();

    return 0;
}

