// TODO move to package
#if not defined(EMULATION_INTERFACE_H)
#define EMULATION_INTERFACE_H

#include <vector>
#include <any>
#include <map>
#include <MethodProfile.h>
#include <iostream>
#include <ostream>
#include <unistd.h>

using namespace std;

/**
 * \brief An interface for emulating functionalities.
 * 
 * This class defines a set of methods and properties that should be implemented
 * by classes that aim to emulate certain functionalities. Derived classes will 
 * provide the actual implementations and can elaborate further.
 */
class EmulationInterface {
public:
  virtual ~EmulationInterface() {}

  int _wait; // The wait time for the emulator.

  int _lastPsuedoException; // The last pseudo-exception recorded.
  
  vector<MethodProfile> _methods; // A list of methods associated with the emulator.

  vector<std::map<const char *, uint16_t>> _exceptions; // A list of exceptions for the emulator.

  /**
   * \brief           Sets the wait time.
   * \param seconds   The time in seconds to wait.
   */
  virtual void waits(int seconds) = 0;

  /**
   * \brief           Pauses the emulator for the specified wait time.
   */
  virtual void await() = 0;

  /**
   * \brief           Dumps the methods associated with the emulator.
   */
  virtual void dumpMethods() = 0;

 /**
   * \brief           Configures the emulator to return a specific value when a method is called.
   * \param func      The name of the method.
   * \param var_t     The value that should be returned when the method is invoked.
   */
  virtual Emulator& returns(const char * func, std::any var_t, int delay_ms = 0) = 0;
      
  /**
   * \brief           Sets an exception for a method.
   * \param func      The method's name.
   * \param exception The exception to set.
   */
  virtual void setException(const char * func, uint16_t exception) = 0;

  /**
   * \brief           Resets the emulator's state.
   */
  virtual void reset() = 0;

  /**
   * \brief           Records the last pseudo-exception.
   * \param exception The exception to record.
   */
  virtual void setInternalException(int exception) = 0;

  /**
   * \brief           Throws an exception for a method.
   * \param func      The method's name.
   * \return          The exception code.
   */
  virtual int throwException(const char * func) = 0;

  /**
   * \brief           Sets a method for the emulator.
   * \param func      The method's name.
   * \param function  A pointer to the method function.
   * \param var_t     The return value for the method.
   */
  virtual void setMethod(const char * func, void (*function)(),  std::any var_t) = 0;

  /**
   * \brief           Invokes a method by its name.
   * \param methodName The name of the method to invoke.
   */
  virtual void invokeMethod(const char * methodName) = 0;

  /**
   * \brief           A mock method. Should be overridden by derived classes.
   * \param func      The method's name.
   * \return          A value of type T.
   */
  template<typename T>
  T mock(const char * func) {}
  
  /**
   * \brief           Determines the return value for a method. Should be overridden by derived classes.
   * \param func      The method's name.
   * \return          A value of type T.
   */
  template<typename T>
  T doReturn(const char * func) {}
};

#endif
