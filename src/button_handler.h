#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H
#include <stdint.h>

#define BUTTON_HANDLER_MAX_PRESS_DURATION           5000        //Maximum duation allowed to be set in the config for minimum_press_duration

/*
Button handler takes in configuration containing a callback function.
Implement the callback function in main.c
Button handler also takes in minimum_press_duration in milliseconds.
This can be used to create simple debounce functionality.
Using minimum_press_duration and implementing debounce functionality is a optional, extra task.
Main task is to implement initialization and have button_handler call provided callback function on putton press.
*/

/*
Recap of GPIO init and settingup callback, documentation online and previous examples will help with details.
Get gpio_dt_spec
Check: gpio_is_ready_dt()
Configure: gpio_pin_configure_dt()
Configure interrupt: gpio_pin_interrupt_configure_dt()
Init callback: gpio_init_callback()
Setup internal callback: gpio_add_callback_dt()
Internal callback will call the function in main.c
*/

typedef struct button_handler_config_s
{
    uint16_t minimum_press_duration;                            //How long should the button be held down to reqister as a push. Value in milliseconds
    void (*button_handler_event_callback)(void);             //Function pointer to callback function responsible of handling the press event
}button_handler_config;             

/*Initialize the button handler.
Initializes the button GPIO, configures it and setups callback.
@return Returns -1 on error, 0 on success*/
int32_t button_handler_initialize(button_handler_config config);




#endif