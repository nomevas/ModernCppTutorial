// The template has always been one of C++'s unique Black Magic. In traditional
// C++, both a class template and a function template could only accept a fixed
// set of template parameters as specified; C++11 added a new representation,
// allowing any number, template parameters of any category, and there is no
// need to fix the number of parameters when defining.

#include <gtest/gtest.h>

TEST(ObjectOriented, DelegateConstructor) {
  class Class {
   public:
    Class() : Class(0){};
    Class(int value1) : Class(value1, 0) {}
    Class(int value1, int value2) : value1(value1), value2(value2) {}
    auto operator()() const { return std::make_tuple(value1, value2); }

   private:
    int value1 = -1;
    int value2 = -1;
  };

  EXPECT_EQ(std::make_tuple(0, 0), Class{}());
  EXPECT_EQ(std::make_tuple(1, 0), Class{1}());
  EXPECT_EQ(std::make_tuple(1, 2), (Class{1, 2}()));
}

TEST(ObjectOriented, InheritanceConstructor) {
  class Base {
   public:
    int value1 = -1;
    Base() : value1{5} {}
    auto operator()() const { return value1; }
  };

  class Class : public Base {
   public:
    using Base::Base;  // inheritance constructor
  };
  EXPECT_EQ(5, Class{}());
}

TEST(ObjectOriented, ForceGeneratingDefaultConstructor) {
  struct Class {
    Class() = default;                        // explicit let compiler use default constructor
    Class& operator=(const Class&) = delete;  // explicit declare refuse constructor
    Class(int value) : value(value){};
    int value = -1;
  };

  EXPECT_EQ(-1, Class{}.value);
}

TEST(ObjectOriented, CheckIfMethodIsDeclaredAsVirtualInBaseClass) {
  struct Base {
    virtual int foo(int) = 0;
  };

  struct Class : Base {
    int foo(int value) override { return value; };  // legal
    // virtual void foo(float) override {}; illegal, no virtual function in super class
  };

  EXPECT_EQ(5, Class{}.foo(5));
}

TEST(ObjectOriented, PreventTheClassFromBeingContinuedToInherit) {
  struct Base {
    virtual int foo(int) = 0;
  };

  struct Class : Base {
    int foo(int value) final { return value; };
  };

  EXPECT_EQ(5, Class{}.foo(5));
}
