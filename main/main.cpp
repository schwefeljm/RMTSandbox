#include "Arduino.h"
#include "rmt_test.h"
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"


extern "C" void app_main()
{
  initArduino();
  RMTTest rmt = RMTTest(GPIO_NUM_2);
  Blitter blt = Blitter(rmt.rmtChannel, rmt.rmtSimpleByteEncoder);




  uint32_t data[] = {0xAAAAAAAA};  
  blt.sendItemToQueue(data);

  // while(1) {
  //   // Send arbitrary number of bytes
  //   //
  //   // byte data[] = "\777UUUU";
  //   // rmt.sendBytes(data, 1, LOW);

  
  //   rmt.sendUint32_t(0xFFFFFFFF, 1, LOW);
  //   rmt.sendUint32_t(0x0, 1, LOW);
  //   rmt.sendUint32_t(0xFFFFFFFF, 1, LOW);


  //   // for(uint32_t i = 85215; i < 85255; i++) {
  //   //   rmt.sendUint32_t(85215, 1, LOW);
  //   //   //vTaskDelay(1);
  //   // }



  //   vTaskDelay(10000);
  // }

}