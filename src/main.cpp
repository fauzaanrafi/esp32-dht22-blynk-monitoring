#define BLYNK_TEMPLATE_ID "TMPL6JZ0iLhxi"
#define BLYNK_TEMPLATE_NAME "dht22"
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#include "secrets.h"

// Pin & sensor config
#define DHTPIN 13
#define DHTTYPE DHT22

// LCD config
#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

// Blynk virtual pins
#define VPIN_TEMP V5
#define VPIN_HUMI V6

// Objects
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);
BlynkTimer timer;

// Variables
float humi = 0.0;
float temp = 0.0;

// =====================
// Function Declarations
// =====================
void cekKoneksi();
void readDHT22();
void myTimer();

// =====================
// Check Blynk Connection
// =====================
void cekKoneksi() {
  lcd.setCursor(0, 1);
  if (Blynk.connected()) {
    lcd.print("Koneksi Sukses  ");
  } else {
    lcd.print("Koneksi Gagal   ");
  }
}

// =====================
// Read DHT22 Sensor
// =====================
void readDHT22() {
  float newHumi = dht.readHumidity();
  float newTemp = dht.readTemperature();

  if (isnan(newHumi) || isnan(newTemp)) {
    Serial.println("[ERROR] DHT22 tidak terbaca!");
    return;
  }

  humi = newHumi;
  temp = newTemp;

  Serial.printf("[DHT22] Temp: %.1f C, Humi: %.1f %%\n", temp, humi);

  // Update LCD
  lcd.setCursor(0, 1);
  lcd.printf("T=%.1fC H=%.1f%% ", temp, humi);
}

// =====================
// Timer Callback
// =====================
void myTimer() {
  readDHT22();
  Blynk.virtualWrite(VPIN_TEMP, temp);
  Blynk.virtualWrite(VPIN_HUMI, humi);
  cekKoneksi();
}

// =====================
// Setup
// =====================
void setup() {
  Serial.begin(115200);

  // Init LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Monitoring DHT22");
  lcd.setCursor(0, 1);
  lcd.print("Via Blynk IoT   ");
  delay(2000);

  lcd.clear();
  lcd.print("Tunggu Koneksi..");

  // Init Blynk & WiFi
  Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASS);
  cekKoneksi();

  // Init DHT
  dht.begin();
  delay(2000);

  lcd.setCursor(0, 1);
  lcd.print("T=  C, H=   %   ");

  // Set timer interval 2 detik
  timer.setInterval(2000L, myTimer);
}

// =====================
// Loop
// =====================
void loop() {
  Blynk.run();
  timer.run();
}