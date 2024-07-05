#include <gtest/gtest.h>

struct MyStruct {
    int number;
    const char* string; 
};

TEST(InitializerList, PrimitiveType) {
    int value = {};
    EXPECT_EQ(value, 0);
}

TEST(InitializerList, UserDefined_initialize) {
    struct MyStruct {
        int number;
        const char* string; 
    };

    auto my_struct = MyStruct{5, "test"};
    EXPECT_EQ(5, my_struct.number);
    EXPECT_STREQ("test", my_struct.string);
}

TEST(InitializerList, UserDefined_defaultConstructr) {
    auto my_struct = MyStruct{};
    EXPECT_EQ(0, my_struct.number);
    EXPECT_STREQ(nullptr, my_struct.string);
}

TEST(InitializerList, UserDefined_partialInitialization) {
    auto my_struct = MyStruct{5};
    EXPECT_EQ(5, my_struct.number);
    EXPECT_STREQ(nullptr, my_struct.string);
}

TEST(InitializerList, UserDefined_partialInitializationUnordered) {
    auto my_struct = MyStruct{.string = "test"};
    EXPECT_EQ(0, my_struct.number);
    EXPECT_STREQ("test", my_struct.string);
}