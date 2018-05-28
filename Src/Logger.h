/******************************************************************************
This file is part of battleVision.

battleVision is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

battleVision is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with battleVision.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef SC_LOGGER_H
#define SC_LOGGER_H

#include <cstdio>
#include <ctime>
#include <thread>

#include "boost/date_time/posix_time/posix_time.hpp"

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

class Logger {
 public:
  enum LoggingLevel {
    LoggingVerbose = -1,
    LoggingTrace,
    LoggingDebug,
    LoggingInfo,
    LoggingWarning,
    LoggingError
  };

  static Logger& logger() {
    static Logger instance;
    return instance;
  }

  static void set_logging_level(LoggingLevel level) { logging_level_ = level; }

  template <typename... I>
  static void error(I... items) {
    if (logging_level_ <= LoggingError) {
      print_time();
      printf("%s", KRED);
      printf("Error: ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

  template <typename... I>
  static void warning(I... items) {
    if (logging_level_ <= LoggingWarning) {
      print_time();
      printf("%s", KMAG);
      printf("Warn : ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

  template <typename... I>
  static void info(I... items) {
    if (logging_level_ <= LoggingInfo) {
      print_time();
      printf("%s", KGRN);
      printf("Info : ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

  template <typename... I>
  static void debug(I... items) {
    if (logging_level_ <= LoggingDebug) {
      print_time();
      printf("%s", KCYN);
      printf("Debug: ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

  template <typename... I>
  static void trace(I... items) {
    if (logging_level_ <= LoggingTrace) {
      print_time();
      printf("%s", KWHT);
      printf("Trace: ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

  template <typename... I>
  static void verbose(I... items) {
    if (logging_level_ <= LoggingVerbose) {
      print_time();
      printf("%s", KWHT);
      printf("Verb : ");
      printf(items...);
      printf("\n");
      printf("%s", KNRM);
    }
  }

 private:
  Logger();

  void static print_time() {
    printf("%s T:%zX ",
           boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::local_time())
               .substr(12)
               .c_str(),
           hasher_(std::this_thread::get_id()));
  }

  static LoggingLevel logging_level_;
  static std::hash<std::thread::id> hasher_;
};

#endif