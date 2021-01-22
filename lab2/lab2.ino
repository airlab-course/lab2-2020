#include <LedControl.h>
#include <MD_TCS230.h>

const int displays = 6;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displays);

#define S0_OUT 2
#define S1_OUT 3
#define S2_OUT 4
#define S3_OUT 5
MD_TCS230 ColorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

char digit[10][5][3] = {
    {
     {1, 1, 1},
     {1, 0, 1},
     {1, 0, 1}, 
     {1, 0, 1},
     {1, 1, 1}},
    {
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {0, 1, 0}},
    {
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}},
    {
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}},
    {
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1},
     {0, 0, 1}},
    {
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}}
};

void activatePixel(int row, int column)
{
    lc.setLed(column / 8, row, column, true);
}

void drawSymbol(int horizontalOffset, int verticalOffset, char symbol[5][3])
{
    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 3; column++)
        {
            if (symbol[row][column] == 1)
            {
                activatePixel(row + verticalOffset, column + horizontalOffset);
            }
        }
    }
}

void drawNumber(int offset, int number)
{
    int hund = number / 100 % 10;
    int dec = number / 10 % 10;
    int num = number % 10;

    drawSymbol(offset, 1, digit[hund]);
    drawSymbol(offset + 4, 1, digit[dec]);
    drawSymbol(offset + 8, 1, digit[num]);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");
// Не собирал, потому значения для калибровки не знаю(
    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 0;
    whiteCalibration.value[TCS230_RGB_G] = 0;
    whiteCalibration.value[TCS230_RGB_B] = 0;
    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 0;
    blackCalibration.value[TCS230_RGB_G] = 0;
    blackCalibration.value[TCS230_RGB_B] = 0;

    ColorSensor.begin();
    ColorSensor.setDarkCal(&blackCalibration);
    ColorSensor.setWhiteCal(&whiteCalibration);

    lc.shutdown(0, false);
    lc.setIntensity(0, 16);
    lc.clearDisplay(0);
}

void loop()
{
    colorData rgb;
    ColorSensor.read();
    while (!ColorSensor.available());
    ColorSensor.getRGB(&rgb);
    
    lc.clearDisplay(0);
    int offset = 1;

    drawNumber(offset, 255 - rgb.value[TCS230_RGB_R]);

    drawNumber(offset + 16, 255 - rgb.value[TCS230_RGB_G]);

    drawNumber(offset + 32, 255 - rgb.value[TCS230_RGB_B]);

    delay(1000);
}
