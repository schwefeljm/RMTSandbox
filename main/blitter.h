#define blitter_h
#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "driver/rmt_tx.h"

typedef struct {
  QueueHandle_t messageQueue;
  rmt_channel_handle_t rmtChannel;
  rmt_encoder_handle_t rmtSimpleByteEncoder;
} queue_handler_t;
  

class Blitter {
  public:
    Blitter(rmt_channel_handle_t rmtChannel, rmt_encoder_handle_t rmtSimpleByteEncoder);
    void sendItemToQueue(uint32_t data[], int discardBits = 0);
       
    QueueHandle_t dataQueue;

    //void queueEntryCheck(void* params);
  
  private:
    static void queueEntryCheck(void* params);
    rmt_channel_handle_t channel;
    rmt_encoder_handle_t simpleByteEncoder;
    
    queue_handler_t queueHandlerParams;
};

typedef struct {
  Blitter blitter;
} blitter_task_t;

