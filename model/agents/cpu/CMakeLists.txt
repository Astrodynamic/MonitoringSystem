cmake_minimum_required(VERSION 3.1)

project(cpu_agent)

# добавляем путь к заголовочным файлам
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/../agent
  ${CMAKE_CURRENT_SOURCE_DIR}/../../settings/agent
)

set(HEADERS
    cpu_agent.h
    ../agent/agent.h
    ../../settings/agent/agent_settings.h
)

# список исходников
set(SOURCES
    cpu_agent.cc
    ../agent/agent.cc
    ../../settings/agent/agent_settings.cc
)

set(PROJECT_SOURCES
    ${HEADERS}
    ${SOURCES}
)

# создаем динамическую библиотеку
add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES})

# добавляем конфигурационный файл в сборку библиотеки
configure_file(settings.conf settings.conf COPYONLY)
