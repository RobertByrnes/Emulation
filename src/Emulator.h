#pragma once

// TODO move to package
#if not defined(EMULATOR_H)
#define EMULATOR_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <EmulationInterface.h>
#include <Exceptions/NoReturnValueException.h>
#include <iostream>
#include <ostream>
#include <unistd.h>

unsigned int microseconds = 1000000;

using namespace std;

#define PSUEDO_EXCEPTION_NO_RET_VAL         (10000)
#define PSUEDO_EXCEPTION_NO_EXCEPT          (20000)

#ifdef EMULATOR_LOG
#include <Logger.h>
#define EMULATION_LOG(x)                    log_out<const char *>(x);
#else 
#define EMULATION_LOG(x)
#endif

/**
 * \class Emulator
 * \brief Provides emulation capabilities for various functionalities.
 * 
 * The Emulator class serves as a base for emulating different aspects 
 * of a system, primarily for testing purposes. Derived from the EmulationInterface, 
 * this class provides the foundational structure and methods that can be 
 * expanded upon in child classes to offer more specific emulation functionalities.
 */
class Emulator : public EmulationInterface {
public:    
  /**
   * \brief Default constructor for the Emulator class.
   * 
   * Initializes an instance of the Emulator. Any setup needed for 
   * the basic emulation capabilities can be added here.
   */
  Emulator() {}

    /**
   * \brief Destructor for the Emulator class.
   * 
   * Handles any necessary cleanup and resource deallocation for an instance 
   * of the Emulator when it goes out of scope or is explicitly deleted. If the class
   * holds resources like memory allocations or open file handles, ensure they are 
   * freed or closed here.
   */
  ~Emulator() {}

  /**
   * \brief Sets the inactive period for this class instance.
   *
   * Specifies a duration for which the emulator should pause or be inactive.
   * This function sets a wait time to simulate delays or other time-based behaviors.
   *
   * \param seconds   int  - The duration of the inactivity period in seconds.
   */
  void waits(int seconds) { _wait = seconds; }

  /**
   * \brief Pauses the emulator for the previously set wait time.
   *
   * This function will cause the emulator to pause for the duration specified
   * using the waits() method. If no wait time was set or if the wait time is 
   * set to zero or a negative value, the function will return immediately without 
   * causing any delay.
   */
  void await() {
    if (_wait <= 0) {
      return;
    } 
    usleep(_wait * microseconds);
  }

  /**
   * \brief Dumps the names and details of all methods stored in the _methods vector.
   * 
   * This method iterates over all MethodProfile objects in the _methods vector, 
   * printing their details to the standard output or a logging system. 
   * Useful for debugging or getting an overview of the current emulator state.
   */
  void dumpMethods() {
    for (const auto& method : _methods) {
      std::cout << "Method Name: " << method.methodName << std::endl;
      std::cout << "Return Value (count): " << method.retVal.first 
                << ", Value: " << std::any_cast<std::string>(method.retVal.second) << std::endl;
      std::cout << "Number of times method invoked: " << method.invoked << std::endl;

      if (!method.then.empty()) {
        std::cout << "Then values:" << std::endl;
        for (const auto& thenRetVal : method.then) {
          std::cout << "Count: " << thenRetVal.first 
                    << ", Value: " << std::any_cast<std::string>(thenRetVal.second) << std::endl;
        }
      }
      std::cout << "---------------------" << std::endl;
    }
  }

  /**
   * \brief Configures a method's return value and optional delay for the mock.
   *
   * This function sets the return value and potential delay for a mocked method 
   * represented by its function name. When this mocked method is later called, 
   * it will return the configured return value after waiting for the specified delay.
   * 
   * \param func        const char* - The name of the method/function being mocked.
   * \param var_t       any - The value that the mocked function should return.
   * \param delay_ms    int - An optional delay in milliseconds to be applied before 
   *                   returning the value. Default is 0, meaning no delay.
   * 
   * \return Emulator&  A reference to the current Emulator instance, allowing for 
   *                   method chaining.
   */
  virtual Emulator& returns(const char * func, any var_t, int delay_ms = 0) {
    _lastFunc = func;
    RetVal retVal = { 1, var_t };
    vector<RetVal> then = {};
    MethodProfile method = { func, retVal, then, 0, delay_ms };
    _methods.push_back(method);
    return *this;
  }

  /**
   * \brief Specifies how many times a mocked method should return a particular value.
   * 
   * This function defines the number of times a mocked method should return its 
   * configured value. The method to be configured must be previously set 
   * using the `returns` method.
   * 
   * \param n     int - The number of times the method should return its 
   *             configured value before moving on to any subsequently configured return value 
   *             (if any has been set using the `then` method).
   * 
   * \return Emulator&  A reference to the current Emulator instance, allowing for 
   *                   method chaining.
   *
   * \note If the `then` method has been used to set up a sequence of return values 
   *       for a method, calling `times` after `returns` but before `then` will 
   *       set the repetition count for the `returns` value. If called after 
   *       `then`, it sets the repetition count for the last `then` value.
   */
  Emulator& times(int n) {     
    for (auto method_It = _methods.begin(); method_It != _methods.end(); ++method_It) {
      if (method_It->methodName == _lastFunc) {
        if (method_It->then.size() == 0) {
          method_It->retVal.first = n;
        } else {
          RetVal retVal = method_It->then.back();
          retVal.first = n;
        }
        break;
      }
    }
    return *this;
  }

  /**
   * \brief Chains another return value to the last configured mocked method.
   * 
   * After a method's return behavior is set with `returns`, this function 
   * allows for chaining additional return values in sequence. The method will 
   * return its initially configured value (from `returns`) the number of times 
   * specified by `times`. Once that count is exhausted, it will start returning 
   * the values specified by successive calls to `then`, in the order they were added.
   * 
   * \param var_t     std::any - The next return value to be used after the current 
   *                 value's repetition count (from `times`) has been exhausted.
   * 
   * \return Emulator&  A reference to the current Emulator instance, allowing for 
   *                   method chaining.
   *
   * \note The `returns` method must be called before calling `then` to specify 
   *       the initial return behavior of the mocked method.
   */
  Emulator& then(any var_t) {
    for (auto method_It = _methods.begin(); method_It != _methods.end(); ++method_It) {
      if (method_It->methodName == _lastFunc) {
        RetVal retVal = { 1, var_t };
        method_It->then.push_back(retVal);
        break;
      }
    }
    return *this; 
  }

  /**
   * \brief Configures a mock method to throw an exception.
   * 
   * When the specified mock method is called, instead of returning 
   * a value, it will throw the provided exception.
   * 
   * \param func          const char* - The name of the mock method for which 
   *                     the exception behavior is to be set.
   * \param exception     uint16_t - The numeric exception code to be thrown 
   *                     when the mock method is called.
   * 
   * \note The current implementation uses a map for storing exception 
   *       configurations, but future versions might use a pair for 
   *       improved efficiency.
   * 
   * \todo Refactor the method to move the logic into the 'Invokable' class.
   * \todo Consider changing the data structure from std::map to std::pair 
   *       for better performance.
   */
  void setException(const char * func, uint16_t exception) {     
    std::map<const char *, uint16_t> exceptionMap { { func, exception } };
    _exceptions.push_back(exceptionMap);
  }

  /**
   * \brief Resets the state of the emulator to its default state.
   * 
   * This function restores the emulator to its initial state by:
   * 1. Setting the wait time back to zero.
   * 2. Clearing all stored mock method profiles.
   * 3. Clearing all stored exceptions associated with mock methods.
   * 
   * This method is typically used between tests or scenarios to ensure
   * that previous configurations don't influence subsequent operations.
   * 
   * \note Subclasses can override this method to provide additional reset functionality.
   */
  virtual void reset() {
    _wait = 0;
    _methods.clear();
    _exceptions.clear();
  }

  /**
   * \brief Record the last exception throw by the class
   * 
   * \param exception 
   * 
   */
  void setInternalException(int exception) { _lastPsuedoException = exception; }

  /**
   * \brief Stores the provided method in the _methods vector.
   * 
   * \param methodName   const char* - The name of the method.
   * \param method       void (*method)() - A pointer to the method function.
   * \param var_t        std::any - A value of any type that the method should return.
   */
  void setMethod(const char *methodName, void (*method)(), std::any var_t) {
    RetVal retVal = { 1, var_t };
    vector<RetVal> then = {};
    MethodProfile invokableMethod = { methodName, retVal, then, 0, 0 };
    _methods.push_back(invokableMethod);
  }


  /**
   * \brief Records a call to a specified mock method.
   * 
   * Iterates through the list of available mock methods to find the 
   * specified one, then increments its call count to indicate it has 
   * been invoked. This function is useful for tracking how many times 
   * a mock method is called during testing.
   * 
   * \param methodName    const char* - The name of the mock method 
   *                      that is being invoked.
   * 
   * \note Currently, the actual method is commented out and only the 
   *       invocation count is incremented. If there are future plans 
   *       to actually call the method or do more, remember to modify 
   *       this doc-block accordingly.
   */
  void invokeMethod(const char * methodName) {
    for(auto method : _methods) {
      if (method.methodName == methodName) {    
        method.invoked += 1;
        // method.method();
        break;
      }
    }
  }

  /**
   * \brief Emulates a mock method and returns a pre-defined value or throws a pre-defined exception.
   * 
   * This function emulates the behavior of the specified mock method. Upon entering, it logs 
   * the method's invocation. If the method has a predefined delay, it waits for the given duration 
   * before proceeding. If an exception is set to be thrown for the specified method, it throws 
   * the exception. Otherwise, it returns the predefined return value for the mock method.
   * 
   * \tparam T       typename - Expected return type of the mock method.
   * \param func     const char* - The name of the mock method that is being emulated.
   * 
   * \return T       Returns the emulated output (return value) of the mock method.
   * 
   * \throw int      Throws an exception if one is predefined for the mock method.
   * 
   * \note This method relies on other methods like throwException and doReturn to handle exceptions 
   *       and return values respectively.
   */
  template<typename T>
  T mock(const char * func) {
    string logMsg = string("Entered mock method for ") + string(func);
    EMULATION_LOG(logMsg.c_str());
    
    // Find the method in _methods and if found, delay by its specific delay amount
    for (auto &method : _methods) {
      if (method.methodName == func) {
        usleep(method.delay * 1000);
        break;
      }
    }

    int exception = throwException(func);
    if (exception > -1) {
      EMULATION_LOG("Throwing expected exception");
      throw exception;
    }
    EMULATION_LOG("Calling doReturn method");
    return doReturn<T>(func);
  }

  /**
   * \brief Retrieves the predefined return value for the given mock method.
   * 
   * This function searches for the predefined return value of the specified mock method
   * within the collection of emulated methods. Once found, it increments the invocation
   * count for that method and returns the associated value. This value is determined by
   * the `findRetVal` method which handles the logic to decide the correct return value
   * based on the method's configuration.
   * 
   * \tparam T       typename - Expected return type of the mock method.
   * \param func     const char* - The name of the mock method whose return value is to be fetched.
   * 
   * \return T       Returns the emulated output (return value) of the mock method.
   * 
   * \note This method relies on findRetVal to determine the exact return value.
   */
  template<typename T>
  T doReturn(const char * func) { 
    T value;
    for (auto &method : _methods) {
      if (method.methodName == func) {
        value = this->findRetVal<T>(method);
        method.invoked += 1;
        break;
      }
    }
    return value;
  }

  /**
   * \brief Finds the return value for the given method based on its configured behavior.
   *
   * This method determines the appropriate return value for a mocked method by evaluating
   * the return value count and the sequence of alternate return values. 
   *
   * \details The behavior is determined as follows:
   * - If the return count `n` is greater than 0, the method decrements `n` and returns the associated value.
   * - If `n` is 0, and there are no alternate return values (`then` is empty), the current value is returned.
   * - If `n` is 0 and there are alternate return values, the method picks the next value in sequence.
   *   It replaces the current return value with the next one and removes the next value from the sequence.
   *
   * If no valid return value can be determined, a `NoReturnValueException` is thrown indicating the 
   * need to call `.returns()` for the method.
   *
   * \tparam T         The type of the expected return value.
   * \param method     A reference to the MethodProfile of the method being called.
   * \return T         The determined return value.
   * \throws           NoReturnValueException if no valid return can be found.
   */
  template<typename T>
  T findRetVal(MethodProfile &method) {
    T value;
    // if n > 0 return and decrement n
    if (method.retVal.first > 0) {
      --method.retVal.first;
      try {
        value = std::any_cast<T>(method.retVal.second); 
      } catch (std::bad_any_cast e) {
        EMULATION_LOG(e.what());
      }
    }
    // answer if then vector contains elements 
    bool thenIsEmpty = false;
    if (method.then.size() == 0) {
      thenIsEmpty = true;
    }
    if (method.retVal.first == 0) {
      // if then is empty and n is 0 return value anyway
      if (thenIsEmpty) {            
        try {
          value = std::any_cast<T>(method.retVal.second); 
          return value;
        } catch (std::bad_any_cast e) {
          std::string eMessage = "Return value for " + std::string(method.methodName) + " found, casting failed: " + e.what();
          EMULATION_LOG(eMessage.c_str());
          NoReturnValueException(eMessage.c_str());
        }
      } else { // if then not empty and n is 0 move onto to then
        method.retVal = method.then[0];
        method.then.erase(method.then.begin()); 
        return this->findRetVal<T>(method);
      }
    }
    std::string eMessage = "Could not find a return value for " + std::string(method.methodName) + ", .returns() must be called for this method.";
    EMULATION_LOG(eMessage.c_str());
    NoReturnValueException(eMessage.c_str());
    return value;
  }

  /**
   * \brief Attempts to throw a pre-configured exception based on the function's name.
   *
   * This method searches through a list of exceptions mapped to function names. If a match 
   * is found, the associated exception code is returned, indicating that the exception 
   * should be thrown. If no exception is configured for the given function name, a default 
   * exception code (PSUEDO_EXCEPTION_NO_EXCEPT) is set internally.
   *
   * \param func      The name of the function for which an exception should be checked.
   * \return int      The exception code if one is mapped to the function. If no exception is found, 
   *                  -1 is returned.
   */
  int throwException(const char * func) {
    for (auto exception : _exceptions) {
      if (auto part = exception.find(func); part != exception.end()) {
        return part->second;
      }
    }
    setInternalException(PSUEDO_EXCEPTION_NO_EXCEPT);
    return -1;
  }

  /**
   * \brief A store of methods for the mock class.
   * Methods are stored as a vector of function pointers.
   * 
   */
  vector<MethodProfile> _methods;

  protected:
  /**
   * \brief The amount of time the emulator will wait (in seconds) before executing a method.
   * 
   * This delay emulates asynchronous behavior, especially useful for testing time-sensitive logic.
   */
  int _wait = 0;

  /**
   * \brief Last pseudo-exception that was thrown or encountered.
   * 
   * Utilized to keep track of any internal exceptions that might not be propagated outwardly 
   * but can be useful for diagnostic purposes.
   */
  int _lastPsuedoException = 0;

  /**
   * \brief Stores the name of the last function that was set or called.
   * 
   * This member aids in chaining calls and keeping context between various emulator method calls.
   */
  std::string _lastFunc = "";

  /**
   * \brief Throwable exceptions for this mock instance. Stored as a std::map
   * of function name (const char *) and exception (int).
   * Currently only integer supported.
   * 
   */
  vector<std::map<const char *, uint16_t>> _exceptions;
};

#endif
