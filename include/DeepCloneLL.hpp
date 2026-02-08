#ifndef DEEP_CLONE_LL_HPP
#define DEEP_CLONE_LL_HPP

/*
Given the head to a singly linked list, where each node also has a “random”
pointer that points to anywhere in the linked list, deep clone the list.
*/

class DeepCloneLL {
 public:
  struct Node {
    int val;
    Node* next{nullptr};
    Node* random{nullptr};
    Node(int v) : val(v), next(nullptr), random(nullptr) {}
  };
  Node* DeepClone(Node* head) {
    if (!head) return nullptr;
    // Create new nodes and interleave them with original nodes
    for (Node* curr = head; curr; curr = curr->next->next) {
      Node* copy = new Node(curr->val);
      copy->next = curr->next;
      curr->next = copy;
    }

    // Set random pointers for the new nodes
    for (Node* curr = head; curr != nullptr; curr = curr->next->next) {
      Node* copy = curr->next;
      if (curr->random) {
        copy->random = curr->random->next;
      }
    }
    //Separate the interleaved list into original and cloned
    Node* newHead = head->next;
    for (Node* curr = head; curr != nullptr; curr = curr->next) {
      Node* copy = curr->next;
      curr->next = copy->next;
      if (copy->next) {
        copy->next = copy->next->next;
      }
    }


    return newHead;
  }
};

#endif  // DEEP_CLONE_LL_HPP