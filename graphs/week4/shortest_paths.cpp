#include <iostream>
#include <limits>
#include <vector>

using std::vector;
using std::pair;

#define INF std::numeric_limits<long long>::max()

bool relax(vector<long long> &dist, vector<int> &reachable, int cost, int u, int v) {
    if (dist[u] != INF && dist[v] > dist[u] + cost) {
        reachable[v] = 1;
        dist[v] = dist[u] + cost;
        return true;
    }
    return false;
}

void expand_negative_loop(int vertex, vector<bool> &visited, vector<vector<int> > &adj, vector<int> &shortest) {
    for (int u : adj[vertex]) {
        if (!visited[u] && shortest[u] != 0) {
            visited[u] = true;
            shortest[u] = 0;
            expand_negative_loop(u, visited, adj, shortest);
        }
    }
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
    int N = adj.size();
    distance[s] = 0;
    shortest[s] = 1;
    reachable[s] = 1;
    vector<bool> visited(N, false);
    for (int k = 0; k < N; ++k) {
        for (int u = 0; u < N; ++u) {
            for (int j = 0; j < adj[u].size(); ++j) {
                int v = adj[u][j];
                if (relax(distance, reachable, cost[u][j], u, v) && k == N - 1) {
                    expand_negative_loop(u, visited, adj, shortest);
                    expand_negative_loop(v, visited, adj, shortest);
                }
            }
        }
    }
}

int main() {
    int n, m, s;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    vector<vector<int> > cost(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int x, y, w;
        std::cin >> x >> y >> w;
        adj[x - 1].push_back(y - 1);
        cost[x - 1].push_back(w);
    }
    std::cin >> s;
    s--;
    vector<long long> distance(n, INF);
    vector<int> reachable(n, 0);
    vector<int> shortest(n, 1);
    shortest_paths(adj, cost, s, distance, reachable, shortest);
    for (int i = 0; i < n; i++) {
        if (!reachable[i]) {
            std::cout << "*\n";
        } else if (!shortest[i]) {
            std::cout << "-\n";
        } else {
            std::cout << distance[i] << "\n";
        }
    }
}
