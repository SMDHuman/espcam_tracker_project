#ifndef ESPNET_HANDLER_H
#define ESPNET_HANDLER_H

#include <Arduino.h>
#include "p_array.h"

#define LED_BUILTIN 33

#define MAX_PEERS 5
#define ESPNET_SEARCH_INTERVAL 200
#define ESPNET_TIMEOUT_SEARCH 3000
#define ESPNET_TIMEOUT_PING 1000
#define ESPNET_TIMEOUT_CONLOST 4000

//-----------------------------------------------------------------------------
enum ESPNET_PACKETS: uint8_t{
    ESPNET_REQ_PING = 0,
    ESPNET_RSP_PONG,
    ESPNET_REQ_LEDTOGGLE,
    ESPNET_REQ_POINTS,
    ESPNET_RSP_POINTS,
    ESPNET_REQ_FRAME_COUNT,
    ESPNET_RSP_FRAME_COUNT,
    ESPNET_REQ_ESPNET_CONFIG,
    ESPNET_RSP_ESPNET_CONFIG,
    ESPNET_SET_ESPNET_CONFIG,
    ESPNET_RSP_ERROR,
    ESPNET_REQ_JOIN,
    ESPNET_RSP_JOIN_ACCEPT,
    ESPNET_RSP_JOIN_DENY,
    ESPNET_REQ_LEAVE,
    ESPNET_RSP_LEAVE,
};

enum ESPNET_MODES: uint8_t{
    MODE_NONE = 0,
    MODE_HOST,
    MODE_CLIENT,
    MODE_SEARCHING
};

struct espnet_config_t{
    uint8_t id;
    ESPNET_MODES mode;
    uint8_t mac[6]; 
    uint8_t host_mac[6]; 
    uint32_t last_response;
};

extern espnet_config_t espnet_config;
extern array *peer_list;

void espnet_init();
void espnet_task(void * pvParameters );
void espnet_send(ESPNET_PACKETS tag, uint8_t id);
void espnet_send(ESPNET_PACKETS tag, uint8_t id, uint8_t *data, uint32_t len);
uint8_t espnet_check_id(uint8_t id);
void espnow_recv_cb(const uint8_t *addr, const uint8_t *data, int len);

#endif