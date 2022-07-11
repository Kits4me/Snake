
/* this sketch uses libraries:
* https://github.com/AlexisTM/ASCIIDic
* https://github.com/AlexisTM/NX7Seg
* need to download zip and install
*/
//
#include <ASCIIDic.h>
#include <NX7Seg.h>

#define CLK_DIO   8   // sclk
#define LATCH_DIO 7 //rclk
#define DATA_DIO  5  // dio
//bool reverse = false;
bool reverse = true;

nx7seg my4x7seg = nx7seg(LATCH_DIO, CLK_DIO, DATA_DIO, reverse);

void setup_7seg() {
    /* Set DIO pins to outputs */
    pinMode(LATCH_DIO, OUTPUT);
    pinMode(CLK_DIO, OUTPUT);
    pinMode(DATA_DIO, OUTPUT);
}

void showNum(int sec, int refreshTime) {
    my4x7seg.writeInt(sec);
    my4x7seg.refresh(refreshTime);
}
//void showFinishedScore(int gameScore, int refresh_time) {
//    char* data = "----";
//    data[2] = char('0' + gameScore % 10);
//    if (gameScore >= 10) {
//        data[1] = char('0' + (gameScore / 10) % 10);
//    }
//    my4x7seg.write(data, 4);
//    my4x7seg.refresh(refresh_time);
//}
void displayOFF() {
    char* data = "    ";
    my4x7seg.write(data, 4);
    my4x7seg.refresh(1500);
}
//void displayVoid(int refresh_time) {
//    char* data = "----";
//    my4x7seg.write(data, 4);
//    my4x7seg.refresh(refresh_time);
//}



