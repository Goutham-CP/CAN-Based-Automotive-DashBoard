#include <xc.h>
#include <stdint.h>
#include "can.h"
#include "clcd.h"
#include "msg_id.h"
#include "message_handler.h"
//#include "isr.h"
#include "timer0.h"

static void init_leds() {
    TRISB = 0x08; // Set RB2 as output, RB3 as input, remaining as output
    PORTB = 0x00;
}

static void init_config(void) {
    // Initialize CLCD and CANBUS
    init_clcd();
    init_can();
   // init_leds();

    // Enable Interrupts
  //  PEIE = 1;
  //  GIE = 1;
  //  init_timer0();
}

void main(void) {
    // Initialize peripherals
    init_config();
    uint16_t msg_id;
    uint8_t len=0;
    uint8_t data[8];
    
    /* ECU1 main loop */
    while (1) {
        
        can_receive(&msg_id,data,&len);
        data[len] = '\0';
        
        if(msg_id==SPEED_MSG_ID){
            
            clcd_print("SP", LINE1(0));
            clcd_print(data, LINE2(0));
            
        }
        
        if(msg_id==GEAR_MSG_ID){
            
            clcd_print("EV", LINE1(4));
            clcd_print(data, LINE2(4));
            
        }
        
        if(msg_id==RPM_MSG_ID){
            clcd_print("RPM", LINE1(8));
            clcd_print(data, LINE2(8));
            
            
        }
        
        if(msg_id==INDICATOR_MSG_ID){
            
            
            if(data[0]=='L'){
                
            clcd_print("IND", LINE1(13));
          //  clcd_print("  ", LINE2(12));
            clcd_print("<-", LINE2(13));
           
            
            }else if(data[0]=='R'){
             clcd_print("IND", LINE1(13));
            clcd_print("->", LINE2(13));
            
            }else{
             clcd_print("IND", LINE1(13));
            clcd_print("_ ", LINE2(13));   
            
            }            
            
        }
        // Read CAN Bus data and handle it
        
    }

    return;
}
