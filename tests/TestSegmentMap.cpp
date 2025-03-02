#include "GTestCommon.hpp"
#include "SegmentMap.hpp"

TEST(TestSegmentMap, Empty) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 1, 'B');

  EXPECT_TRUE(imap.segment_map_.empty());
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'A');
  EXPECT_EQ(imap[2], 'A');
}

TEST(TestSegmentMap, EmptyInterval) {
  SegmentMap<int, int> imap(0);
  imap.Add(10, 10, 5);
  EXPECT_EQ(imap[5], 0);
  EXPECT_EQ(imap[15], 0);
}

TEST(TestSegmentMap, EmptyMapReturnsDefault) {
  SegmentMap<int, std::string> imap("default");
  EXPECT_EQ(imap[5], "default");
}

TEST(TestSegmentMap, DoubleEmptyMapReturnsDefault) {
  SegmentMap<double, int> imap(0);
  EXPECT_EQ(imap[3.14], 0);
}

TEST(TestSegmentMap, BasicTest) {
  SegmentMap<int, char> imap('A');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[100], 'A');

  imap.Add(10, 20, 'B');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[15], 'B');
  EXPECT_EQ(imap[25], 'A');

  imap.Add(15, 30, 'C');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[12], 'B');
  EXPECT_EQ(imap[18], 'C');
  EXPECT_EQ(imap[28], 'C');
  EXPECT_EQ(imap[35], 'A');

  imap.Add(5, 12, 'D');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[8], 'D');
  EXPECT_EQ(imap[14], 'B');
  EXPECT_EQ(imap[35], 'A');
}

TEST(TestSegmentMap, SingleAssignment) {
  SegmentMap<int, std::string> imap("default");
  EXPECT_EQ(imap[5], "default");

  imap.Add(10, 20, "test");

  EXPECT_EQ(imap[10], "test");
  EXPECT_EQ(imap[15], "test");
  EXPECT_EQ(imap[19], "test");

  EXPECT_EQ(imap[9], "default");
  EXPECT_EQ(imap[20], "default");
}

TEST(TestSegmentMap, Single) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'B');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[3], 'A');
  EXPECT_EQ(imap[4], 'A');
}

TEST(TestSegmentMap, Overlapping) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 5, 'B');
  imap.Add(3, 7, 'C');

  EXPECT_EQ(imap.segment_map_.size(), 3);
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[3], 'C');
  EXPECT_EQ(imap[4], 'C');
  EXPECT_EQ(imap[6], 'C');
  EXPECT_EQ(imap[7], 'A');
  EXPECT_EQ(imap[8], 'A');
}

TEST(TestSegmentMap, OverlappingString) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 20, "range1");
  imap.Add(30, 40, "range2");

  EXPECT_EQ(imap[10], "range1");
  EXPECT_EQ(imap[15], "range1");
  EXPECT_EQ(imap[19], "range1");

  EXPECT_EQ(imap[25], "default");
  EXPECT_EQ(imap[30], "range2");
  EXPECT_EQ(imap[35], "range2");
  EXPECT_EQ(imap[39], "range2");
  EXPECT_EQ(imap[5], "default");
  EXPECT_EQ(imap[45], "default");
}

TEST(TestSegmentMap, OverlappingIntervals) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 20, "first");
  imap.Add(15, 25, "second");

  EXPECT_EQ(imap[5], "default");
  EXPECT_EQ(imap[12], "first");
  EXPECT_EQ(imap[18], "second");
  EXPECT_EQ(imap[22], "second");
  EXPECT_EQ(imap[30], "default");

  imap.Add(5, 30, "third");
  EXPECT_EQ(imap[15], "third");
  EXPECT_EQ(imap[20], "third");
}

TEST(TestSegmentMap, ClearEntireRange) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 20, "value1");
  imap.Add(20, 30, "value2");
  imap.Add(30, 40, "value3");
  EXPECT_EQ(imap.segment_map_.size(), 4);

  imap.Add(5, 45, "default");

  EXPECT_EQ(imap[15], "default");
  EXPECT_EQ(imap[25], "default");
  EXPECT_EQ(imap[35], "default");
  EXPECT_EQ(imap.segment_map_.size(), 0);
}

TEST(TestSegmentMap, BeginningAndEnd) {
  SegmentMap<int, int> imap(0);
  imap.Add(0, 5, 1);
  EXPECT_EQ(imap[2], 1);
  EXPECT_EQ(imap[7], 0);

  imap.Add(5, 10, 2);
  EXPECT_EQ(imap[7], 2);
  EXPECT_EQ(imap[12], 0);
}

TEST(TestSegmentMap, SameValue) {
  SegmentMap<int, int> imap(0);
  imap.Add(10, 20, 5);
  imap.Add(15, 25, 5);
  EXPECT_EQ(imap[12], 5);
  EXPECT_EQ(imap[22], 5);

  imap.Add(0, 100, 5);
  EXPECT_EQ(imap[50], 5);
}

TEST(TestSegmentMap, NegativeKeys) {
  SegmentMap<int, double> imap(0.0);
  imap.Add(-10, 0, 1.0);
  EXPECT_EQ(imap[-5], 1.0);
  EXPECT_EQ(imap[5], 0.0);

  imap.Add(-20, -15, 2.0);
  EXPECT_EQ(imap[-17], 2.0);
  EXPECT_EQ(imap[-12], 0.0);
}

TEST(TestSegmentMap, StringKeys) {
  SegmentMap<std::string, int> imap(0);
  imap.Add("apple", "banana", 1);
  EXPECT_EQ(imap["apricot"], 1);
  EXPECT_EQ(imap["coconut"], 0);

  imap.Add("dog", "elephant", 2);
  EXPECT_EQ(imap["duck"], 2);
  EXPECT_EQ(imap["ant"], 0);
}

TEST(TestSegmentMap, Adjacent) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'B');
  imap.Add(3, 5, 'C');

  EXPECT_EQ(imap.segment_map_.size(), 3);
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[3], 'C');
  EXPECT_EQ(imap[4], 'C');
  EXPECT_EQ(imap[5], 'A');
}

TEST(TestSegmentMap, OverwriteEntireMap) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 5, 'B');
  imap.Add(0, 10, 'C');
  EXPECT_EQ(imap.segment_map_.size(), 2);
  EXPECT_EQ(imap[-1], 'A');
  EXPECT_EQ(imap[0], 'C');
  EXPECT_EQ(imap[1], 'C');
  EXPECT_EQ(imap[9], 'C');
  EXPECT_EQ(imap[10], 'A');
}

TEST(TestSegmentMap, MultipleAssignments) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'B');
  imap.Add(5, 7, 'C');
  imap.Add(2, 6, 'D');

  EXPECT_EQ(imap.segment_map_.size(), 4);
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'D');
  EXPECT_EQ(imap[3], 'D');
  EXPECT_EQ(imap[5], 'D');
  EXPECT_EQ(imap[6], 'C');
  EXPECT_EQ(imap[7], 'A');
}

TEST(TestSegmentMap, BoundaryConditions) {
  SegmentMap<int, char> imap('A');
  imap.Add(0, 10, 'B');
  imap.Add(10, 20, 'C');
  EXPECT_EQ(imap.segment_map_.size(), 3);
  EXPECT_EQ(imap[-1], 'A');
  EXPECT_EQ(imap[0], 'B');
  EXPECT_EQ(imap[9], 'B');
  EXPECT_EQ(imap[10], 'C');
  EXPECT_EQ(imap[19], 'C');
  EXPECT_EQ(imap[20], 'A');
}

TEST(TestSegmentMap, FormMaintainence) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'A');
  EXPECT_TRUE(imap.segment_map_.empty());
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'A');
  EXPECT_EQ(imap[2], 'A');
  EXPECT_EQ(imap[3], 'A');

  imap.Add(1, 3, 'B');
  imap.Add(3, 5, 'B');
  EXPECT_EQ(imap.segment_map_.size(), 2);
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[4], 'B');
  EXPECT_EQ(imap[5], 'A');
}

TEST(TestSegmentMap, LookupFunctionality) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'B');
  imap.Add(5, 7, 'C');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[3], 'A');
  EXPECT_EQ(imap[5], 'C');
  EXPECT_EQ(imap[6], 'C');
  EXPECT_EQ(imap[7], 'A');
}

TEST(TestSegmentMap, BasicTestIntChar) {
  SegmentMap<int, char> imap('A');
  imap.Add(1, 3, 'B');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'B');
  EXPECT_EQ(imap[3], 'A');
  EXPECT_EQ(imap[100], 'A');

  imap.Add(2, 5, 'C');
  EXPECT_EQ(imap[0], 'A');
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[2], 'C');
  EXPECT_EQ(imap[4], 'C');
  EXPECT_EQ(imap[5], 'A');
}

TEST(TestSegmentMap, BasicTestStringString) {
  SegmentMap<std::string, std::string> smap("Default");
  smap.Add("Alpha", "Omega", "XYZ");
  EXPECT_EQ(smap[""], "Default");
  EXPECT_EQ(smap["Alpha"], "XYZ");
  EXPECT_EQ(smap["AlphaZ"], "XYZ");
  EXPECT_EQ(smap["Omega"], "Default");
}

TEST(TestSegmentMap, PerformanceWithLargeRanges) {
  SegmentMap<int, std::string> imap("default");

  for (int i = 0; i < 1000; i += 10) {
    imap.Add(i, i + 5, "value-" + std::to_string(i));
  }
  imap.Add(100, 500, "wide-range");

  EXPECT_EQ(imap[50], "value-50");
  EXPECT_EQ(imap[200], "wide-range");
  EXPECT_EQ(imap[600], "value-600");
}

TEST(TestSegmentMap, VeryLargeKeyRange) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(std::numeric_limits<int>::min() + 1,
              std::numeric_limits<int>::max(), "extreme-range");

  EXPECT_EQ(imap[0], "extreme-range");
  EXPECT_EQ(imap[std::numeric_limits<int>::min() + 2], "extreme-range");
  EXPECT_EQ(imap[std::numeric_limits<int>::max() - 1], "extreme-range");
}

TEST(TestSegmentMap, ZeroWidthIntervals) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 50, "base");
  imap.Add(20, 20, "ignored1");
  imap.Add(30, 30, "ignored2");

  EXPECT_EQ(imap[20], "base");
  EXPECT_EQ(imap[30], "base");

  EXPECT_EQ(imap.segment_map_.size(), 2);
}

TEST(TestSegmentMap, BoundaryEdgeCases) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 20, "first");
  imap.Add(20, 30, "second");
  imap.Add(30, 40, "third");

  EXPECT_EQ(imap[19], "first");
  EXPECT_EQ(imap[20], "second");
  EXPECT_EQ(imap[21], "second");
  imap.Add(20, 30, "new-middle");
  EXPECT_EQ(imap[19], "first");
  EXPECT_EQ(imap[20], "new-middle");
  EXPECT_EQ(imap[30], "third");
}

TEST(TestSegmentMap, ChainedOverwrites) {
  SegmentMap<int, std::string> imap("default");
  for (int i = 0; i < 100; i++) {
    imap.Add(i, i + 1, "value-" + std::to_string(i));
  }

  imap.Add(10, 20, "level1");
  imap.Add(5, 25, "level2");
  imap.Add(0, 30, "level3");

  EXPECT_EQ(imap[3], "level3");
  EXPECT_EQ(imap[15], "level3");
  EXPECT_EQ(imap[27], "level3");
  EXPECT_EQ(imap[50], "value-50");
}

TEST(TestSegmentMap, AlternatingValues) {
  SegmentMap<int, std::string> imap("default");
  for (int i = 0; i < 100; i++) {
    imap.Add(i * 2, i * 2 + 1, (i % 2 == 0) ? "even" : "odd");
  }

  EXPECT_EQ(imap[0], "even");
  EXPECT_EQ(imap[2], "odd");
  EXPECT_EQ(imap[3], "default");
  EXPECT_EQ(imap[4], "even");

  imap.Add(0, 100, "uniform");

  for (int i = 0; i < 100; i++) {
    EXPECT_EQ(imap[i], "uniform");
  }
}

TEST(TestSegmentMap, MinMaxBoundaries) {
  SegmentMap<int, std::string> imap("default");
  const int maxInt = std::numeric_limits<int>::max();
  const int minInt = std::numeric_limits<int>::min();

  imap.Add(minInt, 0, "negative");
  imap.Add(0, maxInt, "positive");

  EXPECT_EQ(imap[minInt], "negative");
  EXPECT_EQ(imap[-1], "negative");
  EXPECT_EQ(imap[0], "positive");
  EXPECT_EQ(imap[1], "positive");
  EXPECT_EQ(imap[maxInt - 1], "positive");
}

TEST(TestSegmentMap, EmptyRemovalAndInsertion) {
  SegmentMap<int, std::string> imap("default");
  imap.Add(10, 30, "initial");
  imap.Add(9, 31, "default");

  EXPECT_TRUE(imap.segment_map_.empty());
  EXPECT_EQ(imap.segment_map_.size(), 0);
  imap.Add(10, 30, "new-value");

  EXPECT_EQ(imap[20], "new-value");
  EXPECT_FALSE(imap.segment_map_.empty());
  EXPECT_EQ(imap.segment_map_.size(), 2);
}

TEST(TestSegmentMap, RepeatedAssignmentsSameRange) {
  SegmentMap<int, std::string> imap(std::string("default"));
  for (int i = 0; i < 1000; i++) {
    imap.Add(10, 20, "value-" + std::to_string(i));
  }

  EXPECT_EQ(imap[15], "value-999");
  EXPECT_EQ(imap.segment_map_.size(), 2);
}

TEST(TestSegmentMap, VectorValues) {
  SegmentMap<int, std::vector<int>> vector_map(std::vector<int>{});

  std::vector<int> v1{1, 2, 3};
  std::vector<int> v2{4, 5, 6};

  vector_map.Add(10, 20, v1);
  vector_map.Add(20, 30, v2);

  EXPECT_EQ(vector_map[15], v1);
  EXPECT_EQ(vector_map[25], v2);
}

TEST(TestSegmentMap, MultiLayeredAssignments) {
  SegmentMap<int, std::string> imap(std::string("default"));
  imap.Add(0, 100, std::string("layer1"));

  for (int i = 0; i < 10; i++) {
    imap.Add(i * 10, (i + 1) * 10, "layer2-segment" + std::to_string(i));
  }

  imap.Add(5, 25, "layer3-a");
  imap.Add(35, 55, "layer3-b");
  imap.Add(65, 85, "layer3-c");
  imap.Add(30, 70, "layer4");

  EXPECT_EQ(imap[3], "layer2-segment0");
  EXPECT_EQ(imap[15], "layer3-a");
  EXPECT_EQ(imap[40], "layer4");
  EXPECT_EQ(imap[75], "layer3-c");
  EXPECT_EQ(imap[95], "layer2-segment9");
}

TEST(TestSegmentMap, Representation) {
  SegmentMap<int, char> imap('A');

  imap.Add(1, 5, 'B');
  imap.Add(5, 10, 'C');
  imap.Add(10, 15, 'B');
  imap.Add(15, 20, 'A');

  ASSERT_EQ(imap.segment_map_.size(), 4);
  EXPECT_EQ(imap[1], 'B');
  EXPECT_EQ(imap[5], 'C');
  EXPECT_EQ(imap[10], 'B');
}

TEST(TestSegmentMap, Performance) {
  SegmentMap<int, char> imap('A');

  for (int i = 0; i < 1000000; i += 2) {
    imap.Add(i, i + 1, 'B');
  }

  ASSERT_EQ(imap.segment_map_.size(), 1000000);
  for (int i = 0; i < 1000000; i += 2) {
    EXPECT_EQ(imap[i], 'B');
    EXPECT_EQ(imap[i + 1], 'A');
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}