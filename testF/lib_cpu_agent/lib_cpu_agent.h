#pragma once

#include "lib_cpu_agent_global.h"
#include <QDebug>

class LIB_CPU_AGENT_EXPORT Lib_cpu_agent
{
public:
   LIB_CPU_AGENT_EXPORT void getMetrics();
private:
    Lib_cpu_agent() = delete; // запрещаем создание объекта класса
    Lib_cpu_agent(const Lib_cpu_agent&) = delete; // запрещаем копирование объекта класса
    ~Lib_cpu_agent() = delete; // запрещаем удаление объекта класса
};
