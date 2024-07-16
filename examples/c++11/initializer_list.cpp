#include <gtest/gtest.h>

struct MyStruct {
  int number;
  const char* string;
};

TEST(InitializerList, InitializePrimitiveDataType) {
  int value = {};
  EXPECT_EQ(value, 0);
}

TEST(InitializerList, InitializeUserDefinedDataType) {
  struct MyStruct {
    int number;
    const char* string;
  };

  auto my_struct = MyStruct{5, "test"};
  EXPECT_EQ(5, my_struct.number);
  EXPECT_STREQ("test", my_struct.string);
}

TEST(InitializerList, PartialInitializationOfUserDefinedDataType) {
  auto my_struct = MyStruct{5};
  EXPECT_EQ(5, my_struct.number);
  EXPECT_STREQ(nullptr, my_struct.string);
}

TEST(InitializerList, UnorderedPartialInitializationOfUserDefinedDataType) {
  auto my_struct = MyStruct{.string = "test"};
  EXPECT_EQ(0, my_struct.number);
  EXPECT_STREQ("test", my_struct.string);
}