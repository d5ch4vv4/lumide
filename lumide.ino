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

// uint16_t  num_leds 12				// instead of NUM_LEDS?

CRGB leds[NUM_LEDS];						// Array to set/clear led data
SoftwareSerial BTSerial(0, 1); 	// RX | TX
char last_color = 'r';					// Default: red
char received = 0;							// Data from Bluetooth

// Used for FX
int fx = 0;										// Default: no moving fx
uint8_t initial_hue = 0;
uint8_t hue = 0;								// red?
uint8_t saturation = 255;
uint8_t brightness = 255;
//uint8_t fade_amount = 255;		// instead of fade_amount ?

// Used for "Fading through rainbow"
CRGBPalette16 palette = RainbowColors_p;
uint8_t index = 0;

int current_led = 0;
int fade_amount = 255;
unsigned long color_delay = 30;		// uint32_t ?
unsigned long chase_delay = 50;		// uint32_t ?
int delay_time = 30;						// Used twice?
CRGB wipe_color = CRGB::Blue;

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

		// Static rainbow
    case 'p': {
			int initialHue = 0;
			int deltaHue = 7;
      fill_rainbow(leds, NUM_LEDS, initialHue, deltaHue);
			}
      break;

		// Moving FX
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

/*
  if (BTSerial.available()) {

    received = BTSerial.read();
*/

	// TESTING PURPOSES
	if (true) {
		received = '7';

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

		// Static rainbow
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
      Serial.println("Effect 1: Upward moving rainbow.");
    }
		else if (received == '2') {
			fx = 2;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 2: Downward moving rainbow.");
    }
		else if (received == '3'){
			fx = 3;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 3: Raibow lava.");
    }
		else if (received == '4'){
			fx = 4;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 4: Pulsating rainbow.");
    }
		else if (received == '5'){
			fx = 5;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 5: Pushing colors downward.");
    }
		else if (received == '6'){
			fx = 6;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 6: Rainbow stripe moving upward.");
    }
		else if (received == '7'){
			fx = 7;
			UpdateInitials (EEPROM_ADDRESS, received);
      Serial.println("Effect 7: Colored stripe moves upwards over another.");
    }
	}

	// Upwards moving rainbow
	if (fx == 1) {
		EmitUpwardMovingRainbow (leds);
	}

	// Downward moving rainbow
	if (fx == 2){
		EmitDownwardMovingRainbow (leds);
	}

	// Fading through rainbow
	if(fx == 3) {
		EmitRainbowLava (leds, palette);
	}

	// Pulsating rainbow
	if (fx == 4){
		EmitPulsatingRainbow (leds);
	}

	// Pushing colors upwards
	if (fx == 5){
		EmitPushDownward (leds);
	}

	// Moving rainbow stripe upwards
	if (fx == 6){
		EmitRainbowStripeUpwards (leds);
	}

	// Blue stripe moving over green one upwards
	if (fx == 7){
		EmitUpwardMovingStripes (leds, CRGB::Blue, CRGB::Green);
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

void EmitRainbow (CRGB* target_array, int num_leds, uint8_t initial_hue, uint8_t delta_hue) {
// Emit "Rainbow"
	fx = 0;
	fill_rainbow (target_array, num_leds, initial_hue, delta_hue);
	FastLED.show();
}

void EmitUpwardMovingRainbow (CRGB* target_array) {
	static uint8_t current_led = 0;
	if (current_led > NUM_LEDS)
		current_led	= 0;
	hue = millis() / 7;
	saturation = 255;
	brightness = 255;
	target_array[current_led] = CHSV (hue, saturation, brightness);
	FastLED.show();
	current_led = (current_led + 1) % NUM_LEDS;
	delay(50);
}

void EmitDownwardMovingRainbow (CRGB* target_array) {
	static uint8_t hue = 0;
	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = CHSV (hue + (i * 256 / NUM_LEDS), 255, 255);
	}
	FastLED.show();
	int fade_amount = 255;
	fadeToBlackBy(target_array, NUM_LEDS, fade_amount);
	hue++;
	delay(10);
}

void EmitRainbowLava (CRGB* target_array, CRGBPalette16 palette) {
	int fade_amount = 10;
	fadeToBlackBy(target_array, NUM_LEDS, fade_amount);
	for (int i = 0; i < NUM_LEDS; i++) {
		uint8_t index = millis() / 30 + i *2;
		uint8_t brightness = 255;
		target_array[i] = ColorFromPalette(palette, index, brightness);
	}
	FastLED.show();
	delay(30);
}

void EmitPulsatingRainbow (CRGB* target_array) {
	static uint8_t hue;
	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < NUM_LEDS; i++) {
		target_array[i] = CHSV (hue, 255, 255);
	}
	FastLED.show();
	hue++;
	delay(10);
}

void EmitPushDownward (CRGB* target_array) {
	static uint8_t hue = 0;
	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < NUM_LEDS; i++) {
		saturation = 255;
		brightness = 255;
		target_array[i] = CHSV(hue, saturation, brightness);
	}
	FastLED.show();
	hue += 10;
	color_delay = 30;
	chase_delay = 50;
	delay(color_delay);
	for (int i = 0; i < NUM_LEDS; i++) {
		target_array[i] = CRGB::Black;
		FastLED.show();
		delay(chase_delay);
	}
}

void EmitRainbowStripeUpwards (CRGB* target_array) {
	static uint8_t current_led = 0;
	static uint8_t fade_amount = 255;
	unsigned long delay_time = 30;

	// Fill range of LEDs with a solid color
	fill_solid(target_array, NUM_LEDS, CRGB::Black);
	for (int i = 0; i < NUM_LEDS; i++) {
		hue = millis() / 7;
		saturation = 255;
		brightness = 255;
		target_array[current_led] = CHSV(hue, saturation, brightness);
		FastLED.show();
		delay(delay_time);
		current_led = (current_led + 1) % NUM_LEDS;
		target_array[i] = CRGB::Black;
	}

	// change j to uint8_t limit?
	for (int j = 255; j >= 0; j -= fade_amount) {
		for (int k = 0; k < NUM_LEDS; k++) {
			target_array[k].fadeToBlackBy(fade_amount);
			target_array[k].maximizeBrightness(j);
		}
		FastLED.show();
		delay(delay_time);
	}
}

void EmitUpwardMovingStripes (CRGB* target_array, CRGB pixel_color_1, CRGB pixel_color_2) {
		for(int i = 0; i < NUM_LEDS; i++) {
			leds[i] = pixel_color_1;
			FastLED.show();
			delay(50);
		}

		for(int i = 0; i < NUM_LEDS; i++) {
			leds[i] = pixel_color_2;
			FastLED.show();
			delay(50);
		}
}
