// Before you understand the type alias template, you need to understand the difference between "template" and "type". 
// Carefully understand this sentence: Templates are used to generate types. In traditional C++, typedef can define 
// a new name for the type, but there is no way to define a new name for the template. Because the template is not a type.

#include <gtest/gtest.h>

TEST(UsingAlias, ItIsNotANewType) {
    using IntVector = std::vector<int>;
    IntVector vec = {1, 2, 3};
    static_assert(std::is_same<decltype(vec), std::vector<int>>::value, "type vec == std::vector<int>");
}

int TestFunction(int value) {
    return 5 + 5;
}

TEST(UsingAlias, FuntionPointer) {
    using FunctionType = int(*)(int);
    FunctionType function = TestFunction;
    EXPECT_EQ(10, function(5));
}