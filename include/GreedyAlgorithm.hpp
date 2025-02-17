#ifndef GREEDYALGORITHM_HPP
#define GREEDYALGORITHM_HPP

#include <algorithm>
#include <functional>
#include <queue>
#include <ranges>
#include <vector>


struct TimeInterval {
  int start;
  int end;
};

auto MinMeetingRoom(std::vector<TimeInterval>& intervals) -> int {
  if (intervals.empty()) return 0;

  std::ranges::sort(intervals, [](const TimeInterval& a, const TimeInterval& b) {
    return a.start < b.start;
  });

  std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
  if (!intervals.empty()) { 
    min_heap.push(intervals[0].end);
  }

  for (size_t i = 1; i < intervals.size(); ++i) {  
    int start = intervals[i].start;
    int end = intervals[i].end;
    if (start >= min_heap.top()) {
      min_heap.pop();
    }
    min_heap.push(end);
  }


  return min_heap.size();
}

#endif  // GREEDYALGORITHM_HPP