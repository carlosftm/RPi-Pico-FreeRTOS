// Copyright (c) 2023 CarlosFTM
// This code is licensed under MIT license (see LICENSE for details)

#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

#define GPIO_INPUT_PIN    0

// Handles
TaskHandle_t handleTaskBlinkLed = NULL;
// Function declarations
void gpioIsr( uint gpio, uint32_t events );


/* Enables/disable the IRQ */
void enableIrq( bool state )
{
    gpio_set_irq_enabled_with_callback( GPIO_INPUT_PIN,
                                        GPIO_IRQ_LEVEL_HIGH,
                                        state,
                                        &gpioIsr );
}

/* Task: Blink LED */
void taskBlinkLed( void *pvParameters )
{
    int ledState = 1;
    char cnt = 0;

    while( 1 )
    {
        int eventsToProcess = ulTaskNotifyTake( pdTRUE, pdMS_TO_TICKS( 5000 ) );
        if ( eventsToProcess != 0 )
        {
            printf( "Toggle Led [ %03d ]\n\r", cnt++ );
            for ( int x = 0; x < 20; x++ )
            {
                ledState = ledState ^ 1;
                gpio_put( PICO_DEFAULT_LED_PIN, ledState );
                vTaskDelay( pdMS_TO_TICKS( 50 ) );
            }
            enableIrq( true );
        }
        else
        {
            printf( "! Wait for notification Time out\n\r" );
        }
    }
}

/* Handles the GPIO IRQ */
void gpioIsr( uint gpio, uint32_t events )
{
    enableIrq( false );
    static BaseType_t higherPrioTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR( handleTaskBlinkLed, &higherPrioTaskWoken );

    portYIELD_FROM_ISR( higherPrioTaskWoken );
}

/* ***********************************************
 * Main function
 * ********************************************* */
void main( void )
{
    stdio_init_all( );
    gpio_init( PICO_DEFAULT_LED_PIN );
    gpio_set_dir( PICO_DEFAULT_LED_PIN, GPIO_OUT );

    gpio_init( GPIO_INPUT_PIN );
    gpio_set_dir( GPIO_INPUT_PIN, GPIO_IN );

    sleep_ms(1000);
    printf( "[ GPIO IRQ ] \n\n\r");
    enableIrq( true );

    xTaskCreate( taskBlinkLed, "Blink_LED", 256, NULL, 1, &handleTaskBlinkLed );
    vTaskStartScheduler( );
    
    while( 1 );
}
