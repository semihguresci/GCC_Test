#include "GTestCommon.hpp"
#include "ValidateBTSInOrder.hpp"

TEST(ValidateBTSInOrder, Empty) {
  std::unique_ptr<TreeNode<int>> root = nullptr;
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, SingleNode) {
  auto root = CreateNode(1);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, ValidBST) {
  auto root = CreateNode(2);
  root->left = CreateNode(1);
  root->right = CreateNode(3);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, InvalidBST) {
  auto root = CreateNode(5);
  root->left = CreateNode(1);
  root->right = CreateNode(4);
  root->right->left = CreateNode(3);
  root->right->right = CreateNode(6);

  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, DublicateLeftInvalidBST) {
  auto root = CreateNode(2);
  root->left = CreateNode(2);
  root->right = CreateNode(3);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, DublicateRightInvalidBST) {
  auto root = CreateNode(2);
  root->left = CreateNode(1);
  root->right = CreateNode(2);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, ComplexValidBST) {
  auto root = CreateNode(10);
  root->left = CreateNode(5);
  root->left->left = CreateNode(2);
  root->left->right = CreateNode(7);

  root->right = CreateNode(15);
  root->right->left = CreateNode(12);
  root->right->right = CreateNode(20);

  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, ComplexInvalidBST) {
  auto root = CreateNode(10);
  root->left = CreateNode(5);
  root->left->left = CreateNode(2);
  root->left->right = CreateNode(7);

  root->right = CreateNode(15);
  root->right->left = CreateNode(9);
  root->right->right = CreateNode(20);

  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, NagativeValuesBST) {
  auto root = CreateNode(-10);
  root->left = CreateNode(-20);
  root->right = CreateNode(0);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, InvalidNagativeValuesBST) {
  auto root = CreateNode(-10);
  root->left = CreateNode(0);
  root->right = CreateNode(-20);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, LargeValuesBST) {
  auto root = CreateNode(1000000000);
  root->left = CreateNode(1000000000 - 1);
  root->right = CreateNode(1000000000 + 1);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, InvalidLargeValuesBST) {
  auto root = CreateNode(1000000000);
  root->left = CreateNode(1000000000 + 1);
  root->right = CreateNode(1000000000 - 1);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, FloatingPoint) {
  auto root = CreateNode<double>(10.5);
  root->left = CreateNode<double>(5.5);
  root->right = CreateNode<double>(20.6);
  auto result = IsValidBST(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, InvalidFloatingPoint) {
  auto root = CreateNode<double>(10.5);
  root->left = CreateNode<double>(50.5);
  root->right = CreateNode<double>(20.6);
  auto result = IsValidBST<double>(root);
  EXPECT_EQ(result, false);
}

TEST(ValidateBTSInOrder, Text) {
  auto root = CreateNode<std::string>("Dog");
  root->left = CreateNode<std::string>("Cat");
  root->right = CreateNode<std::string>("Elephant");
  auto result = IsValidBST<std::string>(root);
  EXPECT_EQ(result, true);
}

TEST(ValidateBTSInOrder, InvalidText) {
  auto root = CreateNode<std::string>("Dog");
  root->left = CreateNode<std::string>("Elephant");
  root->right = CreateNode<std::string>("Cat");
  auto result = IsValidBST<std::string>(root);
  EXPECT_EQ(result, false);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}