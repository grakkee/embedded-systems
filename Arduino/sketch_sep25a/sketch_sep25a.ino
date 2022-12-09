int btn;
void setup() {
  // put your setup code here, to run once:
  pinMode(A10, INPUT); //Pin PK2
  pinMode(21, OUTPUT); //Pin PD0 LED 1
  pinMode(5, OUTPUT); //Pin PE3 LED 2
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  btn = digitalRead(A10);
  if(btn == 1){
    digitalWrite(21, HIGH);
    digitalWrite(5,LOW);
  } else {
    digitalWrite(21, LOW);
    digitalWrite(5, HIGH);
  }

}
