#include <reg51.h>  // Include 8051 microcontroller headers

sbit MQ05 = P1^0;    // Pin assignment for MQ-05 gas sensor
sbit LED = P3^5;     // Pin assignment for LED indicator
sbit RS = P3^0;      // Pin assignment for RS pin of LCD
sbit RW = P3^1;      // Pin assignment for RW pin of LCD
sbit E = P3^2;       // Pin assignment for E pin of LCD

void delay(unsigned int time) {    
    while (time--);  // Simple delay loop
}

void lcd_cmd(unsigned char cmd) {
    P0 = cmd;  // Send command
    RS = 0;    // Command mode
    RW = 0;    // Write mode
    E = 1;
    delay(50);
    E = 0;
}

void lcd_write(unsigned char value) {
    P0 = value;  // Send value to LCD
    RS = 1;      // Data mode
    RW = 0;      // Write mode
    E = 1;
    delay(50);
    E = 0;
}

void lcd_init(void) {
    delay(15000);  // Initial delay for LCD startup
    lcd_cmd(0x38);  // Function set: 8-bit mode, 2 lines, 5x7 font
    lcd_cmd(0x0C);  // Display ON, Cursor OFF
    lcd_cmd(0x01);  // Clear display
}

void lcd_print(char *str) {
    while (*str) {
        lcd_write(*str);
        str++;
    }
}

void main(void) {
    lcd_init();  // Initialize the LCD display
    
    while (1) {
        lcd_cmd(0x01);  // Clear LCD before printing new message
        delay(1000);

        if (MQ05 == 0) {  // If alcohol is detected
            LED = 1;  // Turn on the LED indicator
            lcd_print("Alcohol Detected");
        } else {  // If alcohol is not detected
            LED = 0;  // Turn off the LED indicator
            lcd_print("No Alcohol");
        }

        delay(50000);  // Add some delay before refreshing message
    }
}
