#ifndef MAJORITY_ELEMENT_H
#define MAJORITY_ELEMENT_H

#include <span>

class MajorityElement {
 public:
  template <typename T>
  static auto FindMajorityElement(const std::span<T>& nums) -> T {
	T candidate{};
	int count = 0;
	for (const auto& num : nums) {
	  if (count == 0) {
		candidate = num;
		count = 1;
	  } else if (num == candidate) {
		++count;
	  } else {
		--count;
	  }
	}
	return candidate;
  }
};

#endif  // !MAJORITY_ELEMENT_H