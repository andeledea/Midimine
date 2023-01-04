/*
  This is an example of the "Bank" class of the MIDI_controller library.
  Connect a potentiometer to analog pins A0.

  Connect push buttons to pins 2 and 3, and a shift register to pins 10 (ST_CP), 11 (DS) and 13 (SH_CP).
  Connect LEDs (+ current limiting resistors) to the 8 outputs of the shift register.

  Pins 2 and 3 increment or decrement the bank setting, and the LEDs display the bank setting.
  
  This allows you to control multiple tracks with only a limited amount of physical potentiometers and buttons

  Map accordingly in your DAW or DJ software.

  Written by Pieter P, 08-09-2017
  https://github.com/tttapa/MIDI_controller
*/
#define ENCODER_USE_INTERRUPTS
#include <Encoder.h>
#include <MIDI_Controller.h> // Include the library

HairlessMIDI_Interface interface;
// Create a new instance of the class 'Analog', on pin A0,
// that sends MIDI messages with controller 7 (channel volume) on MIDI channel 1
Analog potentiometer(A0, MIDI_CC::Channel_Volume, 1);

// Create a new bank that has one track per bank
Bank bank(1);

// Create a new bank selector that changes the bank setting of the bank we just created
// It has pushbuttons connected to pins 2 and 3 that increment or decrement the bank setting,
// and 8 LEDs connected to the shift register, that display the current bank setting.
Encoder enc(2, 3);
BankSelector bankSelector(bank, &enc, { 
  7, 8, 9 
});

/*_______________________________________________________________________________________________________________________________________*/

void setup() {
  // Add the potentiometer control object to the bank
  bank.add(potentiometer, Bank::CHANGE_ADDRESS); // When the bank setting is changed, change the channel of the potentiometer
}

/*_______________________________________________________________________________________________________________________________________*/

void loop() {
  // Refresh the MIDI controller (check whether the inputs have changed since last time, if so, send the new value over MIDI)
  // It also refreshes the bank selector
  MIDI_Controller.refresh();
}
