// C++ itself already has the concept of constant expressions, such as 1+2, 3*4. Such expressions always produce the same result without any side effects.
// If the compiler can directly optimize and embed these expressions into the program at compile-time, it will increase the performance of the program.

#include <gtest/gtest.h>

#include <chrono>

constexpr int fibonacci(const int n) { return n == 1 || n == 2 ? 1 : fibonacci(n - 1) + fibonacci(n - 2); }

TEST(ConstExpr, EvaluateTheFucntionInCompileTime) {
  auto start_t = clock();
  constexpr auto compile_time_perf = fibonacci(20);
  auto end_t = clock();
  EXPECT_LE(end_t - start_t, 5);
}

TEST(ConstExpr, ConstExprUserDefinedType) {
  struct ConstExprType {
    const char* string;
    int intValue;
  };
 
  constexpr auto obj = ConstExprType{"0", 1};
  static_assert("0" == obj.string);
  static_assert(1 == obj.intValue);
}

TEST(ConstExpr, ConstExprFunctionThatReturnsString) {
  constexpr auto constexprFunction = [](){
    return std::string{"test"};
  };
 
  // std::string and std::vectors are supported in c++20
  static_assert("test" == constexprFunction());
}