cmake_minimum_required(VERSION 3.0)
project(MovingCameraDemo)

if (MSVC)
    option(GLFW_BUILD_DOCS OFF)
    option(GLFW_BUILD_EXAMPLES OFF)
    option(GLFW_BUILD_TESTS OFF)
    add_subdirectory(3rd-party/glfw)
    include_directories(
        3rd-party/glfw/include
    )
else()
    find_package(glfw3 3 REQUIRED)
    include_directories(${GLFW_INCLUDE_DIRS})
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories(
        ${FP3D_INCLUDE_DIRECTORIES}
)
file(COPY ../sample-obj/ DESTINATION sample-obj)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES} FP3D)

install(TARGETS ${PROJECT_NAME} DESTINATION demos)
