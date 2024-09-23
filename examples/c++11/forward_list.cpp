#include <gtest/gtest.h>

#include <forward_list>

TEST(ForwardList, ASinglyLinkedList) {
  std::forward_list<int> list = {1, 2, 3, 4};

  EXPECT_FALSE(list.empty());
  EXPECT_EQ(5, *list.insert_after(list.cbegin(), 5));
}