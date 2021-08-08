cmake_minimum_required(VERSION 3.13.4)

project(stb_image)

add_library(
  stb_image
  stb_image.h
  stb_image.cpp
)

target_include_directories(stb_image
  PUBLIC .
)