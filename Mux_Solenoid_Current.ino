// reads solenoid current data

void solenoidCurrentRead() {


  //read Mux
  for (int i = 1; i <= 10; i++) {
    if (i % 2 == 0) {
      solenoidCurrent[i] = readCurrentMux(i + 1);
    } else {
      solenoidCurrent[i] = readCurrentMux(i + 3);
    }
  }
  v3RegulatorCurrent = readCurrentMux(13);
  v5RegulatorCurrent = readCurrentMux(14);
  v12RegulatorCurrent = readCurrentMux(15);



}

int readCurrentMux(int currentChannel) {
  int controlPin[] = {ss0, ss1, ss2, ss3};

  //loop through the 4 sig
  for (int i = 0; i < 4; i ++) {
    digitalWrite(controlPin[i], muxChannel[currentChannel][i]);
  }

  //read the value at the SIG pin
  int currentVal = analogRead(ssSignal);
  //return the value
  return currentVal;
}
