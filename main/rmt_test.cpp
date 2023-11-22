#include "Arduino.h"
#include "rmt_test.h"
//#include "driver/gpio.h"

RMTTest::RMTTest(gpio_num_t pin) {
  createChannel(pin);
  createSimpleBytEncoder(true);
  rmt_enable(rmtChannel);
}


void RMTTest::sendBytes(byte data[], size_t sizeInBytes, int loopCount, uint32_t eotLevel) {
  
  const rmt_transmit_config_t txConf = {
    .loop_count = loopCount,
    .flags = {
      .eot_level = eotLevel
    },
  };
  ESP_ERROR_CHECK(rmt_transmit(rmtChannel, rmtSimpleByteEncoder, data, sizeInBytes, &txConf));
}

void RMTTest::createChannel(gpio_num_t pin)
{
  // To install an RMT TX channel, there is a configuration structure that
  // needs to be given in advance rmt_tx_channel_config_t. The following list
  // describes each member of the configuration structure.
  //
  // https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-reference/peripherals/rmt.html#install-rmt-tx-channel
  const rmt_tx_channel_config_t config = {
    // sets the GPIO number used by the transmitter.
    .gpio_num = pin,

    // selects the source clock for the RMT channel.
    .clk_src = RMT_CLK_SRC_DEFAULT,

    // sets the resolution of the internal tick counter. The timing parameter
    // of the RMT signal is calculated based on this tick.
    .resolution_hz = 80000000 / RMT_CLOCK_DIVIDER,

    // this field controls the size of the dedicated memory block owned by the
    // channel, which MUST be at least SOC_RMT_MEM_WORDS_PER_CHANNEL.
    .mem_block_symbols = SOC_RMT_MEM_WORDS_PER_CHANNEL,

    // sets the depth of the internal transaction queue, the deeper the queue, 
    // the more transactions can be prepared in the backlog.
    .trans_queue_depth = size_t(1),

    .flags = {
      // is used to decide whether to invert the RMT signal before sending it
      // to the GPIO pad.
      .invert_out = false,

      // enables the DMA backend for the channel.
      .with_dma = false,

      // enables both input and output capabilities on the channel’s assigned
      // GPIO.
      .io_loop_back = false,

      // configures the channel’s assigned GPIO as open-drain.
      .io_od_mode = false,
    },

    // Set the priority of the interrupt. If set to 0 , then the driver will
    // use a interrupt with low or medium priority (priority level may be one
    // of 1,2 or 3),
    .intr_priority = 3,
  };

  ESP_ERROR_CHECK(rmt_new_tx_channel(&config, &rmtChannel));
}

void RMTTest::createSimpleBytEncoder(bool msbFirst) {
  // The layout of RMT symbol stored in memory, which is decided by the
  // hardware design.
  //
  // https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-reference/peripherals/rmt.html#_CPPv417rmt_symbol_word_t
  rmt_symbol_word_t symbolWord0 = {
    // Level of the first part
    .duration0 = DCC_0_HALFPERIOD,

    // Level of the first part
    .level0 = SYMBOL_WORD_LEVEL0,

    // Level of the second part
    .duration1 = DCC_0_HALFPERIOD,
    // Level of the second part
    .level1 = SYMBOL_WORD_LEVEL1,
  };

  rmt_symbol_word_t symbolWord1 = {
    .duration0 = DCC_1_HALFPERIOD,
    .level0 = SYMBOL_WORD_LEVEL0,
    .duration1 = DCC_1_HALFPERIOD,
    .level1 = SYMBOL_WORD_LEVEL1,
  };

  // Bytes encoder configuration.
  //
  // https://docs.espressif.com/projects/esp-idf/en/v5.1.2/esp32/api-reference/peripherals/rmt.html#_CPPv426rmt_bytes_encoder_config_t
  const rmt_bytes_encoder_config_t byteEncoderConfig {
    // How to represent BIT0 in RMT symbol
    .bit0 = symbolWord0,
    // How to represent BIT1 in RMT symbol
    .bit1 = symbolWord1,
    .flags = {
      // Whether to encode MSB bit first
      .msb_first = msbFirst,
    },
  };

  ESP_ERROR_CHECK(rmt_new_bytes_encoder(&byteEncoderConfig, &rmtSimpleByteEncoder));

}



