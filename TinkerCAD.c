int PinPot1 = 0;
int ValPot1 = 0;
int ValPotMap = 0;
int num[10] = {0x00, 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90};
int redLED = 13;
int yellowLED = 11;
int greenLED = 8;
int pushUp = 3;
int pushDown = 2;
int octaveVal = 0;

void setup()
{
    Serial.begin(9600);
    DDRD = 0xFF;
    pinMode(pushUp, INPUT);   // Button 1
    pinMode(pushDown, INPUT); // Button 2
    pinMode(redLED, OUTPUT);
    pinMode(yellowLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    digitalWrite(redLED, HIGH);
}
void loop()
{
    int buttonStateUp = digitalRead(pushUp);
    int buttonStateDown = digitalRead(pushDown);

    if (buttonStateUp == 1 && octaveVal < 10)
    {
        octaveVal++;
    }
    else if (buttonStateDown == 1 && octaveVal > 0)
    {
        octaveVal--;
    }
    Serial.print("OctaveVal = ");
    Serial.print(octaveVal);
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    ValPotMap = map(ValPot1, 0, 1023, 0, 9);
    ValPot1 = analogRead(PinPot1);
    Serial.println();
    Serial.print("ValPot1 = ");
    Serial.print(ValPot1);
    Serial.println();
    Serial.print("ValPotMap = ");
    Serial.print(ValPotMap); // Returns the value of the potentiometer
    if (ValPotMap == 9)
    {
        digitalWrite(greenLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED, LOW);
    }
    if (ValPotMap == 0)
    {
        digitalWrite(redLED, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(greenLED, LOW);
    }
    Serial.println();
    Serial.println();
    delay(50);
    PORTD = num[ValPotMap];
}