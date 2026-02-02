#ifndef POST_ORDER_DFS_HPP
#define POST_ORDER_DFS_HPP
/**
 * Post Order DFS Evaluation of Arithmetic Expression Tree
 * Problem:
Suppose an arithmetic expression is given as a binary tree.Each leaf is
    an integer and each internal node is one of '+',
    '−', '∗', or '/'.Given the root to such a tree,
    write a function to evaluate it.
*/

#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

namespace PostOrderDFS {
struct Node {
  std::string val;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> right;

  explicit Node(const std::string& v) : val(v), left(nullptr), right(nullptr) {}
  Node(const std::string& v, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
      : val(v), left(std::move(l)), right(std::move(r)) {}
};

long long Evaluate(const std::unique_ptr<Node>& root) {
  if (!root->left && !root->right) {
    return std::stol(root->val);
  }
  long left_val = Evaluate(root->left);
  long right_val = Evaluate(root->right);
  if (root->val == "+") {
    return left_val + right_val;
  } else if (root->val == "-") {
    return left_val - right_val;
  } else if (root->val == "*") {
    return left_val * right_val;
  } else if (root->val == "/") {
    if (right_val == 0) {
      throw std::invalid_argument("Division by zero");
    }
    return left_val / right_val;
  } else {
    throw std::invalid_argument("Invalid operator: " + root->val);
  }
}
}  // namespace PostOrderDFS

#endif // POST_ORDER_DFS_HPP