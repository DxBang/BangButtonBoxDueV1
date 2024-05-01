#ifndef BANG_h
	#define BANG_h
#endif

#ifndef JOYSTICK_h
	#include "Joystick.h"
#endif
#ifndef KEYBOARD_h
	#include "Keyboard.h"
#endif

/*
36 buttons
8 rotary encoders
*/

// Lights Pins
#define LUMINOSITY_PIN 8
#define R_PIN 9
#define G_PIN 10
#define B_PIN 11
#define VIBRATE_PIN 12
#define VISUAL_PIN 13

#define LUMINOSITY_RED_1 8
#define LUMINOSITY_RED_2 7
#define LUMINOSITY_RED_3 6
#define LUMINOSITY_YELLOW 5
#define LUMINOSITY_GREEN 4
#define LUMINOSITY_BLUE 3
#define LUMINOSITY_WHITE 2


// Buttons Pins
// 8 duponts
#define B_IGNITION 22
#define B_ENGINE 24
#define B_PIT_LIMITER 26
// 28 is reserved for future use
#define B_FLASH 30
#define B_CYCLE_LIGHTS 32
#define B_RAINLIGHTS 34
#define B_CYCLE_WIPERS 36

// 8 duponts
#define B_COCKPIT_CAM 23
#define B_BONNET_CAM 25
#define B_CHASE_CAM 27
#define B_CYCLE_CAMERA 29
#define B_NAMES 31
#define B_RACELOGIC 33
#define B_DASHBOARD_UP 35
#define B_DASHBOARD_DOWN 37

// 8 duponts
#define B_CYCLE_MAP 38
#define B_CYCLE_HUD 40
#define B_NAVIGATION_UP 42
#define B_NAVIGATION_DOWN 44
#define B_NAVIGATION_LEFT 46
#define B_NAVIGATION_RIGHT 48
#define B_SELECT 50 // 50
#define B_BACK 52 // 52

// 39 is reserved for future use
// 41 is reserved for future use
// 43 is reserved for future use

// 5 duponts
#define B_INDICATOR_LEFT 45
#define B_INDICATOR_RIGHT 47
#define B_SAVE_REPLAY 49
#define B_ADD_HIGHLIGHT 51
#define B_SAVE_HIGHLIGHTS 53

// 8 duponts
#define B_MODE 62
#define B_SPECIAL 63
#define B_VOLUME 64
#define B_BRAKE_BIAS 65
#define B_TRACTION_CONTROL 66
#define B_ENGINE_MAP 67
#define B_ANTILOCK_BRAKING_SYSTEM 68
#define B_TRACKING_CONTROL_CUT 69

// 2x8 duponts
#define E_MODE_UP 14
#define E_MODE_DN A0
#define E_SPECIAL_UP 15
#define E_SPECIAL_DN A1
#define E_VOLUME_UP 16
#define E_VOLUME_DN A2
#define E_BRAKE_BIAS_UP 17
#define E_BRAKE_BIAS_DN A3
#define E_TRACTION_CONTROL_UP 18
#define E_TRACTION_CONTROL_DN A4
#define E_ENGINE_MAP_UP 19
#define E_ENGINE_MAP_DN A5
#define E_ANTILOCK_BRAKING_SYSTEM_UP 20
#define E_ANTILOCK_BRAKING_SYSTEM_DN A6
#define E_TRACKING_CONTROL_CUT_UP 21
#define E_TRACKING_CONTROL_CUT_DN A7


// index ids for rotary encoders
#define E_MODE 0
#define E_SPECIAL 1
#define E_VOLUME 2
#define E_BRAKE_BIAS 3
#define E_TRACTION_CONTROL 4
#define E_ENGINE_MAP 5
#define E_ANTILOCK_BRAKING_SYSTEM 6
#define E_TRACKING_CONTROL_CUT 7

/*
button pins to index
*/
int getButtonIndex(int pin) {
	switch(pin) {
		case B_IGNITION:
			return 0;
		case B_ENGINE:
			return 1;
		case B_PIT_LIMITER:
			return 2;
		case B_CYCLE_LIGHTS:
			return 3;
		case B_FLASH:
			return 4;
		case B_RAINLIGHTS:
			return 5;
		case B_INDICATOR_LEFT:
			return 6;
		case B_INDICATOR_RIGHT:
			return 7;
		case B_CYCLE_WIPERS:
			return 8;
		case B_COCKPIT_CAM:
			return 9;
		case B_BONNET_CAM:
			return 10;
		case B_CHASE_CAM:
			return 11;
		case B_CYCLE_CAMERA:
			return 12;
		case B_NAMES:
			return 13;
		case B_RACELOGIC:
			return 14;
		case B_DASHBOARD_UP:
			return 15;
		case B_DASHBOARD_DOWN:
			return 16;
		case B_CYCLE_HUD:
			return 17;
		case B_CYCLE_MAP:
			return 18;
		case B_NAVIGATION_UP:
			return 19;
		case B_NAVIGATION_DOWN:
			return 20;
		case B_NAVIGATION_LEFT:
			return 21;
		case B_NAVIGATION_RIGHT:
			return 22;
		case B_SELECT:
			return 23;
		case B_BACK:
			return 24;
		case B_SAVE_REPLAY:
			return 25;
		case B_ADD_HIGHLIGHT:
			return 26;
		case B_SAVE_HIGHLIGHTS:
			return 27;
		case B_BRAKE_BIAS:
			return 28;
		case E_BRAKE_BIAS_UP:
			return 29;
		case E_BRAKE_BIAS_DN:
			return 30;
		case B_TRACTION_CONTROL:
			return 31;
		case E_TRACTION_CONTROL_UP:
			return 32;
		case E_TRACTION_CONTROL_DN:
			return 33;
		case B_ENGINE_MAP:
			return 34;
		case E_ENGINE_MAP_UP:
			return 35;
		case E_ENGINE_MAP_DN:
			return 36;
		case B_ANTILOCK_BRAKING_SYSTEM:
			return 37;
		case E_ANTILOCK_BRAKING_SYSTEM_UP:
			return 38;
		case E_ANTILOCK_BRAKING_SYSTEM_DN:
			return 39;
		case B_TRACKING_CONTROL_CUT:
			return 40;
		case E_TRACKING_CONTROL_CUT_UP:
			return 41;
		case E_TRACKING_CONTROL_CUT_DN:
			return 42;
		case B_VOLUME:
			return 43;
		case E_VOLUME_UP:
			return 44;
		case E_VOLUME_DN:
			return 45;
		case B_SPECIAL:
			return 46;
		case E_SPECIAL_UP:
			return 47;
		case E_SPECIAL_DN:
			return 48;
		default:
			return -1;
	}
}


struct RGB {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

class Color {
	private:
		int hue;
		float saturation;
		float lightness;

	public:
		Color(int h, float s, float l) : hue(h), saturation(s), lightness(l) {}

		void setHSL(int h, float s, float l) {
			hue = h;
			saturation = s;
			lightness = l;
		}
		void setHue(int h) {
			hue = h;
		}
		int getHue() {
			return hue;
		}
		void setSaturation(float s) {
			saturation = s;
		}
		float getSaturation() {
			return saturation;
		}
		void setLightness(float l) {
			lightness = l;
		}
		float getLightness() {
			return lightness;
		}

		RGB getRGB() {
			RGB rgb;
			float c = (1 - abs(2 * lightness - 1)) * saturation;
			float h_prime = hue / 60.0;
			float x = c * (1 - abs(fmod(h_prime, 2) - 1));
			float m = lightness - c / 2;
			float r_temp, g_temp, b_temp;
			if (h_prime >= 0 && h_prime < 1) {
				r_temp = c;
				g_temp = x;
				b_temp = 0;
			} else if (h_prime >= 1 && h_prime < 2) {
				r_temp = x;
				g_temp = c;
				b_temp = 0;
			} else if (h_prime >= 2 && h_prime < 3) {
				r_temp = 0;
				g_temp = c;
				b_temp = x;
			} else if (h_prime >= 3 && h_prime < 4) {
				r_temp = 0;
				g_temp = x;
				b_temp = c;
			} else if (h_prime >= 4 && h_prime < 5) {
				r_temp = x;
				g_temp = 0;
				b_temp = c;
			} else {
				r_temp = c;
				g_temp = 0;
				b_temp = x;
			}
			rgb.r = (r_temp + m) * 255;
			rgb.g = (g_temp + m) * 255;
			rgb.b = (b_temp + m) * 255;
			return rgb;
		}
};

class Game {
	public:
		bool heldEncoder = false;
		bool isKeyboard = false;
		bool isMouse = false;
		bool isJoystick = false;
		// bool activeJoystick = false;
		// Joystick_* joystick;
		int miniDelay = 5;
		int shortDelay = 10;
		int mediumDelay = 50;
		int longDelay = 100;
		int longerDelay = 200;
		int longestDelay = 500;
		int tapDelay = 50;
		int recurrenceDelay = 100;
		Game() {};
		virtual void button(unsigned char pin, bool pressed) {
			// check if SerialUSB is available
			if (SerialUSB) {
				SerialUSB.print("Game::button(");
				SerialUSB.print(pin);
				SerialUSB.print(", ");
				SerialUSB.print(pressed);
				SerialUSB.println(")");
			}
		};
		virtual void begin() {
			if (isKeyboard) {
				SerialUSB.println("Keyboard->begin()");
				Keyboard.begin();
				Keyboard.releaseAll();
			}
		};
		virtual void end() {
			if (isKeyboard) {
				SerialUSB.println("Keyboard->end()");
				Keyboard.releaseAll();
				Keyboard.end();
			}
		};
		void hold(char key, unsigned char miliseconds = 0) {
			if (miliseconds) {
				Keyboard.press(key);
				delay(miliseconds);
				Keyboard.release(key);
			}
			else {
				Keyboard.press(key);
			}
		}
		void release(char key) {
			Keyboard.release(key);
		}
		void tap(char key, unsigned char times = 1) {
			for (unsigned char i = 0; i < times; i++) {
				Keyboard.press(key);
				delay(tapDelay);
				Keyboard.release(key);
				// check if last iteration
				if (i == times - 1) {
					return;
				}
				delay(recurrenceDelay);
			}
		}
		void releaseAll() {
			Keyboard.releaseAll();
		}
		void push(char key) {
			Keyboard.press(key);
		}
};

class Controller {
	public:
		const char* name;
		Game* game;
		Color* color;
		float intensity;
		Controller(
			const char* name,
			Game* game,
			Color* color,
			float intensity = 0.5
		) {
			this->name = name;
			this->game = game;
			this->color = color;
			this->intensity = intensity;
		};
		void button(unsigned char index, bool pressed) {
			this->game->button(index, pressed);
		};
		void begin() {
			// check if SerialUSB is available
			if (SerialUSB) {
				SerialUSB.print("Controller::begin(");
				SerialUSB.print(name);
				SerialUSB.println(")");
			}
			this->game->begin();
		};
		void end() {
			// check if SerialUSB is available
			if (SerialUSB) {
				SerialUSB.print("Controller::end(");
				SerialUSB.print(name);
				SerialUSB.println(")");
			}
			this->game->end();
		};
		float getIntensity() {
			return this->intensity;
		};
		void setIntensity(float intensity) {
			this->intensity = intensity;
			if (SerialUSB) {
				SerialUSB.print("Controller::setIntensity(");
				SerialUSB.print(intensity);
				SerialUSB.println(")");
			}
		};
};
