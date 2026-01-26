// ============================================
// KONFIGURAČNÝ SÚBOR PRE MPPT REGULÁTOR
// ============================================

#ifndef CONFIG_H
#define CONFIG_H

// ============================================
// HARDVÉROVÉ NASTAVENIA - GPIO PINTY
// ============================================

#define PWM_PIN 27                 // PWM výstupný pin pre MOSFET
#define PWM_CHANNEL 0              // Číslo PWM kanála ESP32
#define PWM_FREQUENCY 20000        // Frekvencia PWM 20kHz (bez zvuku)
#define PWM_RESOLUTION 10          // Rozlíšenie PWM 10-bit (0-1023)

#define LED_PIN 2                  // Stavová LED dióda
#define ERROR_LED_PIN 4            // LED pre indikáciu chýb
#define BATTERY_DISCONNECT_PIN 14  // Pin pre odpojenie batérie (relé/MOSFET)
#define PANEL_DISCONNECT_PIN 12    // Pin pre odpojenie panelu (relé/MOSFET)
#define TEMP_PIN 34                // Analógový vstup pre teplotný senzor

#define BUTTON_UP_PIN 32           // Tlačidlo HORE pre menu
#define BUTTON_DOWN_PIN 33         // Tlačidlo DOLE pre menu
#define BUTTON_ENTER_PIN 25        // Tlačidlo POTVRDIŤ pre menu
#define BUTTON_BACK_PIN 26         // Tlačidlo SPÄŤ pre menu

// ============================================
// ANALÓGOVÉ SENZORY - NASTAVENIA ADC
// ============================================

#define ADC_SCALE_FACTOR 0.125f    // Konverzný faktor ADS1115 (mV na digit)
#define SHUNT_RESISTOR 0.01f       // Hodnota shunt odporu pre meranie prúdu (Ω)
#define VOLTAGE_DIVIDER_RATIO 5.11f // Pomer deliča napätia (R1=39k, R2=10k)

// ============================================
// BEZPEČNOSTNÉ LIMITY - OCHRANNÉ PARAMETRE
// ============================================

// Batéria - napäťové limity pre AGM batériu 12V
#define BATTERY_VOLTAGE_CRITICAL_HIGH 15.0f  // Absolútne maximum! (V)
#define BATTERY_VOLTAGE_ABSORPTION 14.6f     // Absorpčné napätie (V)
#define BATTERY_VOLTAGE_FLOAT 13.8f          // Plávajúce napätie (V)
#define BATTERY_VOLTAGE_LOW 11.0f            // Varovanie pri nízkom napätí (V)
#define BATTERY_VOLTAGE_CRITICAL_LOW 10.0f   // Kritické minimum (V)
#define BATTERY_VOLTAGE_HYSTERESIS 0.2f      // Hysteréza pre prepínanie stavov (V)

// Prúdové limity - ochrana pred preťažením
#define MAX_CHARGE_CURRENT 5.0f              // Maximálny nabíjací prúd pre AGM (A)
#define MAX_DISCHARGE_CURRENT 30.0f          // Maximálny vybíjací prúd (A)
#define CURRENT_SHORT_CIRCUIT_THRESHOLD 50.0f // Prah pre detekciu zkratu (A)
#define MAX_CURRENT_RISE_RATE 100.0f         // Maximálna povolená rýchlosť nábehu prúdu (A/ms)

// Teplotné limity - ochrana pred prehriatím
#define TEMPERATURE_MAX 70.0f                // Maximálna teplota MOSFETu (°C)
#define TEMPERATURE_WARNING 60.0f            // Varovanie pri vysokej teplote (°C)
#define BATTERY_TEMP_MAX 50.0f               // Maximálna teplota batérie pre nabíjanie (°C)
#define BATTERY_TEMP_MIN -10.0f              // Minimálna teplota batérie pre nabíjanie (°C)

// Panelové napätie - vstupné parametre
#define PANEL_VOLTAGE_MAX 60.0f              // Maximálne vstupné napätie (V)
#define PANEL_VOLTAGE_MIN 10.0f              // Minimálne napätie pre fungovanie (V)

// ============================================
// FILTRE SIGNÁLOV - NASTAVENIA FILTRÁCIE
// ============================================

#define ALPHA_VOLTAGE 0.05f    // Koeficient filtra pre napätie (pomalá odozva)
#define ALPHA_CURRENT 0.1f     // Koeficient filtra pre prúd (stredná odozva)
#define ALPHA_TEMP 0.02f       // Koeficient filtra pre teplotu (veľmi pomalá odozva)

// ============================================
// ČASOVÉ KONŠTANTY PRE TELEMETRIU
// ============================================

#define TELEMETRY_INTERVAL_FAST 1000     // Rýchla telemetria každú sekundu (ms)
#define TELEMETRY_INTERVAL_SLOW 5000     // Pomalá telemetria každých 5 sekúnd (ms)
#define TELEMETRY_INTERVAL_STATS 60000   // Štatistiky každú minútu (ms)

// ============================================
// PRÚDOVÉ PRAHY PRE NABÍJANIE
// ============================================

#define ABSORPTION_CURRENT_THRESHOLD 0.05f  // 5% max prúdu pre koniec absorpcie
#define FLOAT_CURRENT_THRESHOLD 0.02f       // 2% max prúdu pre float režim

// ============================================
// MPPT ALGORITMUS - KONŠTANTY
// ============================================

#define MPPT_STEP_INITIAL 0.01f        // Počiatočná veľkosť kroku MPPT
#define MPPT_STEP_MIN 0.001f           // Minimálna veľkosť kroku MPPT
#define MPPT_UPDATE_INTERVAL_MS 100    // Interval aktualizácie MPPT (ms)

// ============================================
// EEPROM ADRESY PRE UKLADANIE DÁT
// ============================================

#define EEPROM_SIZE 512                    // Celková veľkosť EEPROM
#define TELEMETRY_HISTORY_START 0          // Začiatok histórie telemetrie
#define DAILY_STATS_ADDRESS 400            // Adresa denných štatistík
#define MONTHLY_STATS_ADDRESS 440          // Adresa mesačných štatistík

#endif // CONFIG_H