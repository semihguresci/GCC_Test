#ifndef LINKED_LIST_CYCLE_DETECTION_HPP
#define LINKED_LIST_CYCLE_DETECTION_HPP

#include <memory>
#include <vector>

namespace LinkedListCycleDetection {
template <typename T>
struct ListNode {
  T val;
  ListNode<T>* next;
  explicit ListNode(T x) : val(x), next(nullptr) {}
};

template <typename T>
bool HasCycle(const ListNode<T>* head) {
  if (!head) return false;

  auto* slow = head;
  auto* fast = head;

  while (fast && fast->next) {
    slow = slow->next;
    fast = fast->next->next;

    if (slow == fast) return true;
  }
  return false;
}

template <typename T>
auto VectorToList(const std::vector<T>& vec) -> ListNode<T>* {
  if (vec.empty()) return nullptr;

  auto head = new ListNode<T>(vec[0]);
  ListNode<T>* current = head;

  for (size_t i = 1; i < vec.size(); ++i) {
    current->next = new ListNode<T>(vec[i]);
    current = current->next;
  }
  return head;
}

template <typename T>
void CreateCycle(ListNode<T>* head, int pos) {
  if (!head) return;

  ListNode<T>* cycle_node = nullptr;
  ListNode<T>* current = head;
  int index = 0;

  if (!head->next) {
    if (pos == 0 || pos == -1) {
      head->next = head;
    }
    return;
  }

  while (current->next) {
    if (index == pos) cycle_node = current;
    current = current->next;
    index++;
  }

  if (pos == -1 || index == pos) {
    current->next = current;
  } else if (cycle_node) {
    current->next = cycle_node;
  }
}

}  // namespace LinkedListCycleDetection
#endif  // !LINKED_LIST_CYCLE_DETECTION_HPP
