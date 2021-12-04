#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial MyLED(2, 3); // RX | TX for HC-05 Controller

// Definitions of LED pin and servo pins
#define ledPin 4          // Initially used for testing HC-05
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
int state = 0;            // Psuedo-FSM that will drive different functions depending on input


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);     // Default communication rate of the Bluetooth module
  MyLED.begin(9600);
  servo0.attach(8);
  servo1.attach(9);
  servo2.attach(10);
  servo3.attach(11);
  
  servo0.write(92);       // set servos to mid-point
  servo1.write(93);
  servo2.write(93);
  servo3.write(93);
}

void loop() {
  //if
  //servo0.write(93);
  if (MyLED.available()) {        // Checks whether data is comming from the serial port
    state = MyLED.read();         // Reads the data from the serial port
    //state = Serial.read();      // If Bluetooth module not working, uncomment and test with serial I/O
  }
  // Switch statement to control functionality
  switch (state) {
  // LED cases were for testing phase only
    case '0':
      digitalWrite(ledPin, LOW); // Turn LED OFF
      Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
      state = 0;
      break;
    case '1':
      digitalWrite(ledPin, HIGH);
      Serial.println("LED: ON");;
      state = 0;
      break;
      
  // Different movements depending on keyboard/mobile inputs
    case 'w':
      moveForward();
      break;
    case 's':
      moveBackward();
      break;
    case 'd':
       turnRight();
       break;
    case 'a':
       turnLeft();
       break;
    case 'f':
      stopMove();
      break;
  }
}

// Locomotion Functions
void moveForward() {
  Serial.println("Servos Forward");
  servo0.write(80);
  servo1.write(100);
  servo2.write(100);
  servo3.write(80);
  state = 0;
}

void stopMove() {
  Serial.println("Stop Servos");
  servo0.write(92);  // set servo to mid-point
  servo1.write(93);
  servo2.write(93);
  servo3.write(93);
  state = 0;
}

void moveBackward() {
  Serial.println("Servos Backward");
  servo0.write(100);
  servo1.write(80);
  servo2.write(80);
  servo3.write(100);
  state = 0;
}

void turnRight() {
  Serial.println("Turn Right Slowly");
  servo0.write(95);
  servo1.write(95);
  servo2.write(95);
  servo3.write(95);
  state = 0;
}

void turnLeft() {
  Serial.println("Turn Left Slowly");
  servo0.write(90);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  state = 0;
}
