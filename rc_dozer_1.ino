//sebelumnya pastikan esp32 dan stick ps4 sudah dipairing atau kek sudah punya id bt yang sama gitu dah pokonya

#include <PS4Controller.h>
#include <Wire.h>

const int oLedPin = 2; //led 1 ps

bool oLedState = false;
bool pLedState = false;
bool aLedState = false;
bool sLedState = false;
bool dLedState = false;

bool oButtonPressed = false;
bool pButtonPressed = false;
bool aButtonPressed = false;
bool sButtonPressed = false;
bool dButtonPressed = false;

int ledpin = 2;// led 2 kotak
int ledpin1 = 16;// led 3 bulat
int motor1 = 5;// motor 1 X
int motor2 = 17;// motor 2 Share
int engine1 = 22;// engine L2
int engine2 = 23;

int ENApin = 27; //pwm1 jy 1
int IN1pin = 26; //ch1   jy1
int IN2pin = 25; //ch1   jy1
int IN3pin = 18; //ch2   jy2
int IN4pin = 19; //ch2   jy2
int ENBpin = 21; //pwm2 jy 2
   


void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");
}

void setup()
{
  Serial.begin(115200);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");

  pinMode(oLedPin, OUTPUT);

  pinMode(ledpin, OUTPUT);
  pinMode(ledpin1, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(engine1, OUTPUT);
  pinMode(engine2, OUTPUT);

  pinMode(ENApin, OUTPUT);
  pinMode(IN1pin, OUTPUT);
  pinMode(IN2pin, OUTPUT);
  pinMode(IN3pin, OUTPUT);
  pinMode(IN4pin, OUTPUT);
  pinMode(ENBpin, OUTPUT);

}

void loop() {
 if (PS4.isConnected()) { //led 1 psbutton
  if (PS4.PSButton()) {
    if (!oButtonPressed) {
        oLedState = !oLedState;
        digitalWrite(oLedPin, oLedState ? HIGH : LOW);
        oButtonPressed = true;
    }
  } else {
      oButtonPressed = false;
    }
  }
  
  if (PS4.isConnected()) {  //led 2 kotak
   if (PS4.Square()) {
    if (!pButtonPressed) {
        pLedState = !pLedState;
        digitalWrite(ledpin, pLedState ? HIGH : LOW);
        pButtonPressed = true;
    }
  } else {
      pButtonPressed = false;
    }
  }

  if (PS4.isConnected()) {  //led 3 bulat
   if (PS4.Circle()) {
    if (!aButtonPressed) {
        aLedState = !aLedState;
        digitalWrite(ledpin1, aLedState ? HIGH : LOW);
        aButtonPressed = true;
    }
  } else {
      aButtonPressed = false;
    }
  }

  if (PS4.isConnected()) {  //motor 1 x
   if (PS4.Cross()) {
    if (!sButtonPressed) {
        sLedState = !sLedState;
        digitalWrite(motor1, sLedState ? HIGH : LOW);
        sButtonPressed = true;
    }
  } else {
      sButtonPressed = false;
    }
  }

  if (PS4.isConnected()) {  //motor 2 share
   if (PS4.Share()) {
    if (!dButtonPressed) {
        dLedState = !dLedState;
        digitalWrite(motor2, dLedState ? HIGH : LOW);
        dButtonPressed = true;
    }
  } else {
      dButtonPressed = false;
    }
  }

  int R_data = PS4.RStickY(); // joy kanan ch1-1 dan ch2-1
  
    Serial.print("R_data:");
    Serial.print(R_data);
    Serial.print("\E");
    delay(0);

  int x_data = PS4.LStickY(); // joy kiri ch1-2 dan ch2-2
  
    Serial.print("x_data:");
    Serial.print(x_data);
    Serial.print("\n");
    delay(0);

    if (x_data <= -25) { //ch1-1
      int speed_F = map(x_data, -25, -128, 70, 255);

      digitalWrite(IN1pin, HIGH);
      digitalWrite(IN2pin, LOW);
      analogWrite(ENApin, speed_F);
    }  

    if (x_data >= 25) { //ch2-1

      int speed_B = map(x_data, 25, 126, 70, 255);

      digitalWrite(IN1pin, LOW);
      digitalWrite(IN2pin, HIGH);
      analogWrite(ENApin, speed_B);
    }
   
    if (R_data <= -25) { //ch1-2
      int speed_I = map(R_data, -25, -128, 70, 255);

      digitalWrite(IN3pin, HIGH);
      digitalWrite(IN4pin, LOW);
      analogWrite(ENBpin, speed_I);
    }
    
    if (R_data >= 25) { //ch2-2

      int speed_C = map(R_data, 25, 126, 70, 255);

      digitalWrite(IN3pin, LOW);
      digitalWrite(IN4pin, HIGH);
      analogWrite(ENBpin, speed_C);
    }

  if (PS4.LStickY() > -25 && PS4.LStickY() < 25) { //motor rem
      digitalWrite(IN1pin, LOW);
      digitalWrite(IN2pin, LOW);
      analogWrite(ENApin, 0);
    }
  
  if (PS4.RStickY() > -25 && PS4.RStickY() < 25) { //motor rem
      digitalWrite(IN3pin, LOW);
      digitalWrite(IN4pin, LOW);
      analogWrite(ENBpin, 0);
    }

  int enginespeed1 = PS4.L2Value();
    if (enginespeed1) { // engine

      int speed_S = map(enginespeed1, 0, 255, 30, 255);
      analogWrite(engine1, speed_S);
    }
    else {
      int speed_S = map(enginespeed1, 0, 255, 0, 0);
      analogWrite(engine1, speed_S);
    }


  int enginespeed2 = PS4.L1();
    if (enginespeed2) { // engine

      int speed_X = map(enginespeed2, 0, 255, 255, 180);
      analogWrite(engine2, speed_X);
    }
    else {
      int speed_X = map(enginespeed2, 0, 255, 0, 0);
      analogWrite(engine2, speed_X);
    }
}
