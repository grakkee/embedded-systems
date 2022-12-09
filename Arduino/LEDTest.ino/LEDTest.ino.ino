
#define BLUE 3
#define GREEN 5
#define RED 6

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

}

void loop() {
  updateState(0);
  delay(1000);
  updateState(1);
  delay(1000);
  updateState(2);
  delay(1000);
  updateState(3);
  delay(1000);
}

void updateState(int num) {
  
  switch (num)
    {
    case 0: //disabled
      RBG_color(255, 255, 0); //yellow
      break;

    case 1: //error
      RBG_color(255, 0, 0); //red
      break;

    case 2: //idle
      RBG_color(0, 255, 0); //green
      break;

    case 3: //running
      RBG_color(0, 0, 255); //blue
      break;
    
    default:
      break;
    }
}

void RBG_color(int redValue, int greenValue, int blueValue){
  analogWrite(RED, redValue);
  analogWrite(GREEN, greenValue);
  analogWrite(BLUE, blueValue);
  
}
