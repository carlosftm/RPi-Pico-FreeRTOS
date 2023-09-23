# 02. Inter Task Communication

With this example, I want to demostrate how 2 task can communicate. In this particular case, one task notifies anotherone when an event occurred.
**taskDelay** will wait for 500ms to pass, then it will notify **taskToggleLed** that the time expired. **taskToggleLed** is waiting for a notification. When the notification arrives, it will toggle the LED, otherwise it will print a timeout wearning.

The timeout can be specified when building the example:
```
    cmake .. -DMAX_WAIT_TIME_MS=600
    make all
```

- When **MAX_WAIT_TIME_MS** > 500ms, you should see one print from **taskDelay** saying that the delay is completed, and a second trace from **taskToggleLed** indicating that the LED toggled.

- When **MAX_WAIT_TIME_MS** < 500ms, you should see the same traces from **taskDelay** and **taskToggleLed**, however there will be an additional trace saying that the there is a timeout while waiting for the task notification.