#include <gtest/gtest.h>

#include <unordered_set>

TEST(UnorderedSet, HashBasedSet_O1Lookup) {
  // hash based set container
  std::unordered_set<int> unordered_set = {1, 2, 3, 4};

  EXPECT_FALSE(unordered_set.empty());
  EXPECT_EQ(1, unordered_set.count(2));
}

TEST(UnorderedSet, UserDefinedType_defineEqualAndHash) {
  struct MyType {
    bool operator==(const MyType& rho) const {
      return value == rho.value;
    }
    int value;
  };
  struct Hash {
    size_t operator()(const MyType& test) const { return test.value; }
  };
  std::unordered_set<MyType, Hash> container;
  container.emplace(0);
  container.emplace(1);
  container.emplace(2);
  container.emplace(2);
  EXPECT_EQ(3, container.size()) << "duplicates should be filtered out";
}