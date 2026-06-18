#include <stdio.h>
#include <vector>
#include <iostream>
using namespace std;

int mochila(int capacidade, const vector<pair<int,int>>& produtos) {
    vector<int> dp(capacidade + 1, 0);
    for (int i = 0; i < (int)produtos.size(); i++) {
        int preco = produtos[i].first;
        int peso  = produtos[i].second;
        for (int c = capacidade; c >= peso; c--) {
            dp[c] = max(dp[c], dp[c - peso] + preco);
        }
    }
    return dp[capacidade];
}

int main() {

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<pair<int,int>> produtos(N);
        for (int i = 0; i < N; i++)
            cin >> produtos[i].first >> produtos[i].second;

        int G;
        cin >> G;

        int totalGasto = 0;
        for (int i = 0; i < G; i++) {
            int capacidade;
            cin >> capacidade;
            totalGasto += mochila(capacidade, produtos);
        }

        cout << totalGasto << "\n";
    }

    return 0;
}