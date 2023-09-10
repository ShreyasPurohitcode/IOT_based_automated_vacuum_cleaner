#include <NewPing.h>


#define BAUDRATE 9600

#define MT1_A    4
#define MT1_EN1  5 
#define MT2_A    6
#define MT2_B    7
#define Flm      A0
#define Vacuum   3

#define TRIG_PIN A1 
#define ECHO_PIN A2 

#define MAX_DISTANCE 300
#define COLL_DIST 30 

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
int curDist = 0;

int cm = 0;
int ivalue;
int temp1 = 0; 
#define Mspeed 100

char command;
bool Status = false;

boolean flag = 0;
boolean flag1 = 0;
unsigned int US1;

//***************************************************************
void setup()
 {
  Serial.begin(BAUDRATE);
  //blue.begin(BAUDRATE);

  pinMode(MT1_A,OUTPUT); pinMode(MT1_EN1,OUTPUT);
  pinMode(MT2_A,OUTPUT); pinMode(MT2_B,OUTPUT);
  pinMode(Vacuum,OUTPUT);
  pinMode(Flm,INPUT);
  Serial.println("Wel-Come");
 }

//***************************************************************
void loop()
 {
  if(Serial.available())
   {
    command = (Serial.read());
    switch(command)
      {
        case 'F': Robot_Forword();  break;
        case 'B': Robot_Reverse();  break;
        case 'L': Robot_Left();     break;
        case 'R': Robot_Right();    break;
        case 'S': Robot_Stop();     break;      
        case 'V': Robot_Vacuum();   break;
        case 'A': Robot_Auto();     break;
      }
   }
//.....................................................
  if(flag == 0)
  {
   US1 = sonar.ping_in();  delay(50);
   if(US1 >= 1 && US1 <= 20)  { Robot_Stop(); } 
  } 
//.....................................................
   if(digitalRead(Flm) == 0 && flag1 == 0)  
   {
    Robot_Stop(); 
    Serial.println("Flame Detected");
    flag1 = 1;
   }
   else if(digitalRead(Flm) == 1 && flag1 == 1)
   {
    Serial.println("No Flame");
    flag1 = 0;
   }
 
 }  // Main Loop
 
//*******************************************************************************
//*******************************************************************************
 void Robot_Forword()
  { 
   if(US1 >= 1 && US1 <= 20)  { Robot_Stop(); Serial.println(US1); }

   else
      {
       digitalWrite(MT1_A, LOW);   analogWrite(MT1_EN1,255);
       digitalWrite(MT2_A, LOW);   digitalWrite(MT2_B, HIGH);
       flag = 0;
      }
  }
//___________________________________________________________
 void Robot_Reverse()
  { 
   digitalWrite(MT1_A, HIGH);   analogWrite(MT1_EN1,0);
   digitalWrite(MT2_A, HIGH);   digitalWrite(MT2_B, LOW);
   flag = 1;
  }
//___________________________________________________________
 void Robot_Right()
  { 
   digitalWrite(MT1_A, HIGH);   analogWrite(MT1_EN1,0);
   digitalWrite(MT2_A, LOW);   digitalWrite(MT2_B, HIGH);
   flag = 1;
  }
//___________________________________________________________
 void Robot_Left()
  { 
   digitalWrite(MT1_A, LOW);   analogWrite(MT1_EN1,255);
   digitalWrite(MT2_A, HIGH);  digitalWrite(MT2_B, LOW);
   flag = 1;
  }
     
//___________________________________________________________
void Robot_Stop()
  { 
   digitalWrite(MT1_A, LOW);   digitalWrite(MT1_EN1, LOW);    
   digitalWrite(MT2_A, LOW);   digitalWrite(MT2_B, LOW);
   flag = 0;
  }    
//**********************************************************
void Robot_Vacuum()
  { 
   digitalWrite(Vacuum, !digitalRead(Vacuum));  
   flag = 0;
  }   
//**********************************************************
void Robot_Auto()
  { 
   while(!Serial.available())
    {
     US1 = sonar.ping_in();  delay(50);
     if(US1 >= 1 && US1 <= 12)  { Robot_Stop(); delay(1000); Robot_Right(); delay(500); }

     digitalWrite(Vacuum,HIGH);
     digitalWrite(MT1_A, LOW);   analogWrite(MT1_EN1,255);
     digitalWrite(MT2_A, LOW);   digitalWrite(MT2_B, HIGH);
    }

   command = (Serial.read());
   switch(command)
      {
        case 'S': Robot_Stop();   break;      
      }
  } 
//**************************************************************
//**************************************************************
