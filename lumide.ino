#include <FastLED.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define LED_PIN 5
#define NUM_LEDS 12
#define BAUD_RATE 9600
#define EEPROM_ADDRESS 0


CRGB leds[NUM_LEDS];
CRGB color = CRGB::White;
CRGBPalette16 palette = RainbowColors_p;
boolean animationRunning = true;
SoftwareSerial BTSerial(0, 1); // RX | TX
char lastColor = 'r';

int currentColor = 0;
int currentLed = 0;
int currentLed23 = 0;
int hue = 0;
int fadeAmount = 255;
int fadeAmount23 = 255;
int Chase_Delay = 50;
int Color_Delay = 30;
int delayTime = 30;

void setup() {
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  BTSerial.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);
  lastColor = EEPROM.read(EEPROM_ADDRESS);
  switch (lastColor) {
    case 'r':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
      break;
    case 'g':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      break;
    case 'b':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
      }
      break;
    case 'c':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Cyan;
      }
      break;
    case 'm':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Magenta;
      }
      break;
    case 'v':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Violet;
      }
      break;
    case 'o':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Orange;
      }
      break;
    case 'y':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
      }
      break;
    case 'w':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
      }
      break;
    case 'q':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Yellow;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Red;
       }
      }
      break;
    case 'e':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Red;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Blue;
       }
      }
      break;
    case 't':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Blue;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Green;
       }
      }
      break;
    case 'z':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Magenta;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Red;
       }
      }
      break;
    case 'u':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Red;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Green;
       }
      }
      break;
    case 'i':
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 25) {
         leds[i] = CRGB::Yellow;
       }
       else if (i >= 25 && i < 50) {
         leds[i] = CRGB::Magenta;
       }
      }
      break;
    case 'p':
      fill_rainbow(leds, NUM_LEDS, 0, 7);
      break;
    case 'x':
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      break;
    case '1':
      currentColor = 18;
      break;
    case '2':
      currentColor = 19;
      break;
    case '3':
      currentColor = 20;
      break;
    case '4':
      currentColor = 21;
      break;
    case '5':
      currentColor = 22;
      break;
    case '6':
      currentColor = 23;
      break;
    case '7' :
      currentColor = 24;
      break;
   default:
      for (int i = 0; i < NUM_LEDS; i++) {
       leds[i] = CRGB::Red;
     }
     break;
  }  
  FastLED.show();
}

void loop() {
  if (BTSerial.available()) {
    char received = BTSerial.read();
    if (received == 'r') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
      }
      stopAnimation();
      currentColor = 0;
      FastLED.show();
      Serial.println("All LEDs are set to Red");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;      
    } else if (received == 'g') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      currentColor = 1;
      FastLED.show();
      Serial.println("All LEDs are set to Green");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;      
    } else if (received == 'b') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
      }
      currentColor = 2;
      FastLED.show();
      Serial.println("All LEDs are set to Blue");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'c') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Cyan;
      }
      currentColor = 3;
      FastLED.show();
      Serial.println("All LEDs are set to Cyan");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received; 
    } else if (received == 'm') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Magenta;
      }
      currentColor = 4;
      FastLED.show();
      Serial.println("All LEDs are set to Magenta");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received; 
    } else if (received == 'v') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Violet;
      }
      currentColor = 5;
      FastLED.show();
      Serial.println("All LEDs are set to Violet");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'o') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Orange;
      }
      currentColor = 6;
      FastLED.show();
      Serial.println("All LEDs are set to Orange");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'y') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
      }
      currentColor = 7;
      FastLED.show();
      Serial.println("All LEDs are set to Yellow");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'w') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
      }
      currentColor = 8;
      FastLED.show();
      Serial.println("All LEDs are set to White");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'q') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Yellow;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Red;
       }
      }
      currentColor = 9;
      FastLED.show();
      Serial.println("LEDs are set to Yellow/Red");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'e') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Red;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Blue;
       }
      }
      currentColor = 10;
      FastLED.show();
      Serial.println("LEDs are set to Red/Blue");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 't') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Blue;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Green;
       }
      }
      currentColor = 11;
      FastLED.show();
      Serial.println("LEDs are set to Blue/Green");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'z') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Magenta;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Red;
       }
      }
      currentColor = 12;
      FastLED.show();
      Serial.println("LEDs are set to Magenta/Red");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'u') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Red;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Green;
       }
      }
      currentColor = 13;
      FastLED.show();
      Serial.println("LEDs are set to Red/Green");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'i') {
      for (int i = 0; i < NUM_LEDS; i++) {
       if (i >= 0 && i < 6) {
         leds[i] = CRGB::Yellow;
       }
       else if (i >= 6 && i < 12) {
         leds[i] = CRGB::Magenta;
       }
      }
      currentColor = 14;
      FastLED.show();
      Serial.println("LEDs are set to Yellow/Magenta");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'p'){
      fill_rainbow(leds, NUM_LEDS, 0, 7);
      currentColor = 15;
      FastLED.show();
      delay(10);
      Serial.println("Rainbow is activated");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == 'x') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      currentColor = 17;
      FastLED.show();
      Serial.println("All LEDs are set to Black");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '1') {
      currentColor = 18;
      Serial.println("1");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '2') {
      currentColor = 19;
      Serial.println("2");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '3'){
      currentColor = 20;
      Serial.println("3");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '4'){
      currentColor = 21;
      Serial.println("4");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '5'){
      currentColor = 22;
      Serial.println("5");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '6'){
      currentColor = 23;
      Serial.println("6");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;
    } else if (received == '7'){
      currentColor = 24;
      Serial.println("7");
      EEPROM.write(EEPROM_ADDRESS, received);
      lastColor = received;      
    }
  }
  if(currentColor == 18){
    leds[currentLed] = CHSV(millis() / 7, 255, 255);
    FastLED.show();
    currentLed = (currentLed + 1) % NUM_LEDS;
    delay(50);
  }
  if(currentColor == 19){
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 256 / NUM_LEDS), 255, 255);
  }
  FastLED.show();
  hue++;
  if (hue >= 256) {
    hue = 0;
  }
  fadeToBlackBy(leds, NUM_LEDS, fadeAmount);
  delay(10);
  }
  if(currentColor == 20){
    fadeToBlackBy(leds, NUM_LEDS, 10);
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = ColorFromPalette(palette, millis() / 30 + i * 2, 255);
    }
    FastLED.show();
    delay(30);
  }
  if (currentColor == 21){
    static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = CHSV(hue, 255, 255);
    }
    FastLED.show();
    hue++;
    delay(10);
  }
  if (currentColor == 22){
    static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++){
      leds[i] = CHSV(hue, 255, 255);
    }
    FastLED.show();
    hue++;
    delay(Color_Delay);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
      delay(Chase_Delay);
    }
  }
  if (currentColor == 23){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[currentLed23] = CHSV(millis() / 7, 255, 255);
      FastLED.show();
      delay(delayTime);
      currentLed23 = (currentLed23 + 1) % NUM_LEDS;
      leds[i] = CRGB::Black;
    }
    for (int j = 255; j >= 0; j -= fadeAmount23) {
      for (int k = 0; k < NUM_LEDS; k++) {
        leds[k].fadeToBlackBy(fadeAmount23);
        leds[k].maximizeBrightness(j);
      }
      FastLED.show();
      delay(delayTime);
    }
  }
  if (currentColor == 24){
  CRGB wipeColor = CRGB::Blue;
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = wipeColor;
    FastLED.show();
    delay(50);
  }
  if(!animationRunning){
    return;
  }
  wipeColor = CRGB::Green;
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = wipeColor;
    FastLED.show();
    delay(50);
  }
  if(!animationRunning){
    return;
  }
}
}
void stopAnimation(){
  animationRunning = false;
}






