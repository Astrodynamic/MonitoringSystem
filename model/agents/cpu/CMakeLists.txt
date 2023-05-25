cmake_minimum_required(VERSION 3.5)

project(cpu_agent VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.2 COMPONENTS Core REQUIRED)

set(HEADERS
  cpu_agent.h
  ../agent/agent.h
  ../../settings/agent/agent_settings.h
)

set(SOURCES
  agent.json
  cpu_agent.cc
  ../agent/agent.cc
  ../../settings/agent/agent_settings.cc
)

set(PROJECT_SOURCES
  ${HEADERS}
  ${SOURCES}
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../agent
  ${CMAKE_CURRENT_SOURCE_DIR}/../../settings/agent
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    SUFFIX .so
    # CXX_VISIBILITY_PRESET hidden
    # VISIBILITY_INLINES_HIDDEN 1
    LIBRARY_OUTPUT_DIRECTORY ${LBD_TARGET}/agents/${PROJECT_NAME}
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "cpu_agent")

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTOUIC TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES AUTORCC TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES QT_PLUGIN TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES QT_VERSION_MAJOR ${Qt6Core_VERSION_MAJOR})
set_target_properties(${PROJECT_NAME} PROPERTIES QT_VERSION_MINOR ${Qt6Core_VERSION_MINOR})

target_compile_definitions(${PROJECT_NAME} PRIVATE MYPLUGIN_LIBRARY)

target_compile_features(${PROJECT_NAME}
  PUBLIC
  cxx_std_17
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

#target_link_options(
#    ${PROJECT_NAME}
#    PRIVATE
#    # -fsanitize=address
#)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Qt6::Core
)

# Копируем файл настроек в выходную директорию
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/setting.json
    ${LBD_TARGET}/agents/${PROJECT_NAME}
)
