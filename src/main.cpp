#include <cstdlib>
#include <format>
#include <iostream>
#include <vector>

#include "MaxProduct.hpp"

int main() {
#ifdef _WIN32
  std::system("ver");
#elif __linux__ || __APPLE__
  std::system("uname -a");
#else
  std::cout << "Platform: Unknown" << std::endl;
#endif

  std::cout << "C++ Compiler Version: ";

#if defined(__clang__)
  std::cout << __clang_version__ << " (Clang)" << std::endl;
#elif defined(__GNUC__) || defined(__GNUG__)
  std::cout << __VERSION__ << " (GCC)" << std::endl;
#elif defined(_MSC_VER)
  std::cout << _MSC_VER << " (MSVC)" << std::endl;
#else
  std::cout << "Unknown Compiler" << std::endl;
#endif

  std::cout << "Hello, World with C++20!" << std::endl;
  return 0;
}
