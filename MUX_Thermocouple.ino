//reads thermocouple data

void thermocoupleRead() {


  //read Mux
  for (int i = 1; i <= 10; i++) {
    thermocouple[i] = readThermoMux(16 - i);
  }


}

int readThermoMux(int thermoChannel) {
  int controlPin[] = {ts0, ts1, ts2, ts3};

  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[thermoChannel][i]);
  }

  //read the value at the SIG pin

  int thermoVal =analogRead(thermoPin); //ads.readADC_SingleEnded(thermoPin);
  //return the value
  return thermoVal;
}
