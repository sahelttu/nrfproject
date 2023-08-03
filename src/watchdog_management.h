#ifndef WATCHDOG_MANAGEMENT_H
#define WATCHDOG_MANAGEMENT_H
#include <zephyr/drivers/watchdog.h>

/*
This system initializes watchdog timer with configuration we have defined in main.c
System at early stage supports only one watchdog channel
*/

/*@brief Initializes and configures watchdog timer
@param[in] *wdt_config A pointer to watchdog configuration struct
@return Returns -1 on error, 0 on success*/
int32_t watchdog_initialize(struct wdt_timeout_cfg *wdt_config);

/*@brief Resets watchdog counter*/
void watchdog_feed(void);

#endif
