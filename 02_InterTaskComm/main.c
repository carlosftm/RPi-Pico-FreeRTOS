// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define TOGGLE_TIME_MS         500
#ifndef MAX_WAIT_TIME_MS
#    define MAX_WAIT_TIME_MS   600
#endif

TaskHandle_t handleTaskToggleLed = NULL;

/* Task: Toggle LED */
void taskToggleLed( void *pvParameters )
{
    int ledState = 1;

    while( 1 )
    {
        int eventsToProcess = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( MAX_WAIT_TIME_MS ) );
        if ( eventsToProcess != 0)
        {
            ledState = ledState ^ 1;
            gpio_put(PICO_DEFAULT_LED_PIN, ledState );
            printf( "Toggle Led [%d]\n\n\r", ledState );
        }
        else
        {
            printf( "taskToggleLed Timeout!!\n\n\r" );
        }
    }
}

/* Task: Delay */
void taskDelay( void *pvParameters )
{
    char cnt = 0;
    while( 1 )
    {
        vTaskDelay( pdMS_TO_TICKS( TOGGLE_TIME_MS ) );
        printf( "Delay over [%03d]\n\r", cnt++ );
        xTaskNotifyGive( handleTaskToggleLed );
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

    printf( "[ Inter Task Communication ]\n\n\r");
    xTaskCreate( taskToggleLed, "Toggle_LED", 256, NULL, 1, &handleTaskToggleLed );
    xTaskCreate( taskDelay,     "Delay",      256, NULL, 1, NULL );
    vTaskStartScheduler( );
    while( 1 );
}
