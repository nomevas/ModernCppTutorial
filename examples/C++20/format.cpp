#include <gtest/gtest.h>

#include <format>

TEST(Format, FormatString_IgnoresObsoluteArguments) { EXPECT_EQ("Hello World!", std::format("{} {}!", "Hello", "World", "IGNORE THIS")); }

TEST(Format, FormatString_ChangeOrder) { EXPECT_EQ("World, Hello!", std::format("{1}{2} {0}!", "Hello", "World", ",")); }

TEST(Format, FormatToBuffer) {
  std::string buffer;
  std::format_to(std::back_inserter(buffer), "{} {}!", "Hello", "World"), std::back_inserter(buffer);
  EXPECT_EQ(buffer, "Hello World!");
}

TEST(Format, FormatToBuffer_Concat) {
  std::string buffer;
  std::format_to_n(std::back_inserter(buffer), 5, "{} {}!", "Hello", "World"), std::back_inserter(buffer);
  EXPECT_EQ(buffer, "Hello");
}

TEST(Format, NonTemplateVariant) {
  auto string_builder = [](auto fmt, auto... args) { return std::vformat(fmt, std::make_format_args(args...)); };

  EXPECT_EQ("Hello World!", string_builder("{} {}!", "Hello", "World"));
}