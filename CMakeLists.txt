cmake_minimum_required(VERSION 3.18)

project(ModernCppTutorial)

include(GoogleTest)
include(cmake/add_test.cmake)

find_package(Threads)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

# C++11 Features
add_test(examples/c++11/auto.cpp)
add_test(examples/c++11/constexpr.cpp)
add_test(examples/c++11/initializer_list.cpp)
add_test(examples/c++11/nullptr.cpp)
add_test(examples/c++11/tuple.cpp)
add_test(examples/c++11/decltype.cpp)
add_test(examples/c++11/range_loop.cpp)
add_test(examples/c++11/using_alias.cpp)
add_test(examples/c++11/extern_template.cpp examples/c++11/extern_template_class.cpp examples/c++11/extern_template_class.h)

# C++17 Features
add_test(examples/c++17/if_constexpr.cpp)
add_test(examples/c++17/declaration_in_if.cpp)

