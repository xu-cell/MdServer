cmake_minimum_required(VERSION 3.0)

project(Webserver)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


set(CXX_FLAGS
    -g
    -Wall
    -std=c++11
    -D_PTHREADS
    -Wno-unused-parameter
)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/include/base)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O0")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#替换
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# 将${CMAKE_BUILD_TYPE}转换为大写输出到BUILD_TYPE
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE)
#类似printf打印信息
message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_subdirectory(src/server)
add_subdirectory((src/base))
add_subdirectory(src/test)