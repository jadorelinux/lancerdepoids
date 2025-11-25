cmake_minimum_required(VERSION 3.14)
project(LancerDePoids LANGUAGES CXX)

# Recherche de Python et NumPy
find_package(Python3 COMPONENTS Interpreter Development NumPy REQUIRED)

include_directories(${Python3_INCLUDE_DIRS})
include_directories(${Python3_NumPy_INCLUDE_DIRS})
include_directories(matplotlib-cpp)

add_executable(LancerDePoids LancerDePoids.cpp)
target_link_libraries(LancerDePoids ${Python3_LIBRARIES})
set_target_properties(LancerDePoids PROPERTIES OUTPUT_NAME "LancerDePoids")
