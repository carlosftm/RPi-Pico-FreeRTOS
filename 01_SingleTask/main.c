// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE.txt for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

/* Task: Toggle LED */
void taskToggleLed( void *pvParameters )
{
    int ledState = 1;

    while( 1 )
    {
        ledState = ledState ^ 1;
        gpio_put(PICO_DEFAULT_LED_PIN, ledState );
        printf( "Toggle Led [%d]\n\r", ledState );
        vTaskDelay( 500 );
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

    sleep_ms(1000);
    printf( "[ Single Task ] \n\n\r");
    xTaskCreate( taskToggleLed, "Toggle_LED", 256, NULL, 1, NULL );
    vTaskStartScheduler( );
    while( 1 );
}
