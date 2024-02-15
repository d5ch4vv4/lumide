// HEADER COMMENT: 2DO!

#define FASTLED_INTERNAL // Include to disable pragma message

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

const byte num_leds = 18;
const char eeprom_address = 0;	// Memory Address
CRGB leds[num_leds];						// Array to set/clear led data
SoftwareSerial BTSerial(0, 1); 	// RX | TX
char last_color = 'r';					// Default: red
byte fx = 0;										// Default: no moving fx

void setup() {
	const byte led_pin = 5;				// Data Pin
	const word baud_rate = 9600;	// Symbol rate

  FastLED.addLeds<WS2811, led_pin, GRB>(leds, num_leds);
  BTSerial.begin(baud_rate);
  Serial.begin(baud_rate);
  last_color = EEPROM.read(eeprom_address);
  
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
			SetDualHorizontal (CRGB::Yellow, CRGB::Red);
			break;
		case 'e':
			SetDualHorizontal (CRGB::Red, CRGB::Blue);
			break;
		case 't':
			SetDualHorizontal (CRGB::Blue, CRGB::Green);
			break;
		case 'z':
			SetDualHorizontal (CRGB::Magenta, CRGB::Red);
			break;
		case 'u':
			SetDualHorizontal (CRGB::Red, CRGB::Green);
			break;
		case 'i':
			SetDualHorizontal (CRGB::Yellow, CRGB::Magenta);
			break;

		// Static rainbow
    case 'p':
			SetRainbow ();
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
	char received = 0;							// Data from Bluetooth

  if (BTSerial.available()) {

    received = BTSerial.read();

/*
	// TESTING PURPOSES
	if (true) {
		received = '5';
*/

		// Static one color
    if (received == 'r') {
			EmitMonoColor (CRGB::Red);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Red");
    }
		else if (received == 'g') {
			EmitMonoColor (CRGB::Green);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Green");
    }
		else if (received == 'b') {
			EmitMonoColor (CRGB::Blue);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Blue");
    } 
		else if (received == 'c') {
			EmitMonoColor (CRGB::Cyan);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Cyan");
    }
		else if (received == 'm') {
			EmitMonoColor (CRGB::Magenta);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Magenta");
    }
		else if (received == 'v') {
			EmitMonoColor (CRGB::Violet);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Violet");
    }
		else if (received == 'o') {
			EmitMonoColor (CRGB::Orange);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Orange");
    }
		else if (received == 'y') {
			EmitMonoColor (CRGB::Yellow);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Yellow");
    }
		else if (received == 'w') {
			EmitMonoColor (CRGB::White);
			UpdateInitials (received);
      Serial.println("All LEDs are set to White");
    }
		else if (received == 'x') {
			EmitMonoColor (CRGB::Black);
			UpdateInitials (received);
      Serial.println("All LEDs are set to Black");
    }

		// Static two colors
		else if (received == 'q') {
			EmitDualHorizontal (CRGB::Yellow, CRGB::Red);
			UpdateInitials (received);
      Serial.println("LEDs are set to Yellow/Red");
    }
		else if (received == 'e') {
			EmitDualHorizontal (CRGB::Red, CRGB::Blue);
			UpdateInitials (received);
      Serial.println("LEDs are set to Red/Blue");
    }
		else if (received == 't') {
			EmitDualHorizontal (CRGB::Blue, CRGB::Green);
			UpdateInitials (received);
      Serial.println("LEDs are set to Blue/Green");
    }
		else if (received == 'z') {
			EmitDualHorizontal (CRGB::Magenta, CRGB::Red);
			UpdateInitials (received);
      Serial.println("LEDs are set to Magenta/Red");
    }
		else if (received == 'u') {
			EmitDualHorizontal (CRGB::Red, CRGB::Green);
			UpdateInitials (received);
      Serial.println("LEDs are set to Red/Green");
    }
		else if (received == 'i') {
			EmitDualHorizontal (CRGB::Yellow, CRGB::Magenta);
			UpdateInitials (received);
      Serial.println("LEDs are set to Yellow/Magenta");
    }

		// Static rainbow
		else if (received == 'p'){
			EmitRainbow ();
			UpdateInitials (received);
      Serial.println("Rainbow is activated");
    }

		// Setup for moving Effects
		else if (received == '1') {
			fx = 1;
			UpdateInitials (received);
      Serial.println("Effect 1: Emit upward moving rainbow.");
    }
		else if (received == '2') {
			fx = 2;
			UpdateInitials (received);
      Serial.println("Effect 2: Emit downward moving rainbow.");
    }
		else if (received == '3'){
			fx = 3;
			UpdateInitials (received);
      Serial.println("Effect 3: Emit lava-like effect (rainbow colors).");
    }
		else if (received == '4'){
			fx = 4;
			UpdateInitials (received);
      Serial.println("Effect 4: Emit pulsating rainbow.");
    }
		else if (received == '5'){
			fx = 5;
			UpdateInitials (received);
      Serial.println("Effect 5: Emit a color pushing darkness away.");
    }
		else if (received == '6'){
			fx = 6;
			UpdateInitials (received);
      Serial.println("Effect 6: Emit stripe moving upward (rainbow).");
    }
		else if (received == '7'){
			fx = 7;
			UpdateInitials (received);
      Serial.println("Effect 7: Colored stripe moves upwards over another.");
    }
	}

	// Moving FX:
	if (fx == 1) {
		EmitUpwardMovingRainbow ();
	}
	if (fx == 2){
		EmitDownwardMovingRainbow ();
	}
	if (fx == 3) {
		EmitRainbowLava ();
	}
	if (fx == 4){
		EmitPulsatingRainbow ();
	}
	if (fx == 5){
		EmitPushDownward ();
	}
	if (fx == 6){
		EmitRainbowStripeUpwards ();
	}
	if (fx == 7){
		EmitUpwardMovingStripe (CRGB::Blue, CRGB::Green);
	}
}

void setMonoColor (CRGB pixel_color) {
// Set all LEDs to a given color
	fx = 0;
	for (int i = 0; i < num_leds; i++) {
		leds[i] = pixel_color;
	}
}

void SetDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
// Set part of LEDs to one color, the other to another
	fx = 0;

	// Modifier:
	float color_ratio = 0.4;

	for (int i = 0; i < num_leds; i++) {
		if (i >= 0 && i < num_leds * color_ratio) {
			leds[i] = pixel_color_bot;
		}
		else {
			leds[i] = pixel_color_top;
		}
	}
}

void SetRainbow () {
// Set LEDs to a static rainbow effect
	// Modifiers:
	uint8_t hue = 0;
	uint8_t delta_hue = 35;

	fill_rainbow (leds, num_leds, hue, delta_hue);
}

void UpdateInitials (uint8_t eeprom_value) {
// Update Memory and last_color
// Used to set presets values for power-on
	EEPROM.update (eeprom_address, eeprom_value);
	last_color = eeprom_value;
}

void EmitMonoColor (CRGB pixel_color) {
// All LEDs emit same color
	setMonoColor (pixel_color);
	FastLED.show();
}

void EmitDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
// Part of LEDs emit one color, the other part emits another
	SetDualHorizontal (pixel_color_bot, pixel_color_top);
	FastLED.show();
}

// XXXX Link this somehow to SetRainbow?
void EmitRainbow () {
// Emit a rainbow
	fx = 0;

	// Modifiers:
	uint8_t hue = 0;
	uint8_t delta_hue = 35;

	fill_rainbow (leds, num_leds, hue, delta_hue);
	FastLED.show();
}

void EmitUpwardMovingRainbow () {
// Emit an upward moving rainbow
	static uint8_t current_led = 0;

	// Modifiers:
	uint8_t hue = millis() * 0.7;		// hue should be int? XXXX
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	unsigned long delay_time = 50;	// ms

	if (current_led > num_leds) {
		current_led	= 0;
	}
	leds[current_led] = CHSV (hue, saturation, brightness);
	FastLED.show();
	current_led = (current_led + 1) % num_leds;
	delay(delay_time);
}

void EmitDownwardMovingRainbow () {
// Emit an downward moving rainbow
	static uint8_t hue = 0;

	// Modfiers:
	unsigned long delay_time = 10;
	uint8_t fade_amount = 255;		// Whats fade fore again?

	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CHSV (hue + (i * 256 / num_leds), 255, 255);
	}
	FastLED.show();
	// The following does NOTHING? XXXX
	fadeToBlackBy(leds, num_leds, fade_amount);
	hue++;
	delay(delay_time);
}

void EmitRainbowLava () {
// Emit an lava-like effect with rainbow colors

	// Modifier:
	CRGBPalette16 palette = RainbowColors_p;
	unsigned long delay_time = 30;
	uint8_t fade_amount = 100;
	uint8_t brightness = 255;
	float colorchange_speed = 0.03;

	fadeToBlackBy(leds, num_leds, fade_amount);
	for (int i = 0; i < num_leds; i++) {
		uint8_t index = millis() * colorchange_speed + i * 2;
		leds[i] = ColorFromPalette(palette, index, brightness);
	}
	FastLED.show();
	delay(delay_time);
}

void EmitPulsatingRainbow () {
// Pulsating light going through rainbow colors
	static uint8_t hue;

	// Modifier:
	unsigned long delay_time = 5;		// Lower is faster pulsation
	uint8_t saturation = 255;
	uint8_t brightness = 255;

	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CHSV (hue, saturation, brightness);
	}
	FastLED.show();
	hue++;
	delay(delay_time);
}

void EmitPushDownward () {
// Looks like a color is pushing darkness away
	static uint8_t hue = 0;

	// Modifier:
	unsigned long color_delay = 300;	// Higher: color persists longer
	unsigned long chase_delay = 40;	// Lower: faster built-down of effect
	uint8_t saturation = 255;
	uint8_t brightness = 255;

	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CHSV(hue, saturation, brightness);
	}
	FastLED.show();
	hue += 10;
	delay(color_delay);
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(chase_delay);
	}
}

void EmitRainbowStripeUpwards () {
// Emit an stripe that moves upwards
// With the right settings: stripe looks like a rainbow
	static uint8_t fade_amount = 255;
	static uint8_t current_led = 0;
	uint8_t hue = 0;

	// Modifier:
	unsigned long movement_speed = 90;	// Lower: faster
	unsigned long delay_time = 65;				// Delay between cycles
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	float hue_modifier = 0.7;					// Lower: slower color changes

	// Fill range of LEDs with a solid color
	fill_solid(leds, num_leds, CRGB::Black);
	for (int i = 0; i < num_leds; i++) {
		hue = millis() * hue_modifier;
		leds[current_led] = CHSV(hue, saturation, brightness);
		FastLED.show();
		delay(movement_speed);
		current_led = (current_led + 1) % num_leds;
		leds[i] = CRGB::Black;
	}

	// WHAT EXACTLY DOES THIS DO? XXXX
	for (int j = 255; j >= 0; j -= fade_amount) {
		for (int k = 0; k < num_leds; k++) {
			leds[k].fadeToBlackBy(fade_amount);
			leds[k].maximizeBrightness(j);
		}
		FastLED.show();
		delay(delay_time);
	}
}

void EmitUpwardMovingStripe (CRGB pixel_color_1, CRGB pixel_color_2) {
		// Modifier:
		unsigned long delay_time = 50;

		for(int i = 0; i < num_leds; i++) {
			leds[i] = pixel_color_1;
			FastLED.show();
			delay(delay_time);
		}

		for(int i = 0; i < num_leds; i++) {
			leds[i] = pixel_color_2;
			FastLED.show();
			delay(delay_time);
		}
}
