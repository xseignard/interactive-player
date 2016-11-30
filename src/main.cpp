#include "ofMain.h"
#include "player.h"

int main() {
	ofSetLogLevel(OF_LOG_NOTICE);
	ofSetLogLevel("ofThread", OF_LOG_ERROR);
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new player());
}
