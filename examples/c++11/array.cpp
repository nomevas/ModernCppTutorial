#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <unordered_map>
#include <unordered_set>

TEST(Array, FixedSizeContainer_AvoidPerformanceSpaceOverhead) {
  std::array<int, 4> arr = {1, 2, 3, 4};

  EXPECT_EQ(4, arr.size());
  EXPECT_FALSE(arr.empty());
  std::ranges::sort(arr, std::greater<int>());
  EXPECT_EQ(4, arr[0]);
}
