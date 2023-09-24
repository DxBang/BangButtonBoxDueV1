// Game Profile: Joystick

#ifndef BANG_h
	#include "Bang.h"
#endif

class GameJoystick : public Game {
	public:
		Joystick_* joystick;
		GameJoystick(
			Joystick_* joystick
		): joystick(joystick) {
			isJoystick = true;
		}
		void begin() {
			// check if joystick is available
			if (SerialUSB) {
				SerialUSB.println("GameJoystick::begin()");
			}
			if (isJoystick) {
				joystick->begin();
			}
			Game::begin();
		}
		void end() {
			// check if joystick is available
			if (SerialUSB) {
				SerialUSB.println("GameJoystick::end()");
			}
			if (isJoystick) {
				joystick->end();
			}
			Game::end();
		}
		void button(unsigned char pin, bool pressed) override {
			// check if SerialUSB is available
			int index = getButtonIndex(pin);
			if (SerialUSB) {
				SerialUSB.print("Joystick Button ");
				SerialUSB.print(pin);
				SerialUSB.print(" -> ");
				SerialUSB.print(index);
				SerialUSB.print("/");
				SerialUSB.print(49);
				SerialUSB.print(" = ");
				SerialUSB.println(pressed);
			}
			// check if joystick is available
			if (!joystick) {
				return;
			}
			switch (pin) {
				case E_SPECIAL_UP:
				case E_SPECIAL_DN:
				case E_VOLUME_UP:
				case E_VOLUME_DN:
				case E_BRAKE_BIAS_UP:
				case E_BRAKE_BIAS_DN:
				case E_TRACTION_CONTROL_UP:
				case E_TRACTION_CONTROL_DN:
				case E_ANTILOCK_BRAKING_SYSTEM_UP:
				case E_ANTILOCK_BRAKING_SYSTEM_DN:
				case E_ENGINE_MAP_UP:
				case E_ENGINE_MAP_DN:
				case E_TRACKING_CONTROL_CUT_UP:
				case E_TRACKING_CONTROL_CUT_DN:
					joystick->setButton(index, true);
					delay(shortDelay);
					joystick->setButton(index, false);
				break;
				default:
					joystick->setButton(index, pressed);
				break;
			}
		}
};
