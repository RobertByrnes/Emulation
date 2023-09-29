#ifndef EMULATION_FRAME_H
#define EMULATION_FRAME_H

#include <Arduino.h>
#include <unity.h>
#include <ctime>
#include <cstdarg>
#include "FunctionEmulator.h"
#include "TimeFunctionEmulators.h"

/**
 * \var MillisFunctionEmulator millisEmulator
 * \brief An instance of the MillisFunctionEmulator class.
 * 
 * This instance emulates the behavior of the millis function found in embedded 
 * systems, providing a controlled environment for time-sensitive testing scenarios.
 */
MillisFunctionEmulator millisEmulator;

/**
 * \var DelayFunctionEmulator delayEmulator
 * \brief An instance of the DelayFunctionEmulator class.
 * 
 * This instance simulates the behavior of the delay function found in embedded 
 * systems. Instead of causing an actual delay, it provides a test-friendly emulation 
 * ensuring that unit tests run efficiently without real-world waiting.
 */
DelayFunctionEmulator delayEmulator;

/**
 * \var FunctionEmulator log_d_stub
 * \brief An emulator instance for the debug log function.
 * 
 * This instance emulates the behavior of the debug log function (typically represented as "log_d" in embedded systems). 
 * It captures and logs debug messages for testing and verification purposes.
 */
FunctionEmulator log_d_stub("log_d");

/**
 * \var FunctionEmulator log_i_stub
 * \brief An emulator instance for the info log function.
 * 
 * This instance emulates the behavior of the info log function (typically represented as "log_i" in embedded systems). 
 * It captures and logs informational messages for testing and verification purposes.
 */
FunctionEmulator log_i_stub("log_i");

/**
 * \var FunctionEmulator log_w_stub
 * \brief An emulator instance for the warning log function.
 * 
 * This instance emulates the behavior of the warning log function (typically represented as "log_w" in embedded systems). 
 * It captures and logs warning messages for testing and verification purposes.
 */
FunctionEmulator log_w_stub("log_w");

/**
 * \var FunctionEmulator log_e_stub
 * \brief An emulator instance for the error log function.
 * 
 * This instance emulates the behavior of the error log function (typically represented as "log_e" in embedded systems). 
 * It captures and logs error messages for testing and verification purposes.
 */
FunctionEmulator log_e_stub("log_e");

/**
 * \var FunctionEmulator log_v_stub
 * \brief An emulator instance for the verbose log function.
 * 
 * This instance emulates the behavior of the verbose log function (typically represented as "log_v" in embedded systems). 
 * It captures and logs detailed verbose messages for testing and verification purposes.
 */
FunctionEmulator log_v_stub("log_v");

/**
 * \fn void log_d(const char* format, ...)
 * \brief Mocked debug log function.
 * 
 * Emulates the behavior of the debug log function, capturing the arguments
 * and recording the function call for testing and verification.
 * 
 * \param format Format string for the log message.
 * \param ... Variable arguments for the format string.
 */
void log_d(const char* format, ...) { 
  va_list args;
  va_start(args, format);
  log_d_stub.captureArgs(format, args);
  va_end(args);
  log_d_stub.recordFunctionCall();
}

/**
 * \fn void log_i(const char* format, ...)
 * \brief Mocked info log function.
 * 
 * Emulates the behavior of the info log function, capturing the arguments
 * and recording the function call for testing and verification.
 * 
 * \param format Format string for the log message.
 * \param ... Variable arguments for the format string.
 */
void log_i(const char* format, ...) { 
  va_list args;
  va_start(args, format);
  log_i_stub.captureArgs(format, args);
  va_end(args);
  log_i_stub.recordFunctionCall();
}

/**
 * \fn void log_v(const char* format, ...)
 * \brief Mocked verbose log function.
 * 
 * Emulates the behavior of the verbose log function, capturing the arguments
 * and recording the function call for testing and verification.
 * 
 * \param format Format string for the log message.
 * \param ... Variable arguments for the format string.
 */
void log_v(const char* format, ...) { 
  va_list args;
  va_start(args, format);
  log_v_stub.captureArgs(format, args);
  va_end(args);
  log_v_stub.recordFunctionCall();
}

/**
 * \fn void log_w(const char* format, ...)
 * \brief Mocked warning log function.
 * 
 * Emulates the behavior of the warning log function, capturing the arguments
 * and recording the function call for testing and verification.
 * 
 * \param format Format string for the log message.
 * \param ... Variable arguments for the format string.
 */
void log_w(const char* format, ...) { 
  va_list args;
  va_start(args, format);
  log_w_stub.captureArgs(format, args);
  va_end(args);
  log_w_stub.recordFunctionCall();
}

/**
 * \fn void log_e(const char* format, ...)
 * \brief Mocked error log function.
 * 
 * Emulates the behavior of the error log function, capturing the arguments
 * and recording the function call for testing and verification.
 * 
 * \param format Format string for the log message.
 * \param ... Variable arguments for the format string.
 */
void log_e(const char* format, ...) { 
  va_list args;
  va_start(args, format);
  log_e_stub.captureArgs(format, args);
  va_end(args);
  log_e_stub.recordFunctionCall();
}

/**
 * \fn void resetEmulators()
 * \brief Resets all emulators to their default state.
 * 
 */
void resetEmulators() {
  millisEmulator.resetMillis();
  log_d_stub.reset();
  log_i_stub.reset();
  log_v_stub.reset();
  log_w_stub.reset();
  log_e_stub.reset();
}

#if not defined(ARDUINO)
  #define delay(x) delayEmulator.mockDelay(x)
  #define millis() millisEmulator.mockMillis()
  #define ResetEmulators() resetEmulators()
#endif

#endif // end of EMULATION_FRAME_H
