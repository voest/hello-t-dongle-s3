#include <Arduino.h>
#include "pin_config.h"
#include "TFT_eSPI.h" // https://github.com/Bodmer/TFT_eSPI

#define GFXFF 1
#define FONT_DELAY 1000

// https://github.com/Bodmer/TFT_eSPI/blob/master/Fonts/GFXFF/print.txt
const GFXfont* FF[] = {
  &FreeMono9pt7b,
  &FreeMonoBold9pt7b,
  &FreeMonoOblique9pt7b,
  &FreeMonoBoldOblique9pt7b,
  &FreeSans9pt7b,
  &FreeSansBold9pt7b,
  &FreeSansOblique9pt7b,
  &FreeSansBoldOblique9pt7b,
  &FreeSerif9pt7b,
  &FreeSerifBold9pt7b,
  &FreeSerifItalic9pt7b,
  &FreeSerifBoldItalic9pt7b,
};
const char* sFF[] = {
  "Mono",
  "Mono bold",
  "Mono oblique",
  "Mono bold oblique",
  "Sans",
  "Sans bold",
  "Sans oblique",
  "Sans bold oblique",
  "Serif",
  "Serif bold",
  "Serif italic",
  "Serif bold italic",
};

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Serial.println("Hello T-Dongle-S3");
  pinMode(TFT_LEDA_PIN, OUTPUT);
  // Initialise TFT
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  digitalWrite(TFT_LEDA_PIN, 0);
}

void loop() {

  // Draw teaser to the top left
  tft.setTextDatum(TL_DATUM);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(1);
  tft.setTextFont(0);
  tft.drawString("All the colors", 0 ,0);

  uint8_t totalFonts = sizeof(sFF) / sizeof(sFF[0]);
  for (uint8_t i = 0; i < totalFonts; i++) {
      // Serial debug infos
      Serial.print("Font ");
      Serial.print(i);
      Serial.print(" of ");
      Serial.print(totalFonts);
      Serial.print(": ");
      Serial.println(sFF[i]);

      // Partially clear screen
      tft.fillRect(0, 32, tft.width(), tft.height() - 32, TFT_BLACK);

      // Pick a random (non-black) foreground color
      tft.setTextColor(default_4bit_palette[random(1, 15)], TFT_BLACK);

      // Draw sample text output in the center of the screen
      tft.setFreeFont(FF[i]);
      tft.setTextSize(1); // size is defined in GFX font definition
      tft.setTextDatum(MC_DATUM);
      tft.drawString("Hello Andi!", tft.width() / 2, tft.height() / 2, GFXFF);

      // Draw font name in the bottom right
      tft.setTextFont(0);
      tft.setTextColor(TFT_GREENYELLOW, TFT_BLACK);
      tft.setTextDatum(BR_DATUM);
      tft.drawString(sFF[i], tft.width(), tft.height());
      delay(FONT_DELAY);
  }

  // Flip da screen
  if (tft.getRotation() == 1) {
    tft.setRotation(3);
  } else {
    tft.setRotation(1);
  }
  tft.fillScreen(TFT_BLACK);

}
