#include <gtest/gtest.h>

TEST(NullptrTest, IsSameAsNull_Not) { 
    auto IsSameAsNull = std::is_same<decltype(NULL), decltype(nullptr)>::value; 
    EXPECT_FALSE(IsSameAsNull);
}