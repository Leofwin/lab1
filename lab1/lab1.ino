#include "button.h"
#include "pitches.h"
#include "buzzer.h"

#define R_OUT 7
#define G_OUT 8
#define B_OUT 9

#define PIN_BUZZER 6
#define PIN_BUTTON 5

Button button(PIN_BUTTON);
Buzzer buzzer(PIN_BUZZER);

bool isActivated = false;
int notes[] = {NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_G3, NOTE_SILENCE, NOTE_DS3, NOTE_SILENCE};
double durations[] = {8, 8, 1, 8, 1, 8, 1, 24};
int melodyLength = 8;

void setup()
{
    buzzer.setMelody(notes, durations, melodyLength);
    buzzer.turnSoundOn();

     pinMode(R_OUT, OUTPUT);
     pinMode(G_OUT, OUTPUT);
     pinMode(B_OUT, OUTPUT);
     set_rgb(0, 0, 0);
}

void loop() 
{
    if (button.wasPressed())
    {
        isActivated = true;
        buzzer.turnSoundOn();
        set_rgb(128, 128, 128);
    }

    if (isActivated) {
        buzzer.playSound();
        if (buzzer.isMelodyOver()) {
            isActivated = false;
        }
    }
    else 
    {
        buzzer.turnSoundOff();
        set_rgb(0, 0, 0);
    }
}

void set_rgb(int r, int g, int b)
{
    analogWrite(R_OUT, 255 - r);
    analogWrite(G_OUT, 255 - g);
    analogWrite(B_OUT, 255 - b);
}
