cmake_minimum_required(VERSION 3.5)

project(cpu_agent VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2
  COMPONENTS
  Core
  REQUIRED
)

set(HEADERS
  cpu_agent.h
  ../agent/agent.h
  ../../settings/agent/agent_settings.h
)

set(SOURCES
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
