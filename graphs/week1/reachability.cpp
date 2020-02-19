#include <iostream>
#include <vector>
#include <unordered_set>
#include<deque>

using std::vector;
using std::pair;
using std::unordered_set;
using std::deque;


int reach(vector<vector<int> > &adj, int x, int y) {
  unordered_set<int> visited;
  deque<int> stack;
  stack.push_back(x);
  visited.emplace(x);
  while(stack.size()) {
      int curr_vertex = stack.back();
      stack.pop_back();
      if (curr_vertex == y) {
          return 1;
      }
      for (auto& adj_vertex : adj[curr_vertex]) {
          if (visited.find(adj_vertex) == visited.end()) {
              visited.emplace(adj_vertex);
              stack.push_back(adj_vertex);
          }
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
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}