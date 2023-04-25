#include <Bounce2.h>
#include <Tone.h>

/*ima 3 tipke, s jednom tipkom odnosno glavnom tipkom prilikom pritiska 
krece pjesma na kamionskoj trubi. cim se pusti pjesma prestaje i svakim novim pritiskom pjesma krece ispocetka. 
Preostale dvije tipke trebaju mijenjati odabir pjesme lijeva i desna. pjesme su u notama 
*/


/*"There are 3 buttons. Pressing the main button starts playing a song on a truck horn. 
As soon as the button is released, the song stops, and with each new press, 
the song starts over. The other two buttons 
should change the song selection left and right. The songs are in musical notes."

*/


// Define pins
const int mainButtonPin = 2;
const int leftButtonPin = 3;
const int rightButtonPin = 4;

// 5 examples and some random shitty notes that can be replaced with pre-made songs 
// git on which somebody already made some popular songs https://github.com/robsoncouto/arduino-songs 
const int tune1[] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
const int tune2[] = { NOTE_F3, NOTE_F3, NOTE_C4, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_G3, 0 };
const int tune3[] = { NOTE_A3, NOTE_A3, NOTE_A3, NOTE_G3, NOTE_A3, NOTE_C4, NOTE_B3, 0 };
const int tune4[] = { NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3, 0, NOTE_D3, NOTE_E3, 0 };
const int tune5[] = { NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B3, NOTE_A3, 0 };

// Define debouncing 
Bounce mainButton = Bounce();
Bounce leftButton = Bounce();
Bounce rightButton = Bounce();

// Define variables for tracking button state and current tune
bool mainButtonPressed = false;
int currentTune = 1;

void setup() {
  // Set up button pins as inputs and enable internal pull-up resistors
  pinMode(mainButtonPin, INPUT_PULLUP);
  pinMode(leftButtonPin, INPUT_PULLUP);
  pinMode(rightButtonPin, INPUT_PULLUP);

  // Initialize button debouncing objects
  mainButton.attach(mainButtonPin, INPUT_PULLUP);
  mainButton.interval(25);
  leftButton.attach(leftButtonPin, INPUT_PULLUP);
  leftButton.interval(25);
  rightButton.attach(rightButtonPin, INPUT_PULLUP);
  rightButton.interval(25);

  // Set up serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Update button states
  mainButton.update();
  leftButton.update();
  rightButton.update();

  // Check if the main button is pressed and start playing the current tune
  if (mainButton.fell()) {
    mainButtonPressed = true;
    playTune(currentTune);
  }

  // Check if the main button is released and stop playing the current tune
  if (mainButton.rose() && mainButtonPressed) {
    noTone(9);
    mainButtonPressed = false;
  }

  // Check if the left button is pressed and select the previous tune
  if (leftButton.fell()) {
    currentTune--;
    if (currentTune < 1) {
      currentTune = 5;
    }
    Serial.print("Selected tune ");
    Serial.println(currentTune);
  }

  // Check if the right button is pressed and select the next tune
  if (rightButton.fell()) {
    currentTune++;
    if (currentTune > 5) {
      currentTune = 1;
    }
    Serial.print("Selected tune ");
    Serial.println(currentTune);
  }
}

void playTune(int tune) {
  int *notes;
  int numNotes;
  
  // Select the appropriate tune based on the input
  switch (tune) {
    case 1:
      notes = (int*)tune1;
      numNotes = 8;
      break;
   
