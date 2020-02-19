#include <iostream>
#include <vector>
#include <unordered_set>
#include <deque>

using std::vector;
using std::pair;
using std::unordered_set;
using std::deque;

void explore(vector<vector<int> > &adj, int start, unordered_set<int>& visited) {
    deque<int> stack;
    stack.push_back(start);
    visited.emplace(start);
    while(stack.size()) {
        int curr_vertex = stack.back();
        stack.pop_back();
        for (auto& adj_vertex : adj[curr_vertex]) {
            if (visited.find(adj_vertex) == visited.end()) {
                visited.emplace(adj_vertex);
                stack.push_back(adj_vertex);
            }
        }
    }
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  unordered_set<int> visited;
  for (int i = 0; i < adj.size(); ++i) {
      if (visited.find(i) == visited.end()) {
          explore(adj, i, visited);
          ++res;
      }
  }
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
