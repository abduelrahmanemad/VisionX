#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Models/image.h"
#include <opencv2/opencv.hpp>

class Controller
{
protected:
    Image *img;
    Mat processedImg;

public:
    Controller();
    QPixmap uploadImg(); 
    QPixmap convertToGrayScale();
};

#endif // CONTROLLER_H
