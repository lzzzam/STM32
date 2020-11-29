#include <MIDI.h>

// Created and binds the MIDI interface to the default hardware Serial port
//MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  
  Serial.begin(31250);  // default midi speed rate 
  
  //MIDI.begin(2); 
}

int iAn0Val, iAn1Val, iAn2Val, iAn3Val, iAn4Val, iAn5Val;

void loop(){
  
   int iAn0ValPrev = iAn0Val; // previous value
   iAn0Val = analogRead(A0)/8; // Divide by 8 to get range of 0-127 for midi
   analogPinMidiTX(1,iAn0Val,iAn0ValPrev); //TX value 
  
}

void analogPinMidiTX(int iChan, int iVal, int iValPrev)
{  
  // TX Value only if it has changed
  if(iValPrev != iVal)
  {
    MidiTX(176,iChan,iVal); // 176 = CC command, 1 = Which Control, val = value read from Potentionmeter
  }
}

void MidiTX(unsigned char MESSAGE, unsigned char CONTROL, unsigned char VALUE) //Valeur en Midi Command
{
   Serial.write(MESSAGE);
   Serial.write(CONTROL);
   Serial.write(VALUE);
}
