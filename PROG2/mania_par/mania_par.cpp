#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    
    int C, V;
    cin >> C >> V;

    vector<vector<pair<int,int>>> adj(2 * C + 1);

    for (int i = 0; i < V; i++) {
        int c1, c2, g;
        cin >> c1 >> c2 >> g;
        adj[c1].push_back({c2 + C, g});
        adj[c2].push_back({c1 + C, g});
        adj[c1 + C].push_back({c2, g});
        adj[c2 + C].push_back({c1, g});
    }

    const int INF = INT_MAX;
    vector<int> dist(2 * C + 1, INF);

    dist[1] = 0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> heap;
    heap.push({0, 1});

    while (!heap.empty()) {
        int custo = heap.top().first;
        int u     = heap.top().second;
        heap.pop();

        if (custo > dist[u]) continue;

        for (int i = 0; i < (int)adj[u].size(); i++) {
            int v = adj[u][i].first;
            int g = adj[u][i].second;
            if (custo + g < dist[v]) {
                dist[v] = custo + g;
                heap.push({dist[v], v});
            }
        }
    }

    int resposta = dist[C];
    cout << (resposta == INF ? -1 : resposta) << "\n";

    return 0;
}