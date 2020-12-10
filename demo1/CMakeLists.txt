CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(demo1)

set(CMALE_CXX_COMPILER "/usr/bin/g++")

set(GLAD_SRC ../glad/src/glad.c)

aux_source_directory(src DEMO_SRC)

add_executable(demo1 ${DEMO_SRC} ${GLAD_SRC})

target_link_libraries(demo1 -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor)






