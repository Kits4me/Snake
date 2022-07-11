#define WAITING_FOR_NEW_GAME	1
#define START_WAITING			2
#define START_NEW_GAME			3
#define PLAYING					4
#define GAME_FINISHED			5
short currState;

#define pinBtn_R 2
#define pinBtn_G 12

bool blinkPartON;
int blinkRate = 500;
unsigned long lastToggleTimeForDisplay;

void Snake_setup() {
	pinMode(pinBtn_R, INPUT_PULLUP);
	pinMode(pinBtn_G, INPUT_PULLUP);
	currState = START_WAITING;
}

void Snake_SM() {
	//Serial.println(currState);
	switch (currState) {
		case START_WAITING:
			startWaitingForNewGame();
			currState = WAITING_FOR_NEW_GAME;
			break;
		case WAITING_FOR_NEW_GAME:
			if (isJstickDown()) {
				currState = START_NEW_GAME;
			}
			break;
		case GAME_FINISHED:
			blinkScore();
			if (areBothButtonsPressed()) {
				currState = START_WAITING;
			}
			break;
		case START_NEW_GAME:
			StartNewGame();
			//printBoard();
			currState = PLAYING;
			//while (true);
			break;
		case PLAYING:
			Snake_gameManager();
			break;
	}
	delay(10);
}
void StartNewGame() {
	Score = 0;
	StartNewBoard();
	SetFrameRate();
	Move();
	SetNewApple();
	LastFrameTime = millis();
	lightBoard(false);
}
void SetFrameRate() {
	// starting at 1000 and coming to 200 at 16 points
	FrameRate = max(200, 1000 - Score * 50);
}
void Snake_FinishGame() {
	lightBoard(true);
	lastToggleTimeForDisplay = millis();
	blinkPartON = true;
	currState = GAME_FINISHED;
}
void Snake_gameManager() {
	showNum(Score, 50);
	jStickMoveCheck();
	if (millis() - LastFrameTime > FrameRate) {
		LastFrameTime = millis();
		lightBoard(Move());
		SetFrameRate();
	}
}
void startWaitingForNewGame() {
	displayOFF();
	StartNewBoard();
	lightBoard(false);
	currState = WAITING_FOR_NEW_GAME;
}
void blinkScore() {
	if (millis() - lastToggleTimeForDisplay >= blinkRate) {
		blinkPartON = !blinkPartON;
		lastToggleTimeForDisplay = millis();
	}
	if (blinkPartON) {
		showNum(Score, 50);
	} else {
		displayOFF();
	}
}
bool areBothButtonsPressed() {
	bool ret = false;
	if ((digitalRead(pinBtn_R) == LOW) && (digitalRead(pinBtn_G) == LOW)) {
		ret = true;
	}
	return ret;
}
