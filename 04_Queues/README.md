# Queues

In FreeRTOS, a queue is a fundamental synchronization and communication mechanism used for inter-task communication. It allows tasks to send and receive data items in a thread-safe manner. Queues are commonly used in real-time systems to pass messages, events, or data between tasks.

In this example, the **taskDataGen** will send data to **taskDataConsum** using a data structure. The data structure contains a integer and a pointer to an array of characters. **taskDataGen** will send 3 messages in a row every second. It will fill up the message and add it to the queue. 
**taskDataConsum** will wait for messages in the queue. When a message arrives, **taskDataConsum** will print the received data and blink shortly the onboard LED.

Build instructions:

1. `cd 04_Queues`
2. `cmake ..`
3. `make all`
4. Flash the generate uf2 to the Pico board.
