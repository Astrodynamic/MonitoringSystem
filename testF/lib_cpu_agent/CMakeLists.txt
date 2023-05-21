cmake_minimum_required(VERSION 3.14)

project(lib_cpu_agent LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(lib_cpu_agent SHARED
  lib_cpu_agent_global.h
  lib_cpu_agent.cpp
  lib_cpu_agent.h
)

target_link_libraries(lib_cpu_agent PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(lib_cpu_agent PRIVATE LIB_CPU_AGENT_LIBRARY)
