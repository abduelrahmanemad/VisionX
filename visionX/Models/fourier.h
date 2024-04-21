#ifndef FOURIER_H
#define FOURIER_H

#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace cv;

class Fourier
{
private:

public:
    Fourier();
    static Mat applyDFT(Mat img);
    static Mat applyIDFT(Mat img);
    static Mat applyShifting(Mat img);
};

#endif // FOURIER_H
