#include <gtest/gtest.h>

#include <regex>
#include <string>

static const std::string TestString =
    "Some people, when confronted with a problem, think "
    "\"I know, I'll use regular expressions.\" "
    "Now they have two problems.";

TEST(Regex, SearchForSubString) {
  static const std::regex self_regex("REGULAR EXPRESSIONS", std::regex_constants::ECMAScript | std::regex_constants::icase);
  EXPECT_TRUE(std::regex_search(TestString, self_regex)) << "Text contains the phrase 'regular expressions'\n";
}

TEST(Regex, RegexIterator) {
  static const std::regex word_regex("(\\w+)");
  const auto words_begin = std::sregex_iterator(TestString.begin(), TestString.end(), word_regex);
  const auto words_end = std::sregex_iterator();
  EXPECT_EQ(20, std::distance(words_begin, words_end));
}

TEST(Regex, Replace) {
  std::string text = "Quick brown fox";
  std::regex vowel_re("a|e|i|o|u");
  EXPECT_EQ("Q[u][i]ck br[o]wn f[o]x", std::regex_replace(text, vowel_re, "[$&]"));
}

TEST(Regex, Match) {
  const std::string test_string = "Extract this and that from the text";
  static const std::regex regex(".*(this).*(that).*");
  std::smatch smatch;
  EXPECT_TRUE(std::regex_match(test_string, smatch, regex));
  ASSERT_EQ(3, smatch.size());
  EXPECT_EQ("Extract this and that from the text", smatch[0]);
  EXPECT_EQ("this", smatch[1]);
  EXPECT_EQ("that", smatch[2]);
}