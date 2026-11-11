#include "ecu2_sensor.h"
#include "adc.h"
#include "can.h"
#include "msg_id.h"
#include "uart.h"
#include"ssd_display.h"
uint16_t get_rpm()
{
    //Implement the rpm function
       uint16_t ADC_Val = read_adc(0x04);
       uint16_t RPM = (ADC_Val/10.23)*60;
       
     
       
    /*   ssd[3] = digit[RPM%10];
		ssd[2] = digit[(RPM/10)%10];
		ssd[1] = digit[(RPM/100)%10];
		ssd[0] = digit[(RPM/1000)];*/
 
    return RPM;
}

uint16_t get_engine_temp()
{
    //Implement the engine temperature function
}



IndicatorStatus process_indicator()
{
    
    unsigned char val =  read_digital_keypad(STATE_CHANGE);
    
    if(val==0x0E){
        
          OFF = 0;
          if(right==1){
              right = 0;
              RB6= 0;
            RB7 = 0;
          }
          left = 1;
           return e_ind_left;
                  
        
    }else if(val==0x0B){
        
        OFF = 0;
        
        right = 1;
        if(left==1){
            left = 0;
            RB0= 0;
            RB1 = 0;
        }
        return e_ind_right;
                       
    }else if(val==0x0D){
        
        OFF = 1;
        if(left==1){
            left = 0;
            
        }
        
        if(right==1){
            right = 0;
        }
        return e_ind_off;
    }
    
    if(left==1){
        return e_ind_left;
    }
    
    if(right==1){
        return e_ind_right;
        
    }
    
    if(OFF==1){
        return e_ind_off;
    }
    //Implement the indicator function
}