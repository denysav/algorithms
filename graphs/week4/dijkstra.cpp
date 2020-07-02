#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <limits>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::unordered_set;
using std::make_pair;

#define INF std::numeric_limits<long long>::max()


int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    auto N = adj.size();
    auto processed = unordered_set<int>(N);
    auto cmp = [](pair<long long, int> x, pair<long long, int> y) {return y.first < x.first;};
    auto queue = priority_queue<pair<long long, int>, vector<pair<long long, int>>, decltype(cmp)>(cmp);
    auto dist = vector<long long>(N, INF);
    dist[s] = 0;
    for (auto i = 0; i < N; ++i) {
        queue.push(make_pair(dist[i], i));
    }
    while(!queue.empty()) {
        auto u = queue.top().second;
        queue.pop();
        if (processed.find(u) != processed.end()) {
            continue;
        }
        processed.emplace(u);
        for (auto i = 0; i < adj[u].size(); ++i) {
            if (dist[u] == INF) break; // corner case: there's no path from source hence break the loop
            auto v = adj[u][i];
            auto d = dist[u] + cost[u][i];
            if (d < dist[v]) {
                dist[v] = d;
                queue.push(make_pair(d, v));
            }
        }
    }
    return dist[t] == INF ? -1: (int) dist[t];
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
    int s, t;
    std::cin >> s >> t;
    s--, t--;
    std::cout << distance(adj, cost, s, t);
}
