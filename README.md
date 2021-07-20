# arduino-car-ignition-by-phone
Simple Arduino code to start a car remotely by calling a phone connected to an Arduino Uno installed in the car

Project made by me inteded to be used to start a car remotely by calling a phone connected to an Arduino installed in the car. The idea was to call a phone number only I would know from a purposefully bought pre-paid SIM card, call for a pre-determined period of time and the algorithm would start the car if the transmission was in neutral. If after 30 minutes the key would not be inserted in the ignition, if I wouldn't go to the car, the engine would stop again.

An old Nokia 3410 phone's speaker was connected to the Arduino and using a composed ringtone which consisted of a continous monotonous sound, aided by a capacitor, it produced a continous signal while the phone was ringing which was read by the Arduino as an analog input. The Arduino was to be connected to 2 relays inside the car which would have to be wired to the car:
- For turning on the car ignition
- For turning on the car starter

A magnetic switch would have to be installed on the transmission stick to check if the car was in neutral before starting. While not strictly necessary for the contraption to work, it is included in the code and a good safety measure.

For the car to actually start, the electronic imobilizer would need to see the car key inside so the spare key would need to have been left in the car. Power adapters would also have to have been fashioned in order to continously power the Arduino Uno and the phone.

I have never actually installed the contraption in my Ford Focus because I was afraid of messing with the car's electric system but I have bench tested the system with the realys and everything worked well.
