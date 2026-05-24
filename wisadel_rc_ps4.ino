#include <PS4Controller.h>
#include <Wire.h>

//Right motor
int rightMotorPin1=18;
int rightMotorPin2=17;
//Left motor
int leftMotorPin1=1;
int leftMotorPin2=3;

const int PWMFreq = 1000; /* 1 KHz */
const int PWMResolution = 8;
const int rightMotorPWMSpeedChannel = 4;
const int leftMotorPWMSpeedChannel = 5;

const int oLedPin = 2;

bool oLedState = false;
bool oButtonPressed = false;

void notify()
{
  digitalWrite(rightMotorPin1, PS4.RStickY()<-25);
  digitalWrite(rightMotorPin2, PS4.RStickY()>25);
  digitalWrite(leftMotorPin1, PS4.LStickY()<-25);
  digitalWrite(leftMotorPin2, PS4.LStickY()>25);


}

void onConnect()
{
  Serial.println("Connected!.");
}

void onDisConnect()
{
  Serial.println("Disconnected!.");
}
void setUpPinModes()
{
  pinMode(rightMotorPin1,OUTPUT);
  pinMode(rightMotorPin2,OUTPUT);
  
  pinMode(leftMotorPin1,OUTPUT);
  pinMode(leftMotorPin2,OUTPUT);

}


void setup()
{
  setUpPinModes();
  Serial.begin(115200);
  PS4.attach(notify);
  PS4.attachOnConnect(onConnect);
  PS4.attachOnDisconnect(onDisConnect);
  PS4.begin();
  Serial.println("Ready.");

  pinMode(oLedPin, OUTPUT);

}

void loop() {
  if (PS4.isConnected()) {
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

}
