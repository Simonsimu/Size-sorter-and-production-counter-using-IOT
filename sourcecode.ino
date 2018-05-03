

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>  // Include the Servo library

Servo servo_motor;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "b36c653424b049088a5ae7e332a95b4";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Digisol";
char pass[] = "";

int ir1=12; //Digital pin D6
int ir2=16; //Digital pin D7

int servoPin = 2 ;//Digital pin D4
int small=0;
int big=0;

int blynk_pin = 0;
void setup() {
  // put your setup code here, to run once:
     Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  servo_motor.attach(servoPin); // We need to attach the servo to the used pin number
  servo_motor.write(90);  //set servo at 90 degrees default
  Blynk.virtualWrite(V2,big);
  Blynk.virtualWrite(V3,small);
}

BLYNK_WRITE(V1){
    if (param.asInt()){       
        blynk_pin=1;
    } 
    else{
      blynk_pin=0;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
   Blynk.run();
if(blynk_pin) {
  int ir1_status=digitalRead(ir1);
  int ir2_status=digitalRead(ir2);
 /* if(ir1_status == 1 && ir2_status == 1){
    big = big + 1;
    Blynk.virtualWrite(V2,big);
    servo_motor.write(90);
    //delay(1000);
  }*/
  if(ir1_status == 1 && ir2_status == 0){
    small = small + 1;
    Blynk.virtualWrite(V3,small);
    servo_motor.write(160);
    //delay(1000);
  }
  else{
    servo_motor.write(90);
    //delay(1000);
        big = big + 1;
    Blynk.virtualWrite(V2,big);
  }
  delay(1000);
}

}
