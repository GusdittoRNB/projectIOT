#include<SPI.h>
#include<MFRC522.h>
#include<Servo.h>

const int pin_ss = 10;
const int pin_rst = 5;
const int pin_sp = 13;
MFRC522 rfid(pin_ss, pin_rst);

Servo palang;

const int pinTrig = 9;
const int pinEcho = 8;

void setup(){
  Serial.begin(9600);
  delay(1000);
  SPI.begin();
  rfid.PCD_Init();
  
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  palang.attach(4);

  palang.write(0);
}

void loop(){
  long duration, distance;
  digitalWrite(pinTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  duration = pulseIn(pinEcho, HIGH);
  distance = duration/58.2;
  Serial.println(distance);

  if((distance < 10) && (distance > 1)){
    palang.write(0);
  }

  if(!rfid.PICC_IsNewCardPresent() || rfid.PICC_ReadCardSerial()){
    return;
  }
  String id;
  id = String(rfid.uid.uidByte[0]) + String(rfid.uid.uidByte[1]) + String(rfid.uid.uidByte[2]) + String(rfid.uid.uidByte[3]);
  Serial.print("ID Anda: ");
  Serial.println(id);

  if(id == "23315853178"){
    Serial.print("Akses Diterima");
    palang.write(90);
    delay(1000);
    return;
  } else {
    Serial.print("Akses Ditolak");
    delay(1000);
  }

}