#include "houghcontroller.h"
#include "Helpers/helpers.h"


HoughController::HoughController():Controller()
{

}

QPixmap HoughController::detectLines(int threshold)
{
    Mat res;
    res = HoughTransform::detectLines(img->getOriginalImg(),threshold);
    return Helpers::convertMatToPixmap(res);

}

QPixmap HoughController::detectCircles(int threshold ,int minRadius, int maxRadius)
{
    Mat res;
    res = HoughTransform::Hough_Circle_Transform(img->getOriginalImg(),threshold,minRadius,maxRadius);
    return Helpers::convertMatToPixmap(res);
}

QPixmap HoughController::detectEllipses(int threshold ,int minRadius, int maxRadius)
{
    Mat res,edges;
    img->getOriginalImg().copyTo(res);
    edges=img->getOriginalImg();
    Canny(img->getOriginalImg(), edges, 100, 200);
    std::vector<cv::Vec6d> ellipses;
    HoughTransform::HoughEllipse(edges, ellipses, threshold, minRadius, maxRadius);
    HoughTransform::drawEllipse(res, ellipses, cv::Scalar(0,0,255));
    return Helpers::convertMatToPixmap(res);
}
