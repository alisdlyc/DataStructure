#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "cJSON.h"
#include "utf8togbk.h"

/* 出行数据 IP及端口 */
#define  WEATHER_IP_ADDR   "182.92.193.59"
#define  WEATHER_PORT	   8880

/* GET请求包 */
#define  GET_REQUEST_PACKAGE     \
        "GET https://api.seniverse.com/v3/weather/%s.json?key=%s&location=%s&language=zh-Hans&unit=c\r\n\r\n"