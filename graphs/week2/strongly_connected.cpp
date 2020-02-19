#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int>>& adj, vector<int>& visited, vector<int>& postorder, int x) {
    for (auto& vertex : adj[x]) {
        if (!visited[vertex]) {
            visited[vertex] = 1;
            dfs(adj, visited, postorder, vertex);
        }
    }
    postorder.emplace_back(x);
}

void explore(vector<vector<int>>& adj, vector<int>& visited, int vertex) {
    for (auto v : adj[vertex]) {
        if (!visited[v]) {
            visited[v] = 1;
            explore(adj, visited, v);
        }
    }
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  //write your code here
  vector<vector<int>> reversed {adj.size()};
  for (int i = 0; i < adj.size(); i++) {
      //reversed.emplace_back();
      for (int v : adj[i]) {
          reversed[v].push_back(i);
      }
  }
  vector<int> postorder;
  vector<int> visited;
  visited.resize(adj.size(), 0);
  for (int i = 0; i < adj.size(); i++) {
      if (!visited[i]) {
          visited[i] = 1;
          dfs(reversed, visited, postorder, i);
      }
  }

  int components = 0;

  visited.clear();
  visited.resize(adj.size(), 0);

  for (auto it = postorder.rbegin(); it != postorder.rend(); it++) {
      if (!visited[*it]) {
          visited[*it] = 1;
          explore(adj, visited, *it);
          ++components;
      }
  }

  return components;
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
  std::cout << number_of_strongly_connected_components(adj);
}
