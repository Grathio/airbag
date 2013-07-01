/* Sketch for deploying a scratch-built air bag.
   
   Not in any way safe. Don't try this at home. Or at work.
   
   Steve Hoefer
   Steve@Grathio.com

   Licensed under MIT license:
    The MIT License (MIT)
    
    Copyright (c) 2013 Steve Hoefer
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
  
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

int readyLED = 2;         // Green LED, shows power applied and Arduino is ready to go.
int armedLED = 3;         // Orange LED. Pyro igniter connected.
int firedLED = 4;         // Red LED lights when pyro fires.
int reportButton = 5;     // When pressed reports the highest G force recorded via blinking the above LEDs (green=hundreds, orange=tens, red=singes)
int armedSwitch = 6;      // When closed, the igniter is armed. (via a DPDT switch)
int manualSwitch = 7;     // When shorted it triggers the pyro. (Used only for testing.)
int pyroTrigger = 8;      // When high it triggers whatever I'm using to light the charge.
int accelerometerIn = A0; // Accelerometer input. (ADXL193 using Sparkfun's breakout board. #SEN-09332)

int maxG = 0;             // Maxiumum Gs detected since power on.
int triggerG = 11;        // G force required to trigger the switch.
boolean pyroTriggered = false; // True if the pyro has been triggered already. (So we don't keep triggereing it after it's fired.)

unsigned long reportButtonActiveTimer = 0;   // When the "report" button was depressed.
int reportButtonTriggerTime = 1000;  // How long the report button needs to be pressed before reporting. (Reporting takes some time and will disrupt G readings for a bit, so don't di it accidentally.)

void triggerPyro(boolean forceFire = false);  // Prototyping this function up top so I can set a default value.

void setup() {                
  pinMode(readyLED, OUTPUT);   
  digitalWrite(readyLED, LOW);  
  pinMode(armedLED, OUTPUT);     
  digitalWrite(armedLED, LOW);  
  pinMode(firedLED, OUTPUT);     
  digitalWrite(firedLED, LOW);  
  pinMode(reportButton, INPUT);  
  pinMode(armedSwitch, INPUT);  
  pinMode(manualSwitch, INPUT);  
  pinMode(pyroTrigger, OUTPUT);  
  digitalWrite(pyroTrigger, LOW);  
  pinMode(accelerometerIn, INPUT);   

  // Should really run the self test on the accelerometer as well. But we didn't even hook it up.
  
  // Wait a bit for everything to power up and settle down.
  delay(500);
  
  // Ready to go!
  digitalWrite(readyLED, HIGH); 
}

void loop() {
  int currentG = getCurrentGForce();
  
  if (currentG >= triggerG) {
    triggerPyro();    // Do this first since it's the most time sensitive.
  }
  
  digitalWrite(armedLED, digitalRead(armedSwitch));   // Turn on the Armed LED if needed.
  
  if (currentG > maxG){    // Remember the maxiumum G force in case we're currious about it later.
    maxG = currentG;
  }
  
  int now = millis();
  
  // See if the "Report" button is pressed and report if it's been pressed long enough.
  if (digitalRead(reportButton) == HIGH){
    if (reportButtonActiveTimer == 0) {  // Only set this if it wasn't pressed last time we checked.
      reportButtonActiveTimer = now;
    }
    if (now - reportButtonActiveTimer > reportButtonTriggerTime){
      reportMaxGForce(maxG);
      reportButtonActiveTimer = 0;
    }
  } else {
     reportButtonActiveTimer = 0;    // not pressed, reset the timer.
  }
    
  // See if the manual trigger button is pressed.
  if (digitalRead(manualSwitch) == HIGH){
    triggerPyro(true);                      // Force a firing even if it's been triggered before.
  }
  
}

// Returns the current G force reading.
// The ADXL193 returns a value of 2.5V to 5V (2.5 is zero, 5 is 250G) 
// This reads that value and converts it to the associated G reading.
int getCurrentGForce(){
  return  map(analogRead(accelerometerIn), 511, 1023, 0, 250);
}

// Triggers the pyro (If it hasn't been triggered before or of forceFire is true)
void triggerPyro(boolean forceFire){
  if ((forceFire == true) || (pyroTriggered == false)){
    digitalWrite(pyroTrigger, HIGH);
    digitalWrite(firedLED, HIGH);
    delay(500);                        // keep the firing pin high for a bit, just to give it a change to ignite.                   
    digitalWrite(pyroTrigger, LOW);    // And stop trying to trigger it after a bit so if it didn't go off, you can approach it with less worry about when it's going to detonate.
  }
  pyroTriggered = true;
}
 
// Blinks the lights to report a numeric value.
// Green light blinks are the hundreds place
// Orange light blinks the tens place
// Red light blinks the single digits. 
void reportMaxGForce(int reportValue){
  int onTime = 250;
  int offTime = 250;
  int betweenTime = 1000; // Delay between hundreds and tens place, etc.
  int afterTime = 2000;  // Delay after it's been thrown to 
  
  // turn them all off to start with.
  digitalWrite(readyLED, LOW);   
  digitalWrite(armedLED, LOW);    
  digitalWrite(firedLED, LOW);  
  
  delay(betweenTime);
  
  if (reportValue > 0) {
    int hundreds = reportValue/100;
    reportValue = reportValue - (hundreds * 100);
    int tens = reportValue/10;
    reportValue = reportValue - (tens * 10);
    
    // Hundreds.
    for (int i = 0; i<hundreds ;i++){
      digitalWrite(readyLED, HIGH);
      delay(onTime);
      digitalWrite(readyLED, LOW);
      delay(offTime);
    }
    
    delay(betweenTime);
    
    // Tens.
    for (int i = 0; i<tens;i++){
      digitalWrite(armedLED, HIGH);
      delay(onTime);
      digitalWrite(armedLED, LOW);
      delay(offTime);
    }
    
    delay(betweenTime);
    
    // Ones.
    for (int i = 0; i<reportValue;i++){
      digitalWrite(firedLED, HIGH);
      delay(onTime);
      digitalWrite(firedLED, LOW);
      delay(offTime);
    }
  } else { // Zero displays differently so we can tell it from being broken.
    for (int i=0;i<5;i++){
      digitalWrite(readyLED, HIGH);   
      digitalWrite(armedLED, HIGH);
      digitalWrite(firedLED, HIGH);
      delay(100);
      digitalWrite(readyLED, LOW);   
      digitalWrite(armedLED, LOW);
      digitalWrite(firedLED, LOW); 
      delay(100);
    }
  }
  delay(afterTime);
  
  // Return light to their original status.
  digitalWrite(readyLED, HIGH);
  if (pyroTriggered == true){
    digitalWrite(firedLED, HIGH);
  }
  digitalWrite(armedLED, digitalRead(armedSwitch));
}
