#include <algorithm>
#include <map>
#include <stdexcept>
#include <vector>

class RangeMap {
 private:
  std::map<int, int> ranges;  // key start of the range, value end of the range
 public:
  auto AddRange(int start, int end) -> void {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be less than end");
    }

    // Find the first interval that could overlap or be adjacent:
    // lower_bound(start) -> first entry with key >= start
    // but we step back if there's an interval that might extend into [start,
    // end].
    auto it = ranges.lower_bound(start);
    if (it != ranges.begin()) {
      auto prev = std::prev(it);
      // If the previous interval's end is at least start-1, they might merge.
      if (prev->second >= start - 1) {
        it = prev;
      }
    }

    int newStart = start;
    int newEnd = end;

    // Merge all intervals that overlap or are adjacent ([start..end] touches
    // [it->first..it->second])
    while (it != ranges.end() && it->first <= newEnd + 1) {
      // If this interval starts after newStart, we can unify:
      newStart = std::min(newStart, it->first);
      newEnd = std::max(newEnd, it->second);
      it = ranges.erase(it);
    }

    // Finally, insert the merged interval
    ranges[newStart] = newEnd;
  }

  auto RemoveRange(int start, int end) -> void {
    if (start >= end) {
      throw std::invalid_argument("Invalid range: start must be less than end");
    }

    // Find the first interval that could overlap with [start, end].
    // lower_bound(start) returns the first interval with key >= start;
    // but we step back one interval if possible, because
    // an interval that starts before 'start' might still overlap.
    auto it = ranges.lower_bound(start);
    if (it != ranges.begin()) {
      --it;
      // If this interval is strictly to the left (ends before start), move on
      if (it->second < start) {
        ++it;
      }
    }

    // Now process all intervals that overlap [start, end].
    while (it != ranges.end() && it->first < end) {
      // If there's no overlap, move on
      if (it->second <= start) {
        ++it;
        continue;
      }

      // Save the old interval's boundaries
      int oldStart = it->first;
      int oldEnd = it->second;

      // Erase the old interval from the map
      it = ranges.erase(it);

      // If there's a left portion that remains after removal
      // (i.e., [oldStart, start]), store it:
      if (oldStart < start) {
        ranges[oldStart] = std::min(oldEnd, start);
      }

      // If there's a right portion that remains after removal
      // (i.e., [end, oldEnd]), store it:
      if (oldEnd > end) {
        ranges[end] = oldEnd;
      }

      // At this point, it points to the next interval after
      // we erased the old one, so the loop continues.
    }
  }

  auto QueryRange(int start, int end) -> bool {
    if (start > end) {
      throw std::invalid_argument("Invalid range: start must be less than end");
    }
    // Find the first interval whose 'start' is >= 'start'.
    // (lower_bound(start) gives the first element with a key that
    // is not less than 'start'.)
    auto it = ranges.lower_bound(start);
    // If possible, move one interval back, because an interval that begins
    // before 'start' might still fully cover [start, end].
    if (it != ranges.begin()) {
      --it;
      // Now 'it' might point to an interval that starts before 'start'.
      // We check if that interval covers [start, end].

      // Condition for coverage:
      // - it->first <= start
      // - it->second >= end
      if (it->second >= end && it->first <= start) {
        return true;
      }
    }
    return false;
  }

  auto GetRanges() -> std::vector<std::pair<int, int>> {
    std::vector<std::pair<int, int>> range_list;
    for (const auto& [start, end] : ranges) {
      range_list.push_back({start, end});
    }
    return range_list;
  }

  bool operator==(RangeMap& other) {
    return this->GetRanges() == other.GetRanges();
  }
};