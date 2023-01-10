#include "BmodeClass.h"

/*Coded on dataBuffer.cpp, imageParam.cpp, BmodeClass.cpp and Bmode.cpp. 
The other codes were provided by my Professor.*/

BmodeClass::BmodeClass()
{
imparams = NULL; //set imparams to NULL
RFData = NULL; //set RFData to NULL
next = NULL; //set next to NULL
line = 0; //set line to 0
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
imparams = params; //set imparams to params
RFData = data; //set RFData to data
line = numline; //set line to numline
scanline = createScanline(imparams->getNumPixel()); // invoke to allocate memory for scanline
beamform(); //invoke to beamform the scanline
}

BmodeClass::~BmodeClass()
{
deleteScanline(); //release the arrays dynamically allocated for scanline
}

float *BmodeClass::createScanline(int numPixel)
{
float *mem; //dynamically allocate a 1D float array of size numPixel as mem
mem = new float[numPixel];
return mem; //return mem
}

void BmodeClass::beamform()
{
float time = 0;
int s = 0;
float pReal = 0;
float pImag = 0;

for (int i = 0; i < imparams -> getNumPixel(); i++){  //for length of imparams -> update how tbackward is calculated based on the equation given
    pReal = 0;
    pImag = 0;

    for (int j = 0; j<imparams -> getNumElement(); j++){ //for length of imparams
        time = (imparams -> getYPosition(line,i) + sqrt(pow(imparams->getYPosition(line, i), 2) + pow(imparams->getXPosition(line,i)-imparams->getElementPosition(j),2)))/imparams->SOS; //calculate time
        s = floor(time*imparams->FS); // calculate s
        if (s<imparams->getNumSample()){ 
            pReal += RFData->getRealRFData(j,s);
            pImag += RFData->getImagRFData(j,s);
        }
        scanline[i] = sqrt(pow(pReal, 2) + pow(pImag, 2));
    }
}
}

void BmodeClass::getScanline(float *data)
{
for (int i = 0; i< imparams->getNumPixel(); i++){ //copy the content inside scanline to data element-by-elemen
    data[i] = scanline[i];
}
}

void BmodeClass::deleteScanline()
{
 delete scanline;  //release the memory allocated for scanline
}