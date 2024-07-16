// The decltype keyword is used to solve the defect that the auto keyword can only type the variable. Its usage is very similar to typeof

#include <gtest/gtest.h>

template <typename T>
auto add_some_value(const T& t) {
  if constexpr (std::is_integral<T>::value) {
    return t + 1;
  } else {
    return t + 0.01;
  }
}

// At compile time, the actual code will behave as follows:
// int print_type_info(const int& t) {
//     return t + 1;
// }
// double print_type_info(const double& t) {
//     return t + 0.01;
// }

TEST(IfConstexpr, CompileTimeIfConditino) {
  EXPECT_EQ(6, add_some_value(5));
  EXPECT_EQ(3.15, add_some_value(3.14));
}