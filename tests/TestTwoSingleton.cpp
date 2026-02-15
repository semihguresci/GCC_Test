#include "GTestCommon.hpp"
#include "TwoSingleton.hpp"

TEST(TwoSingletonTests, AlternatesOddSecondEvenFirst) {
  EXPECT_EQ(TwoSingleton::getInstance().id(), 1);
  EXPECT_EQ(TwoSingleton::getInstance().id(), 2);
  EXPECT_EQ(TwoSingleton::getInstance().id(), 1);
  EXPECT_EQ(TwoSingleton::getInstance().id(), 2);
  EXPECT_EQ(TwoSingleton::getInstance().id(), 1);
  EXPECT_EQ(TwoSingleton::getInstance().id(), 2);
}

TEST(TwoSingletonTests, OnlyTwoDistinctInstancesEverReturned) {
  std::set<const TwoSingleton*> addresses;

  for (int i = 0; i < 100; ++i) {
    addresses.insert(&TwoSingleton::getInstance());
  }

  EXPECT_EQ(addresses.size(), 2u);
}

TEST(TwoSingletonTests, AddressesAndIdsAreConsistentWithAlternation) {
  TwoSingleton& a = TwoSingleton::getInstance();
  TwoSingleton& b = TwoSingleton::getInstance();
  ASSERT_NE(&a, &b);
  EXPECT_EQ(a.id(), 1);
  EXPECT_EQ(b.id(), 2);

  TwoSingleton& c = TwoSingleton::getInstance();
  TwoSingleton& d = TwoSingleton::getInstance();

  EXPECT_EQ(&a, &c);
  EXPECT_EQ(&b, &d);
  EXPECT_EQ(c.id(), 1);
  EXPECT_EQ(d.id(), 2);
}

TEST(TwoSingletonTests, StressReturnsOnlyTwoAddresses) {
  std::vector<const TwoSingleton*> addrs;
  addrs.reserve(10000);

  for (int i = 0; i < 10000; ++i) {
    addrs.push_back(&TwoSingleton::getInstance());
  }

  std::set<const TwoSingleton*> uniq(addrs.begin(), addrs.end());
  EXPECT_EQ(uniq.size(), 2u);
}