cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

project(qslice-viewer)

find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories("src")

file(GLOB QSLICE_VIEWER_SRC src/*.h src/*.cpp)

add_executable(${PROJECT_NAME} ${QSLICE_VIEWER_SRC})
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
