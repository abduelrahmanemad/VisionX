#include "harriscontroller.h"
#include "config.h"
#include "Helpers/helpers.h"
#include "Models/harris.h"

HarrisController::HarrisController()
{

}

QPixmap HarrisController::detectCorners(int detectorType,double threshold, int kernelSize){
    if(!img->isEmpty()){ // Checks if the image is not empty and has been processed
        Mat res;
        switch (detectorType) {
        case HarrisDetector:
            res = Harris::harrisDetection(img->getOriginalImg(),threshold,kernelSize);
            break;
        case LambdaDetector:
            res = Harris::lamdaDetection(img->getOriginalImg(), threshold, kernelSize);
            break;
        default:
            res = img->getOriginalImg();
            break;
        }
        processedImg = res;
        return Helpers::convertMatToPixmap(processedImg); // Converts the processed image to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if conditions are not met
}

