#include "DeepCloneLL.hpp"
#include "GTestCommon.hpp"

TEST(DeepCloneLL, DeepCloneLLTests) {
  DeepCloneLL::Node* head = new DeepCloneLL::Node(1);
  head->next = new DeepCloneLL::Node(2);
  head->next->next = new DeepCloneLL::Node(3);

  head->random = head->next->next;        // 1's random -> 3
  head->next->random = head;              // 2's random -> 1
  head->next->next->random = head->next;  // 3's random -> 2

  DeepCloneLL deepClone;
  DeepCloneLL::Node* clonedHead = deepClone.DeepClone(head);

  EXPECT_NE(clonedHead, head);
  EXPECT_EQ(clonedHead->val, head->val);

  EXPECT_NE(clonedHead->random, head->random);

  EXPECT_NE(clonedHead->next, head->next);
  EXPECT_EQ(clonedHead->next->val, head->next->val);

  EXPECT_NE(clonedHead->random, nullptr);
  EXPECT_EQ(clonedHead->random->val, head->random->val);

  delete head->next->next;
  delete head->next;
  delete head;

  delete clonedHead->next->next;
  delete clonedHead->next;
  delete clonedHead;
}
