#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int PIN_LED_R = 4;
int PIN_BTN_R = 28;
volatile int btn_flag = 0;

void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    btn_flag = 1;
  }
}


int main() {
  stdio_init_all();
  
  gpio_init(PIN_LED_R);
  gpio_set_dir(PIN_LED_R, GPIO_OUT);
  gpio_init(PIN_BTN_R);
  gpio_set_dir(PIN_BTN_R, GPIO_IN);
  gpio_pull_up(PIN_BTN_R);
  
  gpio_set_irq_enabled_with_callback(
    PIN_BTN_R, GPIO_IRQ_EDGE_FALL, true, &btn_callback);
    
    
    
    while (true) {
    int state =0;
    if (btn_flag == 1) {
      state = !state;
      gpio_put(PIN_LED_R, state);
      btn_flag = 0;
    }
  }
}
