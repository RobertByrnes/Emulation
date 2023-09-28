# Time Function Emulators in Emulation Framework
The Emulation framework provides the ability to simulate and control time-based functions typically available in embedded environments. By using this feature, developers can emulate time-sensitive functionalities and write tests that execute predictably without being hindered by real-world time.

## Delay Function Emulator
The DelayFunctionEmulator class simulates the behavior of the delay function, often used in embedded software. Instead of causing an actual delay, it emulates this delay in a test-friendly manner, ensuring tests run quickly.

### Usage:

```cpp
DelayFunctionEmulator delayEmulator;
delayEmulator.mockDelay(1000); // Emulates a delay of 1000 milliseconds.
```
By using this in your tests, the delay function's calls are recorded, but the real-world waiting time is bypassed.

## Millis Function Emulator
The MillisFunctionEmulator class is designed to emulate the millis function. Instead of relying on the real-world elapsed time, this emulator offers a controlled way to return "time", making it invaluable for tests that are sensitive to time or require deterministic behavior.

### Features include:

Resetting the Emulated Time: You can reset the emulated millis counter to a known state, ensuring tests start from a predictable point in time.

```cpp
MillisFunctionEmulator millisEmulator;
millisEmulator.resetMillis(); // Resets the emulated millis value to 0.
```  
Getting the Emulated Time: Returns an emulated time value, which can be incremented based on a predefined value.

```cpp
unsigned long time = millisEmulator.mockMillis(); // Gets the emulated time.
```

Setting Time Increment: By default, each call to the emulated millis function increases the time by 100 milliseconds. However, you can modify this increment to any value, providing flexibility in time simulation.

```cpp
millisEmulator.setTimeIncrement(500); // Sets the time increment to 500 milliseconds.
```

By incorporating these time function emulators in your test suites, you can exercise your code in ways that would be difficult or impossible in a real-world scenario. They're particularly useful when testing functions or modules that respond to elapsed time or rely on specific timing behaviors.