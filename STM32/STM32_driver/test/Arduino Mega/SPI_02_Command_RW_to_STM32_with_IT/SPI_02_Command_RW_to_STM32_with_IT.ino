#include <SPI.h>
#include<stdint.h>

#define SPI_SCK 52
#define SPI_MISO 50
#define SPI_MOSI 51
#define SPI_SS 53


char dataBuff[500];

//Initialize SPI slave.
void SPI_SlaveInit(void) 
{ 
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);

  // Enable SPI as slave.
  SPCR = (1 << SPE);
}



//This function returns SPDR Contents 
uint8_t SPI_SlaveReceive(void){
  /* Wait for reception complete */
  while(!(SPSR & (1<<SPIF)));
  /* Return Data Register */
  return SPDR;
}

//sends one byte of data 
void SPI_SlaveTransmit(char data){
  /* Start transmission */
  SPDR = data;
  
  /* Wait for transmission complete */
  while(!(SPSR & (1<<SPIF)));
}


void setup() 
{
  // Initialize serial communication 
  Serial.begin(2000000);
  
  // Initialize SPI Slave.
  SPI_SlaveInit();
  
  Serial.println("Slave Initialized");
}

void loop() 
{

  char str[] = "Ciao io sono Arduino Mega e sono in grado di leggere da SPI\n";
  char read_str[50];
  uint8_t str_size = sizeof(str);
  uint8_t  i;
  uint16_t val = 0; 
  uint32_t op1 = 0;
  

   //Read OpCode
   val = SPI_SlaveReceive();
   
   if(val == 0x1C ){ //Read String from STM32
      //Read arg0
      val = SPI_SlaveReceive();

      //Read arg1
      for(i=0; i<val; i++){
        read_str[i] = SPI_SlaveReceive();
      }
      
      Serial.print(read_str);
   }
   else if(val == 0x1D ){ //Read uint32_t value from STM32
    
      //Read arg0
      val = SPI_SlaveReceive();
      
      //Read arg1
      for(i=0; i<val; i++)
        op1 |= ((uint32_t)SPI_SlaveReceive() << i*8);
  
      Serial.println(op1);
   }
   else if(val == 0x1E ){ //Send String to STM32

      //Send string size
      SPI_SlaveTransmit(str_size);

      //Send string
      for(i=0; i<str_size; i++)
        SPI_SlaveTransmit(str[i]);
  
      //Discard last received byte on RXFIFO
      SPI_SlaveReceive();
      
      Serial.print("Comando 3\n");  
   }
}

