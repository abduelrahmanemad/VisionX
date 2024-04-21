#include "matchcontroller.h"
#include "config.h"
#include "Helpers/helpers.h"
#include "Models/matching.h""

MatchController::MatchController():Controller()
{
  img2 = new Image();
}

QPixmap MatchController::uploadImg2()
{
    QString path = Helpers::openFile(); // Opens a file dialog to select an image file
    if(!path.isEmpty()){
        delete img2; // Deletes any previous image
        img2 = new Image(path.toStdString()); // Loads the image from the selected path
        if(!img2->isEmpty()){ // Checks if the image is successfully loaded
            return Helpers::convertMatToPixmap(img2->getOriginalImg()); // Converts the image to QPixmap
        }
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if image loading fails
}

QPixmap MatchController::convertToGrayScale2() {
    if(!img2->isEmpty()){ // Checks if there is a valid image
        processedImg = Filter::convertToGrayScale(img2->getOriginalImg()); // Converts the image to grayscale
        img2->setIsProcessed(true); // Marks the image as processed
        return Helpers::convertMatToPixmap(processedImg); // Converts the processed image to QPixmap
    }
    return Helpers::convertMatToPixmap(Mat::zeros(1,1,CV_8UC1)); // Returns a blank QPixmap if there is no valid image
}

Mat MatchController::getOriginalImgMat()
{
  return img->getOriginalImg();
}

void MatchController::applyMatching(int lossType, Rect & roi)
{
    if(!img->isEmpty() && !img2->isEmpty()){ // Checks if the image is not empty and has been processed
          switch (lossType) {
          case SSDIndex:
              Matching::SumOfSqauredDiff(img->getOriginalImg(),img2->getOriginalImg(),roi);
              break;
          case CrossCorrIndex:
              Matching::CrossCorrelation(img->getOriginalImg(),img2->getOriginalImg(),roi);
              break;
          }
      }
}


