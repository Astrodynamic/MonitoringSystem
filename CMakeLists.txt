cmake_minimum_required(VERSION 3.19)

project(MonitoringSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
    Quick
    REQUIRED
)

set(PROJECT_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cc
)

qt_add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE}
)

qt_add_qml_module(${PROJECT_NAME}
    URI WINDOW
    VERSION 1.0
    QML_FILES
    components/Main.qml
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
)
