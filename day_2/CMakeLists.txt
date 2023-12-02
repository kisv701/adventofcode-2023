set(APPLICATION_NAME day_2)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR} "*.cpp" "*.h")

add_executable(
  ${APPLICATION_NAME}
  ${SOURCES}
)

include_directories("${CMAKE_SOURCE_DIR}/utils")
target_link_libraries(${APPLICATION_NAME} PUBLIC utils)

configure_file(input.txt input.txt COPYONLY)
