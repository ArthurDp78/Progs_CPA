#include <iostream>
#include <string>
#include <vector>

using namespace std;

int find_award_index(const vector<int>& thresholds, int score, int left, int right) {
    // Busca binaria recursiva para localizar a primeira faixa cujo limite e maior que a pontuacao.
    // Quando left ultrapassa right, left indica exatamente a faixa correta.
    if (left > right) {
        return left;
    }

    // Divide o intervalo atual de busca ao meio.
    int mid = (left + right) / 2;

    // Se a pontuacao for menor que o limite central, a resposta esta na metade esquerda.
    if (score < thresholds[mid]) {
        return find_award_index(thresholds, score, left, mid - 1);
    }

    // Caso contrario, a faixa correta esta da posicao mid para a direita.
    return find_award_index(thresholds, score, mid + 1, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int m;

    if (!(cin >> n >> m)) {
        return 0;
    }

    // Limites que separam uma faixa da outra.
    vector<int> thresholds(n - 1);
    for (int i = 0; i < n - 1; i += 1) {
        cin >> thresholds[i];
    }

    // Premio associado a cada uma das N faixas.
    vector<int> awards(n);
    for (int i = 0; i < n; i += 1) {
        cin >> awards[i];
    }

    // Pontuacoes obtidas pelos M alunos.
    vector<int> scores(m);
    for (int i = 0; i < m; i += 1) {
        cin >> scores[i];
    }

    vector<string> result;
    for (int score : scores) {
        // Descobre em qual faixa a pontuacao do aluno se encaixa.
        int award_index = find_award_index(thresholds, score, 0, static_cast<int>(thresholds.size()) - 1);
        // Usa o indice da faixa para recuperar o premio correspondente.
        result.push_back(to_string(awards[award_index]));
    }

    // Imprime os premios na mesma ordem em que os alunos foram informados.
    for (size_t i = 0; i < result.size(); i += 1) {
        if (i > 0) {
            cout << ' ';
        }
        cout << result[i];
    }

    return 0;
}
