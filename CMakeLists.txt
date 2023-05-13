cmake_minimum_required(VERSION 3.19)

project(MonitoringSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS
    Quick
    QuickControls2
    REQUIRED
)

if(APPLE)
    set(MACOSX_BUNDLE_ICON_FILE appicon.png)
    set(app_icon "${CMAKE_CURRENT_SOURCE_DIR}/data/icon/appicon.png")
    set_source_files_properties(${app_icon} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
endif()

set(PROJECT_RESOURCES
    main.cc
)

qt_add_executable(${PROJECT_NAME}
    ${PROJECT_RESOURCES}
    ${app_icon}
)

qt6_add_resources(${PROJECT_NAME} "qml"
    PREFIX "/"
    BASE module
    FILES
    module/Main.qml
)

qt6_add_resources(${PROJECT_NAME} "controls"
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
    # -fsanitize=address
)

target_link_options(
    ${PROJECT_NAME}
    PRIVATE

    # -fsanitize=address
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt6::Quick
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
elseif(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        WIN32_EXECUTABLE TRUE
        LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif()

qt_finalize_executable(${PROJECT_NAME})

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