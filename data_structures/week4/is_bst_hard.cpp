#include <algorithm>
#include <iostream>
#include <vector>
#include <limits.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool isBST(const vector<Node>& tree, int idx, long long int max, long long int min) {
    if (idx == -1) {
        return true;
    }
    const auto& node = tree[idx];
    if (node.key >= max || node.key < min) {
        return false;
    }
    return isBST(tree, node.left, node.key, min) && isBST(tree, node.right, max, node.key);
}
bool IsBinarySearchTree(const vector<Node>& tree) {
    if (!tree.size()) return true;
    return isBST(tree, 0, LONG_MAX, LONG_MIN);
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
