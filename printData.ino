
// prints and loggs all data

void printData() {


  Serial.print(batteryVoltage);
  Serial.print(" , ");

  dataline = String(batteryVoltage );
  dataline += String(",");

  for (int i = 1; i <= 10; i++) {
    Serial.print(solenoidState[i]);
    Serial.print(" , ");
    dataline += String(solenoidState[i]);
    dataline += String(",");
  }


  for (int i = 1; i <= 10; i++) {
    Serial.print(solenoidCurrent[i]);
    Serial.print(" , ");
    dataline += String(solenoidCurrent[i]);
    dataline += String(",");
  }


  Serial.print(v3RegulatorCurrent);
  Serial.print(" , ");
  Serial.print(v5RegulatorCurrent);
  Serial.print(" , ");
  Serial.print(v12RegulatorCurrent);
  Serial.print(" , ");
  dataline += String(v3RegulatorCurrent);
  dataline += String(",");
  dataline += String(v5RegulatorCurrent);
  dataline += String(",");
  dataline += String(v12RegulatorCurrent);
  dataline += String(",");

  for (int i = 1; i <= 10; i++) {
    Serial.print(pressureSensor[i]);
    Serial.print(" , ");
    dataline += String(pressureSensor[i]);
    dataline += String(",");
  }


  for (int i = 1; i <= 4; i++) {
    Serial.print(analogInput[i]);
    Serial.print(" , ");
    dataline += String(analogInput[i]);
    dataline += String(",");
  }

//averages thermocouple readings
avg();

  dataline += String(average);
  dataline += String(",");

  Serial.print(average);
  Serial.print(" , ");

  for (int i = 2; i <= 10; i++) {

    Serial.print(thermocouple[i]);
    Serial.print(" , ");
    dataline += String(thermocouple[i]);
    dataline += String(",");
  }







  Serial.println(counter++);
  dataline += String(counter);

//log to SD card
  logfile.println(dataline);
  logfile.flush();


}
