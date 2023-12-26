add_library(budp++ STATIC src/socket.cpp)
target_link_libraries(budp++ PUBLIC budp)
target_include_directories(budp++ PUBLIC ./include)
target_include_directories(budp++ PRIVATE ../budp/include)

add_executable(budp++_test test/test.cpp)
target_link_libraries(budp++_test PRIVATE budp++)