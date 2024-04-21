#include "hybrid.h"

Hybrid::Hybrid() {}

Mat Hybrid::mixImg(Mat originalImga,Mat originalImgb,int maskRadiusLP,int maskRadiusHP){
    int h , w;
    w = min(originalImga.size[0],originalImgb.size[0]);
    h = min(originalImga.size[1],originalImgb.size[1]);
    cv::resize(originalImga, originalImga,cv::Size(w,h));
    cv::resize(originalImgb, originalImgb,cv::Size(w,h));
    cv::Mat lowpassImg, highpassImg;
    lowpassImg = Filter::applyFrequencyFilter(originalImga,maskRadiusLP,HighPassFilter);
    highpassImg = Filter::applyFrequencyFilter(originalImgb,maskRadiusHP,LowPassFilter);
    cv::Mat hybridImg;
    hybridImg = lowpassImg + highpassImg;
    cv::normalize(hybridImg, hybridImg, 0, 255, cv::NORM_MINMAX);
    return hybridImg;
}
