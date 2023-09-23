# GPIO IRQ

Let's have a look on how work with IRQ and ISR on FreeRTOS.

On the main function the GPIOs are initialized. The one controlling the onboard LED as output and the GPIO0 as input. Then the IRQ for GPIO0 is enabled with a callback to **gpioIsr()** function.

When the GPIO0 get a +3.3V pulse, the **gpioIsr()** is called. This function, as any ISR, must be kept short. For this reason, this function disabled the GPIO0 IRQ, notifies **handleTaskBlinkLed()** that an event occurred, and at the end the task call portYIELD_FROM_ISR. This function will make a context switch if higherPrioTaskWokenwas set to pdTRUE inside **vTaskNotifyGiveFromISR()**. 

**handleTaskBlinkLed()** will blink the onboard LED repeated times, print a trace and re-enable the IRQ. 

Build instructions:

```
cd 02_GpioIrq
mkdir build
cd build
cmake ..
make all
Flash the generate uf2 to the Pico board
```
