#include <iostream>
#include <vector>
using namespace std;

void maxSubarraySum(vector<int> &arr, int route) {
    int bestSum = arr[0];
    int currentSum = arr[0];

    int bestStart = 0, bestEnd = 0;
    int currentStart = 0;

    for (int i = 1; i < arr.size(); i++) {
        // Decide se continua o segmento atual ou começa um novo
        if (currentSum + arr[i] < arr[i]) {
            currentSum = arr[i];
            currentStart = i;
        } else {
            currentSum += arr[i];
        }

        // Atualiza melhor resposta
        if (currentSum > bestSum) {
            bestSum = currentSum;
            bestStart = currentStart;
            bestEnd = i;
        }
        // Desempate: pega o segmento mais longo
        else if (currentSum == bestSum) {
            if ((i - currentStart) > (bestEnd - bestStart)) {
                bestStart = currentStart;
                bestEnd = i;
            }
        }
    }

    if (bestSum <= 0) {
        cout << "Route " << route << " has no nice parts" << endl;
    } else {
        cout << "The nicest part of route " << route
             << " is between stops " << bestStart + 1
             << " and " << bestEnd + 2 << endl;
    }
}

int main() {
    int b;
    cin >> b;

    if (b >= 1 && b <= 100) {
        for (int i = 0; i < b; i++) {
            int s;
            cin >> s;

            vector<int> v;
            for (int j = 0; j < s - 1; j++) {
                int valor;
                cin >> valor;
                v.push_back(valor);
            }

            maxSubarraySum(v, i + 1);
        }
    }

    return 0;
}