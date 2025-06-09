#ifndef ADD_TWO_NUMBERS_LL_HPP
#define ADD_TWO_NUMBERS_LL_HPP
/**
* Add Two Numbers (Linked List)
* Problem:
* You are given two non-empty linked lists representing two non-negative integers.
* The digits are stored in reverse order, and each node contains a single digit.
* Add the two numbers and return the sum as a linked list.
*/

#include <vector>
namespace AddTwoNumbersLL {

template <typename T>
struct ListNode {
  T val;
  ListNode* next;
  ListNode(T x) : val(x), next(nullptr) {}
  ~ListNode() { delete next; }
};
template <typename T>
inline auto AddTwoNumbers(ListNode<T>* l1, ListNode<T>* l2) -> ListNode<T>* {
  if (!l1 && !l2) return nullptr;

  auto dummy = new ListNode<T>(0);
  auto current = dummy;
  T carry = T(0);

  while (l1 || l2 || carry) {
    T sum = carry;
    if (l1) {
      sum += l1->val;
      l1 = l1->next;
    }
    if (l2) {
      sum += l2->val;
      l2 = l2->next;
    }
    carry = sum / 10;
    current->next = new ListNode<T>(sum % 10);
    current = current->next;
  }
  return dummy->next;
}

template <typename T>
std::vector<T> ListToVector(ListNode<T>* head) {
  std::vector<T> result;
  while (head) {
    result.push_back(head->val);
    head = head->next;
  }
  return result;
}

template <typename T>
ListNode<T>* MakeList(std::initializer_list<T> vals) {
  ListNode<T>* dummy = new ListNode<T>(T(0));
  auto current = dummy;
  for (auto v : vals) {
    current->next = new ListNode<T>(v);
    current = current->next;
  }
  auto head = dummy->next;
  dummy->next = nullptr; 
  delete dummy;
  return head;
}

template <typename T>
void DeleteList(ListNode<T>* head) {
  delete head;
}

}  // namespace AddTwoNumbersLL
#endif  //! ADD_TWO_NUMBERS_LL_HPP
