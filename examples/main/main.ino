#include <Max72xx.h>

Max72xx dev = Max72xx(12,10,11,3);


void setup(){
  Serial.begin(9600);
    int devs = dev.get_device_count();
    Serial.println(devs);

    dev.set_LED(1,2,2,false);
}

void loop(){

}
