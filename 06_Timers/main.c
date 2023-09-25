// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include <stdio.h>

// Handles
TimerHandle_t timerLed, timerTrace;

// Global LED state
int ledState = 1;


/*   Function: Toggle LED
 *     Toggles the onboard LED
 */
void toggleLed( TimerHandle_t xTimer )
{
    ledState = ledState ^ 1;
    gpio_put( PICO_DEFAULT_LED_PIN, ledState );
}


/*   Function: Trace Count
 *     reads the timer counter and trace it. Then the timer is updated
 *     with the incremented counter value.
 */
void traceCount( TimerHandle_t xTimer )
{
    // Get TimerId (used as counter) and increment
    int timerCount = ( int ) pvTimerGetTimerID( xTimer );
    printf("timerCount = %08d \n\r", timerCount++ );

    // Update the timer counter
    vTimerSetTimerID( xTimer, ( void * ) timerCount );
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
    printf( "[ Timers ] \n\n\r" );

    timerTrace = xTimerCreate(  "TimerTrace",        // Timer name
                                pdMS_TO_TICKS(500),  // Timer period
                                pdTRUE,              // auto-reload
                                ( void * ) 0,        // Timer ID used as counter (initialized to 0)
                                traceCount );        // Call back function

    timerLed = xTimerCreate(    "TimerLed",          // Timer name
                                pdMS_TO_TICKS(200),  // Timer period
                                pdTRUE,              // auto-reload
                                ( void * ) 0,        // Timer ID used as counter (initialized to 0)
                                toggleLed );         // Call back function

    xTimerStart( timerTrace, 0 );
    xTimerStart( timerLed,   0 );
    vTaskStartScheduler( );

    while( 1 );
}