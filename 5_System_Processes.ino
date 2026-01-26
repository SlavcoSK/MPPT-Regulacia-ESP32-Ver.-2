// Pridajte tieto funkcie na KONIEC súboru:

// ============================================
// INICIALIZAČNÉ FUNKCIE PRE SYSTÉM
// ============================================

void initHardware() {
  // Inicializácia hardvérových komponentov
  
  Serial.println("Inicializujem hardvérové komponenty...");
  
  // Inicializácia I2C komunikácie
  Wire.begin(21, 22);  // SDA=21, SCL=22 pre ESP32
  Serial.println("I2C komunikácia inicializovaná");
  
  // Inicializácia časovačov
  Serial.println("Časovače inicializované");
  
  // Kontrola pamäte
  Serial.print("Voľná pamäť: ");
  Serial.print(ESP.getFreeHeap());
  Serial.println(" bajtov");
}

void initCommunication() {
  // Inicializácia komunikačných rozhraní
  
  Serial.println("Inicializujem komunikačné rozhrania...");
  
  // Sériová komunikácia už je inicializovaná v setup()
  
  // Inicializácia WiFi (ak je potrebná)
  // WiFi.begin() sa volá v initWirelessTelemetry()
  
  Serial.println("Komunikačné rozhrania pripravené");
}

void startInitializationSequence() {
  // Spustenie inicializačnej sekvencie
  
  Serial.println("Štartujem inicializačnú sekvenciu...");
  // Tu by sa spustili rôzne inicializačné kroky
}

void startSelfTest() {
  // Spustenie samotestu
  
  Serial.println("Štartujem samotest systémových komponentov...");
  
  // Test LED
  testLEDs();
  
  // Test PWM
  testPWM();
  
  // Test senzorov
  testSensorCommunication();
  
  Serial.println("Samotest štartovaný");
}

void enterIdleMode() {
  // Vstup do režimu nečinnosti
  
  Serial.println("Vstupujem do režimu nečinnosti...");
  
  // Zníženie spotreby
  setPWM(0.0f);
  
  // Aktualizácia času aktivity
  lastActivityTime = millis();
  
  Serial.println("Režim nečinnosti aktívny");
}

void prepareCharging() {
  // Príprava systému pre nabíjanie
  
  Serial.println("Pripravujem systém pre nabíjanie...");
  
  // Resetovanie MPPT algoritmu
  prevPower = 0.0f;
  prevDuty = 0.0f;
  mpptState = MPPT_SCANNING;
  
  // Nastavenie počiatočnej PWM
  setPWM(1.0f);  // Malá hodnota na začiatok
  
  Serial.println("Systém pripravený na nabíjanie");
}

void handleFaultEntry() {
  // Spracovanie vstupu do chybového stavu
  
  Serial.println("Spracovávam chybový stav...");
  
  // Zastavenie všetkých aktívnych procesov
  emergencyStop();
  
  // Logovanie chyby
  logError("Vstup do chybového stavu");
  
  // Indikácia na displeji
  displayFaultMessage();
}

void enterSleepMode() {
  // Vstup do spánkového režimu
  
  Serial.println("Vstupujem do spánkového režimu...");
  
  // Zaznamenanie času vstupu
  sleepStartTime = millis();
  
  // Minimalizácia spotreby
  setPWM(0.0f);
  setDisplayBrightness(0);
  
  Serial.println("Spánkový režim aktívny");
}

void enterConfigurationMode() {
  // Vstup do konfiguračného režimu
  
  Serial.println("Vstupujem do konfiguračného režimu...");
  
  // Zastavenie aktívnych procesov
  setPWM(0.0f);
  
  // Zobrazenie konfiguračného menu
  displayConfigMenu();
  
  Serial.println("Konfiguračný režim aktívny");
}

// ============================================
// EXIT FUNKCIE PRE STAVY
// ============================================

void cleanupAfterInit() {
  // Čistenie po inicializácii
  
  Serial.println("Čistím dočasné údaje po inicializácii...");
  // Uvoľnenie dočasnej pamäte, resetovanie bufferov, atď.
}

void evaluateSelfTest() {
  // Vyhodnotenie výsledkov samotestu
  
  Serial.println("Vyhodnocujem výsledky samotestu...");
  
  bool allTestsPassed = true;
  
  // Tu by sa kontrolovali výsledky jednotlivých testov
  // a vyhodnocovala sa celková úspešnosť
  
  if (allTestsPassed) {
    Serial.println("Všetky testy prešli úspešne");
  } else {
    Serial.println("Niektoré testy zlyhali");
  }
}

void wakeFromSleep() {
  // Prebudenie zo spánkového režimu
  
  Serial.println("Prebúdzam sa zo spánkového režimu...");
  
  // Obnovenie normálnej činnosti
  setDisplayBrightness(100);
  
  // Resetovanie časovačov
  lastActivityTime = millis();
  
  Serial.println("Systém prebudený");
}

// ============================================
// TESTOVACIE FUNKCIE
// ============================================

void testLEDs() {
  // Test LED indikácie
  
  Serial.println("Testujem LED indikáciu...");
  
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(ERROR_LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(ERROR_LED_PIN, LOW);
    delay(200);
  }
  
  Serial.println("Test LED dokončený");
}

void testPWM() {
  // Test PWM výstupu
  
  Serial.println("Testujem PWM výstup...");
  
  for (int i = 0; i <= 50; i += 10) {
    setPWM(i);
    delay(100);
  }
  
  for (int i = 50; i >= 0; i -= 10) {
    setPWM(i);
    delay(100);
  }
  
  setPWM(0.0f);
  Serial.println("Test PWM dokončený");
}

void testSensorCommunication() {
  // Test komunikácie so senzormi
  
  Serial.println("Testujem komunikáciu so senzormi...");
  
  // Test ADS1115
  if (!ads.begin()) {
    Serial.println("CHYBA: ADS1115 neodpovedá!");
  } else {
    Serial.println("ADS1115 komunikácia OK");
  }
  
  // Test teplotného senzora
  float temp = readRawTemperature();
  if (temp > 100.0f || temp < -20.0f) {
    Serial.println("VAROVANIE: Teplotný senzor mimo rozsahu");
  } else {
    Serial.print("Teplotný senzor OK: ");
    Serial.print(temp, 1);
    Serial.println(" °C");
  }
}

// ============================================
// DISPLEJOVÉ FUNKCIE
// ============================================

void displayConfigMenu() {
  // Zobrazenie konfiguračného menu
  
  Serial.println("Zobrazujem konfiguračné menu...");
  // Implementácia závisí od vášho menu systému
}

void updateDisplayIdle() {
  // Aktualizácia displeja v režime nečinnosti
  
  // Táto funkcia by sa implementovala v LCDMenu.ino
}

void updateDisplayCharging() {
  // Aktualizácia displeja počas nabíjania
  
  // Táto funkcia by sa implementovala v LCDMenu.ino
}

void displayFaultScreen() {
  // Zobrazenie chybovej obrazovky
  
  Serial.println("Zobrazujem chybovú obrazovku...");
  // Implementácia v LCDMenu.ino
}

void displaySleepScreen() {
  // Zobrazenie spánkovej obrazovky
  
  // Implementácia v LCDMenu.ino
}

void displayConfigScreen() {
  // Zobrazenie konfiguračnej obrazovky
  
  // Implementácia v LCDMenu.ino
}

// ============================================
// EMERGENCY FUNKCIE
// ============================================

void emergencyStop() {
  // Okamžité núdzové zastavenie
  
  Serial.println("NÚDZOVÉ ZASTAVENIE!");
  
  // Zastavenie PWM
  ledcWrite(PWM_CHANNEL, 0);
  
  // Odpojenie batérie a panelu
  digitalWrite(BATTERY_DISCONNECT_PIN, LOW);
  digitalWrite(PANEL_DISCONNECT_PIN, LOW);
  
  // Vypnutie všetkých výstupov
  digitalWrite(LED_PIN, LOW);
  digitalWrite(ERROR_LED_PIN, LOW);
}

// ============================================
// KOMUNIKAČNÉ FUNKCIE
// ============================================

void sendFaultNotification() {
  // Odoslanie notifikácie o chybe
  
  Serial.println("Odosielam notifikáciu o chybe...");
  // Tu by sa odoslala správa cez WiFi/Blynk/Serial
}

void saveFaultToLog() {
  // Uloženie chyby do logu
  
  Serial.println("Ukladám chybu do logu...");
  // Implementácia závisí od vášho logovacieho systému
}

bool isActivityDetected() {
  // Detekcia aktivity používateľa
  
  // Skontrolovať tlačidlá
  bool buttonPressed = (digitalRead(BUTTON_UP_PIN) == LOW) ||
                       (digitalRead(BUTTON_DOWN_PIN) == LOW) ||
                       (digitalRead(BUTTON_ENTER_PIN) == LOW) ||
                       (digitalRead(BUTTON_BACK_PIN) == LOW);
  
  // Skontrolovať zmeny v senzoroch
  static float lastPanelPower = 0.0f;
  bool sensorActivity = (abs(panelPower - lastPanelPower) > 0.5f);
  lastPanelPower = panelPower;
  
  return (buttonPressed || sensorActivity);
}

void checkButtons() {
  // Kontrola stavu tlačidiel
  
  // Táto funkcia sa implementuje v LCDMenu.ino
}

void processSerialInput() {
  // Spracovanie vstupu zo sériového portu
  
  // Táto funkcia sa volá z hlavnej slučky
}