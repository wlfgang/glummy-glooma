cmake_minimum_required(VERSION 3.0)
project(glummy-glooma)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(glummy-glooma main.cpp)

target_include_directories(glummy-glooma PUBLIC
    ${CONAN_INCLUDE_DIRS}
    )

target_link_directories(glummy-glooma PUBLIC
    ${CONAN_LIB_DIRS}
    )

target_link_libraries(glummy-glooma
    ${CONAN_LIBS}
    )
