// Definisikan Library
#include <Wire.h>               
#include <LiquidCrystal_I2C.h>  
#include <DHT.h>                

// Konfigurasi LCD dengan alamat I2C 0x27 dan ukuran 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konfigurasi sensor DHT11
#define DHTPIN 2  
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

// Pin untuk mengontrol relay kipas dan peltier
#define FAN_PIN 7      
#define PELTIER_PIN 8  
// Relay aktif pada logika LOW => LOW (nilai 0). !LOW = 1 = HIGH
#define RELAY_ACTIVE LOW

// Variabel untuk mengatur interval pembacaan sensor
unsigned long previousMillis = 0;
const long interval = 3000;

// Inisialisasi
void setup() {
  Serial.begin(9600);  
  lcd.init();          
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  dht.begin();
  
  pinMode(FAN_PIN, OUTPUT);
  pinMode(PELTIER_PIN, OUTPUT);
  
  // FanDC + Peltier settel
  digitalWrite(FAN_PIN, !RELAY_ACTIVE);
  digitalWrite(PELTIER_PIN, !RELAY_ACTIVE);

  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Mengecek sensor lagi (sesuai waktunya)
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Read sensor
    float suhu = dht.readTemperature();
    float kelembapan = dht.readHumidity();

    // Error message for sensor
    if (isnan(suhu) || isnan(kelembapan)) {
      Serial.println("DHT Sensor Error!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("DHT Error");
      return;
    }

    // Show data suhu & kelembapan to LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(suhu, 1);
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(kelembapan, 0);
    lcd.print("%");

    // Show data suhu & kelembapan di serial monitor
    Serial.print("Suhu: "); Serial.println(suhu);
    Serial.print("Kelembapan: "); Serial.println(kelembapan);

    // Mengontrol FanDC dan peltier base suhu
    if (suhu > 30) {
      digitalWrite(FAN_PIN, RELAY_ACTIVE);
      digitalWrite(PELTIER_PIN, RELAY_ACTIVE);
      Serial.println("Fan: ON | Peltier: ON");
    } else {
      digitalWrite(FAN_PIN, !RELAY_ACTIVE);
      digitalWrite(PELTIER_PIN, !RELAY_ACTIVE);
      Serial.println("Fan: OFF | Peltier: OFF");
    }
  }
}
