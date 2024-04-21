#ifndef HARRIS_H
#define HARRIS_H
#include<config.h>

class Harris
{
public:
    Harris();

    static Mat harrisDetection(Mat img , double threshold , int kernelSize);
     static Mat lamdaDetection(Mat img , double threshold , int kernelSize);
    static Mat plotCorners(Mat img, Mat harrisComp  ,double threshold );


};

#endif // HARRIS_H
