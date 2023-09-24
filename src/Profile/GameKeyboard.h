// Game Profile: GameKeyboard

#ifndef BANG_h
	#include "Bang.h"
#endif

class GameKeyboard : public Game {
	public:
		GameKeyboard() {
			isKeyboard = true;
		}
		void button(unsigned char pin, bool pressed) override {
			if (SerialUSB) {
				SerialUSB.print("GameKeyboard::button(");
				SerialUSB.print(pin);
				SerialUSB.print(", ");
				SerialUSB.print(pressed);
			}

			switch (pin) {
				case B_ENGINE: // engine
					startEngine(pressed);
					break;
				case B_IGNITION: // ignition
					ignition(pressed);
					break;
				case B_PIT_LIMITER: // pit limiter
					pitLimiter(pressed);
					break;
				case B_CYCLE_LIGHTS: // lights
					cycleLights(pressed);
					break;
				case B_FLASH: // flash
					flash(pressed);
					break;
				case B_RAINLIGHTS: // rain lights
					rainLights(pressed);
					break;
				case B_INDICATOR_LEFT: // indicator left
					indicatorLeft(pressed);
					break;
				case B_INDICATOR_RIGHT: // indicator right
					indicatorRight(pressed);
					break;
				case B_CYCLE_WIPERS: // wipers
					cycleWiper(pressed);
					break;
				case B_NAMES: // names
					names(pressed);
					break;
				case B_CYCLE_HUD: // hud
					cycleHUD(pressed);
					break;
				case B_CYCLE_MAP: // map
					cycleMap(pressed);
					break;
				case B_NAVIGATION_UP: // navigation up
					navigationUp(pressed);
					break;
				case B_NAVIGATION_DOWN: // navigation down
					navigationDown(pressed);
					break;
				case B_NAVIGATION_LEFT: // navigation left
					navigationLeft(pressed);
					break;
				case B_NAVIGATION_RIGHT: // navigation right
					navigationRight(pressed);
					break;
				case B_SELECT: // select
					select(pressed);
					break;
				case B_BACK: // mfd
					cycleLeaderboard(pressed);
					break;
				case B_RACELOGIC: // racelogic
					raceLogic(pressed);
					break;
				case B_DASHBOARD_UP: // dashboard up
					dashboardUp(pressed);
					break;
				case B_DASHBOARD_DOWN: // dashboard down
					dashboardDown(pressed);
					break;
				case B_SAVE_REPLAY: // save replay
					saveReplay(pressed);
					break;
				case B_ADD_HIGHLIGHT: // add highlight
					addHighlight(pressed);
					break;
				case B_SAVE_HIGHLIGHTS: // save highlights
					saveHighlights(pressed);
					break;
				case B_CYCLE_CAMERA: // camera
					cycleCamera(pressed);
					break;
				case B_COCKPIT_CAM: // cockpit
					cockpit(pressed);
					break;
				case B_BONNET_CAM: // bonnet
					bonnet(pressed);
					break;
				case B_CHASE_CAM: // chase
					chase(pressed);
					break;
				case B_ENGINE_MAP: // engine map
					engineMap(pressed);
					break;
				case B_BRAKE_BIAS: // brake bias
					brakeBias(pressed);
					break;
				case B_ANTILOCK_BRAKING_SYSTEM: // antilock braking system
					antilockBrakingSystem(pressed);
					break;
				case B_TRACTION_CONTROL: // traction control
					tractionControl(pressed);
					break;
				case B_TRACKING_CONTROL_CUT: // tracking control cut
					tractionControlCut(pressed);
					break;
				case B_SPECIAL: // special
					special(pressed);
					break;
				case B_VOLUME: // volume
					volume(pressed);
					break;
				case E_ENGINE_MAP_UP: // engine map up
					engineMapUp(pressed);
					break;
				case E_ENGINE_MAP_DN: // engine map down
					engineMapDown(pressed);
					break;
				case E_BRAKE_BIAS_UP: // brake bias up
					brakeBiasUp(pressed);
					break;
				case E_BRAKE_BIAS_DN: // brake bias down
					brakeBiasDown(pressed);
					break;
				case E_ANTILOCK_BRAKING_SYSTEM_UP: // antilock braking system up
					antilockBrakingSystemUp(pressed);
					break;
				case E_ANTILOCK_BRAKING_SYSTEM_DN: // antilock braking system down
					antilockBrakingSystemDown(pressed);
					break;
				case E_TRACTION_CONTROL_UP: // traction control up
					tractionControlUp(pressed);
					break;
				case E_TRACTION_CONTROL_DN: // traction control down
					tractionControlDown(pressed);
					break;
				case E_TRACKING_CONTROL_CUT_UP: // tracking control cut up
					tractionControlCutUp(pressed);
					break;
				case E_TRACKING_CONTROL_CUT_DN: // tracking control cut down
					tractionControlCutDown(pressed);
					break;
				case E_SPECIAL_UP: // special up
					specialUp(pressed);
					break;
				case E_SPECIAL_DN: // special down	
					specialDown(pressed);
					break;
				case E_VOLUME_UP: // volume up
					volumeUp(pressed);
					break;
				case E_VOLUME_DN: // volume down	
					volumeDown(pressed);
					break;
			}
		}
		void begin() override {
			if (SerialUSB) {
			}
			Game::begin();
		}
		void end() override {
			if (SerialUSB) {
			}
			Game::end();
		}
	private:
		void startEngine(bool pressed) { // B_ENGINE
			if (pressed) {
				this->hold('m');
			} else {
				this->release('m');
			}
		}
		void ignition(bool pressed) { // B_IGNITION
			if (pressed) {
				this->hold('n');
			} else {
				this->release('n');
			}
		}
		void pitLimiter(bool pressed) { // B_PIT_LIMITER
			if (pressed) {
				this->hold('b');
			} else {
				this->release('b');
			}
		}
		void cycleLights(bool pressed) { // B_CYCLE_LIGHTS
			if (pressed) {
				this->hold('t');
			}
			else {
				this->release('t');
			}
		}
		void flash(bool pressed) { // B_FLASH
			if (pressed) {
				this->hold('g');
			}
			else {
				this->release('g');
			}
		}
		void rainLights(bool pressed) { // B_RAINLIGHTS
			if (pressed) {
				this->hold('y');
			}
			else {
				this->release('y');
			}
		}
		void cycleWiper(bool pressed) { // B_CYCLE_WIPERS
			if (pressed) {
				this->hold('u');
			}
			else {
				this->release('u');
			}
		}
		void cockpit(bool pressed) { // B_COCKPIT_CAM
			if (pressed) {
				this->hold('i');
			}
			else {
				this->release('i');
			}
		}
		void bonnet(bool pressed) { // B_BONNET_CAM
			if (pressed) {
				this->hold('o');
			}
			else {
				this->release('o');
			}
		}
		void chase(bool pressed) { // B_CHASE_CAM
			if (pressed) {
				this->hold('p');
			}
			else {
				this->release('p');
			}
		}
		void cycleCamera(bool pressed) { // B_CYCLE_CAMERA
			if (pressed) {
				this->hold('j');
			}
			else {
				this->release('j');
			}
		}
		void names(bool pressed) { // B_NAMES
			if (pressed) {
				this->hold(KEY_INSERT);
			}
			else {
				this->release(KEY_INSERT);
			}
		}
		void raceLogic(bool pressed) { // B_RACELOGIC
			if (pressed) {
				this->hold(KEY_HOME);
			}
			else {
				this->release(KEY_HOME);
			}
		}
		void dashboardUp(bool pressed) { // B_DASHBOARD_UP
			if (pressed) {
				this->hold(KEY_PAGE_UP);
			}
			else {
				this->release(KEY_PAGE_UP);
			}
		}
		void dashboardDown(bool pressed) { // B_DASHBOARD_DOWN
			if (pressed) {
				this->hold(KEY_PAGE_DOWN);
			}
			else {
				this->release(KEY_PAGE_DOWN);
			}
		}
		void cycleLeaderboard(bool pressed) { // B_CYCLE_MFD
			if (pressed) {
				this->hold('l');
			}
			else {
				this->release('l');
			}
		}
		void cycleHUD(bool pressed) { // B_CYCLE_HUD
			if (pressed) {
				this->hold('h');
			}
			else {
				this->release('h');
			}
		}
		void cycleMap(bool pressed) { // B_CYCLE_MAP
			if (pressed) {
				this->hold('j');
			}
			else {
				this->release('j');
			}
		}
		void select(bool pressed) { // B_SELECT
			if (pressed) {
				this->hold(KEY_RETURN);
			}
			else {
				this->release(KEY_RETURN);
			}
		}
		void navigationUp(bool pressed) { // B_NAVIGATION_UP
			if (pressed) {
				this->hold(KEY_UP_ARROW);
			}
			else {
				this->release(KEY_UP_ARROW);
			}
		}
		void navigationDown(bool pressed) { // B_NAVIGATION_DOWN
			if (pressed) {
				this->hold(KEY_DOWN_ARROW);
			}
			else {
				this->release(KEY_DOWN_ARROW);
			}
		}
		void navigationLeft(bool pressed) { // B_NAVIGATION_LEFT
			if (pressed) {
				this->hold(KEY_LEFT_ARROW);
			}
			else {
				this->release(KEY_LEFT_ARROW);
			}
		}
		void navigationRight(bool pressed) { // B_NAVIGATION_RIGHT
			if (pressed) {
				this->hold(KEY_RIGHT_ARROW);
			}
			else {
				this->release(KEY_RIGHT_ARROW);
			}
		}
		void indicatorLeft(bool pressed) { // B_INDICATOR_LEFT
			if (pressed) {
				this->hold(KEY_F5);
			}
			else {
				this->release(KEY_F5);
			}
		}
		void indicatorRight(bool pressed) { // B_INDICATOR_RIGHT
			if (pressed) {
				this->hold(KEY_F8);
			}
			else {
				this->release(KEY_F8);
			}
		}
		void saveReplay(bool pressed) { // B_SAVE_REPLAY
			if (pressed) {
				this->hold(KEY_F2);
			}
			else {
				this->release(KEY_F2);
			}
		}
		void addHighlight(bool pressed) { // B_ADD_HIGHLIGHT
			if (pressed) {
				this->hold(KEY_F3);
			}
			else {
				this->release(KEY_F3);
			}
		}
		void saveHighlights(bool pressed) { // B_SAVE_HIGHLIGHTS
			if (pressed) {
				this->hold(KEY_F4);
			}
			else {
				this->release(KEY_F4);
			}
		}
		void engineMap(bool pressed) { // B_ENGINE_MAP
			heldEncoder = pressed;
		}
		void engineMapUp(bool pressed) { // E_ENGINE_MAP_UP
			// SHIFT + E
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap(KEY_KP_5, 2);
			} else {
				this->tap(KEY_KP_5);
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void engineMapDown(bool pressed) { // E_ENGINE_MAP_DN
			// CTRL + E
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_5, 2);
			} else {
				this->tap(KEY_KP_5);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void brakeBias(bool pressed) { // B_BRAKE_BIAS
			heldEncoder = pressed;
		}
		void brakeBiasUp(bool pressed) { // E_BRAKE_BIAS_UP
			// SHIFT + B
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap(KEY_KP_7, 5);
			} else {
				this->tap(KEY_KP_7);
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void brakeBiasDown(bool pressed) { // E_BRAKE_BIAS_DN
			// CTRL + B
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_7, 5);
			} else {
				this->tap(KEY_KP_7);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void antilockBrakingSystem(bool pressed) { // B_ANTILOCK_BRAKING_SYSTEM
			heldEncoder = pressed;
		}
		void antilockBrakingSystemUp(bool pressed) { // E_ANTILOCK_BRAKING_SYSTEM_UP
			// SHIFT + A
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap(KEY_KP_1, 5);
			} else {
				this->tap(KEY_KP_1);
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void antilockBrakingSystemDown(bool pressed) { // E_ANTILOCK_BRAKING_SYSTEM_DN
			// CTRL + A
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_1, 5);
			} else {
				this->tap(KEY_KP_1);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void tractionControl(bool pressed) { // B_TRACTION_CONTROL
			heldEncoder = pressed;
		}
		void tractionControlUp(bool pressed) { // E_TRACTION_CONTROL_UP
			// SHIFT + T
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap(KEY_KP_9, 5);
			} else {
				this->tap(KEY_KP_9);
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void tractionControlDown(bool pressed) { // E_TRACTION_CONTROL_DN
			// CTRL + T
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_9, 5);
			} else {
				this->tap(KEY_KP_9);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void tractionControlCut(bool pressed) { // B_TRACKING_CONTROL_CUT
			heldEncoder = pressed;
		}
		void tractionControlCutUp(bool pressed) { // E_TRACKING_CONTROL_CUT_UP
			// SHIFT + Y
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap(KEY_KP_3, 5);
			} else {
				this->tap(KEY_KP_3);
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void tractionControlCutDown(bool pressed) { // E_TRACKING_CONTROL_CUT_DN
			// CTRL + Y
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_3, 5);
			} else {
				this->tap(KEY_KP_3);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void special(bool pressed) { // B_SPECIAL
			heldEncoder = pressed;
		}
		void specialUp(bool pressed) { // E_SPECIAL_UP
			// CTRL + Right Arrow
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_RIGHT_ARROW, 5);
			} else {
				this->tap(KEY_RIGHT_ARROW);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void specialDown(bool pressed) { // E_SPECIAL_DN
			// CTRL + Left Arrow
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_LEFT_ARROW, 5);
			} else {
				this->tap(KEY_LEFT_ARROW);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void volume(bool pressed) { // B_VOLUME
			heldEncoder = pressed;
		}
		void volumeUp(bool pressed) { // E_VOLUME_UP
			// NUM PLUS
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_PLUS, 5);
			} else {
				this->tap(KEY_KP_PLUS);
			}
			this->release(KEY_LEFT_CTRL);
		}
		void volumeDown(bool pressed) { // E_VOLUME_DN
			// NUM MINUS
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap(KEY_KP_MINUS, 10);
			} else {
				this->tap(KEY_KP_MINUS);
			}
			this->release(KEY_LEFT_CTRL);
		}
};
