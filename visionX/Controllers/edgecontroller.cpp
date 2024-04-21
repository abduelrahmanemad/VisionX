#include "edgecontroller.h"
#include "config.h"
#include "Helpers/helpers.h"
EdgeController::EdgeController():Controller() {}


QPixmap EdgeController::detectEdges(int detectorType, int lowThreshold , int highThreshold) {
    if(!img->isEmpty()&&img->isProcessed()){
        Mat res;
        switch (detectorType) {
            case SobelDetector:
                res = EdgeDetection::detectEdgeSobel(processedImg);
                break;
            case RobertDetector:
                res = EdgeDetection::detectEdgeRobert(processedImg);
                break;
            case PrewittDetector:
                res = EdgeDetection::detectEdgePrewitt(processedImg);
                break;
            case CannyDetector:
                res = EdgeDetection::detectEdgeCanny(processedImg,lowThreshold ,highThreshold);
                break;
            default:
                res = img->getOriginalImg();
                break;
        }
        processedImg = res;
        return Helpers::convertMatToPixmap(processedImg);
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}
