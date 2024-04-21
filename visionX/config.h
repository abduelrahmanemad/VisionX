// Use this file in cpp files to avoid Circular Depnd.
#ifndef CONFIG_H
#define CONFIG_H

#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>
#include"Models/noise.h"
#include"Models/filter.h"
#include "Models/image.h"
#include "Models/edgedetection.h"
#include "Models/fourier.h"
#include "Models/hybrid.h"
#include "Models/histogram.h"
#include "Models/threshold.h"
#include "Models/houghtransform.h"
#include <QString>
#include <QFileDialog>
#include <QCoreApplication>
#include <QDir>

using namespace std;
using namespace cv;
// externs


const double PI = 3.14159265358979323846264338327950288;
const double deg2rad = (CV_PI/180.0);

// digital scale space configuration and keypoint detection
const int MAX_REFINEMENT_ITERS = 5;
const float SIGMA_MIN = 0.8;
const float MIN_PIX_DIST = 0.5;
const float SIGMA_IN = 0.5;
const int N_OCT = 8;
const int N_SPO = 3;
const float C_DOG = 0.015;
const float C_EDGE = 10;

// computation of the SIFT descriptor
const int N_BINS = 36;
const float LAMBDA_ORI = 1.5;
const int N_HIST = 4;
const int N_ORI = 8;
const float LAMBDA_DESC = 6;

// feature matching
const float THRESH_ABSOLUTE = 350;
const float THRESH_RELATIVE = 0.7;


extern string birdPth;
extern string catPth;
extern string cutiePth;
extern string palestinePth;
extern string whalePth;

 enum NoiseType{
    UniformNoise = 1,
    SaltAndPepperNoise = 2,
    GaussianNoise = 3
};

 enum FilterType{
    AvgFilter = 1,
    MedianFilter,
    GaussianFilter,
    HighPassFilter,
    LowPassFilter
};

 enum ThresholdingType{
     LocalThresholding = 1,
     GlobalThresholding,
 };

 enum cornerDetectionType{
      HarrisDetector = 1,
      LambdaDetector,
 };

 struct CornerDetectionParams{
    int kernelSize = 3;
 };

 struct FilterAndEdgeParams{
    int kernelSize = 3;
    float SigmaFilter = 0;
    float SigmaNoise = 0;
    float MeanNoise = 0;
    float SaltToPepperNoise = 15;
    float CannyLowThreshold = 50;
    float CannyHighThreshold = 150;

 };

 struct ThresholdParams{
    int ThresholdKernelSize = 3;
    int ThresholdValue = 210;
    int CParam = 2;

 };

 enum DetectorType{
    SobelDetector = 1,
    RobertDetector = 2,
    PrewittDetector = 3,
    CannyDetector   = 4
};

 enum ShapeType{
     Line,
     Circle,
     Ellipse
 };

 enum lossType{
     SSDIndex = 0,
     CrossCorrIndex = 1,
 };

 enum Pages{
    FilterPage = 0,
    EdgeDetectionPage = 1,
    HistogramPage = 2,
    ThresholdingPage = 3,
    HybridPage = 4,
    FrequencyPage = 5
};
#endif // CONFIG_H
