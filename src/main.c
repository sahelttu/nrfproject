/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "led_control.h"

int main(void)
{
	printk("Hello IoT World\n");
	led_control_initialize();
	led_control_blink(LED_COLOR_RED, 3);
	led_control_blink(LED_COLOR_BLUE, 4);
	led_control_blink(LED_COLOR_GREEN, 5);
	return 0;
}
