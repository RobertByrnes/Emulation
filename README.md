<h1 align="center">Emulation Framework for Unity</h1>

<p align="center">

<img src="https://img.shields.io/badge/made%20by-RobertByrnes-blue.svg" >

<img src="https://img.shields.io/npm/v/vue2-baremetrics-calendar">

<img src="https://img.shields.io/badge/vue-2.6.10-green.svg">

<img src="https://badges.frapsoft.com/os/v1/open-source.svg?v=103" >

<img src="https://img.shields.io/github/stars/silent-lad/Vue2BaremetricsCalendar.svg?style=flat">

<img src="https://img.shields.io/github/languages/top/silent-lad/Vue2BaremetricsCalendar.svg">

<img src="https://img.shields.io/github/issues/silent-lad/Vue2BaremetricsCalendar.svg">

<img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat">
</p>

_A Vue.js wrapper for the beautiful date-range picker made by the **[Baremetrics](https://baremetrics.com)** team._

---

# Emulator
Emulator is a C++ class designed to provide a flexible environment for creating mock classes to be used in Unit Testing within the PlatformIO framework for IoT devices. This class can be extended and customized to create various types of Mock classes which can be used to simulate real-world scenarios, such as HTTP requests for testing purposes.

# Purpose
The main purpose of Emulator is to simplify the process of creating and running unit tests on IoT devices. It allows developers to test their IoT devices on local machines, without the need to have access to the physical device. By using the Emulator class, developers can simulate various events and conditions, helping them to ensure that their code performs optimally and bug-free on the actual device.

# Implementation
To use Emulator, simply extend the class and customize it to suit your specific needs. For example, you may want to create a mock class for HTTP requests during testing. In this case, you would create a new class that inherits from Emulator and add specific methods to simulate HTTP requests.

The Unity test framework is utilized with the ArduinoFake emulation framework, allowing unit tests to be run on a native local machine platform without the need for an embedded chip. Along with these frameworks, Emulator provides a powerful tool for streamlining the unit testing process for IoT devices.

# Conclusion
Using Emulator, developers can easily create and run unit tests for their IoT devices. With its flexibility and customization options, Emulator provides a useful tool for simulating real-world scenarios, helping developers to ensure their code is optimized and free of bugs.

# Functions
## findRetVal()
This is a C++ function called findRetVal() that searches for the return value of a method in a MethodProfile object. It uses a combination of logical conditions and try-catch statements to determine whether or not the MethodProfile object contains a valid return value for the given method.

### Inputs
The function accepts one input parameter, method, which is a reference to a MethodProfile object.

### Steps
The first step checks whether method.retVal.first > 0. If this is true, it means that there are still some return values left, so the function decrements method.retVal.first and returns the corresponding value stored in method.retVal.second.
If method.retVal.first equals zero, the function checks if method.then is empty. If it is, then there is no return value for the method, and an exception is thrown.
If method.retVal.first equals zero and method.then is not empty, the first element of method.then is assigned to method.retVal, and the corresponding return value is returned recursively by calling the findRetVal() function.
If none of the previous conditions are met, this means that there is no return value for the method, and an exception is thrown.
### Outputs
The function outputs a value of T, which is the return value of the method (if found). If there is no return value, the function throws a NoReturnValueException.

# doReturn() - Explanation
Explanation
The given code is a part of a class method for finding the return value of a function in a vector of method profiles. This particular method named doReturn() searches the profile for the function specified and calls another method findRetVal() to check if a return value exists in the profile for that function.

Method findRetVal
This method runs some logical checks to safely and correctly find the return value associated with a method being invoked:

The first section of the method checks whether there is an n value associated with the method and returns the corresponding value if it exists.
In the case where the n is zero, the method then checks whether the vector of nexts is empty using the bool thenIsEmpty.
If the vector is empty too, this means there is no return value associated with this method and so an exception is thrown.
If the vector has elements it grabs the first element sets RetVal as its copy and removes it from "then" vector. It then retries using the same method call.
If the n > 0 and then is empty, method simply returns the last available value as T.
Any casting errors are logged if any occur.
Method doReturn()
It accepts the name of the function to be checked for return values.
It iterates through each method profile and checks if the function name matches, then passes the matching method profile variable to findRetVal() method.
If found, increments the invoked count associated with that method & returns the associated value.

# mock() - Explanation
This code snippet appears to be a part of a software that mocks virtual functions, which are represented as Methods. Mocking functions in C++ is done through templates.

This specific template is used to find a return value for a method. The aim of this method findRetVal is to search the return values within the MethodProfile structure and return them. MethodProfile can store all calls and expectations made in the current test case.

The T findRetVal(MethodProfile &method) function accepts a reference to MethodProfile as an argument and returns T.
It uses a local variable value of type T which will hold the output value.
The declared string variable methodName simply saves the input method name in a readable format.
The function uses several conditional statements to determine what condition the code should execute.
If the method's expected return values are not found in the then vector, it will throw a NoReturnValueException error with a message indicating the issue by combining strings. Otherwise, if the searching criteria matches the logic defined in this function, then it will eventually return the value along with decrementing n, called "How many times the mock is called with the same arguments" in the FunctionCallMatcher class.

The template<typename T> T doReturn(const char * func) is a wrapper around this method, which allows for public functionality and invocation outside of the C++ mock generator.

Explanation of Code
Functionally, these code snippets form part of a mocking framework used for testing purposes mainly. The framework allows you to mock and manipulate the behavior of individual method calls detected on your code. Emulation is performed by resetting any returned value of that method to the default (or defined) return value. Method chaining can be used to define how many times different values are returned after the first call.

The commented descriptions in the code refer to four key functions in this system.

findRetVal a private method called by doReturn()
doReturn, function to search for a specified function by name and return its value using findRetVal(), defining how many times it is called on return.
mock, responsible for calling functions when they are invoked by user code
returns, which creates an entry for each mocked method and defines a default return value.
Each of the above functions takes in a template type T; this enables the function to accept any data type as an argument, allowing for cleaner code by avoiding overloading functions.

Finally, the method below uses times() to specify how many times it expects the named method should be called. If called more or fewer times, an exception would be thrown.

Copy
Insert
New
Emulator& times(int n)
Internally, the implementation seems to be intersecting multiple C++ functionalities such as lambda expressions, move semantics, iterators, templates and exceptions. Some examples include vector class as a container for methods to mock, std::any to return custom types without returning unsafe pointers, and namespace adl (lookup mechanisms enabled by the namespace) with lambdas to create logging messages.

Even with the comments, there is no mention of parameter usage, which could be confusing. Developers must look for external documentation since these snippets only provide functionality description, starting condition (input), and end state (output) without specifying what dependencies and assumptions could change throughout the operation.

This code appears to be a part of a larger program that creates an Emulator for testing code in a more controlled environment.

The doReturn method searches for the correct method in _methods, finds its related MethodProfile, and then returns a value obtained from findRetVal.

The mock method is used to first wait, then check if exceptions are expected by calling throwException. Finally, it calls doReturn and returns the value.

The returns method initializes a MethodProfile object for every method that it is called on with a provided return value. This value will always be returned as a default behaviour, unless the user adds further behaviour using the times and then methods.

The times method is chained to a previous returns call and is used to the add new behaviour of how many times it should output the specified return value.

The then function allows the programmers to chain multiple invalid return types to simulate fluctuating results while unit testing.

This is the header file for an EmulationInterface class. It seems to define a set of methods that will be implemented by some other class, which will inherit from this one. Here's a description of each method:

waits(int seconds): sets _wait to seconds.
await(): calls sleep(_wait) (i.e., waits for _wait seconds).
dumpMethods(): outputs information about all of the mock methods that have been registered.
setException(const char * func, uint16_t exception): registers the specified exception code to be thrown for the named function when it's called.
reset(): clears all of the registered mock methods and exceptions.
setInternalException(int exception): sets _lastPsuedoException to the specified value.
throwException(const char * func): checks to see whether an exception has been registered for the named function, and returns it; otherwise, returns _lastPsuedoException.
invokeMethod(const char * methodName): calls the real implementation of the named function.
There are also two template methods (mock and doReturn) defined here, but they don't appear to be part of the public interface -- it looks like they'll only be called internally by the derived class.


# Emulation Framework for PlatformIO
The Emulation Framework is a powerful tool that enables developers to test their code in a controlled environment. The Emulation Framework allows the developer to simulate hardware peripherals and other elements that would normally be present in the production environment.

This package is designed to integrate with the PlatformIO development environment, allowing developers to test their code on different platforms and environments.

Installation
You can install the Emulation Framework via the PlatformIO library manager. Simply search for "emulation framework" and click "Install". Alternatively, you can add the following line to your platformio.ini file:

```C++
lib_deps = 
  Svanurj/EmulationFramework@^1.0.0
```
Getting started
To start using the Emulation Framework, simply add the following snippet to the top of your test file: 

```C++
#include <emulation.h>
``` 

Create an instance of the appropriate emulation class/service. You can then define the expected behavior of the simulated peripherals/mock functions by calling specific methods.

For example, below is a simple mock class definition for Arduino's SPIFFSFS file system using the Emulation Framework.

```C++
#include <Arduino.h>
#include <Emulator.h>
#include "MockFs.h"

namespace fs {

class SPIFFSFS : virtual public Emulator, public FS {
public:
    SPIFFSFS(FSImplPtr impl): FS(impl) {}
    virtual ~SPIFFSFS() {}

    bool begin(
        bool formatOnFail=false,
        const char * basePath="/spiffs",
        uint8_t maxOpenFiles=10,
        const char * partitionLabel=NULL
    ) {
        return this->mock<bool>("begin");
    }
    bool format() { return this->mock<bool>("format"); }
    size_t totalBytes() { return this->mock<size_t>("totalBytes"); }
    size_t usedBytes() { return this->mock<size_t>("usedBytes"); }
    void end() {}

private:
    char * partitionLabel_;
};

}

fs::FSImplPtr impl;
extern fs::SPIFFSFS SPIFFS;
```

Here we have created a custom class that inherits from both the Emulator class and the FS class provided by the Arduino file system library. We then define several key functions that should be available to the file system when it is implemented in our software, such as begin, format, totalBytes, and usedBytes. By setting up these key functions, we can use the Emulation Framework to test our software's interactions with the file system.

Usage - Key concepts
There are several key concepts that you need to understand in order to effectively use the Emulation Framework. Here are the main components that make up the Emulation Framework:

MethodProfile
In order to emulate a method, we need to create a MethodProfile. A MethodProfile describes how a given method should behave when called. It contains information such as the method name, the return value(s) (if any), and what to do when the method is called.

```C++
typedef std::pair<int, std::any> RetVal;
typedef struct {
    const char * methodName;
    RetVal retVal;
    std::vector<RetVal> then = {};
    int invoked = 0;
} MethodProfile;
```
Mocking
To start emulating a method, we need to call the mock function. For example:

```C++
bool result = SPIFFS.mock<bool>("begin");
```
This tells the Emulation Framework that it should simulate a call to SPIFFS.begin(), and should return a boolean result.

If we want to define more specifically how the mocked processing should work, we can chain calls together to define things like how many times to execute the function.

```C++
SPIFFS.returns("open", File(MockFsFile::file1));
SPIFFS.times(2);
SPIFFS.then(File(MockFsFile::file2));
```
Here we're first saying that when the open method is called, it should return a mock file object representing file1. Then, we say that it should execute twice, and on the third time (assuming there is one), it should return a different file object representing file2.

## Variables
The Emulation Framework supports the use of variables inside MethodProfiles. This means that you can configure how mocked method parameters are treated, allowing you to test edge cases and other scenarios more accurately.

```C++
SPIFFS.returns("open", File(MockFsFile::file1));
SPIFFS.with("filename").returns("open", File(MockFsFile::file2));  
SPIFFS.enterFilename("/path/to/filename.txt");
file = SPIFFS.open(SPIFFS.getFilename().c_str());
```
With this code block, we're creating a MethodProfile which maps the open() method to

## License
This software package is licensed under the MIT license. Feel free to use, modify and contribute to it. Consult the LICENSE file for details.
