#include "logger.h"

using namespace std;

namespace Logger
{

  string getPrefix(LogType logType)
  {
    switch (logType)
    {
    case INFO:
      return "[INFO] ";
    case WARN:
      return "[WARNING] ";
    case ERROR:
      return "[ERROR] ";
    default:
      return "";
    }
  }

  void print(LogType type, string message)
  {
    cout << getPrefix(type) << message << endl;
  }

};