#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include "Models/image.h"
#include <opencv2/opencv.hpp>
#include "Models/noise.h"
#include "Helpers/helpers.h"

class ImageController
{
private:
    Image *img;
    Mat processedImg;
    
public:
    ImageController();
    QPixmap uploadImg();
    QPixmap getGreyScaledImg();
    QPixmap getProcessedImg();
    QPixmap FilterImg(int filterType, int kernelSize);
    QPixmap addNoise(int noiseType, int r, float mean, float sigma);

    QPixmap DetectEdges(int detectorType, int lowThreshold , int highThreshold);
    QPixmap frequencyFilter(int radius, int Filter);

};

#endif // IMAGECONTROLLER_H&
