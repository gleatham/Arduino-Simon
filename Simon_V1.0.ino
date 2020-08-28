// LED pin numbers
#define yellowLedPin 2
#define blueLedPin 3
#define greenLedPin 4
#define redLedPin 5

// LED pin numbers
#define yellowButtonPin 6
#define blueButtonPin 7
#define greenButtonPin 8
#define redButtonPin 9
#define startPin 10

// Set difficulty pins
#define onePin 11
#define twoPin 12 
#define threePin 13

int yellowButtonState = 0;
int lastYellowButtonState = 0;
int blueButtonState = 0;
int lastBlueButtonState = 0;
int greenButtonState = 0;
int lastGreenButtonState = 0;
int redButtonState = 0;
int lastRedButtonState = 0;

int userInput[99];
int randomPattern[99];
int turnCounter = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellowLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  pinMode(yellowButtonPin, INPUT_PULLUP);
  pinMode(blueButtonPin, INPUT_PULLUP);
  pinMode(greenButtonPin, INPUT_PULLUP);
  pinMode(redButtonPin, INPUT_PULLUP);

  // debugging
  Serial.begin(9600);

  // fill random array with numbers
  generatePattern();
}

void generatePattern() {
  int n = 99;
  int i = 0;
  int upper = 4;
  int lower = 0;

  for (i = 0; i < n; i++) {
    randomPattern[i] = (rand() % (upper - lower)) + lower;
    //Serial.println(randomPattern[i]);
  }
}

void displayPattern(){
  for (int i = 0; i < turnCounter; i++) {
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
  while (numInputs <= turnCounter){
    if (digitalRead(yellowButtonPin) == LOW)
    {
      delay(50);
      digitalWrite(yellowLedPin, HIGH);
      userInput[numInputs] = 0;
      checkInput(numInputs);
      numInputs++;
    }
    if (digitalRead(blueButtonPin) == LOW)
    {
      delay(50);
      digitalWrite(blueLedPin, HIGH);
      userInput[numInputs] = 1;
      checkInput(numInputs);
      numInputs++;
    }
    if (digitalRead(greenButtonPin) == LOW)
    {
      delay(50);
      digitalWrite(greenLedPin, HIGH);
      userInput[numInputs] = 2;
      checkInput(numInputs);
      numInputs++;
    }
    if(digitalRead(redButtonPin) == LOW)
    {
      delay(50);
      digitalWrite(redLedPin, HIGH);
      userInput[numInputs] = 3;
      checkInput(numInputs);
      numInputs++;
      digitalWrite(redLedPin, LOW);
    }

    delay(100);
    //digitalWrite(yellowLedPin, LOW);
    //digitalWrite(blueLedPin, LOW);
    //digitalWrite(greenLedPin, LOW);
    //digitalWrite(redLedPin, LOW);
  
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
}
