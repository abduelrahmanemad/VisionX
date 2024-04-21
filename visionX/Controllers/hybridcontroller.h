#ifndef HYBRIDCONTROLLER_H
#define HYBRIDCONTROLLER_H
#include "controller.h"
#include "qpixmap.h"

class HybridController : public Controller
{
public:
    HybridController();
     Image *img2;
     QPixmap uploadImg2();
     QPixmap convertToGrayScale2();
     QPixmap Mix(int maskRadiusLP, int maskRadiusHP);
};

#endif // HYBRIDCONTROLLER_H
