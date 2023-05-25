cmake_minimum_required(VERSION 3.5)

# Установить имя вашего проекта здесь
project(Agent)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# При необходимости настройте версию Qt
find_package(Qt6 6.2 REQUIRED COMPONENTS Core )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/agent
                     ${CMAKE_CURRENT_SOURCE_DIR}/agent_settings)
# Соберем библиотеку для плагина
add_library(Agent SHARED
        cpu_agent.cc
        cpu_agent.h
        agent/agent.cc
        agent/agent.h
        agent_settings/agent_settings.cc
        agent_settings/agent_settings.h
        agent.json
        )

# Добавляем линковку с потребляемыми библиотеками (если нужно)
target_link_libraries(Agent PRIVATE Qt6::Core)

# Указываем название плагина (должен соответствовать значению "implements" в plugin.json)
set_target_properties(Agent PROPERTIES OUTPUT_NAME "agent")

# Указываем целевой каталог, где будет размещаться плагин после сборки
set_target_properties(Agent PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/plugins")

# Указываем, что это является плагином для фреймворка Qt
set_target_properties(Agent PROPERTIES AUTOMOC TRUE)
set_target_properties(Agent PROPERTIES AUTOUIC TRUE)
set_target_properties(Agent PROPERTIES AUTORCC TRUE)
set_target_properties(Agent PROPERTIES QT_PLUGIN TRUE)
set_target_properties(Agent PROPERTIES QT_VERSION_MAJOR ${Qt6Core_VERSION_MAJOR})
set_target_properties(Agent PROPERTIES QT_VERSION_MINOR ${Qt6Core_VERSION_MINOR})

# Идентификаторы для экспорта
target_compile_definitions(Agent PRIVATE MYPLUGIN_LIBRARY)

# Указываем, что это плагин Qt и включаем его в автозагрузку приложения
install(TARGETS Agent DESTINATION "${PROJECT_BINARY_DIR}/plugins")
