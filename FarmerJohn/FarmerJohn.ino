//-----------------------------------------------------
// Team-2B
// Overview
//    The device will listen for a conductor to play
//    Row Row Your Boat, and then also play the song
//    at a different octave synced with the conductor.
// Design Name:   Farmer John
// File Name:     farmerJohn.ino
//
// Inputs: 
//    Box Tilt Sensor: Tell the Conductor when the box is opened
//    Volume: controls the volume
//    Tempo: controls the tempo of the song
// Outputs: 
//    Servo: Moves the conductor out of the box
//    DC Motor: Waves the conducors baton
//
// History:       8 February 2021 File created
//                8 February Added base conductor params
//
//-----------------------------------------------------
#include <Servo.h>
#include <stdio.h>
#include <math.h>

#define TempoCal 512
#define TempoPotMax 1023
#define PwmMax 255
#define rest 0

//States
#define IDLE 1
#define SYNC 2
#define PLAY 3

//Inputs
#define pOctaveUp 5
#define pOctaveDown 6
#define pConductorSignal 2

//Outputs
#define pRedLED 4
#define pYellowLED 7
#define pGreenLED 8
#define pConductorOctave 12
#define pHeadServo 9
#define pArmServo 10
//hex display/LCD pins

//Song Parameters
int ConductorOctave = 4;
int MyOctave = 5;
int song_tempo = 250;

//Music Notes based on Octave--
double C =  16.3516*pow(2,MyOctave);
double D =  18.35405*pow(2,MyOctave);
double E =  20.60172*pow(2,MyOctave);
double F =  21.82676*pow(2,MyOctave);
double G =  24.49971*pow(2,MyOctave);
double A =  27.5*pow(2,MyOctave);
double B =  30.86771*pow(2,MyOctave);
double high_C =  32.70320*pow(2,MyOctave);

//Music Notes
int songLength = 54;  
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};


//Hardware
Servo HeadServo;
Servo ArmServo;

int currentState;
void setup()
{
    //LEDs
    pinMode(pRedLED, OUTPUT);
    pinMode(pYellowLED, OUTPUT);
    pinMode(pGreenLED, OUTPUT);

    //Octave Selection
    pinMode(pOctaveUp, INPUT);
    pinMode(pOctaveDown, INPUT);
  
    //Conductor Signal
    pinMode(pConductorSignal, INPUT);

    //Servos
    HeadServo.attach(pHeadServo);
    ArmServo.attach(pArmServo);
    HeadServo.write(0);
    ArmServo.write(0);
  
    //State Machine
    currentState = IDLE;

    //Debug
    Serial.begin(9600);
    Serial.print("Setup Complete\n");
    delay(1000);
}

void idle()
{
  if(digitalRead(pOctaveUp) == LOW && ConductorOctave != 9)
  {
    ConductorOctave = ++ConductorOctave%10;
    MyOctave = (ConductorOctave+1)%10;
    Serial.print("Conductor Octave|MyOctave: ");
    Serial.print(ConductorOctave);
    Serial.print(", ");
    Serial.print(MyOctave);
    Serial.print("\n");
    delay(75);
  }
  if(digitalRead(pOctaveDown) == LOW && ConductorOctave != 0)
  {
    ConductorOctave = --ConductorOctave;
    MyOctave = (ConductorOctave+1)%10;
    Serial.print("Conductor Octave|MyOctave: ");
    Serial.print(ConductorOctave);
    Serial.print(", ");
    Serial.print(MyOctave);
    Serial.print("\n");
    delay(75);
  }
  if(digitalRead(pConductorSignal) == HIGH)
  {
    currentState = SYNC;
  }  
}

void sync()
{
  long start = millis();
  while(digitalRead(pConductorSignal) == HIGH) {}
  long end = millis();
  song_tempo = (end-start)/2;
  Serial.print("Tempo: ");
  Serial.print(song_tempo);
  Serial.print("\n");
  currentState = PLAY;
}

void play()
{

}

void loop() {
  // put your main code here, to run repeatedly:
  switch (currentState) 
  {
    case IDLE:
      idle();
      break;
    case SYNC:
      sync();
      break;
    case PLAY:
      break;
  }
}
