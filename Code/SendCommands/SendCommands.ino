/*
  using the rc-relay
  https://github.com/MrBramme/443mhz-RF-relay-command
*/

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);
  mySwitch.setProtocol(1);
  mySwitch.setPulseLength(489);
  mySwitch.setRepeatTransmit(4);
}

void loop() {

  sendCommand(0,0,1);
  delay(5000);  
  sendCommand(0,0,0);
  delay(5000);

}

void sendCommand(int selector, int number, int state) {
 // all list are zero based
 // Selector list (A, B, C)
 char* selectorCodes[3] = { "0FF", "F0F", "FF0"};

 // Button number list
 char* buttonCodes[4] = { "0FFFFFFF", "F0FFFFFF", "FF0FFFFF", "FFF0FFFF" };

// State list
 char* stateCodes[2] = { "0", "1" };
 
 // Concatenate into Tri-State command
 char sendCommand[12] = "";
 strcat(sendCommand, selectorCodes[selector]);
 strcat(sendCommand, buttonCodes[number]);
 strcat(sendCommand, stateCodes[state]);

 // Send the code
 Serial.println(sendCommand);
 mySwitch.sendTriState(sendCommand);
}

