#include <gtest/gtest.h>

#include <functional>
#include <random>

TEST(Random, NumberOfStandardDistributions) {
  std::uniform_int_distribution<int> distribution(0, 100);
  std::mt19937 engine;
  auto generator = std::bind(distribution, engine);
  auto generated_value = generator();

  EXPECT_GE(generated_value, 0);
  EXPECT_LE(generated_value, 100);
}

TEST(Random, NormalDistribution) {
  std::random_device rd{};
  std::mt19937 gen{rd()};
  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  std::normal_distribution d{5.0, 2.0};
  // draw a sample from the normal distribution and round it to an integer
  auto random_int = [&d, &gen] { return std::round(d(gen)); };

  std::map<int, int> hits{};
  for (int i = 0; i < 1000; ++i) {
    ++hits[random_int()];
  }

  auto sum_left = hits[0] + hits[1] + hits[2] + hits[3];
  auto sum_in_mean = hits[4] + hits[5] + hits[6];
  auto sum_right = hits[7] + hits[8] + hits[9] + hits[10];
  EXPECT_LT(sum_left, sum_in_mean);
  EXPECT_LT(sum_right, sum_in_mean);
}