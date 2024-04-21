#ifndef MATCHING_H
#define MATCHING_H
#include<config.h>


class Matching
{
public:
    Matching();
    static void SumOfSqauredDiff(Mat img , Mat src, Rect & roi);
    static void CrossCorrelation(Mat img, Mat src, Rect & roi);
    static void applyMatching(Mat img1,Mat img2, vector<Vec3d>& matched);

};

#endif // MATCHING_H
