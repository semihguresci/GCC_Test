#include <algorithm>
#include <exception>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class ValueRangeMap {
 private:
  std::map<int, std::pair<int, std::string>> ranges;
  void MergeWithNeighbors(
      std::map<int, std::pair<int, std::string>>::iterator it) {
    if (it == ranges.end()) return;

    const auto& current_value = it->second.second;
    auto start_pos = it->first;
    auto end_pos = it->second.first;

    // merge backwards
    if (it != ranges.begin()) {
      auto prev = std::prev(it);
      // if previous  range has the same value or touches or overlaps
      if (prev->second.second == current_value &&
          prev->second.first + 1 >= start_pos) {
        // merge them
        start_pos = prev->first;
        end_pos = std::max(prev->second.first, end_pos);

        // erase booth intervals
        it = ranges.erase(it);
        ranges.erase(prev);

        it = ranges.insert({start_pos, {end_pos, current_value}}).first;
      }
    }
    // merge forward
    auto next = std::next(it);
    if (next != ranges.end()) {
      if (next->second.second == current_value &&
          it->second.first + 1 >= next->first) {
        // merge them
        int new_start = it->first;
        int new_end = std::max(it->second.first, next->second.first);

        ranges.erase(it);
        ranges.erase(next);

        it = ranges.insert({new_start, {new_end, current_value}}).first;
      }
    }
  }

 public:
  void Add(int start, int end, const std::string& value) {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be <= end");
    }

    auto it = ranges.lower_bound(start);
    if (it != ranges.begin()) {
      auto prev = std::prev(it);
      if (prev->second.first >= start - 1) {
        it = prev;
      }
    }
    std::vector<std::tuple<int, int, std::string>> to_add;

    while (it != ranges.end() && it->first <= end + 1) {
      int existing_start = it->first;
      int existing_end = it->second.first;
      std::string existing_value = it->second.second;

      if (existing_end >= start && existing_start <= end) {
        if (existing_start < start) {
          to_add.push_back({existing_start, start - 1, existing_value});
        }
        if (existing_end > end) {
          to_add.push_back({end + 1, existing_end, existing_value});
        }

        it = ranges.erase(it);
      } else {
        ++it;
      }
    }

    auto inserted_it = ranges.insert({start, {end, value}}).first;

    for (auto& info : to_add) {
      auto s = std::get<0>(info);
      auto e = std::get<1>(info);
      auto v = std::get<2>(info);
      ranges[s] = {e, v};
    }
    MergeWithNeighbors(inserted_it);

    inserted_it = ranges.lower_bound(start);

    if (inserted_it == ranges.end() || inserted_it->first != start) {
      if (inserted_it != ranges.begin()) {
        --inserted_it;
      }
    }
    if (inserted_it != ranges.end()) {
      MergeWithNeighbors(inserted_it);
    }
  }

  // Removes coverage in the interval [start, end].
  void Remove(int start, int end) {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be <= end");
    }

    // Find the first interval that might overlap [start, end].
    // Move back one interval if necessary, to catch partial overlaps.
    auto it = ranges.lower_bound(start);
    if (it != ranges.begin()) {
      auto prev = std::prev(it);
      if (prev->second.first >= start) {
        it = prev;
      }
    }

    std::vector<std::tuple<int, int, std::string>> leftover;

    while (it != ranges.end() && it->first <= end) {
      int existing_start = it->first;
      int existing_end = it->second.first;
      std::string existing_value = it->second.second;

      if (existing_end < start) {
        ++it;
        continue;
      }
      if (existing_start > end) {
        break;
      }

      it = ranges.erase(it);

      if (existing_start < start) {
        int leftover_start = existing_start;
        int leftover_end = start - 1;
        if (leftover_start <= leftover_end) {
          leftover.push_back({leftover_start, leftover_end, existing_value});
        }
      }

      if (existing_end > end) {
        int leftover_start = end + 1;
        int leftover_end = existing_end;
        if (leftover_start <= leftover_end) {
          leftover.push_back({leftover_start, leftover_end, existing_value});
        }
      }
    }

    for (auto& info : leftover) {
      int s = std::get<0>(info);
      int e = std::get<1>(info);
      std::string v = std::get<2>(info);
      ranges[s] = {e, v};
    }
  }

  void Update(int start, int end, const std::string& value) {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be <= end");
    }

    Add(start, end, value);
  }

  auto Query(int point) -> std::string {
    auto it = ranges.upper_bound(point);
    if (it != ranges.begin()) {
      --it;
      if (it->second.first >= point) {
        return it->second.second;
      }
    }
    return "";
  }

  auto QueryRange(int start, int end) -> std::pair<bool, std::string> {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be <= end");
    }

    auto it = ranges.upper_bound(end);
    if (it == ranges.begin()) {
      return {false, ""};
    }
    --it;

    if (it->first <= start && it->second.first >= end) {
      return {true, it->second.second};
    }
    return {false, ""};
  }

  auto GetRanges() const -> std::vector<std::tuple<int, int, std::string>> {
    std::vector<std::tuple<int, int, std::string>> range_list;
    for (auto& entry : ranges) {
      range_list.push_back(
          {entry.first, entry.second.first, entry.second.second});
    }
    return range_list;
  }

  bool operator==(const ValueRangeMap& other) const {
    return this->GetRanges() == other.GetRanges();
  }
};