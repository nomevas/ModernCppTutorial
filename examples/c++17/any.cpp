#include <gtest/gtest.h>

#include <any>

TEST(Any, construct) { EXPECT_NO_THROW(std::any(12)); }

TEST(Any, cast) { EXPECT_EQ(12, std::any_cast<int>(std::any(12))); }

TEST(Any, castWhenInvalidThrowAnException) { EXPECT_THROW(std::any_cast<std::string>(std::any(12)), std::bad_any_cast); }

TEST(Any, castToPointer) {
  std::any any = 12;
  int* i = std::any_cast<int>(&any);
  EXPECT_EQ(12, *i);
}

TEST(Any, castToRef) {
  std::any any = std::string("hello");
  auto& ref = std::any_cast<std::string&>(any);
  ref[1] = '0';
  EXPECT_EQ(ref, "h0llo");
}

TEST(Any, castToRvalueRef) {
  std::any any = std::string("hello");
  auto value = std::any_cast<std::string&&>(std::move(any));
  EXPECT_EQ(value, "hello");
  EXPECT_EQ(std::any_cast<std::string>(any), "");
}