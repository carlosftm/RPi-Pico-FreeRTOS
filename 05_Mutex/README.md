# 05. Mutex

In FreeRTOS, a mutex (short for mutual exclusion) is a synchronization primitive used to protect shared resources from concurrent access by multiple tasks. It provides a way to enforce exclusive access to a resource, ensuring that only one task can access it at a time.

In this example, two task are accessing the same HW resource (onboard LED). The access to this LED must be secured to avoid simultaneous access.
**taskToggleLed** is toggling the onboard LED every 500ms. **taskCounter** is incrementing a counter every 200ms, but if the count is module 32, then it blinks the LED repeatedly for 1 second. **taskCounter** blocks the mutex for 1 second, while **taskToggleLed** only for a very short time every 500ms.

The LED must toggle every 500ms, thats why the mutext blocking time in **taskToggleLed** is 0.

Build instructions:

1. `cd 05_Mutex`
2. `cmake ..`
3. `make all`
4. Flash the generate uf2 to the Pico board.
