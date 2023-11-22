#define rmt_test_h

#include "driver/gpio.h"
#include "driver/rmt_tx.h"

#define SYMBOL_WORD_LEVEL0    LOW  
#define SYMBOL_WORD_LEVEL1    HIGH  

#define UNUSED_PIN            GPIO_NUM_NC
#define RMT_CLOCK_FREQUENCY   80000000
// make calculations easy and set up for microseconds
#define RMT_CLOCK_DIVIDER     80
#define DCC_1_HALFPERIOD      58       //4640 - (1 / 80000000) * 4640 = 58us
#define DCC_0_HALFPERIOD      100      //8000 - (1 / 80000000) * 8000 = 100us

// const int     PREAMBLE_BITS_MAIN = 16;
// const int     PREAMBLE_BITS_PROG = 22;
// const int     MAX_PACKET_SIZE = 5;      // NMRA standard extended packets,
//                                         // payload size WITHOUT checksum.


class RMTTest {
  public:
    RMTTest(gpio_num_t pin);
    void sendBytes(byte data[], size_t sizeInBytes, int loopCount, uint32_t eotLevel);


  private:
    // Both RMT TX and RX channels are represented by rmt_channel_handle_t in
    // the driver. The driver internally manages which channels are available
    // and hands out a free channel on request.
    //
    // https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-reference/peripherals/rmt.html#resource-allocation
    rmt_channel_handle_t rmtChannel;

    void createChannel(gpio_num_t pin);

    // An RMT encoder is part of the RMT TX transaction, whose responsibility
    // is to generate and write the correct RMT symbols into hardware memory
    // or DMA buffer at a specific time. 
    //
    // https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-reference/peripherals/rmt.html#rmt-encoder
    rmt_encoder_handle_t rmtSimpleByteEncoder;
    void createSimpleBytEncoder(bool msbFirst);  

};