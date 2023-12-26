add_library(budp STATIC src/udp_socket.c src/socket.c)
target_include_directories(budp PUBLIC ./include)

add_executable(test test/main.c)
target_link_libraries(test budp)