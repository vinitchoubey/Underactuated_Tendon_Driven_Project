#define BLYNK_TEMPLATE_ID "TMPL3ZWLu1XRT"
#define BLYNK_TEMPLATE_NAME "DESIGN LAB"
#define BLYNK_AUTH_TOKEN "7_gWYwq_PiAepl6b-ZvccmFhrDrXQ_j9"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

Servo f1, f2, f3;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Realme P3 Pro"; 
char pass[] = "111111101";     

int pin1 = 18;
int pin2 = 19;
int pin3 = 21;
int stopPoint = 90; 

int speedGrip = 85;   
int speedRetract = 105; 

void setup() {
  Serial.begin(115200);
  
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  f1.setPeriodHertz(50);
  f2.setPeriodHertz(50);
  f3.setPeriodHertz(50);

 
  Blynk.begin(auth, ssid, pass);

  f1.attach(pin1); 
  f2.attach(pin2); 
  f3.attach(pin3);

  f1.write(stopPoint); 
  f2.write(stopPoint); 
  f3.write(stopPoint);
  
  Serial.println("ESP32 System Ready (Pins 18, 19, 21)!");
}

BLYNK_WRITE(V0) {
  if (param.asInt() == 1) {
    Serial.println("Grip: ON");
    f1.write(speedGrip); f2.write(speedGrip); f3.write(speedGrip);
  } else {
    Serial.println("Grip: STOP");
    f1.write(stopPoint); f2.write(stopPoint); f3.write(stopPoint);
  }
}


BLYNK_WRITE(V2) {
  if (param.asInt() == 1) {
    Serial.println("!!! MANUAL STOP !!!");
    f1.write(stopPoint); f2.write(stopPoint); f3.write(stopPoint);
  }
}


BLYNK_WRITE(V3) {
  if (param.asInt() == 1) {
    Serial.println("Retract: ON");
    f1.write(speedRetract); f2.write(speedRetract); f3.write(speedRetract);
  } else {
    Serial.println("Retract: STOP");
    f1.write(stopPoint); f2.write(stopPoint); f3.write(stopPoint);
  }
}

void loop() {
  Blynk.run();
}