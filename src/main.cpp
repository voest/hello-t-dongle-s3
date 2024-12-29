#include <Arduino.h>
#include "pin_config.h"
#include "TFT_eSPI.h" // https://github.com/Bodmer/TFT_eSPI

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Serial.println("Hello T-Dongle-S3");
  pinMode(TFT_LEDA_PIN, OUTPUT);
  // Initialise TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_DARKGREY);
  digitalWrite(TFT_LEDA_PIN, 0);
  tft.setTextFont(2);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("Hallo Andi!", 0, 0);
}

void loop() { // Put your main code here, to run repeatedly:
  Serial.println("Hello Andi!");
  delay(1000);
}