#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           
#define SS_PIN          10         

MFRC522 mfrc522(SS_PIN, RST_PIN);  
const int buzzer = 7;

String IDs[5] = {"Thang","Ngoc","Minh","Thu","Nghia"};
int index = 0;
int tags = 5;


void setup() {
  pinMode(buzzer, OUTPUT);
  
  Serial.begin(9600);        
  SPI.begin();               
  mfrc522.PCD_Init();        
  Serial.println(F("Write personal data on a MIFARE PICC "));
}

void loop() {  
  if(tags > 0){
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
  
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    card_info();
    MFRC522::StatusCode status;
    MFRC522::MIFARE_Key key;
    for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
    
    byte block = 4;
    
    if (get_authenticate(status, key, block) == 0) return;    

    byte len = 16;
    byte buffer[len]; 
    preprocess(buffer, len);

    Serial.println();

    write_info(status, block, buffer, len);
    
    Serial.print("Card ID: ");
    Serial.print(IDs[index]);
  
    Serial.println(" ");
    mfrc522.PICC_HaltA(); // Halt PICC
    mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD

    index++;
    --tags;
  }
}

void card_info(){
  Serial.println();
  Serial.print(F("Card UID:"));    //Dump UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }

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

void preprocess(byte buffer[16], byte len){
  String temp = (IDs[index]);
  for(int i = 0; i < len; ++i) 
    buffer[i] = 0;
    
  for(int i = 0; i < temp.length(); ++i)
    buffer[i] = temp[i];
  buffer[temp.length()] = '*';
}

void write_info(MFRC522::StatusCode status, byte block, byte buffer[16], byte len){
  status = mfrc522.MIFARE_Write(block, buffer, len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("MIFARE_Write() failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }
  else{
    Serial.println(F("MIFARE_Write() success "));
    tone(buzzer, 3136, 250);
  }
}
