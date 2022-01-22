//libraries========================================================
#include "TVout.h"
#include "fontALL.h"
#include <string.h>
#include <EEPROM.h>
#include <stdio.h>

#include <SPI.h>
#define PADDLE_W 1
#define PADDLE_H 10
#define CENTERX 60
#define CENTERY 48
#define OFFSETX 10                                            //Needed for the big PONG in intro()
#define OFFSETY 20                                            //^^
#define BALLSPEED 20                                          //The time between ball redrawings
#define MAX_FOOLNESS 5
#define POINTS_LINE 8
#define SINGLE_PLAYER_OFFSET 0
#define MULTIPLAYER_OFFSET 60
#define MENUY 90
TVout TV;int y = 0;const char* menu_items[] = {};
char buf = 0b00000000;
char command[] = {};
int strings = 0;char* strings2[7];
int scroll2 = 0;int port_x = 0;int element;
int port_y = 0;
//test programms

//programms========================================================

  void code(){            
      int __a;    
      __asm__ __volatile__                      
      ( "=1" (__a));
      TV.fill(0);
      TV.print(__a);
    
    
  }
  void readmusicfromeeprom(int port){
    int x = 0;
    int time;
    int time2;
    int tone_;
    while(x <= 500){ 
    tone_ = 8 * EEPROM.read(x);
    time = 8 * EEPROM.read(x + 1);time2 = 8 * EEPROM.read(x + 2);
    tone(port,tone_,time);
    delay(time2);
    x = x + 3;
    
    
    
  }}
  void eeprom_utilwrite(){
 delay(500);
  TV.fill(0);
  char data = 0;
  int reading_sector = 0;
  while(analogRead(A1) < 100){
  if(analogRead(A0) > 100){reading_sector = reading_sector + 1;while(analogRead(A0) > 100){}}
  TV.set_cursor(60,60);TV.print(reading_sector);
  }
  delay(200);
  while(analogRead(A1) < 100){
  if(analogRead(A0) > 100){if(data == 255){data == 0;}data = data + 1;while(analogRead(A0) > 100){}}
  TV.set_cursor(60,60);TV.print(int(data));
  
  }
  TV.fill(0);
  EEPROM.write(reading_sector,data);
  while(analogRead(A0) < 100){} 
  
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

void eeprom_util(){
 delay(500);
  TV.fill(0);
  uint8_t* buff;
  int reading_sector = 0;
  while(analogRead(A1) < 100){
  if(analogRead(A0) > 100){reading_sector = reading_sector + 1;while(analogRead(A0) > 100){}}
  TV.set_cursor(60,60);TV.print(reading_sector);
  }
  TV.fill(0);
  TV.print(int(EEPROM.read(reading_sector)));
  while(analogRead(A0) < 100){} 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
}
 void PINSREAD(){
   TV.fill(0);
   TV.draw_rect(0,0,128,3,0,0);
   while(analogRead(A0) < 100){
   TV.fill(0);
   TV.set_cursor(6,10);
   TV.print("A0:");
   TV.set_cursor(6,20);
   TV.print("A1:");
   TV.set_cursor(6,30);
   TV.print("A2:");
   TV.set_cursor(6,40);
   TV.print("A3:");
   TV.set_cursor(6,50);
   TV.print("A4:");
   TV.set_cursor(6,60);
   TV.print("A5:");
   TV.set_cursor(30,10);
   TV.print(analogRead(A0));
   TV.set_cursor(30,20);
   TV.print(analogRead(A1));
   TV.set_cursor(30,30);
   TV.print(analogRead(A2));
   TV.set_cursor(30,40);
   TV.print(analogRead(A3));
   TV.set_cursor(30,50);
   TV.print(analogRead(A4));
   TV.set_cursor(30,60);
   TV.print(analogRead(A5));
   delay(500);
   }}
void menu_select(){
  //TV.fill(0);
  TV.draw_rect(0,0,128,3,1,1);
  TV.set_cursor(6,6);
  TV.print("MENU_SELECT_UTILITY:");
  int y = 0;
  while(analogRead(A0) < 100){

    TV.draw_rect(0,0,128,3,1,1);
    TV.set_cursor(6,14);TV.print(menu_items[y]);
    TV.set_cursor(6,20);TV.print(menu_items[y + 1]);
    TV.set_cursor(6,26);TV.print(menu_items[y + 2]);
    TV.set_cursor(6,32);TV.print(menu_items[y + 3]);
    TV.set_cursor(6,60);TV.print(y);
    if(analogRead(A1) > 100){y = y + 1;TV.draw_rect(10,15,128,96,0,0);while(analogRead(A1) > 100){}}
    if(y >= sizeof(menu_items)){y = 0;} 
    
  }
element = y;
}
void flappygame() {
  const int JUMP_BTN_PIN = A0;float fball_y = 40;
float fball_dy = -1.5;


bool btn_pressed = false;
bool game_over = false;
int score = 0;
  // put your setup code here, to run once:
  TV.select_font(font6x8);
  pinMode(JUMP_BTN_PIN, INPUT_PULLUP);
  TV.delay(1000);
  new_port();console_panel("flappygame:");
  while(1){  // put your main code here, to run repeatedly:

  // 1. check for game end condition
  if ((int)fball_y+4>TV.vres() || (int)fball_y-3<0) game_over=true;
  if (32==port_x && (fball_y<port_y-16 || fball_y>port_y+16)) game_over=true; 

  // 2. if port leaves the screen, create new
  if (port_x==1) {
    score=score+1;
    new_port();
  }

  // 3. handle input
  if (digitalRead(JUMP_BTN_PIN)==HIGH) {
    btn_pressed = false;
  }
  else {
    // jump up only _once_ when the btn goes down
    if (!btn_pressed) {
      fball_dy=-1.5;
      btn_pressed = true;

      // start a new game with a press of a btn
      if (game_over) {  
        score = 0;
        fball_y = 40;
        new_port();
        game_over = false;
      }
    }
  }
  // do not update state if game is already over
  if (game_over) return;  

  // 4. update state by ...
  // ... accelerating fall, and
  fball_dy=fball_dy+0.04;
  fball_y=fball_y+fball_dy;
  // ... progressing wall
  port_x=port_x-1;

  // 5. wait for vsync and then redraw the screen
  TV.delay_frame(1);
  TV.clear_screen();
  TV.print(2, 2, score);
  // ports
  TV.draw_line(port_x, 0, port_x, port_y-16, WHITE);
  TV.draw_line(port_x, port_y+16, port_x, TV.vres()-1, WHITE);
  // ball
  TV.draw_circle(30, (int)fball_y, 3, WHITE, WHITE);
  // "eye" of the ball
  if (btn_pressed) TV.draw_line(30, (int)fball_y, 33, (int)fball_y, BLACK);
  else TV.draw_circle(31, (int)fball_y, 1, BLACK, BLACK);}
}

void new_port() {
  port_x=TV.hres()-1;
  port_y=random(20,TV.vres()-30); 
}




//main code=======================================================
/*void eeprom_executer(){
 //execute mini aliases from eeprom 
  int sector = 0;
  char data;
  int x = 0;
  while(x <= 1024){
   data = EEPROM.read(sector); 
   if(data == 0b00000001){TV.fill(int(EEPROM.read(sector + 1)));sector = sector + 2;}
   if(data == 0b00000001){TV.draw_rect(int(EEPROM.read(sector + 1)),int(EEPROM.read(sector + 2)),int(EEPROM.read(sector + 3)),int(EEPROM.read(sector + 4)),int(EEPROM.read(sector + 5)),int(EEPROM.read(sector + 6)));sector = sector + 7;}
 if(data == 0b00000001){sector = sector + 7;}
    
    
    
    
    
    
    
  }
  
  
  
  
  
  
  
  
  
  
}*/
void console_panel(char* text){TV.draw_rect(0,0,127,8,1,0);TV.set_cursor(0,3);TV.print(text);}
void console_output(char* text){TV.set_cursor(6,80);TV.print(">>");TV.set_cursor(12,60);strings = strings + 1;TV.print(text);}
void input_buttons(){int read1;int read2;int x = 0;int y;int a = 10;while(x <= 7){read1 = digitalRead(A0);    if(read1 == 1){    digitalWrite(2,0);    read2 = digitalRead(A1);int b = 0;int num = 1;while(!(b >= 7 - x))  {    num = num * 0b10;        b = b + 1;  }    if(read2 == 1){buf = buf + num;}    if(read2 == 0){}    x = x + 1;    while(read1 != 0){read1 = digitalRead(A0);}  }  if(x >= 8){}}digitalWrite(3,1);delay(100);digitalWrite(3,0);x = 0;}
void print_(char* text){
 strings2[0] = strings2[1];
 strings2[1] = strings2[2];
 strings2[2] = strings2[3];
 strings2[3] = strings2[4];
 strings2[4] = strings2[5];
 strings2[5] = strings2[6];
 strings2[6] = text;
 TV.fill(0);
 TV.set_cursor(6,10);TV.print(strings2[0]);
 TV.set_cursor(6,20);TV.print(strings2[1]);
 TV.set_cursor(6,30);TV.print(strings2[2]);
 TV.set_cursor(6,40);TV.print(strings2[3]);
 TV.set_cursor(6,50);TV.print(strings2[4]);
 TV.set_cursor(6,60);TV.print(strings2[5]);
 TV.set_cursor(6,70);TV.print(strings2[6]);
  
  
}
void setup(){
TV.begin(PAL);
TV.select_font(font6x8);console_panel("MAIN_MENU");
}
void loop(){
  const char* main_menu_items[] = {"flappy","eeprom_readblock","pinsread","unstable menu","code","eepromwriteblock","readmusicfromeeprom"};
  
  
  
  
  

if(analogRead(A0) > 100){y = y + 1;TV.fill(0); console_panel("main menu:"); while(analogRead(A0) > 100){}}
if(y >= 7){y = 0;}
TV.set_cursor(10,40);
TV.print(main_menu_items[y]);
TV.set_cursor(10,60);
TV.print(y);
if(analogRead(A1) > 100){

if(y == 0){flappygame();TV.fill(0);}
if(y == 1){eeprom_util();TV.fill(0);}
if(y == 2){PINSREAD();TV.fill(0);}
if(y == 3){const char* menu_items[] = {"flappy","eeprom_util","pinsread","unstable menu"};menu_select();TV.fill(0);}
if(y == 4){code();TV.fill(0);}
if(y == 5){eeprom_utilwrite();TV.fill(0);}
if(y == 6){readmusicfromeeprom(4);TV.fill(0);}
}

  }









