# Solar Cool Storage

Sistem pendingin penyimpanan berbasis energi surya menggunakan Arduino, sensor DHT11, modul Peltier, dan LCD I2C. Proyek inovasi robotik yang secara otomatis mengontrol suhu ruang penyimpanan menggunakan efek termoelektrik Peltier.

---

## Deskripsi Proyek

Solar Cool Storage adalah sistem pendinginan otomatis yang memanfaatkan energi surya sebagai sumber daya. Sistem ini memantau suhu dan kelembapan secara real-time menggunakan sensor DHT11, lalu mengaktifkan kipas DC dan modul Peltier secara otomatis ketika suhu melebihi ambang batas 30°C.

### Cara Kerja

1. Sensor DHT11 membaca suhu dan kelembapan setiap 3 detik
2. Data ditampilkan pada LCD 16x2 dan Serial Monitor
3. Jika suhu **> 30°C** → relay mengaktifkan kipas DC dan modul Peltier
4. Jika suhu **≤ 30°C** → kipas dan Peltier dimatikan secara otomatis

---

## Komponen yang Dibutuhkan

| Komponen | Jumlah | Keterangan |
|---|---|---|
| Arduino Uno | 1 | Mikrokontroler utama |
| Sensor DHT11 | 1 | Sensor suhu & kelembapan |
| LCD 16x2 I2C | 1 | Alamat I2C: 0x27 |
| Modul Relay 2-Channel | 1 | Aktif LOW |
| Kipas DC | 1 | Terhubung ke relay ch.1 |
| Modul Peltier (TEC1-12706) | 1 | Terhubung ke relay ch.2 |
| Panel Surya + Buck Converter | 1 set | Sumber daya utama |
| Kabel jumper | secukupnya | |
| Breadboard | 1 | |

---

## Skema Wiring

```
DHT11        → Arduino Pin 2
LCD SDA      → Arduino A4
LCD SCL      → Arduino A5
Relay IN1    → Arduino Pin 7  (Kipas DC)
Relay IN2    → Arduino Pin 8  (Peltier)
Relay VCC    → 5V
Relay GND    → GND
```

> ⚠️ Modul Peltier membutuhkan daya yang lebih besar dari output Arduino.
> Gunakan sumber daya eksternal (panel surya + buck converter) untuk menyuplai Peltier dan kipas melalui relay.

---

## Library yang Dibutuhkan

Install library berikut melalui **Arduino IDE → Library Manager**:

- `LiquidCrystal_I2C` by Frank de Brabander
- `DHT sensor library` by Adafruit
- `Adafruit Unified Sensor` by Adafruit
- `Wire` *(built-in Arduino)*

---

## Output Serial Monitor

```
Suhu: 31.50
Kelembapan: 65
Fan: ON | Peltier: ON

Suhu: 28.20
Kelembapan: 70
Fan: OFF | Peltier: OFF
```

---

## Konfigurasi

Ubah nilai berikut di kode sesuai kebutuhan:

```cpp
const long interval = 3000;   // Interval pembacaan sensor (ms)
#define DHTPIN 2              // Pin sensor DHT11
#define FAN_PIN 7             // Pin relay kipas
#define PELTIER_PIN 8         // Pin relay Peltier
// Ubah threshold suhu di baris:
if (suhu > 30) { ... }        // Default: 30°C
```

---

## Struktur Folder

```
solar-cool-storage/
├── solar_cool_storage.ino    # Kode utama Arduino
├── README.md                 # Dokumentasi proyek
└── schematics/               # Gambar skema wiring (tambahkan sendiri)
```

---

## Author
**[RevoFlow]**
STEAM 2025 — Solar Cool Storage  

---

## Lisensi

Proyek ini dilisensikan di bawah [MIT License](LICENSE).  
Bebas digunakan, dimodifikasi, dan didistribusikan dengan mencantumkan kredit kepada pembuat asli.
