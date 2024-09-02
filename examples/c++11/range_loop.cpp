// C++11 introduces a range-based iterative method.

#include <gtest/gtest.h>

TEST(RangeLoop, RangeBasedLoop_Vector) {
  std::vector<int> vec = {1, 2, 3, 4};
  int sum = 0;
  for (auto&& item : vec) {
    sum += item;
  }
  EXPECT_EQ(10, sum);
}

TEST(RangeLoop, RangeBasedLoop_Map) {
  std::map<int, int> dict = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
  int sum = 0;
  for (auto&& item : dict) {
    sum += item.first + item.second;
  }
  EXPECT_EQ(20, sum);
}

TEST(RangeLoop, BenefitOfUsingForwardReferences) {
  std::vector<bool> v(10, false);

  // for (auto& e : v) {    <- non-const lvalue reference to type 'std::_Bit_reference' cannot bind to a temporary of type 'std::_Bit_iterator::reference' (aka
  // 'std::_Bit_reference')
  //   e = true;
  // }

  for (auto e : v) {  // e is always a new object, copy of the proxy returned by vector iterator
    e = true;
  }
  EXPECT_TRUE(v[0]);

  for (auto&& e : v) {  // it uses r-value reference created by the vector iterator.
    e = false;
  }
  EXPECT_FALSE(v[0]);
}