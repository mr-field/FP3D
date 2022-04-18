cmake_minimum_required(VERSION 3.0)
project(WxDemo)

find_package(wxWidgets COMPONENTS gl core base)
if (wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
else()
    set(wxBUILD_SHARED OFF)
    set(wxBUILD_TESTS OFF)
    set(wxBUILD_SAMPLES OFF)
    set(wxUSE_XRC OFF)
    add_subdirectory(3rd-party/wxWidgets)

    include_directories(3rd-party/wxWidgets/include)
    list(APPEND wxWidgets_LIBRARIES "gl" "core" "base")
endif()

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

include_directories(
        FP3D/include
)
file(COPY ../sample-obj/ DESTINATION sample-obj)

add_executable(${PROJECT_NAME} App.cpp App.h MainWindow.cpp MainWindow.h RayTraceViewer.cpp RayTraceViewer.h ControlPanel.cpp ControlPanel.h)
target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES} FP3D)

install(TARGETS ${PROJECT_NAME} DESTINATION demos)
