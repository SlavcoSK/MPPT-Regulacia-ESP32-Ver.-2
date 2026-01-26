// Pridajte tieto funkcie na KONIEC súboru (pred poslednú }):

// ============================================
// POMOCNÉ FUNKCIE PRE OCHRANU A RIADENIE
// ============================================

void reduceChargeCurrent() {
  // Táto funkcia redukuje nabíjací prúd pri prekročení limitu
  
  float reduction = 0.1f;  // Redukovať o 10%
  float newLimit = currentProfile->maxChargeCurrent * (1.0f - reduction);
  
  currentProfile->maxChargeCurrent = max(newLimit, 1.0f);  // Minimum 1A
  
  Serial.print("Redukovaný max prúd na: ");
  Serial.print(currentProfile->maxChargeCurrent, 1);
  Serial.println(" A");
}

void disableChargingTemporarily(int ms) {
  // Dočasné zastavenie nabíjania na zadaný čas
  
  Serial.print("Dočasné zastavenie nabíjania na ");
  Serial.print(ms);
  Serial.println(" ms");
  
  setPWM(0.0f);  // Nastaviť PWM na 0%
  
  delay(ms);     // Počkať zadaný čas
  
  Serial.println("Obnovenie nabíjania");
}

void disableCharging() {
  // Úplné zastavenie nabíjania
  
  Serial.println("Úplné zastavenie nabíjania");
  setPWM(0.0f);
  currentChargePhase = PHASE_OFF;
}

void setPWMlimit(float percent) {
  // Nastavenie maximálnej PWM střídy
  
  percent = constrain(percent, 0.0f, 100.0f);
  
  // Ak aktuálna PWM je vyššia ako limit, znížiť ju
  if (pwmDutyCycle > percent) {
    pwmDutyCycle = percent;
    applyPWM(pwmDutyCycle);
  }
  
  Serial.print("Max PWM limit nastavený na: ");
  Serial.print(percent, 1);
  Serial.println("%");
}

void setChargeCurrentLimit(float current) {
  // Nastavenie limitu nabíjacieho prúdu
  
  current = constrain(current, 0.1f, 30.0f);  // Rozsah 0.1-30A
  currentProfile->maxChargeCurrent = current;
  
  Serial.print("Limit nabíjacieho prúdu nastavený na: ");
  Serial.print(current, 1);
  Serial.println(" A");
}

void switchToFloatMode() {
  // Prechod do plávajúceho (float) režimu nabíjania
  
  Serial.println("Prechod do plávajúceho režimu nabíjania");
  currentChargePhase = PHASE_FLOAT;
  floatStartTime = millis();
}

// ============================================
// PWM OVLÁDACIE FUNKCIE
// ============================================

void applyPWM(float dutyPercent) {
  // Aplikovanie PWM střídy na hardvér
  
  int pwmValue = (int)(dutyPercent * 10.23f);  // Konverzia na 10-bit (0-1023)
  pwmValue = constrain(pwmValue, 0, 1023);
  
  ledcWrite(PWM_CHANNEL, pwmValue);
  
  // Debug výpis (voliteľné)
  /*
  static float lastDuty = -1.0f;
  if (abs(dutyPercent - lastDuty) > 0.1f) {
    Serial.print("PWM nastavené na: ");
    Serial.print(dutyPercent, 1);
    Serial.print("% (");
    Serial.print(pwmValue);
    Serial.println(")");
    lastDuty = dutyPercent;
  }
  */
}

void setPWM(float dutyPercent) {
  // Nastavenie PWM střídy (s ochranou)
  
  dutyPercent = constrain(dutyPercent, 0.0f, 95.0f);  // Max 95% pre bezpečnosť
  
  pwmDutyCycle = dutyPercent;
  applyPWM(dutyPercent);
}

// ============================================
// ŠETRNÝ REŽIM - POMOCNÉ FUNKCIE
// ============================================

void setMeasurementInterval(unsigned long interval) {
  // Nastavenie intervalu meraní (pre šetrný režim)
  
  Serial.print("Interval meraní nastavený na: ");
  Serial.print(interval);
  Serial.println(" ms");
  // Táto funkcia by ovplyvnila hlavnú slučku, implementácia závisí od vášho kódu
}

void setDisplayBrightness(int percent) {
  // Nastavenie jasu displeja
  
  percent = constrain(percent, 0, 100);
  
  // Pre OLED displej s reguláciou jasu
  // u8g2.setContrast(percent * 2.55);  // 0-100 -> 0-255
  
  Serial.print("Jas displeja nastavený na: ");
  Serial.print(percent);
  Serial.println("%");
}

void disableNonEssentialPeripherals() {
  // Vypnutie nepodstatných periférií pre šetrenie energie
  
  Serial.println("Vypínam nepodstatné periférie...");
  // Tu by sa vypínali veci ako Bluetooth, nepotrebné GPIO, atď.
}

void enablePeripherals() {
  // Zapnutie periférií
  
  Serial.println("Zapínam všetky periférie...");
}

void disconnectFromBattery() {
  // Odpojenie od batérie (ak hardvér umožňuje)
  
  digitalWrite(BATTERY_DISCONNECT_PIN, LOW);
  Serial.println("Odpojené od batérie");
}

void connectToBattery() {
  // Pripojenie k batérii
  
  digitalWrite(BATTERY_DISCONNECT_PIN, HIGH);
  Serial.println("Pripojené k batérii");
}

// ============================================
// KALIBRÁCIA A DIAGNOSTIKA
// ============================================

void savePhaseStatistics(ChargePhase phase) {
  // Uloženie štatistík pre ukončenú fázu
  
  Serial.print("Ukladám štatistiky pre fázu: ");
  Serial.println(getPhaseName(phase));
  // Tu by sa ukladali štatistiky do EEPROM
}

void saveSystemState() {
  // Uloženie stavu systému pred deep sleep
  
  Serial.println("Ukladám stav systému do EEPROM...");
  // Implementácia závisí od vášho ukladacieho mechanizmu
}

void loadSystemState() {
  // Načítanie stavu systému po prebudení
  
  Serial.println("Načítavam stav systému z EEPROM...");
}

void setupWakeupInterrupt() {
  // Nastavenie interruptu pre prebudenie zo spánku
  
  Serial.println("Nastavujem interrupt pre prebudenie...");
  // Pre ESP32: esp_sleep_enable_ext0_wakeup(), atď.
}