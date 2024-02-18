#include <SoftwareSerial.h>
SoftwareSerial bt(4, 5);
const int lock = 8;
void setup() {
  Serial.begin(9600);
  bt.begin(9600);
  pinMode(lock, OUTPUT);
  digitalWrite(lock, HIGH);
}

void loop() {
  char data = 0;
  if(bt.available()){
    data = bt.read();
    if(data == 'f'){
      buka();
    }
  }
  delay(1000);
}

void buka(){
  digitalWrite(lock, LOW);
  Serial.println("Kunci terbuka");
  delay(5000);
  digitalWrite(lock, HIGH);
}