#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int main(void) {
  float R1 = 10000.0;
  float beta = 3977.0;
  float temp0 = 298.0;
  float R0 = 10000.0;
  float Rntc;
  float TemperaturaK;
  float Vm;

  stdio_init_all();
  adc_init();
  adc_gpio_init(28);
  adc_select_input(2);

  while (1) {
    uint16_t val = adc_read();
    Vm = (3.3/4095)* val;
    Rntc = R1/((3.3/Vm)-1);
    TemperaturaK = beta/(log (Rntc/R0)+(beta/temp0)); 
    printf("Temperatura es: %.2f°\n", TemperaturaK - 273.15);
    sleep_ms(1000);
  }
}