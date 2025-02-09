#include "DijkstraShortestPath.hpp"
#include "GTestCommon.hpp"

TEST(DijkstraShortestPath, EmptyGraph) {
  std::vector<std::vector<DijkstraNode>> graph = {};
  auto result = Dijkstra(graph, 0);
  EXPECT_FALSE(result.has_value());
}

TEST(DijkstraShortestPath, SingleNode) {
  std::vector<std::vector<DijkstraNode>> graph = {{}};
  auto result = Dijkstra(graph, 0);

  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0};
  EXPECT_EQ(result.value(), expected);
}

TEST(DijkstraShortestPath, InvalidStartNode) {
  std::vector<std::vector<DijkstraNode>> graph = 
  {
      {{1, 2}}, 
      {}
  };
  auto result = Dijkstra(graph, -1);
  EXPECT_FALSE(result.has_value());
}

TEST(DijkstraShortestPath, BasicGraph) {
  std::vector<std::vector<DijkstraNode>> graph = {
      {{1, 4}, {2, 1}}, 
      {{3, 1}}, 
      {{1, 2}, {3, 5}}, 
      {{4, 3}}, 
      {}
  };
  auto result = Dijkstra(graph, 0);

  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0, 3, 1, 4, 7};
  EXPECT_EQ(result.value(), expected);
}

TEST(DijkstraShortestPath, DisconnectedGraph) {
  std::vector<std::vector<DijkstraNode>> graph = {{{1, 2}}, {}, {{3, 4}}, {}};
  auto result = Dijkstra(graph, 0);

  ASSERT_TRUE(result.has_value());
  std::vector<int> expected{0, 2, std::numeric_limits<int>::max(),
                            std::numeric_limits<int>::max()};
  EXPECT_EQ(result.value(), expected);
}

TEST(DijkstraShortestPath, GraphWithNegativeValues) {
  std::vector<std::vector<DijkstraNode>> graph = {
      {{1, 4}, {2, -1}}, 
      {{3, 1}}, 
      {{1, 2}, {3, 5}}, 
      {{4, 3}}, 
      {}
  };
  auto result = Dijkstra(graph, 0);
  EXPECT_FALSE(result.has_value());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}