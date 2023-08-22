#include "network.h"
#include <zephyr/kernel.h>
#include <modem/lte_lc.h>
#include "led_control.h"
#include "watchdog_management.h"

volatile bool connecting = false;

/*@brief Initialize network module
@Note Calls lte_lc_init(); and prints error message on error, success message on success
@return Returns -1 on error, 0 on success*/
int32_t network_initialize(){
    int retcode;
    retcode = lte_lc_init();
    if(retcode){
        printk("lte_lc_init failed\n");
        return -1;
    }else{
        printk("lte_lc_init succeeded\n");
        return 0;
    }
}

/*@brief Connect to network.
@Note While searching for network and trying to connect, system blinks with blue lights.
Once connected, green light will blink three times.
This function does not return until a connection is made. (timeout functionality not yet implemented)
@return Returns 0 on success (connection is established) -1 on error*/
int32_t network_handler(const struct lte_lc_evt *const evt){


         switch (evt->type) {
     case LTE_LC_EVT_NW_REG_STATUS:
             if ((evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_HOME) &&
             (evt->nw_reg_status != LTE_LC_NW_REG_REGISTERED_ROAMING)) {
                     break;
             }

             printk("Connected to: %s network\n",
             evt->nw_reg_status == LTE_LC_NW_REG_REGISTERED_HOME ? "home" : "roaming");
             connecting = false;
             break;
     case LTE_LC_EVT_PSM_UPDATE:
     case LTE_LC_EVT_EDRX_UPDATE:
     case LTE_LC_EVT_RRC_UPDATE:
     case LTE_LC_EVT_CELL_UPDATE:
     case LTE_LC_EVT_LTE_MODE_UPDATE:
     case LTE_LC_EVT_TAU_PRE_WARNING:
     case LTE_LC_EVT_NEIGHBOR_CELL_MEAS:
     case LTE_LC_EVT_MODEM_SLEEP_EXIT_PRE_WARNING:
     case LTE_LC_EVT_MODEM_SLEEP_EXIT:
     case LTE_LC_EVT_MODEM_SLEEP_ENTER:
             /* Callback events carrying LTE link data */
             break;
     default:
             break;
     }

}

int32_t network_connect(){
    int retcode;
    retcode = lte_lc_connect_async(network_handler);
    connecting = true;
    while(connecting){
        led_control_blink(LED_COLOR_BLUE, 3);
        k_msleep(7000);
		watchdog_feed();
		printk("NETWORK: Watchdog fed\n");
    }
    led_control_blink(LED_COLOR_GREEN, 1);
    led_control_blink(LED_COLOR_GREEN, 1);
    led_control_blink(LED_COLOR_GREEN, 1);
}


/*@brief Sets the modem in offline mode
@Note prints information about success of the disconnecting process
@return Returns 0 on success, -1 on error*/
int32_t network_disconnect(){
    int retcode;
    retcode = lte_lc_offline();
    if (retcode){
        printk("Disconnect failed\n");
    }else{
        printk("Disconnect successful\n");
    }
}
