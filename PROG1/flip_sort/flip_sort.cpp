#include <iostream>
#include <string>
#include <vector>

using namespace std;

long long merge_and_count(vector<int>& arr, vector<int>& temp, int left, int mid, int right) {
    // i percorre a metade esquerda, j a metade direita e k escreve no vetor auxiliar.
    int i = left;
    int j = mid + 1;
    int k = left;
    // Acumula as inversoes encontradas entre as duas metades.
    long long inversions = 0;

    while (i <= mid && j <= right) {
        // Se o elemento da esquerda ja e menor ou igual, ele mantem a ordem.
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i += 1;
        } else {
            // arr[j] e menor que arr[i], entao ele forma inversao com todos
            // os elementos restantes da metade esquerda.
            temp[k] = arr[j];
            inversions += mid - i + 1;
            j += 1;
        }
        k += 1;
    }

    // Copia para o auxiliar os elementos que sobraram da metade esquerda.
    while (i <= mid) {
        temp[k] = arr[i];
        i += 1;
        k += 1;
    }

    // Copia para o auxiliar os elementos que sobraram da metade direita.
    while (j <= right) {
        temp[k] = arr[j];
        j += 1;
        k += 1;
    }

    // Atualiza o trecho original com os elementos agora ordenados.
    for (int idx = left; idx <= right; idx += 1) {
        arr[idx] = temp[idx];
    }

    return inversions;
}

long long merge_sort_and_count(vector<int>& arr, vector<int>& temp, int left, int right) {
    // Um trecho com 0 ou 1 elemento ja esta ordenado.
    if (left >= right) {
        return 0;
    }

    // Divide o intervalo atual em duas metades.
    int mid = (left + right) / 2;

    // Soma as inversoes da esquerda, da direita e do merge.
    long long inversions = merge_sort_and_count(arr, temp, left, mid);
    inversions += merge_sort_and_count(arr, temp, mid + 1, right);
    inversions += merge_and_count(arr, temp, left, mid, right);

    return inversions;
}

long long count_minimum_exchanges(const vector<int>& values) {
    // Vetor vazio nao precisa de nenhuma troca.
    if (values.empty()) {
        return 0;
    }

    // Faz uma copia para preservar a lista original.
    vector<int> arr = values;
    // Vetor auxiliar usado pelo Merge Sort durante as intercalacoes dos vetores.
    vector<int> temp(arr.size(), 0);
    return merge_sort_and_count(arr, temp, 0, static_cast<int>(arr.size()) - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    vector<string> output;

    while (cin >> n) {
        // N igual a zero indica o fim da entrada.
        if (n == 0) {
            break;
        }

        // Le os N valores do caso atual.
        vector<int> values(n);
        for (int i = 0; i < n; i += 1) {
            cin >> values[i];
        }

        // O numero minimo de trocas adjacentes e igual ao numero de inversoes.
        long long exchanges = count_minimum_exchanges(values);
        output.push_back("Minimum exchange operations : " + to_string(exchanges));
    }

    // Imprime uma resposta por linha, no formato pedido pelo enunciado.
    for (size_t i = 0; i < output.size(); i += 1) {
        if (i > 0) {
            cout << '\n';
        }
        cout << output[i];
    }
    cout << "\n";

    return 0;
}
