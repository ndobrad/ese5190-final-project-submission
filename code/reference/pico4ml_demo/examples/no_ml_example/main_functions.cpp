/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "main_functions.h"
#include <LCD_st7735.h>
#include <hardware/gpio.h>
#include <hardware/irq.h>
#include <hardware/uart.h>
#include <pico/stdio_usb.h>
#include <pico/stdio.h>
#include <cstdio>
#include <pico/double.h>

//#include "detection_responder.h"
#include "image_provider.h"
#include "settings.h"
//#include "person_detect_model_data.h"
//#include "tensorflow/lite/micro/micro_error_reporter.h"
//#include "tensorflow/lite/micro/micro_interpreter.h"
//#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
//#include "tensorflow/lite/schema/schema_generated.h"
//#include "tensorflow/lite/version.h"

const uint LED_PIN = 25;
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1
// Globals, used for compatibility with Arduino-style sketches.
int8_t image_data[96*96*2];

#ifndef DO_NOT_OUTPUT_TO_UART

// RX interrupt handler
void on_uart_rx() {
  char cameraCommand = 0;
  while (uart_is_readable(UART_ID)) {
    cameraCommand = uart_getc(UART_ID);
    // Can we send it back?
    if (uart_is_writable(UART_ID)) {
      uart_putc(UART_ID, cameraCommand);
    }
  }
}

void setup_uart() {
  // Set up our UART with the required speed.
  uint baud = uart_init(UART_ID, BAUD_RATE);
  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
  // Set our data format
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
  // Turn off FIFO's - we want to do this character by character
  uart_set_fifo_enabled(UART_ID, false);
  // Set up a RX interrupt
  // We need to set up the handler first
  // Select correct interrupt for the UART we are using
  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

  // And set up and enable the interrupt handlers
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);

  // Now enable the UART to send interrupts - RX only
  uart_set_irq_enables(UART_ID, true, false);
}

#else
void setup_uart() {}
#endif

// The name of this function is important for Arduino compatibility.
void setup() {
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_put(LED_PIN, !gpio_get(LED_PIN));

  setup_uart();
  stdio_usb_init();
  int setup_status = ScreenInit();
  if (setup_status != 0) {
    printf("setup failed\n");
    //TF_LITE_REPORT_ERROR(error_reporter, "Set up failed\n");
  }
  else {
    printf("setup done");
  }
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  gpio_put(LED_PIN, !gpio_get(LED_PIN));
}

int person_score = 0;
// The name of this function is important for Arduino compatibility.
void loop() {
  gpio_put(LED_PIN, !gpio_get(LED_PIN));
#if EXECUTION_TIME
  TF_LITE_MICRO_EXECUTION_TIME_BEGIN
  TF_LITE_MICRO_EXECUTION_TIME_SNIPPET_START(error_reporter)
#endif
  // Get image from provider.
  if (0 != GetImage(kNumCols, kNumRows, kNumChannels, image_data)) {
    printf("image capture failed\n");
    //TF_LITE_REPORT_ERROR(error_reporter, "Image capture failed.");
  }
  else {
    printf("captured image\n");
  }
#if SCREEN
  person_score += 1;
  if (person_score > 100) {person_score = 0;}
  char array[10];
  sprintf(array, "Hi!"); //"%d%%", ((person_score + 128) * 100) >> 8);
  ST7735_FillRectangle(10, 120, ST7735_WIDTH, 40, ST7735_BLACK);
  ST7735_WriteString(13, 120, array, Font_16x26, ST7735_GREEN, ST7735_BLACK);
#endif
  //TF_LITE_REPORT_ERROR(error_reporter, "**********");
}
