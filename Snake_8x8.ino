/*
 Name:		Snake_8x8.ino
 Created:	7/11/2022 12:08:44 PM
 Author:	amird
*/

unsigned long LastFrameTime;
int FrameRate;
int Score;

// the setup function runs once when you press reset or power the board
void setup() {
	randomSeed(analogRead(A7));
	setup_7seg();
	jStickSetUp();
	MatrixSetUp();
	Snake_setup();
}

// the loop function runs over and over again until power down or reset
void loop() {
	Snake_SM();
}
