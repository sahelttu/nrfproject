#ifndef MQTT_MANAGE_H
#define MQTT_MANAGE_H
#include <stdint.h>
#include <zephyr/net/mqtt.h>

#define MQTT_CLIENT_ID              "oregano5085"  //set to something unique.
#define MQTT_MESSAGE_BUFFER_SIZE    256
#define MQTT_PAYLOAD_BUFFER_SIZE    256
#define MQTT_BROKER_PORT            1883
#define MQTT_BROKER_HOST            "broker.hivemq.com"

/*@brief Initializes the mqtt client struct and resolves broker connection data
@Note Prints success and failure information
return 0 on success, -1 on error*/
int32_t mqtt_manage_initialize();

/*@brief Connects to a MQTT broker
@Note Blocks until connected, no timeout functionality at the moment
@return return -1 on error, 0 on success*/
int32_t mqtt_manage_connect();

/*@brief Disconnects from the MQTT broker
@Note Blocks until disconnected, no timout functionality at the moment
@return returns -1 on error 0 on success*/
int32_t mqtt_manage_disconnect();

/*@brief Sends MQTT message
@note Suports only QoS0 and no retain at the moment
@param[in] *payload Message payload string
@param[in] payload_length Length of the payload, use strlen
@param[in] *topic Topic payload string
@param[in] topic_length Length of the payload, use strlen
@return Return -1 on error, 0 on success
*/
int32_t mqtt_manage_publish(uint8_t *payload, size_t payload_length, uint8_t *topic, size_t topic_length);

/*
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/networking/api/mqtt.html
https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/connectivity/networking/api/mqtt.html#mqtt-api-reference
*/
#endif