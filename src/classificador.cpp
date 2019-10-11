#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

string GetStdoutFromCommand(string cmd) {

    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) 
                data.append(buffer);
        pclose(stream);
    }
    return data;
}


int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Uso: " << argv[0] << " entrada tipo qtd" << endl;
        exit(EXIT_FAILURE);
    }
    
    unsigned qtdExecucoes = stoi(argv[3]);

    string comando, flags;
    string programa;

    if (strcmp(argv[2], "bag") == 0 || strcmp(argv[2], "fila") == 0) {
        comando += "./single ";
    } else {
        comando += "./cpa.exe ";
    }

    comando += "./" + string(argv[1]) + " " + string(argv[2]);

    float somatorio = 0.0f;
    for (unsigned i = 0; i < qtdExecucoes; i++) {
        somatorio += stof(GetStdoutFromCommand(comando));
    }

    cout << float(somatorio / float(qtdExecucoes)) << endl;
    
    return 0;
}
