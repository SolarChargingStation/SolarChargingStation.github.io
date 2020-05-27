#include<SPI.h>
#include<MFRC522.h>

#define SS_PIN 53
#define RST_PIN 49
MFRC522 mfrc522(SS_PIN, RST_PIN);

int EncoderA = 2;
int EncoderB = 3;
int M1C1 = 4;
int M1C2 = 5;
int M1PWM = 6;
int M1E = 7;
int M2C1 = 8;
int M2C2 = 9; 
int M2WM = 10;
int M2E = 11;
int M2Pot = A0;
int greenLed = 30;
int redLed = 31;
int resolution = 41.47;
unsigned long time1, time2;

int reading;

volatile float encoderPos;

void setup() {
    pinMode(2, INPUT);
    attachInterrupt(digitalPinToInterrupt(EncoderA), doEncoderA, RISING);
    pinMode(3, INPUT);
    attachInterrupt(digitalPinToInterrupt(EncoderB), doEncoderB, RISING);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(30, OUTPUT);
    pinMode(31, OUTPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);
    pinMode(18, INPUT);
    attachInterrupt(digitalPinToInterrupt(18), RFID, CHANGE);
    pinMode(19, INPUT);
    pinMode(53, OUTPUT);

    SPI.begin();
    mfrc522.PCD_Init();

    Serial.begin(9600);
}

void loop() {
    // receive data
    digitalWrite(53, HIGH);
    while(Serial.available()==0) {
        Serial.println("<Arduino is ready>");
        delay(1000);
    }
    digitalWrite(53, LOW);
    String message="";
    message = Serial.readString();
    Serial.println(message);
    String opCodeStr, azimuthStr, altitudeStr;
    for(int i=0; i<=2; i++) {
        opCodeStr = opCodeStr + message[i];
    }
    for(int i=3; i<=5; i++) {
        azimuthStr = azimuthStr + message[i];
    }
    for(int i=6; i<=8; i++) {
        altitudeStr = altitudeStr + message[i];
    }
    Serial.println(opCodeStr);
    Serial.println(azimuthStr);
    Serial.println(altitudeStr);
    Serial.println(message);
    
    int opCode = opCodeStr.toInt();
    int azimuth = azimuthStr.toInt();
    int altitude = altitudeStr.toInt();
;
    if (opCode == 110) {
        while(encoderPos > 0) {
            CCW();
        }
        stopAll();
    }

    if (opCode == 120) {
        azimuth = azimuth*resolution;
        while(encoderPos < azimuth) {
            CW();
        }
        stopAll();
        delay(1000);
        altitude = 90-altitude;
        Serial.println(altitude);
        reading = analogRead(M2Pot);
        altitude = map(altitude, 10, 70, 60, 980);
        Serial.println("Altitude mapped:");
        Serial.println(altitude);
        delay(1000);
        time1 = millis();
        while(reading < altitude) {
            extend();
            reading = analogRead(M2Pot);
            time2 = millis();
            if(time2-time1>10000) {
                break;
            }
        }
        stopAll();
        while(reading > altitude) {
            retract();
            reading = analogRead(M2Pot);
            time2 = millis();
            if(time2-time1>10000) {
                break;
            }
        }
        stopAll();
    }

   delay(1000);
   Serial.print(opCodeStr);Serial.print(" ");
   Serial.print(azimuthStr);Serial.print(" ");
   Serial.println(altitudeStr);
   Serial.println("<Return>");
    
}

// FUNCTIONS
void CCW() {
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
}
void CW() {
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);

}
void extend() {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
}
void retract() {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
}
void stopAll() {
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
}
void doEncoderA() {
    encoderPos += (digitalRead(EncoderA)==digitalRead(EncoderB))?0:1;
}
void doEncoderB() {
    encoderPos += (digitalRead(EncoderA)==digitalRead(EncoderB))?0:-1;
}
void RFID() {
    for(int i=0; i<5; i++) {
        digitalWrite(greenLed, HIGH);
        digitalWrite(redLed, LOW);
        delay(50);
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
        delay(50);
    }
    bool state1, state2;
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
    if (!mfrc522.PICC_ReadCardSerial()) {
        return;
    }
    Serial.print("UID tag: ");
    String content = "";
    byte letter;
    for (byte i=0; i<mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0":"");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
        content.concat(String(mfrc522.uid.uidByte[i], HEX)); 
    }
    Serial.println();
    Serial.println("Message: ");
    content.toUpperCase();
    Serial.println(content);
    if (content == "125C5D42" | content == "A2FAA342") {
        for(int i=0; i<3; i++) {
            digitalWrite(greenLed, HIGH);
            delay(50);
            digitalWrite(greenLed, LOW);
            delay(50);
        }
        while(1) {
            state1 = digitalRead(32);
            state2 = digitalRead(33);
            while(state1 == 1 && state2 == 0) {
                CW();
                digitalWrite(greenLed, HIGH);
                digitalWrite(redLed, LOW);
                state1 = digitalRead(32);
                state2 = digitalRead(33);
            }
            stopAll();
            while(state1 == 0 && state2 == 1) {
                CCW();
                digitalWrite(greenLed, LOW);
                digitalWrite(redLed, HIGH);
                state1 = digitalRead(32);
                state2 = digitalRead(33);
            }
            digitalWrite(greenLed, LOW);
            digitalWrite(redLed, LOW);
            stopAll();
            if(digitalRead(32) == 1 && digitalRead(33) == 1) {
                for (int i=0; i<20; i++) {
                    digitalWrite(greenLed, HIGH);
                    digitalWrite(redLed, LOW);
                    delay(50);
                    digitalWrite(greenLed, LOW);
                    digitalWrite(redLed, HIGH);
                    delay(50);
                    digitalWrite(greenLed, LOW);
                    digitalWrite(redLed, LOW);
                }
                delay(1000);
                encoderPos = 0;
                break;
            }
        }
    }
    

}
