#include<Wire.h> // Include the Wire library for I2C communication
#include<LiquidCrystal_I2C.h> // Include the LiquidCrystal_I2C library for I2C LCD

LiquidCrystal_I2C lcd_1(0x27, 16, 2); // Create an instance of the LiquidCrystal_I2C class with the LCD address and size

int seconds = 30; // Variable to store the number of seconds
bool countdownStarted = false; // Flag to indicate if the countdown has started
bool restartRequested = false; // Flag to indicate if a restart is requested

void setup() {
  lcd_1.init(); // Initialize the LCD
  lcd_1.backlight(); // Turn on the backlight
  pinMode(3, OUTPUT); // Set pin 1 as an output
  pinMode(2, INPUT); // Set pin 2 as an input
  pinMode(5, OUTPUT); // Set pin 5 as an output
  pinMode(9, OUTPUT); // Set pin 9 as an output
  pinMode(10, OUTPUT); // Set pin 10 as an output
  pinMode(6, OUTPUT); // Set pin 6 as an output
  Serial.begin(9600); // Initialize the serial communication
}

// Notes for sound effect at each second
#define NOTE_C4  261
#define NOTE_E4  329

// Duration of each note for sound effect at each second
#define NOTE_DURATION_PER_SECOND 200


// Notes for victory song
float NOTE_G3 = 196.00;
float NOTE_GB3 = 207.65;
float NOTE_AB3 = 233.08;
float NOTE_C = 261.63;
float NOTE_D = 293.67;
float NOTE_DB = 311.13;
float NOTE_E = 329.63;
float NOTE_F = 349.23;
float NOTE_G = 392.00;
float NOTE_GB = 415.31;
float NOTE_AB = 440.00;
float NOTE_C5 = 523.25;
float NOTE_D5 = 587.33;
float NOTE_DB5 = 622.25;
float NOTE_E5 = 659.26;
float NOTE_G5 = 783.99;
float NOTE_GB5 = 830.61;
float NOTE_AB5 = 932.33;
float NOTE_C6 = 1046.5;


// Melody sequence
float victory_melody[] = {NOTE_G3, NOTE_C, NOTE_E, NOTE_G, NOTE_C5, NOTE_E5, NOTE_G5, NOTE_E5,
                  NOTE_GB3, NOTE_C, NOTE_DB, NOTE_GB, NOTE_C5, NOTE_DB5, NOTE_GB5, NOTE_DB5,
                  NOTE_AB3, NOTE_D, NOTE_F, NOTE_AB, NOTE_D5, NOTE_AB5, NOTE_AB5, NOTE_AB5, NOTE_AB5, NOTE_C6};

// Durations of each note in victory song
int duration[] = {200, 200, 200, 200, 200, 200, 500, 500,
                  200, 200, 200, 200, 200, 200, 500, 500,
                  200, 200, 200, 200, 200, 500, 200, 200, 200, 1000};


void loop() {
  if (restartRequested) {
    restartProgram(); // Restart the program if restart is requested
  }

  if (digitalRead(2) == HIGH && !countdownStarted) { // If the sensor picks up movement and the countdown has not started
    countdownStarted = true; // Start the countdown
    lcd_1.print("Wash your hands!"); // Display a message on the LCD
    Serial.println("MOTION DETECTED"); // Print a message to the serial monitor
  }
  
  if (countdownStarted && seconds >= 0 && seconds != 20 && seconds != 15 && seconds != 5) { // For each second in the coundown as long as its not a checkpoint second
    analogWrite(5, 10); // Turn the red LED on
    lcd_1.setBacklight(1); // Turn the backlight on
    lcd_1.setCursor(7, 1); //Print the secconds on the second row, 7th cololum
    lcd_1.print(seconds);
    delay(1000); // Delay the below sound effect for 1 second
    tone(6, NOTE_C4, NOTE_DURATION_PER_SECOND); // Play the sound effect
    delay(NOTE_DURATION_PER_SECOND);
    tone(6, NOTE_E4, NOTE_DURATION_PER_SECOND);
    delay(NOTE_DURATION_PER_SECOND);
    noTone(6); // Turn off the buzzer
    seconds--; // Decrease the seconds for the next illeration
    lcd_1.setCursor(0,1); // Clear the seconds
    lcd_1.print("                   ");
  }
  
  if (seconds == 20) { // At 20 seconds (the first checkpoint)
    analogWrite(5, 10); // Turn the red LED on
    analogWrite(9, 10);  // Turn the yellow LED on
    lcd_1.setBacklight(1); // Turn the LCD backlight on
    lcd_1.clear(); // Completely clear the LCD (get rid of the "Wash your hands!" message)
    lcd_1.setCursor(2, 0); // Change the message
    lcd_1.print("Almost There!"); 
    lcd_1.setCursor(7, 1); // Then print the seconds
    lcd_1.print(seconds);
    delay(1000); // Delay for 1 second
    tone(6, NOTE_C4, NOTE_DURATION_PER_SECOND); // And then play the sound effect
    delay(NOTE_DURATION_PER_SECOND);
    tone(6, NOTE_E4, NOTE_DURATION_PER_SECOND);
    delay(NOTE_DURATION_PER_SECOND);
    noTone(6); // Turn the buzzer off
    seconds--; // Decrease the seconds for the next itteration 
    lcd_1.clear(); // Clear the LCD
    lcd_1.print("Wash your hands!"); // And go back to the "Wash your hands!" message
  }
  
  if (seconds == 15) { // At 15 seconds (the second checkpoint)
    analogWrite(5, 10); // Turn the red LED on
    analogWrite(10, 40); // Turn the green LED on
    lcd_1.setBacklight(1); // Turn the LCD backlight on
    lcd_1.clear(); // Clear the LCD
    lcd_1.setCursor(1, 0); // Print the new checkpoint message
    lcd_1.print("Getting Closer!"); 
    lcd_1.setCursor(7, 1); // Print the seconds on the LCD
    lcd_1.print(seconds); 
    delay(1000); // Delay for 1 second
    tone(6, NOTE_C4, NOTE_DURATION_PER_SECOND); // Play the sound effect
    delay(NOTE_DURATION_PER_SECOND);
    tone(6, NOTE_E4, NOTE_DURATION_PER_SECOND);
    delay(NOTE_DURATION_PER_SECOND);
    noTone(6); // Turn the buzzer on
    seconds--; // Decrease the seconds for the next itteraiton
    lcd_1.clear(); // Clear the LCD
    lcd_1.print("Wash your hands!"); // And go back to the "Wash your hands!" message
  }


  if (seconds == 5) { // At 5 seconds (the second checkpoint)
    analogWrite(5, 10); // Turn the red LED on
    digitalWrite(3, HIGH); // Turn the blue LED on
    lcd_1.setBacklight(1); // Turn the LCD backlight on
    lcd_1.clear(); // Clear the LCD
    lcd_1.setCursor(2, 0); // Print the new checkpoint message
    lcd_1.print("Little More!"); 
    lcd_1.setCursor(7, 1); // Print the seconds on the LCD
    lcd_1.print(seconds); 
    delay(1000); // Delay for 1 second
    tone(6, NOTE_C4, NOTE_DURATION_PER_SECOND); // Play the sound effect
    delay(NOTE_DURATION_PER_SECOND);
    tone(6, NOTE_E4, NOTE_DURATION_PER_SECOND);
    delay(NOTE_DURATION_PER_SECOND);
    noTone(6); // Turn the buzzer on
    seconds--; // Decrease the seconds for the next itteraiton
    lcd_1.clear(); // Clear the LCD
    lcd_1.print("Wash your hands!"); // And go back to the "Wash your hands!" message
  }

  
  if (seconds < 0) { // At the end of the coundown
    countdownStarted = false; // Set the countdown to false (ready for the next use)
    digitalWrite(5, LOW); // Turn all the LEDs off
    digitalWrite(3, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    lcd_1.clear(); // Clear the LCD
    for (int note = 0; note < 28; note++) { // Play the victory note, one note at a time
      tone(6, victory_melody[note]); // This plays the note to the buzzer (pin 6) and takes each note from the victory method list I made before
      delay(duration[note]); // The delay works the same way as above: it takes the duration length in the duration list I made before
      noTone(6); // And then turn the buzzer off, these three steps get repeated for each note
    }
    lcd_1.setCursor(2, 0); // Print the "You're Done!" message
    lcd_1.print("You're Done!");
    delay(800); // Keep it on screen for 0.8 seconds
    restartRequested = true; // And set the restartRequested to true, so next time this void loop runs, it goes to the void restartProgram function
  }
}

void restartProgram() { // Once its time to restart the program for the next use
  seconds = 30; // Set the seconds back to 30
  countdownStarted = false; // Set the countdown to false
  restartRequested = false; // Set the restart requested to false
  lcd_1.clear(); // Clear the LCD
  lcd_1.setBacklight(1); // And turn the LCD baclight on
}