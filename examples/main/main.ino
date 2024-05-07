#include "Max72xx.h"

Max72xx d = Max72xx(12,11,10,4);

  int i = 0;
    int pannel = 0;

#define left_button 9
#define right_button 8



void setup() {
  Serial.begin(9600);
  setup_board();
  d.set_LED(2,7,7,true);
  pinMode(left_button,INPUT);
  pinMode(right_button,INPUT);
}

void loop() {
  int pushedr = digitalRead(right_button);
  int pushedl = digitalRead(left_button);s
  
  if(pushedr == HIGH)
    Serial.println("Right!");
  else if(pushedl == HIGH)
    Serial.println("Left!");
  
  int c_pan = pannel;
  int c_i = i;
  if(i != 0 && i != 1 && i % 8 == 0){
      //if(pannel == 3) && dir = right
      //  pannel = 0;
      if (pannel == -1){
        pannel = 3;
      }
      else
        pannel--;
      i=0;
  }
  else{
    i++;
  }
  //Serial.println(i);
  delay(50);
  d.set_LED(pannel,1,i,true);
  d.set_LED(c_pan,1,c_i,false);
}

void setup_board(){
  for (int i = 0; i < 4; i++){
    d.power_saving(i,false);
    d.set_intesity(i,8);
    d.clear_display(i);
  }
}
