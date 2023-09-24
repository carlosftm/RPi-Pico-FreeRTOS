# 01. Single Task

This is the first example of the series. It is basically an introduction to FreeRTOS.

On the main function, the STDIO and GPIOs are initialized, the **taskToggleLed** task is created and the scheduler is called.

The **taskToggleLed** toggles the LED and then it is suspended for 500ms when calling **vTaskDelay()**. If there were more task scheduled, the **taskToggleLed** would volutarely yield the processor to the next task, entering in blocking state. After the 500ms, the task is moved from the Blocked state list to the Ready state list. The task becomes eligible for execution again and will resume execution when it is scheduled by the FreeRTOS scheduler and there is no higher-priority task ready to run.

The primary function of the scheduler is to manage the execution of tasks or threads in a multitasking environment.
The scheduler determines which task should run at any given time based on predefined scheduling policies.
Unless there is not enough FreeRTOS heap memory available, the scheduler function wiull not return.

Build instructions:

```
cd 01_SingleTask
mkdir build
cd build
cmake ..
make all
Flash the generate uf2 to the Pico board
```
