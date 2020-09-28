/* This game will consist of four LEDs and four buttons, the game will start as soon as the player pressed Button 1, 
 *  after that it will end and we will need to reset the board to be able to play again. We will then have 5 levels
 *  all the LEDs will light up for a couple of seconds and then the first level will start:
 *  
 *  LEVEL 1 - The player can see a sequence of 2 LEDs lighting up 
 *  LEVEL 2 - The player can see a sequence of 3 LEDs lighting up
 *  LEVEL 3 - The player can see a sequence of 4 LEDs lighting up
 *  LEVEL 4 - The player can see a sequence of 5 LEDs lighting up
 *  LEVEL 5 - The player can see a sequence of 6 LEDs lighting up
 *  
 *  If the player answers correctly each level before level 5 they just transition to the next level, all the LEDS light up
 *  for 2 seconds before the next level. Once the player gets level 5 correct the LEDs light up one by one as in celebration!
 *  If the player answers incorrectly at any point the LEDs just light up and off all together for five seconds and the game ends.
*/

//TODO: Finish compare input function - DONE
//TODO: Check for winning and losing conditions - DONE
//TODO: Include buzzer - CONTINUE IMPLEMENTING 
//TODO: Check for advise on how to avoid bouncing in buttons - I THINK THIS SHOULD BE 
//TODO: Save in GitHub 


// Defining the LED pins
#define LED1 2 
#define LED2 3
#define LED3 4 
#define LED4 5

#define BUTTON1 6
#define BUTTON2 7
#define BUTTON3 8
#define BUTTON4 9

#define BUZZER 10

// Will let us know if led is on or of
  boolean led1On;
  boolean led2On;
  boolean led3On;
  boolean led4On;
  boolean startGame;
  int currentLevel = 1;

void setup() {
  // put your setup code here, to run once:
  // Start serial
  Serial.begin(9600);
  
  // Setting up the pins
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  // Internal pull up resistor to be able to have a direct ground to pin connection in the switch
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);

  led1On = false;
  led2On = false;
  led3On = false;
  led4On = false;
  startGame = false;

  // Checking for the start button
  checkForStartButton();

  // Random seed being generated from a floating pin
  randomSeed(analogRead(0));
}

void checkForStartButton(){
  //we start at this loop until the user presses the first button
  while(digitalRead(BUTTON1)){
    }
  }

void playToneLED(int LEDSelected){
    switch(LEDSelected){
        case 2:
          tone(BUZZER, 783); // Send 789Hz signal which is a G5
          delay(500);        // ...for 500milli sec
          noTone(BUZZER);     // Stop sound...
          break;
        case 3:
          tone(BUZZER, 880); // Send 880Hz which is a A5
          delay(500);        // ...for 500milli sec
          noTone(BUZZER);     // Stop sound...
          break;
        case 4:
          tone(BUZZER, 987); // Send 987Hz which is a B5
          delay(500);        // ...for 500mili sec
          noTone(BUZZER);     // Stop sound...
          break;
        case 5: 
          tone(BUZZER, 1046); // Send 1046Hz which is a C6
          delay(500);        // ...for 500milli sec
          noTone(BUZZER);     // Stop sound...
          break;
      }
  }

void displayNextState(int *randomNumbers){
    // Display transition of LEDs lighten up for 2 seconds
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(2000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    delay(500);

    // Next level being displayed
    
    // Populating randomNumber array
    for(int i = 0; i < currentLevel+1; i++){
        randomNumbers[i] = random(LED1,LED4+1);
      }

    for(int i = 0; i < currentLevel + 1; i++){
        Serial.println(randomNumbers[i]);
      }
    // Turning random LEDs on based on the random numbers inside the randomNumber array
    for(int i = 0; i < currentLevel+1; i++){
        digitalWrite(randomNumbers[i], HIGH);
        playToneLED(randomNumbers[i]);
        delay(300);
        digitalWrite(randomNumbers[i], LOW);
        delay(400);
      }
  }

void getUserInput(int* userInput){
  // Number of inputs inputted by the user
  int inputs = 0;

  // While the number of inputs is less than the current level + 1
  while(inputs < currentLevel+1){
      
      if(!(digitalRead(BUTTON1))){
          userInput[inputs] = 2; 
          inputs++;
          
          while(!digitalRead(BUTTON1)){
              digitalWrite(LED1, HIGH);
              playToneLED(2);
            }
            delay(100);
            digitalWrite(LED1, LOW);
          Serial.println("button1");
        }
        
      if(!(digitalRead(BUTTON2))){
          userInput[inputs] = 3;
          inputs++;
         
          while(!digitalRead(BUTTON2)){
              digitalWrite(LED2, HIGH);
              playToneLED(3);
            }
            delay(100);
            digitalWrite(LED2, LOW);
            Serial.println("button2");
        }
        
      if(!(digitalRead(BUTTON3))){
          userInput[inputs] = 4;
          inputs++;
          
          while(!digitalRead(BUTTON3)){
              digitalWrite(LED3, HIGH);
              playToneLED(4);
            }
            delay(100);
            digitalWrite(LED3, LOW);
            Serial.println("button3");
        }
        
      if(!(digitalRead(BUTTON4))){
          userInput[inputs] = 5;
          inputs++;
          
          while(!digitalRead(BUTTON4)){
              digitalWrite(LED4, HIGH);
              playToneLED(5);
            }
            delay(100);
            digitalWrite(LED4, LOW);
            Serial.println("button4");
        }

    }

  for(int i = 0; i < currentLevel+1; i++){
      Serial.println(userInput[i]);
    }
  return userInput;
}

boolean compareInput(int *userInput, int* randomNumbers){
  for(int i = 0; i < currentLevel+1; i++){
      if(userInput[i] != randomNumbers[i]){
          return false;
        }
    }
  return true;
}

void loop() {
  tone(BUZZER, 1000); // Send 1KHz sound signal...
  delay(200);        // ...for 1 sec
  noTone(BUZZER);     // Stop sound...
  
  // Initialize randomNumbers array
  int randomNumbers[currentLevel+1];

  // Array to keep track of user input
  int userInput[currentLevel+1];
  
  // Displaying next levels in the LEDs
  displayNextState(randomNumbers);

  // Getting user input
  getUserInput(userInput);

  Serial.print("userInput = ");
  for(int i = 0; i < currentLevel + 1; i++){
      Serial.print(*(userInput+i));
    }
    Serial.println("");
  Serial.print("randomNumbers = ");
  for(int i = 0; i < currentLevel + 1; i++){
      Serial.print(*(randomNumbers+i));
    }
    Serial.println("");
    
  // Comparing user input and deciding what to do next
  boolean equalInputLed = compareInput(userInput, randomNumbers);
 
  currentLevel++;

  //TODO: account for when the user wins or loses to do something special with the LEDs in each case
  if(equalInputLed == false){
      //LOSING LED BEHAVIOR - FLASHING FIVE TIMES ALL TOGETHER
      for(int i = 0; i < 6; i++){
        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        delay(200);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);
        delay(200);
      }
      Serial.println("You lose!");
      delay(500);
      exit(0);
    }
  if(currentLevel == 7){
    //WINNING LED BEHAVIOR - FLASHING IN SERIES 
    for(int i = 0; i < 5; i++){
        digitalWrite(LED1, HIGH);
        delay(100);
        digitalWrite(LED1, LOW);
        delay(200);

        digitalWrite(LED2, HIGH);
        delay(100);
        digitalWrite(LED2, LOW);
        delay(200);

        digitalWrite(LED3, HIGH);
        delay(100);
        digitalWrite(LED3, LOW);
        delay(200);

        digitalWrite(LED4, HIGH);
        delay(100);
        digitalWrite(LED4, LOW);
        delay(200);
      }
    Serial.println("You win!");
    delay(500);
    exit(0);
  }
  

}
