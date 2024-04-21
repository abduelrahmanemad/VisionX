#ifndef EDGECONTROLLER_H
#define EDGECONTROLLER_H

#include "controller.h"

class EdgeController : public Controller
{
public:
    EdgeController();
    QPixmap detectEdges(int detectorType, int lowThreshold , int highThreshold);
};

#endif // EDGECONTROLLER_H
