project(Cpp11Features)

add_executable(TestNullptr nullptr.cpp)
target_link_libraries(TestNullptr gtest_main gtest Threads::Threads)
