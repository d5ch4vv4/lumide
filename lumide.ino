/*
 * Arduino Sketch for Lamp Color Control via Bluetooth
 * 
 * 
 * File:			lumide.ino
 * Author1:		Andreas Berhmani (bermo@aon.at)
 * Author2:		Rafal Fresel (fresel.rafal@gmail.com)
 * Date:			Spring 2024
 * 
 * 
 * Description:
 *
 * 		This program allows control of a lamp's colors. The lamp is connected
 *		to an Arduino board, and communication is established via Bluetooth 
 *		with a mobile app. The app sends commands to change the lamp's color 
 *		modes, including static colors and dynamic (moving) effects.
 * 
 * 
 * Features:
 *
 * 		- Mono-color emission (predefined colors)
 *		- Dual-color emission (horizontally divided, predefined colors)
 * 		- Moving effects for dynamic color changes
 * 		- Bluetooth communication with a mobile app
 * 
 * 
 * Global Variables:
 * 
 * 		- const uint8_t num_leds
 *				- Total number of LEDs
 * 
 *		- const char eeprom_address
 *				- Memory address
 * 
 *		- CRGB leds[num_leds]
 *				- Array to store color data for the LED strip
 * 
 *		- SoftwareSerial BTSerial (0, 1)
 *				- Software-based serial communication channel on pins 0 (RX)
 *					and 1 (TX) of the Arduino board
 * 
 *		- char last_color
 *				- Stored value represents a "color code"
 *				- Defaults to 'r' (red)
 * 
 *		- uint8_t fx
 *				- Effect control variable: 0 for static, non-zero for moving effects
 * 
 * 
 * Setup:
 * 
 * 		- Variables:
 * 
 * 				- const uint8_t led_pin
 * 						- The pin to which the LED strip is connected
 * 
 *				- const uint16_t baud_rate
 * 						- Specifies the data transfer speed or baud rate at which
 *							communication will occur
 * 
 *		- Description:
 * 
 * 				- Configuring FastLED to communicate with a WS2811-based LED strip by
 * 					using the addLeds function from the FastLED library.
 *				- Initializing a serial communication for a Bluetooth module using the
 *					begin function from the SoftwareSerial library.
 *				- Initializing a hardware serial communication with a baud rate of
 *					9600 baud, by making use of the begin function on the Serial
 *					object.
 *						- The Serial object is the name of a hardware serial object.
 *						- Here it is used for communication over USB.
 * 				- Retrieving a previously stored "color code" (last_color) from the
 *					memory (EEPROM - Electrically Erasable Programmable Read-Only
 *					Memory).
 *						- The retrieved value is assigned to last_color, allowing the lamp
 *							to initialize with the same color(s)/effect upon power-on that
 *							was set before shutdown.
 *				- Setting up LEDs by making use of a switch statement:
 *						- Depending on the "color code" in last_color, the setup can be:
 *								- Mono color (static)
 *								- Dual color (static)
 *								- Rainbow effect (static)
 *								- A moving effect (multi-colored)
 *						- Default is: all LEDs are red.
 *				- Finally emit the setup with the help of the show function from the
 *					FastLED library.
 *
 * 
 * Loop:
 * 
 * 		- Variables:
 * 
 * 				- char received
 *						- Holds data used to decide which program to run (i.e., which
 *							color(s) are used, static or non-static)
 *
 *		- Description: 
 * 
 * 				- Reading data from a previously established Bluetooth connection
 * 				- Depending on the received data a specific light effect is emitted:
 *						- Mono color (static)
 *						- Dual color (static)
 *						- Rainbow effect (static)
 *						- A moving effect (multi-colored)
 * 
 * 
 * Hardware:
 * 
 * 		- WS2811 LED strip
 *				http://fastled.io/docs/class_w_s2811.html
 * 
 * 		- Teensy 2.0
 *				https://deskthority.net/wiki/Teensy
 * 
 * 
 * Libraries:
 * 
 *		- SoftwareSerial.h
 *				https://docs.arduino.cc/learn/built-in-libraries/software-serial/
 * 
 * 		- EEPROM.h
 *				https://docs.arduino.cc/learn/built-in-libraries/eeprom/
 * 
 * 		- FastLED.h
 *				https://www.arduino.cc/reference/en/libraries/fastled/
 *				http://fastled.io/
 * 
 * 
 * CRGB Information:
 * 
 * 		- CRGB is a color representation type used in FastLED library for RGB
 *			colors.
 *		- Learn more: https://github.com/FastLED/FastLED/wiki/Pixel-reference
 * 
 */

#define FASTLED_INTERNAL // Include to disable pragma message

#include <FastLED.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

const uint8_t num_leds = 18;
const char eeprom_address = 0;
CRGB leds[num_leds];
SoftwareSerial BTSerial (0, 1);
char last_color = 'r';
uint8_t fx = 0;

void setup() {
	const uint8_t led_pin = 5;
	const uint16_t baud_rate = 9600;

  FastLED.addLeds<WS2811, led_pin, GRB>(leds, num_leds);
  BTSerial.begin(baud_rate);
  Serial.begin(baud_rate);

  last_color = EEPROM.read(eeprom_address);
  
  // Set up LEDs after power On
  switch (last_color) {

		// Static one color
		case 'r':
			SetMonoColor (CRGB::Red);
			break;
		case 'g':
			SetMonoColor (CRGB::Green);
			break;
		case 'b':
			SetMonoColor (CRGB::Blue);
			break;
		case 'c':
			SetMonoColor (CRGB::Cyan);
			break;
		case 'm':
			SetMonoColor (CRGB::Magenta);
			break;
		case 'v':
			SetMonoColor (CRGB::Violet);
			break;
		case 'o':
			SetMonoColor (CRGB::Orange);
			break;
		case 'y':
			SetMonoColor (CRGB::Yellow);
			break;
		case 'w':
			SetMonoColor (CRGB::White);
			break;
		case 'x':
			SetMonoColor (CRGB::Black);

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

		// Moving effects
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
		SetMonoColor (CRGB::Red);
    break;
  }  

	// Update controllers with LED colors
  FastLED.show();
}

void loop() {
	char received = 0;

  if (BTSerial.available()) {

    received = BTSerial.read();

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

		// Set up moving effects
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

	// Moving effects:
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

/**
 *
 * void SetMonoColor (CRGB pixel_color)
 *
 * This function is used to assosiate LEDs with a single color.
 * 
 * 
 * Parameters:
 * 		- CRGB pixel_color: represents a color in RGB color space.

 * Variables:
 *		- uint8_t fx
 *				- Globally defined.
 *				- Used to decide whether the function is a moving effect.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Declaring this function as a non moving effect
 *		- Using a for-loop to associate LEDs with a given pixel_color
 *		- Note: not emitting!
 *
 */
void SetMonoColor (CRGB pixel_color) {
	fx = 0;
	for (int i = 0; i < num_leds; i++) {
		leds[i] = pixel_color;
	}
}

/**
 *
 * void SetDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top)
 *
 * A set of LEDs, given by an array, is divided into two sets.
 * One set is associated with one color, the other with another.
 * 
 * 
 * Parameters:
 *		- CRGB pixel_color_bot
 *				- Represents the color in RGB color space of a LED in the
 *					"bottom" set of LEDs.
 *		- CRGB pixel_color_top
 *				- Represents the color in RGB color space of a LED in the
 *					"top" set of LEDs.
 *
 * Variables:
 *		- uint8_t fx
 *				- Globally defined.
 *				- Used to decide whether the function is a moving effect.
 *		- float color_ratio
 *				- Used to define the ratio between the two sets of LEDs.
 *		
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *
 * Return values:
 *		- None.
 *		
 * Description:
 *		- Declaring this function as a non moving effect.
 *		- Using for-loops to associate LEDs with given pixel_colors.
 *		- Lower color_ratio means less LEDs are associated with the "bot" color.
 *		- Note: not emitting!
 *		
 */
void SetDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
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

/**
 *
 * void SetRainbow ()
 *
 * This function is used to associate LEDs with a rainbow of colors.
 *
 *
 * Parameters:
 *		- None
 * 
 * Variables:
 *		- const uint8_t num_leds
 *				- Globally defined.
 *				- Nummer of LEDs to fill in the array (total number of LEDs).
 *		- uint8_t hue
 *				- Represents an angle around the color wheel
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t delta_hue
 *				- Defines how many hue values to advance for each LED.
 * 
 * Data structures:
 *		- CRGB leds
 *				- Globally defined array that associates its elements with LEDs.
 *
 * Return values:
 *		- None.
 * 
 * Description:
 *		- Declaring this function as a non moving effect.
 *		- Using the fill_rainbow function from the FastLED lib to associate
 *			LEDs with a rainbow of colors.
 *		- Modifying hue means to shift the starting hue for the rainbow.
 *		- Higher delta_hue values mean faster shift through the color wheel.
 *		- Note: not emitting!
 *
 */
void SetRainbow () {
	fx = 0;

	// Modifiers:
	uint8_t hue = 0;
	uint8_t delta_hue = 35;

	fill_rainbow (leds, num_leds, hue, delta_hue);
}

/**
 * 
 * void UpdateInitials (uint8_t eeprom_value)
 *
 * Set preset values used after power-on.
 *
 *
 * Parameters:
 *		- uint8_t eeprom_value
 *				- Value that is written to the EEPROM.
 *
 * Variables:
 *		- const char eeprom_address
 *				- The location to write to.
 *		- char last_color
 *				- Color value used to set initial color(s) of LEDs after power-on.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the update() method to write a color value to the EEPROM, which
 *			then is used to initialize LEDs
 *		- After power-on the eeprom_value will be copied from memory into 
 *			last_color, and this value is used to associate LEDs with specific
 *			color(s).
 *
 */
void UpdateInitials (uint8_t eeprom_value) {
	EEPROM.update (eeprom_address, eeprom_value);
	last_color = eeprom_value;
}

/**
 *
 * void EmitMonoColor (CRGB pixel_color)
 *
 * Let all LEDs emit the same color.
 *
 *
 * Parameters:
 * 		- CRGB pixel_color
 *				- Represents a color in RGB color space.
 *
 * Variables:
 *		- None.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the SetMonoColor function to set LEDs to a specific color given
 *			by pixel_color.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *
 */
void EmitMonoColor (CRGB pixel_color) {
	SetMonoColor (pixel_color);
	FastLED.show();
}

/**
 *
 * void EmitDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top)
 *
 * Split LEDs into two sets. Let one set emit one color and the other set
 * another.
 *
 *
 * Parameters:
 *		- CRGB pixel_color_bot
 *				- Represents the color in RGB color space of a LED in the "bottom"
 *					set of LEDs.
 *		- CRGB pixel_color_top
 *				- Represents the color in RGB color space of a LED in the "top"
 *					set of LEDs.
 *
 * Variables:
 *		- None.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the SetDualHorizontal function to set up the LEDs.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *
 */
void EmitDualHorizontal (CRGB pixel_color_bot, CRGB pixel_color_top) {
	SetDualHorizontal (pixel_color_bot, pixel_color_top);
	FastLED.show();
}

/**
 *
 * void EmitRainbow ()
 *
 * Emit an rainbow of colors.
 *
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- None.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the SetRainbow function to set up the LEDs.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *
 */
void EmitRainbow () {
	SetRainbow();
	FastLED.show();
}

/**
 *
 * void EmitUpwardMovingRainbow ()
 *
 * Emit an upward moving rainbow.
 *
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- static uint8_t current_led
 *				- Used to keep track of and modify specific LED.
 *		- const uint8_t num_leds
 *				- Globally defined.
 *				- Nummer of LEDs to fill in the array (total number of LEDs).
 *		- uint8_t hue
 *				- Represents an angle around the color wheel.
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation
 *				- Color saturation.
 *				- Representing a percentage.
 *		- uint8_t brightness
 *				- Color brighntess.
 *				- Representing a percentage.
 *		- uint32_t delay_time
 *				- Represents some amount of time in millisec.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *		- CHSV
 *				- Representation of an HSV pixel:
 *						- hue
 *						- saturation
 *						- value (aka brightness)
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Set current_led to zero (i.e., the first LED), once the value exceeds
 *			the total of LEDs (num_leds).
 *		- Assign the current LED a color:
 *				- The color is specified by using the millis() function multiplied
 *					by an float.
 *				- millis() returns the number of milliseconds passed since the
 *					arduino board began running in the current program.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *		- Moving to next LED.
 *		- Pausing the program by an specified amount of time using delay().
 *		- Rotating over all LEDs by using the modulo operator.
 *		- Higher dealy_time values slow down the movement effect.
 *
 */
void EmitUpwardMovingRainbow () {
	static uint8_t current_led = 0;

	// Modifiers:
	uint8_t hue = millis() * 0.7;		// Overflow?
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	uint32_t delay_time = 50;

	if (current_led > num_leds) {
		current_led	= 0;
	}
	leds[current_led] = CHSV (hue, saturation, brightness);
	FastLED.show();
	current_led = (current_led + 1) % num_leds;
	delay(delay_time);
}

/**
 *
 * void EmitDownwardMovingRainbow ()
 *
 * Emit an downward moving rainbow
 *
 *
 * Parameters:
 *		- None.
 * 
 * Variables:
 *		- const uint8_t num_leds
 *				- Globally defined.
 *				- Nummer of LEDs to fill in the array (total number of LEDs).
 *		- uint8_t hue
 *				- Represents an angle around the color wheel.
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation
 *				- Color saturation.
 *				- Representing a percentage.
 *		- uint8_t brightness
 *				- Color brighntess.
 *				- Representing a percentage.
 *		- uint8_t speed_modifier
 *				- Modifies the movement speed of the rainbow.
 *		- uint32_t delay_time
 *				- Represents some amount of time in milliseconds.
 *		- uint8_t fade_amount
 *				- How much to fade each LED.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *		- CHSV
 *				- Representation of an HSV pixel:
 *						- hue
 *						- saturation
 *						- value (aka brightness)
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for loop to generate a rainbow effect.
 *		- Increasing the hue value by the speed_modifier value to generate
 *			movement.
 *		- Reseting the hue value to zero once it exceeds 256.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *		- Higher speed_modifier values increase the movement speed of the
 *			rainbow.
 *		- delay_time can also be used to manipulate movement.
 *				- Direct comparison would be needed for more exact description.
 *		- Still clueless what fadeToBlackBy does here. No obvious change could
 *			be observed once commented out.
 *				- fadeToBlackBy():
 *						- Reduce the brightness of an array of pixels all at once.
 *
 */
void EmitDownwardMovingRainbow () {
	static uint8_t hue = 0;

	// Modfiers:
	uint8_t fade_amount = 255;
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	uint8_t speed_modifier = 2;
	uint32_t delay_time = 10;

	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CHSV (hue + (i * 256 / num_leds), saturation, brightness);
	}
	FastLED.show();
	fadeToBlackBy(leds, num_leds, fade_amount);
	hue = hue + speed_modifier;
	delay(delay_time);
}

/**
 *
 * void EmitRainbowLava ()
 *
 * Emit an lava-like effect with rainbow colors.
 *
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- uint32_t delay_time
 *				- Represents some amount of time in millisec.
 *		- uint8_t fade_amount
 *				- How much to fade each LED.
 *		- uint8_t brightness
 *				- Color brighntess.
 *				- Representing a percentage.
 *		- float colorchange_speed
 *				- Modifies the speed of transition from one color to another.
 *		- const uint8_t num_leds
 *				- Globally defined.
 *				- Nummer of LEDs to fill in the array (total number of LEDs).
 *		- CRGBPalette16 palette
 *				- RGB color palette with 16 discrete values.
 *		- uint8_t index
 *				- Position in a color palette (to retrieve the color for).
 *
 * Data structures:
 *		- CRGB leds:
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for-loop to transition colors through a predefined color 
 *			palette.
 *				- ColorFromPalette(): get a color from a palette.
 *				- millis() returns the number of milliseconds passed since the
 *					arduino board began running in the current program.
 *				- By increasing colorchange_speed, we can increase the speed of
 *				  the transition from one color to the next.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *		- Very high delay_time values stop the fading from one color to another.
 *		- Still clueless what fadeToBlackBy does here. No obvious change could
 *			be observed once commented out.
 *				- fadeToBlackBy():
 *						- Reduce the brightness of an array of pixels all at once.
 *
 *
 */
void EmitRainbowLava () {

	// Modifier:
	CRGBPalette16 palette = RainbowColors_p;
	uint32_t delay_time = 30;
	uint8_t fade_amount = 255;
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

/**
 * void EmitPulsatingRainbow ()
 *
 * Emit an pulsating rainbow. All LEDs take on the same color at the same
 * time. Fading through rainbow colors while pulsating.
 *
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- uint8_t hue
 *				- Represents an angle around the color wheel.
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation
 *				- Color saturation.
 *				- Representing a percentage.
 *		- uint8_t brightness
 *				- Color brighntess.
 *				- Representing a percentage.
 *		- uint32_t delay_time
 *				- Represents some amount of time in milliseconds.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *		- CHSV
 *				- Representation of an HSV pixel:
 *						- hue
 *						- saturation
 *						- value (aka brightness)
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for-loop to associate LEDs with a color.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *		- Fading through colors is generated by hue++.
 *		- Reset hue to zero once it exceeds the max value.
 *		- Increasing the delay_time lowers the pulsation speed.
 *
 */
void EmitPulsatingRainbow () {
	static uint8_t hue;

	// Modifier:
	uint32_t delay_time = 5;
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

/**
 *
 * void EmitPushDownward ()
 *
 * Color pushes darkness away. All LEDs emit same color, then fade into
 * into darkness from the bottom to top. Color change.
 *
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- uint32_t color_delay
 *				- Amount of time in millisec that a color persists before changing
 *					to another.
 *		- uint32_t chase_delay
 *				- Amount of time in millisec that defines the duration of the 
 *					"build-down" (the fading into darkness).
 *		- uint8_t hue
 *				- Represents an angle around the color wheel.
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation
 *				- Color saturation.
 *				- Representing a percentage.
 *		- uint8_t brightness
 *				- Color brighntess.
 *				- Representing a percentage.
 *		- uint8_t color_delta
 *				- Amount of hue difference between loops.
 *		
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *		- CHSV
 *				- Representation of an HSV pixel:
 *						- hue
 *						- saturation
 *						- value (aka brightness)
 *
 * Return values:
 *		- None.
 *
 * Descrption:
 *		- Using a for-loop to associate the LEDs with a color.
 *		- Using a second for-loop to generate a "build-down" effect:
 *				- After all LEDs have taken on the value of a color, they fade
 *					into CRGB::Black, from bottom to top.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *		- Color change is accomplished by 'hue += 10'.
 *		- Higher color_delay values mean longer color persistence.
 *		- Lower chase_delay values mean faster "build-down" effect.
 *		- Higher color_delta values change colors faster.
 *				
 */
void EmitPushDownward () {
	static uint8_t hue = 0;

	// Modifier:
	uint32_t color_delay = 30;
	uint32_t chase_delay = 40;
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	uint8_t color_delta = 10;

	if (hue >= 256) {
		hue = 0;
	}
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CHSV(hue, saturation, brightness);
	}
	FastLED.show();
	hue += color_delta;
	delay(color_delay);
	for (int i = 0; i < num_leds; i++) {
		leds[i] = CRGB::Black;
		FastLED.show();
		delay(chase_delay);
	}
}

/**
 *
 * void EmitRainbowStripeUpwards ()
 *
 * Emit an stripe that looks like a rainbow moving upwards.
 *
 *
 * Paramters:
 *		- None.
 *
 * Variables:
 *		- uint8_t fade_amount
 *				- How much to fade each LED.
 *		- static uint8_t current_led
 *				- Used to keep track of and modify specific LEDs.
 *		- uint8_t hue
 *				- Represents an angle around the color wheel.
 * 				- 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation
 *				- Color saturation.
 *				- Representing a percentage.
 *		- uint8_t brightness
 *				- Color brightness.
 *				- Representing a percentage.
 *		- uint32_t movement_speed
 *				- Amount of time in milliseconds the program pauses.
 *				- Modifies speed of movement.
 *		- uint32_t delay_time
 *				- Amount of time in milliseconds the program pauses.
 *				- Modifies delay in between cycles.
 *		- float hue_modifier
 *				- Modifies color changes.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *		- CHSV
 *				- Representation of an HSV pixel:
 *						- hue
 *						- saturation
 *						- value (aka brightness)
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Filling the range of LEDs with a solid color (CRGB::Black).
 *		- Using a for loop to generate a rainbow stripe that moves upward.
 *				- millis() returns the number of milliseconds passed since the
 *					arduino board began running in the current program.
 *				- Lower movement_speed values speed up the movement of the stripe.
 *				- Lower hue_modifier values slow down color changes.
 *		- Using show() to update all controllers with current LED color.
 *		- Higher delay_time values increase the time between cycles, i.e.,
 *			increases the time in darkness.
 *		- Clueless about what exactly the second loop does. No obvious change
 *			when commenting it out.
 *				- fadeToBlackBy():
 *						- Reduce the brightness of an array of pixels all at once.
 *				- maximizeBrightness():
 *						- Maximize the brightness of the CRGB object.
 *
 *
 */
void EmitRainbowStripeUpwards () {
	static uint8_t fade_amount = 255;
	static uint8_t current_led = 0;
	uint8_t hue = 0;

	// Modifier:
	uint32_t movement_speed = 90;
	uint32_t delay_time = 650;
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	float hue_modifier = 0.7;

	fill_solid(leds, num_leds, CRGB::Black);
	for (int i = 0; i < num_leds; i++) {
		hue = millis() * hue_modifier;
		leds[current_led] = CHSV(hue, saturation, brightness);
		FastLED.show();
		delay(movement_speed);
		current_led = (current_led + 1) % num_leds;
		leds[i] = CRGB::Black;
	}

	// WHAT EXACTLY DOES THIS DO?
	for (int j = 255; j >= 0; j -= fade_amount) {
		for (int k = 0; k < num_leds; k++) {
			leds[k].fadeToBlackBy(fade_amount);
			leds[k].maximizeBrightness(j);
		}
		FastLED.show();
	}
	delay(delay_time);
}

/**
 *
 * void EmitUpwardMovingStripe (CRGB pixel_color_1, CRGB pixel_color_2)
 *
 * Emit a color that builds up from the bottom and "pushes" the other away.
 *
 *
 * Parameters:
 *		- CRGB pixel_color_1
 *				- Represents the first color in RGB color space.
 *		- CRGB pixel_color_2
 *				- Represents the second color in RGB color space.
 *
 * Variables:
 *		- uint32_t delay_time
 *				- The amount of time in milliseconds the program pauses.
 *
 * Data structures:
 *		- CRGB leds
 *				- Globally defined.
 *				- Array that associates its elements with LEDs.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using two for-loops:
 *				- The first one builds up from the bottom by associate LEDs with the
 *					first color until all LEDs emit pixel_color_1.
 *				- Then the second one does the same with pixel_color_2 and thereby 
 *					"pushes" the first one away.
 *				- After that the first one "pushes" the second one away and so on.
 *		- Higher delay_time values slow down the whole process.
 *		- Using show() from the FastLED library to update all controllers 
 *			with current LED color.
 *
 */
void EmitUpwardMovingStripe (CRGB pixel_color_1, CRGB pixel_color_2) {
		// Modifier:
		uint32_t delay_time = 50;

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
