cmake_minimum_required(VERSION 3.0)
project(MovingCameraDemo)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(libs/glfw)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories(
        libs/glfw/include
        ${FP3D_INCLUDE_DIRECTORIES}
)
file(COPY ../sample-obj/ DESTINATION sample-obj)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} FP3D)
