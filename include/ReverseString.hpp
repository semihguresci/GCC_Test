#ifndef REVERSE_STRING_HPP
#define REVERSE_STRING_HPP
#include <string>
#include <algorithm>

// Function to reverse a string in place
inline void ReverseString(std::string& str) {
	std::reverse(str.begin(), str.end());
}
#endif  // !REVERSE_STRING_HPP
