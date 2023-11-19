#include <iostream>
#include <fstream>

using namespace std;

const int NUM_AVENIDAS = 10;
const int NUM_RUAS = 19;
const int NUM_ANOS = 4;

// Função para inicializar a matriz de acidentes
void inicializarMatriz(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS]) {
    for (int i = 0; i < NUM_AVENIDAS; ++i) {
        for (int j = 0; j < NUM_RUAS; ++j) {
            for (int k = 0; k < NUM_ANOS; ++k) {
                matriz[i][j][k] = 0;
            }
        }
    }
}

// Função para carregar os dados de acidentes a partir de um arquivo TXT
void carregarDados(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS], const char *nomeArquivo) {
    ifstream arquivo(nomeArquivo);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    int avenida, rua, ano, acidentes;

    while (arquivo >> avenida >> rua >> ano >> acidentes) {
        matriz[avenida - 1][rua - 11][ano - 2016] = acidentes;
    }

    arquivo.close();
}

// Função para contar acidentes em uma determinada avenida e ano
int contarAcidentesAvenidaAno(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS], int avenida, int ano) {
    int totalAcidentes = 0;
    for (int i = 0; i < NUM_RUAS; ++i) {
        totalAcidentes += matriz[avenida - 1][i][ano - 2016];
    }
    return totalAcidentes;
}

// Função para contar acidentes em um cruzamento específico
int contarAcidentesCruzamento(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS], int avenida, int rua) {
    int totalAcidentes = 0;
    for (int i = 0; i < NUM_ANOS; ++i) {
        totalAcidentes += matriz[avenida - 1][rua - 11][i];
    }
    return totalAcidentes;
}

// Função para encontrar cruzamentos com mais de 10 acidentes
void cruzamentosMaisDeDezAcidentes(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS]) {
    cout << "Cruzamentos com mais de 10 acidentes:" << endl;
    for (int i = 0; i < NUM_AVENIDAS; ++i) {
        for (int j = 0; j < NUM_RUAS; ++j) {
            int totalAcidentes = 0;
            for (int k = 0; k < NUM_ANOS; ++k) {
                totalAcidentes += matriz[i][j][k];
            }
            if (totalAcidentes > 10) {
                cout << "Avenida " << i + 1 << ", Rua " << j + 11 << ": " << totalAcidentes << " acidentes." << endl;
            }
        }
    }
}

// Função para encontrar o cruzamento mais perigoso
void cruzamentoMaisPerigoso(int matriz[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS]) {
    int maxAcidentes = 0;
    int avenidaMaisPerigosa, ruaMaisPerigosa, anoMaisPerigoso;

    for (int i = 0; i < NUM_AVENIDAS; ++i) {
        for (int j = 0; j < NUM_RUAS; ++j) {
            for (int k = 0; k < NUM_ANOS; ++k) {
                if (matriz[i][j][k] > maxAcidentes) {
                    maxAcidentes = matriz[i][j][k];
                    avenidaMaisPerigosa = i + 1;
                    ruaMaisPerigosa = j + 11;
                    anoMaisPerigoso = k + 2016;
                }
            }
        }
    }

    cout << "Cruzamento mais perigoso: Avenida " << avenidaMaisPerigosa << ", Rua " << ruaMaisPerigosa
         << " no ano " << anoMaisPerigoso << " com " << maxAcidentes << " acidentes." << endl;
}

int main() {
    int matrizAcidentes[NUM_AVENIDAS][NUM_RUAS][NUM_ANOS];
    inicializarMatriz(matrizAcidentes);

    const char *nomeArquivo = "dados_acidentes.txt";
    carregarDados(matrizAcidentes, nomeArquivo);

    char opcao;

    do {
        cout << "\nMenu de Opcoes:" << endl;
        cout << "a) Quantidade de acidentes na avenida X no ano AAAA" << endl;
        cout << "b) Quantidade de acidentes no cruzamento da avenida X com a rua Y" << endl;
        cout << "c) Cruzamentos com mais de 10 acidentes" << endl;
        cout << "d) Cruzamento mais perigoso" << endl;
        cout << "e) Carregar dados de acidentes a partir de arquivo TXT" << endl;
        cout << "s) Sair" << endl;

        cout << "\nEscolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 'a': {
                int avenida, ano;
                cout << "Digite o numero da avenida (1-" << NUM_AVENIDAS << "): ";
                cin >> avenida;
                cout << "Digite o ano (2016-2019): ";
                cin >> ano;
                cout << "Total de acidentes na avenida " << avenida << " no ano " << ano << ": "
                     << contarAcidentesAvenidaAno(matrizAcidentes, avenida, ano) << endl;
                break;
            }
            case 'b': {
                int avenida, rua;
                cout << "Digite o numero da avenida (1-" << NUM_AVENIDAS << "): ";
                cin >> avenida;
                cout << "Digite o numero da rua (11-" << NUM_RUAS + 10 << "): ";
                cin >> rua;
                cout << "Total de acidentes no cruzamento da avenida " << avenida << " com a rua " << rua << ": "
                     << contarAcidentesCruzamento(matrizAcidentes, avenida, rua) << endl;
                break;
            }
            case
