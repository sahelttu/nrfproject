#include "led_control.h"
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>


#define LED_RED_NODE DT_NODELABEL(red_led)
#define LED_GREEN_NODE DT_NODELABEL(green_led)
#define LED_BLUE_NODE DT_NODELABEL(blue_led)

#define SLEEP_TIME_MS 1000

struct gpio_dt_spec redspec = GPIO_DT_SPEC_GET(LED_RED_NODE, gpios);
struct gpio_dt_spec greenspec = GPIO_DT_SPEC_GET(LED_GREEN_NODE, gpios);
struct gpio_dt_spec bluespec = GPIO_DT_SPEC_GET(LED_BLUE_NODE, gpios);
gpio_flags_t flags = GPIO_OUTPUT_INACTIVE;

int32_t led_control_initialize(void){
	
    int32_t returncode = 0;
    
    if (!gpio_is_ready_dt(&redspec)||
        !gpio_is_ready_dt(&greenspec)||
        !gpio_is_ready_dt(&bluespec)){
		printk("Error: one or more leds not ready\n");
        return -1;
    }
        printk("flags : %d\n", redspec.dt_flags);
    	returncode = gpio_pin_configure_dt(&redspec, flags);
        printk("Led %d is ready\n", returncode);
        returncode = gpio_pin_configure_dt(&greenspec, flags);
        printk("led %d is ready\n", returncode);
        returncode = gpio_pin_configure_dt(&bluespec, flags);
        printk("led %d is ready\n", returncode);
        printk("Success: leds are ready\n");
        return returncode;
}


int32_t led_control_blink(LED_COLOR1 color,uint8_t count){
     int i;
     for (i=0; i<count; i++){
        led_control_set_state(color, 1);
        k_msleep(SLEEP_TIME_MS);
        led_control_set_state(color, 0);
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}

int32_t led_control_set_state(LED_COLOR1 color, LED_STATE state){
    
    int32_t returncode = 0;

    switch(color){
        case LED_COLOR_RED:
        returncode = gpio_pin_set_dt(&redspec, state);
        break;
        case LED_COLOR_GREEN:
        returncode = gpio_pin_set_dt(&greenspec, state);
        break;
        case LED_COLOR_BLUE:
        returncode = gpio_pin_set_dt(&bluespec, state);
        default:
        printk("No color/invalid color was given.\n");
        break;
    }
    printk("%d has blinked\n", color);
    printk("%d\n", returncode);
    return returncode;
}