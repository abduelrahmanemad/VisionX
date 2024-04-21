#ifndef FREQUENCYCONTROLLER_H
#define FREQUENCYCONTROLLER_H

#include "controller.h"

class FrequencyController : public Controller
{
public:
    FrequencyController();
    QPixmap frequencyFilter(int radius, int Filter);
};

#endif // FREQUENCYCONTROLLER_H
