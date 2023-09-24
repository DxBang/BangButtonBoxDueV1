#include <Arduino.h>
#include <sam.h>
#include <HID.h>
#include <Keyboard.h>
#include <Joystick.h>
#include <Bounce2.h>
#include <RotaryEncoder.h>
#include <Bang.h>
#include <Profile/GameJoystick.h>
#include <Profile/GameKeyboard.h>
#include <Profile/AssettoCorsaCompetizione.h>
#include <Profile/ForzaMotorsport.h>
#include <Profile/ForzaHorizon.h>
#include <Profile/NoFunctions.h>

#define DEBUG true
#define BENCHMARK true

// all luminosity groups in an array
const unsigned char luminosityGroups[] = {
	LUMINOSITY_RED_1,
	LUMINOSITY_RED_2,
	LUMINOSITY_RED_3,
	LUMINOSITY_YELLOW,
	LUMINOSITY_GREEN,
	LUMINOSITY_BLUE,
	LUMINOSITY_WHITE,
};

const unsigned char luminosityGroupsLimit[] = {
	200, // 5 red
	200, // 5 red
	200, // 5 red
	230, // 2 yellow
	180, // 3 green
	255, // 3 blue
	250, // 4 white
};

// number of luminosity groups
const unsigned char luminosityGroupsCount = sizeof(luminosityGroups) / sizeof(luminosityGroups[0]);

#define FEEDBACK_VISUAL_TIME 200
#define FEEDBACK_VISUAL_MIN 50
#define FEEDBACK_VISUAL_MAX 200
#define FEEDBACK_VISUAL_CALC 255
#define FEEDBACK_VIBRATE_TIME 300
#define FEEDBACK_VIBRATE_MIN 200
#define FEEDBACK_VIBRATE_MAX 250
#define FEEDBACK_VIBRATE_CALC 250

#define INTENSITY_MAX 1.0
#define INTENSITY_MIN 0.0
#define INTENSITY_STEP 0.05
#define INTENSITY_STEP_SMALL 0.005
#define INTENSITY_DEFAULT 0.5

#define LIGHTNESS_MAX 0.65
#define LIGHTNESS_MIN 0.0
#define LIGHTNESS_STEP 0.05
#define LIGHTNESS_STEP_SMALL 0.005
#define LIGHTNESS_DEFAULT 0.5

#define BOOT_DELAY 200

#define BUTTON_STATE_IDLE 0
#define BUTTON_STATE_PRESSED 1
#define BUTTON_STATE_HELD 2
#define BUTTON_STATE_RELEASED 3
#define BUTTON_DEBOUNCE_TIME 50
#define BUTTON_HOLD_TIME 1000
#define BUTTON_ACTIVE LOW

// sleep timer for low power mode after X minutes
#define SLEEP_TIME 900000 // 900000, (test 10000)
// hyper sleep timer for low power mode after X*2 minutes
#define HYPER_SLEEP_TIME 1800000 // 1800000 (test 20000)

// define default clcok speed
#define DEFAULT_CLOCK_SPEED F_CPU


unsigned long loopCount;
unsigned long benchTime;
unsigned long timer = 0;
unsigned long lastFeedbackVisual = 0;
unsigned long lastFeedbackVibrate = 0;
unsigned long sleepTimer = 0;
unsigned char sleeping = 0;
float sleepIntensity = 0;
float sleepLightness = 0;

unsigned char controllerIndex = 0;

float intensity = INTENSITY_DEFAULT;
bool buttonPressed = false;

void hyperSleep();
void sleep();
void wakeUp();
void stayAwake();

int minMax(double value, int min, int max) {
	if (value < min) {
		value = min;
	}
	else if (value > max) {
		value = max;
	}
	return round(value);
};

void feedbackVisual(bool toggle) {
	if (toggle) {
		analogWrite(VISUAL_PIN,
			minMax(
				FEEDBACK_VISUAL_CALC * intensity,
				FEEDBACK_VISUAL_MIN,
				FEEDBACK_VISUAL_MAX
			)
		);
		lastFeedbackVisual = timer;
	} else {
		analogWrite(VISUAL_PIN, 0);
		lastFeedbackVisual = 0;
	}
}
void feedbackVibrate(bool toggle) {
	if (toggle) {
		analogWrite(VIBRATE_PIN,
			minMax(
				FEEDBACK_VIBRATE_CALC * intensity,
				FEEDBACK_VIBRATE_MIN,
				FEEDBACK_VIBRATE_MAX
			)
		);
		lastFeedbackVibrate = timer;
	} else {
		analogWrite(VIBRATE_PIN, 0);
		lastFeedbackVibrate = 0;
	}
}
void setRGB(unsigned char r, unsigned char g, unsigned char b) {
	analogWrite(R_PIN, r);
	analogWrite(G_PIN, g);
	analogWrite(B_PIN, b);
}

void setLuminosity(float strength) {
	/*
	SerialUSB.print("Luminosity: ");
	SerialUSB.print(strength);
	SerialUSB.print(" -> ");
	SerialUSB.println((unsigned char) 255 * strength);
	*/
	// set all luminosity groups to the same value
	for (unsigned char i = 0; i < luminosityGroupsCount; i++) {
		analogWrite(luminosityGroups[i], (unsigned char) luminosityGroupsLimit[i] * strength);
	}
}

void checkFeedback() {
	if (lastFeedbackVisual == 0 && lastFeedbackVibrate == 0) {
		return;
	}
	if (buttonPressed) {
		return;
	}
	if (timer - lastFeedbackVisual > FEEDBACK_VISUAL_TIME) {
		analogWrite(VISUAL_PIN, 0);
		lastFeedbackVisual = 0;
	}
	if (timer - lastFeedbackVibrate > FEEDBACK_VIBRATE_TIME) {
		analogWrite(VIBRATE_PIN, 0);
		lastFeedbackVibrate = 0;
	}
}
void bootAnimation() {
	// run thru all the colors the hue send to setRGB()
	delay(3000);
	Color color = Color(0, 1.0, 0.5);
	RGB rgb = color.getRGB();
	if (DEBUG) {
		SerialUSB.println("Boot RGB Animation");
	}
	for (unsigned int i = 0; i < 360; i++) {
		color.setHue(i);
		rgb = color.getRGB();
		setRGB(rgb.r, rgb.g, rgb.b);
		setLuminosity(i / 720.0);
		delay(10);
	}
	if (DEBUG) {
		SerialUSB.println("Boot RGB Animation Done");
	}
}

void bootFeedback(unsigned char code) {
	switch (code) {
		case 1:
			feedbackVisual(0);
			feedbackVibrate(1);
			break;
		case 2:
			feedbackVisual(1);
			feedbackVibrate(0);
			break;
		case 3:
			feedbackVisual(1);
			feedbackVibrate(1);
			break;
		default:
			feedbackVisual(0);
			feedbackVibrate(0);
			break;
	}
}

// make an array of all the buttons
const unsigned char buttonPins[] = {
	B_MODE,
	B_IGNITION,
	B_ENGINE,
	B_PIT_LIMITER,
	B_CYCLE_LIGHTS,
	B_FLASH,
	B_RAINLIGHTS,
	B_INDICATOR_LEFT,
	B_INDICATOR_RIGHT,
	B_CYCLE_WIPERS,
	B_COCKPIT_CAM,
	B_BONNET_CAM,
	B_CHASE_CAM,
	B_CYCLE_CAMERA,
	B_NAMES,
	B_RACELOGIC,
	B_DASHBOARD_UP,
	B_DASHBOARD_DOWN,
	B_SAVE_REPLAY,
	B_ADD_HIGHLIGHT,
	B_SAVE_HIGHLIGHTS,
	B_CYCLE_HUD,
	B_CYCLE_MAP,
	B_NAVIGATION_UP,
	B_NAVIGATION_DOWN,
	B_NAVIGATION_LEFT,
	B_NAVIGATION_RIGHT,
	B_SELECT,
	B_BACK,
	B_VOLUME,
	B_SPECIAL,
	B_BRAKE_BIAS,
	B_TRACTION_CONTROL,
	B_ENGINE_MAP,
	B_ANTILOCK_BRAKING_SYSTEM,
	B_TRACKING_CONTROL_CUT
};
const unsigned char buttonsCount = sizeof(buttonPins) / sizeof(buttonPins[0]);
unsigned char buttonPositions[buttonsCount] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0
};
Bounce * buttons = new Bounce[buttonsCount];

// make an array of all the rotary encoders for A and B directions
const unsigned char encoderPins[8][2] = {
	{E_MODE_UP, E_MODE_DN},
	{E_VOLUME_UP, E_VOLUME_DN},
	{E_SPECIAL_UP, E_SPECIAL_DN},
	{E_BRAKE_BIAS_UP, E_BRAKE_BIAS_DN},
	{E_TRACTION_CONTROL_UP, E_TRACTION_CONTROL_DN},
	{E_ENGINE_MAP_UP, E_ENGINE_MAP_DN},
	{E_ANTILOCK_BRAKING_SYSTEM_UP, E_ANTILOCK_BRAKING_SYSTEM_DN},
	{E_TRACKING_CONTROL_CUT_UP, E_TRACKING_CONTROL_CUT_DN},
};
const unsigned char encodersCount = sizeof(encoderPins) / sizeof(encoderPins[0]);
// store encoders positions
int encoderPositions[encodersCount] = { 0, 0, 0, 0, 0, 0, 0};


RotaryEncoder encoders[] = {
	RotaryEncoder(encoderPins[E_MODE][0], encoderPins[E_MODE][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_VOLUME][0], encoderPins[E_VOLUME][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_SPECIAL][0], encoderPins[E_SPECIAL][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_BRAKE_BIAS][0], encoderPins[E_BRAKE_BIAS][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_TRACTION_CONTROL][0], encoderPins[E_TRACTION_CONTROL][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_ENGINE_MAP][0], encoderPins[E_ENGINE_MAP][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_ANTILOCK_BRAKING_SYSTEM][0], encoderPins[E_ANTILOCK_BRAKING_SYSTEM][1], RotaryEncoder::LatchMode::FOUR3),
	RotaryEncoder(encoderPins[E_TRACKING_CONTROL_CUT][0], encoderPins[E_TRACKING_CONTROL_CUT][1], RotaryEncoder::LatchMode::FOUR3),
};

bool encoderChanged = false;
void encoderInterrupted() {
	encoderChanged = true;
	for (unsigned char i = 0; i < encodersCount; i++) {
		encoders[i].tick();
	}
}

/*
array for buttons and encoders to joystick buttons
e.g.
B_IGNITION = 1
B_ENGINE = 2
B_PIT_LIMITER = 3
...
E_BRAKE_BIAS_UP = 50
E_BRAKE_BIAS_DN = 51
etc so that we can use the same index for both buttons and encoders

*/
const unsigned char totalUserInputs = buttonsCount + (encodersCount * 2);

// setup Joystick Library
Joystick_ joystick{
	JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_GAMEPAD,
	totalUserInputs, 0, // button count, hat switch count
	false, false, false, // x, y, z
	false, false, false, // rx, ry, rz
	false, false, // rudder, throttle
	false, false, false // accelerator, brake, steering
};

// setup controllers for each game
Controller controllers[] = {
	Controller(
		"Joystick",
		new GameJoystick(&joystick),
		 // red hue
		new Color(0, 1.0, 0.5),
		0.8
	),
	Controller(
		"Keyboard",
		new GameKeyboard(),
		 // red hue
		new Color(160, 1.0, 0.5),
		0.8
	),
	Controller(
		"Assetto Corsa Competizione",
		new AssettoCorsaCompetizione(),
		// green hue
		new Color(120, 1.0, 0.4),
		0.4
	),
	Controller(
		"Forza Motorsport",
		new ForzaMotorsport(),
		// cyan hue
		new Color(25, 1.0, 0.5),
		0.4
	),
	Controller(
		"Forza Horizon",
		new ForzaHorizon(),
		// cyan hue
		new Color(180, 1.0, 0.5),
		0.4
	),
	Controller(
		"Low Power",
		new NoFunctions(),
		new Color(0, 1.0, 0.05),
		0.01
	),
};
int controllersCount = sizeof(controllers) / sizeof(controllers[0]);

Controller controller = controllers[0];

void setController(unsigned char index) {
	// end the previous controller
	// controllers[controllerIndex].game->end();
	controllers[controllerIndex].end();
	// set the new controller
	controllerIndex = index % controllersCount;
	controller = controllers[controllerIndex];
	// start the new controller
	controller.begin();
	// get the color from the controller and set the RGB
	RGB rgb = controller.color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
	// get the luminosity from the controller and set the luminosity
	intensity = controller.getIntensity();
	setLuminosity(intensity);

	// print the controller name
	if (DEBUG) {
		SerialUSB.print("Controller: ");
		SerialUSB.print(controller.name);
		SerialUSB.print(" Intensity: ");
		SerialUSB.print(intensity);
		SerialUSB.print(" RGB: ");
		SerialUSB.print(rgb.r);
		SerialUSB.print(", ");
		SerialUSB.print(rgb.g);
		SerialUSB.print(", ");
		SerialUSB.println(rgb.b);
	}
	// check if the controller is a joystick and set the appropriate type
	if (controller.game->isJoystick) {
		joystick.begin();
	}
	else {
		joystick.end();
	}
	
}
void cycleController() {
	unsigned char index = (controllerIndex + 1) % controllersCount;
	setController(index);
}

void sendControllerInput(unsigned char pin, bool state) {
	// if the controller identifier is empty, return joystick button index pressed or released
	stayAwake();
	if (pin == B_MODE) {
		return;
	}
	else {
		controllers[controllerIndex].game->button(pin, state);
	}
}

void adjustIntensity(int direction) {
	float lightness = controller.color->getLightness();
	// intensity = controller.getIntensity();
	if (direction > 0) {
		if (intensity <= 0.15) {
			intensity = min(intensity + INTENSITY_STEP_SMALL, INTENSITY_MAX);
		}
		else {
			intensity = min(intensity + INTENSITY_STEP, INTENSITY_MAX);
		}
		if (lightness <= 0.15) {
			lightness = min(lightness + LIGHTNESS_STEP_SMALL, LIGHTNESS_MAX);
		}
		else {
			lightness = min(lightness + LIGHTNESS_STEP, LIGHTNESS_MAX);
		}
	}
	else {
		if (intensity <= 0.15) {
			intensity = max(intensity - INTENSITY_STEP_SMALL, INTENSITY_MIN);
		}
		else {
			intensity = max(intensity - INTENSITY_STEP, INTENSITY_MIN);
		}
		if (lightness <= 0.15) {
			lightness = max(lightness - LIGHTNESS_STEP_SMALL, LIGHTNESS_MIN);
		}
		else {
			lightness = max(lightness - LIGHTNESS_STEP, LIGHTNESS_MIN);
		}
	}
	if (DEBUG) {
		SerialUSB.print("Adjusting ");
		SerialUSB.print(direction);
		SerialUSB.print(" Intensity: ");
		SerialUSB.print(intensity);
		SerialUSB.print(" and Lightness: ");
		SerialUSB.println(lightness);
	}
	setLuminosity(intensity);
	controller.setIntensity(intensity);
	controller.color->setLightness(lightness);
	RGB rgb = controller.color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
	feedbackVibrate(1);
	feedbackVisual(1);
}

// function to detect if a button is pressed, holding (using timer) and if released and return the appropriate value
void sendInputButton(unsigned char index, unsigned char state) {
	const uint8_t pin = buttonPins[index];
	if (DEBUG) {
		SerialUSB.print("Button ");
		SerialUSB.print(index);
		SerialUSB.print("/");
		SerialUSB.print(totalUserInputs);
		SerialUSB.print(" is ");
		SerialUSB.print(state);
		SerialUSB.print(" as pin ");
		SerialUSB.print(pin);
		SerialUSB.print(" Controller: ");
		SerialUSB.println(controllers[controllerIndex].name);
	}

	if (state == BUTTON_STATE_PRESSED) {
		// check of button is mode button and then cycle controller
		// send button pressed
		feedbackVibrate(1);
		feedbackVisual(1);
		if (index == 0) {
			setLuminosity(1);
			return;
		}
		sendControllerInput(pin, true);
		buttonPressed = true;
	}
	else if (state == BUTTON_STATE_HELD) {
		// send button holding
	}
	else if (state == BUTTON_STATE_RELEASED) {
		// send button released
		if (index == 0) {
			cycleController();
			return;
		}
		sendControllerInput(pin, false);
		buttonPressed = false;
	}
}


void checkButtons() {
	for (unsigned char i = 0; i < buttonsCount; i++) {
		buttons[i].update();
		int state = buttons[i].read();
		if (state == HIGH) {
			if (buttonPositions[i] > 0) {
				buttonPositions[i] = 0;
				sendInputButton(i, BUTTON_STATE_RELEASED);
				continue;
			}
			// sendInputButton(i, BUTTON_STATE_IDLE);
			continue;
		}
		// if the button is pressed and the timer is 0, set the timer to the current time and return 1
		if (buttonPositions[i] == 0) {
			buttonPositions[i] = timer;
			sendInputButton(i, BUTTON_STATE_PRESSED);
			continue;
		}
		// if the button is pressed and the timer is not 0, check if the timer is greater than 500ms and return 2
		if (buttons[i].currentDuration() > BUTTON_HOLD_TIME) {
			sendInputButton(i, BUTTON_STATE_HELD);
			continue;
		}
	}
}


void sendInputEncoder(unsigned char index, int direction) {
	if (DEBUG) {
		SerialUSB.print("E ");
		SerialUSB.print(index);
		SerialUSB.print(" ");
		SerialUSB.println(direction);
	}
	if (index == E_MODE) {
		adjustIntensity(direction);
		feedbackVibrate(1);
		feedbackVisual(1);
		return;
	}
	const signed char point = direction > 0 ? 0 : 1;
	const signed char pin = encoderPins[index][point];
	if (DEBUG) {
		SerialUSB.print("Encoder: ");
		SerialUSB.print(index);
		SerialUSB.print(" Direction: ");
		SerialUSB.print(direction);
		SerialUSB.print(" Point: ");
		SerialUSB.print(point);
		SerialUSB.print(" Pin: ");
		SerialUSB.print(pin);
		SerialUSB.print(" ");

		switch (pin) {
			case E_VOLUME_UP:
				SerialUSB.print("E_VOLUME_UP");
				break;
			case E_VOLUME_DN:
				SerialUSB.print("E_VOLUME_DN");
				break;
			case E_BRAKE_BIAS_UP:
				SerialUSB.print("E_BRAKE_BIAS_UP");
				break;
			case E_BRAKE_BIAS_DN:
				SerialUSB.print("E_BRAKE_BIAS_DN");
				break;
			case E_TRACTION_CONTROL_UP:
				SerialUSB.print("E_TRACTION_CONTROL_UP");
				break;
			case E_TRACTION_CONTROL_DN:
				SerialUSB.print("E_TRACTION_CONTROL_DN");
				break;
			case E_ENGINE_MAP_UP:
				SerialUSB.print("E_ENGINE_MAP_UP");
				break;
			case E_ENGINE_MAP_DN:
				SerialUSB.print("E_ENGINE_MAP_DN");
				break;
			case E_ANTILOCK_BRAKING_SYSTEM_UP:
				SerialUSB.print("E_ANTILOCK_BRAKING_SYSTEM_UP");
				break;
			case E_ANTILOCK_BRAKING_SYSTEM_DN:
				SerialUSB.print("E_ANTILOCK_BRAKING_SYSTEM_DN");
				break;
			case E_TRACKING_CONTROL_CUT_UP:
				SerialUSB.print("E_TRACKING_CONTROL_CUT_UP");
				break;
			case E_TRACKING_CONTROL_CUT_DN:
				SerialUSB.print("E_TRACKING_CONTROL_CUT_DN");
				break;
			case E_MODE_UP:
				SerialUSB.print("E_MODE_UP");
				break;
			case E_MODE_DN:
				SerialUSB.print("E_MODE_DN");
				break;
			default:
				SerialUSB.print("Unknown");
				break;
		}
		SerialUSB.println();
	}

	// convert direction ( 1 vs -1 ) to boolean
	feedbackVibrate(1);
	feedbackVisual(1);
	sendControllerInput(pin, true);
	buttonPressed = false;
}
void checkEncoders() {
	if (encoderChanged) {
		for (unsigned char i = 0; i < encodersCount; i++) {
			// get position of encoder
			int position = encoders[i].getPosition();
			/*
			if (DEBUG) {
				SerialUSB.print("Encoder ");
				SerialUSB.print(i);
				SerialUSB.print(" position: ");
				SerialUSB.print(encoderPositions[i]);
				SerialUSB.print(" -> ");
				SerialUSB.println(position);
			}
			*/
			if (encoderPositions[i] != position) {
				if (DEBUG) {
					SerialUSB.print("Encoder Changed: ");
					SerialUSB.print(i);
				}
				encoderPositions[i] = position;
				sendInputEncoder(i, (int) encoders[i].getDirection());
			}
		}
		encoderChanged = false;
	}
}
void setClockSpeed(uint32_t clockSpeed) {

}

void wakeUp() {
	SerialUSB.println("Waking...");
	sleeping = 0;
	intensity = sleepIntensity;
	controller.setIntensity(intensity);
	controller.color->setLightness(sleepLightness);
	// RGB rgb = controller.color->getRGB();
	// setRGB(rgb.r, rgb.g, rgb.b);
	setController(controllerIndex);
}
void stayAwake() {
	sleepTimer = timer;
	if (sleeping > 0) {
		wakeUp();
	}
}
void hyperSleep() {
	SerialUSB.println("Hyper Sleeping...");
	sleeping = 2;
	setLuminosity(INTENSITY_MIN);
	controller.color->setLightness(LIGHTNESS_MIN);
	RGB rgb = controller.color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
}
void sleep() {
	SerialUSB.println("Sleeping...");
	sleeping = 1;
	sleepIntensity = intensity;
	sleepLightness = controller.color->getLightness();
	intensity = intensity / 16.0;
	setLuminosity(intensity);
	controller.color->setLightness(intensity);
	RGB rgb = controllers[controllerIndex].color->getRGB();
	setRGB(rgb.r, rgb.g, rgb.b);
}

void setup() {
	// set default clock speed
	if (DEBUG || BENCHMARK) {
		SerialUSB.begin(115200);
		SerialUSB.println("Booting...");
	}
	// set resolution to 8 bits
	analogWriteResolution(8);
	// set the pins to output
	pinMode(R_PIN, OUTPUT);
	pinMode(G_PIN, OUTPUT);
	pinMode(B_PIN, OUTPUT);
	for (unsigned char i = 0; i < luminosityGroupsCount; i++) {
		pinMode(luminosityGroups[i], OUTPUT);
		// analogWrite(luminosityGroups[i], 0.1);
	}
	bootAnimation();
	delay(BOOT_DELAY);
	pinMode(VIBRATE_PIN, OUTPUT);
	pinMode(VISUAL_PIN, OUTPUT);
	// set all luminosity groups to output
	delay(BOOT_DELAY);

	// setup all buttons defined above with prefix B_
	bootFeedback(1);
	delay(BOOT_DELAY);
	if (DEBUG) {
		SerialUSB.println("Setting up buttons...");
	}
	for (unsigned char i = 0; i < buttonsCount; i++) {
		// pinMode(buttonPins[i], INPUT_PULLUP);
		if (DEBUG) {
			SerialUSB.print("Button ");
			SerialUSB.print(i);
			SerialUSB.print(" pin: ");
			SerialUSB.println(buttonPins[i]);
		}
		buttons[i].attach(buttonPins[i], INPUT_PULLUP);
		buttons[i].interval(25);
	}
	bootFeedback(2);
	delay(BOOT_DELAY);
	
	// setup all rotary encoders defined above with prefix E_
	if (DEBUG) {
		SerialUSB.println("Setting up encoders...");
	}
	for (unsigned char i = 0; i < encodersCount; i++) {
		if (DEBUG) {
			SerialUSB.print("Encoder ");
			SerialUSB.print(i);
			SerialUSB.print(" pins: ");
			SerialUSB.print(encoderPins[i][0]);
			SerialUSB.print(", ");
			SerialUSB.println(encoderPins[i][1]);
		}

		// pinMode(encoderPins[i][0], INPUT_PULLUP);
		// pinMode(encoderPins[i][1], INPUT_PULLUP);
		encoders[i].setPosition(0);
		// encoders[i] = new RotaryEncoder(encoderPins[i][0], encoderPins[i][1]);
		
		attachInterrupt(digitalPinToInterrupt(encoderPins[i][0]), encoderInterrupted, CHANGE);
		attachInterrupt(digitalPinToInterrupt(encoderPins[i][1]), encoderInterrupted, CHANGE);
	}
	bootFeedback(3);
	delay(BOOT_DELAY);
	bootFeedback(0);
	setController(2);
	stayAwake();
	SerialUSB.println("Setup done");
	// remember the CLKPR register setting
}

void loop() {
	loopCount++;
	timer = millis();
	if ((timer - benchTime) > 5000) {
		if (BENCHMARK) {
			SerialUSB.print("Average loops per second = ");
			SerialUSB.print(loopCount/5);
			SerialUSB.print(" in mode ");
			SerialUSB.print(sleeping);
			SerialUSB.print(" for ");
			SerialUSB.print(sleepTimer);
			SerialUSB.print(" of ");
			SerialUSB.print(timer);
			SerialUSB.print(" (");
			SerialUSB.print(intensity);
			SerialUSB.print("/");
			SerialUSB.print(sleepIntensity);
			SerialUSB.println(")");
			/*
			uint32_t clockSpeed = SystemCoreClock;
			uint32_t defaultClockSpeed = PMC->PMC_MCKR & PMC_MCKR_CSS_Msk;
			SerialUSB.print("Current Clock Speed = ");
			SerialUSB.print(clockSpeed);
			SerialUSB.print(" / ");
			SerialUSB.print(clockSpeed / 1000000);
			SerialUSB.print(" (");
			SerialUSB.print(defaultClockSpeed);
			SerialUSB.print(" / ");
			SerialUSB.print(PMC_MCKR_CSS_SLOW_CLK);
			SerialUSB.print(" / ");
			SerialUSB.print(PMC_MCKR_CSS_MAIN_CLK);
			SerialUSB.print(" / ");
			SerialUSB.print(PMC_MCKR_CSS_PLLA_CLK);
			SerialUSB.print(" / ");
			SerialUSB.print(PMC_MCKR_CSS_UPLL_CLK);
			SerialUSB.println(")");
			*/
		}
		benchTime = timer;
		loopCount = 0;
	}
	checkFeedback();
	checkButtons();
	checkEncoders();
	switch (sleeping) {
		case 1: // unit is sleeping, should it go to hyper sleep?
			// 20 loops per second
			delay(50);
			if (timer - sleepTimer > HYPER_SLEEP_TIME) {
				hyperSleep();
			}
		break;
		case 2: // unit is in hyper sleep...
			// 1 loop per second
			delay(100);
		break;
		default:
			// delay half of a nano second
			delayMicroseconds(500);
			if (timer - sleepTimer > SLEEP_TIME) {
				sleep();
			}
		break;
	}
}
