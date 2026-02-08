#ifndef RODUCTEXCEPTSELF_HPP
#define RODUCTEXCEPTSELF_HPP
/*
Given an array of integers, return a new array such that each element at index i
of the new array is the product of all the numbers in the original array except
the one at i. For example, if our input was [1, 2, 3, 4, 5], the expected output
would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output
would be [2, 3, 6]. Follow-up: what if you can't use division?
*/

class ProductExceptSelf {
 public:
  std::vector<long long> Solve(const std::span<long long> nums) {
    const std::size_t n = nums.size();
    std::vector<long long> out(n, 1LL);

    long long prefix = 1LL;
    for (std::size_t i = 0; i < n; ++i) {
      out[i] = prefix;
      prefix *= nums[i];
    }

    long long suffix = 1LL;
    for (std::size_t i = n; i-- > 0;) {
      out[i] *= suffix;
      suffix *= nums[i];
    }
    return out;
  }
};

#endif  // RODUCTEXCEPTSELF_HPP