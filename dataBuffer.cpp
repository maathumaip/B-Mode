#include "dataBuffer.h"
using namespace std;
/*Coded on dataBuffer.cpp, imageParam.cpp, BmodeClass.cpp and Bmode.cpp. 
The other codes were provided by my Professor.*/

dataBuffer::dataBuffer()
{
    numElement = 0; // initialize numElement to 0
    numSample = 0; // initialize numSample to 0
    scanline = 0; // initialize scanline to 0
    dataMatrix = NULL; // initialize dataMatrix to NULL
    next = NULL; // initialize next to NULL
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    numElement = inputNumElement; // assign inputNumElement, inputNumSample and inputScanline to their corresponding counterpart
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix(); // createDataMatrix dynamically allocates a 2D complex array. Assigns this to dataMatrix
    loadRFData(dataMatrix, imagFile, realFile); // populate dataMatrix
} 

dataBuffer::~dataBuffer()
{
    deleteDataMatrix(); // call deleteDataMatrix to release the 2D array dynamically allocated for dataMatrix
}

complex **dataBuffer::createDataMatrix()
{
 complex **dataMatrix;
 dataMatrix = new complex*[numElement];
 for (int i = 0; i < numElement; i++){ //dynamically allocate 2D array to dataMatrix -> for loop runs for the length of numElement
    dataMatrix[i] = new complex[numSample];
 }
 return dataMatrix; // return
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
const int max_Size = 15;
char line_looked_at[max_Size];
int track_count = 0;
for (int i = 0; i < numElement; i++){ // use for loop for to populate dataBuffer -> for length of numElement, repeat
    for ( int j = 0; j < numSample; j++){ // repeat for length of numSample
        track_count++;
        imagFile->getline(line_looked_at, max_Size);
        RFData[i][j].imag = atof(line_looked_at);
        realFile->getline(line_looked_at, max_Size);
        RFData[i][j].real = atof(line_looked_at);
    }
}
 return 0; 
}

float dataBuffer::getRealRFData(int element,int sample)
{
    return dataMatrix[element][sample].real; // returns real component of complex data stored
}
float dataBuffer::getImagRFData(int element,int sample)
{
    return dataMatrix[element][sample].imag; // returns imaginary component of complex data
}

void dataBuffer::deleteDataMatrix()
{
    for (int i = 0; i<numElement; i++){ // for length of numElement
        delete dataMatrix[i]; //release the 2D array dataMatrix
    }
}




