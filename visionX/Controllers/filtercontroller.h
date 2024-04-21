#ifndef FILTERCONTROLLER_H
#define FILTERCONTROLLER_H

#include "controller.h"

class FilterController : public Controller
{
public:
    FilterController();
    QPixmap addNoise(int noiseType, int r, float mean, float sigma);
    QPixmap filterImg(int filterType, int kernelSize);
};

#endif // FILTERCONTROLLER_H
