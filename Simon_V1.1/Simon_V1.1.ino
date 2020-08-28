/***************************************************************************
Simon v1.1
Author: Geoffrey Leatham
Contact: geoff@gleatham.com
Implementation of the 1978 Simon game from Milton Bradley (Hasbro)

Color key: Yellow == 0, Blue == 1, Green == 2, Red == 3
***************************************************************************/

// LED pin numbers
const int yellowLedPin = 2;
const int blueLedPin = 3;
const int greenLedPin = 4;
const int redLedPin = 5;

// LED pin numbers
const int yellowButtonPin = 6;
const int blueButtonPin = 7;
const int greenButtonPin = 8;
const int redButtonPin = 9;
const int startPin = 10;

// logic and storage vars
int userInput[99];
int randomPattern[99];
int turnCounter = 0; 

//Button state variables
int buttonPushCounter = 0;
int yellowButtonState = 0;
int yellowLastButtonState = 0;
int blueButtonState = 0;
int blueLastButtonState = 0;
int greenButtonState = 0;
int greenLastButtonState = 0;
int redButtonState = 0;
int redLastButtonState = 0;

void setup() {
  // set output pins
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  // set input pins
  pinMode(yellowButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP);

  // debugging
  Serial.begin(9600);

  // fill random array with numbers
  generatePattern(); //Copy function over from 1.0

  turnCounter = 0;
  Serial.println("Begin...");
}

void generatePattern() {
  int n = 99;
  int i = 0;
  int upper = 4;
  int lower = 0;

  for(i = 0; i < n; i++) {
    randomPattern[i] = (rand() % (upper - lower)) + lower;
  }
}

void displayPattern(){
  for (int i = 0; i <= turnCounter; i++) {
    Serial.println(randomPattern[i]);
    if (randomPattern[i] == 0) {
      digitalWrite(yellowLedPin, HIGH);
      delay(200);
      digitalWrite(yellowLedPin, LOW);
      delay(300);
    }
    if (randomPattern[i] == 1) {
      digitalWrite(blueLedPin, HIGH);
      delay(200);
      digitalWrite(blueLedPin, LOW);
      delay(300);
    }
    if (randomPattern[i] == 2) {
      digitalWrite(greenLedPin, HIGH);
      delay(200);
      digitalWrite(greenLedPin, LOW);
      delay(300);
    }
    if (randomPattern[i] == 3) {
      digitalWrite(redLedPin, HIGH);
      delay(200);
      digitalWrite(redLedPin, LOW);
      delay(300);
    }
  }
}

void getInput() {
  int numInputs = 0;

  while(numInputs <= turnCounter) {
    //Read button state
    yellowButtonState = digitalRead(yellowButtonPin);
    blueButtonState = digitalRead(blueButtonPin);
    greenButtonState = digitalRead(greenButtonPin);
    redButtonState = digitalRead(redButtonPin);

    //yellow if
    if(yellowButtonState != yellowLastButtonState) {
      if(yellowButtonState == LOW) {
        userInput[numInputs] = 0;
        checkInput(numInputs);
        Serial.println("Yellow ON");
        delay(50);
        numInputs++;
      }
    }
    
    //blue if
    if(blueButtonState != blueLastButtonState){
      if(blueButtonState == LOW) {
        userInput[numInputs] = 1;
        checkInput(numInputs);
        Serial.println("Blue ON");
        delay(50);
        numInputs++;
      }
    }

    //green if
    if(greenButtonState != greenLastButtonState){
      if(greenButtonState == LOW) {
        userInput[numInputs] = 2;
        checkInput(numInputs);
        Serial.println("Green ON");
        delay(50);
        numInputs++;
      }
    }
    
    //red if
    if(redButtonState != redLastButtonState){
      if(redButtonState == LOW) {
        userInput[numInputs] = 3;
        checkInput(numInputs);
        Serial.println("Red ON");
        delay(50);
        numInputs++;
      }
    }

    //button state change
    yellowLastButtonState = yellowButtonState;
    blueLastButtonState = blueButtonState;
    greenLastButtonState = greenButtonState;
    redLastButtonState = redButtonState;
    delay(50);
  }
}

void checkInput(int number) {
  if (userInput[number] == randomPattern[number]){
    Serial.println("MATCH");
    return;
  }
  else{
    Serial.println("NO MATCH");
    for(int i = 0; i < 3; i++) {
      digitalWrite(yellowLedPin, HIGH);
      digitalWrite(blueLedPin, HIGH);
      digitalWrite(greenLedPin, HIGH);
      digitalWrite(redLedPin, HIGH);
      delay(300);
      digitalWrite(yellowLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
      digitalWrite(greenLedPin, LOW);
      digitalWrite(redLedPin, LOW);
      delay(300);
    }
    delay(1000);
    setup();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  displayPattern();
  getInput();
  turnCounter++;
  Serial.print("Turn: ");
  Serial.println(turnCounter);
}
