#ifndef NETWORK_H
#define NETWORK_H
#include <stdint.h>

/*@brief Initialize network module
@Note Calls lte_lc_init(); and prints error message on error, success message on success
@return Returns -1 on error, 0 on success*/
int32_t network_initialize();

/*@brief Connect to network.
@Note While searching for network and trying to connect, system blinks with blue lights.
Once connected, green light will blink three times.
This function does not return until a connection is made. (timeout functionality not yet implemented)
@return Returns 0 on success (connection is established) -1 on error*/
int32_t network_connect();

/*@brief Sets the modem in offline mode
@Note prints information about success of the disconnecting process
@return Returns 0 on success, -1 on error*/
int32_t network_disconnect();

#endif