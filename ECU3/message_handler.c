#include <xc.h>
#include <string.h>
#include "message_handler.h"
#include "msg_id.h"
#include "can.h"
#include "clcd.h"


volatile unsigned char led_state = LED_OFF, status = e_ind_off;


void handle_speed_data(uint8_t *data, uint8_t len)
{
    //Implement the speed function
}

void handle_gear_data(uint8_t *data, uint8_t len) 
{
    //Implement the gear function
}

void handle_rpm_data(uint8_t *data, uint8_t len) 
{
    //Implement the rpm function
}

void handle_engine_temp_data(uint8_t *data, uint8_t len) 
{
    //Implement the temperature function
}

void handle_indicator_data(uint8_t *data, uint8_t len) 
{
    //Implement the indicator function
}

void process_canbus_data() 
{   
    //process the CAN bus data
}