#ifndef DIJKSTRASHORTESTPATH_HPP
#define DIJKSTRASHORTESTPATH_HPP

#include <limits>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

struct DijkstraNode {
  int distance{0};
  int node{0};
};

struct DijkstraNodeComparer {
  bool operator()(const DijkstraNode& a, const DijkstraNode& b) const {
    return a.distance > b.distance;
  }
};

auto HasNegativeValues(const std::vector<std::vector<DijkstraNode>>& graph)
    -> bool {
  for (const auto& edges : graph) {
    for (const auto& edge : edges) {
      if (edge.node < 0) return true;
    }
  }
  return false;
}

/// <summary>
/// Dijkstra Shortest path
/// </summary>
/// <param name="graph">Node Graph</param>
/// <param name="start">Start Node</param>
/// <returns>Vector of distances</returns>
auto Dijkstra(const std::vector<std::vector<DijkstraNode>>& graph,
              int start) -> std::optional<std::vector<int>> {
  int n = graph.size();

  if (start < 0 || start >= n) {
    return std::nullopt;
  }

  if (HasNegativeValues(graph)) return std::nullopt;

  std::vector<int> dist(n, std::numeric_limits<int>::max());

  dist[start] = 0;

  std::priority_queue<DijkstraNode, std::vector<DijkstraNode>,
                      DijkstraNodeComparer>
      pq;
  pq.push({0, start});

  while (!pq.empty()) {
    int current_dist = pq.top().distance;
    int node = pq.top().node;
    pq.pop();

    if (current_dist > dist[node]) continue;

    for (const auto& edge : graph[node]) {
      int d = edge.distance;
      int n = edge.node;
      if (dist[node] + n < dist[d]) {
        dist[d] = dist[node] + n;
        pq.push({dist[d], d});
      }
    }
  }
  return dist;
}

#endif  // DIJKSTRASHORTESTPATH_HPP