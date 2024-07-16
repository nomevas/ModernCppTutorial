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
  class InheritanceConstructorBase {
   public:
    int value1 = -1;
    InheritanceConstructorBase() : value1{5} {}
    auto operator()() const { return value1; }
  };

  class InheritanceConstructorSubclass : public InheritanceConstructorBase {
   public:
    using InheritanceConstructorBase::InheritanceConstructorBase;  // inheritance constructor
  };
  EXPECT_EQ(5, InheritanceConstructorSubclass{}());
}

struct ExplicitDeletedCreatedConstructors {
  ExplicitDeletedCreatedConstructors() = default;                                                     // explicit let compiler use default constructor
  ExplicitDeletedCreatedConstructors& operator=(const ExplicitDeletedCreatedConstructors&) = delete;  // explicit declare refuse constructor
  ExplicitDeletedCreatedConstructors(int value) : value(value){};
  int value = -1;
};

TEST(ObjectOriented, ForceGeneratingDefaultConstructor) { EXPECT_EQ(-1, ExplicitDeletedCreatedConstructors{}.value); }

struct OverrideBase {
  virtual int foo(int) = 0;
};

struct OverrideSubClass : OverrideBase {
  int foo(int value) override { return value; };  // legal
  // virtual void foo(float) override {}; illegal, no virtual function in super class
};

TEST(ObjectOriented, CheckIfMethodIsDeclaredAsVirtualInBaseClass) { EXPECT_EQ(5, OverrideSubClass{}.foo(5)); }

struct PreventTheClassFromBeingContinuedToInheritBase {
  virtual int foo(int) = 0;
};

struct PreventTheClassFromBeingContinuedToInheritSubClass : PreventTheClassFromBeingContinuedToInheritBase {
  int foo(int value) final { return value; };
};

TEST(ObjectOriented, PreventTheClassFromBeingContinuedToInherit) { EXPECT_EQ(5, PreventTheClassFromBeingContinuedToInheritSubClass{}.foo(5)); }
