int ledPinArray[4] = { 29, 30, 31, 32 };
int potPinArray[4] = { A10, A11, A12, A13 };
int switchPinArray[4] = { 33, 34, 35, 36 };
int potValArray[4] = { 0, 0, 0, 0 };
int mappedPotArray[4] = { 0, 0, 0, 0 };

int ratePot = 0;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledPinArray[i], OUTPUT);
    pinMode(potPinArray[i], INPUT);
    pinMode(switchPinArray[i], INPUT);
  }
  pinMode(ratePot, INPUT);
}

void loop() {
  potVal();
  sequence();
}

void potVal() {
  for (int i = 0; i < 4; i++) {
    potValArray[i] = analogRead(potPinArray[i]);
    mappedPotArray[i] = map(potValArray[i], 0, 1023, 60, 73);
  }
}

void sequence() {
  ratePot = analogRead(A14);
  potVal();
  for (int i = 0; i < 4; i++) {
    if (digitalRead(switchPinArray[3]) == HIGH) {
      if (digitalRead(switchPinArray[0]) == HIGH) {
        digitalWrite(ledPinArray[i], HIGH);
        if (digitalRead(switchPinArray[1]) == HIGH) {
          arpeggioMode(mappedPotArray[i] + 12);
        } else if (digitalRead(switchPinArray[2]) == HIGH) {
          chords(mappedPotArray[i] + 12);
        } else {
          usbMIDI.sendNoteOn(mappedPotArray[i] + 12, 127, 1);
          delay(ratePot);
          usbMIDI.sendNoteOff(mappedPotArray[i] + 12, 0, 1);
        }
        digitalWrite(ledPinArray[i], LOW);
        delay(ratePot);
      }
      if (digitalRead(switchPinArray[0]) == LOW) {
        digitalWrite(ledPinArray[i], HIGH);
        if (digitalRead(switchPinArray[1]) == HIGH) {
          arpeggioMode(mappedPotArray[i]);
        } else if (digitalRead(switchPinArray[2]) == HIGH) {
          chords(mappedPotArray[i]);
        } else {
          usbMIDI.sendNoteOn(mappedPotArray[i], 127, 1);
          delay(ratePot);
          usbMIDI.sendNoteOff(mappedPotArray[i], 0, 1);
        }
        digitalWrite(ledPinArray[i], LOW);
        delay(ratePot);
      }
    }
  }
}

void arpeggioMode(int note) {
  ratePot = analogRead(A14);
  usbMIDI.sendNoteOn(note, 127, 1);
  delay(ratePot);
  usbMIDI.sendNoteOff(note, 0, 1);
  delay(ratePot);
  usbMIDI.sendNoteOn(note + 4, 127, 1);
  delay(ratePot);
  usbMIDI.sendNoteOff(note + 4, 0, 1);
  delay(ratePot);
  usbMIDI.sendNoteOn(note + 7, 127, 1);
  delay(ratePot);
  usbMIDI.sendNoteOff(note + 7, 0, 1);
  delay(ratePot);
  usbMIDI.sendNoteOn(note + 12, 127, 1);
  delay(ratePot);
  usbMIDI.sendNoteOff(note + 12, 0, 1);
}

void chords(int note) {
  ratePot = analogRead(A14);
  usbMIDI.sendNoteOn(note, 127, 1);
  usbMIDI.sendNoteOn(note + 4, 127, 1);
  usbMIDI.sendNoteOn(note + 7, 127, 1);
  delay(ratePot);
  usbMIDI.sendNoteOn(note, 0, 1);
  usbMIDI.sendNoteOn(note + 4, 0, 1);
  usbMIDI.sendNoteOn(note + 7, 0, 1);
  delay(ratePot);
}
