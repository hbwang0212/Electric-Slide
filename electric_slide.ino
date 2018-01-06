#include <LiquidCrystal.h>

const float c = 261.63;
const float d = 293.66;
const float e = 329.63;
const float f = 349.23;
const float g = 392;
const float a = 440; 
const float b = 493.88;
const float b_flat = 466.16; 
const float C = 523;
const float tempo = 200;
const float notes[] = {f,g,c,g,g,a,c,b_flat,a,f,g,c,c,d,e,f,g,e,d,c,c,d,e,c,c,c,c,g,g,g,a,g,f,g,a,f,g,g,g,a,g,c,d,e,f,d,g,g,g,a,g};
const float times[] = {3,1,1,1,1,1,1,1,2,2,3,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,2,6,3,1,1,1,1,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1};

const int buttonPin1 = ;
const int buttonPin2 = ;
const int buttonPin3 = ;
const int buttonPin4 = ; //left the values empty, depends on which pins we attach the buttons to.
const int ledPin1 = ;
const int ledPin2 = ;
const int ledPin3= ;
const int ledPin4 = ;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState 4 = 0;


const int rs_a = 7, en_a = 8, d4_a = 9, d5_a = 10, d6_a = 11, d7_a = 12,
          speaker = 6,
          rs_b = A0, en_b = A1, d4_b = A2, d5_b = A3, d6_b = A4, d7_b = A5,
          btn_1 = 2, btn_2 = 3, btn_3 = 4, btn_4 = 5;


const byte left_arrow_filled[8] = { B00000, B00100, B01110, B11111, B01110, B01110, B01110, B00000 };
const byte left_arrow[8] = { B00000, B00100, B01010, B10001, B01010, B01010, B01110, B00000 };
const byte right_arrow_filled[8] = { B00000, B01110, B01110, B01110, B11111, B01110, B00100, B00000 };
const byte right_arrow[8] = { B00000, B01110, B01010, B01010, B10001, B01010, B00100, B00000 };
const byte down_arrow_filled[8] = { B00000, B00010, B00110, B01111, B11111, B01111, B00110, B00010 };
const byte down_arrow[8] = { B00000, B00010, B00110, B01011, B10001, B01011, B00110, B00010 };
const byte up_arrow_filled[8] = { B00000, B01000, B01100, B11110, B11111, B11110, B01100, B01000 };
const byte up_arrow[8] = { B00000, B01000, B01100, B11010, B10001, B11010, B01100, B01000 };

const byte dancer_1[8] = { B00000, B00100, B10101, B11111, B01110, B01110, B01010, B01010 };
const byte dancer_2[8] = { B00000, B00100, B10100, B11111, B01111, B11110, B10010, B00010 };
const byte dancer_3[8] = { B00000, B00100, B00101, B11111, B11110, B01111, B01001, B01000 };
const byte dancer_4[8] = { B00000, B00100, B00101, B11111, B11110, B01110, B01010, B01010 };
const byte dancer_5[8] = { B00000, B00100, B10100, B11111, B01111, B01110, B01010, B01010 };
const byte dancer_6[8] = { B00000, B00100, B00100, B11111, B11111, B01110, B01010, B01010 };
const byte dancer_7[8] = { B00000, B00000, B00100, B10101, B11111, B01110, B11111, B10001 };

const byte dance[] = {1, 2, 1, 3, 4, 1, 5, 6, 1, 7, 1, 7, 1, 5};

const int arrowConstant = 3;  // the maximum shifts without any spawned arrows.


LiquidCrystal lcd_a (rs_a, en_a, d4_a, d5_a, d6_a, d7_a);
LiquidCrystal lcd_b (rs_b, en_b, d4_b, d5_b, d6_b, d7_b);

int brightness = 100;

void setup() {

  pinMode(rs_a, OUTPUT);
  pinMode(en_a, OUTPUT);
  pinMode(d4_a, OUTPUT);
  pinMode(d5_a, OUTPUT);
  pinMode(d6_a, OUTPUT);
  pinMode(d7_a, OUTPUT);
  pinMode(speaker, OUTPUT);
  pinMode(rs_b, OUTPUT);
  pinMode(en_b, OUTPUT);
  pinMode(d4_b, OUTPUT);
  pinMode(d5_b, OUTPUT);
  pinMode(d6_b, OUTPUT);
  pinMode(d7_b, OUTPUT);
  pinMode(btn_1, INPUT);
  pinMode(btn_2, INPUT);
  pinMode(btn_3, INPUT);
  pinMode(btn_4, INPUT);

  pinMode (ledPin1, OUTPUT);
  pinMode (buttonPin1, INPUT);
  pinMode (ledPin2, OUTPUT);
  pinMode (buttonPin2, INPUT); //added to initialize the 4 buttons
  pinMode (ledPin3, OUTPUT);
  pinMode (buttonPin3, INPUT);
  pinMode (ledPin4, OUTPUT);
  pinMode (buttonPin4, INPUT);

  lcd_a.createChar(byte(1), dancer_1);
  lcd_a.createChar(byte(2), dancer_2);
  lcd_a.createChar(byte(3), dancer_3);
  lcd_a.createChar(byte(4), dancer_4);
  lcd_a.createChar(byte(5), dancer_5);
  lcd_a.createChar(byte(6), dancer_6);
  lcd_a.createChar(byte(7), dancer_7);
  
  lcd_b.createChar(byte(0), left_arrow_filled);
  lcd_b.createChar(byte(1), left_arrow);
  lcd_b.createChar(byte(2), right_arrow_filled);
  lcd_b.createChar(byte(3), right_arrow);
  lcd_b.createChar(byte(4), down_arrow_filled);
  lcd_b.createChar(byte(5), down_arrow);
  lcd_b.createChar(byte(6), up_arrow_filled);
  lcd_b.createChar(byte(7), up_arrow);
    
  lcd_a.begin(16, 2);
  lcd_b.begin(20, 4);

  srand(33196193);

}

int score = 0;

bool left_arrows[20] = { false };
bool right_arrows[20] = { false };
bool down_arrows[20] = { false };
bool up_arrows[20] = { false };

void loop() {

  unsigned long nowTime = millis();

  lcd_a.setCursor(1, 0);
  lcd_a.print("SCORE:");
  lcd_a.setCursor(1, 1);
  lcd_a.print(score);

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2); //code to check value of the button
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);

  if (buttonState1 == HIGH)
  {
    if (checkIfArrow1IsThere(1) == 1)
    {
      score += 10;
    }
    else 
    {
      score -= 5;
    }
  }

  if (buttonState2 == HIGH)
  {
    if (checkIfArrow1IsThere(2) == 1)
    {
      score += 10;
    }
    else 
    {
      score -= 5;
    }
  }

  if (buttonState3 == HIGH)
  {
    if (checkIfArrow1IsThere(3) == 1)
    {
      score += 10;
    }
    else 
    {
      score -= 5;
    }
  }

  if (buttonState4 == HIGH)
  {
    if (checkIfArrow1IsThere(4) == 1)
    {
      score += 10;
    }
    else 
    {
      score -= 5;
    }
  }
  
  printDancers(nowTime);
  playTones(nowTime);
  shiftArrows(nowTime);
  printArrows();



  delay(10);  
}


unsigned long lastDanceTime = 0;
int currentDance = 0;
int dancers[][2] = { {0, 0}, {0, 1} }; 
void printDancers (unsigned long nowTime) {

  if (nowTime - lastDanceTime > tempo * 2) {

      lastDanceTime = nowTime;

      currentDance += 1;
      if(currentDance >= sizeof(dance) / sizeof(*dance)) {
          currentDance = 0;
      }
  }

  lcd_a.setCursor(0, 0);
  for(int i = 0; i < sizeof(dancers) / sizeof(*dancers); i++) {
        lcd_a.setCursor(dancers[i][0], dancers[i][1]);
        lcd_a.write(dance[currentDance]);
  }
}

unsigned long lastNoteTime = 0;
int currentNote = 0;
void playTones (unsigned long nowTime) {

  if (nowTime - lastNoteTime > tempo * times[currentNote]) {

    lastNoteTime = nowTime;

    tone(speaker, notes[currentNote]);

    currentNote += 1;
    if (currentNote >= sizeof(notes) / sizeof(*notes)) {
        currentNote = 0;
    }
  }
}

unsigned long lastShiftTime = 0;
int currentShift = 0;

void shiftArrows (unsigned long nowTime) {

   if (nowTime - lastShiftTime > tempo * 2) {

      lastShiftTime = nowTime;
      currentShift++;

      if (left_arrows[19]) {
          onArrowMissed();
      }
      for (int j = 19; j > 0; j--) {
          left_arrows[j] = left_arrows[j - 1];
      }
      left_arrows[0] = false;


      if (right_arrows[19]) {
          onArrowMissed();
      }
      for (int j = 19; j > 0; j--) {
          right_arrows[j] = right_arrows[j - 1];
      }
      right_arrows[0] = false;


      if (down_arrows[19]) {
          onArrowMissed();
      }
      for (int j = 19; j > 0; j--) {
          down_arrows[j] = down_arrows[j - 1];
      }
      down_arrows[0] = false;


      if (up_arrows[19]) {
          onArrowMissed();
      }
      for (int j = 19; j > 0; j--) {
          up_arrows[j] = up_arrows[j - 1];
      }
      up_arrows[0] = false;


      nextArrows();
   }
}

void printArrows () {

    for (int i = 0; i < 20; i++) {
        lcd_b.setCursor(19 - i, 0);
        if (left_arrows[i]) {
          lcd_b.write(byte(0 + (i != 19)));
        }
        else {
          lcd_b.print(" ");
        }
    }
    for (int i = 0; i < 20; i++) {
        lcd_b.setCursor(19 - i, 1);
        if (right_arrows[i]) {
          lcd_b.write(byte(2 + (i != 19)));
        }
        else {
          lcd_b.print(" ");
        }
    }
    for (int i = 0; i < 20; i++) {
        lcd_b.setCursor(19 - i, 2);
        if (down_arrows[i]) {
          lcd_b.write(byte(4 + (i != 19)));
        }
        else {
          lcd_b.print(" ");
        }
    }
    for (int i = 0; i < 20; i++) {
        lcd_b.setCursor(19 - i, 3);
        if (up_arrows[i]) {
          lcd_b.write(byte(6 + (i != 19)));
        }
        else {
          lcd_b.print(" ");
        }
    }
}


int lastSpawnShift = 0;

void nextArrows () {

  float spawnProb = (currentShift - lastSpawnShift) / ((float) arrowConstant);

  if (randomTest(spawnProb)) {

    lastSpawnShift = currentShift;
    
    switch (randomTest(0.5) * 2 + randomTest(0.5)) {
      case 0:
        left_arrows[0] = true;
      break;
      case 1:
        right_arrows[0] = true;
      break;
      case 2:
        down_arrows[0] = true;
      break;
      case 3:
        up_arrows[0] = true;
      break;
    }
    
  }
}

int checkIfArrowIsThere(int arrowColumn)
{ //this method checks which column that they pressed the button in and then checks if there is an arrow there.
  //If there is, then it returns 1, otherwise returns -1.
  if (arrowColumn = 1)
  {
    if (left_arrows[20] == true)
    {
      return 1;
    }
  }
  
  else if (arrowColumn = 2)
  {
    if (left_arrows[20] == true)
    {
      return 1;
    }
  }
  
  else if (arrowColumn = 3)
  {
    if (left_arrows[20] == true)
    {
      return 1;
    }
  }
  
  else if (arrowColumn = 4)
  {
    if (left_arrows[20] == true)
    {
      return 1;
    }
  }
  
  else
  {
    return -1;
  }
}

bool randomTest (float prob) {

  return ((float)(rand()) / (float)(RAND_MAX)) <= prob;
}


void onArrowMissed () {

    score -= 5;    
}

