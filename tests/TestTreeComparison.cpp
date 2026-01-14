
#include <vector>

#include "TreeComparison.hpp"
#include "GTestCommon.hpp"


using namespace TreeComparison;

template <typename T>
static void DeleteTree(TreeNode<T>* root) {
  if (!root) return;
  DeleteTree(root->left);
  DeleteTree(root->right);
  delete root;
}

static TreeNode<int>* BuildTreeLevelOrder(const std::vector<int>& vals,
                                          const std::vector<bool>& is_null) {
  // vals.size() must equal is_null.size()
  // is_null[i] == true => node i is null, vals[i] ignored.
  if (vals.empty() || is_null.empty() || vals.size() != is_null.size())
    return nullptr;
  if (is_null[0]) return nullptr;

  std::vector<TreeNode<int>*> nodes(vals.size(), nullptr);
  nodes[0] = new TreeNode<int>(vals[0]);

  for (size_t i = 0; i < vals.size(); ++i) {
    if (is_null[i]) continue;
    if (!nodes[i]) nodes[i] = new TreeNode<int>(vals[i]);

    size_t li = 2 * i + 1;
    size_t ri = 2 * i + 2;

    if (li < vals.size() && !is_null[li]) {
      nodes[li] = new TreeNode<int>(vals[li]);
      nodes[i]->left = nodes[li];
    }
    if (ri < vals.size() && !is_null[ri]) {
      nodes[ri] = new TreeNode<int>(vals[ri]);
      nodes[i]->right = nodes[ri];
    }
  }
  return nodes[0];
}

TEST(SubtreeTest, BasicMatchClassic) {
  // s = [3,4,5,1,2]
  auto* s = new TreeNode<int>(
      3, new TreeNode<int>(4, new TreeNode<int>(1), new TreeNode<int>(2)),
      new TreeNode<int>(5));

  // t = [4,1,2]
  auto* t = new TreeNode<int>(4, new TreeNode<int>(1), new TreeNode<int>(2));

  TreeSolution<int> dfs;
  EXPECT_TRUE(dfs.isSubtree(s, t));
  EXPECT_TRUE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, NotSubtreeDifferentStructure) {
  // s = [3,4,5,1,2,null,null,null,null,0]
  // Build it explicitly to include the extra 0 under node 2.
  auto* s = new TreeNode<int>(
      3,
      new TreeNode<int>(4, new TreeNode<int>(1),
                        new TreeNode<int>(2, new TreeNode<int>(0), nullptr)),
      new TreeNode<int>(5));

  // t = [4,1,2] (no extra 0)
  auto* t = new TreeNode<int>(4, new TreeNode<int>(1), new TreeNode<int>(2));

  TreeSolution<int> dfs;
  EXPECT_FALSE(dfs.isSubtree(s, t));
  EXPECT_FALSE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, SubtreeIsWholeTree) {
  auto* s = new TreeNode<int>(1, new TreeNode<int>(2), new TreeNode<int>(3));

  auto* t = new TreeNode<int>(1, new TreeNode<int>(2), new TreeNode<int>(3));

  TreeSolution<int> dfs;
  EXPECT_TRUE(dfs.isSubtree(s, t));
  EXPECT_TRUE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, SubtreeAtDeepRight) {
  // s:
  //    1
  //     \
  //      2
  //       \
  //        3
  //         \
  //          4
  auto* s = new TreeNode<int>(
      1, nullptr,
      new TreeNode<int>(2, nullptr,
                        new TreeNode<int>(3, nullptr, new TreeNode<int>(4))));

  // t:
  //   3
  //    \
  //     4
  auto* t = new TreeNode<int>(3, nullptr, new TreeNode<int>(4));

  TreeSolution<int> dfs;
  EXPECT_TRUE(dfs.isSubtree(s, t));
  EXPECT_TRUE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, SameValuesButWrongShape) {
  // s:
  //     1
  //    /
  //   2
  //  /
  // 3
  auto* s = new TreeNode<int>(
      1, new TreeNode<int>(2, new TreeNode<int>(3), nullptr), nullptr);

  // t:
  //    2
  //     \
  //      3
  auto* t = new TreeNode<int>(2, nullptr, new TreeNode<int>(3));

  TreeSolution<int> dfs;
  EXPECT_FALSE(dfs.isSubtree(s, t));
  EXPECT_FALSE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, SingleNodeMatch) {
  auto* s = new TreeNode<int>(10, new TreeNode<int>(5), new TreeNode<int>(15));

  auto* t = new TreeNode<int>(15);

  TreeSolution<int> dfs;
  EXPECT_TRUE(dfs.isSubtree(s, t));
  EXPECT_TRUE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, SingleNodeNoMatch) {
  auto* s = new TreeNode<int>(10, new TreeNode<int>(5), new TreeNode<int>(15));

  auto* t = new TreeNode<int>(42);

  TreeSolution<int> dfs;
  EXPECT_FALSE(dfs.isSubtree(s, t));
  EXPECT_FALSE(SubtreeKMP<int>::isSubtree(s, t));

  DeleteTree(s);
  DeleteTree(t);
}

TEST(SubtreeTest, BothImplementationsAgreeOnVariousTrees) {
  // A couple of level-order test cases to cross-check.
  // Case 1:
  // s = [8,3,10,1,6,null,14,null,null,4,7,13]
  // t = [6,4,7]
  {
    // indices: 0..12
    std::vector<int> svals = {8, 3, 10, 1, 6, 0, 14, 0, 0, 4, 7, 13, 0};
    std::vector<bool> snull = {false, false, false, false, false, true, false,
                               true,  true,  false, false, false, true};
    auto* s = BuildTreeLevelOrder(svals, snull);

    auto* t = new TreeNode<int>(6, new TreeNode<int>(4), new TreeNode<int>(7));

    TreeSolution<int> dfs;
    bool a = dfs.isSubtree(s, t);
    bool b = SubtreeKMP<int>::isSubtree(s, t);
    EXPECT_EQ(a, b);
    EXPECT_TRUE(a);

    DeleteTree(s);
    DeleteTree(t);
  }

  // Case 2: t not present
  {
    auto* s = new TreeNode<int>(2, new TreeNode<int>(1), new TreeNode<int>(3));
    auto* t = new TreeNode<int>(1, new TreeNode<int>(3), nullptr);

    TreeSolution<int> dfs;
    bool a = dfs.isSubtree(s, t);
    bool b = SubtreeKMP<int>::isSubtree(s, t);
    EXPECT_EQ(a, b);
    EXPECT_FALSE(a);

    DeleteTree(s);
    DeleteTree(t);
  }
}