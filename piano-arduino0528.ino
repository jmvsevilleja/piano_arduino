#include <MIDI.h>  // Add Midi Library
#include <Adafruit_NeoPixel.h> // Add Led Library

//define NeoPixel Pin and Number of LEDs
#define PIN 13
#define NUM_LEDS 61

//create a NeoPixel strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

//Create an instance of the library with default name, serial port and settings
MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
 
  strip.begin(); // start the strip and blank it out
  strip.show();
 
  MIDI.begin(1); // Initialize the Midi Library on channel 1
  Serial.begin(256000);  // Hairless MIDI speed

  MIDI.setHandleNoteOn(MyHandleNoteOn); // This is important!! This command
  // tells the Midi Library which function you want to call when a NOTE ON command
  // is received. In this case it's "MyHandleNoteOn".
  MIDI.setHandleNoteOff(MyHandleNoteOff); // This command tells the Midi Library
  // to call "MyHandleNoteOff" when a NOTE OFF command is received.
}

void loop() { // Main loop
  MIDI.read(); // Continuously check if Midi data has been received.   
}

// MyHandleNoteOn/Off are the functions that will be called by the Midi Library
// when a MIDI Note message is received.
// It will be passed bytes for Channel, Pitch, and Value
// It checks if the MIDI Note Pitch is within the Note Range 36 (C1) to 51 (D#2)
// If it is, it lights up the corresponding LED (LEDs 1 thru 16)
void MyHandleNoteOn(byte channel, byte pitch, byte velocity) {
    int velo = (velocity/50)+1;
    
    int RandomColor[6][3] = {
      {1,1,0},
      {1,0,1},
      {0,1,1},
      {1,0,0},
      {0,1,0},
      {0,0,1},
    };
    
    int Random = random(0,5);
    
    int Red = (random(1, 15)*velo)*RandomColor[Random][0]; 
    int Green = (random(1, 15)*velo)*RandomColor[Random][1];
    int Blue = (random(1,15)*velo)*RandomColor[Random][2]; 
   
    strip.setPixelColor(96 - pitch, Red, Green, Blue);
    strip.show();

  }

void MyHandleNoteOff(byte channel, byte pitch, byte velocity) {
      strip.setPixelColor(96 - pitch, 0, 0, 0);
      strip.show();
  }
