#if not defined(INVOKABLE_H)
#define INVOKABLE_H

#include <any>
#include <vector>

/**
 * \brief Represents a return value configuration for a mocked method.
 *
 * This type is used to configure the return value for a method being emulated.
 * The first element of the pair denotes how many times the associated value 
 * should be returned before moving on to any subsequent return values (as might
 * be listed in a 'then' sequence). The second element of the pair is the 
 * actual value to be returned.
 *
 * \param first   int - The number of times the associated value should be returned.
 * \param second  std::any - The value to be returned by the mocked method.
 */
typedef std::pair<int, std::any> RetVal;

/**
 * \brief Represents the profile of a mocked method for emulation purposes.
 *
 * This structure stores information about a method that's being mocked for testing.
 * It includes details like the method's name, the value it should return (including
 * potential subsequent return values in a 'then' sequence), the number of times it
 * has been invoked, and an optional delay before returning the value.
 *
 * \param methodName  const char* - The name of the method/function being mocked.
 * \param retVal      RetVal - The primary return value configuration for the method.
 * \param then        std::vector<RetVal> - A list of subsequent return values 
 *                     the method should return after the primary value has been used.
 * \param invoked     int - A counter for the number of times the method has been invoked.
 * \param delay       int - An optional delay in milliseconds to be applied before 
 *                     returning the value. Default is 0, meaning no delay.
 */
typedef struct {
    const char * methodName;
    RetVal retVal;
    std::vector<RetVal> then = {};
    int invoked = 0;
    int delay = 0;
} MethodProfile;

#endif
