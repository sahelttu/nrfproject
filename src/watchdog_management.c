#include "watchdog_management.h"
#include <zephyr/device.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>


#define WATCHDOG_NODE_IDENTIFIER DT_NODELABEL(wdt0)

const struct device *wdt_device = DEVICE_DT_GET(WATCHDOG_NODE_IDENTIFIER);
int channelid;
int feedreturn;

int32_t watchdog_initialize(struct wdt_timeout_cfg *wdt_config){
    


    if(!device_is_ready(wdt_device)){
        printk("Device is not ready\n");
        return -1;
    }
    channelid = wdt_install_timeout(wdt_device, wdt_config);
    printk("Channel ID: %d\n", channelid);
    printk("WATCHDOG: Device is ready\n");
    wdt_setup(wdt_device, WDT_OPT_PAUSE_HALTED_BY_DBG);
    printk("WATCHDOG: Device is setup\n");
    return 0;
}

void watchdog_feed(void){
    feedreturn = wdt_feed(wdt_device, channelid);
    printk("Feed: %d\n", feedreturn);
}