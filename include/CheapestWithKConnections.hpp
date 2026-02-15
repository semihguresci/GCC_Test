/*
You are given a huge list of airline ticket prices between different cities
around the world on a given day. These are all direct flights. Each element in
the list has the format (source_city, destination, price). Consider a user who
is willing to take up to k connections from their origin city A to their
destination B. Find the cheapest fare possible for this journey and print the
itinerary for that journey. For example, our traveler wants to go from JFK to
LAX with up to 3 connections, and our input flights are as follows: [ ('JFK',
'ATL', 150), ('ATL', 'SFO', 400), ('ORD', 'LAX', 200), ('LAX', 'DFW', 80),
('JFK', 'HKG', 800), ('ATL', 'ORD', 90), ('JFK', 'LAX', 500), ] Due to some
improbably low flight prices, the cheapest itinerary would be JFK -> ATL -> ORD
-> LAX, costing $440.
*/

#ifndef CHEAPESTWITHKCONNECTIONS_HPP
#define CHEAPESTWITHKCONNECTIONS_HPP
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

class CheapestWithKConnections {
 public:
  struct Edge {
    int to;
    int w;
  };

  struct Prev {
    int prev_city = -1;
    int prev_used = -1;
  };

  // Returns {min_cost, itinerary}. If not found: {INF, {}}
  std::pair<long long, std::vector<std::string>> FindCheapestWithKConnections(
      const std::vector<std::tuple<std::string, std::string, int>>& flights,
      const std::string& A, const std::string& B, int k) {
    const long long INF = std::numeric_limits<long long>::max();

    const int max_edges = k + 1;

    std::unordered_map<std::string, int> city_to_id;
    city_to_id.reserve(flights.size() * 2);

    auto get_city_id = [&](const std::string& city) -> int {
      auto it = city_to_id.find(city);
      if (it != city_to_id.end()) return it->second;
      int nid = static_cast<int>(city_to_id.size());
      city_to_id.emplace(city, nid);
      return nid;
    };

    for (const auto& [from, to, w] : flights) {
      (void)w;
      get_city_id(from);
      get_city_id(to);
    }

    if (!city_to_id.count(A) || !city_to_id.count(B)) {
      return {INF, {}};
    }

    const int n = static_cast<int>(city_to_id.size());

    std::vector<std::string> name(n);
    for (const auto& kv : city_to_id) {
      name[kv.second] = kv.first;
    }

    std::vector<std::vector<Edge>> graph(n);
    for (const auto& [from, to, w] : flights) {
      graph[city_to_id[from]].push_back(Edge{city_to_id[to], w});
    }

    const int start = city_to_id[A];
    const int end = city_to_id[B];

    // dist[used_edges][city]
    std::vector<std::vector<long long>> dist(max_edges + 1,
                                             std::vector<long long>(n, INF));
    std::vector<std::vector<Prev>> prev(max_edges + 1, std::vector<Prev>(n));

    using State = std::tuple<long long, int, int>;  // (cost, city, used_edges)
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;

    dist[0][start] = 0;
    pq.push({0LL, start, 0});

    while (!pq.empty()) {
      auto [cost, city, used] = pq.top();
      pq.pop();

      if (cost != dist[used][city]) continue;
      if (used == max_edges) continue;

      for (const auto& e : graph[city]) {
        const int next_city = e.to;
        const int next_used = used + 1;

        if (cost > INF - static_cast<long long>(e.w)) continue;

        const long long next_cost = cost + static_cast<long long>(e.w);

        if (next_cost < dist[next_used][next_city]) {
          dist[next_used][next_city] = next_cost;
          prev[next_used][next_city] = Prev{city, used};
          pq.push({next_cost, next_city, next_used});
        }
      }
    }

    long long best = INF;
    int best_used = -1;
    for (int used = 0; used <= max_edges; ++used) {
      if (dist[used][end] < best) {
        best = dist[used][end];
        best_used = used;
      }
    }

    if (best == INF) {
      return {INF, {}};
    }

    std::vector<int> path_ids;
    int cur_city = end;
    int cur_used = best_used;

    while (!(cur_city == start && cur_used == 0)) {
      path_ids.push_back(cur_city);
      const Prev& p = prev[cur_used][cur_city];
      if (p.prev_city == -1) {  
        return {best, {}};
      }
      cur_city = p.prev_city;
      cur_used = p.prev_used;
    }
    path_ids.push_back(start);
    std::reverse(path_ids.begin(), path_ids.end());

    std::vector<std::string> path;
    path.reserve(path_ids.size());
    for (int cid : path_ids) path.push_back(name[cid]);

    return {best, path};
  }
};

#endif  // CHEAPESTWITHKCONNECTIONS_HPP