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
//                8 February Buttons added
//                10 February Changes from meeting notes
//                11 February Tempo Detection
//                11 February Notes playing
//                16 February Detection Test
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
#define pOctaveUp A1
#define pOctaveDown A2
#define pConductorSignal A0

//Outputs
#define pRedLED 4
#define pYellowLED 7
#define pGreenLED 8
//Conductor octave pins 0, 1, 2
#define pSpeaker 11
#define pHeadServo 9
#define pArmServo 10
//hex display pins 5,6,12,13

//Song Parameters
int ConductorOctave = 4;
int MyOctave = 5;
int song_tempo = 250;

//Music Notes
#define C 16.3516
#define D 18.35405
#define E 20.60172
#define F 21.82676
#define G 24.49971
#define A 27.5
#define B 30.86771
#define high_C 32.70320
#define rest 0

//Music Notes
int songLength = 54;  
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};


//Hardware
Servo HeadServo;
Servo ArmServo;

int currentState;
int i_note_index;

void setup()
{
    //LEDs
    pinMode(pRedLED, OUTPUT);
    pinMode(pYellowLED, OUTPUT);
    pinMode(pGreenLED, OUTPUT);
    digitalWrite(pRedLED, HIGH);
    digitalWrite(pYellowLED, HIGH);
    digitalWrite(pGreenLED, HIGH);

    //Octave Selection
    pinMode(pOctaveUp, INPUT);
    pinMode(pOctaveDown, INPUT);
  
    //Conductor Signal
    pinMode(pConductorSignal, INPUT);
  
    //Speaker
    pinMode(pSpeaker, OUTPUT);

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
    digitalWrite(pYellowLED, LOW);
    digitalWrite(pGreenLED, LOW);
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
  int calc1;
  int calc2;
  long t1 = millis();
  while(digitalRead(pConductorSignal) == HIGH) {}
  long t2 = millis();
  while(digitalRead(pConductorSignal) == LOW) {}
  long t3 = millis();
  calc1 = (t2-t1)/2;
  calc2 = t3-t2;
  if(abs(calc1-calc2) <= 5)
    song_tempo = (calc1+calc2)/2;
  Serial.print("Tempo: ");
  Serial.print(song_tempo);
  Serial.print("\n");
  currentState = PLAY;
}

void play()
{
  int duration;
  for(int i = 1; i < 53; i++)
  {
    //play the song
    duration = beats[i] * song_tempo;
    tone(pSpeaker, notes[i]*pow(2,MyOctave), duration);
    delay(duration);
  }
  delay(duration/2);
  currentState = IDLE;
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
      play();
      break;
  }
}
