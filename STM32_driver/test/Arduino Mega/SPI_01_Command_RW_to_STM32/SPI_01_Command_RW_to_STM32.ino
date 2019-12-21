#include <SPI.h>
#include<stdint.h>

#define SPI_SCK 52
#define SPI_MISO 50
#define SPI_MOSI 51
#define SPI_SS 53

#define SPI_DATASIZE_8
//#define SPI_DATASIZE_16

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

#ifdef SPI_DATASIZE_8

  //This function returns SPDR Contents 
  uint8_t SPI_SlaveReceive(void){
    uint8_t data = 0;
    /* Wait for reception complete */
    while(!(SPSR & (1<<SPIF)));
    data = SPDR;
    /* Return Data Register */
    return data;
  }
  
  //sends one byte of data 
  void SPI_SlaveTransmit(char data){
    /* Start transmission */
    SPDR = data;
    
    /* Wait for transmission complete */
    while(!(SPSR & (1<<SPIF)));
  }

#else
  #ifdef SPI_DATASIZE_16
    //This function returns SPDR Contents 
    uint16_t SPI_SlaveReceive(void){
      
      uint16_t data = 0;
      /* Wait for reception complete */
      while(!(SPSR & (1<<SPIF)));
      data = SPDR;
      while(!(SPSR & (1<<SPIF)));
      data |= (SPDR << 8);
      /* Return Data Register */
      return data;
      
    }
    
    //sends one byte of data 
    void SPI_SlaveTransmit(char data){
      /* Start transmission */
      SPDR = data;
      /* Wait for transmission complete */
      while(!(SPSR & (1<<SPIF)));

      SPDR = 0;
      /* Wait for transmission complete */
      while(!(SPSR & (1<<SPIF)));
      
    }
  #endif
#endif


void setup() 
{
  // Initialize serial communication 
  Serial.begin(115200);
  
  // Initialize SPI Slave.
  SPI_SlaveInit();
  
  Serial.println("Slave Initialized");
}

void loop() 
{

  char str[] = "Ciao io sono Arduino Mega\n";
  uint8_t str_size = sizeof(str);
  uint8_t  i;
  uint16_t val = 0; 
  uint32_t op1 = 0;

  //Serial.println(SPI_SlaveReceive());

   val = SPI_SlaveReceive();
   if(val == 0x1C ){
      val = SPI_SlaveReceive();
      for(i=0; i<val; i++)
        Serial.print((char)SPI_SlaveReceive());
   }
   else if(val == 0x1D ){
      op1  = SPI_SlaveReceive();
      op1 |= (SPI_SlaveReceive() << 8);
      op1 |= ((uint32_t)SPI_SlaveReceive() << 16);
      op1 |= ((uint32_t)SPI_SlaveReceive() << 24);
      Serial.println(op1);
   }
   else if(val == 0x1E ){
      SPI_SlaveTransmit(str_size);
      for(i=0; i<str_size; i++)
        SPI_SlaveTransmit(str[i]);

      //Clear RXFIFO
      SPI_SlaveReceive();
      
      Serial.print("Comando 3\n");  
   }
}

