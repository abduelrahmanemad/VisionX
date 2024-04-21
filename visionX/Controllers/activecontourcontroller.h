#ifndef ACTIVECONTOURCONTROLLER_H
#define ACTIVECONTOURCONTROLLER_H


#include "controller.h"

class ActiveContourController : public Controller
{
public:
    ActiveContourController();
    QImage uploadImg();
    Mat getMatImg();
};

#endif // ACTIVECONTOURCONTROLLER_H
