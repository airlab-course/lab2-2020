#include <LedControl.h>
#include <MD_TCS230.h>

const int displaysCount = 6;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);

#define S0_OUT 2
#define S1_OUT 3
#define S2_OUT 4
#define S3_OUT 5
MD_TCS230 ColorSensor(S2_OUT, S3_OUT, S0_OUT, S1_OUT);

char digit[10][5][3] = {
    {//1
     {0, 1, 0},
     {1, 1, 0},
     {0, 1, 0},
     {0, 1, 0},
     {1, 1, 1}},
    {//2
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1}},
    {//3
     {1, 1, 1},
     {0, 0, 1},
     {0, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {//4
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {0, 0, 1}},
    {//5
     {1, 1, 1},
     {5, 0, 0},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {//6
     {1, 1, 1},
     {1, 0, 0},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {//7
     {1, 1, 1},
     {0, 0, 1},
     {0, 1, 0},
     {1, 0, 0},
     {1, 0, 0}},
    {//8
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {//9
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 1},
     {0, 0, 1},
     {1, 1, 1}},
    {//0
     {1, 1, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}}};

char rgbLetter[3][5][3] = {
    {//R
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 0},
     {1, 0, 1},
     {1, 0, 1}},
    {//G
     {1, 1, 1},
     {1, 0, 0},
     {1, 0, 1},
     {1, 0, 1},
     {1, 1, 1}},
    {//B
     {1, 1, 1},
     {1, 0, 1},
     {1, 1, 0},
     {1, 0, 1},
     {1, 1, 1}}};

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
//note: leading zeroes are there too, so drawn number always has length of 11
void drawNumber(int initialHorizontalOffset, int number)
{
    int first = number / 100 % 10;
    int second = number / 10 % 10;
    int third = number % 10;

    drawSymbol(initialHorizontalOffset, 1, digit[first]);
    drawSymbol(initialHorizontalOffset + 4, 1, digit[second]);
    drawSymbol(initialHorizontalOffset + 8, 1, digit[third]);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Started!");

    sensorData whiteCalibration;
    whiteCalibration.value[TCS230_RGB_R] = 120060;
    whiteCalibration.value[TCS230_RGB_G] = 117520;
    whiteCalibration.value[TCS230_RGB_B] = 157590;
    sensorData blackCalibration;
    blackCalibration.value[TCS230_RGB_R] = 11280;
    blackCalibration.value[TCS230_RGB_G] = 10270;
    blackCalibration.value[TCS230_RGB_B] = 13230;

    ColorSensor.begin();
    ColorSensor.setDarkCal(&blackCalibration);
    ColorSensor.setWhiteCal(&whiteCalibration);

    lc.shutdown(0, false);
    lc.setIntensity(0, 16);
    lc.clearDisplay(0);
}

int *readRGB()
{
    colorData rgb;
    ColorSensor.read();
    while (!ColorSensor.available())
        ;
    ColorSensor.getRGB(&rgb);
    int rgbArray[3] =
        {
            255 - rgb.value[TCS230_RGB_R],
            255 - rgb.value[TCS230_RGB_G],
            255 - rgb.value[TCS230_RGB_B],
        };
    return rgbArray;
}

void loop()
{
    int *rgb;
    rgb = readRGB();
    lc.clearDisplay(0);
    int initialOffset = 1;
    //R
    drawSymbol(initialOffset, 1, rgbLetter[0]);
    drawNumber(initialOffset + 4, rgb[0]);
    //G
    drawSymbol(initialOffset + 16, 1, rgbLetter[1]);
    drawNumber(initialOffset + 20, rgb[1]);
    //B
    drawSymbol(initialOffset + 32, 1, rgbLetter[1]);
    drawNumber(initialOffset + 36, rgb[2]);

    delay(1500);
}
