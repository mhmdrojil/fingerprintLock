#include <SoftwareSerial.h>
#include <Adafruit_Fingerprint.h>

SoftwareSerial mySerial(2, 3);
SoftwareSerial bt(4, 5);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const int lock = 8;
void setup(){
  Serial.begin(9600);
  while (!Serial);
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  pinMode(lock, OUTPUT);
  digitalWrite(lock, HIGH);
  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  bt.begin(9600);
}


void loop(){
  getFingerprintIDez();
  char dataHp = 0;
  if(bt.available()){
    dataHp = bt.read();
    if(dataHp == 'f'){
      buka();
    }
  }
  delay(100);
}

int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK){
    return -1;
  }

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK){
    return -1;
  }

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK){
    return -1;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.print(finger.confidence);
  buka();
  return finger.fingerID;
}

void buka(){
  digitalWrite(lock, LOW);
  Serial.println("\tKunci Terbuka");
  delay(5000);
  digitalWrite(lock, HIGH);
}