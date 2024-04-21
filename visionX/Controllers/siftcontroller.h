#ifndef SIFTCONTROLLER_H
#define SIFTCONTROLLER_H

#include "controller.h"
#include "config.h"

class SiftController : public Controller
{
public:
    SiftController();
    Image *img2;
    QPixmap uploadImg2();
    QPixmap convertToGrayScale2();
    Mat getOriginalImgMat();
    Mat getOriginalImgMat2();

};

#endif // SIFTCONTROLLER_H
