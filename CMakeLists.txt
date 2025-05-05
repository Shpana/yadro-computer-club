cmake_minimum_required(VERSION 3.28)
project(yadro_computer_club)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(yadro_computer_club main.cpp)
target_link_libraries(yadro_computer_club
        PUBLIC yadro_computer_club_lib
)
