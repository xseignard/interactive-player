#include "player.h"

/**
 * Setup routine
 */
void player::setup() {
	// some setup conf
	ofBackground(0, 0, 0);
	ofHideCursor();
	ofxOMXPlayerSettings settings;
	settings.videoPath = "/home/pi/idle.mov";
	omxPlayer.setup(settings);
	// starting states
	currentUsbState = true;
	previousUsbState = true;
	currentKeyState = true;
	previousKeyState = true;
	// gpio stuff for shutdown button
	if(wiringPiSetup() == -1){
		ofLogNotice(__func__) << "Error on wiringPi setup";
	}
	// shutdown pin
	pinMode(SHUTDOWN_PIN, INPUT);
	pullUpDnControl(SHUTDOWN_PIN, PUD_UP);
	wiringPiISR(SHUTDOWN_PIN, INT_EDGE_FALLING, &player::shutdown);
	// radar pin (usb hacked port)
	pinMode(USB_PIN, INPUT);
	pullUpDnControl(USB_PIN, PUD_UP);
	// 2nd enigma pin (button with key)
	pinMode(KEY_PIN, INPUT);
	pullUpDnControl(KEY_PIN, PUD_UP);
}

/**
 * Update routine
 */
void player::update() {
	currentUsbState = digitalRead(USB_PIN);
	currentKeyState = digitalRead(KEY_PIN);

	// key is on, play enigma, no matter what is the state of usb
	if (currentKeyState != previousKeyState && !currentKeyState) {
		omxPlayer.loadMovie("/home/pi/test.mp4");
	}
	// usb on, play radar
	else if (currentUsbState != previousUsbState && !currentUsbState) {
		omxPlayer.loadMovie("/home/pi/radar.mov");
	}
	// usb off or key off, play idle
	else if (
		(currentUsbState != previousUsbState && currentUsbState) ||
		(currentKeyState != previousKeyState && currentKeyState)
	) {
		omxPlayer.loadMovie("/home/pi/idle.mov");
	}

	// update previous states
	previousUsbState = currentUsbState;
	previousKeyState = currentKeyState;
}

/**
 * Draw routine
 */
void player::draw() {
	omxPlayer.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (DEBUG) {
		ofDrawBitmapStringHighlight(omxPlayer.getInfo(), 60, 60, ofColor(ofColor::red, 90), ofColor::yellow);
	}
}

/**
 * Shutdown function
 */
void player::shutdown() {
	ofLogNotice(__func__) << "shutdown";
	system("shutdown -h now");
	ofExit();
}
