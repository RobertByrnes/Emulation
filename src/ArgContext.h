#if not defined(_ARG_CONTEXT_H)
#define _ARG_CONTEXT_H

#include <cstddef>
#include <vector>
#include <any>

/**
 * \file ArgContext.h
 * \brief Provides an interface for retrieving and working with captured arguments.
 */

/** 
 * \typedef CapturedArgs_t
 * \brief Represents a two-dimensional vector of arguments captured by any type.
 */
using CapturedArgs_t = std::vector<std::vector<std::any>>;

/**
 * \class ArgContext
 * \brief Provides context and utility methods for handling captured arguments.
 * 
 * This class wraps a 2D vector of any-type arguments and offers a templated 
 * resolve method to fetch and cast these arguments to the desired type.
 */
class ArgContext {
private:
  /** Holds the captured arguments. */    
  CapturedArgs_t _args;

public:
  /**
   * \brief Constructs an ArgContext object with the given captured arguments.
   * 
   * \param args The captured arguments to be wrapped by the context.
   */
  ArgContext(const CapturedArgs_t& args) : _args(args) {}

  /**
   * \brief Resolves and retrieves an argument from the captured list, casting it to the specified type.
   * 
   * This method tries to retrieve an argument from the 2D vector at the specified indices 
   * and cast it to the desired type.
   * 
   * \tparam T The type to which the argument should be cast.
   * \param outerIndex The outer index in the 2D vector to locate the group of arguments.
   * \param innerIndex The inner index in the 2D vector to locate the specific argument within the group.
   * 
   * \return The argument cast to the specified type.
   * 
   * \throw std::runtime_error if there's a type mismatch during the cast.
   */
  template<typename T>
  T resolve(size_t outerIndex, size_t innerIndex = 0) const {
    try {
      return std::any_cast<T>(_args[outerIndex][innerIndex]);
    } catch(const std::bad_any_cast& e) {
      EMULATION_LOG("bad_any_cast - Failed to resolve argument to the specified type.");
    }
    return T{};
  }
};

#endif // end of _ARG_CONTEXT_H
