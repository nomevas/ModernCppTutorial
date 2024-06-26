cmake_minimum_required(VERSION 3.18)

project(ModernCppTutorial)

find_package(Threads)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

file(GLOB TEST_SRC ${PROJECT_SOURCE_DIR}/examples/**/*.cpp)

foreach (FILE_NAME IN LISTS TEST_SRC)
    get_filename_component(BARENAME ${FILE_NAME} NAME)
    add_executable(${BARENAME} ${FILE_NAME})
    target_link_libraries(${BARENAME} gtest_main gtest gmock Threads::Threads)
    add_test(NAME ${BARENAME} COMMAND ${BARENAME})
endforeach()

