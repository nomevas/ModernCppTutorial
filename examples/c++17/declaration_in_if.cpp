// In traditional C++, the declaration of a variable can declare a temporary variable int even though it can be located anywhere, 
// even within a for statement, but there is always no way to declare a temporary variable in the if and switch statements.

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

TEST(DeclarationVariableInIf, NominalCase) {
    std::vector<int> vec = {1, 2, 3, 4};

    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3);
        itr != vec.end()) {
        EXPECT_TRUE(true);
    } else {
        EXPECT_TRUE(false);
    }
}
