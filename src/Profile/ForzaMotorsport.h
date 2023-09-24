// Game Profile: ForzaMotorsport
#ifndef BANG_h
	#include "Bang.h"
#endif

class ForzaMotorsport : public Game {
	public:
		ForzaMotorsport() {
			isKeyboard = true;
		}
		void begin() override {
			// Set the keyboard to the correct mode
			Keyboard.begin();
			Keyboard.releaseAll();
		}
		void end() override {
			// Set the keyboard to the correct mode
			Keyboard.releaseAll();
			Keyboard.end();
		}
		void button(unsigned char pin, bool pressed) override {
			switch (pin) {
				case B_ADD_HIGHLIGHT:
					rewind(pressed);
				break;
				case B_IGNITION:
					shiftUp(pressed);
				break;
				case B_PIT_LIMITER:
					shiftDown(pressed);
				break;
				case B_ENGINE:
					horn(pressed);
				break;
				case B_CYCLE_LIGHTS:
					anna(pressed);
				break;
				case B_FLASH:
					toggleConvertible(pressed);
				break;

			}
		}
	private:
		void rewind(bool pressed) { // B_ADD_HIGHLIGHT
			if (pressed) {
				Keyboard.press('r');
			}
			else {
				Keyboard.release('r');
			}
		}
		void accelerate(bool pressed) {
			if (pressed) {
				Keyboard.press('w');
			}
			else {
				Keyboard.release('w');
			}
		}
		void brake(bool pressed) {
			if (pressed) {
				Keyboard.press('s');
			}
			else {
				Keyboard.release('s');
			}
		}
		void steerLeft(bool pressed) {
			if (pressed) {
				Keyboard.press('a');
			}
			else {
				Keyboard.release('a');
			}
		}
		void steerRight(bool pressed) {
			if (pressed) {
				Keyboard.press('d');
			}
			else {
				Keyboard.release('d');
			}
		}
		void activate(bool pressed) {
			if (pressed) {
				Keyboard.press(KEY_RETURN);
			}
			else {
				Keyboard.release(KEY_RETURN);
			}
		}
		void eBrake(bool pressed) {
			if (pressed) {
				Keyboard.press(' ');
			}
			else {
				Keyboard.release(' ');
			}
		}
		void shiftUp(bool pressed) { // B_IGNITION
			if (pressed) {
				Keyboard.press('e');
			}
			else {
				Keyboard.release('e');
			}
		}
		void shiftDown(bool pressed) { // B_PIT_LIMITER
			if (pressed) {
				Keyboard.press('q');
			}
			else {
				Keyboard.release('q');
			}
		}
		void clutch(bool pressed) {
			if (pressed) {
				Keyboard.press(KEY_LEFT_SHIFT);
			}
			else {
				Keyboard.release(KEY_LEFT_SHIFT);
			}
		}
		void cycleCamera(bool pressed) {
			if (pressed) {
				Keyboard.press(KEY_TAB);
			}
			else {
				Keyboard.release(KEY_TAB);
			}
		}
		void toggleConvertible(bool pressed) { // B_FLASH
			if (pressed) {
				Keyboard.press('g');
			}
			else {
				Keyboard.release('g');
			}
		}
		void lookForward(bool pressed) { // B_NAVIGATION_UP
			if (pressed) {
				Keyboard.press(KEY_UP_ARROW);
			}
			else {
				Keyboard.release(KEY_UP_ARROW);
			}
		}
		void lookBackward(bool pressed) { // B_NAVIGATION_DOWN
			if (pressed) {
				Keyboard.press(KEY_DOWN_ARROW);
			}
			else {
				Keyboard.release(KEY_DOWN_ARROW);
			}
		}
		void lookLeft(bool pressed) { // B_NAVIGATION_LEFT
			if (pressed) {
				Keyboard.press(KEY_LEFT_ARROW);
			}
			else {
				Keyboard.release(KEY_LEFT_ARROW);
			}
		}
		void lookRight(bool pressed) { // B_NAVIGATION_RIGHT
			if (pressed) {
				Keyboard.press(KEY_RIGHT_ARROW);
			}
			else {
				Keyboard.release(KEY_RIGHT_ARROW);
			}
		}
		void telemetry(bool pressed) { // B_RACELOGIC
			if (pressed) {
				Keyboard.press('t');
			}
			else {
				Keyboard.release('t');
			}
		}
		void telemetryNext(bool pressed) { // B_DASHBOARD_DOWN
			if (pressed) {
				Keyboard.press(KEY_PAGE_UP);
			}
			else {
				Keyboard.release(KEY_PAGE_UP);
			}
		}
		void telemetryPrevious(bool pressed) { // B_DASHBOARD_UP
			if (pressed) {
				Keyboard.press(KEY_PAGE_DOWN);
			}
			else {
				Keyboard.release(KEY_PAGE_DOWN);
			}
		}
		void map(bool pressed) {
			if (pressed) {
				Keyboard.press('m');
			}
			else {
				Keyboard.release('m');
			}
		}
		void horn(bool pressed) { // B_ENGINE
			if (pressed) {
				Keyboard.press('h');
			}
			else {
				Keyboard.release('h');
			}
		}
		void miniLeaderboard(bool pressed) { // B_NAMES
			if (pressed) {
				Keyboard.press('l');
			}
			else {
				Keyboard.release('l');
			}
		}
		void photoMode(bool pressed) {
			if (pressed) {
				Keyboard.press('p');
			}
			else {
				Keyboard.release('p');
			}
		}
		void radioNext(bool pressed) {
			if (pressed) {
				Keyboard.press(KEY_KP_PLUS);
			}
			else {
				Keyboard.release(KEY_KP_PLUS);
			}
		}
		void radioPrevious(bool pressed) {
			if (pressed) {
				Keyboard.press(KEY_KP_MINUS);
			}
			else {
				Keyboard.release(KEY_KP_MINUS);
			}
		}
		void anna(bool pressed) { // B_CYCLE_HUD
			if (pressed) {
				Keyboard.press('c');
			}
			else {
				Keyboard.release('c');
			}
		}
		void link(bool pressed) { // B_CYCLE_MAP
			if (pressed) {
				Keyboard.press('v');
			}
			else {
				Keyboard.release('v');
			}
		}
		void annaLinkOne(bool pressed) { // B_COCKPIT_CAM
			if (pressed) {
				Keyboard.press('1');
			}
			else {
				Keyboard.release('1');
			}
		}
		void annaLinkTwo(bool pressed) { // B_BONNET_CAM
			if (pressed) {
				Keyboard.press('2');
			}
			else {
				Keyboard.release('2');
			}
		}
		void annaLinkThree(bool pressed) { // B_CHASE_CAM
			if (pressed) {
				Keyboard.press('3');
			}
			else {
				Keyboard.release('3');
			}
		}
		void annaLinkFour(bool pressed) { // B_CYCLE_CAMERA
			if (pressed) {
				Keyboard.press('4');
			}
			else {
				Keyboard.release('4');
			}
		}
};