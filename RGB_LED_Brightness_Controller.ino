/*
Project: RGB LED Brightness Controller
Board: Arduino Uno

Description:
Use the Red, Green, and Blue buttons to select a color.
Adjust the brightness of the selected color using a potentiometer.
*/



//Button Pins
int BlueBtn=2;
int GreenBtn=3;
int RedBtn=4;

//LED Pins
int BlueLED=9;
int GreenLED=10; 
int RedLED=11;

// Analog input pin
int potpin=A0;

// Time delay for smoother button response (milliseconds)
int DelayTime = 100;

void setup(){
  pinMode(BlueBtn,INPUT);
  pinMode(GreenBtn,INPUT);
  pinMode(RedBtn,INPUT);

/*
Enable the internal pull-up resistor
Prevents the input pin from floating
HIGH = Not Pressed
LOW = Pressed
*/
  digitalWrite(BlueBtn,HIGH);
  digitalWrite(GreenBtn,HIGH);
  digitalWrite(RedBtn,HIGH);

/*
Common Anode RGB LED.
The common pin is connected to +5V.
The LED turns ON when the pin is LOW.
(Reverse the logic for a Common Cathode RGB LED.)
*/
  digitalWrite(BlueLED,HIGH);
  digitalWrite(GreenLED,HIGH);
  digitalWrite(RedLED,HIGH);

  pinMode(potpin,INPUT);

  pinMode(BlueLED,OUTPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(RedLED,OUTPUT);
}

void loop(){
  //Read Button states
  int BlueBtnVal=digitalRead(BlueBtn);
  int GreenBtnVal=digitalRead(GreenBtn);
  int RedBtnVal=digitalRead(RedBtn);

//Control the Blue LED until another button is pressed
  while (BlueBtnVal==0 && GreenBtnVal==1 && RedBtnVal==1){

    // Read potentiometer value
    int potVal=analogRead(potpin);
    //Converts Potentiometer value (0-1023) into PWM value (0-255)
    int LEDval= (255./1023.)*potVal;
    analogWrite(BlueLED,LEDval);

    // Check if another button is pressed.
    GreenBtnVal=digitalRead(GreenBtn);
    RedBtnVal=digitalRead(RedBtn);
    delay(DelayTime);

    // Exit Blue mode if Green or Red is pressed.
    if (GreenBtnVal==0 || RedBtnVal==0){
      BlueBtnVal=1;
    }
  }
//Control the Green LED until another button is pressed
  while (BlueBtnVal==1 && GreenBtnVal==0 && RedBtnVal==1){

    int potVal=analogRead(potpin);
    int LEDval= (255./1023.)*potVal;
    analogWrite(GreenLED,LEDval);

    // Check if another button is pressed.
    BlueBtnVal=digitalRead(BlueBtn);
    RedBtnVal=digitalRead(RedBtn);
    delay(DelayTime);
    // Exit Green mode if Blue or Red is pressed
    if (BlueBtnVal==0 || RedBtnVal==0){
      GreenBtnVal=1;
    }
  }
//Control the Red LED until another button is pressed
  while (BlueBtnVal==1 && GreenBtnVal==1 && RedBtnVal==0){

    int potVal=analogRead(potpin);
    int LEDval= (255./1023.)*potVal;
    analogWrite(RedLED,LEDval);

    // Check if another button is pressed
    GreenBtnVal=digitalRead(GreenBtn);
    BlueBtnVal=digitalRead(BlueBtn);
    delay(DelayTime);

    // Exit Red mode if Green or Blue is pressed
    if (GreenBtnVal==0 || BlueBtnVal==0){
      RedBtnVal=1;
    }
  }
}