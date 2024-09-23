#include <gtest/gtest.h>

#include <unordered_set>

TEST(UnorderedSet, HashBasedSet_O1Lookup) {
  // hash based set container
  std::unordered_set<int> unordered_set = {1, 2, 3, 4};

  EXPECT_FALSE(unordered_set.empty());
  EXPECT_EQ(1, unordered_set.count(2));
}