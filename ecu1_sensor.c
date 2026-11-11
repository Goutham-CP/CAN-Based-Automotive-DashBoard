#include "adc.h"
#include "can.h"
#include "ecu1_sensor.h"
#include "msg_id.h"
#include "uart.h"
#include"clcd.h"
#include "matrix_keypad.h"

uint16_t get_speed()
{
    // Implement the speed function
    unsigned short ADC_Val = read_adc(0x04);
    unsigned int duty = (ADC_Val / 10.23);
    
    uint8_t speed[3];
    
    speed[0] = (duty / 10)+'0';
    speed[1] = (duty %10)+'0';
    speed[2] = '\0';
    int len;
    uint16_t msg_id;
    init_can();
    can_transmit(SPEED_MSG_ID, speed, 2);
    __delay_ms(80);
   // can_receive(&msg_id, data, &len);
            
    //data[2] = '\0';
    // clcd_print("SPEED", LINE1(0));
    // clcd_print(data, LINE2(0));
    
    
}

unsigned char get_gear_pos()
{
    
     unsigned char val = read_switches(STATE_CHANGE);
     
     if(val==MK_SW1){
         
         if(ind>=0 && ind<7){
         ind++;

         }
         
      //   clcd_print("GEAR",LINE1(6));
        
      //   clcd_print(ev[ind],LINE2(6));
         
     }else if(val==MK_SW2){
         
         if(ind==8){
             ind = 0;
             
         }
         
         if(ind>0){
         ind--;
         }
         
         
      //   clcd_print("GEAR",LINE1(6));
         
      //   clcd_print(ev[ind],LINE2(6));
         
         
     }else if(val==MK_SW3){
          
         ind = 8;
     //    clcd_print("GEAR",LINE1(6));
        
     //    clcd_print(ev[ind],LINE2(6));
     }
    
     int len;
    uint16_t msg_id;
    init_can();
    uint8_t G[5];
    G[0]=ev[ind][0];
    G[1] = ev[ind][1];
    G[2] = ev[ind][2];
    G[3] = ev[ind][3];
    G[4] = '\0';
    can_transmit(GEAR_MSG_ID,G,4);
    __delay_ms(80);
   // can_receive(&msg_id, GEAR, &len);
   // clcd_print("GEAR",LINE1(6));    
   // clcd_print(GEAR,LINE2(6));
    
    
}