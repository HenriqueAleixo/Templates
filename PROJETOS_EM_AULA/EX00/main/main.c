/**
 * Lib C
 */
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/**
 * FreeRTOS
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**
 * Log
 */
#include "esp_system.h"
#include "esp_log.h"

/*
 * Drivers
 */
#include "driver/gpio.h"


#define BLINK_GPIO 2 //led building
/**
 * Variáveis Globais
 */
static const char *TAG = "main: ";
/*
  task_blink;
  task_idle; 
  app_main; 
*/
void task_blink( void * pvParameter )
{
    unsigned char count = 0;
    /*
	 * Configura a GPIO2 do ESP32 como GPIO-OUTPUT;
	 * Sobre o Led Building do ESP32; 
	 * Ligado 		-> GPIO2 - Nível 0
	 * Desligado 	-> GPIO2 - Nível 1
	*/
    gpio_pad_select_gpio(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	
    for(;;)
	{
        /* Liga Led */
        gpio_set_level(BLINK_GPIO, count % 2 );
        count++;
        
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
   vTaskDelete( NULL ); 
}


/**
 * Esta task é responsável em apresentar o valor em bytes do head.
 * O heap precisa ser monitorado em busca de possíveis falhas no programa
 * provocados por memory leak. 
 */
/*
void monitoring_task( void * pvParameter )
{
    for(;;)
    {
        ESP_LOGI( TAG, "free heap: %d\n", esp_get_free_heap_size() );
        
        vTaskDelay( 5000 / portTICK_PERIOD_MS );
    }
}
*/

void app_main( void )
{
    
    if( xTaskCreate( task_blink, "task_blink", 1024*2, NULL, 2, NULL ) != pdTRUE )
    {
         ESP_LOGI( TAG, "error - Nao foi possivel alocar task_blink.\r\n" );  
         return;   
    }  
   
       /**
     * task que monitora o consumo de memória no Heap;
     */
/*     
    if( xTaskCreate( monitoring_task, "monitoring_task", 2048, NULL, 2, NULL ) != pdTRUE )
    {
        if( DEBUG )
            ESP_LOGI(TAG, " monitoring_task error\r\n" );

        while( TRUE );
    }
*/   
    ESP_LOGI( TAG, "Teste app_main" );  
 ///.......    
}

