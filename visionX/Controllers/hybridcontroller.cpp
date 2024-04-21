#include "hybridcontroller.h"
#include "Helpers/helpers.h"
#include "config.h"

HybridController::HybridController():Controller() {
     img2 = new Image();
}


QPixmap HybridController::uploadImg2() {

    QString path = Helpers::openFile();
    if(!path.isEmpty()){
        delete img2;
        img2 = new Image(path.toStdString());
        if(!img2->isEmpty()){
            return Helpers::convertMatToPixmap(img2->getOriginalImg());
        }
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}

QPixmap HybridController::convertToGrayScale2() {
    if(!img2->isEmpty()){
        processedImg = Filter::convertToGrayScale(img2->getOriginalImg());
        img2->setIsProcessed(true);
        return Helpers::convertMatToPixmap(processedImg);
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1));
}

QPixmap HybridController::Mix(int maskRadiusLP, int maskRadiusHP ){
  Mat originalImga,originalImgb;
  originalImga= img->getOriginalImg();
  originalImga = Filter::convertToGrayScale(originalImga);
  originalImgb= img2->getOriginalImg();
  originalImgb = Filter::convertToGrayScale(originalImgb);
  Mat mixedImg = Hybrid::mixImg(originalImga ,originalImgb,maskRadiusLP,maskRadiusHP );
  mixedImg.convertTo(mixedImg,CV_8UC1);
  imwrite("yah.jpg",mixedImg);
  return Helpers::convertMatToPixmap(mixedImg);
}
