# 443mhz-RF-relay-command
A step by step tutorial to hacking an existing RF relay with Arduino.
This repo serves as a step-by-step tutorial of my attempts to control some 443 mhz relays I had laying around. In my case: Chacon, ref: 99052, Type: EMW200RC-F.

![Front](https://raw.githubusercontent.com/MrBramme/443mhz-RF-relay-command/master/pics/ChaconFront.jpg)
![Back](https://raw.githubusercontent.com/MrBramme/443mhz-RF-relay-command/master/pics/ChaconBack.jpg)

And I'll be using these cheap 443 mhz modules I bought on ebay:
![Front](https://raw.githubusercontent.com/MrBramme/443mhz-RF-relay-command/master/pics/RFmoduleFront.jpg)
![Back](https://raw.githubusercontent.com/MrBramme/443mhz-RF-relay-command/master/pics/RFmoduleBack.jpg)

# Step 1: Getting the commands from the remote

I'll be using an Arduino Uno (clone) to get read the RF signal.
## Step 1: Add the library RcSwitch
You can find the library here: [rc-switch](https://github.com/sui77/rc-switch)

## Step 2: Hook up the hardware
You can hook up both modules at once, we'll navigate through the scripts to use the proper module based on pin but that way you only have to set it up once (using a breadboard).
Arduino | Receiver
------------ | -------------
5V | 5V
Gnd | Gnd
Digital 2 | Data

Arduino | Transmitter
------------ | -------------
5V | 5V
Gnd | Gnd
Digital 10 | Data


## Step 3: Upload the sketch
Open the example sketch ReceiveDemo_Advanced and upload this to your arduino.

## Step 4: Let's read those commands
Now open up the serial monitor and start pressing buttons on the RC remote. You'll see data being logged to the serial monitor. As you can note, not all lines show the same info. this is caused due to interference etc etc.
Time to cycle all buttons on the remote and record your findings so you know what button sends what commands. To avoid interference I suggest keeping the button pressed for a while and you'll quickly see what commands are the correct ones and which are slightly off.
The major points of interest are the tristate result, pulselength and protocol.
I've only noted the A selector since i'll be using that one, but you can add B and C as well!

## Step 5: Open up the transmit sketch
Next we'll code those commands to be sent! Open up the example sketch SendDemo.

## Step 6: Adjust the sketch to your needs
Replace the existing setup with the one below, note the pulselength, place this AFTER the setprotocol!
```
void setup() {
  Serial.begin(9600);
  // Transmitter is connected to Arduino Pin #10  
  mySwitch.enableTransmit(10);

  mySwitch.setProtocol(1);
  mySwitch.setPulseLength(489);
  mySwitch.setRepeatTransmit(3);
}
```
next modify the loop code as desired. You can also checkout my code in the code folder of this repo.

## the end
This will hopefully help inspire people who are struggling to do the same. This was my first journey into RF :)
