int speakerPin = 12; //s pin
int len= 11; //num of notes
char notes[ ] = "ccggaagffeeddc"; //string is taken
int beat[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4}; //array declaration
int tmp= 300;

void playTone(int tone, int dur) {
for (long i = 0; i < dur * 1000L; i += tone * 2) {
digitalWrite(speakerPin, HIGH);
delayMicroseconds(tone);
digitalWrite(speakerPin, LOW);
delayMicroseconds(tone);
}
}
void playNote(char note, int dur) {
char names[] = { 'A', 'A', 'B', 'C', 'C', 'D', 'D', 'E','F', 'G', 'G'}; //the inputs are defined
int tones[] = {440,466,494,523,554,587,624,659,749,784,831 }; //based on different ip the frq are defined

// play the tone corresponding to the note name
for (int i = 0; i < 8; i++) //for loop to play tone
{
if (names[i] == note) {
playTone(tones[i], dur);
}
}
}

void setup() //method to setup pin
{
pinMode(speakerPin, OUTPUT);
}

void loop() {
for (int i = 0; i < len; i++) {
if (notes[i] == ' ') {
delay(beat[i] * tmp); //cal the delay function
} else {
playNote(notes[i], beat[i] * tmp); //play note fun
}

// pause between notes
//delay fun
delay(tmp/ 2);
}
}
