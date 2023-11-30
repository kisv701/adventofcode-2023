cmake_minimum_required(VERSION 3.22)

project(advent_of_code)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(utils)

foreach(day_num RANGE 25)
    set(DIR_NAME "day_${day_num}")
    if(EXISTS ${CMAKE_CURRENT_LIST_DIR}/${DIR_NAME})
        add_subdirectory(${DIR_NAME})
    endif()
endforeach()
