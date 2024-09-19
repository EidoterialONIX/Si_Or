cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(add_tools)

add_library(add_tools STATIC src/Vectors.cpp include/Vectors.h)
target_include_directories(add_tools PUBLIC include/)