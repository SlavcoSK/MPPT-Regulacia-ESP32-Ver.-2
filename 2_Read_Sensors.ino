void readSensors() {

  voltageInput  = analogRead(PIN_VIN) * VIN_MULT;
  voltageOutput = analogRead(PIN_VOUT) * VOUT_MULT;
  currentOutput = analogRead(PIN_IOUT) * IOUT_MULT;

  // jednoduchý filter
  voltageInput  = voltageInput * 0.9  + prevVin * 0.1;
  voltageOutput = voltageOutput * 0.9 + prevVout * 0.1;
  currentOutput = currentOutput * 0.9 + prevIout * 0.1;

  prevVin = voltageInput;
  prevVout = voltageOutput;
  prevIout = currentOutput;
}
