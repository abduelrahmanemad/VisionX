#include "harris.h"

Harris::Harris()
{

}



Mat Harris::harrisDetection(Mat img , double threshold , int kernelSize){
      cvtColor(img, img, COLOR_BGR2GRAY);
   Mat gradientX, gradientY;
   Sobel(img,gradientX,CV_32F,1,0,kernelSize);
   Sobel(img,gradientY,CV_32F,0,1,kernelSize);

   Mat gradientXX = gradientX.mul(gradientX);
   Mat gradientYY = gradientY.mul(gradientY);
   Mat gradientXY = gradientX.mul(gradientY);

   Mat SXX ,SYY,SXY;
    cv::boxFilter(gradientXX,SXX,CV_32FC1,cv::Size(kernelSize,kernelSize));
    cv::boxFilter(gradientYY,SYY,CV_32FC1,cv::Size(kernelSize,kernelSize));
    cv::boxFilter(gradientXY,SXY,CV_32FC1,cv::Size(kernelSize,kernelSize));

    Mat determinant = SXX.mul(SYY) - SXY.mul(SXY);
    Mat trace = SXX + SYY;
    Mat harrisComp = determinant - 0.04* trace.mul(trace);
    normalize(harrisComp, harrisComp, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
    return plotCorners(img,harrisComp,threshold);
}

Mat Harris::lamdaDetection(Mat img, double threshold, int kernelSize)
{
    cvtColor(img, img, COLOR_BGR2GRAY);
        Mat gradientX, gradientY;
        Sobel(img, gradientX, CV_32F, 1, 0, kernelSize);
        Sobel(img, gradientY, CV_32F, 0, 1, kernelSize);

        Mat gradientXX = gradientX.mul(gradientX);
        Mat gradientYY = gradientY.mul(gradientY);
        Mat gradientXY = gradientX.mul(gradientY);

        Mat SXX, SYY, SXY;
        cv::boxFilter(gradientXX, SXX, CV_32FC1, cv::Size(kernelSize, kernelSize));
        cv::boxFilter(gradientYY, SYY, CV_32FC1, cv::Size(kernelSize, kernelSize));
        cv::boxFilter(gradientXY, SXY, CV_32FC1, cv::Size(kernelSize, kernelSize));

        Mat lambda1, lambda2;
        Mat trace = SXX + SYY;
        Mat shiTomasiResponse = min(SXX, SYY);
        normalize(shiTomasiResponse, shiTomasiResponse, 0, 255, NORM_MINMAX, CV_32FC1);
        return plotCorners(img, shiTomasiResponse, threshold);
}

Mat Harris::plotCorners(Mat img, Mat harrisComp  ,double threshold ){

 Mat ret;
 ret = img.clone();
 cv::cvtColor(ret,ret,cv::COLOR_GRAY2BGR);
 for(int i=0;i<ret.rows;i++){
     for(int j=0;j<ret.cols;j++){
          if(harrisComp.at<float>(i,j) > threshold){
              circle(ret,cv::Point(j,i),5,cv::Scalar(255,0,0),1);
          }
     }
 }
return ret;
}
