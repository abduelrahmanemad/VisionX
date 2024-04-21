#ifndef MATCHCONTROLLER_H
#define MATCHCONTROLLER_H
#include "controller.h"


class MatchController : public Controller
{

public:
    MatchController();
    Image *img2;
    QPixmap uploadImg2();
    QPixmap convertToGrayScale2();
    Mat getOriginalImgMat();
    void applyMatching(int lossType, Rect & roi);
};

#endif // MATCHCONTROLLER_H
