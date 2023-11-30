set(LIBRARY_NAME utils)

file(GLOB SOURCES ${CMAKE_SOURCE_DIR} "*.cpp" "*.h")

add_library(
  ${LIBRARY_NAME}
  STATIC
  ${SOURCES}
)
