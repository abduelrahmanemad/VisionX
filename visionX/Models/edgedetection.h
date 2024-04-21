#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>
using namespace cv;

#define STRONG_EDGE 255
#define WEAK_EDGE 40
class EdgeDetection
{
public:
    EdgeDetection();


    static Mat detectEdgeSobel(Mat img);
    static Mat detectEdgeSobelX(Mat img);
    static Mat detectEdgeSobelY(Mat img);

    static Mat detectEdgeRobert(Mat img);
    static Mat detectEdgeRobertX(Mat img);
    static Mat detectEdgeRobertY(Mat img);

    static Mat detectEdgePrewitt(Mat img);
    static Mat detectEdgePrewittX(Mat img);
    static Mat detectEdgePrewittY(Mat img);

    static Mat edgeMagnitude(Mat edgeX, Mat edgeY);
    static Mat Phase_Gradient(Mat gradient_x,Mat gradient_y);



    static Mat hysteresis(Mat thresholded);
    static Mat doubleThresholding(Mat suppressed,float lowThreshold,float HighThreshold);
    static Mat supressionNonMax(Mat magnitudeGradient,Mat phaseGradient);
    static Mat detectEdgeCanny(Mat img ,int t_low ,int t_high);



};

#endif // EDGEDETECTION_H
