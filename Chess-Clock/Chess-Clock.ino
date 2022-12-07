#include "Countimer.h"
#include <TM1637.h>

int CLK1 = 2;
int DIO1 = 3;

int CLK2 = 4;
int DIO2 = 5;

const int Button1Pin = 8;
const int Button2Pin = 10;
const int Button3Pin = 12;

int button1State = 0; 
int button2State = 0; 
int button3State = 0; 

TM1637 tm16371(2, 3);
Countimer timer1;
Countimer timer2;
TM1637 tm16372(4, 5);

void setup() {
 
  Serial.begin(9600);
  
  tm16371.init();
  tm16372.init();

  pinMode(Button1Pin, INPUT);
  pinMode(Button2Pin, INPUT);
  pinMode(Button3Pin, INPUT);

  timer1.setCounter(0, 5, 0, timer.COUNT_DOWN);
  timer2.setCounter(0, 5, 0, timer.COUNT_DOWN);
}

void loop() {
  
  tm16371.display(1234);
  tm16372.display(4567);

  button1State = digitalRead(Button1Pin);
  button2State = digitalRead(Button2Pin);
  button3State = digitalRead(Button3Pin);

  if(button1State == HIGH){
  timer1.run();
  timer2.pause();    
  }
  if(button2State == HIGH){
  timer2.run();
  timer1.pause();    
  }
  if (button3State == HIGH) {
    timer1.pause();
    timer2.pause();
    timer1.restart();
    timer2.restart();
  }
}
