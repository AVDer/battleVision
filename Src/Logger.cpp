#include "Logger.h"

Logger::LoggingLevel Logger::logging_level_{LoggingLevel::LoggingTrace};
std::hash<std::thread::id> Logger::hasher_;
