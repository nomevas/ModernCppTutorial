#include <gtest/gtest.h>

TEST(TestNullptr, IsSameAsNull_Not) { 
    const auto IsSameAsNull = std::is_same<decltype(NULL), decltype(nullptr)>::value; 
    EXPECT_FALSE(IsSameAsNull) << "decltype(nullptr) != decltype(nullptr)";
}

int foo(char*) {
    return 1;
}

int foo(int i) {
    return 2;
}

TEST(TestNullptr, CallTheRightAPI_NullptrCallsPtrVersion) { 
    EXPECT_EQ(foo(nullptr), 1) << "foo(char*) is not called";
    EXPECT_EQ(foo(0), 2) << "foo(int) is not called";
}