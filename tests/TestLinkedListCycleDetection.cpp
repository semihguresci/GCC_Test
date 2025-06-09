#include <numeric>
#include <random>
#include <vector>

#include "GTestCommon.hpp"
#include "LinkedListCycleDetection.hpp"

using namespace LinkedListCycleDetection;

TEST(CycleDetectionTest, EmptyList) {
  ListNode<int>* empty_list = nullptr;
  EXPECT_FALSE(HasCycle(empty_list));
}

TEST(CycleDetectionTest, SingleNodeNoCycle) {
  auto list = VectorToList(std::vector<int>{1});
  EXPECT_FALSE(HasCycle(list));
}

TEST(CycleDetectionTest, SingleNodeSelfCycle) {
  auto list = VectorToList(std::vector<int>{1});
  CreateCycle(list, 0);  
  EXPECT_TRUE(HasCycle(list));
}

TEST(CycleDetectionTest, TwoNodesNoCycle) {
  auto list = VectorToList(std::vector<int>{1, 2});
  EXPECT_FALSE(HasCycle(list));
}

TEST(CycleDetectionTest, TwoNodesWithCycle) {
  auto list = VectorToList(std::vector<int>{1, 2});
  CreateCycle(list, 0);  
  EXPECT_TRUE(HasCycle(list));
}

TEST(CycleDetectionTest, LongListNoCycle) {
  auto list = VectorToList(std::vector<int>{1, 2, 3, 4, 5});
  EXPECT_FALSE(HasCycle(list));
}

TEST(CycleDetectionTest, LongListWithCycle) {
  auto list = VectorToList(std::vector<int>{1, 2, 3, 4, 5});
  CreateCycle(list, 2);  
  EXPECT_TRUE(HasCycle(list));
}

TEST(CycleDetectionTest, CycleAtBeginning) {
  auto list = VectorToList(std::vector<int>{1, 2, 3});
  CreateCycle(list, 0);  
  EXPECT_TRUE(HasCycle(list));
}

TEST(CycleDetectionTest, CycleAtEnd) {
  auto list = VectorToList(std::vector<int>{1, 2, 3});
  CreateCycle(list, 2);  
  EXPECT_TRUE(HasCycle(list));
}

TEST(CycleDetectionTest, CustomTypeNoCycle) {
  struct Person {
    std::string name;
    int age;
  };

  auto list = new ListNode<Person>(Person{"Alice", 30});
  list->next = new ListNode<Person>(Person{"Bob", 25});
  EXPECT_FALSE(HasCycle(list));
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}