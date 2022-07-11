#include <Adafruit_NeoPixel.h>
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define MATRIX_TOTAL 64

#define PIN 11         
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
// NEO_KHZ800 800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
// NEO_KHZ400 400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
// NEO_GRB Pixels are wired for GRB bitstream (most NeoPixel products)
// NEO_RGB Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(MATRIX_TOTAL, PIN, NEO_GRB + NEO_KHZ800);


void MatrixSetUp() {
    strip.begin();
}
void slowLightAll(uint32_t clr) {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, clr);
        strip.show();
        delay(20);
    }
}
void slowOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
        strip.show();
        delay(40);
    }
    delay(200);
}
void MatOffAll() {
    for (int pixelNum = 0; pixelNum < MATRIX_TOTAL; pixelNum++) {
        strip.setPixelColor(pixelNum, strip.Color(0, 0, 0));
    }
    strip.show();
}
void lightPixel(int row, int col, uint32_t clr) {
    int pixelNum = row * MATRIX_COLS + col;
    strip.setPixelColor(pixelNum, clr);
    strip.show();
}
void lightBoard(bool isFinished) {
    uint32_t Color;
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            int pixelNum = row * MATRIX_COLS + col;
            switch (board[row][col]) {
                case APPLE_VALUE:
                    Color = strip.Color(20, 0, 20);
                    break;
                case 0:
                    Color = strip.Color(0, 0, 0);
                    if(isFinished)
                        Color = strip.Color(2, 0, 0);
                    break;
                default:
                    Color = strip.Color(0, 20, 20);
                    break;
            }
            //Serial.println(String(row)+","+String(col)+": "+String(Color));
            strip.setPixelColor(pixelNum, Color);
        }
    }
    strip.show();
}
