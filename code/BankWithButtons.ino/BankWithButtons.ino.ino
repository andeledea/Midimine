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
BankSelector bankSelector(bank, { 2, 3 }, { 
  7, 8, 9
});

/* Alternatively, you could use arrays for the pin numbers:

   const pin_t buttonPins[] = { 2, 3 };
   const pin_t ledPins[] = { 
     ShiftReg.pin(0), 
     ShiftReg.pin(1), 
     ShiftReg.pin(2), 
     ShiftReg.pin(3), 
     ShiftReg.pin(4), 
     ShiftReg.pin(5), 
     ShiftReg.pin(6), 
     ShiftReg.pin(7)
   };

   BankSelector bankSelector(bank, buttonPins, ledPins);
*/

/*_______________________________________________________________________________________________________________________________________*/

void setup() {
  // Add the potentiometer control object to the bank
  bank.add(potentiometer, Bank::CHANGE_CHANNEL); // When the bank setting is changed, change the channel of the potentiometer
}

/*_______________________________________________________________________________________________________________________________________*/

void loop() {
  // Refresh the MIDI controller (check whether the inputs have changed since last time, if so, send the new value over MIDI)
  // It also refreshes the bank selector
  MIDI_Controller.refresh();
}
