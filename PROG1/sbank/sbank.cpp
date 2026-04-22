#include <iostream>
#include <vector>
#include <string>
using namespace std;

string juntarConta(string p1, string p2, string p3, string p4, string p5, string p6) {
    return p1 + p2 + p3 + p4 + p5 + p6;
}

string formatarConta(string conta) {
    return conta.substr(0, 2) + " " +
           conta.substr(2, 8) + " " +
           conta.substr(10, 4) + " " +
           conta.substr(14, 4) + " " +
           conta.substr(18, 4) + " " +
           conta.substr(22, 4);
}

void countingSortPorDigito(vector<string> &contas, int posicao) {
    vector<int> contagem(10, 0);
    vector<string> saida(contas.size());

    for (int i = 0; i < contas.size(); i++) {
        int digito = contas[i][posicao] - '0';
        contagem[digito]++;
    }

    for (int i = 1; i < 10; i++) {
        contagem[i] += contagem[i - 1];
    }

    for (int i = contas.size() - 1; i >= 0; i--) {
        int digito = contas[i][posicao] - '0';
        saida[contagem[digito] - 1] = contas[i];
        contagem[digito]--;
    }

    for (int i = 0; i < contas.size(); i++) {
        contas[i] = saida[i];
    }
}

void radixSort(vector<string> &contas) {
    if (contas.empty()) {
        return;
    }

    int tamanho = contas[0].size();

    for (int posicao = tamanho - 1; posicao >= 0; posicao--) {
        countingSortPorDigito(contas, posicao);
    }
}

void imprimirContasOrdenadas(vector<string> &contas) {
    if (contas.empty()) {
        cout << endl;
        return;
    }

    int repeticoes = 1;

    for (int i = 1; i < contas.size(); i++) {
        if (contas[i] == contas[i - 1]) {
            repeticoes++;
        } else {
            cout << formatarConta(contas[i - 1]) << " " << repeticoes << endl;
            repeticoes = 1;
        }
    }

    cout << formatarConta(contas[contas.size() - 1]) << " " << repeticoes << endl;
    cout << endl;
}

int main() {
    int t;
    cin >> t;

    for (int caso = 0; caso < t; caso++) {
        int n;
        cin >> n;

        vector<string> contas;
        string p1, p2, p3, p4, p5, p6;

        for (int i = 0; i < n; i++) {
            cin >> p1 >> p2 >> p3 >> p4 >> p5 >> p6;
            contas.push_back(juntarConta(p1, p2, p3, p4, p5, p6));
        }

        radixSort(contas);
        imprimirContasOrdenadas(contas);
    }

    return 0;
}