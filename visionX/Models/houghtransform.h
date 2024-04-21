#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include <opencv2/opencv.hpp>
#include <time.h>
#include <cmath>
#include "config.h"
using namespace cv;
using namespace std;

class HoughTransform
{
public:
    HoughTransform();
     ////////////////////////////////////////////////  elipse Detection
    struct ellipse_data
    {

        ellipse_data(): x0(-1), y1(-1) {};
        ellipse_data(int _x0, int _y0, double _a, double _b, double th);
        ellipse_data(int _x0, int _y0, double _a, double _b, double th, int _x1, int _y1, int _x2, int _y2);

        double a, b;
        int x0, y0;
        int x1, y1, x2, y2;

        double orient;
    };
    ////////////////////////////////////////////// Line Detection
    static Mat detectEdge(Mat Image); 
    static void polarToCartesian(double rho, int theta, Point& p1, Point& p2);
    static Mat detectLines(Mat Image, int threshold);
    static Mat lineTransform(Mat edges, Mat output ,int threshold, double rho, int theta);
    //////////////////////////////////////////////// Circle Detection
    static Mat preProcessImg(Mat image,Mat &edges,Mat &grayImage,int canny_min_thresold, int canny_max_thresold);
    static Mat Hough_Circle_Transform (Mat image , int threshold , int min_radius =10 , int max_radius =200 , int canny_min_thresold = 100 , int canny_max_thresold = 200 );
    ////////////////////////////////////////////////  elipse Detection
    static vector<vector<vector<short>>> store_hiearchical_pyramid(Mat& edgesM, int min_size = 32);
    static void voting(vector<pair<ellipse_data, int> > &ellipses, const vector<vector<short> > &data, pair<int, int> xbounds,
                pair<int, int> ybounds, int min_dist, int min_vote, pair<int, int> p0, pair<int, int> p1);
    static vector<pair<ellipse_data, int> > hough_transform(vector<vector<short> > &data, int min_vote = 1, int min_dist = 0);
    static ellipse_data ellipse_detection(Mat edges, int minimized_size = 64, int min_vote = 4, int min_dist = 5);
    static vector<ellipse_data> detect_ellipses(Mat src, int minimized_size = 64, unsigned int number_of_ellipses = 1);
    static Mat elipseTransform(Mat edges,unsigned int nmb_of_ellipses = 1,unsigned int minimised_size = 128);
    /////////////////////////////////////// Elipse Detection Imp2
    static void HoughEllipse(cv::Mat img, std::vector<cv::Vec6d>& ellipses, int threshold, int minRadius, int maxRadius);
    static void drawEllipse(cv::Mat& img, std::vector<cv::Vec6d> ellipses, cv::Scalar color);
private:
    static void oneThreadHough(std::vector<cv::Vec2d> nonZeroImg, std::vector<cv::Vec6d>& ellipses, std::mutex& myMutex, int threshold, int minRadius, int maxRadius, int start, int end);

};

#endif // HOUGHTRANSFORM_H
