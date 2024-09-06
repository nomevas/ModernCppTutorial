#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <unordered_map>
#include <unordered_set>

TEST(Containers, Array) {
  // fixed size, you dont need to think about runtime performance/space overhead related with std::vector
  std::array<int, 4> arr = {1, 2, 3, 4};

  EXPECT_EQ(4, arr.size());
  EXPECT_FALSE(arr.empty());
  std::ranges::sort(arr, std::greater<int>());
  EXPECT_EQ(4, arr[0]);
}

TEST(Containers, ForwardList) {
  // a singly linked list
  std::forward_list<int> list = {1, 2, 3, 4};

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(5, *list.insert_after(list.cbegin(), 5));
}

TEST(Containers, UnorderedMap) {
  // hash based map container
  std::unordered_map<int, int> unordered_map = {{1, 2}, {3, 4}};

  EXPECT_FALSE(unordered_map.empty());
  EXPECT_EQ(2, unordered_map[1]);
  EXPECT_EQ(0, unordered_map.count(2));
  EXPECT_EQ(4, unordered_map[3]);
}

TEST(Containers, UnorderedSet) {
  // hash based set container
  std::unordered_set<int> unordered_set = {1, 2, 3, 4};

  EXPECT_FALSE(unordered_set.empty());
  EXPECT_EQ(1, unordered_set.count(2));
}