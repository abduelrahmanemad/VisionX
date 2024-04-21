#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include<opencv2/opencv.hpp>

#include<iostream>
#include<cstdio>
#include"config.h"

using namespace cv;

struct HistogramData {
    Mat plot_b_hist;
    Mat plot_g_hist;
    Mat plot_r_hist;
    Mat hist_image;
};

struct cumulativeData{
    Mat red;
    Mat green;
    Mat blue;
};

class Histogram{
private:


public:

    static Mat normalizeImg(Mat input_image);

    static Mat equalizeImg(const Mat& input_image);

    static Mat plotHistogram(Mat histogram,int r=0,int g=0,int b=0);

    static Mat calculateHistogram(Mat image);

    static Mat distributionCurve(Mat histogram,int b,int g, int r);

    static cumulativeData plot_rgb_distribution_function(Mat image);

    static HistogramData rgbHistogram(Mat inputImage);

};


#endif // HISTOGRAM_H
