// The purpose of nullptr appears to replace NULL. There are null pointer constants in the C and C++ languages, which can be implicitly converted 
// to null pointer value of any pointer type, or null member pointer value of any pointer-to-member type in C++. NULL is provided by the standard 
// library implementation and defined as an implementation-defined null pointer constant. In C, some standard libraries defines NULL as ((void*)0) 
// and some define it as 0.

#include <gtest/gtest.h>

TEST(Nullptr, IsSameAsNull_False) { 
    auto temp =  std::is_same_v<decltype(nullptr), std::nullptr_t>;
    const auto IsSameAsNull = std::is_same<decltype(NULL), decltype(nullptr)>::value; 
    EXPECT_FALSE(IsSameAsNull) << "decltype(nullptr) != decltype(nullptr)";
}

TEST(Nullptr, IsSameAsStdNullptrT_True) { 
    const auto isSameAsNullPtrT =  std::is_same_v<decltype(nullptr), std::nullptr_t>;
    EXPECT_TRUE(isSameAsNullPtrT) << "decltype(nullptr) != std::nullptr_t";
}

int foo(char*) {
    return 1;
}

int foo(int i) {
    return 2;
}

TEST(Nullptr, OverloadedMethods_NullptrCallsPtrFlavor) { 
    EXPECT_EQ(foo(nullptr), 1) << "foo(char*) is not called";
    EXPECT_EQ(foo(0), 2) << "foo(int) is not called";
}