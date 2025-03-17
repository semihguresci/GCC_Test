#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include <stdexcept>
#include <vector>

template <typename T>
T FibonacciIterative(T n) {
  if (n < 0) {
    throw std::invalid_argument(
        "Fibonacci is not defined for negative numbers.");
  }
  if (n == 0) return 0;
  if (n == 1) return 1;

  T prev = 0;
  T curr = 1;

  for (T i = 2; i <= n; ++i) {
    T next = prev + curr;
    prev = curr;
    curr = next;
  }
  return curr;
}

template <typename T>
class FibonacciMatrix {
  struct Matrix2x2 {
    T data[2][2];
  };

 public:
  void Multiply(Matrix2x2& F, Matrix2x2& M) {
    Matrix2x2 temp;
    temp.data[0][0] = F.data[0][0] * M.data[0][0] + F.data[0][1] * M.data[1][0];
    temp.data[0][1] = F.data[0][0] * M.data[0][1] + F.data[0][1] * M.data[1][1];
    temp.data[1][0] = F.data[1][0] * M.data[0][0] + F.data[1][1] * M.data[1][0];
    temp.data[1][1] = F.data[1][0] * M.data[0][1] + F.data[1][1] * M.data[1][1];

    F.data[0][0] = temp.data[0][0];
    F.data[0][1] = temp.data[0][1];
    F.data[1][0] = temp.data[1][0];
    F.data[1][1] = temp.data[1][1];
  }

  void Power(Matrix2x2& F, T n) {
    Matrix2x2 M = {{{1, 1}, {1, 0}}};
    Matrix2x2 result = {{{1, 0}, {0, 1}}};

    while (n > 0) {
      if (n % 2 != 0) {
        Multiply(result, M);
      }
      Multiply(M, M);
      n /= 2;
    }
    F = result; 
  }

  T Fibonacci(T n) {
    if (n < 0) {
      throw std::invalid_argument(
          "Fibonacci is not defined for negative numbers.");
    }
    if (n == 0) return 0;
    if (n == 1) return 1;

    Matrix2x2 F = {{{1, 1}, {1, 0}}};
    Power(F, n-1);

    return F.data[0][0];
  }
};

template <typename T>
T FibonacciDP(T n) {
  if (n < 0) {
    throw std::invalid_argument(
        "Fibonacci is not defined for negative numbers.");
  }
  if (n == 0) return 0;
  if (n == 1) return 1;

  std::vector<T> dp(n + 1);
  dp[0] = 0;
  dp[1] = 1;
  for (T i = 2; i <= n; ++i) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

template <typename T>
T FibonacciDPSpaceOptimized(T n) {
  if (n < 0) {
    throw std::invalid_argument(
        "Fibonacci is not defined for negative numbers.");
  }
  if (n == 0) return 0;
  if (n == 1) return 1;

  T prev2 = 0;
  T prev1 = 1;
  T curr = 0;
  for (T i = 2; i <= n; ++i) {
    curr = prev1 + prev2;
    prev2 = prev1;
    prev1 = curr;
  }
  return curr;
}


#endif  // FIBONACCI_HPP