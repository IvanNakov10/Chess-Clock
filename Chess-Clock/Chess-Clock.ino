  #include "Countimer.h"
  #include <TM1637Display.h>


  #define CLK1 2
  #define DIO1 3
  #define CLK2 4
  #define DIO2 5


  uint8_t data1[] = {0, 0, 0, 0};
  uint8_t data2[] = {0, 0, 0, 0};

  TM1637Display display1(CLK1, DIO1);
  TM1637Display display2(CLK2, DIO2);
  int pinButton = 8;
  int OnOff = 9;
  int OnOffS;
  int State;

  Countimer timer1;
  Countimer timer2;
  void setup() {
    // put your setup code here, to run once:
    display1.setBrightness(2);
    
    display2.setBrightness(2);  
    
    timer1.setCounter(0, 10, 5, timer1.COUNT_DOWN, onComplete);    
    timer2.setCounter(0, 10, 5, timer2.COUNT_DOWN, onComplete);    
    timer1.setInterval(refreshClock1, 1000);
    timer2.setInterval(refreshClock2, 1000);
    pinMode(pinButton, INPUT_PULLUP);
    pinMode(OnOff, INPUT_PULLUP);
    Serial.begin(9600);
  }

  void refreshClock1() {
    Serial.print("White: ");
    Serial.println(timer1.getCurrentTime());
  }
  void refreshClock2() {
    Serial.print("BLack: ");
    Serial.println(timer2.getCurrentTime());
  }
  void onComplete() {
    
  }
  void loop() {
    State = digitalRead(pinButton);
    OnOffS = digitalRead(OnOff);
    
    if (OnOffS == 1) {
    if(State == 0){
      data1[0] = display1.encodeDigit(timer1.getCurrentMinutes()/10 % 10);
      data1[1] = display1.encodeDigit(timer1.getCurrentMinutes()/1 % 10);
      data1[2] = display1.encodeDigit(timer1.getCurrentSeconds()/10 % 10);
      data1[3] = display1.encodeDigit(timer1.getCurrentSeconds()/1 % 10);
      
      timer1.run();
      timer1.start();
      timer2.pause();

      display1.setSegments(data1);
    }
    else {
    data2[0] = display2.encodeDigit(timer2.getCurrentMinutes()/10 % 10);
    data2[1] = display2.encodeDigit(timer2.getCurrentMinutes()/1 % 10);
    data2[2] = display2.encodeDigit(timer2.getCurrentSeconds()/10 % 10);
    data2[3] = display2.encodeDigit(timer2.getCurrentSeconds()/1 % 10);
    
    timer2.run();
    timer2.start();
    timer1.pause();

    display2.setSegments(data2);
    
    } 
    }
    
    
  }
