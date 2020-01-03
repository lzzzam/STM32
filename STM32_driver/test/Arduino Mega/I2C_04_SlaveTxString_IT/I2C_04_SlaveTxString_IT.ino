// Wire Slave Transmitter and receiver
//Uno, Ethernet 20 (SDA), 21 (SCL)
#include <Wire.h>

uint8_t active_command = 0xff,led_status=0;
char name_msg[32] = "Ciao sono arduino Mega\n";

#define SLAVE_ADDR 0x68

uint8_t get_len_of_data(void)
{
  return (uint8_t)strlen(name_msg);
}
void setup() {
  // Start the I2C Bus as Slave on address 9
  Wire.begin(SLAVE_ADDR); 
  
  // Attach a function to trigger when something is received.
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);


  Serial.begin(9600);
}


//write
void receiveEvent(int bytes) {
  active_command = Wire.read();    // read one character from the I2C 
}

//read
void requestEvent() 
{
  Serial.println("Request Received");
  Wire.write(name_msg,get_len_of_data());
  active_command = 0xff;
}
void loop() {
  

}
