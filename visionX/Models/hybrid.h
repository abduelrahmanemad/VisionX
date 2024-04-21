#ifndef HYBRID_H
#define HYBRID_H

#include <bits/stdc++.h>
#include<opencv2/opencv.hpp>
#include<config.h>
using namespace cv;

class Hybrid
{
public:
    //constructor
    Hybrid();
    static Mat mixImg(Mat originalImga, Mat originalImgb, int maskRadiusLP,int maskRadiusHP);

};

#endif // HYBRID_H
