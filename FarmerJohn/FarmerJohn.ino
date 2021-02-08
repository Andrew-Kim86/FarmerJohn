//-----------------------------------------------------
// Team-2B
// Overview
//    The device will listen for a conductor to play
//    Row Row Your Boat, and then also play the song
//    at a different octave synced with the conductor.
// Design Name:   Farmer John
// File Name:     farmerJohn.c
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

//Music Notes
int songLength = 54;  
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};

//Song Parameters
int ConductorOctave = 4;
int MyOctave = 4;
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

//Hardware
Servo HeadServo;
Servo ArmServo;

void setup()
{
    //LEDs
    pinMode(pRedLED, OUTPUT);
    pinMode(pYellowLED, OUTPUT);
    pinMode(pGreenLED, OUTPUT);

    //Octave Selection
    pinMode(pOctaveUp, INPUT);
    pinMode(pOctaveDown, INPUT);

    //Servos
    HeadServo.attatch(pHeadServo);
    ArmServo.attatch(pArmServo);
}

void idle()
{

}

void sync()
{

}

void play()
{

}

void loop() {
  // put your main code here, to run repeatedly:

}
