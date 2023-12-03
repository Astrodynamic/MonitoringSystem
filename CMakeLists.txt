cmake_minimum_required(VERSION 3.19)

project(MonitoringSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(CURL REQUIRED)

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Gui
    Core
    Quick
    QuickControls2
)

include_directories(
    ${CURL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/model/manager/notification
    ${CMAKE_CURRENT_SOURCE_DIR}/model/manager/watcher
    ${CMAKE_CURRENT_SOURCE_DIR}/model/manager/config
    ${CMAKE_CURRENT_SOURCE_DIR}/model/settings/agent
    ${CMAKE_CURRENT_SOURCE_DIR}/model/manager/agent
    ${CMAKE_CURRENT_SOURCE_DIR}/model/agents/agent
    ${CMAKE_CURRENT_SOURCE_DIR}/model/manager/log
    ${CMAKE_CURRENT_SOURCE_DIR}/model/kernel
)

set(HEADERS
    model/manager/notification/notification_manager.h
    model/manager/watcher/watcher_manager.h
    model/manager/config/config_manager.h
    model/settings/agent/agent_settings.h
    model/manager/agent/agent_manager.h
    model/manager/log/log_manager.h
    model/agents/agent/agent.h
    model/kernel/kernel.h
)

set(SOURCES
    model/manager/notification/notification_manager.cc
    model/manager/watcher/watcher_manager.cc
    model/manager/config/config_manager.cc
    model/settings/agent/agent_settings.cc
    model/manager/agent/agent_manager.cc
    model/manager/log/log_manager.cc
    model/agents/agent/agent.cc
    model/kernel/kernel.cc
)

set(PROJECT_RESOURCES
    ${HEADERS}
    ${SOURCES}
    main.cc
)

qt_add_executable(${PROJECT_NAME}
    ${PROJECT_RESOURCES}
)

qt_add_resources(${PROJECT_NAME} "icon"
    PREFIX "/"
    BASE data/icon
    FILES
    data/icon/appicon.png
)

qt_add_resources(${PROJECT_NAME} "qml"
    PREFIX "/"
    BASE module
    FILES
    module/Main.qml
    module/Agents.qml
    module/Logs.qml
    module/Settings.qml
)

qt_add_resources(${PROJECT_NAME} "controls"
    PREFIX "/"
    BASE styles
    FILES
    styles/qtquickcontrols2.conf
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE

    # -Wall
    # -Werror
    # -Wextra
    # -Wpedantic
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Gui
    Qt6::Core
    Qt6::Quick
    CURL::libcurl
    Qt6::QuickControls2
)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        INSTALL_RPATH "$ORIGIN"
    )
else()
    message(FATAL_ERROR "unsupported platform")
endif()

set(PROJECT_FOLDER "/tmp/MonitoringSystem")

add_definitions(
    -DPROJECT_FOLDER="${PROJECT_FOLDER}"
)

# Add cppcheck
find_program(CPPCHECK cppcheck)

if(CPPCHECK)
    message(STATUS "cppcheck found: ${CPPCHECK}")
    list(
        APPEND CPPCHECK_ARGS
        "--enable=all"
        "--inconclusive"
        "--quiet"
        "--language=c++"
        "--std=c++17"
        "--suppress=missingInclude"
        "--verbose"
    )
    add_custom_target(
        cppcheck
        COMMAND ${CPPCHECK} ${CPPCHECK_ARGS} ${PROJECT_RESOURCES}
    )
else()
    message(STATUS "cppcheck not found")
endif()

# Add clang-format
find_program(CLANG_FORMAT clang-format)

if(CLANG_FORMAT)
    message(STATUS "clang-format found: ${CLANG_FORMAT}")
    list(
        APPEND CLANG_ARGS
        "-i"
        "-style=Google"
        "--verbose"
    )
    add_custom_target(
        clang-format
        COMMAND ${CLANG_FORMAT} ${CLANG_ARGS} ${PROJECT_RESOURCES}
    )
else()
    message(STATUS "clang-format not found")
endif()
