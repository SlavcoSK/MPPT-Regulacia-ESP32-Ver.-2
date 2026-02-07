// ===== BATTERY PROFILES =====

enum BatteryType {
  BAT_LEAD,
  BAT_AGM,
  BAT_GEL,
  BAT_LIFEPO4,
  BAT_LIION
};

BatteryType batteryType = BAT_AGM;

struct BatteryProfile {
  float bulk;
  float absorption;
  float flt;
  float maxCurrent;
  bool useFloat;
};

BatteryProfile batProfiles[] = {
  {14.4, 14.4, 13.6, 20, true},
  {14.6, 14.4, 13.6, 20, true},
  {14.2, 14.2, 13.5, 15, true},
  {14.4, 14.4, 0,   25, false},
  {12.6, 12.6, 0,   15, false}
};

BatteryProfile activeBat;

bool inBulk = true;
bool inAbsorption = false;
bool inFloat = false;
unsigned long absorptionTimer = 0;

float prevPower = 0;
float mpptStep = 0.5;

// ===== MPPT =====
void mpptTrack() {

  float power = voltageInput * currentOutput;

  if (power > prevPower) pwmDuty += mpptStep;
  else pwmDuty -= mpptStep;

  if (pwmDuty > 100) pwmDuty = 100;
  if (pwmDuty < 5) pwmDuty = 5;

  prevPower = power;
}

// ===== CHARGING CONTROL =====
void chargingAlgorithm() {

  activeBat = batProfiles[batteryType];

  // BULK
  if (inBulk) {
    if (voltageOutput < activeBat.bulk) {
      mpptTrack();
    } else {
      inBulk = false;
      inAbsorption = true;
      absorptionTimer = millis();
    }
  }

  // ABSORPTION
  else if (inAbsorption) {

    if (voltageOutput > activeBat.absorption) pwmDuty -= 0.3;

    if (millis() - absorptionTimer > 7200000) {
      inAbsorption = false;
      if (activeBat.useFloat) inFloat = true;
    }
  }

  // FLOAT
  else if (inFloat) {

    if (voltageOutput > activeBat.flt) pwmDuty -= 0.2;
    else pwmDuty += 0.1;
  }

  if (pwmDuty < 0) pwmDuty = 0;
  if (pwmDuty > 100) pwmDuty = 100;
}
