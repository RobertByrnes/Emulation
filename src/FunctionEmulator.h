#ifndef FUNCTION_EMULATOR_H
#define FUNCTION_EMULATOR_H

#ifdef EMULATOR_LOG
#include <Logger.h>
#define EMULATION_LOG(x)  log_out<const char *>(x);
#else 
#define EMULATION_LOG(x)
#endif

#include "Emulator.h"
#include "ArgContext.h"
#include <algorithm>
#include <vector>
#include <any>
#include <string>

class FunctionEmulator : public Emulator {
public:
  explicit FunctionEmulator(std::string funcName) : _functionName(funcName), _callCount(0), _capturedArgs() {}
  
  virtual ~FunctionEmulator() {}

  /**
   * \brief Overrides the `returns` method to handle special behavior for specific functions and introduce delays.
   * 
   * This method captures the function call for the specified function name and records its call before delegating the behavior to the parent class.
   * It allows for a delay to be introduced after the function is called. This delay can be useful in testing scenarios where timing is critical.
   * 
   * \param func      std::string    - The name of the function for which the return value is being set.
   * \param var_t     any            - The return value to be set for the function.
   * \param delay_ms  int            - The delay in milliseconds to be introduced after the function is called. Default value is 0, meaning no delay.
   * 
   * \return Emulator& - Returns a reference to the Emulator, allowing for method chaining.
   */
  Emulator& returns(std::string func, any var_t, int delay_ms = 0) override {
    if (_functionName == func) {
      recordFunctionCall();
      EMULATION_LOG(("FunctionEmulator::returns() - " + func + " was called " + std::to_string(_callCount) + " times.").c_str());
    }
    return Emulator::returns(func, var_t, delay_ms);
  }

  /**
   * \brief Increments the count of function calls.
   * 
   * This method is used to track how many times a specific function has been called. 
   * Each time it's invoked, it increments an internal counter, `_callCount`, by one. 
   * This is useful in testing or mocking scenarios to verify the number of times a method has been triggered.
   * 
   */
  void recordFunctionCall() {
    _callCount++;
  }

  /**
   * \brief Checks if the function was called at least once.
   * 
   * This method returns `true` if the associated function has been invoked at least once, 
   * and `false` otherwise. It does this by checking the `_callCount` member variable.
   * 
   * \return bool Returns `true` if the function was called at least once, otherwise returns `false`.
   */
  bool wasCalled() {
    return _callCount > 0;
  }

  /**
   * \brief Resets the internal state of the function emulator.
   * 
   * This method sets the call count `_callCount` back to zero, clears the captured 
   * arguments from `_capturedArgs`, and then calls the parent class's reset method 
   * to handle any further reset requirements.
   * 
   * \note This method overrides the `reset` method in the base `Emulator` class.
   */
  void reset() override {
    _callCount = 0;
    _capturedArgs.clear();
    Emulator::reset();
    EMULATION_LOG(("FunctionEmulator::reset() - Reset function emulator for " + _functionName).c_str());
  }

  /**
   * \brief Retrieves the number of times the function has been called.
   * 
   * This method returns the current value of `_callCount`, which represents
   * the number of times the associated function has been invoked.
   * 
   * \return int The count of how many times the function has been called.
   */
  int timesCalled() const {
    return _callCount;
  }

  /**
   * \brief Captures and stores the arguments passed to the function.
   * 
   * This method captures a variable number of arguments and saves them 
   * in the `_capturedArgs` vector for later inspection. The arguments are 
   * stored as instances of `std::any`, allowing for flexibility in the 
   * types of captured arguments.
   * 
   * \tparam Args Variadic template argument representing any number of 
   * types of function arguments.
   * 
   * \param args A variable number of arguments to store.
   */
  template<typename... Args>
  void captureArgs(Args... args) {
    _capturedArgs.emplace_back(std::initializer_list<std::any>{args...});
  }

  /**
   * \brief Retrieves the captured arguments.
   * 
   * This method returns the arguments that were previously captured and stored 
   * in the `_capturedArgs` vector. It can be used to inspect or verify the arguments
   * passed to the mocked function during testing.
   * 
   * \return std::vector<std::vector<std::any>> - A nested vector where each inner vector contains 
   * the captured arguments of a particular function call, stored as instances of `std::any`.
   */
  ArgContext getArguments() const {
    ArgContext args(_capturedArgs);
    return args;
  }

  
private:
  /**
   * \brief The name of the function being emulated.
   * 
   * This variable stores the name of the function that this instance of the emulator is responsible for.
   * It is used to determine if a given call is intended for this particular function mock.
   * 
   */
  const std::string _functionName;

  /**
   * \brief Counter for the number of times the function has been called.
   * 
   * This variable increments every time the function being emulated is called. It allows the emulator
   * to keep track of the number of invocations.
   */
  int _callCount;

  /**
   * \brief Stores the arguments that were passed to the emulated function.
   * 
   * Each time the function is called, its arguments are captured and stored 
   * as a new vector inside this nested vector. This structure enables later 
   * inspection or verification of the arguments passed during testing.
   */
  CapturedArgs_t _capturedArgs;
};

#endif
