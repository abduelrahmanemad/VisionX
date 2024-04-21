#include "imagecontroller.h"
#include"config.h"

ImageController::ImageController() {
    this->img = new Image();
}



QPixmap ImageController::uploadImg() {
    QString appDirPath = QCoreApplication::applicationDirPath();
    QString path = QFileDialog::getOpenFileName(nullptr, "Choose an Image", appDirPath);

    if (!path.isEmpty()) {
        delete this->img;
        this->img = new Image(path.toStdString());
        if (!img->isEmpty()) {
            Mat lol = this->img->getOriginalImg();
            cout<<lol.type();
            return Helpers::convertMatToPixmap(this->img->getOriginalImg());
        }
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}


QPixmap ImageController::getGreyScaledImg() {
    if(!img->isEmpty()){
        processedImg = Filter::convertToGrayScale(img->getOriginalImg());
        img->setIsProcessed(true);
        return Helpers::convertMatToPixmap(processedImg);
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}


QPixmap ImageController::getProcessedImg() {
    if(!processedImg.empty()&&img->isProcessed()){
        return Helpers::convertMatToPixmap(processedImg);
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}

QPixmap ImageController::FilterImg(int filterType,int kernelSize) {
    if(!img->isEmpty()&&img->isProcessed()){
        Mat res;
        switch (filterType) {
            case AvgFilter:
                res = Filter::avgFilter(processedImg,kernelSize);
                break;
            case MedianFilter:
                res = Filter::medianFilter(processedImg,kernelSize);
                break;
            case GaussianFilter:
                res = Filter::gaussionFilter(processedImg,kernelSize);
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

QPixmap ImageController::addNoise(int noiseType, int r, float mean, float sigma) {
    if(!img->isEmpty()&&img->isProcessed()){
        Mat res;
        switch (noiseType) {
            case UniformNoise:
            res = Noise::uniformNoise(processedImg);
                break;
            case SaltAndPepperNoise:
                res = Noise::saltAndPepperNoise(processedImg,r);
                break;
            case GaussianNoise:
                res = Noise::gasussianNoise(processedImg,mean,sigma);
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

QPixmap ImageController::DetectEdges(int detectorType, int lowThreshold , int highThreshold) {
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

QPixmap ImageController::frequencyFilter(int radius, int Filter){
    if(!img->isEmpty()&&img->isProcessed()){
        Mat res;
        res = img->getOriginalImg();
        res= Filter::convertToGrayScale(res);
        res = Filter::applyFrequencyFilter(res, radius, Filter);
        res.convertTo(res,CV_8UC1);
        processedImg = res;
        return Helpers::convertMatToPixmap(processedImg);
    }
}






