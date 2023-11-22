#include "Arduino.h"
#include "blitter.h"
#include "esp_log.h"

Blitter::Blitter(rmt_channel_handle_t rmtChannel, rmt_encoder_handle_t rmtSimpleByteEncoder) {
  channel = rmtChannel;
  simpleByteEncoder = rmtSimpleByteEncoder;
  dataQueue = xQueueCreate(64, 32); //Queue Length, Item Size;

  queueHandlerParams = {
    .messageQueue = dataQueue,
    .rmtChannel = rmtChannel,
    .rmtSimpleByteEncoder = rmtSimpleByteEncoder,
  };
  xTaskCreate(&(queueEntryCheck), "zzzz", 4096, &queueHandlerParams, 10, NULL);

}

void Blitter::sendItemToQueue(uint32_t data[], int discardBits) {
  
  for (int i=0; i<sizeof(data)/sizeof(data[0]); i++){
    
    xQueueSendToBack(dataQueue, &data[i], portMAX_DELAY);
  }
   
}

void Blitter::queueEntryCheck(void *params){
  queue_handler_t* btt = (queue_handler_t*)malloc(sizeof(queue_handler_t));
  btt = (queue_handler_t*)params;
  QueueHandle_t queue = btt->messageQueue;
  rmt_channel_handle_t channel = btt->rmtChannel;
  rmt_encoder_handle_t encoder = btt->rmtSimpleByteEncoder;
  uint32_t buffer = 0;
  ESP_LOGD("TAG", "Checking for queue item");
  while(1) {
    BaseType_t rc = xQueueReceive(queue, &buffer, portMAX_DELAY);
    ESP_LOGD("TAG", "Queue item received %lu", buffer);
    const rmt_transmit_config_t txConf = {
      .loop_count = 1,
      .flags = {
        .eot_level = LOW
      },
    };
    ESP_ERROR_CHECK(rmt_transmit(channel, encoder, &buffer, sizeof(uint32_t), &txConf));  
  }
}