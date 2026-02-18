#include <TFT_eSPI.h> 
#include <SPI.h>
#include "graphic.h"  
#include <DHT.h>

// --- HARDWARE SETTINGS ---
#define DHTPIN 4
#define BTN1_PIN 1
#define BTN2_PIN 2
#define BTN3_PIN 5
#define DHTTYPE DHT11

// --- SCREEN SETTINGS ---
#define DIGIT_W 40    
#define DIGIT_H 64    

TFT_eSPI tft = TFT_eSPI(); 
DHT dht(DHTPIN, DHTTYPE);

// Declare array but do NOT initialize here at global scope
// (initializing PROGMEM pointers globally crashes on ESP32-S3)
const unsigned char* myNumbers[10]; 

void setup() {
  Serial.begin(115200);
  delay(1000); 

  // --- 1. MANUALLY LINK IMAGES ---
  // Must be done in setup(), NOT at global scope on ESP32-S3
  myNumbers[0] = epd_bitmap_tempNum0;
  myNumbers[1] = epd_bitmap_tempNum1;
  myNumbers[2] = epd_bitmap_tempNum2;
  myNumbers[3] = epd_bitmap_tempNum3;
  myNumbers[4] = epd_bitmap_tempNum4;
  myNumbers[5] = epd_bitmap_tempNum5;
  myNumbers[6] = epd_bitmap_tempNum6;
  myNumbers[7] = epd_bitmap_tempNum7; 
  myNumbers[8] = epd_bitmap_tempNum8;
  myNumbers[9] = epd_bitmap_tempNum9;

  // --- 2. BACKLIGHT ON ---
  pinMode(38, OUTPUT);
  digitalWrite(38, HIGH);

  // --- 3. INIT HARDWARE ---
  tft.init();
  dht.begin();
  tft.setRotation(0); 
  tft.fillScreen(TFT_BLACK);

  // --- 4. INIT BUTTONS ---
  // Buttons wired between GPIO and GND. LOW = pressed.
  pinMode(BTN1_PIN, INPUT_PULLUP);
  pinMode(BTN2_PIN, INPUT_PULLUP);
  pinMode(BTN3_PIN, INPUT_PULLUP);

  // --- 5. DRAW STATIC INTERFACE ---
  tft.drawBitmap(0, 0, epd_bitmap_bg, 240, 240, TFT_ORANGE, TFT_BLACK);
  tft.drawBitmap(15, 64, epd_bitmap_temp, 85, 30, TFT_ORANGE, TFT_BLACK);
  tft.drawBitmap(15, 149, epd_bitmap_hum, 70, 25, TFT_ORANGE, TFT_BLACK);
}

void loop() {
  float t = dht.readTemperature(); 
  float h = dht.readHumidity();    

  if (isnan(t) || isnan(h)) {
    Serial.println("Waiting for DHT sensor...");
    delay(500);
    return;
  }

  int tempF = (int)((t * 9.0/5.0) + 32); 
  int hum = (int)h;

  Serial.print("Temp F: "); Serial.println(tempF);
  Serial.print("Humidity: "); Serial.println(hum);

  drawMyNumber(tempF, 120, 64); 
  drawMyNumber(hum, 92, 148);

  delay(2000); 
}

void drawMyNumber(int value, int x, int y) {
  if (value > 99) value = 99; 
  if (value < 0) value = 0;   

  int tens = value / 10;      
  int ones = value % 10;      

  tft.drawBitmap(x, y, myNumbers[tens], DIGIT_W, DIGIT_H, TFT_ORANGE, TFT_BLACK);
  tft.drawBitmap(x + DIGIT_W, y, myNumbers[ones], DIGIT_W, DIGIT_H, TFT_ORANGE, TFT_BLACK);
}
