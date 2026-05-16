# 🌡️ ESP32 DHT22 Blynk Monitoring

Sistem monitoring suhu dan kelembaban menggunakan ESP32, sensor DHT22, dan platform Blynk IoT yang ditampilkan pada LCD I2C 16x2.

## 📷 Demo

<!-- Tambahkan foto/video rangkaian kamu di sini -->

## 🛠️ Hardware yang Digunakan

| Komponen | Jumlah |
|---|---|
| ESP32 | 1 |
| Sensor DHT22 | 1 |
| LCD I2C 16x2 | 1 |
| Resistor 10kΩ | 1 |
| Kabel jumper | Secukupnya |
| Breadboard | 1 |

## 📚 Library yang Digunakan

- [Blynk](https://github.com/blynkkk/blynk-library)
- [DHT sensor library](https://github.com/adafruit/DHT-sensor-library)
- [LiquidCrystal I2C](https://github.com/johnrickman/LiquidCrystal_I2C)

## ⚙️ Konfigurasi

### 1. Clone repository ini

```
git clone https://github.com/fauzaanrafi/esp32-dht22-blynk-monitoring.git
```

### 2. Setup secrets

Copy file `include/secrets.example.h` menjadi `include/secrets.h`:

```
cp include/secrets.example.h include/secrets.h
```

Lalu isi dengan kredensial kamu:

```cpp
#define BLYNK_AUTH_TOKEN "your_blynk_token_here"
#define WIFI_SSID        "your_wifi_ssid_here"
#define WIFI_PASS        "your_wifi_password_here"
```

### 3. Setup Blynk

- Buat akun di [Blynk](https://blynk.io)
- Buat template baru dengan nama **monitoring sensor dht11**
- Tambahkan 2 datastream:
  - V5 → Temperature (°C)
  - V6 → Humidity (%)

### 4. Upload ke ESP32

Buka project di PlatformIO, lalu klik **Upload**.

## 📐 Wiring

| DHT22 | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 13 |

| LCD I2C | ESP32 |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

## 🚀 Fitur

- Membaca suhu dan kelembaban setiap 2 detik
- Menampilkan data di LCD I2C 16x2
- Mengirim data ke Blynk IoT secara realtime
- Indikator status koneksi Blynk di LCD
- Credentials aman (tidak hardcode di source code)

## 👤 Author

**fauzaanrafi** - [GitHub](https://github.com/fauzaanrafi)
