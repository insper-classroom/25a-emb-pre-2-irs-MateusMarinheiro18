#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include <stdio.h>

int PIN_BTN_G = 26;
int PIN_BTN_R = 28;

int PIN_LED_R = 4;
int PIN_LED_G = 6;

volatile int flag_red;
volatile int flag_green;


void btn_callback(uint gpio, uint32_t events) {
  if (events == 0x4) { // fall edge
    flag_red = 1;
  }
  else if (events == 0x8) { // rise edge
    flag_green = 1;
  }
}

int main() {
  int green_state = 0;
  int red_state = 0;
  stdio_init_all();

  gpio_init(PIN_BTN_R);
  gpio_set_dir(PIN_BTN_R, GPIO_IN);
  gpio_pull_up(PIN_BTN_R);

  gpio_init(PIN_BTN_G);
  gpio_set_dir(PIN_BTN_G, GPIO_IN);
  gpio_pull_up(PIN_BTN_G);

  gpio_init(PIN_LED_R);
  gpio_set_dir(PIN_LED_R, GPIO_OUT);

  gpio_init(PIN_LED_G);
  gpio_set_dir(PIN_LED_G, GPIO_OUT);

  gpio_set_irq_enabled_with_callback(PIN_BTN_R, GPIO_IRQ_EDGE_FALL, true,
    &btn_callback);

    gpio_set_irq_enabled_with_callback(PIN_BTN_G, GPIO_IRQ_EDGE_RISE, true,
      &btn_callback);


  while (true) {
    if (flag_red){
      red_state = !red_state;
      gpio_put(PIN_LED_R, red_state);
      flag_red = 0;
    }
    else if (flag_green){
      green_state = !green_state;
      gpio_put(PIN_LED_G, green_state);
      flag_green = 0;
    }
  }
}
