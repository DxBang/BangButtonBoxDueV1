// Game Profile: ForzaMotorsport
#ifndef BANG_h
	#include "Bang.h"
#endif

class ForzaHorizon : public Game {
	public:
		ForzaHorizon() {
			isKeyboard = true;
		}
		void button(unsigned char pin, bool pressed) override {
			switch (pin) {
				case B_ADD_HIGHLIGHT:
					rewind(pressed);
				break;
				case B_IGNITION:
					toggleConvertible(pressed);
				break;
				case B_PIT_LIMITER:
					toggleConvertible(pressed);
				break;
				case B_ENGINE:
					horn(pressed);
				break;
				case B_CYCLE_LIGHTS:
					anna(pressed);
				break;
				case B_FLASH:
					miniLeaderboard(pressed);
				break;
				case B_NAMES:
					cycleCamera(pressed);
				break;
				case B_RACELOGIC:
					telemetry(pressed);
				break;
				case B_DASHBOARD_UP:
					telemetryPrevious(pressed);
				break;
				case B_DASHBOARD_DOWN:
					telemetryNext(pressed);
				break;
				case B_NAVIGATION_UP:
					linkOne(pressed);
				break;
				case B_NAVIGATION_DOWN:
					linkTwo(pressed);
				break;
				case B_NAVIGATION_LEFT:
					linkThree(pressed);
				break;
				case B_NAVIGATION_RIGHT:
					linkFour(pressed);
				break;
				case B_CYCLE_CAMERA:
					lookBackward(pressed);
				break;
				case B_COCKPIT_CAM:
					lookLeft(pressed);
				break;
				case B_BONNET_CAM:
					lookForward(pressed);
				break;
				case B_CHASE_CAM:
					lookRight(pressed);
				break;
				case B_CYCLE_MAP:
					shiftUp(pressed);
				break;
				case B_CYCLE_HUD:
					shiftDown(pressed);
				break;
			}
		}
	private:
		void rewind(bool pressed) { // B_ADD_HIGHLIGHT
			if (pressed) {
				this->hold('r');
			}
			else {
				this->release('r');
			}
		}
		void activate(bool pressed) {
			if (pressed) {
				this->hold(KEY_RETURN);
			}
			else {
				this->release(KEY_RETURN);
			}
		}
		void shiftUp(bool pressed) { // B_IGNITION
			if (pressed) {
				this->hold(KEY_LEFT_SHIFT);
				this->tap('e');
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void shiftDown(bool pressed) { // B_PIT_LIMITER
			if (pressed) {
				this->hold(KEY_LEFT_SHIFT);
				this->tap('q');
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void clutch(bool pressed) {
			if (pressed) {
				this->hold(KEY_LEFT_SHIFT);
			}
			else {
				this->release(KEY_LEFT_SHIFT);
			}
		}
		void cycleCamera(bool pressed) {
			if (pressed) {
				this->tap(KEY_TAB);
			}
		}
		void toggleConvertible(bool pressed) { // B_FLASH
			if (pressed) {
				this->hold('g');
			}
			else {
				this->release('g');
			}
		}
		void lookForward(bool pressed) { // B_NAVIGATION_UP
			if (pressed) {
				this->hold(KEY_UP_ARROW);
			}
			else {
				this->release(KEY_UP_ARROW);
			}
		}
		void lookBackward(bool pressed) { // B_NAVIGATION_DOWN
			if (pressed) {
				this->hold(KEY_DOWN_ARROW);
			}
			else {
				this->release(KEY_DOWN_ARROW);
			}
		}
		void lookLeft(bool pressed) { // B_NAVIGATION_LEFT
			if (pressed) {
				this->hold(KEY_LEFT_ARROW);
			}
			else {
				this->release(KEY_LEFT_ARROW);
			}
		}
		void lookRight(bool pressed) { // B_NAVIGATION_RIGHT
			if (pressed) {
				this->hold(KEY_RIGHT_ARROW);
			}
			else {
				this->release(KEY_RIGHT_ARROW);
			}
		}
		void telemetry(bool pressed) { // B_RACELOGIC
			if (pressed) {
				this->tap('t');
			}
		}
		void telemetryNext(bool pressed) { // B_DASHBOARD_DOWN
			if (pressed) {
				this->tap(KEY_PAGE_UP);
			}
		}
		void telemetryPrevious(bool pressed) { // B_DASHBOARD_UP
			if (pressed) {
				this->tap(KEY_PAGE_DOWN);
			}
		}
		void map(bool pressed) {
			if (pressed) {
				this->tap('m');
			}
		}
		void horn(bool pressed) { // B_ENGINE
			if (pressed) {
				this->hold('h');
			}
			else {
				this->release('h');
			}
		}
		void miniLeaderboard(bool pressed) { // B_NAMES
			if (pressed) {
				this->tap('l');
			}
		}
		void photoMode(bool pressed) {
			if (pressed) {
				this->tap('p');
			}
		}
		void radioNext(bool pressed) {
			if (pressed) {
				this->tap(KEY_KP_PLUS);
			}
		}
		void radioPrevious(bool pressed) {
			if (pressed) {
				this->tap(KEY_KP_MINUS);
			}
		}
		void anna(bool pressed) { // B_CYCLE_HUD
			if (pressed) {
				this->tap('c');
			}
		}
		void link(bool pressed) { // B_CYCLE_MAP
			if (pressed) {
				this->tap('v');
			}
		}
		void annaOne(bool pressed) { // B_COCKPIT_CAM
			if (pressed) {
				this->tap('c');
				delay(longDelay);
				this->tap('1');
			}
		}
		void annaTwo(bool pressed) { // B_BONNET_CAM
			if (pressed) {
				this->tap('c');
				delay(longDelay);
				this->tap('2');
			}
		}
		void annaThree(bool pressed) { // B_CHASE_CAM
			if (pressed) {
				this->tap('c');
				delay(longDelay);
				this->tap('3');
			}
		}
		void annaFour(bool pressed) { // B_BUMPER_CAM
			if (pressed) {
				this->tap('c');
				delay(longDelay);
				this->tap('4');
			}
		}
		void linkOne(bool pressed) { // B_NAVIGATION_UP
			if (pressed) {
				this->tap('v');
				delay(longDelay);
				this->tap('1');
			}
		}
		void linkTwo(bool pressed) { // B_NAVIGATION_DOWN
			if (pressed) {
				this->tap('v');
				delay(longDelay);
				this->tap('2');
			}
		}
		void linkThree(bool pressed) { // B_NAVIGATION_LEFT
			if (pressed) {
				this->tap('v');
				delay(longDelay);
				this->tap('3');
			}
		}
		void linkFour(bool pressed) { // B_NAVIGATION_RIGHT
			if (pressed) {
				this->tap('v');
				delay(longDelay);
				this->tap('4');
			}
		}
};