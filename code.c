#include<LPC17xx.h> 
    unsigned char sevensegment[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 
0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71}; 
    unsigned int dig_value[]={0,0,0,0,0}; 
    unsigned int select_segment[]={0,0<<23, 1<<23, 2<<23, 3<<23}; 
    unsigned int dig_count; 
    int prev=0; 
    unsigned long int i, flag, value, count,x,y,dir=1, people=0; 
    void upcount(){ 
        people++; 
    dig_value[1]++; 
    if(dig_value[1]>9){ 
        dig_value[2]++; 
        dig_value[1]=0; 
        if(dig_value[2]>9){ 
        dig_value[3]++; 
        dig_value[2]=0; 
        if(dig_value[3]>9){ 
        dig_value[4]++; 
        dig_value[3]=0; 
        if(dig_value[4]>9){ 
        dig_value[4]=0; 
}}}}} 
    void downcount(){ 
        people--; 
    dig_value[1]--; 
    if(dig_value[1]==-1){ 
        dig_value[2]--; 
        dig_value[1]=9; 
        if(dig_value[2]==-1){ 
        dig_value[3]--; 
        dig_value[2]=9; 
        if(dig_value[3]==-1){ 
        dig_value[4]--; 
        dig_value[3]=9; 
        if(dig_value[4]==-1){ 
        dig_value[4]=9; 
}}}}} 
void display(void){ 
    LPC_GPIO1->FIOPIN=select_segment[dig_count]; 
    LPC_GPIO0->FIOPIN=sevensegment[dig_value[dig_count]]<<4; 
    for(i=0;i<500;i++); 
    LPC_GPIO0->FIOCLR=0x00000FF0; 
} 
void delay(void){ 
    for(i=0;i<500;i++); 
    if(count==2000){ 
        flag=0xFF; 
        count=0; 
    } 
    else 
        count++; 
} 
void buzzer(){   
    LPC_PINCON->PINSEL1=1<<12; 
} 
void stop_buzzer(){  
    LPC_PINCON->PINSEL1=0<<12; 
} 
int main(){ 
    SystemInit(); 
    SystemCoreClockUpdate(); 
    LPC_PINCON->PINSEL0=0; 
    LPC_PINCON->PINSEL3=0; 
    LPC_PINCON->PINSEL4=0; 
    LPC_GPIO0->FIODIR |=0x00400FF0; 
    LPC_GPIO1->FIODIR=0x07800000; 
    LPC_GPIO2->FIODIR = ~(3<<0); 
        // LPC_GPIO0->FIOSET |= 1<<22; 
    while(1){ 
        delay(); 
        dig_count+=1; 
        if(dig_count==0x05){ 
            dig_count=0x00; 
        dig_count+=1;} 
        if(flag==0xFF){ 
            flag=0x00; 
            x=LPC_GPIO2->FIOPIN&1<<0; 
            y=LPC_GPIO2->FIOPIN&1<<1; 
  
            if (x==0) 
            { 
            if(prev==0)  
                            prev=1; 
            else if(prev==2) 
            {                            
            downcount(); 
                            if(people==0) 
                                stop_buzzer(); 
            prev=0; 
            } 
                    } 
  
            if (y==0){ 
            if(prev==0) prev=2; 
            else if(prev==1) 
            { 
            upcount(); 
                            if(people==5) 
                                buzzer(); 
            prev=0; 
  
            } 
                    } 
        } 
        display(); 
    } 
} 
