#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <functional>
#include <stdexcept>
#include <vector>

namespace puzzle {
int Factorial(int n) {
  if (n < 0) {
    throw std::invalid_argument(
        "Factorial is not defined for negative numbers.");
  }
  if (n == 0) return 1;
  int result = 1;
  for (int i = 2; i <= n; ++i) {
    result *= i;
  }
  return result;
}

std::vector<std::vector<int>> Combinations(int n, int k) {
  if (n < 0 || k < 0 || k > n) {
    throw std::invalid_argument("Invalid arguments.");
  }
  std::vector<std::vector<int>> result_;
  std::vector<int> combination_;
  std::function<void(int, int, int, std::vector<int>&,
                     std::vector<std::vector<int>>&)>
      CombinationsHelper;
  CombinationsHelper = [&](int n, int k, int start,
                           std::vector<int>& combination,
                           std::vector<std::vector<int>>& result) -> void {
    if (combination.size() == k) {
      result.push_back(combination);
      return;
    }

    for (int i = start; i <= n; i++) {
      combination.push_back(i);
      CombinationsHelper(n, k, i + 1, combination, result);
      combination.pop_back();
    }
  };
  CombinationsHelper(n, k, 1, combination_, result_);
  return result_;
}

std::vector<std::string> PermutationsRecursive(std::string key, int left,
                                               int right) {
  std::vector<std::string> result;
  if (left == right) {
    result.push_back(key);
    return result;
  }

  for (int i = left; i <= right; ++i) {
    std::swap(key[left], key[i]);
    std::vector<std::string> subPermutations =
        PermutationsRecursive(key, left + 1, right);
    result.insert(result.end(), subPermutations.begin(), subPermutations.end());
    std::swap(key[left], key[i]);
  }

  return result;
}

std::vector<std::string> PermuationsIterative(std::string key, int left,
                                              int right) {
  std::vector<std::string> result;
  if (left > right) {
    return result;
  }

  if (key.empty()) {
    result.push_back("");
    return result;
  }

  int n = right - left + 1;

  std::vector<int> indexes(n, 0);

  result.push_back(key);

  int i = 0;
  while (i < n) {
    if (indexes[i] < i) {
      if (i % 2 == 0) {
        std::swap(key[left], key[left + i]);
      } else {
        std::swap(key[left + indexes[i]], key[left + i]);
      }

      result.push_back(key);

      indexes[i]++;
      i = 0;

    } else {
      indexes[i] = 0;
      i++;
    }
  }

  return result;
}

auto PowerModulo(long long base, long long exponent, long long m) -> long long {
  if (m == 0) {
    throw std::invalid_argument("Modulus (m) cannot be zero.");
  }
  long long result = 1;
  base = base % m;
  while (exponent > 0) {
    if (exponent % 2 == 1) {
      result = (result * base) % m;
    }
    exponent = exponent >> 1;
    base = (base * base) % m;
  }
  return result;
}

auto IntegerSqrt(long long n) -> long long {
  if (n < 0) {
    throw std::invalid_argument(
        "Cannot compute square root of negative number.");
  }
  if (n < 2) {
    return n;
  }

  int x = n;

  while (x > n / x) {
    x = (x + n / x) / 2;
  }
  return x;
}

auto IsPrime(long long n) -> bool {
  if (n <= 1) {
    return false;
  }
  if (n == 2) {
    return true;
  }
  if (n % 2 == 0) {
    return false;
  }

  std::vector<bool> prime(n + 1, true);

  for (long long i = 2; i * i <= n; ++i) {
    if (prime[i]) {
      for (long long j = i * i; j <= n; j += i) {
        prime[j] = false;
      }
    }
  }
  return prime[n];
}

auto PascalTriangleRow(int n) -> std::vector<int> {
  if (n < 0) {
    throw std::invalid_argument("Invalid argument.");
  }
  std::vector<int> result(n + 1, 0);
  result[0] = 1;
  for (int i = 1; i <= n; ++i) {
    result[i] = result[i - 1] * (n - i + 1) / i;  // Combinatorial Formula nCk
  }
  return result;
}

}  // namespace puzzle
#endif  // !PUZZLE_HPP
