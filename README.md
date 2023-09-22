# RPi-Pico-FreeRTOS

Sample code using FreeRTOS on the Raspberry Pi Pico (RP2040).
The code make use of the pico-sdk. 

FreeRTOS was added to the repository as a submodule.
Pico-SDK must be pre-installed on your machine.

**Instructions to build the examples:**

1. Clone the repository
   ```
   git clone https://github.com/carlosftm/RPi-Pico-FreeRTOS.git --recurse-submodules
   ```
  
2. set the following 2 enviroment variables (adapt the path to the pico-sdk according to your setup)
   ```
   cd RPi-Pico-FreeRTOS
   export PICO_SDK_PATH=~/pico/pico-sdk
   export FREERTOS_KERNEL_PATH=$PWD/FreeRTOS-Kernel
   ```

3. build the sample code
   ```
   cd 01_SingleTask
   mkdir build
   cmake ..
   make all
   ```

4. Flash your raspberry pi pico with the generated .u2f file

By default all example are using USB as serial interface. To see the traces of the Pico board you can use any terminal. I use minicom under Linux (Ubuntu or Raspbian). Adapt the TTY terminal according to your system:
  ```
  minicom -b 115200 -D /dev/ttyACM0
  ```
