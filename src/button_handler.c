#include "button_handler.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>

#define BUTTON_NODE DT_NODELABEL(button0)

struct gpio_dt_spec buttonspec = GPIO_DT_SPEC_GET(BUTTON_NODE, gpios);
gpio_flags_t buttonflags = GPIO_INPUT;

struct gpio_callback button_cb;
static button_handler_config buttonconfig;

void button_cb_handler(const struct device *port, struct gpio_callback *cb, gpio_port_pins_t pins){
    printk("A button has been pressed.\n");
}

int32_t button_handler_initialize(button_handler_config config){
    buttonconfig = config;
    int32_t returncode = 0;
    if (!gpio_is_ready_dt(&buttonspec)){
        printk("Error: Button is not ready.\n");
        return -1;
    }

    printk("Flags: %d\n", buttonspec.dt_flags);
    returncode = gpio_pin_configure_dt(&buttonspec, buttonflags);
    printk("Button %d is ready\n", returncode);
    printk("Success: Button is ready\n");
    gpio_pin_interrupt_configure_dt(&buttonspec, GPIO_INT_EDGE_RISING);
    gpio_init_callback(&button_cb, button_cb_handler, BIT(buttonspec.pin));
    gpio_add_callback_dt(&buttonspec, &button_cb);
    return returncode;
}