/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include "led_control.h"
#include "button_handler.h"
#include "network.h"
#include "watchdog_management.h"
#include "mqtt_manage.h"
#include <modem/nrf_modem_lib.h>



static button_handler_config buttonconfig;
struct wdt_timeout_cfg toconfig;

	int32_t example_payload_publish(){
		static int32_t some_sensor_value = 23;
		uint8_t message[128];
		uint8_t topic[128];

		sprintf(message, "%d", some_sensor_value++);
		sprintf(topic, "%s/temperature", MQTT_CLIENT_ID);

		printk("Publishing message %s\n", message);
		printk("Topic %s\n", topic);
		return mqtt_manage_publish(message, strlen(message),topic, strlen(topic));
	}

int main(void)
{
	int retcode;
	retcode = nrf_modem_lib_init();
	if(retcode){
		printk(" nrf_modem_lib_init error\n");
	}else{
		printk("nrf_modem_lib_init success\n");
	}

	network_initialize();
	
	printk("Hello IoT World\n");
	toconfig.window.min = 0;
	toconfig.window.max = 20000;
	toconfig.flags = WDT_FLAG_RESET_SOC;
	watchdog_initialize(&toconfig);
	button_handler_initialize(buttonconfig);
	led_control_initialize();

	network_connect();
	mqtt_manage_initialize();
	mqtt_manage_connect();

	example_payload_publish();

	mqtt_manage_disconnect();
	network_disconnect();
	while(1){
		k_msleep(7000);
		watchdog_feed();
		printk("MAIN: Watchdog fed\n");

	}
	return 0;
}
