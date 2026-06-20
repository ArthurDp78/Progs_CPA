#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    int l;

    while (cin >> l && l != 0) {
        int n;
        cin >> n;

        vector<int> cortes(n + 2);

        cortes[0] = 0;
        cortes[n + 1] = l;

        for (int i = 1; i <= n; i++) {
            cin >> cortes[i];
        }

        sort(cortes.begin(), cortes.end());

        int m = n + 2;

        vector<vector<int>> dp(m, vector<int>(m, 0));

        for (int tamanho = 2; tamanho < m; tamanho++) {
            for (int i = 0; i + tamanho < m; i++) {
                int j = i + tamanho;

                dp[i][j] = INT_MAX;

                for (int k = i + 1; k < j; k++) {
                    int custo = dp[i][k] + dp[k][j] + (cortes[j] - cortes[i]);

                    if (custo < dp[i][j]) {
                        dp[i][j] = custo;
                    }
                }
            }
        }

        cout << dp[0][m - 1] << endl;
    }

    return 0;
}