#include "Max72xx.h"

Max72xx d = Max72xx(12, 11, 10, 4);

int i = 0;
int j = 0;
int pannel = 0;

#define left_button 9
#define right_button 8
#define up_button 7
#define down_button 6

bool left = false;
bool right = false;
bool up = false;
bool down = false;

int rx = random(0,7);
int ry = random(0,7);
int rp = random(0,3);


void setup() {
  Serial.begin(9600);
  setup_board();
  d.set_LED(2, 7, 7, true);
}

void loop() {
  int pushedr = digitalRead(right_button);
  int pushedl = digitalRead(left_button);
  int pushedu = digitalRead(up_button);
  int pushedd = digitalRead(down_button);

  if (pushedr != HIGH) {
    left = false;
    right = true;
    up = false;
    down = false;
  }
  else if (pushedl != HIGH) {
    left = true;
    right = false;
    up = false;
    down = false;
  }
  else if (pushedu != HIGH) {
    down = false;
    up = true;
    left = false;
    right = false;
  }
  else if (pushedd != HIGH) {
    down = true;
    up = false;
    left = false;
    right = false;
  }

  if (right)
    move_right();
  else if (left)
    move_left();
  else if (up)
    move_up();
  else if (down)
    move_down();


  int c_pan = pannel;
  int c_i = i;
  int c_j = j;

  if (i == rx && j == ry && rp == pannel){

    d.set_LED(rp, rx, ry, true);
    generate_fruit();
  }
  
  //move_right();
  //Serial.println(i);
  delay(100);
  d.set_LED(pannel, j, i, true);
  d.set_LED(c_pan, c_j, c_i, false);

}

void move_right() {
  if (i != 8 && i == 0) {
    if (pannel == 3)
      pannel = 0;
    else
      pannel++;
    i = 8;
  }
  else
    i--;
}

void move_down() {
  j--;
   if (j <0)
   j = 7;
}

void move_up() {
   j++;
   if (j >7)
   j = 0;

/*  
  if (j != 0 && j % 8 == 0) {
    j = 0;
  }
  else
    j++;*/
}

void move_left() {
  if (i != 0 && i % 8 == 0) {
    if (pannel == 0) {
      pannel = 3;
    }
    else
      pannel--;
    i = 0;
  }
  else {
    i++;
  }
}

void setup_board() {
  for (int i = 0; i < 4; i++) {
    d.power_saving(i, false);
    d.set_intesity(i, 8);
    d.clear_display(i);
  }
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(up_button, INPUT);
  pinMode(down_button, INPUT);

  first_fruit();
}

void first_fruit(){

  d.set_LED(rp, rx, ry, true);
  
}



void generate_fruit(){
  if (i == rx && j == ry && rp == pannel){
    rx = random(0,7);
    ry = random(0,7);

    
    rp = random(0,3);
    d.set_LED(rp, rx, ry, true);
    generate_fruit();
  }

}
