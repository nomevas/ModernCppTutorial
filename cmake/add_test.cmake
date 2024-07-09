
function(add_test TEST_FILE_NAME)
    get_filename_component(DIR_PATH ${TEST_FILE_NAME} DIRECTORY)
    string(REPLACE "examples/" "" DIR_NAME ${DIR_PATH})
    get_filename_component(BARENAME ${TEST_FILE_NAME} NAME_WLE)
    SET(TEST_NAME ${DIR_NAME}_${BARENAME}_test)
    add_executable(${TEST_NAME} ${TEST_FILE_NAME} ${ARGV})
    target_link_libraries(${TEST_NAME} gtest_main gtest gmock Threads::Threads)
    gtest_discover_tests(${TEST_NAME})
endfunction()