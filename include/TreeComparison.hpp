#ifndef TREECOMPARISON_HPP
#define TREECOMPARISON_HPP
/*
Given two non-empty binary trees s and t, check whether tree t has exactly the
same structure and node values with a subtree of s. A subtree of s is a tree
consists of a node in s and all of this node's descendants. The tree s could
also be considered as a subtree of itself.
*/

#include <string>
#include <vector>

namespace TreeComparison {
template <typename T>
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(const T& v) : val(v), left(nullptr), right(nullptr) {}
  TreeNode(const T& v, TreeNode* l, TreeNode* r) : val(v), left(l), right(r) {}
};

template <typename T>
class TreeSolution {
 private:
  bool isSame(TreeNode<T>* a, TreeNode<T>* b) {
    if (!a && !b) return true;
    if (!a || !b) return false;
    if (a->val != b->val) return false;
    return isSame(a->left, b->left) && isSame(a->right, b->right);
  }

 public:
  bool isSubtree(TreeNode<T>* s, TreeNode<T>* t) {
    if (!s) return false;
    if (isSame(s, t)) return true;
    return isSubtree(s->left, t) || isSubtree(s->right, t);
  }
};

template <typename T>
class SubtreeKMP {
 private:
  static std::string toToken(const T& value) {
    std::ostringstream oss;
    oss << value;
    return "^" + oss.str();  // Prefix to avoid ambiguity
  }

  static void serialize(TreeNode<T>* node, std::vector<std::string>& out) {
    if (!node) {
      out.push_back("#");  // null marker (structure-preserving)
      return;
    }
    out.push_back(toToken(node->val));
    serialize(node->left, out);
    serialize(node->right, out);
  }

  static std::vector<int> buildPi(const std::vector<std::string>& pat) {
    std::vector<int> pi(pat.size(), 0);
    int j = 0;
    for (int i = 1; i < (int)pat.size(); ++i) {
      while (j > 0 && pat[i] != pat[j]) j = pi[j - 1];
      if (pat[i] == pat[j]) pi[i] = ++j;
    }
    return pi;
  }

  static bool kmpSearch(const std::vector<std::string>& text,
                        const std::vector<std::string>& pat) {
    if (pat.empty()) return true;
    auto pi = buildPi(pat);
    int j = 0;
    for (int i = 0; i < (int)text.size(); ++i) {
      while (j > 0 && text[i] != pat[j]) j = pi[j - 1];
      if (text[i] == pat[j]) {
        ++j;
        if (j == (int)pat.size()) return true;
      }
    }
    return false;
  }

 public:
  static bool isSubtree(TreeNode<T>* s, TreeNode<T>* t) {
    if (!s || !t) return false;
    std::vector<std::string> sSer, tSer;
    serialize(s, sSer);
    serialize(t, tSer);
    return kmpSearch(sSer, tSer);
  }
};

}  // namespace TreeComparison

#endif  // TREECOMPARISON_HPP
