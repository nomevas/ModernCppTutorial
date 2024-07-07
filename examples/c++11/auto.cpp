// auto has been in C++ for a long time, but it always exists as an indicator of a storage type, coexisting with register. 
// In traditional C++, if a variable is not declared as a register variable, it is automatically treated as an auto variable. 
// And with register being deprecated (used as a reserved keyword in C++17 and later used, it doesn't currently make sense), the semantic change to auto is very natural.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::MatchesRegex;

TEST(Auto, GenericLambdaExpressions) {
    auto sum = [](auto a1, auto a2) {
        return a1 + a2;
    };

    EXPECT_EQ(10, sum(7, 3));
}

TEST(Auto, GetTypeNameUsingTypeInfo) {
    std::vector<int> container = {1, 2, 3};
    auto iter = container.begin();
    EXPECT_THAT(typeid(iter).name(), MatchesRegex(".*iterator.*vector.*"));
}

TEST(Auto, CheckTypeUsingDecltype) {
    auto x = 1;
    auto y = 2;
    decltype(x + y) z;

    static_assert(std::is_same<decltype(x), int>::value, "type x == int");
    static_assert(std::is_same<decltype(x), decltype(z)>::value, "type z == type x");
}