// The basic syntax of a Lambda expression is as follows:
// [capture list] (parameter list) mutable(optional) exception attribute -> return type {
// function body
// }

#include <gtest/gtest.h>

#include <functional>

TEST(Lambda, Nominal) {
  auto my_lambda = [](int arg) { return arg; };
  // check if closure can be converted to executable object
  static_assert(std::is_convertible_v<decltype(my_lambda), std::function<int(int)>>);
  // Execute the function
  EXPECT_EQ(1, my_lambda(1));
}

TEST(Lambda, CaptureLocalVariables) {
  int local_value = 5;
  auto my_lambda = [local_value](int arg) { return arg + local_value; };
  EXPECT_EQ(6, my_lambda(1));
}

TEST(Lambda, ModifyLocalVariables) {
  int local_value = 5;
  // if you capture a local variable by value and you want to modify it as a "global" then use mutable.
  // I would rather capture by ref
  auto my_lambda = [local_value](int arg) mutable {
    local_value = 1;
    return arg + local_value;
  };
  EXPECT_EQ(2, my_lambda(1));
  EXPECT_EQ(1, local_value);
}

TEST(Lambda, RecursiveLambda) {
  std::function<int(int, int)> sum;

  sum = [&sum](int current, int last) {
    if (current < last)
      return sum(current + 1, last) + current;
    else
      return current;
  };

  EXPECT_EQ(55, sum(1, 10));
}