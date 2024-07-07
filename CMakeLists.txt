cmake_minimum_required(VERSION 3.18)

project(ModernCppTutorial)

include(GoogleTest)

find_package(Threads)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

SET(TEST_SRC
    examples/c++11/auto.cpp 
    examples/c++11/constexpr.cpp
    examples/c++11/initializer_list.cpp
    examples/c++11/nullptr.cpp
    examples/c++11/tuple.cpp
    examples/c++17/declaration_in_if.cpp)

foreach (FILE_NAME IN LISTS TEST_SRC)
    get_filename_component(DIR_PATH ${FILE_NAME} DIRECTORY)
    string(REPLACE "examples/" "" DIR_NAME ${DIR_PATH})
    get_filename_component(BARENAME ${FILE_NAME} NAME_WLE)
    SET(TEST_NAME ${DIR_NAME}_${BARENAME}_test)
    add_executable(${TEST_NAME} ${FILE_NAME})
    target_link_libraries(${TEST_NAME} gtest_main gtest gmock Threads::Threads)
    gtest_discover_tests(${TEST_NAME})
endforeach()