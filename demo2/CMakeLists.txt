CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(demo2)

set(CMALE_CXX_COMPILER "/usr/bin/g++")

set(GLAD_SRC ../glad/src/glad.c)

aux_source_directory(src DEMO_SRC)

add_executable(demo2 ${DEMO_SRC} ${GLAD_SRC})

target_link_libraries(demo2 -lglfw3 -lGL -lm -lXrandr -lXi -lX11 -lXxf86vm -lpthread -ldl -lXinerama -lXcursor)






