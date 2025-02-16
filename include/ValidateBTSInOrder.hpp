#ifndef UNIQUEPATHSWITHOBSTACLES_HPP
#define UNIQUEPATHSWITHOBSTACLES_HPP

#include <functional>
#include <limits>
#include <memory>
#include <optional>
#include <type_traits>

template <typename T>
struct TreeNode {
  T val;
  std::unique_ptr<TreeNode> left;
  std::unique_ptr<TreeNode> right;

  TreeNode(T x) : val(x), left(nullptr), right(nullptr) {}
};

template <typename T>
auto CreateNode(T val) -> std::unique_ptr<TreeNode<T>> {
  return std::make_unique<TreeNode<T>>(val);
}

template <typename T>
auto CheckValidBST(const std::unique_ptr<TreeNode<T>>& root, T min, T max) -> bool {
  std::function<bool(const std::unique_ptr<TreeNode<T>>&, T, T)>
      in_order_traversal;
  in_order_traversal = [&](const std::unique_ptr<TreeNode<T>>& node, T min,
                           T max) -> bool {
    if (!node) return true;

    if (node->val <= min || node->val >= max) return false;

    return in_order_traversal(node->left, min, node->val) &&
           in_order_traversal(node->right, node->val, max);
  };
  return in_order_traversal(root, min, max);
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, bool>::type 
IsValidBST(const std::unique_ptr<TreeNode<T>>& root) {
  return CheckValidBST<T>(root, std::numeric_limits<T>::min(),
                       std::numeric_limits<T>::max());
}

template <typename T>
typename std::enable_if<std::is_same<T, std::string>::value, bool>::type
IsValidBST(
    const std::unique_ptr<TreeNode<T>>& root) {
  return CheckValidBST<T>(root, std::string(""), std::string(1, '\xff'));
}

#endif  // UNIQUEPATHSWITHOBSTACLES_HPP