#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <numeric>
#include <array>
#include <span>

namespace {
  auto sumAll(std::span<const int> values) {
    return std::accumulate(std::begin(values), std::end(values), 0);
  }
}

TEST(Span, constructFromVariousTypeOfContainers) {
  EXPECT_EQ(6, sumAll(std::vector{1,2,3}));
  EXPECT_EQ(6, sumAll(std::array{1,2,3}));
  int values[] = {1,2,3};
  EXPECT_EQ(6, sumAll(values));
}

TEST(Span, obtainASubspan) {
  const auto container = std::vector{1,2,3};
  EXPECT_EQ(3, sumAll(std::span{container}.subspan(0, 2)));
}

TEST(Span, transformToUpper) {
  const auto transformToUpper =[](auto&& string) {
    std::transform(string.begin(), string.end(), string.begin(), ::towupper);
  };
  std::wstring firstLetterUpperCase = L"first letter uppercase";
  transformToUpper(std::span{firstLetterUpperCase.begin(), 1});
  EXPECT_EQ(firstLetterUpperCase, L"First letter uppercase");
  
  std::wstring fullUpperCase = L"full uppercase";
  transformToUpper(fullUpperCase);
  EXPECT_EQ(fullUpperCase, L"FULL UPPERCASE");
}