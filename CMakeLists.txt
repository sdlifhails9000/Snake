cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_C_STANDARD "11")
set(CMAKE_C_STANDARD_REQUIRED TRUE)

project("snake" "C")

find_package(Curses REQUIRED)

add_executable("snake" "main.c")

target_link_libraries(
    "snake"
    "${CURSES_LIBRARIES}"
)

target_include_directories(
    "snake"
    PRIVATE "${PROJECT_SOURCE_DIR}/inc"
    PUBLIC "${CURSES_INCLUDE_DIR}"
)

target_sources(
    "snake"
    PRIVATE "${PROJECT_SOURCE_DIR}/snake.c"
)

