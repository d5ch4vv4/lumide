// HEADER COMMENT: 2DO!

// Include the following before FastLED.h
// to disable pragma messages on compile
#define FASTLED_INTERNAL

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define LED_PIN 5								// Data Pin
#define NUM_LEDS 12
#define BAUD_RATE 9600
#define EEPROM_ADDRESS 0


CRGB leds[NUM_LEDS];						// Array to set/clear led data
CRGB color = CRGB::White;
CRGBPalette16 palette = RainbowColors_p;
boolean animationRunning = true;			// USED FOR WHAT AGAIN?
SoftwareSerial BTSerial(0, 1); // RX | TX
char last_color = 'r';

int currentColor = 0;
int currentLed = 0;
int currentLed23 = 0;					// Used in one func, what for?
int hue = 0;									// hue of red is 0?
int fadeAmount = 255;
int fadeAmount23 = 255;
int Chase_Delay = 50;					// Used once?
int Color_Delay = 30;					// Used once?
int delayTime = 30;						// Used twice?

void setup() {
	// Tell lib about:
	//		- LED strip at DATA_PIN
	//		- Number of LEDs
	// The leds will use the 'leds' array
  FastLED.addLeds<WS2811, LED_PIN, GRB>(leds, NUM_LEDS);
  BTSerial.begin(BAUD_RATE);
  Serial.begin(BAUD_RATE);
  last_color = EEPROM.read(EEPROM_ADDRESS);
  
  // Set up LEDs after Power On
  switch (last_color) {

		// Static one color
		case 'r':
			setMonoColor (CRGB::Red);
			break;
		case 'g':
			setMonoColor (CRGB::Green);
			break;
		case 'b':
			setMonoColor (CRGB::Blue);
			break;
		case 'c':
			setMonoColor (CRGB::Cyan);
			break;
		case 'm':
			setMonoColor (CRGB::Magenta);
			break;
		case 'v':
			setMonoColor (CRGB::Violet);
			break;
		case 'o':
			setMonoColor (CRGB::Orange);
			break;
		case 'y':
			setMonoColor (CRGB::Yellow);
			break;
		case 'w':
			setMonoColor (CRGB::White);
			break;
		case 'x':
			setMonoColor (CRGB::Black);

		// Static two colors
		case 'q':
			setDualHorizontal (CRGB::Yellow, CRGB::Red);
			break;
		case 'e':
			setDualHorizontal (CRGB::Red, CRGB::Blue);
			break;
		case 't':
			setDualHorizontal (CRGB::Blue, CRGB::Green);
			break;
		case 'z':
			setDualHorizontal (CRGB::Magenta, CRGB::Red);
			break;
		case 'u':
			setDualHorizontal (CRGB::Red, CRGB::Green);
			break;
		case 'i':
			setDualHorizontal (CRGB::Yellow, CRGB::Magenta);
			break;

		// Rainbow
    case 'p': {
			int initialHue = 0;
			int deltaHue = 7;
      fill_rainbow(leds, NUM_LEDS, initialHue, deltaHue);
			}
      break;

		// ???	
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

	 // Default
	default:
		setMonoColor (CRGB::Red);
    break;
  }  

	// Update controllers with LED colors
  FastLED.show();
}

void loop() {

  if (BTSerial.available()) {

    char received = BTSerial.read();		// Define at top?

    if (received == 'r') {
			EmitMonoColor (CRGB::Red, 0);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Red");
    }
		else if (received == 'g') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
      }
      currentColor = 1;
      FastLED.show();
      Serial.println("All LEDs are set to Green");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;      
    } else if (received == 'b') {
// Setting LEDs to mono blue
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
      }
      currentColor = 2;
      FastLED.show();
      Serial.println("All LEDs are set to Blue");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'c') {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Cyan;
      }
      currentColor = 3;
      FastLED.show();
      Serial.println("All LEDs are set to Cyan");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received; 
    } else if (received == 'm') {
// Setting LEDs to mono magenta
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Magenta;
      }
      currentColor = 4;
      FastLED.show();
      Serial.println("All LEDs are set to Magenta");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received; 
    } else if (received == 'v') {
// Setting LEDs to mono violet
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Violet;
      }
      currentColor = 5;
      FastLED.show();
      Serial.println("All LEDs are set to Violet");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'o') {
// Setting LEDs to mono orange
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Orange;
      }
      currentColor = 6;
      FastLED.show();
      Serial.println("All LEDs are set to Orange");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'y') {
// Setting LEDs to mono yellow
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
      }
      currentColor = 7;
      FastLED.show();
      Serial.println("All LEDs are set to Yellow");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'w') {
// Setting LEDs to mono white
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::White;
      }
      currentColor = 8;
      FastLED.show();
      Serial.println("All LEDs are set to White");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'q') {
// Setting LEDs to dual yellow red
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
      last_color = received;
    } else if (received == 'e') {
// Setting LEDs to dual red blue
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
      last_color = received;
    } else if (received == 't') {
// Setting LEDs to dual blue green
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
      last_color = received;
    } else if (received == 'z') {
// Setting LEDs to dual magenta red
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
      last_color = received;
    } else if (received == 'u') {
// Setting LEDs to dual red green
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
      last_color = received;
    } else if (received == 'i') {
// Setting LEDs to dual yellow magenta
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
      last_color = received;
    } else if (received == 'p'){
// Setting LEDs to rainbow
      fill_rainbow(leds, NUM_LEDS, 0, 7);
      currentColor = 15;
      FastLED.show();
      delay(10);
      Serial.println("Rainbow is activated");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == 'x') {
// Setting LEDs to black
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Black;
      }
      currentColor = 17;
      FastLED.show();
      Serial.println("All LEDs are set to Black");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '1') {
// Setting up for moving Effects
      currentColor = 18;
      Serial.println("1");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '2') {
      currentColor = 19;
      Serial.println("2");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '3'){
      currentColor = 20;
      Serial.println("3");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '4'){
      currentColor = 21;
      Serial.println("4");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '5'){
      currentColor = 22;
      Serial.println("5");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '6'){
      currentColor = 23;
      Serial.println("6");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;
    } else if (received == '7'){
      currentColor = 24;
      Serial.println("7");
      EEPROM.write(EEPROM_ADDRESS, received);
      last_color = received;      
    }
  }
// ================================
	// Switch the following to cases?

  if(currentColor == 18){
		// CHSV(uint8_t input_hue, uint8_t input_saturation,
		//		  uint8_t input_value)
		// input_value = brightness
		// -> Representation of an HSV pixel
    leds[currentLed] = CHSV(millis() / 7, 255, 255);
    FastLED.show();
    currentLed = (currentLed + 1) % NUM_LEDS;
    delay(50);
  }
/*

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
    static uint8_t hue = 0;							// why defined again?
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

  	if(!animationRunning){				// ???
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
	*/
}

//----- FUNCTIONS -----//

// Needed? Not doing anything?
void stopAnimation(){						// ???
  animationRunning = false;
}

// Set all LEDs to a given color
void setMonoColor (CRGB pixel_color) {
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = pixel_color;
	}
}

// Set half of LEDs to one color, the other half to another
void setDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
	for (int i = 0; i < NUM_LEDS; i++) {
		// Use some factoring variable instead of /2?
		if (i >= 0 && i < NUM_LEDS / 2) {
			leds[i] = pixel_color_bot;
		}
		else {
			leds[i] = pixel_color_top;
		}
	}
}

// All LEDs emit same color
void EmitMonoColor (CRGB pixel_color, int current_color) {
	setMonoColor (pixel_color);
	FastLED.show();
}

// Update Memory and last_color
void UpdateInitials (int eeprom_address, char value) {
	EEPROM.update (eeprom_address, value);
	last_color = value;
}
