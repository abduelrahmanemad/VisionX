#ifndef HOUGHCONTROLLER_H
#define HOUGHCONTROLLER_H
#include "controller.h"
#include "config.h"


class HoughController : public Controller
{
public:
    HoughController();
    QPixmap detectLines(int threshold);
    QPixmap detectCircles(int threshold,int minRadius , int maxRadius);
    QPixmap detectEllipses(int threshold=8 ,int minRadius=20, int maxRadius=70);
};

#endif // HOUGHCONTROLLER_H
