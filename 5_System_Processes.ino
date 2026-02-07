void systemProcesses() {

  readSensors();
  deviceProtection();
  chargingAlgorithm();

  int duty = pwmDuty * 2.55;
  ledcWrite(PWM_CHANNEL, duty);
}
