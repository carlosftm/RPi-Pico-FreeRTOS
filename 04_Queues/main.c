// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

// Array of characters
#define DATA_LENGTH   32
char data[ DATA_LENGTH ];

// Handles
QueueHandle_t queue;

// Data structure for the queue message
struct message
{
    char count;
    char *pData;
};


/* Task: Data Generator
 *   Generates 3 messages every second
 */
void taskDataGen( void *pvParameters )
{
    char cnt = 0;
    struct message dataToSend;

    while( 1 )
    {
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
        dataToSend.count = cnt;
        dataToSend.pData = &data[ cnt++ % DATA_LENGTH ];
        xQueueSend( queue, ( void * )&dataToSend, ( TickType_t ) 100 );

        dataToSend.count = cnt;
        dataToSend.pData = &data[ cnt++ % DATA_LENGTH ];
        xQueueSend( queue, ( void * )&dataToSend, ( TickType_t ) 100 );
        
        dataToSend.count = cnt;
        dataToSend.pData = &data[ cnt++ % DATA_LENGTH ];
        xQueueSend( queue, ( void * )&dataToSend, ( TickType_t ) 100 );
    }
}


/* Task: Data Consumer
 *   Waits for a message in the queue and
 *   flashes the onboard LED everytime a 
 *   message is received
 */
void taskDataConsum( void *pvParameters )
{
    int ledState = 1;
    char message = 0xFF;

    struct message dataReceived;

    while( 1 )
    {
        xQueueReceive( queue, &dataReceived, 1000 );
        printf( "Data received [ Count: %03d ] [Data: %c ]\n\r", dataReceived.count, *( char* )dataReceived.pData );
        for ( int x = 0; x < 2; x++ )
        {
            ledState = ledState ^ 1;
            gpio_put( PICO_DEFAULT_LED_PIN, ledState );
            vTaskDelay( pdMS_TO_TICKS( 20 ) );
        }
    }
}


/* ***********************************************
 * Main function
 * ********************************************* */
void main( void )
{
    stdio_init_all( );
    gpio_init( PICO_DEFAULT_LED_PIN );
    gpio_set_dir( PICO_DEFAULT_LED_PIN, GPIO_OUT );

    sleep_ms( 1500 );
    printf( "[ Queues ] \n\n\r" );

    // Fill up the char array
    for ( int x = 0; x < DATA_LENGTH; x++ )
    {
        data[ x ] = 'A' + x;
    }

    queue = xQueueCreate(10, sizeof( struct message ) );
    xTaskCreate( taskDataConsum, "DataConsumer",  256, NULL, 1, NULL );
    xTaskCreate( taskDataGen,    "DataGenerator", 256, NULL, 1, NULL );
    vTaskStartScheduler( );

    while( 1 );
}