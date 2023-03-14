<h1 align="center">Emulation</h1>

<p align="center">

<img src="https://img.shields.io/badge/made%20by-RobertByrnes-blue.svg" >

<!-- <img src="https://img.shields.io/npm/v/vue2-baremetrics-calendar">

<img src="https://img.shields.io/badge/vue-2.6.10-green.svg"> -->

<!-- <img src="https://badges.frapsoft.com/os/v1/open-source.svg?v=103" >

<img src="https://img.shields.io/github/stars/silent-lad/Vue2BaremetricsCalendar.svg?style=flat">

<img src="https://img.shields.io/github/languages/top/silent-lad/Vue2BaremetricsCalendar.svg">

<img src="https://img.shields.io/github/issues/silent-lad/Vue2BaremetricsCalendar.svg"> -->

<img src="https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat">

</p>

![The Emulator At Work](emulator_at_work.jpg?raw=true "Emulation")

_Emulation Framework for Unity Unit Tests in PlatformIO **[Docs](https://emulation.com)**_

---

# Emulation
Emulation allows the developer to simulate hardware peripherals and other elements that would normally be present in the production environment but may be cumbersome or missing in a development environment.

### Purpose
This package is designed to integrate with the PlatformIO development environment, allowing developers to test their code on different platforms from a native environment. It allows developers to test the business logic of IoT and IIoT projects on local machines, without the need to have access to a physical device. Developers can simulate various events and conditions, helping them to ensure that their code performs optimally and bug-free on the actual device.

---  

# Installation
You can install Emulation in your test files via the PlatformIO library manager. Simply search for "Emulation" and click "Add to Project". Alternatively, you can add the following line to your platformio.ini file:

```ini
lib_deps = digitaldragon/Emulation@^0.0.5
```
### Configuration
In order to configure the PlatformIO test environment to run natively without a requiring firmware upload it is suggested that a native environment is added to your platformio.ini file as follows:

```ini
[env:native]
platform = native
test_framework = unity
test_filter = test_native/*
test_ignore = test_embedded/*
build_flags =
	-DCORE_DEBUG_LEVEL=5
	-std=gnu++17
build_unflags = -std=gnu++11
lib_deps = digitaldragon/Emulation@0.0.5
test_testing_command = ${platformio.build_dir}/${this.__env__}/program
```

The lines (test_filter and test_ignore) may be ommitted but optionally allow for the existance of seperate native and embedded test suites. This platformio.ini example will ignore tests in the `test/test_embedded/` directory whilst running tests in the `test/test_native/` directory. The default gnu++11 compiler is deactivated and instead the gnu++17 compiler is used instead offering richer language features for use in mocking behaviour.

Additionally, the following may be added to the platformio.ini file in order to set the default environment to the native one: 

```ini
[platformio]
default_envs = native
```

- Pros - runnning `pio test` will run the test suite for the native environment only.
- Cons - `pio run` commands will need to be given the `-e {your build environment}` flag in order to build the src and upload correctly. 
---
# Getting started
To start using Emulation and mocks, simply add the following snippet to the top of your test file: 

```C++
#include <emulation.h>
``` 
This will pull into your environment both ArduinoFake and the Unity Unit Test Framework for you.
### Included Mocks
Emulation already includes the follow mock classes for use:
- ArduinoHttpClient
- HttpClient
- FS
- SPIFFS
- SSLClient
- TinyGsm

The intention is that users contribute their mocks back in to help the framework increase its out-of-the-box offering.

### Implementation
To use Emulation, either use an existing mock class or extend the Emulator class and customize it to suit your specific needs. For example, you may want to create a mock class for HTTP requests during testing. In this case, you would create a new class that inherits from Emulator then add specific methods to simulate HTTP requests.

For example, below is a simple mock class implementation for Arduino's SPIFFS file system.


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
---
## Usage - Key concepts
There are several key concepts that you need to understand in order to effectively use Emulation. Here are the main components that make up the Emulation Framework:

### MethodProfile
In order to emulate a method, we need to create a MethodProfile. A MethodProfile describes how a given method should behave when called. It contains information such as the method name, the return value(s) (not needed if method is ```void```), and what to do when the method is called.

```C++
typedef std::pair<int, std::any> RetVal;
typedef struct {
    const char * methodName;
    RetVal retVal;
    std::vector<RetVal> then = {};
    int invoked = 0;
} MethodProfile;
```
### Mocking
To start emulating a method, we need to call the mock function. Using the SPIFFS example:

```C++
size_t totalBytes() { return this->mock<size_t>("totalBytes"); }
```
This tells the Emulation Framework that it should simulate a call to SPIFFS.totalBytes(), and should return a size_t result.

If we want to define more specifically how the mocked processing should work, we can chain calls together to define things like how many times to execute the function.

```C++
#define TINY_GSM_SIM800

#include <TinyGsm.h>

TinyGsm modemDriverMock(MODEM_UART);
Modem<TinyGsm> modemClass;

void testConnectReturnsTrueIfModemConnectedToAPN()
{
    modemDriverMock.returns("waitForNetwork", true);
    modemDriverMock.returns("gprsConnect", true);
    modemDriverMock.returns("isNetworkConnected", true);
    bool connected = modemClass.connect(
        modemDriverMock, 
        apn, 
        gprsUser, 
        gprsPass, 
        ledPin
    );
    
    TEST_ASSERT_TRUE(connected);
}
```
The example above uses the TinyGsm mock `modemDriverMock` to test a Modem wrapper class `modemClass`. The connect function uses the TinyGsm library to connect to a mobile network APN and verify the connection status. The `modemDriverMock` uses 3 functions under the hood to achieve this: "waitForNetwork", "gprsConnect", and "isNetworkConnected" - we specify the mock behaviour before calling the `modemClass` connect method. Finally we assert that the modem is connected and have thereby tested our programming logic without the need of a microcontroller.

### Chaining of Methods
- The returns method initializes a MethodProfile object for every method that it is called on with a provided return value. This value will always be returned as a default behaviour, unless the user adds further behaviour using the times and then methods.
- The times method is chained to a previous returns call and is used to the add new behaviour of how many times it should output the specified return value.
- The then function allows the programmers to chain multiple invalid return types to simulate fluctuating results while unit testing.
  
 ```c++
mockHttpClient.returns("headerAvailable", true).then(false);
```
For example, the above .then() chained to the returns() method instructs the mock to return true once and then false for any remaining calls
### License
This software package is licensed under the MIT license. Feel free to use, modify and contribute to it. Consult the LICENSE file for details.

### :warning: Mock Wisely :warning:
Mocks are best used in cases such a faking network requests or emulating peripheral hardware that is not present. The aim being to test the business logic of the firmware / software you are writing rather than things outdide of your control such as connection reliability, signal strength, erroneous responses, hardware failures etc. 

# Conclusion
Using Emulation, developers can easily create and run unit tests for their IoT devices. With its flexibility and extendability, Emulation provides a useful tool for simulating real-world scenarios, helping developers to ensure their code is optimized and free of bugs.

![The Emulator At Work](hardware.jpg?raw=true "Emulation")
