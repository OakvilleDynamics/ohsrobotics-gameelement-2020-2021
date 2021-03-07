/**
 * @file main.cpp
 * @author Garrett Summerfield (garrettsummerfi3ld@gmail.com)
 * @brief Button game element for 2020-2021 robotics competition
 * @version 0.1
 * @date 2021-02-07
 * 
 */

#include <Arduino.h>
#include <UTFT.h>

static void teamAction(int team);
static void resetAction();
static void debugGame();
static void displayUpdate();

// Set button values
const int redButton = 8, blueButton = 9, resetButton = 10;

// Scoring vars
int redTeamCount = 0, blueTeamCount = 0;

// Delay and time vars
unsigned long timerDelay = 10000;
unsigned long currentTime;

// Team Delay vars
unsigned long redTeamLastPressTime = 0, blueTeamLastPressTime = 0;

// Set font values for TFT screen
extern uint8_t BigFont[];
extern uint8_t SevenSegmentFont[];

// Set TFT Screen values
UTFT myGLCD(ILI9486,38,39,40,41);

/**
 * @brief Arduino setup for game input
 * 
 */
void setup()
{
  // Sets baud rate to communicate to computer for any messages, used for debug
  Serial.begin(9600);

  // Start up TFT screen
  myGLCD.InitLCD();
  myGLCD.clrScr();
  myGLCD.setFont(BigFont);

  // Set button modes
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);
  pinMode(resetButton, INPUT);

  Serial.println("[INFO] Started!");
}

/**
 * @brief Main game logic
 * 
 * Each time a button is pressed, it will run the desired commands for which
 * button is assigned. There are two main buttons that are used for scoring in
 * the game, and a reset button.
 * 
 */
void loop()
{
  // Gets current program time in milliseconds
  currentTime = millis();

  // Red Team
  if (digitalRead(redButton) == HIGH)
  {
    teamAction(redButton);
  }

  // Blue Team
  if (digitalRead(blueButton) == HIGH)
  {
    teamAction(blueButton);
  }

  // Reset Score logic
  if (digitalRead(resetButton) == HIGH)
  {
    resetAction();
    debugGame();
  }

  displayUpdate();
}

/**
 * @brief Updates Display
 * 
 * Sets the cursor and writes text for each row of the display.
 * 
 * Text written is the physical text for the scoreboard.
 * 
 */
void displayUpdate()
{
  // Main Scoreboard
  //lcd.setCursor(0, 0);
  //lcd.print("RED TEAM:  " + String(redTeamCount));
  //lcd.setCursor(0, 1);
  //lcd.print("BLUE TEAM: " + String(blueTeamCount));
}

/**
 * @brief Reset action
 * 
 * Clears scoreboard display, sets all variables to zero, and outputs to the
 * user that the scoreboard reset.
 * 
 */
void resetAction()
{
  // Clear scoreboard
  //lcd.clear();

  // Set vars to zero (0)
  redTeamCount = 0;
  blueTeamCount = 0;

  // Output "RESET SCORES" to end user and serial bridge
  //lcd.setCursor(0, 0);
  //lcd.print("RESET SCORES");
  Serial.println("[INFO] Reset Scores!");
  delay(2500);
}

/**
 * @brief Actions per each button press
 * 
 * When a scoring button is pressed, it will add a single point to the
 * teams score.
 * 
 * Pressing the button when the time last pressed is zero will score a point.
 * 
 * Pressing too early will reset the timer.
 * 
 * The default delay is 10 seconds (10000ms) and is controlled by timerDelay
 * 
 * @param team 
 */
void teamAction(int team)
{
  // Red Team Logic
  if (team == redButton)
  {
    Serial.println("[INFO] RED Team button pressed!");
    // Give points to a team for pressing the button at the right time
    if (currentTime - redTeamLastPressTime >= timerDelay)
    {
      redTeamCount++;
      redTeamLastPressTime = currentTime;
      Serial.println("[INFO] RED Team score added!");
    }
    else if (redTeamLastPressTime == 0)
    {
      redTeamCount++;
      redTeamLastPressTime = currentTime;
      Serial.println("[INFO] RED Team score added!");
    }
    // Reset timer for team for pressing to early
    else
    {
      redTeamLastPressTime = currentTime;
      Serial.println("[INFO] RED Team timer reset!");
    }
  }

  // Blue Team Logic
  if (team == blueButton)
  {
    Serial.println("[INFO] BLUE Team button pressed!");
    // Give points to a team for pressing the button at the right time
    if (currentTime - blueTeamLastPressTime >= timerDelay)
    {
      blueTeamCount++;
      blueTeamLastPressTime = currentTime;
      Serial.println("[INFO] BLUE Team score added!");
    }
    else if (blueTeamLastPressTime == 0)
    {
      blueTeamCount++;
      blueTeamLastPressTime = currentTime;
      Serial.println("[INFO] BLUE Team score added!");
    }
    // Reset timer for team for pressing too early
    else
    {
      blueTeamLastPressTime = currentTime;
      Serial.println("[INFO] BLUE Team timer reset!");
    }
  }
  delay(150);
  debugGame();
}

/**
 * @brief Debug prompts
 * 
 * Outputs the current time in milliseconds and the last time each team has
 * pressed the button.
 * 
 */
void debugGame()
{
  Serial.println("[DEBUG] currentTime:" + String(currentTime));
  Serial.println("[DEBUG] redTeamLastPressTime:" + String(redTeamLastPressTime));
  Serial.println("[DEBUG] blueTeamLastPressTime:" + String(blueTeamLastPressTime));
}
