#ifndef THRESHOLDCONTROLLER_H
#define THRESHOLDCONTROLLER_H
#include "controller.h"
#include "config.h"
class ThresholdController :public Controller
{
public:
    ThresholdController();
    QPixmap ThresholdingFilter(int ThresholdingType,int ThresholdValue , int ThresholdkernelSize, int CParam);

private:
   ThresholdParams thresholdParams;
};

#endif // THRESHOLDCONTROLLER_H
