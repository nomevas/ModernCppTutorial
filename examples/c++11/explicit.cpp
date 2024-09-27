#include <gtest/gtest.h>

TEST(Explicit, PreventUsingImplicitTypeConversionOperators) {
  class Test {
   public:
    explicit Test(int value) : m_value{value} {}
    explicit operator bool() const { return m_value != 0; }

   private:
    int m_value;
  };

  // Test test = {4}; doesn't work
  EXPECT_TRUE(static_cast<bool>(Test{4})) << "implicit cast is disabled";
}