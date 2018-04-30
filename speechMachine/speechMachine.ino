
unsigned long timelineMillis = 0;
uint16_t speed;
uint16_t scale; 
int hue;
int saturation;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupButtons();
  setupLeds(144);
  timelineMillis = 0;

  hue = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  char sRead = Serial.read();
  if(sRead == 'b') { //begin !!
    timelineMillis = millis();
  }
  if(sRead == 's') { //stop !!
    timelineMillis = 0;
  }
  if(sRead == 'q') { //echo !!
    Serial.write('w');
  }


  int state = timeline(timelineMillis);
  updateButtons(); // playing and send serial info
  
  if(state != 0){
    allButtonsOn();
  }

    if(state==1){
        colorWipe();
    }
    else if(state==2){
        colorWipe();
    }
    else if(state==3){
        updateLeds(10, 10, hue++, min(saturation++,255));
    }
    else if(state==4){
        updateLeds(30, 100, hue++, min(saturation++,255));
    }
    else if(state==5){
        colorWipe();
    }
    else if(state == 6){
        colorWipe();
    }else{
      updateLeds(10, 100, 0, 0);
    }

  
}



int timeline(unsigned long m){
    int s = 0;
    if(millis()-m>13000)return 0;
    else if(millis()-m>11000)return 6;
    else if(millis()-m>9000)return 5;
    else if(millis()-m>5000)return 4;
    else if(millis()-m>3000)return 3;
    else if(millis()-m>2000)return 2;
    else if(millis()-m>0)return 1;
    return s;
}


