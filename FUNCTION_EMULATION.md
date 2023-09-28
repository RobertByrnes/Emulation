# Function Emulator Framework
## Overview
The FunctionEmulator framework is a specialized mocking utility designed to emulate specific functions for the purpose of unit testing. Derived from the Emulator base class, the FunctionEmulator provides the capabilities to track the number of times a function is called, capture the arguments passed to it, and define the behavior of the function in a controlled testing environment.

## Features
Function Call Tracking: Allows you to see how many times a specific function has been invoked.
Argument Capturing: Saves the arguments passed to the function for later inspection or verification.
Flexible Return Behavior: Define the return behavior and introduce optional delays for emulated functions.
Reset Capability: Reset the internal state of the emulator to start from a clean slate.
Integrated Logging (optional): With the EMULATOR_LOG flag, you can log function emulator activities to a file or console.
## Usage
Initialization: To begin emulating a function, simply create an instance of the FunctionEmulator class and provide the function name as a parameter.

```cpp
FunctionEmulator exampleEmulator("exampleFunction");
```
Mocking Return Values: Define the return behavior and introduce optional delays.

```cpp
exampleEmulator.returns("exampleFunction", true, 100);
```
Tracking & Verification: Check if a function was called and inspect the arguments passed to it.

```cpp
if (exampleEmulator.wasCalled()) {
  std::vector<std::string> args = exampleEmulator.getArguments();
  // ... Process or verify the arguments
}
```  

### Included Classes:
FunctionEmulator: This class provides the core functionality for emulating specific functions. It offers methods like returns, recordFunctionCall, wasCalled, reset, timesCalled, captureArgs, and getArguments.
Notes
Remember to include the necessary header files before using the FunctionEmulator:

```cpp
#include "FunctionEmulator.h"
```

## Conclusion
The FunctionEmulator framework simplifies unit testing by providing a flexible and comprehensive tool for emulating function calls and their behavior. By leveraging its capabilities, developers can ensure that their code interacts correctly with the emulated functions, leading to robust and reliable software.