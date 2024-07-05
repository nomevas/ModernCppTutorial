#include <gtest/gtest.h>
#include <tuple>

template <class... Ts>
auto FunctionThatReturnsMultipleValues(Ts... args) {
    return std::make_tuple(args...);
}

TEST(Tuple, FunctionThatReturnsMultipleValues_storeResultInLocalVariables) { 
    auto [integer, string, number] = FunctionThatReturnsMultipleValues(1, "test", 2.0);
    EXPECT_EQ(1, integer);
    EXPECT_STREQ("test", string);
    EXPECT_EQ(2.0, number);
}

TEST(Tuple, FunctionThatReturnsMultipleValues_reuseExistingVariables) { 
    int integer = 0;
    const char* string = nullptr;
    double number = 0;
    std::tie(integer, string, number) = FunctionThatReturnsMultipleValues(1, "test", 2.0);
    EXPECT_EQ(1, integer);
    EXPECT_STREQ("test", string);
    EXPECT_EQ(2.0, number);
}