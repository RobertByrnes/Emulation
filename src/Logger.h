#pragma once
#undef abs // remove abs macro from Arduino.h
#undef round // remove round macro from Arduino.h
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>

using namespace std;

/**
 * \file
 * Provides utilities for logging to an emulation log file.
 */

/**
 * \brief Global ofstream object for the emulation log file.
 *
 * This ofstream object represents the log file "emulation.log" which is used 
 * to capture and store logging information related to the emulation process.
 */
ofstream logFile("emulation.log");

/**
 * \brief Retrieves the current timestamp as a string.
 * 
 * This function captures the current time and formats it into a readable 
 * string format suitable for logging.
 *
 * \return std::string   The formatted current timestamp.
 */
std::string currentTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
  auto epoch = seconds.time_since_epoch();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) - epoch;

  std::time_t time = std::chrono::system_clock::to_time_t(now);
  std::tm tm;
  localtime_s(&tm, &time); // Use `localtime_r` for POSIX systems

  std::ostringstream timestampStream;
  timestampStream << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S") << "." << std::setw(6) << std::setfill('0') << millis.count() << "]";
  return timestampStream.str();
}

/**
 * \brief Logs the given output to the emulation log file with a timestamp prefix.
 *
 * This templated function logs the provided input data with a timestamp prefix 
 * to the "emulation.log" file.
 *
 * \tparam T    The type of the output data to be logged.
 * 
 * \param output   T - The data to be logged.
 * 
 * Example:
 * \code{.cpp}
 * log_out("This is a log message.");
 * log_out(12345);
 * \endcode
 */
template<typename T>
void log_out(T output) { 
  logFile << currentTimestamp() << " " << output << std::endl;
}
