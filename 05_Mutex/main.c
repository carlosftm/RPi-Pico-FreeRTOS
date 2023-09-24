// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>

// Handles
SemaphoreHandle_t mutex = NULL;

/* Task: Toggle LED
 *   The onboard LED state is toggled
 *   every 500ms
 */
void taskToggleLed( void *pvParameters )
{
    int ledState = 1;

    while( 1 )
    {
        ledState = ledState ^ 1;
        if( xSemaphoreTake( mutex, 0 ) == pdTRUE )
        {
            gpio_put( PICO_DEFAULT_LED_PIN, ledState );
            xSemaphoreGive( mutex );
        }
        vTaskDelay( pdMS_TO_TICKS( 500 ) );
    }
}


/* Task: Counter
 *   Increment a counter and blinks the
 *   onboard LED if the counter is modulo 32
 */
void taskCounter( void *pvParameters )
{
    int ledState = 1;
    char cnt = 0;

    while( 1 )
    {
        printf( "Counter = %03d\n\r", cnt );
        if ( !( cnt % 32 ) )
        {
            if( xSemaphoreTake( mutex, 10 ) == pdTRUE )
            {
                printf( "Blink!!\n\r", cnt );
                for ( int x = 0; x < 25; x++ )
                {
                    ledState = ledState ^ 1;
                    gpio_put( PICO_DEFAULT_LED_PIN, ledState );
                    sleep_ms( 40 );
                }
                xSemaphoreGive( mutex );
            }
        }
        cnt = cnt +1;
        vTaskDelay( pdMS_TO_TICKS( 200 ) );
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
    printf( "[ Mutex ] \n\n\r" );

    mutex = xSemaphoreCreateMutex();
    xTaskCreate( taskToggleLed, "ToggleLed", 256, NULL, 1, NULL );
    xTaskCreate( taskCounter,   "Counter",   256, NULL, 1, NULL );
    vTaskStartScheduler( );

    while( 1 );
}