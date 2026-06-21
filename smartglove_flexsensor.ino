#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// FLEX SENSORS
int flexPins[4] = {A0, A1, A2, A3};
int threshold = 5; 

// MODE DETECTOR
bool isWordMode = true;

// DATA
String lastMessage = "";
String sentence = "";
int previousCode = -1;

// WORD MODE 
String words[16] = {
  "", "Help", "Chest pain", "Can't breath",
  "back pain", "Fever", "Doctor", "Rash"
  "Diarrhea", "Cough", "Headache", "vomiting",
  "insomia", "bleeding", "Urgency", "Weakness"
};

// LETTER MODE
String letters[16] = {
  "", "A", "B", "C",
  "D", "E", "F", "G",
  "H", "I", "J", "K",
  "L", "M", "N", "O"
};

// GET GESTURE
int getGestureID() {
  int mask = 0;

  for (int i = 0; i < 4; i++) {
    int value = analogRead(flexPins[i]);

    if (value < threshold) {
      mask |= (1 << i);
    }
  }

  return mask;
}

void setup() {
  Serial.begin(9600); 

  lcd.init();
  lcd.backlight();

  lcd.print("Smart Glove");
  delay(1500);
  lcd.clear();
}

void loop() {
  int code = getGestureID();

  // Count bent fingers
  int bentCount = 0;
  for (int i = 0; i < 4; i++) {
    if (analogRead(flexPins[i]) < threshold) {
      bentCount++;
    }
  }

  //  MODE TOGGLE 
  if (bentCount == 4) {
    isWordMode = !isWordMode;

    lcd.clear();
    lcd.setCursor(0, 0);

    if (isWordMode) {
      lcd.print("Word Mode");
      Serial.println("Word Mode");
    } else {
      lcd.print("Letter Mode");
      Serial.println("Letter Mode");
      sentence = "";
    }

    delay(1000);
    previousCode = -1;
    lastMessage = "";
    return;
  }

  // WORD MODE
  if (isWordMode) {
    String message = words[code];

    if (message != lastMessage) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(message);

      if (message != "") {
        Serial.println(message); 
      }

      lastMessage = message;
    }
  }

  // LETTER MODE 
  else {
    if (code != 0 && code != previousCode) {

      if (code == 1) {
        sentence += " ";
      }
      else if (code == 2) {
        sentence = "";
        lcd.clear();
        Serial.println("Cleared");
        previousCode = code;
        delay(300);
        return;
      }
      else {
        sentence += letters[code];
      }

      // Display on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(sentence.substring(0, 16));

      if (sentence.length() > 16) {
        lcd.setCursor(0, 1);
        lcd.print(sentence.substring(16, 32));
      }

      // PRINT FULL SENTENCE
      Serial.println(sentence);
    }
  }

  previousCode = code;
  delay(150);
}