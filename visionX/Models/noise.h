#ifndef NOISE_H
#define NOISE_H

#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>


using namespace std;
using namespace cv;

class Noise
{
public:
    Noise();
    // Add Uniform Noise to an Image object
    static Mat uniformNoise(Mat img);

    // Add Gaussian Noise to an Image object
    static Mat gasussianNoise(Mat img, float mean, float sigma);

    // Add salt and pepper noise Noise to an Image object
    static Mat saltAndPepperNoise(Mat img, int r);

};

#endif // NOISE_H
