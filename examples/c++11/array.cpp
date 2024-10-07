#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <array>
#include <forward_list>
#include <functional>
#include <unordered_map>
#include <unordered_set>

using testing::Each;
using testing::AllOf;
using testing::Eq;

TEST(Array, FixedSizeContainer_AvoidPerformanceSpaceOverhead) {
  std::array<int, 4> arr = {1, 2, 3, 4};

  EXPECT_EQ(4, arr.size());
  EXPECT_FALSE(arr.empty());
  std::ranges::sort(arr, std::greater<int>());
  EXPECT_EQ(4, arr[0]);
}

template <typename T, int N> 
constexpr auto MakeArray(const T& default_value) {
  std::array<T, N> array;
  array.fill(default_value); // constexpr since C++20 
  return array;
}

template <typename T, int N, int M> 
constexpr auto MakeMatrix(const T& default_value) {
  auto array = MakeArray<T, N>(default_value);
  std::array<decltype(array), M> matrix;
  matrix.fill(array); // constexpr since C++20 
  return matrix;
}

TEST(Array, CreateArrayWithDefaultValue) {
  auto array = MakeArray<int, 10>(-1);
  EXPECT_EQ(10, array.size());
  ASSERT_THAT(array, Each(Eq(-1)));
}

TEST(Array, CreateMatrixWithDefaultValue) {
  auto matrix = MakeMatrix<int, 10, 10>(-1);
  EXPECT_EQ(10, matrix.size());
  EXPECT_EQ(10, matrix[0].size());
  ASSERT_THAT(matrix, Each(Eq(MakeArray<int, 10>(-1))));
}