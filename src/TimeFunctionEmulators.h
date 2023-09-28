#if not defined(__TIME_FUNCTION_EMULATORS_H__)
#define __TIME_FUNCTION_EMULATORS_H__

#include "FunctionEmulator.h"

/**
 * \class DelayFunctionEmulator
 * \brief Emulator for the delay function in a testing environment.
 * 
 * This class is derived from the `FunctionEmulator` and is specifically designed 
 * to emulate the delay function for testing purposes. Instead of causing an 
 * actual delay in an embedded environment, it emulates the delay in a manner 
 * suitable for unit testing, ensuring that tests run quickly without real-world 
 * waiting. 
 */
class DelayFunctionEmulator : public FunctionEmulator {
public:
   /**
     * \brief Constructor for the DelayFunctionEmulator.
     * 
     * Initializes the emulator with a default function name of "delay" 
     * unless otherwise specified.
     * 
     * \param funcName The name of the function being emulated. Defaults to "delay".
     */
	explicit DelayFunctionEmulator(const std::string &funcName = "delay") : FunctionEmulator(funcName) {}

  	/**
     * \brief Destructor for the DelayFunctionEmulator.
     * 
     * Cleans up any resources used by the emulator.
     */
	~DelayFunctionEmulator() {}

    /**
     * \brief Emulates the delay function.
     * 
     * Records the function call for testing verification and then emulates 
     * the delay by sleeping the thread for the specified duration.
     * 
     * \param ms The number of milliseconds to delay.
     */
	void mockDelay(unsigned long ms) {
		recordFunctionCall();
		usleep(ms * 1000);
	}
};

/**
 * \class MillisFunctionEmulator
 * \brief Emulates the millis function for a testing environment.
 * 
 * This class is derived from the `FunctionEmulator` and is specifically designed 
 * to emulate the millis function for testing purposes. Instead of returning real-world 
 * elapsed time, it provides a controlled way to manipulate and return "time" in a 
 * unit testing context, ensuring predictability in time-sensitive tests.
 */
class MillisFunctionEmulator : public FunctionEmulator {
public:
   /**
     * \brief Constructor for the MillisFunctionEmulator.
     * 
     * Initializes the emulator with a default function name of "millis"
     * unless otherwise specified.
     * 
     * \param funcName The name of the function being emulated. Defaults to "millis".
     */
	explicit MillisFunctionEmulator(const std::string &funcName = "millis") : FunctionEmulator(funcName) {}

    /**
     * \brief Destructor for the MillisFunctionEmulator.
     * 
     * Cleans up any resources used by the emulator.
     */
	~MillisFunctionEmulator() {}
	 
	/**
     * \brief Resets the emulated millis value.
     * 
     * Resets the emulated time value to zero. Useful to start timing 
     * from a known point in testing scenarios.
     */
	void resetMillis() {
		_lastMillisValue = 0;
	}

    /**
     * \brief Emulates the millis function.
     * 
     * Records the function call for testing verification and returns 
     * an incremented value based on the previously set time increment.
     * 
     * \return The emulated time in milliseconds.
     */
	unsigned long mockMillis() {
		recordFunctionCall();
		return _lastMillisValue += _timeIncrement;
	}

    /**
     * \brief Sets the time increment for the emulated millis function.
     * 
     * This determines by how much the emulated millis value will increase 
     * with every call.
     * 
     * \param increment The amount of milliseconds to add for each call.
     */
	void setTimeIncrement(unsigned long increment) {
		_timeIncrement = increment;
	}

private:
	unsigned long _lastMillisValue = 0; // The last returned value of the emulated millis.
	unsigned long _timeIncrement = 100; // The time increment for each call to the emulated millis.
};

#endif // end of __TIME_FUNCTION_EMULATORS_H__
