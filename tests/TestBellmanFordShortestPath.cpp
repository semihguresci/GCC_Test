#include "BellmanFordShortestPath.hpp"
#include "GTestCommon.hpp"

TEST(BellmanFordShortestPath, EmptyGraph) {
  std::vector<BellmanFordEdge> graph = {};
  int n = 0;
  auto result = BellmanFord(graph, n, 0);
  EXPECT_FALSE(result.has_value());
}

TEST(BellmanFordShortestPath, InvalidStartNode) {
  std::vector<BellmanFordEdge> graph = {{0, 1, 2}};
  int n = 2;
  auto result = BellmanFord(graph, n, -1);
  EXPECT_FALSE(result.has_value());
}

TEST(BellmanFordShortestPath, SingleNodeGraph) {
  std::vector<BellmanFordEdge> graph = {};
  int n = 1;
  auto result = BellmanFord(graph, n, 0);
  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0};
  EXPECT_EQ(result.value(), expected);
}

TEST(BellmanFordShortestPath, DisconnectedGraph) {
  std::vector<BellmanFordEdge> graph = {{0, 1, 2}, {2, 3, 4}};
  int n = 4;
  auto result = BellmanFord(graph, n, 0);
  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0, 2, std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max()};
  EXPECT_EQ(result.value(), expected);
}

TEST(BellmanFordShortestPath, GraphWithNegativeCycle) {
  std::vector<BellmanFordEdge> graph = {{0, 1, 1}, {1, 2, -1}, {2, 0, -1}};
  int n = 3;
  auto result = BellmanFord(graph, n, 0);
  EXPECT_FALSE(result.has_value());
}

TEST(BellmanFordShortestPath, GraphWithNegativeWeights) {
  std::vector<BellmanFordEdge> graph = {{0, 1, 4}, {0, 2, 1}, {1, 3, -1},
                                        {2, 1, 2}, {2, 3, 5}, {3, 4, 3}};
  int n = 5;
  auto result = BellmanFord(graph, n, 0);
  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0, 3, 1, 2, 5};
  EXPECT_EQ(result.value(), expected);
}

TEST(BellmanFordShortestPath, BasicGraph) {
  std::vector<BellmanFordEdge> graph = {{0, 1, 4}, {0, 2, 1}, {1, 3, 1},
                                        {2, 1, 2}, {2, 3, 5}, {3, 4, 3}};
  int n = 5;
  auto result = BellmanFord(graph, n, 0);
  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0, 3, 1, 4, 7};
  EXPECT_EQ(result.value(), expected);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}