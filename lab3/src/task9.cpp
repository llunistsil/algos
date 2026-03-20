#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Edge {
    int u, v, w;
};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
    }
    
    vector<long long> dist(n + 1, 0);
    
    for (int i = 0; i < n - 1; i++) {
        bool changed = false;
        for (const auto& e : edges) {
            if (dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
                changed = true;
            }
        }
        if (!changed) break;
    }
    
    bool hasNegativeCycle = false;
    for (const auto& e : edges) {
        if (dist[e.u] + e.w < dist[e.v]) {
            hasNegativeCycle = true;
            break;
        }
    }
    
    cout << (hasNegativeCycle ? 1 : 0) << endl;
    
    return 0;
}
