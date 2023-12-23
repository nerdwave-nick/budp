cmake_minimum_required(VERSION 3.10)

project(budp
    VERSION 0.1
    DESCRIPTION "BUDP - A UDP based protocol for reliable/unreliable connection-based data transfer"
    LANGUAGES C CXX
)

add_subdirectory(budp)
add_subdirectory(budp++)