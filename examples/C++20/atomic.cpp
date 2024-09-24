#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

TEST(Atomic, Wait_ReplaceConditionalVariables) {
  std::atomic<bool> ready{false};
  bool any_other_variable = false;

  auto future = std::async(std::launch::async, [&]() {
    std::this_thread::sleep_for(10ms);
    ready = true;
    any_other_variable = true;
    ready.notify_one();
  });

  ready.wait(false);
  EXPECT_TRUE(ready);
  EXPECT_TRUE(any_other_variable) << "std::memory_order::seq_cst is used, all varaibles written by the other thread should be synced with the main thread";
}