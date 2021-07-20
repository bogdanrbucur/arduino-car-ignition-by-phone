/*
Program to read value from Nokia speaker on A0
 
 It works with the melody: 1g1 1g1 1g1 etc with a Tempo of 40 BPM
 
 A 100uF condensator must be placed between ground and A0 on the Arduino to smooth the incoming signal and read it as a continuous beep
 (the phone makes short pauses after each note, which the Arduino would otherwise detect)
 
 To be calibrated for desired time in seconds + a little extra for the capacitor to discharge ~500ms
 
 */

int sensorPin = A0;    // pin connected to the phone's speaker
int ledPin = 13;       // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int n=0;              // duration of the received call in seconds
int ignitionPin = 4;
int starterPin = 5;
int keyPin = A1;       //  check if the car's key has been put in
int neutralPin = A2;   //  check if the gear changer is in NEUTRAL
int keyValue = 0;
int neutralValue = 0;
int t = 0;             // variable used for keeping track of the time the engine is running
int ertValue = 1800;     // Engine Running Time. To be adjusted accordingly, it is the time the engine will run without external input, and then stop (in seconds)
int ert = 0;            // DO NOT TOUCH. Variable used for engine running time calculation. 
boolean keyIn = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT:
  pinMode(ignitionPin, OUTPUT);  // ignition relay command pin
  pinMode(starterPin, OUTPUT);  // starter relay command pin
  pinMode(keyPin, INPUT);
  pinMode(neutralPin, INPUT);
  digitalWrite(ignitionPin, LOW);
  digitalWrite(starterPin, LOW);
  ert = ertValue * 5;           // Because engine status is checked and time variable increased every 0.2 seconds (200ms), we multiply by 5 the ERT to get a 1 second increase per cycle  
}

void loop() {

  digitalWrite(ledPin, LOW);            // set the LED LOW
  sensorValue = analogRead(sensorPin);  // read value from phone speaker

  while(sensorValue > 500)              // checks if the phone is rining. 500 seems to work fine. can be adjusted as needed
  {
    digitalWrite(ledPin, HIGH);           // set the LED HIGH
    delay(1000);                          // wait 1 sec to increment n
    n=n+1;                                // increment n by 1 sec
    //Serial.println(n);                  // serial print n for debugging
    sensorValue = analogRead(sensorPin);  // read the value from speaker again to check if need to exit loop
  }

  digitalWrite(ledPin, LOW);            // when there's no more beep, set LED to LOW

    // checks the duration of the call

  if(n>=3 && n < 30)                     // if n was between 3 and 30 seconds
  {
    neutralValue = analogRead(neutralPin);  // checks if the car is in neutral
    keyValue = analogRead(keyPin);  // checks if the key is in the ignition
    if(keyValue > 200)  // 200 is some random value bigger than 0 because it's an analog input
    {
      keyIn = 1;  // marks the key as being in ignition
    }
    else keyIn = 0;
    if(neutralValue > 400 && keyIn == 0)  // check if the car is in NEUTRAL and if the KEY IS NOT IN IGNITION before starting the engine
    {
      startSequence();         // action to be executed: go to the engine starting sequence
      n=0;                                  // reset n to 0 for the next call
    }
  }
  else n=0;
}

void startSequence()
{
  digitalWrite(ignitionPin, HIGH);  // ignition ON
  delay(3500);  // how long ignition is kept on in ms
  digitalWrite(starterPin, HIGH);  // starter ON
  delay(1700);  // how long starter is kept ON in ms
  digitalWrite(starterPin, LOW);  // starter OFF
  engineRunning();
  t=0;        // reset t to 0 for future use
}

void engineRunning()
{
  while(neutralValue > 400 && t <= ert && keyIn == 0)  // if the car is in neutral, the key is not in and the time has not expired, the engine will keep running 
  {
    neutralValue = analogRead(neutralPin);
    keyValue = analogRead(keyPin);
    if(keyValue > 200)
    {
      keyIn = 1;
    }
    else keyIn = 0;
    t=t+1;  // time counter for engine running
    delay(200);  // 200ms delay between checks
  }
  if(keyIn == 0)                // if the key is not in the ignition within ertValue (1800 sec default), the engine stops
  {
    digitalWrite(starterPin, LOW);    // ignition OFF
  }
}

