// std::bind generates a forwarding call wrapper for f. Calling this wrapper is equivalent to invoking f with some of its arguments bound to args.
// The return type of std::bind holds a member object of type std::decay<F>::type constructed from std::forward<F>(f), and one object
// per each of args..., of type std::decay<Arg_i>::type, similarly constructed from std::forward<Arg_i>(arg_i).

#include <gmock/gmock.h>
#include <gtest/gtest.h>

static int MyFunction(int arg1) { return arg1; }

TEST(Bind, CreateACallableObjectFromGlobalFunction) {
  auto callable = std::bind(MyFunction, std::placeholders::_1);
  EXPECT_EQ(1, callable(1));
}

TEST(Bind, CreateACallableFromMemberFunction) {
  struct TestStruct {
    int method(int arg1) const { return arg1; }
  };

  TestStruct test_struct;
  auto callable = std::bind(&TestStruct::method, &test_struct, std::placeholders::_1);
  EXPECT_EQ(1, callable(1));
}

TEST(Bind, CallableReorderArgumentsAndDefaultValues) {
  struct TestStruct {
    int method(int arg1, std::string arg2, double d) const { return arg1; }
  } test_struct;

  auto callable = std::bind(&TestStruct::method, &test_struct, std::placeholders::_2, std::placeholders::_1, 0.0);
  EXPECT_EQ(1, callable("string arg first", 1));
}

TEST(Bind, PassByReference) {
  struct TestStruct {
    int method(const int& arg1, std::string& arg2) const {
      arg2 = "changed value";
      return arg1;
    }
  } test_struct;

  std::string my_string = "intial value";
  auto callable = std::bind(&TestStruct::method, &test_struct, 1, std::ref(my_string));
  EXPECT_EQ(1, callable());
  EXPECT_EQ(my_string, "changed value");
}
