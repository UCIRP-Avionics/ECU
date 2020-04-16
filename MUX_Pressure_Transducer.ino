//reads pressure sensor data

void pressureSensorRead() {

  //read Mux
  for (int i = 1; i <= 8; i++) {
    pressureSensor[i] = readPressureMux(16 - i);
  }
  pressureSensor[9] = readPressureMux(6);
  pressureSensor[10] = readPressureMux(5);
  for (int i = 1; i <= 4; i++) {
    analogInput[i] = readPressureMux(5 - i);
  }
  batteryVoltage = readPressureMux(0);

}

int readPressureMux(int pressureChannel) {
  int controlPin[] = {ps0, ps1, ps2, ps3};

  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[pressureChannel][i]);
  }

  //read the value at the SIG pin
  int pressureVal = analogRead(pressurePin);//ads.readADC_SingleEnded(pressurePin); 
  //return the value
  return pressureVal;
}
