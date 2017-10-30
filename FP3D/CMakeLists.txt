cmake_minimum_required(VERSION 3.0)
project(FP3D)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if (NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
        lib/glfw/include
        lib/glad/include
        include
)
file(GLOB VENDORS_SOURCES lib/glad/src/glad.c)

add_library(${PROJECT_NAME} STATIC ${VENDORS_SOURCES} include/Mesh.h include/Point3.h include/Vector3.h src/Vector3.cpp src/Mesh.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
