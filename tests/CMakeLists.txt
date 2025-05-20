include(FetchContent)
FetchContent_Declare(gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 # release-1.17.0
)
FetchContent_MakeAvailable(gtest)

add_executable(run_tests
        computer_club_tests.cpp)
target_include_directories(run_tests
        PUBLIC ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(run_tests
        PUBLIC yadro_computer_club_lib
        PUBLIC GTest::gtest_main
)
target_compile_definitions(run_tests
        PUBLIC STATIC_FILES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/static"
)