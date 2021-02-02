#include <Arduino.h>
#include <LiquidCrystal.h>
// Set button values
int button1 = 8, button2 = 9, resetButton = 10;

// Scoring vars
int redTeamCount = 0, blueTeamCount = 0;

// Delay vars
unsigned long timerDelay = 10000;

// Team Delay vars
unsigned long redTeamLastPressTime = 0, blueTeamLastPressTime = 0;

// LCD pin vars
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

// Set LCD values
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initialization
void setup()
{
  // Sets baud rate to communicate to computer for any messages, used for debug
  Serial.begin(9600);

  // Start up LCD screen
  lcd.begin(16, 2);

  // Set button modes
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(resetButton, INPUT);

  Serial.println("[INFO] Started!");
}

// Main game logic
//
// Each time a button is pressed, it will run the desired commands for which
// button is assigned. There are two main buttons that are used for scoring in
// the game. When a scoring button is pressed, it will add a single point to the
// teams score, however there is a penalty if you press the button too early,
// and it will deduct a point from the team. There is a ten second delay on when
// the button will be active to press.
void loop()
{

  // Gets current program time in milliseconds
  unsigned long currentTime = millis();

  // Red Team Score logic
  if (digitalRead(button1) == HIGH)
  {
    Serial.println("[INFO] RED Team button pressed!");
    // Give points to a team for pressing the button at the right time
    if (currentTime - redTeamLastPressTime >= timerDelay)
    {
      redTeamCount++;
      redTeamLastPressTime = currentTime;
      Serial.println("[INFO] RED Team score added!");

      delay(150);
    }
    else if (redTeamLastPressTime == 0)
    {
      redTeamCount++;
      redTeamLastPressTime = currentTime;
      Serial.println("[INFO] RED Team score added! TIMER RESET");

      delay(150);
    }
    // Deduct points from team for pressing to early
    else
    {
      redTeamCount--;
      delay(150);
      Serial.println("[INFO] RED Team score lost!");
    }

      // Debug Statements, only available through the serial connection
      Serial.println("[DEBUG] currentTime:" + String(currentTime));
      Serial.println("[DEBUG] redTeamLastPressTime:" + String(redTeamLastPressTime));
      Serial.println("[DEBUG] blueTeamLastPressTime:" + String(blueTeamLastPressTime));
  }


  // Blue Team Score logic
  if (digitalRead(button2) == HIGH)
  {
    Serial.println("[INFO] BLUE Team button pressed!");
    // Give points to a team for pressing the button at the right time
    if (currentTime - blueTeamLastPressTime >= timerDelay)
    {
      blueTeamCount++;
      blueTeamLastPressTime = currentTime;
      Serial.println("[INFO] BLUE Team score added!");
      delay(150);
    }
    else if (blueTeamLastPressTime == 0)
    {
      blueTeamCount++;
      blueTeamLastPressTime = currentTime;
      Serial.println("[INFO] BLUE Team score added! TIMER RESET");
      delay(150);
    }
    // Deduct points from team for pressing too early
    else
    {
      blueTeamCount--;
      Serial.println("[INFO] BLUE Team score lost!");
      delay(150);
    }

    // Debug Statements, only available through the serial connection
    Serial.println("[DEBUG] currentTime:" + String(currentTime));
    Serial.println("[DEBUG] redTeamLastPressTime:" + String(redTeamLastPressTime));
    Serial.println("[DEBUG] blueTeamLastPressTime:" + String(blueTeamLastPressTime));
  }

  // Reset Score logic
  if (digitalRead(resetButton) == HIGH)
  {
    // Clear scoreboard
    lcd.clear();

    // Set vars to zero (0)
    redTeamCount = 0;
    blueTeamCount = 0;

    // Output "RESET SCORES" to end user and serial bridge
    lcd.setCursor(0, 0);
    lcd.print("RESET SCORES");
    Serial.println("[INFO] Reset Scores!");
    delay(2500);

    // Debug Statements, only available through the serial connection
    Serial.println("[DEBUG] currentTime:" + String(currentTime));
    Serial.println("[DEBUG] redTeamLastPressTime:" + String(redTeamLastPressTime));
    Serial.println("[DEBUG] blueTeamLastPressTime:" + String(blueTeamLastPressTime));
  }

  // Main Scoreboard
  lcd.setCursor(0, 0);
  lcd.print("RED TEAM:  " + String(redTeamCount));
  lcd.setCursor(0, 1);
  lcd.print("BLUE TEAM: " + String(blueTeamCount));
}