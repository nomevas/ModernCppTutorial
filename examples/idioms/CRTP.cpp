// The Curiously Recurring Template Pattern is an idiom in which a class X derives from a class template Y, taking a template parameter Z, where Y is instantiated with Z = X.

#include <gtest/gtest.h>

template <class Derived>
struct Base {
  std::string name() { return static_cast<Derived*>(this)->impl(); }

 protected:
  Base() = default;  // prohibits the creation of Base objects, which is UB
};

struct D1 : public Base<D1> {
  D1() = default;
  std::string impl() { return "D1::impl()"; }
};
struct D2 : public Base<D2> {
  D2() = default;
  std::string impl() { return "D2::impl()"; }
};

TEST(CRTP, testCompileTimePolymorphism) {
  EXPECT_EQ(D1{}.name(), "D1::impl()");
  EXPECT_EQ(D2{}.name(), "D2::impl()");
}