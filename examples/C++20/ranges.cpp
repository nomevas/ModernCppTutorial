#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <ranges>
#include <span>
#include <algorithm>

TEST(Ranges, createEmptyView) {
  const auto empty_view = std::ranges::empty_view<int>();
  EXPECT_EQ(0, empty_view.size());
}

TEST(Ranges, createSingleView) {
  const auto single_view = std::ranges::single_view(1);
  ASSERT_EQ(1, single_view.size());
  EXPECT_EQ(1, single_view[0]);
}

TEST(Ranges, createIotaView) {
  const auto iota_view = std::ranges::iota_view(0, 10);
  ASSERT_EQ(10, iota_view.size());
  EXPECT_EQ(0, iota_view[0]);
  EXPECT_EQ(9, iota_view[9]);
}

TEST(Ranges, all_containerToView) {
  std::vector<int> v{0, 1, 2, 3, 4, 5};
  auto all_view = std::views::all(v);
  ASSERT_EQ(6, all_view.size());
}

TEST(Ranges, to_viewToContainer) {
  // std::views::to is c++23 feature, this is an alternative
  const auto range = std::views::iota(1, 3);
  const auto vector = std::vector<int>{std::ranges::begin(range), std::ranges::end(range)};
  EXPECT_THAT(vector, testing::ContainerEq(std::vector{1, 2}));
}


TEST(Ranges, filter) {
  auto filtered_values = std::views::iota(0, 6) | std::views::filter([](auto element) { return element % 2 == 0; });
  std::vector<int> result{std::ranges::begin(filtered_values), std::ranges::end(filtered_values)};
  EXPECT_THAT(result, testing::ContainerEq(std::vector{0, 2, 4}));
}

TEST(Ranges, transform) {
  const auto transformed_values = std::views::iota(0, 6) | std::views::transform([](auto element) { return element % 2 == 0; });
  std::vector<bool> result{std::ranges::begin(transformed_values), std::ranges::end(transformed_values)};
  EXPECT_THAT(result, testing::ContainerEq(std::vector{true, false, true, false, true, false}));
}

TEST(Ranges, take_firstNElements) {
  const auto first_three = std::views::iota(0, 6) | std::views::take(3);
  std::vector<int> result{std::ranges::begin(first_three), std::ranges::end(first_three)};
  EXPECT_THAT(result, testing::ContainerEq(std::vector{0, 1, 2}));
} 

TEST(Ranges, take_whileNotTrue) {
  const auto not_three = [](auto value) {return value != 3;};
  const auto first_three = std::views::iota(0, 6) | std::views::take_while(not_three);
  std::vector<int> result;
  for (auto&& item : first_three) {
    result.push_back(item);
  }
  EXPECT_THAT(result, testing::ContainerEq(std::vector{0, 1, 2}));
}
