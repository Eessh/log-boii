#include "log_boii.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

/*
  * Returns string format of `log_level`.
  *
  */
const char* log_level_string(log_level level)
{
  switch(level)
  {
  case LOG_TRACE:
    return "TRACE";
  case LOG_DEBUG:
    return "DEBUG";
  case LOG_INFO:
    return "INFO ";
  case LOG_WARN:
    return "WARN ";
  case LOG_ERROR:
    return "ERROR";
  default:
    break;
  }
  return "FATAL";
}

/*
  * Returns time struct for current time.
  *
  */
struct tm* time_info()
{
  time_t rawtime;
  struct tm* time_info;

  time(&rawtime);
  time_info = localtime(&rawtime);

  return time_info;
}

/*
  * Base function for all logging functions.
  *
  * Use `log_level` properly :)
  *
  * References how to use log levels properly:
  * https://stackoverflow.com/questions/2031163/when-to-use-the-different-log-levels
  * https://betterstack.com/community/guides/logging/log-levels-explained/
  *
  */
void log_boii(log_level level,
              const char* function,
              const char* file,
              int line,
              const char* format_string,
              ...)
{
  struct tm* timeinfo = time_info();

  // printing usual stuff: time, log level, function, file, line
  fprintf(stderr,
          "[%d:%d:%d] %s %s:%s:%d: ",
          timeinfo->tm_hour,
          timeinfo->tm_min,
          timeinfo->tm_sec,
          log_level_string(level),
          function,
          file,
          line);

  // handling variable arguments
  va_list format_args;
  va_start(format_args, format_string);
  vfprintf(stderr, format_string, format_args);
  va_end(format_args);

  fprintf(stderr, "\n");
}
