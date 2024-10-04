#define BLYNK_TEMPLATE_ID "TMPL6YoDOA6bF"
#define BLYNK_TEMPLATE_NAME "SmartBank"
#define BLYNK_AUTH_TOKEN "Tszg__ZYh_CprSFjCDQ-_HDlN13Ru8Sz"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

#define S0 25
#define S1 33
#define S2 2
#define S3 4
#define OutputSensor 26
#define SS_PIN 15
#define RST_PIN 5
#define BUZZER 32

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Anindita";
char pass[] = "240304180416";

long jumlah = 0;

int lock;
int red = 0;
int green = 0;
int blue = 0;
int white = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

MFRC522 rfid(SS_PIN, RST_PIN);

byte authorizedUID[4] = {0x93, 0x78, 0x62, 0x35};

Servo servo;

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OutputSensor, INPUT);

  pinMode(BUZZER, OUTPUT);

  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  SPI.begin(); 
  rfid.PCD_Init(); 

  lcd.init(); 
  lcd.backlight();

  servo.attach(13);
  servo.write(0);
   
  timer.setInterval(1000L, sendJumlah);
  timer.setInterval(1000L, controlRfid);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
  timer.run();
}

void sendJumlah(){
  digitalWrite(S2, LOW);  
  digitalWrite(S3, LOW);   
  delay(50); 
  red = pulseIn(OutputSensor, digitalRead(OutputSensor) == HIGH ? LOW : HIGH);
  Serial.print("R = ");
  Serial.print(red);
  Serial.print(" ");

  //green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);  
  delay(50);  
  green = pulseIn(OutputSensor, digitalRead(OutputSensor) == HIGH ? LOW : HIGH);
  Serial.print("G = ");
  Serial.print(green);
  Serial.print(" ");

    //blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH); 
  delay(50);  
  blue = pulseIn(OutputSensor, digitalRead(OutputSensor) == HIGH ? LOW : HIGH);
  Serial.print("B = ");
  Serial.print(blue);
  Serial.println(" ");

  if((red >= 180 && red <= 210) && (green >= 240 && green <= 270) && (blue >= 200 && blue <= 230)){
    jumlah = jumlah + 100000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter : 100.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 240 && red <= 270) && (green >= 230 && green <= 270) && (blue >= 180 && blue <= 210)){
    jumlah = jumlah + 50000;
    lcd.setCursor(0, 0);        
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :  50.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 200 && red <= 230) && (green >= 215 && green <= 240) && (blue >= 200 && blue <= 230)){
    jumlah = jumlah + 20000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :  20.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 180 && red <= 210) && (green >= 200 && green <= 230) && (blue >= 180 && blue <= 210)){
    jumlah = jumlah + 10000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :  10.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 170 && red <= 200) && (green >= 220 && green <= 250) && (blue >= 230 && blue <= 260)){
    jumlah = jumlah + 5000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :   5.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 220 && red <= 240) && (green >= 241 && green <= 260) && (blue >= 210 && blue <= 230)){
    jumlah = jumlah + 2000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :   2.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
  } else if((red >= 180 && red <= 230) && (green >= 230 && green <= 250) && (blue >= 250 && blue <= 280)){
    jumlah = jumlah + 1000;
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
    lcd.setCursor(0, 1);   
    lcd.print("N.Ter :   1.000");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW); 
  } else {
    lcd.setCursor(0, 0);         
    lcd.print("Jml : ");
    lcd.setCursor(7, 0);  
    lcd.print(jumlah);
  }

  Blynk.virtualWrite(V0, jumlah);
}

void controlRfid(){
   if (rfid.PICC_IsNewCardPresent()) { // new tag is available
    if (rfid.PICC_ReadCardSerial()) { // NUID has been readed
      MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);

      if (rfid.uid.uidByte[0] == authorizedUID[0] &&
          rfid.uid.uidByte[1] == authorizedUID[1] &&
          rfid.uid.uidByte[2] == authorizedUID[2] &&
          rfid.uid.uidByte[3] == authorizedUID[3] &&
          lock == 0) {
        Serial.println("Door Lock");
        digitalWrite(BUZZER, HIGH);
        delay(100);
        digitalWrite(BUZZER, LOW);
        servo.write(80); 
        lock = 1;
      } else if (rfid.uid.uidByte[0] == authorizedUID[0] &&
          rfid.uid.uidByte[1] == authorizedUID[1] &&
          rfid.uid.uidByte[2] == authorizedUID[2] &&
          rfid.uid.uidByte[3] == authorizedUID[3] &&
          lock == 1) {
          Serial.println("Door Unlock");
          digitalWrite(BUZZER, HIGH);
          delay(100);
          digitalWrite(BUZZER, LOW);
          servo.write(0); 
          lock = 0;
      } else {
        Serial.print("Unauthorized Tag with UID:");
        for (int i = 0; i < rfid.uid.size; i++) {
          Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(rfid.uid.uidByte[i], HEX);
        }
        Serial.println();
        digitalWrite(BUZZER, HIGH);
        delay(100);
        digitalWrite(BUZZER, LOW);
        delay(100);
        digitalWrite(BUZZER, HIGH);
        delay(100);
        digitalWrite(BUZZER, LOW);
      }

      rfid.PICC_HaltA(); 
      rfid.PCD_StopCrypto1();
    }
  }

  if(lock == 0){
    Blynk.virtualWrite(V4, "Terbuka");
  } else if(lock == 1){
    Blynk.virtualWrite(V4, "Terkunci");
  }
}

BLYNK_WRITE(V1){
  int control = param.asInt();

  if (control == HIGH && lock == 0){
    Serial.println("Door Lock");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    servo.write(80); 
    lock = 1;
  } 
}

BLYNK_WRITE(V2){
  int control = param.asInt();

  if (control == HIGH && lock == 1){
    Serial.println("Door Lock");
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
    servo.write(0); 
    lock = 0;
  } 
}

BLYNK_WRITE(V3){
  int reset = param.asInt();

  if(reset == HIGH){
  jumlah = 0;
  lcd.clear();
  lcd.setCursor(0, 0);         
  lcd.print("Jml : ");
  lcd.setCursor(7, 0);  
  lcd.print(jumlah);
  Blynk.virtualWrite(V0, jumlah);
  }
}