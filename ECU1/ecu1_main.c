#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include"clcd.h"
#include "matrix_keypad.h"


unsigned char ind = 0;
char *ev[9] = { "ON  ","GN  ","G1  ","G2  ","G3 ","G4 ","G5 ","GR  ","C_ "};
char data[3];
char GEAR[5];
int main()
{
   init_can();   
    init_matrix_keypad();
    init_adc();
    init_clcd();
    while(1){
    get_speed();
    get_gear_pos();
    }
}