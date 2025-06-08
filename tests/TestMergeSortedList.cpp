#include "GTestCommon.hpp"
#include "MergeSortedList.hpp"

using namespace MergeSortedList;

TEST(MergeSortedList, EmptyListsRecursive) {
  std::unique_ptr<ListNode<int>> l1 = nullptr;
  std::unique_ptr<ListNode<int>> l2 = nullptr;
  auto merged = MergeTwoListsRecursive(l1, l2);
  EXPECT_EQ(merged, nullptr);
}

TEST(MergeSortedList, OneEmptyListRecursive) {
  auto l1 = VectorToList(std::vector<int>{1, 3, 5});
  std::unique_ptr<ListNode<int>> l2 = nullptr;
  auto merged = MergeTwoListsRecursive(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 3, 5}));
}

TEST(MergeSortedList, MergeTwoListsRecursive) {
  auto l1 = VectorToList(std::vector<int>{1, 3, 5});
  auto l2 = VectorToList(std::vector<int>{2, 4, 6});
  auto merged = MergeTwoListsRecursive(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(MergeSortedList, MergeUnevenLengthListsRecursive) {
  auto l1 = VectorToList(std::vector<int>{1, 3});
  auto l2 = VectorToList(std::vector<int>{2, 4, 6, 8});
  auto merged = MergeTwoListsRecursive(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 2, 3, 4, 6, 8}));
}

TEST(MergeSortedList, CustomTypeRecursive) {
  struct Person {
    std::string name;
    int age;
    bool operator<(const Person& other) const { return age < other.age; }
  };

  auto l1 = VectorToList(std::vector<Person>{{"Alice", 25}, {"Bob", 30}});
  auto l2 = VectorToList(std::vector<Person>{{"Charlie", 20}, {"Dave", 35}});
  auto merged = MergeTwoListsRecursive(l1, l2);
  auto result = ListToVector(merged);
  ASSERT_EQ(result.size(), 4);
  EXPECT_EQ(result[0].name, "Charlie");  
  EXPECT_EQ(result[3].name, "Dave");     
}

TEST(MergeSortedList, MemorySafetyRecursive) {
  auto l1 = VectorToList(std::vector<int>{1, 2});
  auto l2 = VectorToList(std::vector<int>{3, 4});
  auto merged = MergeTwoListsRecursive(l1, l2);
  SUCCEED();  
              
}


TEST(MergeSortedList, EmptyListsIterative) {
  std::unique_ptr<ListNode<int>> l1 = nullptr;
  std::unique_ptr<ListNode<int>> l2 = nullptr;
  auto merged = MergeTwoListsIterative(l1, l2);
  EXPECT_EQ(merged, nullptr);
}

TEST(MergeSortedList, OneEmptyListIterative) {
  auto l1 = VectorToList(std::vector<int>{1, 3, 5});
  std::unique_ptr<ListNode<int>> l2 = nullptr;
  auto merged = MergeTwoListsIterative(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 3, 5}));
}

TEST(MergeSortedList, MergeTwoListsIterative) {
  auto l1 = VectorToList(std::vector<int>{1, 3, 5});
  auto l2 = VectorToList(std::vector<int>{2, 4, 6});
  auto merged = MergeTwoListsIterative(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(MergeSortedList, MergeUnevenLengthListsIterative) {
  auto l1 = VectorToList(std::vector<int>{1, 3});
  auto l2 = VectorToList(std::vector<int>{2, 4, 6, 8});
  auto merged = MergeTwoListsIterative(l1, l2);
  EXPECT_EQ(ListToVector(merged), (std::vector<int>{1, 2, 3, 4, 6, 8}));
}

TEST(MergeSortedList, CustomTypeIterative) {
  struct Person {
    std::string name;
    int age;
    bool operator<(const Person& other) const { return age < other.age; }
  };

  auto l1 = VectorToList(std::vector<Person>{{"Alice", 25}, {"Bob", 30}});
  auto l2 = VectorToList(std::vector<Person>{{"Charlie", 20}, {"Dave", 35}});
  auto merged = MergeTwoListsIterative(l1, l2);
  auto result = ListToVector(merged);
  ASSERT_EQ(result.size(), 4);
  EXPECT_EQ(result[0].name, "Charlie");
  EXPECT_EQ(result[3].name, "Dave");
}

TEST(MergeSortedList, MemorySafetyIterative) {
  auto l1 = VectorToList(std::vector<int>{1, 2});
  auto l2 = VectorToList(std::vector<int>{3, 4});
  auto merged = MergeTwoListsIterative(l1, l2);
  SUCCEED();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}