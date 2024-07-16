#include <gtest/gtest.h>

#include <tuple>

template <class... Ts>
auto FunctionThatReturnsMultipleValues(Ts... args) {
  return std::make_tuple(args...);
}

TEST(Tuple, FunctionThatReturnsMultipleValues_storeResultInLocalVariables) {
  auto [integer, string, number] = FunctionThatReturnsMultipleValues(1, "test", 2.0);
  EXPECT_EQ(1, integer);
  EXPECT_STREQ("test", string);
  EXPECT_EQ(2.0, number);
}

TEST(Tuple, FunctionThatReturnsMultipleValues_reuseExistingVariables) {
  int integer = 0;
  const char* string = nullptr;
  double number = 0;
  std::tie(integer, string, number) = FunctionThatReturnsMultipleValues(1, "test", 2.0);
  EXPECT_EQ(1, integer);
  EXPECT_STREQ("test", string);
  EXPECT_EQ(2.0, number);
}

TEST(Tuple, Iterate_WithStdApplyAndFoldExpression) {
  std::ostringstream oss;
  {
    auto cout_buff = std::cout.rdbuf(oss.rdbuf());
    std::apply([](auto&&... args) { ((std::cout << args << '\n'), ...); }, std::make_tuple(0, 'a', 3.14));
    std::cout.rdbuf(cout_buff);
  }
  EXPECT_EQ(oss.str(), "0\na\n3.14\n");
}

template <size_t I = 0, typename... Tp>
void print(const std::tuple<Tp...>& t) {
  std::cout << std::get<I>(t) << std::endl;
  if constexpr (I + 1 != sizeof...(Tp)) print<I + 1>(t);
}

TEST(Tuple, Iterate_Recursive) {
  std::ostringstream oss;
  {
    auto cout_buff = std::cout.rdbuf(oss.rdbuf());
    print(std::make_tuple(0, 'a', 3.14));
    std::cout.rdbuf(cout_buff);
  }
  EXPECT_EQ(oss.str(), "0\na\n3.14\n");
}