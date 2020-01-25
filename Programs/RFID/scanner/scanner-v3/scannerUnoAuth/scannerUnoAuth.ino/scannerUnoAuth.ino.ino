/*

   All the resources for this project: https://randomnerdtutorials.com/
   Modified by Rui Santos

   Created by FILIPEFLOP

*/

#include <SPI.h>
#include <MFRC522.h>
#include <time.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
bool fresh = true;                  // Makes first ID the owner ID
String owner = "";

void setup()
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}
void loop()
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], DEC);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], DEC));
  }
  Serial.println();
  /*  First scan
      Saves scan as owner, changes fresh to false
  */
  if (fresh == true) {
    owner = content.substring(1);
    Serial.println("ID saved");
    fresh = false;
  }

  // not first scan
  else if (fresh == false) {
    /* if new scan is saved ID from first scan,
       grants access, resets owner string to "", and resets fresh to true
    */
    if (owner == content.substring(1)) {
      Serial.println("Authorization Granted");
      owner = "";
      fresh = true;
    }
    /*  if new scan is not saved ID from first scan,
        denies access and goes back to scanning for card
    */
    else if (owner != content.substring(1)) {
      Serial.println("Authorization Denied");
    }
  }
  /*  print separator line and delay to
      keep from repeatedly scanning the same
      ID over and over per second
  */
  Serial.println();
  delay(3000);
}
