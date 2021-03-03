cmake_minimum_required(VERSION 3.17)
project(notifire CXX)

set(CMAKE_CXX_STANDARD 17)
set(WITH_XKB ON)

add_subdirectory(lib)

#get_target_property(XPP_INCLUDES xpp INCLUDE_DIRECTORIES)
#include_directories(${XPP_INCLUDES})

add_executable(notifire main.cpp)

find_package(X11 REQUIRED)

target_link_libraries(notifire lib ${X11_LIBRARIES})