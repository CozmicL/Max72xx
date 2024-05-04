#include <Max72xx.h>

Max72xx dev = Max72xx(12,11,10,1);


void setup(){
    int devs = dev.get_device_count();
    Serial.println(devs);
}

void loop(){

}