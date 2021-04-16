//-----------------------------------------------------
// Engineer: Tim Brothers
// Overview
//    When this device is turned on it plays the song Row
//    Row Row Your Boat.
// Design Name:   The Conductor
// File Name:     conductor.c
//
// Inputs: 
//    Start Switch: switch to start playing the song
//    Volume: controls the volume
//    Tempo: controls the tempo of the song
// Outputs: 
//    Speaker: Used to play the song
//    Tempo Display: Displays the voltage related to the current tempo
//
// History:       4 January 2020 File created
//
//-----------------------------------------------------

#include <stdio.h>
#include <math.h>

#define PwmMax 255

#define rest 0

#define song_tempo 200
#define Octive 4

//Music Notes based on Octive--
#define C 16.3516*pow(2,Octive)
#define D 18.35405*pow(2,Octive)
#define E 20.60172*pow(2,Octive)
#define F 21.82676*pow(2,Octive)
#define G 24.49971*pow(2,Octive)
#define A 27.5*pow(2,Octive)
#define B 30.86771*pow(2,Octive)
#define high_C 32.70320*pow(2,Octive)
#define rest 0

#define speakerPIN 5

//Row Row Row Your Boat
int songLength = 54;  
int notes[] = {C, rest, C, rest, C, rest, D, rest, E, rest, E, rest, D, rest, E, rest, F, rest, G, rest, high_C, rest, high_C, rest, high_C, rest, G, rest, G, rest, G, rest, E, rest, E, rest, E, rest, C, rest, C, rest, C, rest, G, rest, F, rest, E, rest, D, rest, C, rest};
int beats[] = {2,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,1,1,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,5,1};


void setup()
{
  pinMode(A1, INPUT);
  
    //set up outputs
    pinMode(6, OUTPUT);
    
  pinMode(speakerPIN, OUTPUT);
  digitalWrite(6, LOW);
    
  //debug only
  Serial.begin(9600);
    Serial.print("Setup Complete\n");
}
int i_note_index = 0;
void loop()
{
  int duration;                  
  int tempo;
  int tempo_pot;

  tempo = song_tempo;
      
      //play the song
      duration = beats[i_note_index] * tempo;
      if(notes[i_note_index] != rest)
        digitalWrite(6, HIGH);
      tone(speakerPIN, notes[i_note_index], duration);
      delay(duration);
      digitalWrite(6, LOW);
      Serial.print(i_note_index);
      Serial.print("\n");
      //increment the note counter
      ++i_note_index;
      if(i_note_index >= songLength) 
      {
        i_note_index = 0;
      }
  
  
    //block here while the box is closed
  /*while(digitalRead(A1)==0) //check the tilt sensor
  { 
      Serial.print("Waiting for Box to open. Tilt = ");
      Serial.print(digitalRead(A1));
      Serial.print("\n");
      delay(100); // Wait for 100 millisecond(s)
    }
    
    //play the song
    int i_note_index = 0;
    while (digitalRead(A1))
  { 
      tempo = song_tempo;
 
      //play the song
      duration = beats[i_note_index] * tempo;
      if(notes[i_note_index] != rest)
        digitalWrite(6, HIGH);
      tone(speakerPIN, notes[i_note_index], duration);
      delay(duration);
      digitalWrite(6, LOW);
      
      //increment the note counter
      ++i_note_index;
      if(i_note_index >= songLength) 
      {
        i_note_index = 0;
      }
  }*/
}
