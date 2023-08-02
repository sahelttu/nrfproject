#include "button_handler.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

#define BUTTON_NODE DT_NODELABEL(button0)

struct gpio_dt_spec buttonspec = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
gpio_flags_t buttonflags = GPIO_OUTPUT_INACTIVE;

button_handler_config buttonconfig;
int32_t button_handler_initialize(button_handler_config config){
    buttonconfig = config;
    int32_t returncode = 0;
    if (!gpio_is_ready_dt(&buttonspec)){
        printk("Error: Button is not ready.");
        return -1;
    }

    printk("Flags: %d\n", buttonspec.dt_flags);
    returncode = gpio_pin_configure_dt(&buttonspec, buttonflags);
    printk("Button %d is ready\n", returncode);
    printk("Success: Button is ready");
    return returncode;

    return 0;
}