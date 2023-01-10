#include "imageParam.h"

/*Coded on dataBuffer.cpp, imageParam.cpp, BmodeClass.cpp and Bmode.cpp. 
The other codes were provided by my Professor.*/

imageParam::imageParam()
{
numElement = 128; // set given values to numElement, numSample and numScanline
numSample = 3338;
numScanline = 127;
elementPosition = genElementPosition(); // call genElementPosition and assign the returned 1D array to elementPosition
scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition); // call genScanlinePosition and assign the returned 2D array to scanlinePosition
}

imageParam::~imageParam()
{
deletePositionArray(); // release the arrays dynamically allocated for different variables (elementPosition and scanlinePosition)
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{
float *elementLocation; //make pointer needed
elementLocation = new float[numElement];

for (int i = 0; i < numElement; i++){ // for length of numElement
    elementLocation[i] = (i-((float)numElement-1.0)/2.0)*PITCH; // Dynamically allocate a 1D array for elementPosition. PITCH deduces the position of each element
}
return elementLocation;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
std::cout << "Input desired depth: "; // get desired imaging depth from user and assign it to variable
std::cin >> desiredDepth;
std::cout << "Input desired number of pixels: "; // get desired number of pixels from user and assign it to variable
std::cin >> numPixel;

float2 **scanlinePosition;
scanlinePosition = new float2*[numScanline]; 
for (int i = 0; i < numScanline; i++){//Dynamically allocate a 2D array of struct float2 type for scanlinePosition -> for loop occurs for length of numScanline
    scanlinePosition[i] = new float2[numPixel];
    for (int j = 0; j< numPixel; j++){ // for length of numPixel
        scanlinePosition[i][j].x = ((i-(((float)numScanline-1.0)/2.0))*PITCH); //use calculations to derive array
        scanlinePosition[i][j].y = (j*(desiredDepth/(numPixel-1)));
    }
}
return scanlinePosition; // return derived 2D array
}

float imageParam::getXPosition(int scanline, int pixel)
{
return scanlinePosition[scanline][pixel].x; //return the x-coordinate of a pixel specified by scanline and pixel
}

float imageParam::getYPosition(int scanline, int pixel)
{
return scanlinePosition[scanline][pixel].y; // return the y-coordinate of a pixel specified by scanline and pixel
}

float imageParam::getElementPosition(int element)
{
return elementPosition[element]; //return the position of an element specified by element
}

int imageParam::getNumElement()
{
return numElement; //return 
}

int imageParam::getNumSample()
{
return numSample; //return 
}

int imageParam::getNumScanline() 
{
return numScanline; //return 
}

int imageParam::getNumPixel() 
{
return numPixel; //return 
}

void imageParam::deletePositionArray()
{
delete elementPosition; //Release the memory allocated for scanlinePosition and elementPositio
for (int i = 0; i < numScanline; i++){
    delete scanlinePosition[i];
}
}









