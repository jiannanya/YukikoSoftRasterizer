cmake_minimum_required(VERSION 3.20)

project(fallment_soft_rasterizer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQIUIRED True)

file(GLOB_RECURSE APP_SRC ${CMAKE_SOURCE_DIR}/src/*.hh ${CMAKE_SOURCE_DIR}/src/*.cc)

# message("APP_SRC: ${APP_SRC}")

# add_definitions(-D_MSC_VER)

add_subdirectory("case/Phong")
