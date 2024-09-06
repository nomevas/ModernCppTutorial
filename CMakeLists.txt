cmake_minimum_required(VERSION 3.18)

project(ModernCppTutorial)

include(GoogleTest)
include(cmake/add_test.cmake)

find_package(Threads)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

# C++11 Features
add_test(examples/c++11/auto.cpp)
add_test(examples/c++11/bind.cpp)
add_test(examples/c++11/constexpr.cpp)
add_test(examples/c++11/containers.cpp)
add_test(examples/c++11/initializer_list.cpp)
add_test(examples/c++11/nullptr.cpp)
add_test(examples/c++11/tuple.cpp)
add_test(examples/c++11/decltype.cpp)
add_test(examples/c++11/range_loop.cpp)
add_test(examples/c++11/rvalue_lvalue_references.cpp)
add_test(examples/c++11/using_alias.cpp)
add_test(examples/c++11/variadic_template.cpp)
add_test(examples/c++11/object_oriented.cpp)
add_test(examples/c++11/strongly_typed_enumerations.cpp)
add_test(examples/c++11/extern_template.cpp examples/c++11/helpers/extern_template_class.cpp)
add_test(examples/c++11/lambda.cpp)

# C++17 Features
add_test(examples/c++17/if_constexpr.cpp)
add_test(examples/c++17/declaration_in_if.cpp)

