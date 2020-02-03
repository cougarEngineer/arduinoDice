byte val = 0;
bool state = 0;
char out[] = "0000";
byte temp = 0;
const byte dType[] = {2,4,6,8,10,12,20,100};
const char dTypeDisplay[][4] = {"c01n","d  4","d  6","d  8","d 10","d 12","d 20","d100"};
const byte segA = 7;
const byte segB = 6;
const byte segC = 5;
const byte segD = 4;
const byte segE = 3;
const byte segF = 2;
const byte segG = 8;
const byte segPt = A4;
const byte digit1 = 13;
const byte digit2 = 12;
const byte digit3 = 11;
const byte digit4 = 10;
const int DELAY = 1;


void printWaiting();
void printOut();
void printDType();
void setOut();
void disp(const char todisp[]);
void disp(const char todisp);


void setup() 
{
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(13,5);
  digitalWrite(12,5);
  digitalWrite(11,5);
  digitalWrite(10,5);
  digitalWrite(7,0);
  digitalWrite(6,0);
  digitalWrite(5,0);
  digitalWrite(4,0);
  digitalWrite(3,0);
  digitalWrite(2,0);
  digitalWrite(1,0);
  digitalWrite(0,0);
  randomSeed(analogRead(5));
  delay(200);
}


void loop() 
{
  val = analogRead(0) >> 7;
  Serial.println(val);
  if(!digitalRead(9))
  {
    if (!state)
    {
      printRolling();
      setOut();
      delay(200);      
    }
    printOut();
    state = 1;
  }
  else
  {
    state = 0;
    printDType();
  } 

}


void printRolling()
{
  disp("nnnn", false);
}


void printOut()
{
  disp(out, true);
}


void printDType()
{
  disp(dTypeDisplay[val], false);
}


void setOut()
{
  switch (val)
  {
    case 0:
      out[0] = random(0,2) ? 'h' : 't';
      out[1] = random(0,2) ? 'h' : 't';
      out[2] = random(0,2) ? 'h' : 't';
      out[3] = random(0,2) ? 'h' : 't';
      break;
    case 1:
    case 2:
    case 3:
      out[0] = random(0,dType[val])+1;
      out[1] = random(0,dType[val])+1;
      out[2] = random(0,dType[val])+1;
      out[3] = random(0,dType[val])+1;
    break;
    case 4:
    case 5:
    case 6:
      temp = random(0,dType[val])+1;
      out[0] = (temp / 10) ? 1 : ' ';
      out[1] = temp % 10;
      temp = random(0,dType[val])+1;
      out[2] = (temp / 10) ? 1 : ' ';
      out[3] = temp % 10;
    break;
    case 7:
      temp = random(0,dType[val])+1;
      out[0] = ' ';
      out[1] = (temp/100) ? 1 : ' ';
      out[2] = ((out[1] != ' ') || (temp/10)) ? temp/10 : ' ';
      out[3] = temp % 10;
    break;
  }
}


void disp(const char todisp[], bool num)
{
  digitalWrite(digit1,LOW);
  disp(todisp[0], val<4 && num ? HIGH : LOW);
  delay(DELAY);
  digitalWrite(digit1,HIGH);
  
  digitalWrite(digit2,LOW);
  disp(todisp[1], val<8 && num ? HIGH : LOW);
  delay(DELAY);
  digitalWrite(digit2,HIGH);
  
  digitalWrite(digit3,LOW);
  disp(todisp[2], val<4 && num ? HIGH : LOW);
  delay(DELAY);
  digitalWrite(digit3,HIGH);
  
  digitalWrite(digit4,LOW);
  disp(todisp[3], LOW);
  delay(DELAY);
  digitalWrite(digit4,HIGH);
}


void disp(const char todisp, byte decimal)
{
  switch(todisp)
  {
    case ' ':
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, LOW);
      break;
    case 'd':
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, LOW);
      break;
    case '0':
    case 0:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, decimal);
      break;
    case '1':
    case 1:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, decimal);
      break;
    case '2':
    case 2:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '3':
    case 3:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '4':
    case 4:
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '5':
    case 5:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '6':
    case 6:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '7':
    case 7:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, LOW);
      digitalWrite(segF, LOW);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, decimal);
      break;
    case '8':
    case 8:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case '9':
    case 9:
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, LOW);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case 'c':
      digitalWrite(segA, HIGH);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, LOW);
      break;
    case 'n':
      digitalWrite(segA, HIGH);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, LOW);
      digitalWrite(segPt, LOW);
      break;
    case 'h':
      digitalWrite(segA, LOW);
      digitalWrite(segB, HIGH);
      digitalWrite(segC, HIGH);
      digitalWrite(segD, LOW);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
    case 't':
      digitalWrite(segA, LOW);
      digitalWrite(segB, LOW);
      digitalWrite(segC, LOW);
      digitalWrite(segD, HIGH);
      digitalWrite(segE, HIGH);
      digitalWrite(segF, HIGH);
      digitalWrite(segG, HIGH);
      digitalWrite(segPt, decimal);
      break;
  }
}
