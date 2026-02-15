#include <limits>
#include <string>
#include <tuple>
#include <vector>

#include "CheapestWithKConnections.hpp"
#include "GTestCommon.hpp"

TEST(CheapestWithKConnections, ExampleFromPrompt_K3) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"JFK", "ATL", 150}, {"ATL", "SFO", 400}, {"ORD", "LAX", 200},
      {"LAX", "DFW", 80},  {"JFK", "HKG", 800}, {"ATL", "ORD", 90},
      {"JFK", "LAX", 500},
  };

  auto [cost, path] =
      solver.FindCheapestWithKConnections(flights, "JFK", "LAX", 3);

  EXPECT_EQ(cost, 440);
  ASSERT_EQ(path.size(), 4u);
  EXPECT_EQ(path[0], "JFK");
  EXPECT_EQ(path[1], "ATL");
  EXPECT_EQ(path[2], "ORD");
  EXPECT_EQ(path[3], "LAX");
}

TEST(CheapestWithKConnections, DirectFlightChosenWhenCheaper) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "B", 50},
      {"A", "C", 10},
      {"C", "B", 100},
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 1);

  EXPECT_EQ(cost, 50);
  ASSERT_EQ(path.size(), 2u);
  EXPECT_EQ(path[0], "A");
  EXPECT_EQ(path[1], "B");
}

TEST(CheapestWithKConnections, ConnectionBeatsDirectWhenAllowed) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "B", 100},
      {"A", "C", 10},
      {"C", "B", 20},
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 1);

  EXPECT_EQ(cost, 30);
  ASSERT_EQ(path.size(), 3u);
  EXPECT_EQ(path[0], "A");
  EXPECT_EQ(path[1], "C");
  EXPECT_EQ(path[2], "B");
}

TEST(CheapestWithKConnections, NotAllowedWhenKTooSmall) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "C", 10},
      {"C", "B", 20},
      {"A", "B", 1000},
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 0);

  EXPECT_EQ(cost, 1000);
  ASSERT_EQ(path.size(), 2u);
  EXPECT_EQ(path[0], "A");
  EXPECT_EQ(path[1], "B");
}

TEST(CheapestWithKConnections, NoRouteWithinK) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "C", 10},
      {"C", "D", 20},
      {"D", "B", 30},
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 1);

  EXPECT_EQ(cost, std::numeric_limits<long long>::max());
  EXPECT_TRUE(path.empty());
}

TEST(CheapestWithKConnections, MissingCitiesReturnNotFound) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"X", "Y", 5},
  };

  auto [cost1, path1] =
      solver.FindCheapestWithKConnections(flights, "A", "Y", 3);
  EXPECT_EQ(cost1, std::numeric_limits<long long>::max());
  EXPECT_TRUE(path1.empty());

  auto [cost2, path2] =
      solver.FindCheapestWithKConnections(flights, "X", "B", 3);
  EXPECT_EQ(cost2, std::numeric_limits<long long>::max());
  EXPECT_TRUE(path2.empty());
}

TEST(CheapestWithKConnections, MultipleOptionsPickCheapest) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "B", 200}, {"A", "C", 50}, {"C", "B", 60},
      {"A", "D", 10},  {"D", "E", 10}, {"E", "B", 10},
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 2);

  EXPECT_EQ(cost, 30);
  ASSERT_EQ(path.size(), 4u);
  EXPECT_EQ(path[0], "A");
  EXPECT_EQ(path[1], "D");
  EXPECT_EQ(path[2], "E");
  EXPECT_EQ(path[3], "B");
}

TEST(CheapestWithKConnections, TieCostAcceptEitherValidCheapestPath) {
  CheapestWithKConnections solver;

  std::vector<std::tuple<std::string, std::string, int>> flights = {
      {"A", "C", 10},
      {"C", "B", 20},  
      {"A", "D", 15},
      {"D", "B", 15},  
  };

  auto [cost, path] = solver.FindCheapestWithKConnections(flights, "A", "B", 1);

  EXPECT_EQ(cost, 30);
  ASSERT_GE(path.size(), 2u);
  EXPECT_EQ(path.front(), "A");
  EXPECT_EQ(path.back(), "B");

  const bool is_acb = (path.size() == 3 && path[1] == "C");
  const bool is_adb = (path.size() == 3 && path[1] == "D");
  EXPECT_TRUE(is_acb || is_adb);
}
