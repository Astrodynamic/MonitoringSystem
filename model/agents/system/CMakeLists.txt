cmake_minimum_required(VERSION 3.15)

project(system_agent VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 6.2 COMPONENTS Core REQUIRED)

set(HEADERS
  system_agent.h
  ../agent/agent.h
  ../../settings/agent/agent_settings.h
)

set(SOURCES
  system_agent.cc
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
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN 1
    LIBRARY_OUTPUT_DIRECTORY ${LBD_TARGET}/agents/${PROJECT_NAME}
)

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

target_link_options(
    ${PROJECT_NAME}
    PRIVATE

    # -fsanitize=address
)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt6::Core)

# Копируем файл настроек в выходную директорию
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/setting.json
    ${LBD_TARGET}/agents/${PROJECT_NAME}
)
