#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;

    while (cin >> n && n != 0) {
        vector<int> qtd(51, 0);
        int maxNivel = 0;

        for (int i = 0; i < n; i++) {
            int l;
            cin >> l;

            qtd[l]++;
            maxNivel = max(maxNivel, l);
        }

        vector<long long> internos;

        long long pesoFolha = 1;
        long long resposta = 0;

        for (int nivel = maxNivel; nivel >= 1; nivel--) {
            vector<long long> atual = internos;

            for (int i = 0; i < qtd[nivel]; i++) {
                atual.push_back(pesoFolha);
                resposta += pesoFolha;
            }

            sort(atual.begin(), atual.end());

            pesoFolha = atual.back();

            internos.clear();

            for (int i = 0; i < (int) atual.size(); i += 2) {
                internos.push_back(atual[i] + atual[i + 1]);
            }
        }

        cout << resposta << endl;
    }

    return 0;
}