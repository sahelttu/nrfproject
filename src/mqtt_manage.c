#include <zephyr/net/mqtt.h>
#include "mqtt_manage.h"
#include <zephyr/net/socket.h>
#include <zephyr/random/rand32.h>


static struct sockaddr_storage broker;
static struct mqtt_client client;
static uint8_t rx_buffer[MQTT_MESSAGE_BUFFER_SIZE];
static uint8_t tx_buffer[MQTT_MESSAGE_BUFFER_SIZE];

static volatile bool connected = false;
static volatile bool connecting_failed = false;



/**@brief MQTT client event handler
 */
void mqtt_evt_handler(struct mqtt_client *const c,
		      const struct mqtt_evt *evt)
{

	switch (evt->type) {
	case MQTT_EVT_CONNACK:
		if (evt->result != 0) {
			printk("MQTT connect failed: %d\n"
			, evt->result);
			connecting_failed = true;
			break;
		}
		printk("MQTT connect succeeded.\n");
		connected = true;
		break;

	case MQTT_EVT_DISCONNECT:
		if (evt->result != 0) {
			printk("MQTT connect failed: %d\n"
			, evt->result);
			break;
		}
		printk("MQTT disconnect succeeded.\n");
		connected = false;
		break;

	default:
		printk("Unhandled MQTT event type: %d\n", evt->type);
		break;
	}
}


static int broker_init(void)
{
	int err;
	struct addrinfo *result;
	struct addrinfo *addr;
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM
	};

	err = getaddrinfo(MQTT_BROKER_HOST, NULL, &hints, &result);
	if (err) {
		printk("getaddrinfo failed: %d\n", err);
		return -ECHILD;
	}

	addr = result;

	/* Look for address of the broker. */
	while (addr != NULL) {
		/* IPv4 Address. */
		if (addr->ai_addrlen == sizeof(struct sockaddr_in)) {
			struct sockaddr_in *broker4 =
				((struct sockaddr_in *)&broker);
			char ipv4_addr[NET_IPV4_ADDR_LEN];

			broker4->sin_addr.s_addr =
				((struct sockaddr_in *)addr->ai_addr)
				->sin_addr.s_addr;
			broker4->sin_family = AF_INET;
			broker4->sin_port = htons(MQTT_BROKER_PORT);

			inet_ntop(AF_INET, &broker4->sin_addr.s_addr,
				  ipv4_addr, sizeof(ipv4_addr));
			printk("IPv4 Address found %s\n", (char *)(ipv4_addr));

			break;
		} else {
			printk("ai_addrlen = %u should be %u or %u",
				(unsigned int)addr->ai_addrlen,
				(unsigned int)sizeof(struct sockaddr_in),
				(unsigned int)sizeof(struct sockaddr_in6));
		}

		addr = addr->ai_next;
	}

	/* Free the address. */
	freeaddrinfo(result);

	return err;
}

int32_t mqtt_manage_initialize()
{
    int retcode;
	mqtt_client_init(&client);
	retcode = broker_init();
	if(retcode){
	printk("broker_init() failed\n");
	return -1;
	}

	/* MQTT client configuration */
	client.broker = &broker; //MQTT broker connection data
	client.evt_cb = mqtt_evt_handler; //Event handler for MQTT events
	client.client_id.utf8 = MQTT_CLIENT_ID; //Change to your own in .h
	client.client_id.size = strlen(client.client_id.utf8); //Size of client id
	client.password = NULL; //We will not used password
	client.user_name = NULL; //We will not use user name
	client.protocol_version = MQTT_VERSION_3_1_1; //Set MQTT protocol version
	client.transport.type = MQTT_TRANSPORT_NON_SECURE; //We will not use TLS at this point

	/* MQTT buffers configuration */
	client.rx_buf = rx_buffer;
	client.rx_buf_size = sizeof(rx_buffer);
	client.tx_buf = tx_buffer;
	client.tx_buf_size = sizeof(tx_buffer);

	return 0;

}


int32_t mqtt_manage_connect()
{
    connected = false;
	connecting_failed = false;
	int retcode;


	retcode = mqtt_connect(&client);
	if(retcode){
		printk("mqtt_connect() failed");
		return -1;
	}

	do{
		mqtt_input(&client);
		printk("Waiting mqtt for connection\n");
		k_msleep(3000);
	}while(!connected && !connecting_failed);

    return 0;
}

int32_t mqtt_manage_disconnect()
{
    int retcode;


	retcode = mqtt_disconnect(&client);
	if(retcode){
		printk("mqtt_disconnect() failed");
		return -1;
	}

	do{
		mqtt_input(&client);
		printk("Waiting mqtt for disconnection\n");
		k_msleep(3000);
	}while(connected && !connecting_failed);

    return 0;
}

int32_t mqtt_manage_publish(uint8_t *payload, size_t payload_length, uint8_t *topic, size_t topic_length)
{
	struct mqtt_publish_param param;
	int retval = 0;
	param.dup_flag = 0;
	param.message.topic.qos = MQTT_QOS_0_AT_MOST_ONCE;
	param.message.payload.data = payload;
	param.message.payload.len = payload_length;
	param.message.topic.topic.utf8 = topic;
	param.message.topic.topic.size = topic_length;
	param.message_id = sys_rand32_get();
	param.retain_flag = 0;
	
	retval = mqtt_publish(&client, &param);
	if(retval){
		printk("mqtt_publish failed.\n");
		return -1;
	}
	printk("mqtt_publish succeeded.\n");
	return 0;
}
