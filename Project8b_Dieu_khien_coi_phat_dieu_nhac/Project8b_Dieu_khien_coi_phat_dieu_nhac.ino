/*
Mạch điều khiển đèn còiphátđiệunhạc

Linh kiện:
- Còi
- Arduino Uno

Cách lắp mạch:
- Xem hình

Tác giả: Nhân Nguyễn
Ngày: 03/01/2015
Lịch sử thay đổi
- 03/01/2015 Rev. 1.0
Website: http://papcodientu.com/
*/

#include "pitches.h"

const int coi = 11;
const int cambienPIR = 2;

int melody[] = {
  NOTE_C4, NOTE_D4,NOTE_E4, NOTE_C4, 
  NOTE_C4, NOTE_D4,NOTE_E4, NOTE_C4,
  0, 
  NOTE_E4, NOTE_F4, NOTE_G4,
  NOTE_E4, NOTE_F4, NOTE_G4,
  0,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_C4,
  0,
  NOTE_C4, NOTE_G4, NOTE_C4,
  NOTE_C4, NOTE_G4, NOTE_C4,
  0,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8, 8, 8, 8,
  8, 8, 8, 8,
  8,
  8, 8, 8,
  8, 8, 8,
  8,
  8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8,
  8,
  8, 8, 8,
  8, 8, 8
};

void setup() {
  // coi la cong output
  pinMode(coi, OUTPUT);
  
  // cam bien PIR dau vao
  pinMode(cambienPIR, INPUT);
}

void loop() {
  // doc gia tri tu cam bien PIR
  if (digitalRead(cambienPIR) == HIGH) {
    choiNhac();
  }
  delay(10);
}

void choiNhac() {
 // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < sizeof(melody); thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(coi, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(coi);
  } 
}
