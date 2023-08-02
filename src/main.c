/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "led_control.h"
#include "button_handler.h"

static button_handler_config buttonconfig;

int main(void)
{
	printk("Hello IoT World\n");

	button_handler_initialize(buttonconfig);
	led_control_initialize();
	led_control_blink(LED_COLOR_RED, 3);
	led_control_blink(LED_COLOR_BLUE, 3);
	led_control_blink(LED_COLOR_GREEN, 3);
	return 0;
}
