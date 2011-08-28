# openLima & LimaBeans

cmake_minimum_required(VERSION 2.6)
project(openLima)

set(Boost_USE_STATIC_LIBS ON)
add_definitions(-D_UNICODE -DUNICODE)

add_subdirectory(openLima)
add_subdirectory(LimaBeans)