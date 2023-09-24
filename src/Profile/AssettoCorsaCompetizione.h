// Game Profile: AssettoCorsaCompetizione
#ifndef BANG_h
	#include "Bang.h"
#endif

class AssettoCorsaCompetizione : public Game {
	public:
		int tapDelay = 100;
		AssettoCorsaCompetizione() {
			isKeyboard = true;
		}
		void button(unsigned char pin, bool pressed) override {
			if (SerialUSB) {
				SerialUSB.print("AssettoCorsaCompetizione::button(");
				SerialUSB.print(pin);
				SerialUSB.print(", ");
				SerialUSB.print(pressed);
				SerialUSB.println(")");
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
					// back(pressed);
					mfdElectronics(pressed);
					break;
				case B_RACELOGIC: // racelogic
					// raceLogic(pressed);
					timeTable(pressed);
					break;
				case B_DASHBOARD_UP: // dashboard up
					// dashboardUp(pressed);
					mfdPositions(pressed);
					break;
				case B_DASHBOARD_DOWN: // dashboard down
					// dashboardDown(pressed);
					mfdPitstop(pressed);
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
				SerialUSB.println("AssettoCorsaCompetizione::begin()");
			}
			Game::begin();
		}
		void end() override {
			if (SerialUSB) {
				SerialUSB.println("AssettoCorsaCompetizione::end()");
			}
			Game::end();
		}
	private:
		void startEngine(bool pressed) { // B_ENGINE
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("startEngine");
				}
				this->hold('e');
			} else {
				this->release('e');
			}
		}
		void ignition(bool pressed) { // B_IGNITION
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("ignition");
				}
				this->hold(KEY_LEFT_SHIFT);
				this->hold('i');
			} else {
				this->release('i');
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void pitLimiter(bool pressed) { // B_PIT_LIMITER
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("pitLimiter");
				}
				this->hold(KEY_LEFT_ALT);
				this->hold('l');
			} else {
				this->release('l');
				this->release(KEY_LEFT_ALT);
			}
		}
		void cycleLights(bool pressed) { // B_CYCLE_LIGHTS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleLights");
				}
				this->tap('l');
			}
		}
		void flash(bool pressed) { // B_FLASH
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("flash");
				}
				this->hold(KEY_LEFT_SHIFT);
				this->tap('l');
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void rainLights(bool pressed) { // B_RAINLIGHTS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("rainLights");
				}

				this->hold(KEY_LEFT_CTRL);
				this->tap('l');
				this->release(KEY_LEFT_CTRL);
			}
		}
		void indicatorLeft(bool pressed) { // B_INDICATOR_LEFT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("indicatorLeft");
				}
				this->hold(KEY_LEFT_ALT);
				this->tap(KEY_LEFT_ARROW);
				this->release(KEY_LEFT_ALT);
			}
		}
		void indicatorRight(bool pressed) { // B_INDICATOR_RIGHT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("B_INDICATOR_RIGHT");
				}
				this->hold(KEY_LEFT_ALT);
				this->tap(KEY_RIGHT_ARROW);
				this->release(KEY_LEFT_ALT);
			}
		}
		void cycleWiper(bool pressed) { // B_CYCLE_WIPERS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleWiper");
				}
				this->hold(KEY_LEFT_ALT);
				this->tap('w');
				this->release(KEY_LEFT_ALT);
			}
		}
		void names(bool pressed) { // B_NAMES
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("names");
				}
				this->tap('v');
			}
		}
		void cycleMFD(bool pressed) { // B_BACK
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleMFD");
				}
				this->tap(KEY_INSERT);
			}
		}
		void cycleHUD(bool pressed) { // B_CYCLE_HUD
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleHUD");
				}
				this->tap(KEY_F2);
			}
		}
		void cycleMap(bool pressed) { // B_CYCLE_MAP
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleMap");
				}
				this->hold(KEY_LEFT_SHIFT);
				this->tap('m');
				this->release(KEY_LEFT_SHIFT);	
			}
		}
		void navigationUp(bool pressed) { // B_NAVIGATION_UP
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("navigationUp");
				}
				this->tap(KEY_UP_ARROW);
			}
		}
		void navigationDown(bool pressed) { // B_NAVIGATION_DOWN
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("navigationDown");
				}
				this->tap(KEY_DOWN_ARROW);
			}
		}
		void navigationLeft(bool pressed) { // B_NAVIGATION_LEFT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("navigationLeft");
				}
				this->tap(KEY_LEFT_ARROW);
			}
		}
		void navigationRight(bool pressed) { // B_NAVIGATION_RIGHT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("navigationRight");
				}
				this->tap(KEY_RIGHT_ARROW);
			}
		}
		void select(bool pressed) { // B_SELECT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("select");
				}
				this->tap(KEY_RETURN);
			}
		}
		void raceLogic(bool pressed) { // B_RACELOGIC
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("raceLogic");
				}
				this->hold(KEY_LEFT_ALT);
				this->tap('d');
				this->release(KEY_LEFT_ALT);
			}
		}
		void dashboardUp(bool pressed) { // B_DASHBOARD_UP
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("dashboardUp");
				}
				this->hold(KEY_LEFT_SHIFT);
				this->tap('d');
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void dashboardDown(bool pressed) { // B_DASHBOARD_DOWN
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("dashboardDown");
				}
				this->hold(KEY_LEFT_CTRL);
				this->tap('d');
				this->release(KEY_LEFT_CTRL);
			}
		}
		void timeTable(bool pressed) { // B_RACELOGIC
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("timeTable");
				}
				this->hold(KEY_TAB);
			}
			else {
				this->release(KEY_TAB);
			}
		}
		void mfdElectronics(bool pressed) { // B_MFD_ELECTRONICS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("mfdElectronics");
				}
				this->tap('o');
			}
		}
		void mfdPitstop(bool pressed) { // B_MFD_PIT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("mfdPitstop");
				}
				this->tap('p');
			}
		}
		void mfdStandings(bool pressed) { // B_MFD_STANDINGS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("mfdStandings");
				}
				this->tap('i');
			}
		}
		void mfdPositions(bool pressed) { // B_MFD_POSITIONS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("mfdPositions");
				}
				this->tap('u');
			}
		}
		void saveReplay(bool pressed) { // B_SAVE_REPLAY
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("saveReplay");
				}
				this->tap('m');
			}
		}
		void addHighlight(bool pressed) { // B_ADD_HIGHLIGHT
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("addHighlight");
				}
				this->hold(KEY_LEFT_ALT);
				this->tap('m');
				this->release(KEY_LEFT_ALT);
			}
		}
		void saveHighlights(bool pressed) { // B_SAVE_HIGHLIGHTS
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("saveHighlights");
				}
				this->hold(KEY_LEFT_CTRL);
				this->tap('m');
				this->release(KEY_LEFT_CTRL);
			}
		}
		void cycleCamera(bool pressed) { // B_CYCLE_CAMERA
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cycleCamera");
				}
				this->tap(KEY_F1);
			}
		}
		void cockpit(bool pressed) { // B_COCKPIT_CAM
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("cockpit");
				}
				this->tap('1');
			}
		}
		void bonnet(bool pressed) { // B_BONNET_CAM
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("bonnet");
				}
				this->tap('2');
			}
		}
		void chase(bool pressed) { // B_CHASE_CAM
			if (pressed) {
				if (SerialUSB) {
					SerialUSB.println("chase");
				}
				this->tap('3');
			}
		}
		void engineMap(bool pressed) { // B_ENGINE_MAP
			heldEncoder = pressed;
		}
		void engineMapUp(bool pressed) { // E_ENGINE_MAP_UP
			// SHIFT + E
			if (SerialUSB) {
				SerialUSB.println("engineMapUp: SHIFT + E");
			}
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap('e', 2);
			} else {
				this->tap('e');
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void engineMapDown(bool pressed) { // E_ENGINE_MAP_DN
			// CTRL + E
			if (SerialUSB) {
				SerialUSB.println("engineMapDown: CTRL + E");
			}
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap('e', 2);
			} else {
				this->tap('e');
			}
			this->release(KEY_LEFT_CTRL);
		}
		void brakeBias(bool pressed) { // B_BRAKE_BIAS
			heldEncoder = pressed;
		}
		void brakeBiasUp(bool pressed) { // E_BRAKE_BIAS_UP
			// SHIFT + B
			if (SerialUSB) {
				SerialUSB.println("brakeBiasUp: SHIFT + B");
			}
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap('b', 10);
			} else {
				this->tap('b');
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void brakeBiasDown(bool pressed) { // E_BRAKE_BIAS_DN
			// CTRL + B
			if (SerialUSB) {
				SerialUSB.println("brakeBiasDown: CTRL + B");
			}
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap('b', 10);
			} else {
				this->tap('b');
			}
			this->release(KEY_LEFT_CTRL);
		}
		void antilockBrakingSystem(bool pressed) { // B_ANTILOCK_BRAKING_SYSTEM
			heldEncoder = pressed;
		}
		void antilockBrakingSystemUp(bool pressed) { // E_ANTILOCK_BRAKING_SYSTEM_UP
			// SHIFT + A
			if (SerialUSB) {
				SerialUSB.println("antilockBrakingSystemUp: SHIFT + A");
			}
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap('a', 2);
			} else {
				this->tap('a');
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void antilockBrakingSystemDown(bool pressed) { // E_ANTILOCK_BRAKING_SYSTEM_DN
			// CTRL + A
			if (SerialUSB) {
				SerialUSB.println("antilockBrakingSystemDown: CTRL + A");
			}
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap('a', 2);
			} else {
				this->tap('a');
			}
			this->release(KEY_LEFT_CTRL);
		}
		void tractionControl(bool pressed) { // B_TRACTION_CONTROL
			heldEncoder = pressed;
		}
		void tractionControlUp(bool pressed) { // E_TRACTION_CONTROL_UP
			// SHIFT + T
			if (SerialUSB) {
				SerialUSB.println("tractionControlUp: SHIFT + T");
			}
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap('t', 2);
			} else {
				this->tap('t');
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void tractionControlDown(bool pressed) { // E_TRACTION_CONTROL_DN
			// CTRL + T
			if (SerialUSB) {
				SerialUSB.println("tractionControlDown: CTRL + T");
			}
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap('t', 2);
			} else {
				this->tap('t');
			}
			this->release(KEY_LEFT_CTRL);
		}
		void tractionControlCut(bool pressed) { // B_TRACKING_CONTROL_CUT
			heldEncoder = pressed;
		}
		void tractionControlCutUp(bool pressed) { // E_TRACKING_CONTROL_CUT_UP
			// SHIFT + Y
			if (SerialUSB) {
				SerialUSB.println("tractionControlCutUp: SHIFT + Y");
			}
			this->hold(KEY_LEFT_SHIFT);
			if (heldEncoder) {
				this->tap('y', 2);
			} else {
				this->tap('y');
			}
			this->release(KEY_LEFT_SHIFT);
		}
		void tractionControlCutDown(bool pressed) { // E_TRACKING_CONTROL_CUT_DN
			// CTRL + Y
			if (SerialUSB) {
				SerialUSB.println("tractionControlCutDown: CTRL + Y");
			}
			this->hold(KEY_LEFT_CTRL);
			if (heldEncoder) {
				this->tap('y', 2);
			} else {
				this->tap('y');
			}
			this->release(KEY_LEFT_CTRL);
		}
		void special(bool pressed) { // B_SPECIAL
			heldEncoder = pressed;
		}
		void specialUp(bool pressed) { // E_SPECIAL_UP
			// CTRL + Right Arrow
			if (SerialUSB) {
				SerialUSB.println("specialUp: CTRL + Right Arrow");
			}
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
			if (SerialUSB) {
				SerialUSB.println("specialDown: CTRL + Left Arrow");
			}
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
			if (SerialUSB) {
				SerialUSB.println("volumeUp: NUM PLUS");
			}
			if (heldEncoder) {
				this->tap(KEY_KP_PLUS, 10);
			} else {
				this->tap(KEY_KP_PLUS);
			}
		}
		void volumeDown(bool pressed) { // E_VOLUME_DN
			// NUM MINUS
			if (SerialUSB) {
				SerialUSB.println("volumeDown: NUM MINUS");
			}
			if (heldEncoder) {
				this->tap(KEY_KP_MINUS, 10);
			} else {
				this->tap(KEY_KP_MINUS);
			}
		}
};
