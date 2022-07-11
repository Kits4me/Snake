#define BOARD_SIZE 8
int board[BOARD_SIZE][BOARD_SIZE] = { 0 };

#define APPLE_VALUE 100 //more than 64 pixels
int SnakeLen;
#define IDLE	10
#define UP		11
#define DOWN	12
#define RIGHT	13
#define LEFT	14
int SnakeDirection;
int NextSnakeDirection;

typedef struct position{ int row; int col; } ;
position SnakeHeadPosition;

void printBoard() {
	Serial.println("SnakeHeadPosition=("+String(SnakeHeadPosition.row)+","+ String(SnakeHeadPosition.col) +")");
	String L = "";
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			L += String(board[row][col])+" ";
		}
		L += "\n";
	}
	Serial.println(L);
}
void StartNewBoard() {
	SnakeLen = 2;
	SnakeHeadPosition.row = SnakeLen-1;
	SnakeHeadPosition.col = 1;
	SnakeDirection = DOWN;
	NextSnakeDirection = DOWN;
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			board[row][col] = 0;
		}
	}
	for (int k = 0; k < SnakeLen; k++) {
		board[SnakeHeadPosition.row-k][SnakeHeadPosition.col] = 1+k;
	}
}
bool MoveHead() {
	bool ret = true;
	int newRow;
	int newCol;
	SnakeDirection = NextSnakeDirection;
	switch (SnakeDirection) {
		case DOWN:
			newRow = SnakeHeadPosition.row + 1;
			newCol = SnakeHeadPosition.col;
			break;
		case UP:
			newRow = SnakeHeadPosition.row - 1;
			newCol = SnakeHeadPosition.col;
			break;
		case LEFT:
			newRow = SnakeHeadPosition.row;
			newCol = SnakeHeadPosition.col - 1;
			break;
		case RIGHT:
			newRow = SnakeHeadPosition.row;
			newCol = SnakeHeadPosition.col + 1;
			break;
	}
	if ((newRow >= BOARD_SIZE) || (newRow < 0)
		|| (newCol >= BOARD_SIZE) || (newCol < 0)
		|| ((board[newRow][newCol] != APPLE_VALUE)&&(board[newRow][newCol] > 0))) {
		Serial.println("SnakeDirection=" + String(SnakeDirection));
		Serial.println("newPos=(" + String(newRow) + "," + String(newCol) + ")");
		printBoard();
		return false;// GameOver();
	}
	SnakeHeadPosition.row = newRow;
	SnakeHeadPosition.col = newCol;
	if (board[newRow][newCol] == APPLE_VALUE) {
		//setting the head before having new apple
		// so apple won't be in head place
		board[SnakeHeadPosition.row][SnakeHeadPosition.col] = 1;
		EatApple();
	} else {
		board[SnakeHeadPosition.row][SnakeHeadPosition.col] = 1;
	}

	return true;
}
void EatApple() {
	SnakeLen++;
	Score++;
	SetNewApple();
}
void SetNewApple() {
	int r, c;
	do {
		r = random(BOARD_SIZE);
		c = random(BOARD_SIZE);
	} while (board[r][c] != 0);
	board[r][c] = APPLE_VALUE;
}
bool Move() {
	if (!MoveHead()) {
		Snake_FinishGame();
		return true;
	} else {
		for (int row = 0; row < BOARD_SIZE; row++) {
			for (int col = 0; col < BOARD_SIZE; col++) {
				if ((board[row][col] > 0) &&
					(!((row == SnakeHeadPosition.row) && (col == SnakeHeadPosition.col)))) {
					if (board[row][col] != APPLE_VALUE) {
						board[row][col]++;
						if (board[row][col] > SnakeLen) {
							board[row][col] = 0;
						}
					}
				}
			}
		}
		return false;
	}
}

