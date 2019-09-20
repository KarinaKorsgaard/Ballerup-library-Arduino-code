bool buttonState[10];
unsigned long buttonCounter[10];
int motion;
#define motionPin 0
int time, lastTime;
#define SHUFFLE 12
#define SHUFFLE_LIGHT 13
bool p_shuffle;

void setup() {
  Serial.begin(9600);
  
  for(int i = 2; i<12;i++){
     pinMode(i, INPUT_PULLUP);
  }
  pinMode(SHUFFLE, INPUT_PULLUP);

}
char buttons[10] = {'a','b','c','d','e','f','g','h','i','j'};
void loop() {
  for(int i = 2; i < 12; i++){
    // button pins are connected from 2-11
    int buttonID = 9 - (i - 2);
    bool r = digitalRead(i); 

    if(!r && !buttonState[buttonID] && millis() - buttonCounter[buttonID] > 1000) {
      buttonState[buttonID] = true;
      Serial.println(buttons[buttonID]);
      buttonCounter[buttonID] = millis();
    }
    else if(r){
      buttonState[buttonID] = false;
    }
  }
  bool r = digitalRead(SHUFFLE);
  analogWrite(SHUFFLE_LIGHT, !r*255);
  if(!r && !p_shuffle) {
    p_shuffle = true;
    Serial.write('k');
  }
  else if(r){
    p_shuffle = false;
  }
   
 int m = analogRead(motionPin);
 if(abs(motion - m) > 100){
   motion = m; 
   //Serial.println(motion);
   Serial.write('l');
 }
char sRead = Serial.read();
  if(sRead == 'q') { //echo !!
    Serial.write('w');
  }
}
