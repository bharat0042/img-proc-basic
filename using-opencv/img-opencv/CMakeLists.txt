cmake_minimum_required(VERSION 3.5)

project(img-opencv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "C:/Dev/projects/libs/opencv/build/x64/vc15/lib")

add_executable(img-opencv main.cpp)

include_directories("C:/Dev/projects/libs/opencv/build/include")

find_package(OpenCV CONFIG REQUIRED)

target_link_libraries(img-opencv "C:/Dev/projects/libs/opencv/build/x64/vc15/lib/opencv_world453.lib")
