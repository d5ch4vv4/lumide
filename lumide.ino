// HEADER COMMENT: 2DO!

// Include the following before FastLED.h
// to disable pragma messages on compile
#define FASTLED_INTERNAL

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define LED_PIN 5								// Data Pin
#define NUM_LEDS 12							// Number of LEDs
#define BAUD_RATE 9600					// Symbol rate
#define EEPROM_ADDRESS 0				// Memory address


CRGB leds[NUM_LEDS];						// Array to set/clear led data
SoftwareSerial BTSerial(0, 1); 	// RX | TX
char last_color = 'r';					// Default: red
char received = 0;							// Data from Bluetooth

// Used for FX
int fx = 0;										// Default: no moving fx


int currentLed = 0;
int currentLed23 = 0;					// Used in one func, what for?
int hue = 0;									// hue of red is 0?
int fadeAmount = 255;
int fadeAmount23 = 255;
int Chase_Delay = 50;					// Used once?
int Color_Delay = 30;					// Used once?
int delayTime = 30;						// Used twice?
CRGB color = CRGB::White;				//?????
CRGBPalette16 palette = RainbowColors_p;

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

		// Moving Effects
    case '1':
      fx = 1;
      break;
    case '2':
      fx = 2;
      break;
    case '3':
      fx = 3;
      break;
    case '4':
      fx = 4;
      break;
    case '5':
      fx = 5;
      break;
    case '6':
      fx = 6;
      break;
    case '7' :
      fx = 7;
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

    received = BTSerial.read();
		
		// Static one color
    if (received == 'r') {
			EmitMonoColor (CRGB::Red);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Red");
    }
		else if (received == 'g') {
			EmitMonoColor (CRGB::Green);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Green");
    }
		else if (received == 'b') {
			EmitMonoColor (CRGB::Blue);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Blue");
    } 
		else if (received == 'c') {
			EmitMonoColor (CRGB::Cyan);
			UpdateInitials (EEPROM_ADDRESS, received);
      last_color = received; 
      Serial.println("All LEDs are set to Cyan");
    }
		else if (received == 'm') {
			EmitMonoColor (CRGB::Magenta);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Magenta");
    }
		else if (received == 'v') {
			EmitMonoColor (CRGB::Violet);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Violet");
    }
		else if (received == 'o') {
			EmitMonoColor (CRGB::Orange);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Orange");
    }
		else if (received == 'y') {
			EmitMonoColor (CRGB::Yellow);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Yellow");
    }
		else if (received == 'w') {
			EmitMonoColor (CRGB::White);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to White");
    }
		else if (received == 'x') {
			EmitMonoColor (CRGB::Black);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("All LEDs are set to Black");
    }

		// Static two colors
		else if (received == 'q') {
			EmitDualHorizontal (CRGB::Yellow, CRGB::Red);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Yellow/Red");
    }
		else if (received == 'e') {
			EmitDualHorizontal (CRGB::Red, CRGB::Blue);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Red/Blue");
    }
		else if (received == 't') {
			EmitDualHorizontal (CRGB::Blue, CRGB::Green);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Blue/Green");
    }
		else if (received == 'z') {
			EmitDualHorizontal (CRGB::Magenta, CRGB::Red);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Magenta/Red");
    }
		else if (received == 'u') {
			EmitDualHorizontal (CRGB::Red, CRGB::Green);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Red/Green");
    }
		else if (received == 'i') {
			EmitDualHorizontal (CRGB::Yellow, CRGB::Magenta);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("LEDs are set to Yellow/Magenta");
    }

		// Rainbow
		else if (received == 'p'){
			EmitRainbow (leds, NUM_LEDS, 0, 7);
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Rainbow is activated");
			delay(10);
    }

		// Setup for moving Effects
		else if (received == '1') {
			fx = 1;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 1: Upwards moving rainbow");
    }
		else if (received == '2') {
			fx = 2;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 2: Rainbow Lava");
    }
		else if (received == '3'){
			fx = 3;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 3");
    }
		else if (received == '4'){
			fx = 4;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 4");
    }
		else if (received == '5'){
			fx = 5;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 5");
    }
		else if (received == '6'){
			fx = 6;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 6");
    }
		else if (received == '7'){
			fx = 7;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 7");
    }
	}

	// Upwards moving rainbow effect
	if (fx == 1) {
		// CHSV(uint8_t input_hue, uint8_t input_saturation,
		//		  uint8_t input_value)
		// input_value = brightness
		// -> Representation of an HSV pixel
		leds[currentLed] = CHSV(millis() / 7, 255, 255);
		FastLED.show();
		currentLed = (currentLed + 1) % NUM_LEDS;
		delay(50);
	}

	// Rainbow Lava effect
	if (fx == 2){
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

	// Fading through rainbow
	if(fx == 3){
		fadeToBlackBy(leds, NUM_LEDS, 10);
		for (int i = 0; i < NUM_LEDS; i++){
			leds[i] = ColorFromPalette(palette, millis() / 30 + i * 2, 255);
		}
		FastLED.show();
		delay(30);
	}

	// Seems like Effect 3 but faster?
	if (fx == 4){
		static uint8_t hue = 0;							// why defined again?
		for (int i = 0; i < NUM_LEDS; i++){
			leds[i] = CHSV(hue, 255, 255);
		}
		FastLED.show();
		hue++;
		delay(10);
	}

	// Blackening mono color upwards
	if (fx == 5){
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

	// Moving rainbow stripe upwards
	if (fx == 6){
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

	// Blue stripe moving over green one upwards
	if (fx == 7){
		CRGB wipeColor = CRGB::Blue;
		for(int i = 0; i < NUM_LEDS; i++) {
			leds[i] = wipeColor;
			FastLED.show();
			delay(50);
		}

		wipeColor = CRGB::Green;

		for(int i = 0; i < NUM_LEDS; i++) {
			leds[i] = wipeColor;
			FastLED.show();
			delay(50);
		}
	}
}


//--------- FUNCTIONS ---------//


void setMonoColor (CRGB pixel_color) {
// Set all LEDs to a given color
	fx = 0;
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = pixel_color;
	}
}

void setDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
// Set half of LEDs to one color, the other half to another
	fx = 0;
	for (int i = 0; i < NUM_LEDS; i++) {
		if (i >= 0 && i < NUM_LEDS / 2) {
		// Use some factoring variable instead of /2?
			leds[i] = pixel_color_bot;
		}
		else {
			leds[i] = pixel_color_top;
		}
	}
}

void UpdateInitials (int eeprom_address, char value) {
// Update Memory and last_color
	EEPROM.update (eeprom_address, value);
	last_color = value;
}

void EmitMonoColor (CRGB pixel_color) {
// All LEDs emit same color
	setMonoColor (pixel_color);
	FastLED.show();
}

void EmitDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
// Half of LEDs emit one color, other half another
	setDualHorizontal (pixel_color_bot, pixel_color_top);
	FastLED.show();
}

void EmitRainbow (CRGB *target_array, int num_leds, uint8_t initial_hue, uint8_t delta_hue) {
// Emit "Rainbow"
	fx = 0;
	fill_rainbow (target_array, num_leds, initial_hue, delta_hue);
	FastLED.show();
}
