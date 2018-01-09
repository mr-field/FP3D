cmake_minimum_required(VERSION 3.0)
project(WxDemo)

set(wxBUILD_SHARED OFF)
set(wxBUILD_TESTS OFF)
set(wxBUILD_SAMPLES OFF)
add_subdirectory(3rd-party/wxWidgets)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories(
        3rd-party/wxWidgets/include
        FP3D/include
)

add_executable(${PROJECT_NAME} App.cpp App.h MainWindow.cpp MainWindow.h OGLViewer.cpp OGLViewer.h)
target_link_libraries(${PROJECT_NAME} gl core base FP3D)
