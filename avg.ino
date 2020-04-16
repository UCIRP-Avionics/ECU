  //For running average on thermcouple
avg(){

  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = thermocouple[1];
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
}
