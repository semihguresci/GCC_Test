#ifndef MERGE_SORTED_LIST_HPP
#define MERGE_SORTED_LIST_HPP

#include <memory>
#include <vector>

namespace MergeSortedList {
template <typename T>
struct ListNode {
  T val;
  std::unique_ptr<ListNode<T>> next;
  explicit ListNode(T val) : val(val), next(nullptr) {}
};

template <typename T>
[[nodiscard]] auto MergeTwoListsRecursive(std::unique_ptr<ListNode<T>>& l1,
                                          std::unique_ptr<ListNode<T>>& l2)
    -> std::unique_ptr<ListNode<T>> {
  if (!l1) return std::move(l2);
  if (!l2) return std::move(l1);

  if (l1->val < l2->val) {
    l1->next = MergeTwoListsRecursive(l1->next, l2);
    return std::move(l1);
  } else {
    l2->next = MergeTwoListsRecursive(l1, l2->next);
    return std::move(l2);
  }
}

template <typename T>
[[nodiscard]] auto MergeTwoListsIterative(std::unique_ptr<ListNode<T>>& l1,
                                          std::unique_ptr<ListNode<T>>& l2)
    -> std::unique_ptr<ListNode<T>> {
  if (!l1) return std::move(l2);
  if (!l2) return std::move(l1);

  std::unique_ptr<ListNode<T>> head = nullptr;
  ListNode<T>* tail = nullptr;  

  if (l1->val < l2->val) {
    head = std::move(l1);
    l1 = std::move(head->next);
  } else {
    head = std::move(l2);
    l2 = std::move(head->next);
  }
  tail = head.get();

  while (l1 && l2) {
    if (l1->val < l2->val) {
      tail->next = std::move(l1);
      tail = tail->next.get();
      l1 = std::move(tail->next);
    } else {
      tail->next = std::move(l2);
      tail = tail->next.get();
      l2 = std::move(tail->next);
    }
  }

  if (l1) {
    tail->next = std::move(l1);
  } else if (l2) {
    tail->next = std::move(l2);
  }

  return head;
}

template <typename T>
auto ListToVector(const std::unique_ptr<ListNode<T>>& head) -> std::vector<T> {
  std::vector<T> vec;
  for (auto* node = head.get(); node != nullptr; node = node->next.get()) {
    vec.push_back(node->val);
  }
  return vec;
}

template <typename T>
auto VectorToList(const std::vector<T>& vec) -> std::unique_ptr<ListNode<T>> {
  if (vec.empty()) return nullptr;
  auto head = std::make_unique<ListNode<T>>(vec[0]);
  ListNode<T>* tail = head.get();
  for (size_t i = 1; i < vec.size(); ++i) {
    tail->next = std::make_unique<ListNode<T>>(vec[i]);
    tail = tail->next.get();
  }
  return head;
}

}  // namespace MergeSortedList

#endif  // !MERGE_SORTED_LIST_HPP
