#ifndef LED_CONTROL_H
#define LED_CONTROL_H
#include <stdint.h>

#define LED_CONTROL_MAX_BLINK_COUNT         5       //Optional. Manage maximum requested blinkcount
#define LED_CONTOL_BLINK_STATE_LENGTH_MS    500     //Defines the length of on and off states in milliseconds

/*Color definitions used by functions, defines what color led is used*/
typedef enum LED_COLOR_E
{
    LED_COLOR_RED,
    LED_COLOR_GREEN,
    LED_COLOR_BLUE
} LED_COLOR1;

/*Pin logical state definition*/
typedef enum LED_STATE_E
{
    LED_STATE_OFF = 0,
    LED_STATE_ON = 1,

}LED_STATE;

/*@brief Initialize leds
@return Returns 0 on success, -1 on error
*/
int32_t led_control_initialize(void);

/*@brief Blink led for a given number of times. Uses led_control_set_state(..) internally.
@Note led will be in OFF state after blinkin. 
If led was ON before calling this function, it is first turned to OFF state and then blinked for the given number of times.
Blinker will fail if requested blink count is greater than LED_CONTROL_MAX_BLINK_COUNT
@param[in] color Color of the red requested to be blinked
@param[in] count Number of blinks requested
@return Returns 0 on success, -1 on failure*/
int32_t led_control_blink(LED_COLOR1 color,uint8_t count);

/*@brief Set the state of the led
@param[in] color Color of the led to be controlled
@param[in] state, Requested state for the led 
@return Returns 0 on success, -1 on error*/
int32_t led_control_set_state(LED_COLOR1 color, LED_STATE state);
#endif