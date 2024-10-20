#include <gtest/gtest.h>

#include <functional>

TEST(Move, podMembersAreAutomaticallyMoved) {
  struct Test {
    std::function<int()> member;  
  };
  auto test = Test{.member = []{return 5;}};
  auto newObject = std::move(test);
  EXPECT_FALSE(test.member) << "The member is moved to the new object";
  ASSERT_TRUE(newObject.member);
  EXPECT_EQ(5, newObject.member());
}

TEST(Move, destructorDisablesGeneratingTheMoveOperator) {
  struct Test {
    ~Test() {}
    std::function<int()> member;  
  };
  auto test = Test{.member = []{return 5;}};
  auto newObject = std::move(test);
  EXPECT_TRUE(test.member) << "Custom destructor disables default move operators. The object is copied";
  EXPECT_EQ(5, test.member());
  ASSERT_TRUE(newObject.member);
  EXPECT_EQ(5, newObject.member());
}