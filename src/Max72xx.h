#ifndef MAX72XX
#define MAX72XX

//Includes
#include <avr/pgmspace.h>

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h> // !fix maybe
#endif

// this is used to keep program data rather that RAM
const static byte charTable [] PROGMEM  = {
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B10000000,B00000001,B10000000,B00000000,
    B01111110,B00110000,B01101101,B01111001,B00110011,B01011011,B01011111,B01110000,
    B01111111,B01111011,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00000000,B00000000,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00001000,
    B00000000,B01110111,B00011111,B00001101,B00111101,B01001111,B01000111,B00000000,
    B00110111,B00000000,B00000000,B00000000,B00001110,B00000000,B00010101,B00011101,
    B01100111,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,
    B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000
};

class Max72xx {
    private:
        // Array for shifting data to device/devices
        byte spi[16];
        // Invoke command to device
        void spi_transfer(int adr, byte op, byte dta);
        // status of all 64 LED's
        byte stat[64];
        // Data is shifted out of this pin
        int SPI_MOSI;
        //The Clock pin
        int SPI_CLK;
        // Chip select pin
        int SPI_CS;
        // the max devices
        int max_devices;
    public:
        /*
        # This creates a new instance
        ## Params:
        - dataPin: the pin where the data is shifted
        - clockPin: the pin for the clock
        - csPin: the pin for selecting device
        - numDevices: max number of devices that can be controled
        */
        Max72xx(int dataPin, int clkPin, int csPin, int numDevices=1);

        /*
        # Gets the amount of devices that are attached
        ## Returns:
        - the number of devices attached
        */
        int get_device_count();

        /*
        # puts the device into power saving mode
        ## Params:
        - addr: The adrress of the display
        - status: True for power saving, False for normal
        */
        void power_saving(int addr, bool status);

        /*
        # Sets the intesity/brightness of the screen
        ## Params:
        - addr: The adrress of the display
        - intensity: the brightness of the display
        */
        void set_intesity(int addr, int intensity);

        /*
        # Turns off all LEDS
        ## Params:
        - addr: The adrress of the display
        */
        void clear_display(int addr);

        /*
        # Sets a LED on or off
        ## Params:
        - addr: The adrress of the display
        - row: The row the LED is on
        - col: The column the LED is on
        - state: True for LED on, False for LED off
        */
        void set_LED(int addr, int row, int col, bool state);

        /*
        # Sets a row of LEDs on or off
        ## Params:
        - addr: The adrress of the display
        - row: The row of LEDs
        - value: A byte to represent all values
        */
        void set_row(int addr, int row, byte value);

        /*
        # Sets a column of LEDs on or off
        ## Params:
        - addr: The adrress of the display
        - row: The column of LEDs
        - value: A byte to represent all values
        */
        void set_col(int addr, int col, byte value);

        /* 
         # Set the number of digits (or rows) to be displayed.
         ## See datasheet for sideeffects of the scanlimit on the brightnessof the display.
         ## Params :
         - addr	address of the display to control
         - limit	number of digits to be displayed (1..8)
         */
        void setScanLimit(int addr, int limit);

};

#endif