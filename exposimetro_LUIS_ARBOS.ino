//STATES DEFINITION
enum State {ON_WITHOUT_PIN,      //We define the states we're going to use, ON, ON WITH PIN, GO OUT MID WORKTIME, EXIT CAMERA, EXCESS EXPOSED TIME, LOW BATTERY
            ON_PIN_OK,
            GO_OUT_WHY,  
            EXIT_CAMERA_BREAK,
            EXCESS_EXPOSED_TIME,
            BATTERY_LOW};
State state= ON_WITHOUT_PIN; //We define this one as the default. 

//VARIABLES AND PINS
unsigned long currentMillis;
const int buzzerPin = 11; 
const int greenLedPin = 12;
const int redLedPin = 13;
unsigned long timeTotal, timeMax, timeCamera, timeCamera2, AuxiliarTime, AuxiliarTime2; //Time related variables
unsigned long AuxiliarMillis, AuxiliarMillis2, AuxiliarMillis3;
int timeBreak;
int i, l, m, n, g; //Aux variables to help us print info only once.

//VARIABLES FOR THE BUTTON
int State; 
unsigned long previousMillis;
int interval = 1000;
int interval2 = 5000;
int intervalSt1=100;
int PreviousMillisSt1;
int CurrentState, PreviousState, NewState;

//BATTERY FUNCTION
//We'll write a function that returns false if the voltage of the battery is out of range, being range 4.2-2.4V. In theory, nothing would happen if the voltage was higher, but we need to make sure it doesn't happen.
bool batt(float M, float m, float V); 
bool batt(float M, float m, float V){
  if(V>M){
    return (true);}//This one should be false. It says true to be able to test it using the 5V pins of an Arduino UNO.
  if(V<m){
    return (false);}
  else{
    return (true);}} 
float Max = 4.2;
float Min = 2.4;

//Keyboard function
char GetKey(void);
char GetKey(void){
  static char A,a,help;
  //There are cleaner ways to do it, but we're doing it with conditionals.
  for(int i=2; i<6; i++){ 
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(i,LOW);
  
  if(digitalRead(6)== LOW && i==2){
  a='1';}

  else if(digitalRead(6)== LOW && i==3){
  a='4';}
  
  else if(digitalRead(6)== LOW && i==4){
  a='7';}
  
  else if(digitalRead(6)== LOW && i==5){
  a='A';}
  
  else if(digitalRead(7)== LOW && i==2){
  a='2';}

  else if(digitalRead(7)== LOW && i==3){
  a='5';}
  
  else if(digitalRead(7)== LOW && i==4){
  a='8';}
  
  else if(digitalRead(7)== LOW && i==5){
  a='0';}
    
  else if(digitalRead(8)== LOW && i==2){
  a='3';}
  
  else if(digitalRead(8)== LOW && i==3){
  a='6';}
  
  else if(digitalRead(8)== LOW && i==4){
  a='9';}
  
  else if(digitalRead(8)== LOW && i==5){
  a='B';}
  
  else if(digitalRead(9)== LOW && i==2){
  a='F';}
  
  else if(digitalRead(9)== LOW && i==3){
  a='E';} 
  
  else if(digitalRead(9)== LOW && i==4){
  a='D';} 
  
  else if(digitalRead(9)== LOW && i==5){
  a='C';}}
  if(a==help){A=0;} //Just in case nobody presses any key.
  else if(a!=help){A=a; a=help;}
  return(A);}
  
//VARIABLES FOR THE KEYBOARD
  char Code[6]={'1','2','3','4','A',0};
  char Code2[6]={'5','6','7','8','B',0}; 
  char PIN[6]={'0','0','0','0','F',0};
  int a,b; char help2;
  int  LastKey;
//VARIABLES FOR THE LEDS AND BUZZER
unsigned long previousMillis1, previousMillis2, previousMillis3;
int stateaux1, stateaux2, stateaux3;

//LED AND BUZZER FUNCTION
//The next three functions will be the same, one for a green led, one for a red one and one for the buzzer. It was done that way because that was the original request.
void greenLed(int x, int y); 
void greenLed(int x, int y){ 
  currentMillis = millis(); 
  if(x==0){digitalWrite(greenLedPin, LOW);}
  else if(y==0){digitalWrite(greenLedPin, HIGH);}
  else{  
    if(currentMillis - previousMillis1 >= y && stateaux1==0){
      previousMillis1 = currentMillis;
      digitalWrite(greenLedPin,HIGH); 
      stateaux1 = 1;}
    else if(currentMillis - previousMillis1 >= x && stateaux1 ==1){    
      previousMillis1 = currentMillis;
      digitalWrite(greenLedPin,LOW);
      stateaux1 = 0;}}}
      
void redLed(int x, int y);
void redLed(int x, int y){
  if(x==0){digitalWrite(redLedPin, LOW);}
  else if(y==0){digitalWrite(redLedPin, HIGH);}
  else{
    if(currentMillis - previousMillis2 >= y && stateaux2 ==0){
      previousMillis2 = currentMillis;
      digitalWrite(redLedPin,HIGH);
      stateaux2 = 1;}
    else if(currentMillis - previousMillis2 >= x && stateaux2 ==1){
      previousMillis2 = currentMillis;
      digitalWrite(redLedPin,LOW);
      stateaux2 = 0;}}}
      
void buzzer(int x, int y);
void buzzer(int x, int y){
  if(x==0){digitalWrite(buzzerPin,LOW);}
  else if(y==0){digitalWrite(buzzerPin,HIGH);}
  else{if(currentMillis - previousMillis3 >= y && stateaux3 ==0){
      previousMillis3 = currentMillis;
      digitalWrite(buzzerPin,HIGH);
      stateaux3 = 1;}
    else if(currentMillis - previousMillis3 >= x && stateaux3 ==1){
      previousMillis3 = currentMillis;
      digitalWrite(buzzerPin,LOW);
      stateaux3 = 0;}}}

//Special function to turn on and off simultaneously the green and red leds
void doubleLed(int x, int y); 
void doubleLed(int x, int y){ 
  currentMillis = millis(); 
  if(x==0){digitalWrite(greenLedPin, LOW);
           digitalWrite(redLedPin, LOW);}
  else if(y==0){digitalWrite(greenLedPin, HIGH);
                digitalWrite(redLedPin, HIGH);}
  else{  
    if(currentMillis - previousMillis1 >= y && stateaux1==0){
      previousMillis1 = currentMillis;
      digitalWrite(greenLedPin,HIGH);
      digitalWrite(redLedPin,HIGH); 
      stateaux1 = 1;}
    else if(currentMillis - previousMillis1 >= x && stateaux1 ==1){    
      previousMillis1 = currentMillis;
      digitalWrite(greenLedPin,LOW);
      digitalWrite(redLedPin,LOW);
      stateaux1 = 0;}}}     

//VARIABLES FOR TEMPERATURE SENSORS
  float consigna1= -5.0, consigna2 = -18.0;
  float histeresis = 1.0;
  bool previousState1 = true, previousState2 = true;
  int stateTemp, previousStateTemp = 0, New;
  
// FUNCTION FOR THE TEMPERATURE SENSOR
void temperatureState(float Temperatura, float H, float consigna, bool *previousState);
void temperatureState(float Temperatura, float H, float consigna, bool *previousState)
{
if(*previousState == true){
  if(Temperatura < (consigna - H)){
    *previousState = false;}}
else{
  if(Temperatura > (consigna + H)){
    *previousState = true;}}
}


//SETTING THE PINS
void setup(){
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,INPUT_PULLUP);
  pinMode(7,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(buzzerPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  
}
void loop(){
//BUTTON
State = digitalRead(10);
currentMillis = millis(); 
if(State == HIGH){
  previousMillis = currentMillis;
  PreviousState=1;}

if(currentMillis - previousMillis>=interval && CurrentState==0 && PreviousState ==1){
  greenLed(100,0);
  NewState = 1; CurrentState =1; PreviousState =0;}

if(currentMillis- previousMillis>= interval2 && CurrentState == 1 && PreviousState ==1){
  greenLed(0,100);
  NewState =0; CurrentState =0;PreviousState=0;} 
 
//BATTERY
float percentage;
int sensorValuebatt = analogRead(A1);
float Value = sensorValuebatt*(5.0/1023.0);//Should be 4.2 as the maximum, but we're using 5.0 to test this on an Arduino Board.
  if(batt(Max, Min, Value)== false){
    percentage=0;}
  else if(batt(Max, Min, Value)== true){
    percentage = ((Value-2.4)*100.0)/1.8;}

//KEYBOARD
char myChar = GetKey();
 if(myChar != LastKey){help2 = true; 
   LastKey = myChar;}
 else{help2 = false;}
 
 if(myChar!=0 && help2==true){
    if(b<5){ 
      PIN[b]=myChar;
     Serial.println(PIN); 
      if(b!=4){b++;}
      else{b=0;}}
    else{b=0;}}

//TEMPERATURE SENSOR
 int SensorValuetemp = analogRead(A0);
 //5V -20ºC, 3.3V -13.2ºC and 0V 0ºC 

 float Temperatura = SensorValuetemp*(5.0/1023.0)*(-4.0);
 //We call the function twice to make it join the loop and know in which state we are 
 temperatureState(Temperatura, histeresis,consigna1, &previousState1);
 temperatureState(Temperatura, histeresis,consigna2, &previousState2);

//TEMPERATURE STATE
if((previousState1 == 1) && (previousState2 == 1) && (New != 0)){ stateTemp=0; previousStateTemp = 1;} 
else if((previousState1 == 1) && (previousState2 == 1) && (New == 0)){ stateTemp=0; previousStateTemp = 0;}//0 means outside the chamber
//else if((previousState1== 0) && (previousState2== 1) && (New != 1)){ stateTemp=1;}
else if((previousState1== 0) && (previousState2== 1)){ stateTemp=1;}// 1 means inside the chamber
else if((previousState1== 0) && (previousState2==0)) stateTemp=2; // 2 means we activate the alarm

//AUX VARIABLES FOR TIME
if(state != ON_PIN_OK && state != GO_OUT_WHY){AuxiliarTime = millis();}
if(stateTemp==0){AuxiliarMillis = millis() - AuxiliarTime;}
if(stateTemp==0){AuxiliarMillis3 = millis();}
if(stateTemp==1){AuxiliarMillis2 = millis();}
Serial.print(timeCamera);Serial.print(' ');Serial.print(stateTemp);Serial.println(' ');

if(NewState==1){ 

switch (state){
  case ON_WITHOUT_PIN:
    //INFO
    for(i; i<1 ;i++){
    Serial.println("ON");}
    greenLed(500,1000);
    redLed(0,100);
    if(percentage < 10) state = BATTERY_LOW;
    else {
      if(strcmp(PIN,Code)==0){
        for(n;n<1;n++){
        Serial.println("PIN accepted");
        Serial.println("Please enter the chamber");}
        state = ON_PIN_OK;
        n=0;}
      else if(strcmp(PIN,Code2)==0){
        for(n;n<1;n++){
        Serial.println("PIN accepted");
        Serial.println("Please enter the chamber");}
        state = ON_PIN_OK;
        n=0;}
      else {state = ON_WITHOUT_PIN;}}
  break;
  case ON_PIN_OK:
    //INFO
    greenLed(1000,5000);
    redLed(0,100);
    AuxiliarTime2 = millis();
    if(percentage < 10) {
      Serial.println("Low Battery");
      state = BATTERY_LOW;}
    else if(stateTemp==2){
      buzzer(100,0);}
    else{
      buzzer(0,100);
      unsigned long CurrentMillis2 = millis() - AuxiliarTime - AuxiliarMillis; 
      timeCamera2 = millis()-AuxiliarTime - AuxiliarMillis;
      timeCamera = CurrentMillis2; 
      timeTotal = timeCamera;
      if(timeCamera > 100){New = 1;}
        if(timeTotal>=timeMax){
          Serial.println("Leave the chamber, daily max reached."); 
          state=EXCESS_EXPOSED_TIME;}
        else if(timeTotal<timeMax && timeCamera>12000){
          for(m;m<1;m++){Serial.println("Time break!");}
          state=EXIT_CAMERA_BREAK;
          m=0; New = 0;
          timeCamera = 0; timeTotal = 0;
          timeMax = timeMax - 12000;}
        else if(timeTotal < timeMax && timeCamera2 < 12000 && stateTemp == 0 && previousStateTemp == 1 && strcmp(PIN,Code2)==0){
          for(g;g<1;g++){Serial.println("Why are you leaving?");}
          state = GO_OUT_WHY;
          redLed(0,100);
          greenLed(0,100);
          g=0; New = 0;
          redLed(0,0);
          greenLed(0,0);}}
              
    
    break;
  case GO_OUT_WHY: 
    doubleLed(500,250);
    if(percentage < 10) {
      Serial.println("Low Battery");
      state = BATTERY_LOW;}
    else if(stateTemp==2){
      buzzer(100,0);}
    else{
      buzzer(0,100);
      unsigned long CurrentMillis3 = millis() - AuxiliarTime;
      timeCamera = CurrentMillis3;
      if(timeTotal < timeMax && timeCamera > 12000){
        for(m;m<1;m++){Serial.println("Time out. Take a break.");} 
        state=EXIT_CAMERA_BREAK;
        m=0;
        timeCamera = 0;
        timeTotal = 0; 
        timeMax = timeMax - 12000;}
      else if (timeTotal>=timeMax){
          Serial.println("Leave the chamber, daily max reached."); 
          state=EXCESS_EXPOSED_TIME;}}
      
  
    break;
  case EXIT_CAMERA_BREAK: //BREAK
    greenLed(0,100);
    redLed(1000,1000);
    buzzer(100,1900);
    timeBreak = millis()-AuxiliarMillis2;
    if(percentage < 10) {
      Serial.println("Low Battery"); 
      state = BATTERY_LOW;}
    else if(timeBreak>3000 && timeTotal<timeMax){
      for(l;l<1;l++){Serial.println("Go back inside");}
      state = ON_PIN_OK;
      l=0; New = 0;
      timeCamera = 0;}
    
  break;
  case EXCESS_EXPOSED_TIME://MAX TIME REACHED
    greenLed(0,100);
    redLed(10,10);
    buzzer(100,0);
    if(percentage < 10) {
      Serial.println("Low battery"); 
      state = BATTERY_LOW;}
    else {state = EXCESS_EXPOSED_TIME;}
    
  break;
  case BATTERY_LOW:
    greenLed(500,1000);
    redLed(1000,1000);
    buzzer(1000,1000);
    
  break;
 default:
    state = ON_WITHOUT_PIN;
  break;
    }
   }
 else{//To test it out the time is defined as: 12 secs per work shift, 3 for the break and 72 as max.
     state = ON_WITHOUT_PIN; 
     i=0;
     timeMax = 72000;
     PIN[0]=0; PIN[1]=0; PIN[2]=0; PIN[3]=0; PIN[4]='F'; 
     buzzer(0,100);
     if(percentage < 94){ 
       redLed(100,0);
       greenLed(0,100);}
     else{
       redLed(0,100);
       greenLed(100,0);  
   } 
 }
}
