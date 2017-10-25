cmake_minimum_required(VERSION 3.0)
project(Create3DEngine)
set(PROJECT_BINARY_DIR, "build")

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(include/glfw)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
    if (NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
	include/glfw/include
	include/glad/include
)
file(GLOB VENDORS_SOURCES include/glad/src/glad.c)

add_executable(${PROJECT_NAME} main.cpp ${VENDORS_SOURCES})
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} ${GLAD_LIBRARIES})
