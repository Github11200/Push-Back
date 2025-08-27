#ifndef LOGGER_H
#define LOGGER_H

#include "vex.h"

namespace Logger
{

  enum LogType
  {
    INFO = 0,
    WARN = 1,
    ERROR = 2
  };

  std::string getPrefix(LogType logType);

  void print(LogType type, std::string message);

};

#endif