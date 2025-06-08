#ifndef TWO_SUM_HPP
#define TWO_SUM_HPP

#include <cstdint>
#include <vector>
#include <unordered_map>

inline std::vector<std::int32_t> TwoSum(const std::vector<std::uint32_t>& nums, std::uint32_t target) {
  std::unordered_map<std::uint32_t, std::int32_t> map_num_to_index;
	for (std::int32_t i = 0; i < static_cast<std::int32_t>(nums.size()); ++i) {
    auto it = map_num_to_index.find(target - nums[i]);
          if (it != map_num_to_index.end()) {
			return {it->second, i};
		}
          map_num_to_index[nums[i]] = i;
	}
	return {};
} 

#endif  // !TWO_SUM_HPP
