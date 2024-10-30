// In traditional C++, the declaration of a variable can declare a temporary variable int even though it can be located anywhere,
// even within a for statement, but there is always no way to declare a temporary variable in the if and switch statements.

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

TEST(DeclarationVariableInIf, NominalCase) {
  std::vector<int> vec = {1, 2, 3, 4};

  if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
    EXPECT_TRUE(true);
  } else {
    EXPECT_TRUE(false);
  }
}

TEST(DeclarationVariableInIf, MultipleVariables) {
  auto check_condition1 = []{return true;};
  auto check_condition2 = []{return true;};

  if (auto [condition1, condition2] = std::tuple{check_condition1(), check_condition2()}; condition1 && condition2) {
    EXPECT_TRUE(true);
  } else {
    EXPECT_TRUE(false);
  }
}