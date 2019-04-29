#include <LowPower.h>
#include <pitches.h>

#define NO_SOUND 0 // make the rests in music
//array of notes
int melody[] = {
  /*NOTE_G4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_G4,NO_SOUND,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,
    NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_B3,NOTE_G3,NOTE_C4,NOTE_G3,NOTE_CS4,NOTE_G3,NOTE_C4,NOTE_G3,
    NOTE_E4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_F4,NOTE_E4,NOTE_E4,NOTE_E4,
    NOTE_E4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_G4,NOTE_E4,NOTE_E4,NOTE_E4,*/

  NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_E4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_DS5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_B4,
  NOTE_E4, NOTE_G4, NOTE_DS5, NOTE_D5, NOTE_G4, NOTE_B4,
  NOTE_B4, NOTE_FS5, NOTE_F5, NOTE_B4, NOTE_D5, NOTE_AS5,
  NOTE_A5, NOTE_F5, NOTE_A5, NOTE_DS6, NOTE_D6, NO_SOUND
};

// note duration: 1 = whole note, 2 = half note, 4 = quarter note, 8 = eighth note, etc.
int noteDurations[] = {
  /*8,8,2,8,8,2,16,8,16,8,8,
    2,4,2,4,2,4,2,4,2,4,2,4,2,4,2,4,
    8,16,16,8,4,8,8,8,
    8,16,16,8,4,8,8,8,*/
  8, 16, 16, 8, 4, 8, 8, 8,
  8, 16, 16, 8, 4, 8, 8, 8,
  8, 16, 16, 8, 4, 8, 8, 8,
  8, 16, 16, 8, 4, 8, 8, 8,
  8, 2, 8, 8, 1,
  8, 4, 8, 4, 8, 8,
  8, 8, 4, 8, 4, 8,
  4, 8, 4, 8, 3
};

const int pace = 1450; // change pace of music("speedy")




const int duration = 500;  // 500 miliseconds
const int buzzer_pin = 10;
const int magneticSensorAnalogPin = 2;
const int sec_delay = 1;
const int sec_check_delay = 1;

void setup() {
  Serial.begin(9600);
  pinMode(magneticSensorAnalogPin, INPUT_PULLUP);
}

void alarm() {
  while (true) {
    play_melodey();
    delay(1000);
    if (not shouldBeep()) {
      return;
    }
  }
}
void play_melodey()
{
  for (int Note = 0; Note < 54; Note++) { //counter of Notes (54 limit the array)
    int duration = pace / noteDurations[Note]; //Adjust duration with the pace of music
    tone(buzzer_pin, melody[Note], duration); //Play note

    if (not shouldBeep()) {
      return;
    }
    // to distinguish the notes, set a minimum time between them.
    delay(duration * 1.2);
  }

}

int voltageCheck() {
  return digitalRead(magneticSensorAnalogPin);
}
bool shouldBeep()
{
  int voltageLevel = voltageCheck();
  //  Serial.println(voltageLevel);
  return voltageLevel == HIGH;
}

void loop() {
  if (shouldBeep())
  {
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF,
                  TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF,
                  USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);
    if (shouldBeep()) {
      alarm();
    }
  }

  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF,
                TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF,
                USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER5_OFF, TIMER4_OFF, TIMER3_OFF,
                TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART3_OFF,
                USART2_OFF, USART1_OFF, USART0_OFF, TWI_OFF);
}
