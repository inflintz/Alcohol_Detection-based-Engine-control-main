#include <reg51.h>

sbit MQ05 = P1^0;    

sbit LED = P3^5;

sbit RS = P3^0;
sbit RW = P3^1;
sbit E  = P3^2;

sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit IN3 = P2^2;
sbit IN4 = P2^3;

void delay(unsigned int time)
{
    unsigned int i,j;
    for(i=0;i<time;i++)
    for(j=0;j<1275;j++);
}

void lcd_cmd(unsigned char cmd)
{
    P0 = cmd;
    RS = 0;
    RW = 0;
    E = 1;
    delay(2);
    E = 0;
}

void lcd_data(unsigned char value)
{
    P0 = value;
    RS = 1;
    RW = 0;
    E = 1;
    delay(2);
    E = 0;
}

void lcd_print(char *str)
{
    while(*str)
    {
        lcd_data(*str++);
    }
}

void lcd_init()
{
    delay(20);
    lcd_cmd(0x38);
    lcd_cmd(0x0C);
    lcd_cmd(0x01);
    lcd_cmd(0x06);
}

void main()
{
    lcd_init();

    while(1)
    {
        lcd_cmd(0x01);
        delay(5);

        if(MQ05 == 0)
        {
            LED = 1;

            IN1 = 0;
            IN2 = 0;
            IN3 = 0;
            IN4 = 0;

            lcd_print("Alcohol Detected");
        }
        else
        {
            LED = 0;

            IN1 = 1;
            IN2 = 0;
            IN3 = 1;
            IN4 = 0;

            lcd_print("No Alcohol");
        }

        delay(500);
    }
}