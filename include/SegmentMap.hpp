#ifndef SEGMENTMAP_HPP
#define SEGMENTMAP_HPP

#include <map>

template <typename KeyType, typename ValueType>
class SegmentMap {
 public:
  ValueType default_value_;
  std::map<KeyType, ValueType> segment_map_;
  SegmentMap(const ValueType& val) : default_value_(val) {}

  void Add(const KeyType& begin, const KeyType& end, const ValueType& value) {
    if (!(begin < end)) {
      return;
    }

    auto it_low = segment_map_.lower_bound(begin);
    auto it_up = segment_map_.lower_bound(end);

    auto get_value_at = [&](const KeyType& key) -> ValueType {
      auto it = segment_map_.lower_bound(key);
      return (it != segment_map_.begin()) ? std::prev(it)->second : default_value_;
    };

    auto val_before = get_value_at(begin);
    auto val_after = get_value_at(end);

    segment_map_.erase(it_low, it_up);

    auto insert_or_merge = [&](const KeyType& key, const ValueType& val_to_insert) {
      auto it_insert = segment_map_.emplace_hint(segment_map_.lower_bound(key), key, val_to_insert);
      if (it_insert != segment_map_.begin() && std::prev(it_insert)->second == val_to_insert) {
        segment_map_.erase(it_insert);
      }
    };

    if (val_before != value) {
      insert_or_merge(begin, value);
    }

    if (val_after != value) {
      insert_or_merge(end, val_after);
    }

    if (!segment_map_.empty() && segment_map_.begin()->second == default_value_) {
      segment_map_.erase(segment_map_.begin());
    }
  }

  const ValueType& operator[](const KeyType& key) const {
    auto it = segment_map_.upper_bound(key);
    if (it == segment_map_.begin()) {
      return default_value_;
    } else {
      return std::prev(it)->second;
    }
  }
};

#endif  // SEGMENTMAP_HPP