#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include"ssd_display.h"

char OFF=1 ;
char left=0;
char right=0;
unsigned int delayL=0;
unsigned int delayR=0;
 unsigned char ssd[MAX_SSD_CNT];
 unsigned char digit[] = {ZERO, ONE,TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
 uint16_t data;
void init_config(void)
{
	init_ssd_control();
}

void Blink_Led(IndicatorStatus input){
    
    switch(input){
        
        
        case e_ind_left:
            if(delayL++==2){
            RB0=!RB0;
            RB1 = !RB1;
            delayL=0;
            }
            break;
         case e_ind_right:
             if(delayR++==2){
            RB6=!RB6;
            RB7 = !RB7;
            delayR = 0;
             }
            break;          
        
          case e_ind_off:
            RB0 = 0;
             RB1 = 0;
             RB6=0;
             RB7=0;
            break;
        
    }
    
    
    
    
    
    
}

int main()
{
    
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB6 = 0;
    TRISB7 = 0;
    init_adc();
    init_config();
    init_digital_keypad();
    init_can();
    while(1){
        
        uint16_t RPM =  get_rpm(); 
        
         ssd[3] = digit[RPM%10];
		ssd[2] = digit[(RPM/10)%10];
		ssd[1] = digit[(RPM/100)%10];
		ssd[0] = digit[(RPM/1000)];
        
        uint8_t str[5];
        str[0] = (RPM/1000) + '0';
        str[1] = ((RPM/100)%10) + '0';
        str[2] = ((RPM/10)%10) + '0';
        str[3] = (RPM%10) + '0';
        str[4] = '\0';
        uint8_t len;
    uint16_t msg_id;
    
    can_transmit(RPM_MSG_ID, str,4);
    __delay_ms(80);
    //can_receive(&msg_id, &data, &len);
            
    
        
       
    
 //   display(ssd);
       
     IndicatorStatus val =  process_indicator();
     
          uint8_t l;
    uint8_t tx_data;
    uint16_t msg;
    tx_data = (uint8_t)val;
    uint8_t rx_data;
    uint8_t Ind[2];
    if(val==e_ind_left){
        Ind[0] = 'L';
    }else if(val==e_ind_right){
        Ind[0] = 'R';
    }else if(val==e_ind_off){
        Ind[0] = 'N';
    }
    Ind[1] = '\0';
   
    can_transmit(INDICATOR_MSG_ID, Ind, 1);
    __delay_ms(80);
   // can_receive(&msg, &rx_data, &l);
     
    //IndicatorStatus coll = (IndicatorStatus)rx_data;
     
     if(val==e_ind_left){
         
         Blink_Led(e_ind_left);
                 
     }else if(val==e_ind_right){
         
         Blink_Led(e_ind_right);
                 
     }else{
         
         delayL = 0;
         delayR = 0;
         RB0=0;
         RB1 = 0;
         RB6 = 0;
         RB7 = 0;
     }
    }
    //call the functions*/
    }
    

