#include <gtest/gtest.h>

#include <unordered_map>

TEST(UnorderedMap, HashBasedMap_O1Lookup) {
  std::unordered_map<int, int> unordered_map = {{1, 2}, {3, 4}};

  EXPECT_FALSE(unordered_map.empty());
  EXPECT_EQ(2, unordered_map[1]);
  EXPECT_EQ(0, unordered_map.count(2));
  EXPECT_EQ(4, unordered_map[3]);
}