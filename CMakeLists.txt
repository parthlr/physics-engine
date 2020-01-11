cmake_minimum_required(VERSION 3.15)
project(physics_engine)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp glad.c TransformObject.cpp TransformObject.h Physics.cpp Physics.h polygons/Polygon.cpp polygons/Polygon.h polygons/Circle.cpp polygons/Circle.h TransformObject.cpp TransformObject.h Physics.cpp Physics.h polygons/Polygon.cpp polygons/Polygon.h polygons/Circle.cpp polygons/Circle.h polygons/Rectangle.cpp polygons/Rectangle.h Application.cpp Application.h shaders/Shader.cpp shaders/Shader.h)

add_executable(physics_engine ${SOURCE_FILES})
target_link_libraries(physics_engine -lglfw3 -lopengl32 -lgdi32)