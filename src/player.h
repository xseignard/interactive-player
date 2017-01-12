#pragma once

#include "ofMain.h"
#include "ofxOMXPlayer.h"
#include "wiringPi.h"

class player : public ofBaseApp {
	public:
		// openframeworks routines
		void setup();
		void update();
		void draw();
		// instance of omxplayer
		ofxOMXPlayer omxPlayer;
		// radar pin (usb hacked port)
		const static int USB_PIN = 0;
		// 2nd enigma pin (button with key)
		const static int KEY_PIN = 2;
		// shutdown button
		const static int SHUTDOWN_PIN = 7;
		static void shutdown();
		// current usb pin state
		bool currentUsbState;
		// previous usb pin state
		bool previousUsbState;
		// current key pin state
		bool currentKeyState;
		// previous key pin state
		bool previousKeyState;
		// debug flag
		const static bool DEBUG = false;
};
