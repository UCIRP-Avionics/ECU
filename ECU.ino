#include <SD.h>
#include <SD_t3.h>
#include <SPI.h>



// chipselect for teensy 3.6 sdcard
const int chipSelect = BUILTIN_SDCARD;
// sdcard
File logfile;
String dataline;


//indicator LED
const int led = 13;
const int sled = 0;

//Current Sensor Mux
const int ss0 = 23;
const int ss1 = 22;
const int ss2 = 20;
const int ss3 = 21;
const int ssSignal = A5;

int solenoidCurrent[11];
int v3RegulatorCurrent = 0;
int v5RegulatorCurrent = 0;
int v12RegulatorCurrent = 0;

//Pressure Transducer / Analog Mux
const int ps0 = 27;
const int ps1 = 26;
const int ps2 = 24;
const int ps3 = 25;
const int pressurePin = A22;

int pressureSensor[11];
int analogInput[5];
int batteryVoltage = 0;

//Thermocouple Mux
const int ts0 = 17;
const int ts1 = 16;
const int ts2 = 14;
const int ts3 = 15;
const int thermoPin = A21;

int thermocouple[11];

//Solenoid Pins
const int s1 = 1;
const int s2 = 2;
const int s3 = 3;
const int s4 = 4;
const int s5 = 5;
const int s6 = 6;
const int s7 = 7;
const int s8 = 8;
const int s9 = 9;
const int s10 = 10;

int solenoidState[11];


//Mux Channel Select
const int muxChannel[16][4] = {{0, 0, 0, 0}, {1, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 1}, {1, 0, 0, 1}, {0, 1, 0, 1}, {1, 1, 0, 1}, {0, 0, 1, 1}, {1, 0, 1, 1}, {0, 1, 1, 1}, {1, 1, 1, 1} };
long counter = 0;




//Running Average for thermocouple
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;







void setup() {


  // initialize serial
  Serial.begin(921600);

  // initialize solenoid pins
  for (int i = 0; i <= 10; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  // initial solenoid states
  for (int i = 1; i <= 10; i++) {
    solenoidState[i] = 0;
  }

  // initialize solenoid current sensor mux pins
  for (int i = 20; i <= 23; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  // initialize pressure transducer sensor mux pins
  for (int i = 24; i <= 27; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  // initialize thermocouple sensor mux pins
  for (int i = 14; i <= 17; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  Serial.print("hit");
  // initialize status led
  pinMode(led, OUTPUT);





  //set ADC Resolution (13 bit on board ADC)
  analogReadResolution(12);


 

    // initialize SD Card
    if (!SD.begin(chipSelect)) {
      Serial.println("Card failed, or not present");
    }
    else Serial.println("Card initialized.");


    // create a new file on SD card
    char filename[] = "LOG00.CSV";
    for (int i = 0; i < 100; i++) {
      filename[6] = i / 10 + '0';
      filename[7] = i % 10 + '0';
      if (! SD.exists(filename)) {
        // only open a new file if it doesn't exist
        logfile = SD.open(filename, FILE_WRITE);
        break;
      }
    }
    if (! logfile) {
      Serial.println("couldnt create file");
    }
    Serial.print("Logging to: ");
    Serial.println(filename);

    //CSV starting line
    dataline = String( "Battery Voltage,Solenoid State 1,Solenoid State 2,Solenoid State 3,Solenoid State 4,Solenoid State 5,Solenoid State 6,Solenoid State 7,Solenoid State 8,Solenoid State 9,Solenoid State 10,Solenoid Current 1,Solenoid Current 2,Solenoid Current 3,Solenoid Current 4,Solenoid Current 5,Solenoid Current 6,Solenoid Current 7,Solenoid Current 8,Solenoid Current 9,Solenoid Current 10,3.3V Reg Current,5V Reg Current,12V Reg Current,Pressure Sensor 1,Pressure Sensor 2,Pressure Sensor 3,Pressure Sensor 4,Pressure Sensor 5,Pressure Sensor 6,Pressure Sensor 7,Pressure Sensor 8,Pressure Sensor 9,Pressure Sensor 10,Analog Sensor 1,Analog Sensor 2,Analog Sensor 3,Analog Sensor 4,Thermocouple 1,Thermocouple 2,Thermocouple 3,Thermocouple 4,Thermocouple 5,Thermocouple 6,Thermocouple 7,Thermocouple 8,Thermocouple 9,Thermocouple 10, Cycle #");
    logfile.println(dataline);
    logfile.flush();

//For running average on thermocouple
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}





void loop() {



  digitalWrite(led, HIGH);
  digitalWrite(sled, HIGH);

  //turn on test solenoid
  digitalWrite(s1, solenoidState[1]);

  //Cycle through Mux channels to read all onboard sensors
  solenoidCurrentRead();
  pressureSensorRead();
  thermocoupleRead();

  digitalWrite(sled, LOW);
  digitalWrite(led, LOW);


  //save data to SD card and print to serial
  printData();


  //Serial input
  if (Serial.available()>0)
    if (Serial.read() == 'q') {
      {
        solenoidState[1] = Serial.parseInt();
      }
    }


}
