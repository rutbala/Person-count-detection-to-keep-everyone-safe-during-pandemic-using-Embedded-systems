#include <LiquidCrystal.h>

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int entrySensor = 2; // IR sensor for entry
const int exitSensor = 3;  // IR sensor for exit
const int buzzer = 4;      // Buzzer pin

int maxPeople = 10;        // Maximum allowed people
int currentCount = 0;      // Current number of people inside

void setup() {
  lcd.begin(16, 2);        // Set up the LCD's number of columns and rows
  pinMode(entrySensor, INPUT);
  pinMode(exitSensor, INPUT);
  pinMode(buzzer, OUTPUT);
  
  lcd.print("People Count: ");
  lcd.setCursor(0, 1);
  lcd.print(currentCount);
}

void loop() {
  int entryState = digitalRead(entrySensor);
  int exitState = digitalRead(exitSensor);

  // Debouncing the IR sensor signals to avoid multiple counts
  delay(200);  // Short delay to debounce

  // Check if someone enters
  if (entryState == HIGH && currentCount < maxPeople) {
    currentCount++;
    updateDisplay();
    if (currentCount >= maxPeople) {
      triggerBuzzer();
      lcd.clear();          // Clear the display
      lcd.setCursor(0, 0);
      lcd.print("Max Limit Reached");
    }
  }

  // Check if someone exits
  if (exitState == HIGH && currentCount > 0) {
    currentCount--;
    updateDisplay();
  }

  // Reset buzzer if count goes below maxPeople
  if (currentCount < maxPeople) {
    digitalWrite(buzzer, LOW);  // Turn off the buzzer
  }
}

void updateDisplay() {
  lcd.clear();               // Clear the previous display
  lcd.setCursor(0, 0);
  lcd.print("People Count: ");
  lcd.setCursor(0, 1);
  lcd.print(currentCount);
}

void triggerBuzzer() {
  for (int i = 0; i < 5; i++) { // Beep 5 times
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
  }
}
