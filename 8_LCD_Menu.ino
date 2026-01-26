// Pridajte tieto funkcie na KONIEC súboru:

// ============================================
// MENU OVLÁDACIE FUNKCIE
// ============================================

int getMenuItemsCount() {
  // Vráti počet položiek v aktuálnom menu
  
  switch(currentMenu) {
    case MENU_MAIN:
      return 6;  // Stav, Nabíjanie, Štatistiky, Nastavenia, Systém, Diagnostika
      
    case MENU_SETTINGS:
      return 5;  // Typ batérie, Šetrný režim, Kalibrácia, Reset štatistík, Reboot
      
    case MENU_BATTERY_SETUP:
      return 4;  // AGM, LiFePO4, Olovo, Vlastný
      
    default:
      return 0;  // Ostatné menu nemajú zoznam položiek
  }
}

void toggleLowPowerMode() {
  // Prepnutie šetrného režimu
  
  if (lowPowerMode) {
    exitLowPowerMode();
  } else {
    enterLowPowerMode();
  }
  
  // Aktualizácia displeja
  updateDisplay();
}

void updateDisplayIdle() {
  // Aktualizácia displeja v režime nečinnosti
  
  char buffer[64];
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  // Nadpis
  u8g2.drawStr(0, 0, "MPPT REGULATOR");
  u8g2.drawStr(0, 12, "Stav: NECINNY");
  
  // Batéria
  sprintf(buffer, "Bat: %.1fV", batteryVoltage);
  u8g2.drawStr(0, 25, buffer);
  
  // Panel
  sprintf(buffer, "Panel: %.1fV", panelVoltage);
  u8g2.drawStr(0, 37, buffer);
  
  // Teplota
  sprintf(buffer, "Teplota: %.1fC", temperature);
  u8g2.drawStr(0, 49, buffer);
  
  // Indikátor menu
  u8g2.drawStr(110, 60, "MENU");
  
  u8g2.sendBuffer();
}

void updateDisplayCharging() {
  // Aktualizácia displeja počas nabíjania
  
  char buffer[64];
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  // Nadpis
  u8g2.drawStr(0, 0, "NABIJANIE");
  
  // Fáza
  sprintf(buffer, "Faza: %s", getPhaseName(currentChargePhase).c_str());
  u8g2.drawStr(0, 12, buffer);
  
  // Batéria
  sprintf(buffer, "Bat: %.1fV %.1fA", batteryVoltage, batteryCurrent);
  u8g2.drawStr(0, 25, buffer);
  
  // Panel
  sprintf(buffer, "Panel: %.1fV %.1fW", panelVoltage, panelPower);
  u8g2.drawStr(0, 37, buffer);
  
  // Účinnosť a PWM
  sprintf(buffer, "Ucin: %.1f%%", efficiency);
  u8g2.drawStr(0, 49, buffer);
  
  sprintf(buffer, "PWM: %.1f%%", pwmDutyCycle);
  u8g2.drawStr(70, 49, buffer);
  
  u8g2.sendBuffer();
}

void displayFaultMessage() {
  // Zobrazenie chybového hlásenia na displeji
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  u8g2.drawStr(0, 10, "CHYBOVY STAV!");
  u8g2.drawStr(0, 25, "Skontrolujte:");
  u8g2.drawStr(0, 35, "- Napätie batérie");
  u8g2.drawStr(0, 45, "- Teplotu systému");
  u8g2.drawStr(0, 55, "- Spojenia");
  
  u8g2.sendBuffer();
}

// ============================================
// KONFIGURAČNÉ FUNKCIE
// ============================================

void handleConfigButtons() {
  // Spracovanie tlačidiel v konfiguračnom režime
  
  // Táto funkcia by spracovávala tlačidlá špecificky pre konfiguráciu
  // Momentálne sa používa všeobecná funkcia readButtons()
}

void turnOffDisplay() {
  // Vypnutie displeja
  
  u8g2.clearBuffer();
  u8g2.sendBuffer();
  u8g2.setPowerSave(1);  // Režim úspory energie
}

void turnOnDisplay() {
  // Zapnutie displeja
  
  u8g2.setPowerSave(0);  // Normálny režim
  updateDisplay();
}

// ============================================
// DIAGNOSTICKÉ ZOBRAZENIA
// ============================================

void displayInitScreen() {
  // Zobrazenie inicializačnej obrazovky
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  u8g2.drawStr(0, 20, "Inicializacia...");
  u8g2.drawStr(0, 40, "Prosim cakajte");
  
  u8g2.sendBuffer();
}

void displayTestScreen() {
  // Zobrazenie testovacej obrazovky
  
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  
  u8g2.drawStr(0, 20, "Testovanie...");
  u8g2.drawStr(0, 40, "Prebieha diagnostika");
  
  u8g2.sendBuffer();
}