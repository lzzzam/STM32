// Wire Master Transmitter and Receiver 
//Uno, Ethernet 20 (SDA), 21 (SCL)
#include <Wire.h>

uint8_t rcv_buf[32];

int data_len=0;
#define SLAVE_ADDR 0x69

void setup() {
  
  Serial.begin(9600);
  Serial.println("Arduino Master");
  Serial.println("Send character:\n -\"s\" to receive string\n -\"t\" to toggle STM32 LED");
  Serial.println("-----------------------------");
  
  // join i2c bus (address optional for master)
  Wire.begin();  
}


void loop() {

  while(!Serial.available());
  char in_read=Serial.read();
  
  if(in_read == 's')
  {
    data_len = 0;
    for(int i=0; i<32; i++)
      rcv_buf[i] = 0;
    
    Serial.println("****************************************");
    Serial.println("command: s");
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0X51); //Send this command to read the length
    Wire.endTransmission();
    Wire.requestFrom(SLAVE_ADDR,1); // Request from Slave 1 byte
  
    if(Wire.available())
      data_len = Wire.read(); // Reads the data 
    
    Serial.print("Data Length ==>");
    Serial.println(String(data_len,DEC));
  
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0X52); //Send this command to ask for string
    Wire.endTransmission();
    Wire.requestFrom(SLAVE_ADDR,data_len);// Request from Slave "data_len" bytes
  
    uint32_t i=0;
    for( i =0; i <= data_len ; i++)
    {
      if(Wire.available())
        rcv_buf[i] = Wire.read(); // Reads the data 
    }

    rcv_buf[i] = '\0';

    Serial.print("Received string ==> ");
    Serial.println((char*)rcv_buf);
  }
  else if(in_read == 't')
  {
    Serial.println("****************************************");
    Serial.println("command: t");
    Serial.println("Toogle LED");
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(0X53); //Send this command to toogle STM32 LED
    Wire.endTransmission();
  }
}
