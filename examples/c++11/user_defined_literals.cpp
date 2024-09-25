#include <gtest/gtest.h>

struct MyType {
  unsigned long long m;
  auto value() const { return m; }
};

constexpr MyType operator""_mytype(unsigned long long n) { return MyType{n}; }

TEST(UserDefinedLiterals, MyTypeLiteral) { EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(15_mytype)>, MyType>)); }

TEST(UserDefinedLiterals, CallMemberFunctionAfterLiteral) {
  // clang-format off
  EXPECT_EQ(10, 10_mytype .value()) << "with a space between the user defined literal and the member function";
  // clang-format on
  EXPECT_EQ(10, (10_mytype).value()) << "or by using parentheses";
}