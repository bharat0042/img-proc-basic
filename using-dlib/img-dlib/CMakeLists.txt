cmake_minimum_required(VERSION 3.5)

project(img-dlib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:/Dev/projects/libs/dlib-19.6/build/install/include")

add_executable(img-dlib main.cpp)

target_link_libraries(img-dlib "C:/Dev/projects/libs/dlib-19.6/build/install/lib/dlib.lib")
