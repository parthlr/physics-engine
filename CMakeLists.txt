cmake_minimum_required(VERSION 3.15)
project(physics_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(physics_engine main.cpp TransformObject.cpp TransformObject.h Physics.cpp Physics.h polygons/Polygon.cpp polygons/Polygon.h polygons/Circle.cpp polygons/Circle.h)