#include <LedControl.h>

const int displaysCount = 1;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, displaysCount);

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
    lc.setLed(0, row, column, true); //count addr also
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
    lc.shutdown(0, false);
    lc.setIntensity(0, 16);
    lc.clearDisplay(0);
}

int* readRGB(){
    
}

void loop()
{
    int* rgb;
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
