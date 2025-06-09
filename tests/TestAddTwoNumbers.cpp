#include "AddTwoNumbers.hpp"
#include "GTestCommon.hpp"

using namespace AddTwoNumbersLL;

template <typename T>
class AddTwoNumbersTest : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}

  ListNode<T>* l1 = nullptr;
  ListNode<T>* l2 = nullptr;
  ListNode<T>* result = nullptr;
};

using TestTypes = ::testing::Types<int, long, unsigned int>;
TYPED_TEST_SUITE(AddTwoNumbersTest, TestTypes);

TYPED_TEST(AddTwoNumbersTest, BasicAddition) {
  this->l1 = MakeList<TypeParam>({2, 4, 3});  // 342
  this->l2 = MakeList<TypeParam>({5, 6, 4});  // 465
  this->result = AddTwoNumbers<TypeParam>(this->l1, this->l2);

  EXPECT_EQ(ListToVector(this->result), std::vector<TypeParam>({7, 0, 8}));

  DeleteList(this->l1);
  DeleteList(this->l2);
  DeleteList(this->result);
}

TYPED_TEST(AddTwoNumbersTest, UnequalLengthLists) {
  this->l1 = MakeList<TypeParam>({9, 9, 9, 9});  // 9999
  this->l2 = MakeList<TypeParam>({1});           // 1
  this->result = AddTwoNumbers<TypeParam>(this->l1, this->l2);

  EXPECT_EQ(ListToVector(this->result),
            std::vector<TypeParam>({0, 0, 0, 0, 1}));

  DeleteList(this->l1);
  DeleteList(this->l2);
  DeleteList(this->result);
}

TYPED_TEST(AddTwoNumbersTest, EmptyLists) {
  this->result = AddTwoNumbers<TypeParam>(nullptr, nullptr);
  EXPECT_EQ(this->result, nullptr);
}

TYPED_TEST(AddTwoNumbersTest, OneEmptyList) {
  this->l1 = MakeList<TypeParam>({1, 2, 3});  // 321
  this->l2 = MakeList<TypeParam>({0});
  this->result = AddTwoNumbers<TypeParam>(this->l1, this->l2);

  EXPECT_EQ(ListToVector(this->result), std::vector<TypeParam>({1, 2, 3}));

  DeleteList(this->l1);
  DeleteList(this->result);
}

TYPED_TEST(AddTwoNumbersTest, CarryPropagation) {
  this->l1 = MakeList<TypeParam>({9, 9});  // 99
  this->l2 = MakeList<TypeParam>({1});     // 1
  this->result = AddTwoNumbers<TypeParam>(this->l1, this->l2);

  EXPECT_EQ(ListToVector(this->result), std::vector<TypeParam>({0, 0, 1}));

  DeleteList(this->l1);
  DeleteList(this->l2);
  DeleteList(this->result);
}

TYPED_TEST(AddTwoNumbersTest, LargeNumbers) {
  this->l1 = MakeList<TypeParam>({9, 9, 9, 9, 9, 9, 9});
  this->l2 = MakeList<TypeParam>({1});
  this->result = AddTwoNumbers<TypeParam>(this->l1, this->l2);

  EXPECT_EQ(ListToVector(this->result),
            std::vector<TypeParam>({0, 0, 0, 0, 0, 0, 0, 1}));

  DeleteList(this->l1);
  DeleteList(this->l2);
  DeleteList(this->result);
}

TEST(AddTwoNumbersSpecificTest, UnsignedOverflow) {
  auto* l1 = MakeList<unsigned int>({255});
  auto* l2 = MakeList<unsigned int>({1});
  auto* result = AddTwoNumbers<unsigned int>(l1, l2);

  EXPECT_EQ(ListToVector(result), std::vector<unsigned int>({6, 5, 2}));

  DeleteList(l1);
  DeleteList(l2);
  DeleteList(result);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}