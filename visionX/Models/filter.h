#ifndef FILTER_H
#define FILTER_H


#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace cv;


// Edge detection --> Grey scale image 
// Smoothing --> Grey scale image
// TODO: Convert the filter functions to grayscale



class Filter
{
private:
    static Mat gaussianKernel(int kernelSize, float sigma);
public:

    // Initiallize Filter object
    Filter();

    // Apply gaussian filter to the image
    static Mat gaussionFilter(Mat img,int kernelSize);

    // Apply median filter to the image
    static Mat medianFilter(Mat img,int kernelSize);

    // Apply average filter to the image
    static Mat avgFilter(Mat img,int kernelSize);

    // Apply Freq Filter
    static Mat applyFrequencyFilter(Mat img,int radius,int Filter);

    //----------------------------------------------

    // Convert the image to gray scale
    static Mat convertToGrayScale(Mat img);

    static Mat detectEdgeSobel(Mat img);
    static Mat detectEdgeSobelX(Mat img);
    static Mat detectEdgeSobelY(Mat img);

    static Mat detectEdgeRobert(Mat img);
    static Mat detectEdgeRobertX(Mat img);
    static Mat detectEdgeRobertY(Mat img);

    static Mat detectEdgePrewitt(Mat img);
    static Mat detectEdgePrewittX(Mat img);
    static Mat detectEdgePrewittY(Mat img);

    static Mat detectEdgeCanny(Mat img);
    static Mat edgeMagnitude(Mat edgeX, Mat edgeY);

    // OpenCV filters
    static Mat opencvGaussianFilter(Mat img, int kernelSize);
    static Mat opencvMedianFilter(Mat img, int kernelSize);
    static Mat opencvAvgFilter(Mat img, int kernelSize);

};

#endif // FILTER_H
