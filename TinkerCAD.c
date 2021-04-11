#include <Bounce2.h>

int pin;

Bounce increment = Bounce();
Bounce decrement = Bounce();

int val = 0;

void setup()
{
    increment.attach(A2, INPUT_PULLUP); //Button to increment
    decrement.attach(A1, INPUT_PULLUP); // Button to decrement

    increment.interval(10);
    decrement.interval(10);
    pinMode(5, OUTPUT);  // For CD4511
    pinMode(6, OUTPUT);  // For CD4511
    pinMode(8, OUTPUT);  // For LED
    pinMode(11, OUTPUT); // For Speakers
    pinMode(12, OUTPUT); // For CD4511
    pinMode(13, OUTPUT); // For CD4511
}

void loop()
{
    increment.update();
    decrement.update();

    if (increment.fell() == true && val < 10)
    {
        digitalWrite(8, HIGH); // LED test to see if the LED lights when pushing the top most button
        ++val;
    }
    if (decrement.fell() == true && val > -1)
    {
        digitalWrite(8, LOW); // Turn off the LED
        --val;
    }
    d7seg(val);        // Show the value
    Serial.print(val); // Print the value for test
    tone(11, 200);     // Setting a tone for the Speakers
    //  delay(200);
}
void d7seg(int valor) // Sets individual LED by setting the 4 LED Pins for CD4511
{
    if (val == 0)
    {
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
    }
    if (val == 1)
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
    }
    if (val == 2)
    {
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
        digitalWrite(7, HIGH);
    }
    if (val == 3)
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(5, LOW);
    }
    if (val == 4)
    {
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
    }
    if (val == 5)
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
    }
    if (val == 6)
    {
        digitalWrite(13, LOW);
        digitalWrite(12, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
    }
    if (val == 7)
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
    }
    if (val == 8)
    {
        digitalWrite(13, LOW);
        digitalWrite(12, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
    }
    if (val == 9)
    {
        digitalWrite(13, HIGH);
        digitalWrite(12, LOW);
        digitalWrite(6, LOW);
        digitalWrite(5, HIGH);
    }
}