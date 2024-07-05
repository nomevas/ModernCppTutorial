// C++ itself already has the concept of constant expressions, such as 1+2, 3*4. Such expressions always produce the same result without any side effects. 
// If the compiler can directly optimize and embed these expressions into the program at compile-time, it will increase the performance of the program.

#include <gtest/gtest.h>
#include <chrono>

constexpr int fibonacci(const int n) {
    return n == 1 || n == 2 ? 1 : fibonacci(n-1) + fibonacci(n-2);
}

TEST(ConstExpr, StoreInConstExprVariable_RunInCompileTime) {
    auto start_t = clock();
    constexpr auto compile_time_perf = fibonacci(20);
    auto end_t = clock();
    EXPECT_LE(end_t - start_t, 5);
}

TEST(ConstExpr, StoreInNormalVariable_RunInRuntime) {
    auto start_t = clock();
    auto runtime_time_perf = fibonacci(20);
    auto end_t = clock();
    EXPECT_GE(end_t - start_t, 5);
}