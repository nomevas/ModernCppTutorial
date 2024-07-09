// The decltype keyword is used to solve the defect that the auto keyword can only type the variable. Its usage is very similar to typeof

#include <gtest/gtest.h>

TEST(Decltype, CheckTypeUsingDecltype) {
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;

    static_assert(std::is_same<decltype(x), int>::value, "type x == int");
    static_assert(std::is_same<decltype(x), decltype(z)>::value, "type z == type x");
}