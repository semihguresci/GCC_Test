#ifndef URL_SHORTENER_HPP
#define URL_SHORTENER_HPP

#include <optional>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_map>
/*
Implement a URL shortener with the following methods: shorten(url), which
shortens the url into a six-character alphanumeric string, such as zLg6wl.
restore(short), which expands the shortened string into the original url. If no
such shortened string exists, return null. Hint: What if we enter the same URL
twice?
*/
namespace URL{

class URLShortener {
 public:
  std::string shorten(const std::string& url) {
    if (url.empty()) throw std::invalid_argument("url cannot be empty");

    if (auto it = url_to_code_.find(url); it != url_to_code_.end()) {
      return it->second;
    }

    std::string code;
    do {
      code = generateCode6_();
    } while (code_to_url_.find(code) != code_to_url_.end());

    url_to_code_[url] = code;
    code_to_url_[code] = url;
    return code;
  }

  std::optional<std::string> restore(const std::string& code) const {
    if (auto it = code_to_url_.find(code); it != code_to_url_.end()) {
      return it->second;
    }
    return std::nullopt;
  }

 private:
  static constexpr std::string_view kAlphabet =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  static constexpr int kAlphabetSize = static_cast<int>(kAlphabet.size());

  std::string generateCode6_() {
    std::string s(6, '0');
    for (int i = 0; i < 6; ++i) {
      s[i] = kAlphabet[dist_(rng_)];
    }
    return s;
  }

  std::unordered_map<std::string, std::string> url_to_code_;
  std::unordered_map<std::string, std::string> code_to_url_;

  mutable std::mt19937 rng_{std::random_device{}()};
  mutable std::uniform_int_distribution<int> dist_{0, kAlphabetSize - 1};
};

}  // namespace URLShortener

#endif  // URL_SHORTENER_HPP