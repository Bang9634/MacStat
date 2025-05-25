cmake_minimum_required(VERSION 3.16)
project(mac_stat VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

include_directories(
    ${Qt6Widgets_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/system_stats/memory_stats.cpp
)

set(HEADERS
    include/mainwindow.h
    include/system_stats/memory_stats.h
)

add_executable(mac_stat
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(mac_stat PRIVATE
    Qt6::Widgets
    "-framework IOKit"
    "-framework CoreFoundation"
)

target_include_directories(mac_stat PRIVATE
    ${CMAKE_SOURCE_DIR}/include
) 