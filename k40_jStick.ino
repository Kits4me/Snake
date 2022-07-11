#define jXpin A6
#define jYpin A5

int jStickChangeMsec = 50;
long jStickChangeTime;

void jStickSetUp() {
    jStickChangeTime = millis();
}
bool isJstickDown() {
    int jPosY = analogRead(jYpin);
    //Serial.println("jPosY="+String(jPosY));
    if (jPosY > 800) {
        return true;
    }
    return false;
}
void jStickMoveCheck() {
    int jPosX = analogRead(jXpin);
    int jPosY = analogRead(jYpin);

    bool changeEntered = false;
    if ((SnakeDirection == UP) || (SnakeDirection == DOWN)) {
        //change only on X
        if ((jPosX < 200)&&(NextSnakeDirection != LEFT)) {
            NextSnakeDirection = LEFT;
            changeEntered = true;
        } else if ((jPosX > 800) && (NextSnakeDirection != RIGHT)) {
            NextSnakeDirection = RIGHT;
            changeEntered = true;
        }
    }
    if ((SnakeDirection == LEFT) || (SnakeDirection == RIGHT)) {
        //change only on Y
        if ((jPosY < 200) && (NextSnakeDirection != UP)) {
            NextSnakeDirection = UP;
            changeEntered = true;
        } else if ((jPosY > 800) && (NextSnakeDirection != DOWN)) {
            NextSnakeDirection = DOWN;
            changeEntered = true;
        }
    }
    if (changeEntered) {
        shortBeep();
    }

}
