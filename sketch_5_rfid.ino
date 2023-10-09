#include <MFRC522.h> //library responsible for communicating 
with the module RFID-RC522
#include <SPI.h> //library responsible for communicating of SPI 
bus
#define SS_PIN 21
#define RST_PIN 22
#define SIZE_BUFFER 18
#define MAX_SIZE_BLOCK 16
#define greenPin 12
#define redPin 32
//used in authentication
MFRC522::MIFARE_Key key;
//authentication return status code
MFRC522::StatusCode status;
// Defined pins to module RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() 
{
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
 
  // Init MFRC522
  mfrc522.PCD_Init(); 
  Serial.println("Approach your reader card...");
  Serial.println();
}

void loop() 
{
  // Aguarda a aproximacao do cartao
  //waiting the card approach
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select a card
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  // Dump debug info about the card; PICC_HaltA() is 
  automatically called
  // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));</p><p> //call 
  menu function and retrieve the desired option
  int op = menu();
  if(op == 0) 
    readingData();
  else if(op == 1) 
    writingData();
  else {
    Serial.println(F("Incorrect Option!"));
  return;
}
//instructs the PICC when in the ACTIVE state to go to a "STOP" 
state
 mfrc522.PICC_HaltA(); 
 // "stop" the encryption of the PCD, it must be called after 
communication with authentication, otherwise new communications 
can not be initiated
 mfrc522.PCD_StopCrypto1(); 

//reads data from card/tag
void readingData()
{
 //prints the technical details of the card/tag
 mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); 
 
 //prepare the key - all keys are set to FFFFFFFFFFFFh
 for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
 
 //buffer for read data
 byte buffer[SIZE_BUFFER] = {0};
 //the block to operate
 byte block = 1;
 byte size = SIZE_BUFFER;</p><p> //authenticates the block to 
operate
 status = 
mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, 
&key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
 if (status != MFRC522::STATUS_OK) {
 Serial.print(F("Authentication failed: "));
 Serial.println(mfrc522.GetStatusCodeName(status));
 digitalWrite(redPin, HIGH);
 delay(1000);
 digitalWrite(redPin, LOW);
 return;
 }
 //read data from block
 status = mfrc522.MIFARE_Read(block, buffer, &size);
 if (status != MFRC522::STATUS_OK) {
 Serial.print(F("Reading failed: "));
 Serial.println(mfrc522.GetStatusCodeName(status));
 digitalWrite(redPin, HIGH);
 delay(1000);
 digitalWrite(redPin, LOW);
 return;
 }
 else{
 digitalWrite(greenPin, HIGH);
 delay(1000);
 digitalWrite(greenPin, LOW);
 }
 Serial.print(F("\nData from block ["));
 Serial.print(block);Serial.print(F("]: "));
//prints read data
for (uint8_t i = 0; i < MAX_SIZE_BLOCK; i++)
 {
 Serial.write(buffer[i]);
 }
 Serial.println(" ");
}