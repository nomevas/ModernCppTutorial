#include <gtest/gtest.h>

#include <string>

TEST(StringLiteral, RawStringLiterals_AEasyWayToAvoidEscapeChars) {
  const std::string raw_string = R"my-char-seq(
    )\
    a""
    )my-char-seq";
  const std::string regular_string = "\n    )\\\n    a\"\"\n    ";
  EXPECT_EQ(regular_string, raw_string);
}

TEST(StringLiteral, ConcatenatedString) {
  const std::string concatenated_string =
      "\n"
      ")\\\n"
      "a\"\"\n";
  const std::string regular_string = "\n)\\\na\"\"\n";
  EXPECT_EQ(regular_string, concatenated_string);
}

TEST(StringLiteral, WideStringLiteral) {
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*L"мој стринг")>, wchar_t>));
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*LR"my_key(мој стринг)my_key")>, wchar_t>));
}

TEST(StringLiteral, utf8Literal) {
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*u8"мој стринг")>, char8_t>)) << "not a char since c++20";
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*u8R"my_key(мој стринг)my_key")>, char8_t>)) << "not a char since c++20";
}

TEST(StringLiteral, utf16Literal) {
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*u"мој стринг")>, char16_t>)) << "not a char since c++20";
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*uR"my_key(мој стринг)my_key")>, char16_t>)) << "not a char since c++20";
}

TEST(StringLiteral, utf32Literal) {
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*U"мој стринг")>, char32_t>)) << "not a wchar since c++20";
  EXPECT_TRUE((std::is_same_v<std::remove_cvref_t<decltype(*UR"my_key(мој стринг)my_key")>, char32_t>)) << "not a wchar since c++20";
}
