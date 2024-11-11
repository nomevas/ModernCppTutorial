#include <gtest/gtest.h>

#include <string>
#include <variant>

TEST(Variant, index) {
  std::variant<int, std::string> variant{0};
  EXPECT_EQ(0, variant.index());
  variant = "my string";
  EXPECT_EQ(1, variant.index());
}

TEST(Variant, visitor) {
  std::variant<int, std::string, double> variant{0};

  auto set_and_get = [&variant](auto value) {
    std::any return_value;
    variant = value;
    std::visit(
        [&return_value](auto&& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, std::string>)
            return_value = arg;
          else if constexpr (std::is_same_v<T, int>)
            return_value = arg;
          else if constexpr (std::is_same_v<T, double>)
            return_value = arg;
          else
            static_assert(false, "non-exhaustive visitor!");
        },
        variant);
    return std::any_cast<decltype(value)>(return_value);
  };

  EXPECT_EQ(1, set_and_get(1));
  EXPECT_EQ(std::string{"string"}, set_and_get(std::string{"string"}));
  EXPECT_EQ(2.0, set_and_get(2.0));
}


TEST(Variant, get) {
  std::variant<int, std::string, double> variant{0};

  auto set_and_get = [&variant](auto value) {
    variant = value;
    return std::get<decltype(value)>(variant);
  };

  EXPECT_EQ(1, set_and_get(1));
  EXPECT_EQ(std::string{"string"}, set_and_get(std::string{"string"}));
  EXPECT_EQ(2.0, set_and_get(2.0));
}

TEST(Variant, getWhenOtherTypeThenThrowsAnException) {
  std::variant<int, std::string, double> variant{0};
  EXPECT_THROW(std::get<std::string>(variant), std::bad_variant_access);
}