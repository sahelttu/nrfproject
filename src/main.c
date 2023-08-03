/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "led_control.h"
#include "button_handler.h"
#include "watchdog_management.h"

static button_handler_config buttonconfig;
struct wdt_timeout_cfg toconfig;

int main(void)
{
	printk("Hello IoT World\n");
	toconfig.window.min = 0;
	toconfig.window.max = 20000;
	toconfig.flags = WDT_FLAG_RESET_SOC;
	watchdog_initialize(&toconfig);
	button_handler_initialize(buttonconfig);
	led_control_initialize();
	led_control_blink(LED_COLOR_RED, 1);
	led_control_blink(LED_COLOR_BLUE, 1);
	led_control_blink(LED_COLOR_GREEN, 1);

	while(1){
		k_msleep(7000);
		watchdog_feed();
		printk("MAIN: Watchdog fed\n");

	}
	return 0;
}
