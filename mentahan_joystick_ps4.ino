if (PS4.LStickY() <= -25) {
    int motorSpeed = map(PS4.LStickY(), -25, -508, 70, 255);

    digitalWrite(IN1pin, HIGH);
    digitalWrite(IN2pin, LOW);
    digitalWrite(IN3pin, HIGH);
    digitalWrite(IN4pin, LOW);
    analogWrite(ENApin, motorSpeed);
    analogWrite(ENBpin, motorSpeed);
  }






  