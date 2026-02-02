#include "URLShortener.hpp"
#include "GTestCommon.hpp"

using namespace URL;

TEST(URLShortener, ShortenAndRetrieve) {
  URLShortener urlShortener;
  std::string longURL = "https://www.example.com/some/very/long/url";
  std::string shortURL = urlShortener.shorten(longURL);
  EXPECT_FALSE(shortURL.empty());
  auto retrievedURL = urlShortener.restore(shortURL);
  ASSERT_TRUE(retrievedURL.has_value());
  EXPECT_EQ(retrievedURL.value(), longURL);
}