/*
 Example sketch for the Addicore Illuminated Arcade Push Button
 The LED in the button will grow brighter then grow dimmer and repeat
 that pattern until the arcade button is pressed then the LED will
 be max brightness until the button is released.
 
 Wiring:
 Arcade Button ---> Arduino
 +LED             5
 -LED             GND
 Sw_1             GND
 Sw_2             6
 
 Created: by Craig Thompson, December 15, 2014
 */

//Arduino pins attached to the arcade button
#define NUM_BUTTONS 6
int arcade_button_LED[NUM_BUTTONS];
int arcade_button[NUM_BUTTONS];

byte LED_value[NUM_BUTTONS];
bool LED_increasing[NUM_BUTTONS];
bool button_press[NUM_BUTTONS];
bool p_button_press[NUM_BUTTONS];

int dimmerSpeed;
bool p_shuffle = false;
bool shuffle = true;

#define shuffle_button 12
// the setup routine runs once when you press reset:
void setupButtons() {
    dimmerSpeed = 5;
    for (int i=0; i<NUM_BUTTONS; i++) {
        
        arcade_button[i] = i*2 +2;
        arcade_button_LED[i] = i*2+1 +2;
        Serial.println(i*2);
        Serial.println(i*2+1);
        pinMode(arcade_button[i], INPUT_PULLUP);        // Enable the pullup resistor on pin 6 for the input from the button's switch
        pinMode(arcade_button_LED[i], OUTPUT);          // Set the pin attached to the arcade button's LED to be an output pin
        
        LED_value[i] = 20*i;
        LED_increasing[i] = true;
        button_press[i] = false;
        analogWrite(arcade_button_LED[i], button_press[i]*255);
    }

    
}

void updateButtons() {
   // bool s = digitalRead(shuffle_button);
   // analogWrite(shuffle_button+1, !s*255);
    //if(!s)Serial.write('r'); // r for shuffle... s is stop!!
    
    updateButton();
    //Serial.println(digitalRead(6));
    //analogWrite(0, digitalRead(6)*255);
}
char buttons[11] = {'a','b','c','d','e','f','g','h','i','j','r'};
void updateButton() {
    for (int i = 0; i<NUM_BUTTONS-1; i++) {
        bool b = !digitalRead(arcade_button[i]);   
        
        if(b && !p_button_press[i]) {
            p_button_press[i] = true;
            button_press[i] = !button_press[i];
            Serial.write(buttons[i]+5*!button_press[i]);
        }
        else if(!b) {
          p_button_press[i] = false;
        }
        analogWrite(arcade_button_LED[i], !button_press[i]*255);
    }
    //shuffle
    button_press[NUM_BUTTONS-1]=!digitalRead(arcade_button[NUM_BUTTONS-1]);  
    analogWrite(arcade_button_LED[NUM_BUTTONS-1], !button_press[NUM_BUTTONS-1]*255);
    if(button_press[NUM_BUTTONS-1])Serial.write('r');
}


void allButtonsOn(){
    for (int i=0; i<NUM_BUTTONS; i++) {
        button_press[i] = false;
        analogWrite(arcade_button_LED[i], 255);    
    } 
    dimmerSpeed = 200;
}


