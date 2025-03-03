#include <chrono>

#include "GTestCommon.hpp"
#include "MOsAlgorithm.hpp"

TEST(MOsAlgorithm, BasicTest) {
  std::vector<int> arr = {1, 1, 2, 1, 3, 4, 5, 2, 8};
  std::vector<MosQuery> queries = {{0, 4}, {1, 3}, {2, 6}};

  std::vector<int> expected_results = {2, 3, 5};
  std::vector<int> results = MosAlgorithm().Process(arr, queries);

  ASSERT_EQ(results.size(), expected_results.size());
  for (size_t i = 0; i < results.size(); i++) {
    EXPECT_EQ(results[i], expected_results[i]) << "Mismatch at index " << i;
  }
}

TEST(MOsAlgorithm, EmptyArrayTest) {
  std::vector<int> arr = {};
  std::vector<MosQuery> queries = {{0, 0}};
  std::vector<int> expected_results = {0};

  MosAlgorithm mos;
  std::vector<int> results = mos.Process(arr, queries);

  ASSERT_EQ(results.size(), expected_results.size());
  for (size_t i = 0; i < results.size(); i++) {
    EXPECT_EQ(results[i], expected_results[i]) << "Mismatch at index " << i;
  }
}

TEST(MOsAlgorithm, SingleElementArrayTest) {
  std::vector<int> arr = {42};
  std::vector<MosQuery> queries = {{0, 0}};
  std::vector<int> expected_results = {1};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);

  ASSERT_EQ(results.size(), expected_results.size());
  for (size_t i = 0; i < results.size(); i++) {
    EXPECT_EQ(results[i], expected_results[i]) << "Mismatch at index " << i;
  }
}

TEST(MOsAlgorithm, AllElementsSameTest) {
  std::vector<int> arr = {5, 5, 5, 5, 5};
  std::vector<MosQuery> queries = {{0, 4}, {1, 3}, {2, 2}};
  std::vector<int> expected_results = {1, 1, 1};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, NonOverlappingQueriesTest) {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<MosQuery> queries = {{0, 2}, {3, 5}, {6, 8}};
  std::vector<int> expected_results = {3, 3, 3};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, OverlappingQueriesTest) {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<MosQuery> queries = {{0, 4}, {2, 6}, {4, 8}};
  std::vector<int> expected_results = {5, 5, 5};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, LargeArrayTest) {
  std::vector<int> arr(100000, 1);
  std::vector<MosQuery> queries = {{0, 99999}, {100, 200}, {500, 600}};
  std::vector<int> expected_results = {1, 1, 1};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, LargeNumberOfQueriesTest) {
  std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<MosQuery> queries;
  for (int i = 0; i < 1000; i++) {
    queries.push_back({0, 8});
  }
  std::vector<int> expected_results(1000, 9);

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, NegativeNumbersTest) {
  std::vector<int> arr = {-1, -2, -3, -1, -2, -3, -4};
  std::vector<MosQuery> queries = {{0, 3}, {2, 5}, {4, 6}};
  std::vector<int> expected_results = {3, 3, 3};

  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  ASSERT_EQ(results, expected_results);
}

TEST(MOsAlgorithm, OutOfBoundQueriesTest) {
  std::vector<int> arr = {1, 2, 3, 4, 5};
  std::vector<MosQuery> queries = {{-1, 2}, {3, 10}};

  EXPECT_THROW(MosAlgorithm().Process(arr, queries), std::out_of_range);
}

TEST(MOsAlgorithm, PerformanceTest) {
  const int ARRAY_SIZE = 1000000;
  const int NUM_QUERIES = 100000;

  std::vector<int> arr(ARRAY_SIZE);
  for (int i = 0; i < ARRAY_SIZE; i++) {
    arr[i] = rand() % 1000;
  }

  std::vector<MosQuery> queries(NUM_QUERIES);
  for (int i = 0; i < NUM_QUERIES; i++) {
    int L = rand() % ARRAY_SIZE;
    int R = rand() % ARRAY_SIZE;
    if (L > R) std::swap(L, R);
    queries[i] = {L, R};
  }

  auto start = std::chrono::high_resolution_clock::now();
  std::vector<int> results = MosAlgorithm().Process(arr, queries);
  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  ASSERT_EQ(results.size(), NUM_QUERIES);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}