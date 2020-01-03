// Wire Slave Transmitter and receiver
//Uno, Ethernet 20 (SDA), 21 (SCL)
#include <Wire.h>

uint8_t active_command = 0xff,led_status=0;
char name_msg[] = "Ciao sono arduino Mega\n";

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
void requestEvent() {

  if(active_command == 0X51)
  {
    uint8_t len = get_len_of_data();
    Wire.write(&len,1);
    active_command = 0xff;
    Serial.println("0x51 received");
  }

  if(active_command == 0x52)
  {
    uint8_t len = get_len_of_data();
    Wire.write(name_msg,len);
      
    active_command = 0xff;
    Serial.println("0x52 received");
  }

}
void loop() {
  

}
