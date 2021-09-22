/*
 * Lib C
 */
#include <stdio.h>
#include <stdint.h>  

/*
 * FreeRTOS
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/*
 * logs
 */
#include "esp_log.h"

static const char * TAG = "MAIN: ";
/*
 * Variável Global. 
 */
QueueHandle_t xQueue;

void task_count( void * pvParameter )
{
    unsigned int count = 0;
    
    for(;;)
    {

		if( xQueueSend( xQueue, &count, 1000 / portTICK_PERIOD_MS ) == pdPASS )
		{
			ESP_LOGI( TAG, "O VALOR %d DE COUNT FOI ENVIADO NA QUEUE.\n", count );
			count++;
		}
        
        vTaskDelay( 10 / portTICK_PERIOD_MS );
    }    
    vTaskDelete( NULL ); 
}

void task_print( void * pvParameter )
{
    unsigned int count; 
    
    for(;;)
    {
        xQueueReceive( xQueue, &count, portMAX_DELAY );
		ESP_LOGI( TAG, "COUNT RECEBIDO. VALOR = %d\n", count );	
		
    }
    vTaskDelete( NULL ); 
}


void app_main( void )
{

    if( (xQueue = xQueueCreate( 5, sizeof(uint32_t)) ) == NULL )
	{
		ESP_LOGI( TAG, "error - nao foi possivel alocar xQueue.\n" );
		return;
	} 
    
    if( xTaskCreate( task_count, "task_count", 1024*2, NULL, 2, NULL ) != pdTRUE )
    {
         ESP_LOGI( TAG, "error - Nao foi possivel alocar task_count.\r\n" );  
         return;   
    } 

    if( xTaskCreate( task_print, "task_print", 1024*2, NULL, 2, NULL ) != pdTRUE )
    {
         ESP_LOGI( TAG, "error - Nao foi possivel alocar task_print.\r\n" );  
         return;   
    }    
}