#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10          
const int buzzer = 7;


MFRC522 mfrc522(SS_PIN, RST_PIN);   
//*****************************************************************************************//
void setup() {
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);                                           
  SPI.begin();                                                  
  mfrc522.PCD_Init();                                              
  Serial.println("CLEARDATA");
  Serial.println("LABEL,CLOCK,ID");
}

void loop(){
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  byte block = 4;
  byte len = 18;
  byte buffer1[18];
  
  MFRC522::StatusCode status;
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  if (get_authenticate(status, key, block) == 0) return; 

  if (read_ID(status, block, buffer1, len) == 0) return;
  
  Serial.print("DATA,TIME,");
  String ID = get_ID(buffer1);
  Serial.print(ID);
  Serial.println();
  
  tone(buzzer, 3136, 250);

  delay(1000); //change value if you want to read cards faster
  
  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD
}

bool get_authenticate(MFRC522::StatusCode status, MFRC522::MIFARE_Key key, byte block){
    
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("PCD_Authenticate() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 0;
  }
  else 
  {
    Serial.println(F("PCD_Authenticate() success "));
    return 1;
  }
}

bool read_ID(MFRC522::StatusCode status, byte block, byte buffer1[18], byte len){
  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 0;
  }
  return 1;
}

String get_ID(byte buffer1[18]){
  String ID = "";
  for (int i = 0; i < 16; i++)
    if((char)buffer1[i] == '*') break;
      else ID = ID + (char)buffer1[i];
  return ID;
}
