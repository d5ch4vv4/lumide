// HEADER COMMENT: 2DO!
/*
 * References:
 *		https://www.arduino.cc/reference/en/language/variables/data-types/byte/
 *		https://www.arduino.cc/reference/en/language/variables/data-types/float/
 *		https://github.com/FastLED/FastLED/wiki/Pixel-reference#crgb
*/


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
		SetMonoColor (CRGB::Red);
    break;
  }  

	// Update controllers with LED colors
  FastLED.show();
}

void loop() {
	char received = 0;							// Data from Bluetooth

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

/**
 *
 * void SetMonoColor (CRGB pixel_color)
 *
 * This function is used to assosiate LEDs with a single color.
 * 
 * Parameters:
 * 		- CRGB pixel_color: represents a color in RGB color space.

 * Variables:
 *		- byte fx: used to decide whether the function is a moving effect.
 *				Globally defined.
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
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
 * Parameters:
 *		- CRGB pixel_color_bot: represents the color in RGB color space of a LED
 *				in the "bottom" set of LEDs.
 *		- CRGB pixel_color_top: represents the color in RGB color space of a LED
 *				in the "top" set of LEDs.
 *
 * Variables:
 *		- byte fx: used to decide whether the function is a moving effect.
 *				Globally defined.
 *		- float color_ratio: used to define the ratio between the two sets of
 *				LEDs.
 *		
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *
 * Return values:
 *		- None.
 *		
 * Description:
 *		- Declaring this function as a non moving effect.
 *		- Lower color_ratio means less LEDs are associated with the "bot" color.
 *		- Using for-loops to associate LEDs with given pixel_colors.
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
 * Parameters:
 *		- None
 * 
 * Variables:
 *		- const byte num_leds: nummer of LEDs to fill in the array.
 *				Globally defined. Total number of LEDs.
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t delta_hue: defines how many hue values to advance for each LED
 * 
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *
 * Return values:
 *		- None.
 * 
 * Description:
 *		- Declaring this function as a non moving effect
 *		- Using the fill_rainbow function from the FastLED lib to associate LEDs
 *			with a rainbow of colors
 *		- Modifying hue means to shift the starting hue for the rainbow
 *		- Higher delta_hue values mean faster shift through the color wheel
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
 * Parameters:
 *		- uint8_t eeprom_value: value that is written to the EEPROM
 *
 * Variables:
 *		- const char eeprom_address: the location to write to
 *		- char last_color: last color value used to set initial color(s) of LEDs
 *				after power-on.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the update() method to write a color value to the EEPROM, which
 *			then is used to initialize LEDs
 *		- After power-off the eeprom_value will be copied into last_color, and
 *			this value is used to associate LEDs with specific color(s)
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
 * Parameters:
 * 		- CRGB pixel_color: represents a color in RGB color space.
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
 *		- Using show() to update all controllers with current LED colors.
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
 * Parameters:
 *		- CRGB pixel_color_bot: represents the color in RGB color space of a LED
 *				in the "bottom" set of LEDs.
 *		- CRGB pixel_color_top: represents the color in RGB color space of a LED
 *				in the "top" set of LEDs.
 *
 * Variables:
 *		- None.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using the SetDualHorizontal function to set up the LEDs.
 *		- Using show() to update all controllers with current LED colors.
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
 * Emit an rainbow of colors
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
 *		- Using show() to update all controllers with current LED colors.
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
 * Emit an upward moving rainbow
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- static uint8_t current_led: used to keep track of and modify specific
 *				LED
 *		- const byte num_leds: nummer of LEDs to fill in the array.
 *				Globally defined. Total number of LEDs.
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation: color saturation.
 *				Representing a percentage.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- unsigned long delay_time: represents some amount of time in millisec
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *		- CHSV: Representation of an HSV pixel (hue, saturation, value (aka
 *				brightness)).
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Set current_led to zero (i.e., the first LED), once the value exceeds
 *			the total value of LEDs (num_leds).
 *		- Assign the current LED a color:
 *				- The color is specified by using the millis() function multiplied
 *					by an float.
 *				- millis() returns the number of milliseconds passed since the
 *					arduino board began running in the current program.
 *		- Using show() to update all controllers with current LED color.
 *		- Moving to next LED.
 *		- Pausing the program by an specified amount of time to slow down the
 *			movement of the Effect.
 *		- Rotating over all LEDs by using the modulo operator.
 *
 */
void EmitUpwardMovingRainbow () {
	static uint8_t current_led = 0;

	// Modifiers:
	uint8_t hue = millis() * 0.7;		// Overflow?
	uint8_t saturation = 255;
	uint8_t brightness = 255;
	unsigned long delay_time = 50;

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
 * Parameters:
 *		- None.
 * 
 * Variables:
 *		- const byte num_leds: nummer of LEDs to fill in the array.
 *				Globally defined. Total number of LEDs.
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation: color saturation.
 *				Representing a percentage.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- uint8_t speed_modifier: higher values increase the movements
 *				speed of the rainbow.
 *		- unsigned long delay_time: represents some amount of time
 *				in millisec.
 *		- uint8_t fade_amount: how much to fade each LED.
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *		- CHSV: Representation of an HSV pixel (hue, saturation, value (aka
 *				brightness)).
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for loop to generate a rainbow effect.
 *		- Increasing the hue value by the speed_modifier value to generate
 *			a movement.
 *		- Reseting the hue value to zero once it exceeds 256.
 *		- Using show() to update all controllers with current LED color.
 *		- The delay_time can also be used to manipulate movement.
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
	unsigned long delay_time = 10;

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
 * Emit an lava-like effect with rainbow colors
 *
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- unsigned long delay_time: represents some amount of time in millisec.
 *		- uint8_t fade_amount: how much to fade each LED.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- float colorchange_speed: modifies the speed of transition from one
 *				color to another.
 *		- const byte num_leds: nummer of LEDs to fill in the array.
 *				Globally defined. Total number of LEDs.
 *		- CRGBPalette16 palette: RGB color palette with 16 discrete values.
 *		- uint8_t index: position in a color palette (to retrieve the color
 *				for).
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for-loop transition through a predefined color palette.
 *				- ColorFromPalette(): get a color from a palette.
 *				- millis() returns the number of milliseconds passed since the
 *					arduino board began running in the current program.
 *				- By increasing colorchange_speed, we can increase the speed of
 *				  the transition from one color to the next.
 *		- Using show() to update all controllers with current LED color.
 *		- Very high delay_time stop the fading from one color to another.
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
	unsigned long delay_time = 30;
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
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation: color saturation.
 *				Representing a percentage.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- unsigned long delay_time: represents some amount of time
 *				in millisec.
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *		- CHSV: Representation of an HSV pixel (hue, saturation, value (aka
 *				brightness)).
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using a for-loop to associate LEDs with a color.
 *		- Using show() to update all controllers with current LED color.
 *		- Fading through colors is generated by hue++.
 *		- Whe reset hue to zero once it exceeds the max value.
 *		- Increasing the delay_time lowers the pulsation speed.
 *
 */
void EmitPulsatingRainbow () {
	static uint8_t hue;

	// Modifier:
	unsigned long delay_time = 5;
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
 * Parameters:
 *		- None.
 *
 * Variables:
 *		- unsigned long color_delay: amount of time in millisec that a color
 *				persists before changing to another.
 *		- unsigned long chase_delay: amount of time in millisec that defines
 *				the duration of the "build-down" (the fading into darkness).
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation: color saturation.
 *				Representing a percentage.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- uint8_t color_delta: amount of hue difference between loops.
 *		
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *		- CHSV: Representation of an HSV pixel (hue, saturation, value (aka
 *				brightness)).
 *
 * Return values:
 *		- None.
 *
 * Descrption:
 *		- Using a for-loop to associate the LEDs with a color
 *		- Using a second for-loop to generate a "build-down" effect:
 *				- After all LEDs have taken on the value of a color, they fade
 *					into CRGB::Black, from bottom to top.
 *		- Using show() to update all controllers with current LED color.
 *		- Color change is accomplished by 'hue += 10'.
 *		- Higher color_delay values mean longer color persistence.
 *		- Lower chase_delay values mean faster "build-down" effect.
 *		- Higher color_delta values change colors faster.
 *				
 */
void EmitPushDownward () {
	static uint8_t hue = 0;

	// Modifier:
	unsigned long color_delay = 30;
	unsigned long chase_delay = 40;
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
 * Paramters:
 *		- None.
 *
 * Variables:
 *		- uint8_t fade_amount: how much to fade each LED.
 *		- static uint8_t current_led: used to keep track of and modify
 *				specific LED.
 *		- uint8_t hue: represents an angle around the color wheel:
 * 				Where 0 is 0 deg, and 255 is 358 deg.
 *		- uint8_t saturation: color saturation.
 *				Representing a percentage.
 *		- uint8_t brightness: color brighntess.
 *				Representing a percentage.
 *		- unsigned long movement_speed: amount of time in millisec the
 *				program pauses. Modifies speed of movement.
 *		- unsigned long delay_time: amount of time in millisec the
 *				program pauses. Modifies delay in between cycles.
 *		- float hue_modifier: modifies color changes
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *		- CHSV: Representation of an HSV pixel (hue, saturation, value (aka
 *				brightness)).
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Filling the range of LEDs with a solid color (CRGB::Black)
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
	unsigned long movement_speed = 90;
	unsigned long delay_time = 650;
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
 * Parameters:
 *		- CRGB pixel_color_1: represents the first color in RGB color space.
 *		- CRGB pixel_color_2: represents the second color in RGB color space.
 *
 * Variables:
 *		- unsigned long delay_time: the amount of time in millisec the program
 *				pauses.
 *
 * Data structures:
 *		- CRGB leds: globally defined array that associates its elements with
 *				LEDs.
 *
 * Return values:
 *		- None.
 *
 * Description:
 *		- Using two for-loops:
 *				- The first one builds up from the bottom with the first color.
 *				- Then the second one does the same and thereby "pushes" the first
 *					one from the bottom away.
 *				- After that the first one "pushes" the second one away and so on.
 *		- Higher delay_time values slow down the whole process.
 *		- Using show() to update all controllers with current LED color.
 *
 */
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
