cmake_minimum_required(VERSION 3.0)
project(AnimationDemo)

find_package(wxWidgets COMPONENTS core base)
include(${wxWidgets_USE_FILE})

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories(
        FP3D/include
)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} FP3D)

install(TARGETS ${PROJECT_NAME})
