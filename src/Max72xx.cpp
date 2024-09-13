#include "Max72xx.h"
#include <algorithm>
#include <cstring>

// OP codes for the Max72xx family
enum OpCodes {
    OP_NOOP = 0,
    OP_DIGIT0 = 1,
    OP_DIGIT1 = 2,
    OP_DIGIT2 = 3,
    OP_DIGIT3 = 4,
    OP_DIGIT4 = 5,
    OP_DIGIT5 = 6,
    OP_DIGIT6 = 7,
    OP_DIGIT7 = 8,
    OP_DECODEMODE = 9,
    OP_INTENSITY = 10,
    OP_SCANLIMIT = 11,
    OP_SHUTDOWN = 12,
    OP_DISPLAYTEST = 15
};

// A macro for checking if an addr is valid
#define CHECK_ADDRESS_RANGE(addr, maxDevices) \
    if ((addr) < 0 || (addr) >= (maxDevices)) \
        return;

#define CHECK_ROW(row) \
    if(row < 0 || row > 7) \
        return;

#define CHECK_COL(col) \
    if(col < 0 || col > 7) \
        return;

Max72xx::Max72xx(int dataPin,int clkPin, int csPin, int numDevices){
    SPI_MOSI=dataPin;
    SPI_CLK=clkPin;
    SPI_CS=csPin;
    //this is because the limit of the Max72xx
    if(numDevices<=0 || numDevices>=8)
        numDevices = 8;
    
    max_devices = numDevices;


    pinMode(SPI_MOSI, OUTPUT);
    pinMode(SPI_CLK,OUTPUT);
    pinMode(SPI_CLK,OUTPUT);

    digitalWrite(SPI_CS, HIGH);

    memset(stat, 0, sizeof(stat));

    for(int i = 0; i < max_devices; i++) {
        spi_transfer(i, OpCodes::OP_DISPLAYTEST, 0);
        //scanLimit is set to max on startup
        setScanLimit(i, 7);
        
        spi_transfer(i, OpCodes::OP_DECODEMODE, 0);
        clear_display(i);

        power_saving(i, true);
    }
}


int Max72xx::get_device_count() const {
    return max_devices;
}

void Max72xx::power_saving(int addr, bool status){
    CHECK_ADDRESS_RANGE(addr,max_devices);

    if(status)
        spi_transfer(addr,OP_SHUTDOWN,0);
    else
        spi_transfer(addr,OP_SHUTDOWN,1);
}

void Max72xx::set_intesity(int addr, int intensity) {
    CHECK_ADDRESS_RANGE(addr,max_devices);
    
    if(intensity >= 0 && intensity < 16)
        spi_transfer(addr, OpCodes::OP_INTENSITY, intensity);
}

void Max72xx::clear_display(int addr) {
    int offset;

    CHECK_ADDRESS_RANGE(addr,max_devices);

    int offset = addr * 8;

    for (int i = 0; i < 8; i++) {
        stat[offset + i] = 0;
        spi_transfer(addr, i + 1, stat[offset + i]);
    }
}

void Max72xx::set_LED(int addr, int row, int col, bool state) {
    int offset;
    byte val = 0x00;

    CHECK_ADDRESS_RANGE(addr,max_devices);

    CHECK_ROW(row)
    CHECK_COL(col)
    
    offset = addr*8;

    val=B10000000 >> col;
    if(state)
        //the '|' is an bitwise OR opp
        stat[offset+row] = stat[offset+row]|val;
    else{
        //the'=~' is a NOT opp
        val=~val;
        //the '&' is a AND opp
        stat[offset+row] = stat[offset+row]&val;
    }
}

void Max72xx::setScanLimit(int addr, int limit){
    CHECK_ADDRESS_RANGE(addr,max_devices);

    if(limit>=0 && limit<8)
        spi_transfer(addr,OP_SCANLIMIT,limit);
}

void Max72xx::spi_transfer(int addr, volatile byte op, volatile byte data) {
    int offset = addr * 2;
    int max_bytes = max_devices * 2;

    memset(spi, 0, sizeof(spi));
    
    spi[offset + 1] = op;
    spi[offset] = data;

    digitalWrite(SPI_CS, LOW);

    for(int i = max_bytes; i > 0; i--)
        shiftOut(SPI_MOSI, SPI_CLK, MSBFIRST, spi[i-1]);
    
    digitalWrite(SPI_CS, HIGH);
}