/**
 * @file main.cpp
 * @author Garrett Summerfield (garrettsummerfi3ld@gmail.com)
 * @brief Button game element for 2020-2021 robotics competition
 * @version 1.0
 * @date 2021-02-07
 * 
 */

#include <Arduino.h>
#include <UTFT.h>

static void teamAction(int team);
static void debugGame();
static void displayUpdate();

// Set button values to hardware pinouts
const int redButton = 8, blueButton = 9;

// Scoring vars, set to zero at start of game
int redTeamCount = 0, blueTeamCount = 0;

// Delay and time vars, has a constant delay of 10 seconds and a variable to hold the time of the game
const unsigned long timerDelay = 10000;
unsigned long currentTime;

// Team Delay vars, used to mark when the buttons have been pressed during time
unsigned long redTeamLastPressTime = 0, blueTeamLastPressTime = 0;

// Set font values for TFT screen
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Set TFT screen display
UTFT myGLCD(ILI9486, 38, 39, 40, 41);

/**
 * @brief Arduino setup for game input
 * 
 * Sets up the display and buttons for inputs.
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
  myGLCD.fillScr(VGA_WHITE);
  myGLCD.setBackColor(VGA_BLACK);

  // Set button modes
  pinMode(redButton, INPUT);
  pinMode(blueButton, INPUT);

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
  myGLCD.setColor(VGA_RED);
  myGLCD.fillRect(230, 0, 245, 305);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.fillRect(245, 0, 260, 305);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print("RED TEAM:", 50, 25);
  myGLCD.print("BLUE TEAM:", 280, 25);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print(String(redTeamCount), 60, 80);
  myGLCD.print(String(blueTeamCount), 310, 80);
  myGLCD.setFont(BigFont);
  myGLCD.print(String(redTeamLastPressTime), 50, 160);
  myGLCD.print(String(blueTeamLastPressTime), 280, 160);
  myGLCD.print("GAME TIMER: " + String(currentTime), 120, 305);
  return;
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
 * @param team Each team has a specific value to run the code specific for each team
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
  debugGame();
  return;
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
  return;
}
