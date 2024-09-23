#include <gtest/gtest.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

TEST(Atomic, Wait_ReplaceConditionalVariables) {
  std::atomic<bool> ready{false};

  auto future = std::async(std::launch::async, [&]() {
    std::this_thread::sleep_for(10ms);
    ready = true;
    ready.notify_one();
  });

  EXPECT_TRUE(ready.wait(true));
  EXPECT_TRUE(ready);
}