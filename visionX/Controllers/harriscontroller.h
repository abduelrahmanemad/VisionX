#ifndef HARRISCONTROLLER_H
#define HARRISCONTROLLER_H
#include "controller.h"

class HarrisController : public Controller
{
public:
    HarrisController();
     QPixmap detectCorners(int detectorType,double threshold, int kernelSize);
};

#endif // HARRISCONTROLLER_H
