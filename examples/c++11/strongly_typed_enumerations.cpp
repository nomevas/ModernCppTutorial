// In traditional C++, enumerated types are not type-safe, and enumerated types are treated as integers, which allows two completely different enumerated types to be directly
// compared (although the compiler gives the check, but not all), ** Even the enumeration value names of different enum types in the same namespace cannot be the same**, which is
// usually not what we want to see.

#include <gtest/gtest.h>

TEST(StronglyTypedEnumerations, NoImplicitTypeConversion) {
  enum class TestEnum { Item = 0 };

  EXPECT_EQ(0, static_cast<int>(TestEnum::Item));
}

TEST(StronglyTypedEnumerations, Scoping) {
  auto Item = -1;
  enum class TestEnum { Item = 0 };

  EXPECT_EQ(-1, Item);
}

TEST(StronglyTypedEnumerations, UnderlyingType) {
  enum class A : unsigned long { A1 = 1, A2 = 2 };
  EXPECT_TRUE((std::is_same_v<std::underlying_type_t<A>, unsigned long>));
}

TEST(StronglyTypedEnumerations, ForwardDeclarationOfEnums) {
  enum class A : unsigned long;
  EXPECT_TRUE((std::is_same_v<std::underlying_type_t<A>, unsigned long>));
}