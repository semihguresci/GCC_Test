#ifndef BELLMANFORTSHORTESTPATH_HPP
#define BELLMANFORTSHORTESTPATH_HPP

#include <limits>
#include <optional>
#include <vector>

struct BellmanFordEdge {
  int u{0};
  int v{0};
  int weight{0};
};

auto BellmanFord(const std::vector<BellmanFordEdge>& edges, int n,
                 int start) -> std::optional<std::vector<int>> {
  if (start < 0 || start >= n) return std::nullopt;

  std::vector<int> dist(n, std::numeric_limits<int>::max());
  dist[start] = 0;

  for (int i = 1; i < n; ++i) {
    for (const auto& edge : edges) {
      int u = edge.u;
      int v = edge.v;
      int weight = edge.weight;

      if (dist[u] != std::numeric_limits<int>::max() &&
          dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
      }
    }
  }

  // check for negative weights
  for (const auto& edge : edges) {
    int u = edge.u;
    int v = edge.v;
    int weight = edge.weight;

    if (dist[u] != std::numeric_limits<int>::max() &&
        dist[u] + weight < dist[v]) {
      return std::nullopt;
    }
  }

  return dist;
}

#endif  // BELLMANFORTSHORTESTPATH_HPP