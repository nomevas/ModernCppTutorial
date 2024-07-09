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