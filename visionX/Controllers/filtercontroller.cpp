#include "filtercontroller.h"
#include "Helpers/helpers.h"
#include "config.h"

/**
 * @brief Constructor for FilterController class.
 *
 * Initializes a FilterController object.
 */
FilterController::FilterController():Controller() {

}

/**
 * @brief Adds noise to the processed image and returns a QPixmap.
 *
 * This function applies different types of noise to the processed image
 * based on the noiseType parameter and returns the result as a QPixmap.
 *
 * @param noiseType Type of noise to be added. It can be UniformNoise, SaltAndPepperNoise, or GaussianNoise.
 * @param r Parameter used in SaltAndPepperNoise indicating the density of noise.
 * @param mean Mean value for GaussianNoise.
 * @param sigma Standard deviation for GaussianNoise.
 * @return QPixmap representing the image with added noise.
 */
QPixmap FilterController::addNoise(int noiseType, int r=0, float mean=0, float sigma=0){
    if(!img->isEmpty()&&img->isProcessed()){ // Checks if the image is not empty and has been processed
        Mat res;
        switch (noiseType) {
        case UniformNoise:
            res = Noise::uniformNoise(processedImg); // Applies uniform noise
            break;
        case SaltAndPepperNoise:
            res = Noise::saltAndPepperNoise(processedImg,r); // Applies salt and pepper noise
            break;
        case GaussianNoise:
            res = Noise::gasussianNoise(processedImg,mean,sigma); // Applies Gaussian noise
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

/**
 * @brief Applies a filter to the processed image and returns a QPixmap.
 *
 * This function applies different types of filters to the processed image
 * based on the filterType parameter and returns the result as a QPixmap.
 *
 * @param filterType Type of filter to be applied. It can be AvgFilter, MedianFilter, or GaussianFilter.
 * @param kernelSize Size of the filter kernel.
 * @return QPixmap representing the image after applying the filter.
 */
QPixmap FilterController::filterImg(int filterType, int kernelSize){
    if(!img->isEmpty()&&img->isProcessed()){ // Checks if the image is not empty and has been processed
        Mat res;
        switch (filterType) {
        case AvgFilter:
            res = Filter::avgFilter(processedImg,kernelSize); // Applies average filter
            break;
        case MedianFilter:
            res = Filter::medianFilter(processedImg,kernelSize); // Applies median filter
            break;
        case GaussianFilter:
            res = Filter::gaussionFilter(processedImg,kernelSize); // Applies Gaussian filter
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
