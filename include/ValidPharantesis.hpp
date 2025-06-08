#ifndef VALID_PHARANTHESES_HPP
#define VALID_PHARANTHESES_HPP

#include <stack>
#include <string>
#include <unordered_map>
#include <numeric> 

inline bool IsValidPharantesis(const std::string_view s) {
  std::unordered_map<char, char> pairs = {{')', '('}, {'}', '{'}, {']', '['}};

  auto validate = [&pairs](std::stack<char> st, char c) -> std::stack<char> {
    if (auto it = pairs.find(c); it != pairs.end()) {  // Closing Bracket
      if (!st.empty() && st.top() == it->second) {
        st.pop();
      } else {
        st.push('\0');
      }
    } else {  // Openning Bracket
      st.push(c);
    }
    return st;
  };

  std::stack<char> result =
      std::accumulate(s.begin(), s.end(), std::stack<char>(), validate);

  return result.empty();
}
#endif  // !VALID_PHARANTHESES_HPP
