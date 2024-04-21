#include "thresholdcontroller.h"
#include "config.h"
#include "Helpers/helpers.h"

ThresholdController::ThresholdController() {}


QPixmap ThresholdController::ThresholdingFilter(int ThresholdingType,int ThresholdValue , int ThresholdkernelSize, int CParam){
    Mat res;
    switch (ThresholdingType) {
    case LocalThresholding:
        res = Threshold::localThresholding(processedImg,ThresholdkernelSize,CParam);
        break;
    case GlobalThresholding:
        res = Threshold::globalThresholding(processedImg,ThresholdValue);
        break;
    default:
        res = img->getOriginalImg();
        break;
    }
    return Helpers::convertMatToPixmap(res);
}
