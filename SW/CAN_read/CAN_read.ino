// ESP32-S3 DEVKit
// Library https://github.com/autowp/arduino-mcp2515

#include <SPI.h>
#include <mcp2515.h>

#define MOSI  11
#define MISO  13
#define SCK   12
#define CS    10

struct can_frame canMsg;
MCP2515 mcp2515(CS);

#define ON_PIN 47

void setup() {
  pinMode(ON_PIN, OUTPUT);
  digitalWrite(ON_PIN, HIGH);
  Serial.begin(115200);
  SPI.begin(SCK, MISO, MOSI);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  
  Serial.println("------- CAN Read ----------");
  Serial.println("ID  DLC   DATA");
}

void loop() {
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    Serial.print(canMsg.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(canMsg.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<canMsg.can_dlc; i++)  {  // print the data
      Serial.print(canMsg.data[i],HEX);
      Serial.print(" ");
    }

    Serial.println();      
  }
}
