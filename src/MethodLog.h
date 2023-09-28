#ifndef METHOD_LOG_H
#define METHOD_LOG_H

#include <iostream>
#include <fstream>
#include <vector>
#include "MethodProfile.h"

using namespace std;

/**
 * \brief Provides logging functionality for method invocation profiles.
 *
 * The `MethodLog` class is utilized to log information about how mocked 
 * methods have been called during tests. It captures details such as 
 * the number of times a method has been invoked and the set of return 
 * values associated with each method.
 * 
 * Usage:
 * 1. Create an instance of `MethodLog`.
 * 2. After the test run, call `dumpMethodProfiles` to generate a log 
 *    detailing the invocation profile of each mocked method.
 * 
 * Example:
 * \code{.cpp}
 * MethodLog logger;
 * // ... [Tests and mocks run here]
 * logger.dumpMethodProfiles(myMethodList, "myTestMethodProfile");
 * \endcode
 * 
 * This will produce a file named `myTestMethodProfile.log` that contains 
 * information on how each method in `myMethodList` was invoked.
 * 
 * \note Ensure that the log file is closed appropriately or data may 
 * not be written as expected.
 */
class MethodLog {
public:
  ofstream _file;

  MethodLog() {}
  ~MethodLog() {}

  /**
   * \brief Dumps the method invocation profiles to a log file.
   *
   * Generates a detailed log file with information on method invocations,
   * such as the number of times they were invoked and their associated return values.
   * 
   * \param _methods   vector<MethodProfile> - List of methods with their associated invocation profiles.
   * \param filename   const char* - Name of the log file to be generated (without the .log extension).
   */
  void dumpMethodProfiles(vector<MethodProfile> _methods, const char * filename="method") {
    std::string fileName = std::string(filename) + ".log";
    _file.open(fileName.c_str());
    for (auto method_It = _methods.begin(); method_It != _methods.end(); ++method_It) {
      std::string time = (method_It->invoked == 1) ? "time" : "times"; 
      _file << "Method: " << method_It->methodName << "() [invoked " << method_It->invoked << " " << time << "] ";
      size_t nRetVals = method_It->then.size() + 1;
      std::string value = (nRetVals == 1) ? "value" : "values"; 
      _file << "with " << nRetVals << " return " << value << endl;
    }
  }
};

#endif
