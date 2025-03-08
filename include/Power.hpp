#ifndef POWER_HPP
#define POWER_HPP

inline int PowerIterative(int base, int exponent) {
  int result = 1;
  while (exponent > 0) {
    if (exponent % 2 == 1) {
      result *= base;
    }
    base *= base;
    exponent /= 2;
  }
  return result;
}

inline int PowerRecursive(int base, int exponent) {
  if (exponent == 0) {
    return 1;
  }
  if (exponent % 2 == 0) {
    return PowerRecursive(base * base, exponent / 2);
  }
  return base * PowerRecursive(base * base, exponent / 2);
}

inline int PowerBitwise(int base, int exponent) {
  int result = 1;
  while (exponent > 0) {
    if (exponent & 1) {
      result *= base;
    }
    base *= base;
    exponent >>= 1;
  }
  return result;
}


#endif  // ! POWER_HPP
