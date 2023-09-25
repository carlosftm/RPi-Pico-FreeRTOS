# 06. Timers

In FreeRTOS, a timer is a software component that allows you to schedule and execute tasks or callback functions at specific intervals or after a specified delay. It provides a way to trigger actions periodically or after a certain amount of time has elapsed. FreeRTOS timers are typically used for tasks that need to be performed at regular intervals.

In this example, 2 timers are created. Both auto reload (it is not a single-event timer). When **timerLed** expires (every 200ms), it will call the **toggleLed** function. **toggleLed** function will toggle the onboard LED.
When **timerTrace** expires, it will read the timer id (that is used as a counter), it will trace the counter value and then update the timer with the incremented counter value.

Build instructions:

1. `cd 06_Timers`
2. `cmake ..`
3. `make all`
4. Flash the generate uf2 to the Pico board.
