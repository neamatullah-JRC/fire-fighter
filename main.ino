#include <PWMServo.h>
#include <SoftwareSerial.h>


#define in1 4 //Motor1  L298 Pin in1 
#define in2 5 //Motor1  L298 Pin in2 
#define in3 6 //Motor2  L298 Pin in3 
#define in4 7 //Motor2  L298 Pin in4 


//Sensor Connection
const int fire_sensor_pin = 8;
const int servo_pin = 9;
const int relay_pin = 10;
int flame = 1;

int bt_ir_data;
SoftwareSerial BT_Serial(2, 3); // RX, TX
PWMServo myservo;

int pos = 0;

void setup() {
  Serial.begin(9600);
  BT_Serial.begin(9600);
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4

  pinMode(relay_pin, OUTPUT);
  pinMode(fire_sensor_pin, INPUT_PULLUP);
  digitalWrite(relay_pin, HIGH);
  myservo.attach(servo_pin);
  delay(1000);
  myservo.write(90);
}

void loop() {


  int flame = digitalRead(fire_sensor_pin);
  Serial.print(" flame=");
  Serial.print(flame);
  Serial.println();
  if (flame == 1)
  {
    if (BT_Serial.available() > 0) { //if some date is sent, reads it and saves in state
      bt_ir_data = BT_Serial.read();
      Serial.println(bt_ir_data);
    }

    if (bt_ir_data == 1) {
      forword();
    }
    else if (bt_ir_data == 2) {
      backword();
    }
    else if (bt_ir_data == 3) {
      turnLeft();
    }
    else if (bt_ir_data == 4) {
      turnRight();
    }
    else if (bt_ir_data == 5) {
      Stop();
    }
    else if (bt_ir_data == 8) {
      Stop();
    spray();
    }
    else if(bt_ir_data == 10){                                               
      flame == 1;
    }
 
  }
  else if (flame == 0 ) {
    Stop();
    spray();
  }

}
void forword() { //forword

  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin


}

void backword() { //backword

  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin


}

void turnRight() { //turnRight

  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin


}
void turnLeft() { //turnRight

  digitalWrite(in1, HIGH);  //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, HIGH);  //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin

}
void Stop() { //stop

  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin

}
void spray() {
  digitalWrite(relay_pin, LOW);
  for (pos = 90; pos <= 135; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 135; pos >= 45; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 45; pos <= 135 ; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 135; pos >= 45; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 45; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(relay_pin, HIGH);
}
