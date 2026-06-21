#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ===== LCD I2C SETUP =====
LiquidCrystal_I2C lcd(0x27, 16, 2); // try 0x3F if needed

// ===== BUTTONS =====
int buttonPins[4] = {2, 3, 4, 5};

// ===== MODE =====
bool isWordMode = true;

// ===== DATA =====
String lastMessage = "";
String sentence = "";
String lastSentenceSent = "";
int previousCode = -1;

// ===== WORD MODE =====
String words[16] = {
  "", "Yes", "Hello", "Nurse",
  "Sorry", "Medicine", "Doctor", "Hot",
  "Please", "Cold", "Goodbye", "Help",
  "Hungry", "Pain", "Bathroom", "Sleep"
};

// ===== LETTER MODE =====
String letters[16] = {
  "", "A", "B", "C",
  "D", "E", "F", "G",
  "H", "I", "J", "K",
  "L", "M", "N", "O"
};

// ===== GET BUTTON COMBO =====
int getGestureID() {
  int mask = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      mask |= (1 << i);
    }
  }
  return mask;
}

void setup() {
  Serial.begin(9600);  // 🔥 Bluetooth communication

  lcd.init();
  lcd.backlight();

  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT); // pull-down
  }

  lcd.setCursor(0, 0);
  lcd.print("Smart Glove");
  delay(1500);
  lcd.clear();
}

void loop() {
  int code = getGestureID();

  // Count pressed buttons
  int pressedCount = 0;
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      pressedCount++;
    }
  }

  // ===== MODE TOGGLE =====
  if (pressedCount == 4) {
    isWordMode = !isWordMode;

    lcd.clear();
    lcd.setCursor(0, 0);

    if (isWordMode) {
      lcd.print("Word Mode");
    } else {
      lcd.print("Letter Mode");
      sentence = "";
    }

    delay(1000);
    previousCode = -1;
    lastMessage = "";
    lastSentenceSent = "";
    return;
  }

  // ===== WORD MODE =====
  if (isWordMode) {
    String message = words[code];

    if (message != lastMessage) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(message);
      lastMessage = message;

      // 🔥 SEND ONLY ON CHANGE
      if (message != "") {
        Serial.print(message);
      }
    }
  }

  // ===== LETTER MODE =====
  else {
    if (code != 0 && code != previousCode) {

      if (code == 1) {           // SPACE
        sentence += " ";
      }
      else if (code == 2) {      // CLEAR
        sentence = "";
        lcd.clear();
        previousCode = code;
        delay(300);
        return;
      }
      else {
        sentence += letters[code];
      }

      // Display
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(sentence.substring(0, 16));

      if (sentence.length() > 16) {
        lcd.setCursor(0, 1);
        lcd.print(sentence.substring(16, 32));
      }

      // 🔥 SEND ONLY IF CHANGED
      if (sentence != lastSentenceSent) {
        Serial.print(sentence);       
        lastSentenceSent = sentence;
      }
    }
  }

  previousCode = code;
  delay(150); // debounce
}