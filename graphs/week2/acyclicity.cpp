#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>

using namespace std;

void move_vert(int v, unordered_set<int>& s, unordered_set<int>& t) {
    s.erase(v);
    t.emplace(v);
}

bool dfs(int curr, vector<vector<int>>& adj, unordered_set<int>& white, unordered_set<int>& grey, unordered_set<int>& black) {
    move_vert(curr, white, grey);
    for (int adj_v : adj[curr]) {
        if (black.find(adj_v) != black.end()) continue;

        if (grey.find(adj_v) != grey.end())
            return true;

        if (dfs(adj_v, adj, white, grey, black))
            return true;
    }
    move_vert(curr, grey, black);
    return false;
}

int acyclic(vector<vector<int> > &adj) {
    unordered_set<int> white;
    unordered_set<int> grey;
    unordered_set<int> black;
    for (size_t i = 0; i < adj.size(); i++)
        white.emplace(i);
    while (!white.empty()) {
        if (dfs(*white.begin(), adj, white, grey, black)) {
            return 1;
        }
    }
    return 0;
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    vector<vector<int> > adj(n, vector<int>());
    for (size_t i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    std::cout << acyclic(adj);
}
