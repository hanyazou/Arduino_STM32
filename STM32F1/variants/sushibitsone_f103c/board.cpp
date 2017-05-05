/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * &file   wirish/boards/maple_mini/board.cpp
 * &author Marti Bolivar <mbolivar&leaflabs.com>
 * &brief  Maple Mini board file.
 */

#include <board/board.h>

#include <libmaple/gpio.h>
#include <libmaple/timer.h>

/* Roger Clark. Added next to includes for changes to Serial */
#include <libmaple/usart.h>
#include <HardwareSerial.h>

#include <wirish_debug.h>
#include <wirish_types.h>

/* Since we want the Serial Wire/JTAG pins as GPIOs, disable both SW
 * and JTAG debug support, unless configured otherwise. */
void boardInit(void) {
#ifndef CONFIG_MAPLE_MINI_NO_DISABLE_DEBUG
    disableDebugPorts();
#endif
}

// Note. See the enum of pin names in board.h

extern const stm32_pin_info PIN_MAP[BOARD_NR_GPIO_PINS] = {


    {&gpioa, &timer1, NULL,  10, 3, ADCx}, // 0  D0    PA10
    {&gpioa, &timer1, NULL,  9,  2, ADCx}, // 1  D1    PA9
    {&gpiob, NULL,    NULL,  12, 0, ADCx}, // 2  D2    PB12
    {&gpiob, NULL,    NULL,  13, 0, ADCx}, // 3  D3    PB13
    {&gpiob, NULL,    NULL,  14, 0, ADCx}, // 4  D4    PB14
    {&gpiob, NULL,    NULL,  15, 0, ADCx}, // 5  D5    PB15
    {&gpioa, &timer1, NULL,  8,  1, ADCx}, // 6  D6    PA8
    {&gpiob, NULL,    NULL,  4,  0, ADCx}, // 7  D7    PB4
    {&gpiob, NULL,    NULL,  5,  0, ADCx}, // 8  D8    PB5
    {&gpiob, &timer4, NULL,  6,  1, ADCx}, // 9  D9    PB6
    {&gpiob, &timer4, NULL,  7,  2, ADCx}, // 10 D10   PB7
    {&gpiob, NULL,    NULL,  11, 0, ADCx}, // 11 D11   PB11
    {&gpiob, NULL,    NULL,  10, 0, ADCx}, // 12 D12   PB10
    {&gpiob, NULL,    NULL,  2,  0, ADCx}, // 13 D13   PB2
    {&gpioc, NULL,    NULL,  13, 0, ADCx}, // 14 D14   PC13
    {&gpioa, &timer2, &adc1, 2,  3, 2   }, // 15 A0    PA2
    {&gpioa, &timer2, &adc1, 1,  2, 1   }, // 16 A1    PA1
    {&gpioa, &timer2, &adc1, 3,  4, 3   }, // 17 A2    PA3
    {&gpioa, NULL,    &adc1, 4,  0, 4   }, // 18 A3    PA4
    {&gpiob, &timer3, &adc1, 0,  3, 8   }, // 19 A4    PB0
    {&gpiob, &timer3, &adc1, 1,  4, 9   }, // 20 A5    PB1
    {&gpiob, &timer4, NULL,  9,  4, ADCx}, // 21 SDA   PB9
    {&gpiob, &timer4, NULL,  8,  3, ADCx}, // 22 SDL   PB8
    {&gpioa, NULL,    &adc1, 5,  0, 5   }, // 23 SCK   PA5
    {&gpioa, &timer3, &adc1, 6,  1, 6   }, // 24 MISO  PA6
    {&gpioa, &timer3, &adc1, 7,  2, 7   }, // 25 MOSI  PA7
    {&gpioa, &timer2, &adc1, 0,  1, 0   }, // 26 WKUP  PA0
    {&gpioa, &timer1, NULL,  11, 4, ADCx}, // 27 UD-   PA11
    {&gpioa, NULL,    NULL,  12, 0, ADCx}, // 28 UD+   PA12
    {&gpioa, NULL,    NULL,  13, 0, ADCx}, // 29 JTMS  PA13
    {&gpiob, NULL,    NULL,  3,  0, ADCx}, // 30 JTDO  PB3
    {&gpioa, NULL,    NULL,  15, 0, ADCx}, // 31 JTDI  PA15
    {&gpioa, NULL,    NULL,  14, 0, ADCx}, // 32 JTCK  PA14


};

extern const uint8 boardPWMPins[BOARD_NR_PWM_PINS] __FLASH__ = {
    PB0, PA7, PA6, PA3, PA2, PA1, PA0, PB7, PB6, PA10, PA9, PA8
};

extern const uint8 boardADCPins[BOARD_NR_ADC_PINS] __FLASH__ = {
    PB0, PA7, PA6 , PA5 , PA4 , PA3 , PA2 , PA1 , PA0 
};

// Note. These defines are not really used by generic boards. They are for  Maple Serial USB
#define USB_DP PA12
#define USB_DM PA11

// NOte. These definitions are not really used for generic boards, they only relate to boards modified to behave like Maple boards
extern const uint8 boardUsedPins[BOARD_NR_USED_PINS] __FLASH__ = {
     USB_DP, USB_DM
};


/* 
 * Roger Clark
 * 
 * 2015/05/28
 *
 * Moved definitions for Hardware Serial devices from HardwareSerial.cpp so that each board can define which Arduino "Serial" instance
 * Maps to which hardware serial port on the microprocessor
 */
						
#ifdef SERIAL_USB
	DEFINE_HWSERIAL(Serial1, 1);

	DEFINE_HWSERIAL(Serial2, 2);

	DEFINE_HWSERIAL(Serial3, 3);
#else
	DEFINE_HWSERIAL(Serial, 1);

	DEFINE_HWSERIAL(Serial1, 2);

	DEFINE_HWSERIAL(Serial2, 3);
#endif
