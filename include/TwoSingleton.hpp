/*
Implement the singleton pattern with a twist. First, instead of storing one
instance, store two instances. And in every even call of getInstance(), return
the first instance and in every odd call of getInstance(), return the second
instance.
*/

#ifndef TWO_SINGLETON_HPP
#define TWO_SINGLETON_HPP
#include <atomic>
#include <memory>
#include <mutex>
class TwoSingleton {
 public:
  TwoSingleton(const TwoSingleton&) = delete;
  TwoSingleton& operator=(const TwoSingleton&) = delete;
  TwoSingleton(const TwoSingleton&&) = delete;
  TwoSingleton& operator=(const TwoSingleton&&) = delete;

  static TwoSingleton& getInstance() {
    init_once();
    const auto count = call_count_.fetch_add(1, std::memory_order_relaxed);
    const auto call__number = count + 1;
    return (call__number % 2 == 1) ? *instance1_ : *instance2_;
  }
  int id() const { return id_; }

 private:
  explicit TwoSingleton(int id) : id_(id) {}

 static void init_once() {
    std::call_once(init_flag_, [] {
      instance1_.reset(new TwoSingleton(1));
      instance2_.reset(new TwoSingleton(2));
    });
  }

 private:
  static inline std::unique_ptr<TwoSingleton> instance1_;
  static inline std::unique_ptr<TwoSingleton> instance2_;
  static inline std::once_flag init_flag_;
  static inline std::atomic<std::uint64_t> call_count_{0};
  int id_;
};

#endif  // !TWO_SINGLETON_HPP