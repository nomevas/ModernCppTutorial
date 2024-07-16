// auto has been in C++ for a long time, but it always exists as an indicator of a storage type, coexisting with register.
// In traditional C++, if a variable is not declared as a register variable, it is automatically treated as an auto variable.
// And with register being deprecated (used as a reserved keyword in C++17 and later used, it doesn't currently make sense), the semantic change to auto is very natural.

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::MatchesRegex;

TEST(Auto, GenericLambdaExpressions) {
  auto sum = [](auto a1, auto a2) { return a1 + a2; };

  EXPECT_EQ(10, sum(7, 3));
}

TEST(Auto, GetTypeNameUsingTypeInfo) {
  std::vector<int> container = {1, 2, 3};
  auto iter = container.begin();
  EXPECT_THAT(typeid(iter).name(), MatchesRegex(".*iterator.*vector.*"));
}

TEST(Auto, StrippingRefAndCVProperties) {
  const int const_int = 0;
  const int& const_int_ref = 0;

  auto deduced_const_int = const_int;
  auto deduced_const_int_ref = const_int_ref;

  EXPECT_TRUE((std::is_same_v<decltype(deduced_const_int), int>));
  EXPECT_TRUE((std::is_same_v<decltype(deduced_const_int_ref), int>));
}