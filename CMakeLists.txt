cmake_minimum_required(VERSION 3.0)
project(FP3D)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if (NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
        3rd-party/glad/include
        include
)
file(GLOB VENDORS_SOURCES 3rd-party/glad/src/glad.c)

add_library(${PROJECT_NAME} STATIC ${VENDORS_SOURCES} include/Mesh.h include/Point3.h include/Vector3.h src/Vector3.cpp
        src/Mesh.cpp include/Scene.h include/OGLRenderer.h src/OGLRenderer.cpp src/Camera.cpp include/Camera.h
        src/Matrix4.cpp include/Matrix4.h src/ShaderProgram.cpp src/ShaderProgram.h src/Vertex.cpp src/Vertex.h src/Triangle.cpp src/Triangle.h src/Light.cpp include/Light.h src/Object3D.cpp src/Object3D.h include/Material.h)
target_link_libraries(${PROJECT_NAME} ${GLAD_LIBRARIES})

list(APPEND FP3D_INCLUDE_DIRECTORIES "include")
add_subdirectory(demos/moving-camera-demo/)
add_subdirectory(demos/wx-demo)