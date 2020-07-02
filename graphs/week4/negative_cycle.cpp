#include <iostream>
#include <vector>
#include <limits>

using std::vector;

#define INF std::numeric_limits<int>::max()

bool relax(vector<long long> &dist, long long cost, int u, int v) {
    if (dist[v] > dist[u] + cost) {
        dist[v] = dist[u] + cost;
        return true;
    }
    return false;
}

int shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    //write your code here
    int N = adj.size();
    vector<long long> distance(N, INF);
    distance[0] = 0;
    for (int k = 0; k < N; ++k) {
        for (int u = 0; u < N; ++u) {
            for (int v = 0; v < adj[u].size(); ++v) {
                if (relax(distance, cost[u][v], u, adj[u][v]) && k == N - 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}


int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    return shortest_paths(adj, cost);
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
